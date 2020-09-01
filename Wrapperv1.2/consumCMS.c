
#ifdef __linux__
#include <linux/version.h>
#ifdef LINUX_VERSION_CODE >= KERNEL_VERSION(2,6,17)
#define _GNU_SOURCE
#endif
#endif


#include "invokeWrapper.h"
#include "wrapperCom.h"
#include "consumCMS.h"
#include "devSpec.h"
#include "handleQue.h"
#include "xmlParse.h"
#include "xmlResp.h"
#include <poll.h>

extern pthread_mutex_t mutex;// mutex
extern pthread_mutex_t fmutex;// mutex for file
extern pthread_mutex_t Rmutex;// mutex for file
extern pid_t  current_pid;

static int deviceFd ; //  Device descriptor
extern xmlQueue xmlQ ;

static jmp_buf set_pt ;  /* typedef int */
static void signal_handler( int ) ;

int getSysId();

extern long  cmdTimer[MAXDEVCMD];

void checkDevEvent(devResponse *);
void devSpecExecute(parseCMSCmd *, devResponse *, int ); 

/*------------------------------------------------------------*/

 static void signal_handler(int sys_signal ) {
     longjmp(set_pt, sys_signal);
  }

void terminateConsumer(int rc)
{
  int i=0;
     xmlQ.store = 0; xmlQ.retrieve = 0; DeviceComm = TIMEOUT;
      for(i=0; i < MAXDEVCMD;i++) {
            cmdTimer[i]=0;
      }
     fprintf(stderr, " consumCMS : Received signal %d \n", rc);
     fprintf(stderr, "ERROR : DEVICE CONNECTION BROKEN: DeviceCom %d\n", DeviceComm);

     pthread_mutex_unlock(&mutex);

    if(  shutdown(deviceFd, SHUT_RDWR) == ERROR) {
           fprintf(stderr, " consumeCMS: terminateConsumer() Socket fd %d not closed \n",deviceFd);
     }
     if ( close(deviceFd) == ERROR) {
           fprintf(stderr, " consumeCMS: terminateConsumer() Socket fd %d not closed \n",deviceFd);
     }

//    pthread_exit(NULL); 
}

int getSysId() 
{
    extern char subSysID[DATALEN];
    int i=0;
   // update devSpec.h enum for this.
    char *devices[] = { "sentinal", "sigcon", "frontend", "backend", "servo", "dataserver" };

    for( i=0; i < TOTALSYS; i++) {
       if(!strcasecmp(devices[i],subSysID)) {
          return i;
       }
    }
    
    if(i== TOTALSYS) { return ERROR;}
}


void checkDevEvent(devResponse *respPtr) 
{
  int catchRevent=0;

           bzero( (char *)respPtr,devResponseSize);
           while ( (catchRevent = recvRespPkt(&deviceFd,respPtr)) == 0 )
           {
                fprintf(stderr, " RESPONSE FROM DEVICE ?\n");
                printDevResp(respPtr);
                sendRespToCMS(respPtr);
                usleep(300000);
           }

	   if (  (catchRevent&POLLHUP) || (catchRevent&POLLRDHUP)  ||  (catchRevent&POLLNVAL)) {
                  fprintf(stderr," checkDevEvent : pollfd got singla %d \n",catchRevent);
                  terminateConsumer(catchRevent);
                  pthread_exit(NULL); /* exit */ 
           }
           fprintf(stderr,"+");
           return;
}

//
// Handling Asynchronous event like domon, trackcmd failure
// with event > 12 to keep command allive ~ May, 2012
//
void devSpecExecute(parseCMSCmd  *cmdPtr, devResponse *respPtr,int asynch)
{
  #define DEVRESP_TO 5
  int catchRevent=0;
  long sTime=0, nxtTime=0;

    checkDevEvent(respPtr); // Check any pending Event before sending the packet to theCMS

    if(!sendCmdPkt(&deviceFd, cmdPtr))
    {
        sTime = time(NULL); 
        do
        {
             nxtTime=time(NULL);  
             bzero( (char *)respPtr,devResponseSize);
             if(! (catchRevent=recvRespPkt(&deviceFd,respPtr)) )
             {
                    fprintf(stderr, " RESPONSE FROM DEVICE \n");
                    printDevResp(respPtr);
                    sendRespToCMS(respPtr);

                    // post-pone only for response received from the expected command
                    if ((int)cmdPtr->cmdelem.seq == (int)respPtr->cmdelem.seq) sTime=nxtTime+DEVRESP_TO ; 
             }else {

                if (  (catchRevent&POLLHUP) || (catchRevent&POLLRDHUP)  ||  (catchRevent&POLLNVAL)) {
                  fprintf(stderr," checkDevEvent : pollfd got singla %d \n",catchRevent);
                  terminateConsumer(catchRevent);
                  pthread_exit(NULL); /* exit */
                }

                 if( (sTime > 0 ) && (abs(nxtTime-sTime) > DEVRESP_TO) )
                 {
                   respPtr->cmdelem = cmdPtr->cmdelem;
                   respPtr->code = FAILED;   // CMD Failed

                   if(asynch == ASYNCH) respPtr->event = asynch;    /* To keep alive Periodic command incase of failure */
                   else respPtr->event = FINAL;

                   strcpy(&respPtr->message,"DEVICE TIMEOUT");
                   sendRespToCMS(respPtr);
                   break;
                 }
             }

            usleep(300000);
            fprintf(stderr, "Waiting for cmd Response [%ld %ld ] %d %d #Polld %d \n", cmdPtr->cmdelem.seq, respPtr->cmdelem.seq, respPtr->event, abs(nxtTime-sTime), catchRevent);  
        } while(! (((int)cmdPtr->cmdelem.seq == (int)respPtr->cmdelem.seq) && (respPtr->event >  INTERMEDIATE)));

    } else  {
     // Malfunctioning packet Transaction? Terminate - sucide
        terminateConsumer(TIMEOUT);
        pthread_exit(NULL); /* exit */ 
    }
    return;
}

