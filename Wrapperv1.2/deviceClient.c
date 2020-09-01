#ifdef __linux__
#include <linux/version.h>
#ifdef LINUX_VERSION_CODE >= KERNEL_VERSION(2,6,17)
#define _GNU_SOURCE
#endif
#endif

#include <stdio.h>
#include <unistd.h>    /* Symbolic Constants */
#include <fcntl.h>
#include <sys/types.h> /* Primitive System Data Types */
#include <errno.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <setjmp.h>
#include <signal.h>
#include <pthread.h>
#include <poll.h>


#include "deviceClient.h"

int reqFd ;
void  formDeviceResp(parseCMSCmd *, devResponse *);
void sendFinResp(devResponse *, int );
void sendIntmResp(devResponse *, int );

void sendFinResp(devResponse *drptr, int fresp)
{
       drptr->event =  FINAL;
       switch(fresp)
       {
          case SUCCESS :
                         drptr->code = fresp; 
                         sprintf(drptr->message,"CMD %ld %s: SUCCESS\n",drptr->cmdelem.seq, drptr->cmdelem.cmdname);
                         break;
          case FAILED :
                         drptr->code = fresp; 
                         sprintf(drptr->message,"CMD %ld %s: Syntax Failed \n",drptr->cmdelem.seq, drptr->cmdelem.cmdname);
                         break;
          case SYNTX   :
                         drptr->code = fresp; 
                         sprintf(drptr->message,"CMD %ld %s: Syntax Err \n",drptr->cmdelem.seq, drptr->cmdelem.cmdname);
                         break;
          case INCOMPLETE :
                         drptr->code = fresp; 
                         sprintf(drptr->message,"CMD %ld %s: Incomplete \n",drptr->cmdelem.seq, drptr->cmdelem.cmdname);
                         break;
          case INVALID :
                         drptr->code = fresp; 
                         sprintf(drptr->message,"CMD %ld %s: Invalid \n",drptr->cmdelem.seq, drptr->cmdelem.cmdname);
                         break;
          case UNKNOWNERR :
                         drptr->code = fresp; 
                         sprintf(drptr->message,"CMD %ld %s: Unknown Err\n",drptr->cmdelem.seq, drptr->cmdelem.cmdname);
                         break;
       }
       sendRespPkt(&reqFd,drptr);
}

// Intermediate Response Can be only Accepted
void sendIntmResp(devResponse *drptr, int iresp)
{
       drptr->event =  INTERMEDIATE;
       drptr->code = iresp; 
       sprintf(drptr->message,"CMD %ld %s VLD : Accepted\n",drptr->cmdelem.seq, drptr->cmdelem.cmdname);
       sendRespPkt(&reqFd,drptr);
}

void  formDeviceResp(parseCMSCmd *cmdptr, devResponse *drptr)
{
     char *deviceCmds [] =  { "init", "reset", "hold", "stop", "trak", "posn","abrt","sttod","domon"};
     typedef enum {            INIT,   RESET,   HOLD,    STOP,   TRAK,   POSN,  ABRT,  STTOD,  DOMON, TOTCMD } devCmdID; 
     int i;
     int cmdID=ERROR ;
     char tstcmd[64];
     char devCmd[CMDSIZE];
     static int sTemp=20, rawcnt=125;
     struct tm *t;  long  devtime;

     // Get the basic Command structure
      drptr->cmdelem = cmdptr->cmdelem;
      drptr->data.numpkt=0; // number of any argument

     for(i=0; i < TOTCMD; i++)  
       if( !strcasecmp(deviceCmds[i],cmdptr->cmdelem.cmdname) )
       { cmdID=i; break; }

      if(cmdID < 0) {
          sendFinResp(drptr,INVALID);
          return ;
      }  

       fprintf(stderr, "CMD  %s ", cmdptr->cmdelem.cmdname);
       for(i=0; i < cmdptr->data.numpkt;i++) {
           fprintf(stderr, " %s %s ", cmdptr->data.prmname[i], cmdptr->data.prmvalue[i]);
       } 
       fprintf(stderr, "\n");

      switch(cmdID)
      {
             case INIT :
                   sendIntmResp(drptr, SUCCESS); sleep(1);
                   sendFinResp(drptr,SUCCESS); 
                  break ;

              case RESET :
                   sendIntmResp(drptr, SUCCESS); sleep(1);
                   sendFinResp(drptr,SUCCESS); 
                  break;
            
             case HOLD :
                   sendIntmResp(drptr, SUCCESS); sleep(1);
                  // serialportcommand('46x')
                  // check resp
                   sendFinResp(drptr,SUCCESS); 
                   break ;

             case STOP :
                   sendIntmResp(drptr, SUCCESS); sleep(1);
            // execute servo command check resp ? SUCCESS/FAIL - send with message
                   sendFinResp(drptr,SUCCESS); 
                  //sendFinResp(drptr,FAILED);
                   break;

             case TRAK :
                   sendIntmResp(drptr, SUCCESS); sleep(1);
                   sendFinResp(drptr,SUCCESS); sleep(1);
                   break;

             case ABRT :
                   sendIntmResp(drptr, SUCCESS); sleep(1);
                   sendFinResp(drptr,SUCCESS);
                    break;

             case STTOD :
                   sendIntmResp(drptr, SUCCESS); sleep(1);
                   sendFinResp(drptr,SUCCESS);
                    break;

             case DOMON :
                   sendIntmResp(drptr, SUCCESS);
                   strcpy(drptr->cmdelem.cmdname,"Monitoring_Data");
                    drptr->data.numpkt=8;

                    devtime = time(NULL);
                    t= localtime(&devtime);
                    strcpy(drptr->data.prmname[0],"time_of_day");
                    sprintf(drptr->data.prmvalue[0],"%.2d:%.2d:%.2d",t->tm_hour,t->tm_min,t->tm_sec);

                    strcpy(drptr->data.prmname[1],"az_cp");
                    strcpy(drptr->data.prmvalue[1],"200:00:00");
                    strcpy(drptr->data.prmname[2],"az_tp");
                    strcpy(drptr->data.prmvalue[2],"210:30:00");
                    strcpy(drptr->data.prmname[3],"az_pp");
                    strcpy(drptr->data.prmvalue[3],"00:00:00");
                    strcpy(drptr->data.prmname[4],"el_cp");
                    strcpy(drptr->data.prmvalue[4],"70:30:00");
                    strcpy(drptr->data.prmname[5],"el_tp");
                    strcpy(drptr->data.prmvalue[5],"70:10:00");
                    strcpy(drptr->data.prmname[6],"el_pp");
                    strcpy(drptr->data.prmvalue[6],"00:00:00");
                    strcpy(drptr->data.prmname[7],"state");
                    strcpy(drptr->data.prmvalue[7],"REMO");

                    drptr->code = SUCCESS; drptr->event = MON;
                    strcpy(drptr->message,"Simulated MON\n");
                    sendRespPkt(&reqFd,drptr);

                    break;

            default :
                   sendFinResp(drptr,INVALID);
      }
}

char * formDeviceCmd(parseCMSCmd *cPtr) {

    char cmdBuf[CMDSIZE]; int i;

    sprintf(cmdBuf,"%s ",cPtr->cmdelem.cmdname);

    for(i=0;i< cPtr->data.numpkt; i++) {
            strcat(cmdBuf, cPtr->data.prmvalue[i] );
            strcat(cmdBuf, " ");
    }

    return &cmdBuf[0];
}

jmp_buf set_pt ;  /* typedef int */
static void signal_handler( int ) ;
/*------------------------------------------------------------*/
     static void signal_handler(sig)
     int sig; {
             extern unsigned int time_interval;
             switch (sig)     {
               case SIGHUP  :   /* Hang up signal */
               case SIGINT  :   /* interrupt (rubout) */
               case SIGSEGV :   /* segmentation violation */
               case SIGPIPE :
                               longjmp(set_pt,sig);
               default:       fprintf(stderr, " signal_handler() : Signal received %d \n",sig);
             }
     }

/*
 static void signal_handler(int sys_signal ) {
//    extern jump_buf set_pt;

     longjmp(set_pt, sys_signal);
  }
*/