int sendPktToCMS(char *devResp, int cmsPORT) 
{
   int respFd ;

   if( (respFd = initClientConn(cmsPORT)) == ERROR )  {
     fprintf(stderr, "### Error : sendPktToCMS () Could not connect to CMS ..\n");
     return 1;
   } else if(send(respFd,devResp,strlen(devResp),0) < 0 ) {
       fprintf(stderr, "### Error : sendPktToCMS () Respond not send to CMS ..\n"); 
     if(  shutdown(respFd, SHUT_RDWR) == ERROR) {
           fprintf(stderr, " consumeCMS: sendPKtToCMS() Socket fd %d not closed \n",respFd);
     }
     if ( close(respFd) == ERROR) { 
           fprintf(stderr, " consumeCMS: sendPKtToCMS() Socket fd %d not closed \n",respFd);
     }
       return 1;
   }
     if(  shutdown(respFd, SHUT_RDWR) == ERROR) {
           fprintf(stderr, " consumeCMS: sendPKtToCMS() Socket fd %d not closed \n",respFd);
     }
     if ( close(respFd) == ERROR) { 
           fprintf(stderr, " consumeCMS: sendPKtToCMS() Socket fd %d not closed \n",respFd);
     }


   return 0 ;
}

 void localRespToCMS(parseCMSCmd *cptr, int finResp)
 {
      devResponse devResp;

      bzero( (char *)&devResp,devResponseSize);
      memcpy(&devResp.cmdelem, &cptr->cmdelem, BasicFldsSize);
      devResp.event=FINAL;       // Closing command transaction with CMS
      devResp.code=finResp;
      sprintf(devResp.message,"Wrapper Cmd %s Status %d\n",devResp.cmdelem.cmdname, finResp);
      sendRespToCMS(&devResp);
      return ;
 }

 void sendRespToCMS(devResponse *drptr)
 {
   char *xmlbuff; int i, port=resPORT;
   char *response = (char *) malloc(sizeof(char)*MaxBufSize) ;

   if( (char *)  (xmlbuff = (char *) formRespXML(drptr)) != NULL)
   {
      i=strlen(xmlbuff);
      strncpy(response,xmlbuff, i); response[i]='\0';
      fprintf(stderr, "### REPEAT ### CMS TRACK CMD RESPONSE %s \n",response);

      switch(drptr->event)
      {
           case MON : port = monPORT; break;
           case DPLOT : case ALARM :  port = evntPORT; break;
           case ASYNCH : port = resPORT; break;
      }

      if(!sendPktToCMS(response, port) ) {
         fprintf(stderr, " ### COMMAND %s Response send to PORT[%d]\n",drptr->cmdelem.cmdname, port);
      }
   }

   if(response != (char *)NULL) free(response);

   return ;
 }