void main(int argc, char *argv[])
{
    extern int reqFd ;
    parseCMSCmd *cmdptr;
    devResponse *respptr;
    int rc;
    static int return_from_longjmp_to_setjmp ;
    int catchRevent = 0;

/*
    if (  allocComBuf() == ERROR ) {
        fprintf(stderr, "allocComBuf() : could not malloc buffer..\n");
        exit(1) ;
    }
*/

  fprintf(stderr, " BasicFlds %d \n", sizeof(BasicFlds));
  fprintf(stderr, " DataPkt %d \n", sizeof(DataPkt));
  fprintf(stderr, " RespAlarm %d \n", sizeof(RespAlarm));
  fprintf(stderr, " devResponse %d \n", sizeof(devResponse));
  fprintf(stderr, " parseCMSCmd %d \n", sizeof(parseCMSCmd));

  /* To catch the consumCMS termination so that  DeviceComm can be reset */
           (void) signal(SIGHUP,SIG_IGN); (void) signal(SIGINT,signal_handler);
           (void) signal(SIGQUIT,signal_handler); (void) signal(SIGILL,signal_handler);
           (void) signal(SIGTRAP,signal_handler); (void) signal(SIGIOT,signal_handler);
           (void) signal(SIGFPE,signal_handler);  (void) signal(SIGBUS,signal_handler);
           (void) signal(SIGSEGV,signal_handler); (void) signal(SIGPIPE,signal_handler);
           (void) signal(SIGALRM,signal_handler); (void) signal(SIGTERM,signal_handler);
           (void) signal(SIGUSR1,signal_handler); (void) signal(SIGUSR2,signal_handler);

    if ( (cmdptr = (parseCMSCmd *) calloc( parseCMSCmdSize, 1)) == NULL ) {
       fprintf(stderr, " ### ERROR : deviceClient() : Memory for cmdptr could not allocate \n");
       exit(1);
    }        

    if ( (respptr = (devResponse *) calloc( devResponseSize, 1)) == NULL ) {
       fprintf(stderr, " ### ERROR : deviceClient() : Memory for cmdptr could not allocate \n");
       exit(1);
    }        

  do {

    if( (reqFd = initClientConn(reqPORT)) == ERROR ) {
        fprintf(stderr, "### ERROR : deviceClient() reqFd %d: could not connect to RequestPort %d \n", reqFd, reqPORT);
    }else {
        fprintf(stderr, "deviceClient() : Successfully connected to RequestPort %d \n", reqPORT);
    }
    sleep(1);
  } while (reqFd < 0 );

  /* setjmp return 0 if success */
   if((return_from_longjmp_to_setjmp = setjmp(set_pt)) != 0 )
   {
          rc = return_from_longjmp_to_setjmp ;
          fprintf(stderr, " \n#### singal_handler() :: Catched  signal %d \n",rc);
     /*
           //  Unlock the mutex
          switch(rc)
          {
               case SIGHUP  :   // Hang up signal 
               case SIGINT  :   // interrupt (rubout) 
               case SIGQUIT :   // quit (ASCII FS) 
               case SIGABRT :   // used by abort, replace SIGIOT in the future
               case SIGKILL :   // kill (cannot be caught or ignored)
               case SIGBUS  :   // bus error
               case SIGSEGV :   // segmentation violation
               case SIGTERM :   // software termination signal from kill
               case SIGTSTP :   // user stop requested from tty
               case SIGPIPE :
                    break;
          }
     */

        do {
          if( (reqFd = initClientConn(reqPORT)) == ERROR ) {
              fprintf(stderr, "### ERROR : deviceClient() reqFd %d: could not connect to RequestPort %d \n", reqFd, reqPORT);
          }else {
              fprintf(stderr, "deviceClient() : Successfully connected to RequestPort %d \n", reqPORT);
          }
          sleep(1);
        } while (reqFd < 0 );
 
  }

  while(1) 
  {
           // Read event
           bzero(cmdptr,parseCMSCmdSize); 
           if ( (catchRevent = recvCmdPkt(&reqFd,cmdptr)) == 0 )
           {
              printCmdPkt(cmdptr); 
              formDeviceResp(cmdptr, respptr);
           }
           if (  (catchRevent&POLLHUP) || (catchRevent&POLLRDHUP)  ||  (catchRevent&POLLNVAL)) {
                  fprintf(stderr," checkDevEvent : pollfd got singla %d \n",catchRevent);
                  signal_handler(SIGPIPE);
           }
              usleep(500000);
  }
}