void consumer(int* connected)
{
  int oflags;
  static int return_from_longjmp_to_setjmp ;
  parseCMSCmd *rtrCmd, devCmd;
  static devResponse  devResp;
  void  ( * devSpecProcessing )(parseCMSCmd *, int *);
  int i, rc; int chkexec=0;

  pthread_setcanceltype(PTHREAD_CANCEL_ASYNCHRONOUS, &rc);
  rc=0;
  fprintf(stderr, " BasicFlds %d \n", sizeof(BasicFlds));
  fprintf(stderr, " DataPkt %d \n", sizeof(DataPkt));
  fprintf(stderr, " RespAlarm %d \n", sizeof(RespAlarm));
  fprintf(stderr, " devResponse %d \n", sizeof(devResponse));
  fprintf(stderr, " parseCMSCmd %d \n", sizeof(parseCMSCmd));
  
  deviceFd = *connected ;

  fprintf(stderr, " ############## consumer() THREAD %d Starting with deviceFd %d ############\n",pthread_self(), deviceFd);

  /* To catch the consumCMS termination so that  DeviceComm can be reset */
           (void) signal(SIGHUP,signal_handler); //(void) signal(SIGINT,SIG_IGN);
           (void) signal(SIGQUIT,signal_handler); (void) signal(SIGILL,signal_handler);
           (void) signal(SIGTERM,signal_handler);
           (void) signal(SIGTRAP,signal_handler); (void) signal(SIGKILL,signal_handler);
           (void) signal(SIGFPE,signal_handler);  (void) signal(SIGBUS,signal_handler);
           (void) signal(SIGSEGV,signal_handler); (void) signal(SIGPIPE,signal_handler);
       //
       //   (void) signal(SIGALRM,signal_handler);
       //  (void) signal(SIGUSR1,signal_handler); (void) signal(SIGUSR2,signal_handler);
          signal(SIGIO, signal_handler); // dummy sample; sigaction(  ) is better 
          fcntl(deviceFd, F_SETOWN, getpid());
          oflags = fcntl(STDIN_FILENO, F_GETFL);
          fcntl(deviceFd, F_SETFL, oflags| SIGHUP | SIGPIPE | SIGTERM);


/*
     if ( allocComBuf() == ERROR ) {
        fprintf(stderr, "allocComBuf() : could not malloc buffer..\n");
        pthread_exit(NULL); 
     }
*/

     switch( getSysId()) {
          case   SENTINAL : devSpecProcessing = devSentinal ;
                            break;
          case   SIGCON   : devSpecProcessing = devSigcon;
                            break;
          case   FRONTEND : devSpecProcessing = devFrontend ; 
                            break;
          case   BACKEND   :devSpecProcessing = devBackend ;
                            break;
          case   DATASERVER : devSpecProcessing = devDataserver ; 
                             break;
          case   SERVO : devSpecProcessing = devServo ; 
                              break;
          default : devSpecProcessing = devSentinal ; break;

     }
         
   xmlQ.store = 0; xmlQ.retrieve = 0; 
   /* setjmp return 0 if success */
   if((return_from_longjmp_to_setjmp = setjmp(set_pt)) == 0 )
   {
      while(1)
      {
          // (1) Here First Response from Device will check for any alarm/event
          checkDevEvent(&devResp);
          // (2) Retreive the command from Queue.
          // (3) then Check If retrieved command is a priority command If priority
          //     then issue priority command.
          // (4) then Check whether any periodic command exceed timer  - execute periodic cmd
          // (5) Before sendCmdPkt to the Device - Process Device packet
          //     as per the sub-system dependency.**** IMP
          // (6) then issue retrevied command 
           //(7) Wait for a single command to get Final Response EVent=12 
           //    Else check TimeOut Counters - give timeout on exceeding timeout counter

          if ((int) (xmlQ.store) > (int) xmlQ.retrieve)
          {
            //  Lock the mutex
            pthread_mutex_lock(&mutex);
               rtrCmd = (parseCMSCmd*) q_retrieve((int)xmlQ.retrieve);
               if( (parseCMSCmd *) rtrCmd != (parseCMSCmd *)NULL )
               {
                       fprintf(stderr," >>>>> Retriving Data from %d Queue - size : %d \n",xmlQ.retrieve, sizeof(*rtrCmd)); 
                       bzero(&devCmd,(size_t)parseCMSCmdSize);
                       memcpy(&devCmd,rtrCmd, (size_t)parseCMSCmdSize);
                       printCmdPkt((parseCMSCmd *) &devCmd);
                        (* devSpecProcessing)(&devCmd, &chkexec );
                        if(!chkexec) devSpecExecute(&devCmd, &devResp,0); // Command not executed
                       xmlQ.retrieve++; /* q_delete function will be here */
               }
            //  Unlock the mutex
            pthread_mutex_unlock(&mutex);
            fprintf(stderr, " ##### xmlQ store [%d] rertrieve [%d] \n", xmlQ.store, xmlQ.retrieve);
          } 

          // Null Command to seek/check Periodic command
          // Caution getting called twice in normal first time periodic cmd
          // SIGPIPE Error catched only when 'CMS' send some command?
          // and not when the periodic command send to the Device Sep 14, 2011
 
          bzero(&devCmd,(size_t)parseCMSCmdSize);
          (* devSpecProcessing)(&devCmd, &chkexec);
          usleep(300000);
      }
   } 
   else
   {
          rc = return_from_longjmp_to_setjmp ;
          fprintf(stderr, " \n#### consumer() : singal_handler() :: Catched  signal %d \n",rc);
           //  Unlock the mutex

          switch(rc)
          {
               case SIGINT  :   /* interrupt (rubout) */
               case SIGQUIT :   /* quit (ASCII FS) */
               case SIGABRT :   /* used by abort, replace SIGIOT in the future */
               case SIGKILL :   /* kill (cannot be caught or ignored) */
          //    case SIGBUS  :   /* bus error */
               case SIGSEGV :   /* segmentation violation */
               case SIGTERM :   /* software termination signal from kill */
            //  case SIGTSTP :   /* user stop requested from tty */
               case SIGPIPE : 
               case SIGHUP  :   /* Hang up signal */

                terminateConsumer(rc);
                fprintf(stderr, " ############ consumer() Exit THREAD [%d] ##############\n",  pthread_self());
                pthread_exit(NULL); /* exit */
               
          }
     }

     fprintf(stderr, " ############ consumer() Exit THREAD [%d] ##############\n",  pthread_self());
      pthread_exit(NULL); /* exit */
 }
