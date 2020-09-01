/********* 
SerCMS.C ----> Log file code included by Raj on 18/07/2011.
New LIB xml code to parse the xml file is also included .
Modified the servCMS.c so that it takes the LOGPATH and COMMANDPATH from respective subsystem conf file....dt : 26/07/11
Now the Logile portion is separate out in logfile.h and logfile.c respectively....date 26/07/11
InvokeWrapper takes the LOGPATH COMMANDPATH and RESPONSEPATH from .conf file of particular subsystems...
XMLRESP.h and XMLRESP.c added which form the dynamic response ACK by Wrapper from parseCMSCmd structure. Date : 28.7.11
***********/

#include "invokeWrapper.h"
#include "wrapperCom.h"
#include "handleQue.h"
#include "xmlParse.h"
#include "xmlResp.h"
#include "servCMS.h"
#include "logfile.h"
#include <string.h>   //  // used for LOG generation
#include <time.h>     // used for LOG generation

//#ifdef LIBXML_READER_ENABLED


extern pthread_mutex_t mutex;// mutex
extern pthread_mutex_t fmutex;// mutex for file
extern pthread_mutex_t Rmutex;// mutex for file
extern pid_t  current_pid;

// The Thread Task for All Clients

   parseCMSCmd parseCmd; 
   extern int  DeviceComm;



void  formWrapperAck(devResponse *, int );
void  deviceStatResponse( );

void  formWrapperAck(devResponse *drptr, int flag)
{
     char WrapperAck[256];  
                           
     switch(flag) 
     {
        case Success :       sprintf(WrapperAck," Wrapper %s: XML CMD Received Successful", subSysID); break;
        case dTimeout :      sprintf(WrapperAck," Wrapper %s: Not Communicating" ,subSysID); break;
        case Reset    :      sprintf(WrapperAck," Wrapper %s: Reset" ,subSysID); break;
        case xmlSyntxErr :   sprintf(WrapperAck,"Wrapper %s: XML Syntax Error", subSysID); break;
        case xmlIncomplete : sprintf(WrapperAck,"Wrapper %s: XML Invalid Cmd", subSysID); break;
        case xmlInvalid :    sprintf(WrapperAck,"Wrapper %s: Subsystem %s Invalid" ,subSysID,parseCmd.cmdelem.subsysid  ); break;
        default  :sprintf(WrapperAck,"Wrapper %s: Unknown Err", subSysID); break;
     }

        drptr->code = flag;
        drptr->event = WRAPPER ;
        strcpy(drptr->cmdelem.subsysid,subSysID);
        strcpy(drptr->message,WrapperAck);
      
     return ;
}


// Generic System PAcket
void deviceStatResponse() 
{
   char *response, *xmlbuff; int i;
   devResponse devStat;
   struct tm *t;  long  devtime;
   int flag;
// Form Response

   response=(char *)malloc(sizeof(char)*MaxBufSize);


/*
   strcpy(respTO.data.prmname[2],"temp");
   sprintf(respTO.data.prmvalue[2],"00.0");
 
   strcpy(respTO.data.prmname[3],"chan");
   strcpy(respTO.data.prmvalue[3],"0");
 
   strcpy(respTO.data.prmname[4],"rawcnt");
   sprintf(respTO.data.prmvalue[4],"000");
*/

  while (1)
  {
 
  // 10 sec interval too much slow? Sep 20, 2011
   sleep(1);
   if ( ((devtime = time(NULL))%10) || ( DeviceComm > RESET ) ) continue;

   switch (DeviceComm) 
   {
      case TIMEOUT : 
             flag=dTimeout;
             strcpy(devStat.data.prmname[1],"state");
             sprintf(devStat.data.prmvalue[1],"%s","TIMEOUT");
             devStat.event = ALARM; // Timeout is alarm
             break;
 
      case RESET   :
             flag=Reset;
             strcpy(devStat.data.prmname[1],"state");
             sprintf(devStat.data.prmvalue[1],"%s","RESET");
             devStat.event = MON; // Reset is event only
             break;
      default : break;
   }

   devStat.code = FAILED;
   devStat.cmdelem.seq = 0l;
   devStat.cmdelem.priority = 0l;
   devStat.cmdelem.version = 1.0;  // Version will check later Sep 20, 2011
   strcpy(devStat.cmdelem.id,"0000"); 
   strcpy(devStat.cmdelem.cmdname,"domon"); 
   strcpy(devStat.cmdelem.subsysid,subSysID); 
   strcpy(devStat.cmdelem.timestamp,"2012-01-01T00:00:00+05:30");
   devStat.data.numpkt=2;
   
   //
   // Alarm for device Timeout
   //

   devStat.alarm.id = 0;
   strcpy(devStat.alarm.alarmname,"device_timeout");
   devStat.alarm.level = WARNING3;
   sprintf(devStat.alarm.description,"Device %s : Not communicating",subSysID);
 //  formWrapperAck(&devStat,flag); Event getting Assigned hence not calling generic function
 //  temporarily

         t= localtime(&devtime);
         strcpy(devStat.data.prmname[0],"time");

         sprintf(devStat.data.prmvalue[0],"%.2d:%.2d:%.2d",t->tm_hour,t->tm_min,t->tm_sec);
         sprintf(devStat.cmdelem.timestamp,"%.4d-%.2d-%.2dT%.2d:%.2d:%.2d+05:30", (1900+t->tm_year), (1+t->tm_mon),t->tm_mday, t->tm_hour,t->tm_min,t->tm_sec);
         
         fprintf(stderr,"### INFO Cmdname %s %s Event %d Code %d\n", devStat.cmdelem.cmdname,devStat.cmdelem.timestamp, devStat.event, devStat.code);

     
        if( (char *)  (xmlbuff = (char *) formRespXML(&devStat)) != NULL) // Either consumer is not up/reset
          {
               i=strlen(xmlbuff);
               strncpy(response,xmlbuff, i); response[i]='\0';
               fprintf(stderr," ### WRAPPER XML RESPONSE  %s\n", (char *)response);
                if(!sendPktToCMS(response, monPORT) ) {
                   fprintf(stderr, "### devSpecExecute() : Mon Response send\n");
                }
          }
   }
  
  free((char*)response);
}

void service(int *connected)
{
  #define SRVCMSTIMEOUT 30
  ssize_t bytes_recieved,length;
  ssize_t bytes= -1;
  int srvflag,i;
  long sTime=0, nxtTime=0;
   struct pollfd cmsServPoll;
   devResponse respAck; 
  int srvFd;

   char *recvbuffer,*cxmlbuf ;
   char *response,*xmlbuff; 
    pthread_t srvId=pthread_self(); // It gives the thread ID

  // can reclaim  the thread resources again on call
   pthread_detach(srvId);
   fprintf(stderr," ############# Starting Service() THREAD [%d] with Fd %d  ############# \n", srvId, (int)*connected);

// Receive Command
   recvbuffer=(char *)malloc(sizeof(char)*MaxBufSize);
   cxmlbuf=(char *)malloc(sizeof(char)*MaxBufSize);
// Form Response
   response=(char *)malloc(sizeof(char)*MaxBufSize);
  

   bzero(recvbuffer,MaxBufSize);
   bzero(cxmlbuf,MaxBufSize);
   bzero(response,MaxBufSize);

   fprintf(stderr,"\n\n Current Task no %d\n\n",*connected);
   cmsServPoll.fd = *connected;
   cmsServPoll.events = POLLIN|POLLERR;
   srvFd = (int) *connected ;
   length=0; srvflag = 0;

    nxtTime = time(NULL);   

    while(srvflag == 0 )
    {
             sTime = time(NULL);   
             bytes_recieved=0; bzero(recvbuffer,MaxBufSize);
              
/*
              if(  poll(&cmsServPoll, (nfds_t)1,10) != ERROR ) {
                  switch(cmsServPoll.revents) {
                       case POLLIN : fprintf(stderr, " POLLIN Data ready\n"); break;
                       case POLLERR : fprintf(stderr, " POLLERR Data ready\n"); break;
                   }
              }

           if(cmsServPoll.revents & POLLIN) { */
                      // DO NOT REMOVE MSG_DONTWAIT FLAG it is mandatory and weird behaviour seen
                      // during the first cms command i.e. init 27 sep 2011
                bytes_recieved = recv(srvFd,recvbuffer,(MaxBufSize-1),MSG_DONTWAIT); //save the data sent by client

           //   bytes_recieved =  recv(srvFd,recvbuffer,(MaxBufSize-1)); //save the data sent by client

             fprintf(stderr, " ----------- bytes_received %d \n",bytes_recieved);
                      if(bytes_recieved > 0) {
                                recvbuffer[bytes_recieved] = '\0';
                                if(!length) {
                                     strncpy(cxmlbuf,recvbuffer,(strlen(recvbuffer)) );
                                } else  {
                                     strncat (cxmlbuf,recvbuffer,(strlen(recvbuffer))); 
                                }
                                length+=strlen(recvbuffer);
                                fprintf(stderr,"### servCMS : [%d] recv %s ---- [%d] cxmlbuf %s\n",strlen(recvbuffer), recvbuffer, length,cxmlbuf);
                                
                                // It will read till it gets <REQ_END>                 
                                if( cxmlbuf[length-1]=='>' && cxmlbuf[length-2]=='D'&& cxmlbuf[length-3]=='N'&& cxmlbuf[length-4]=='E' && 
                                    cxmlbuf[length-5]=='_' && cxmlbuf[length-6]=='Q'&& cxmlbuf[length-7]=='E'&& cxmlbuf[length-8]=='R' && cxmlbuf[length-9]=='<')  
                                 {
                      
                                          fprintf(stderr,"\nCOMPLETE COMMAND IS RECEIVED BY WRAPPER.. \n\n");
                                          srvflag=Success;
                                          cxmlbuf[length-9] = '\0';
                                 }
                                 nxtTime=sTime+SRVCMSTIMEOUT ;
                     } else { 
                      if( (nxtTime > 0 ) && abs(nxtTime-sTime) > SRVCMSTIMEOUT) {
                           fprintf(stderr, "service()  : Not Received <REQ_END> Tag..\n");
                           srvflag=xmlIncomplete;
                       } else {  usleep(300000); }
                    }
        //  } 
     }
/*
     Openfile(cxmlbuf);   // Open the Log and command file
     CloseFile();          // close Log and command file
*/


   // xml Incomplete
  if( srvflag == Success) {
       // XML Syntax
     fprintf(stderr,"\nParsing XML data.. %s %d \n\n", cxmlbuf, srvflag);
     if( parseDoc(cxmlbuf) == ERROR )  { /* Parsing the XML Command */
               srvflag = xmlSyntxErr;       /* Suppose Basic Command Structure is corrupted ? What info to CMS should send */
     } else if ( strcmp( (char *) parseCmd.cmdelem.subsysid,subSysID) ) {
             srvflag=xmlInvalid ;
             fprintf(stderr, "### ERROR subSysID %s %s \n",parseCmd.cmdelem.subsysid ,subSysID); 
     } else if (!DeviceComm) {
             srvflag=dTimeout;
             fprintf(stderr, "### ERROR : subSysID %s %d Not Communicating\n",parseCmd.cmdelem.subsysid, DeviceComm); 
     }
  }

    respAck.cmdelem = parseCmd.cmdelem;
    formWrapperAck(&respAck,srvflag);

   if( (char *)  (xmlbuff = (char *) formRespXML(&respAck)) != NULL)
   {
       i=strlen(xmlbuff);
       strncpy(response,xmlbuff,i); response[i]='\0';
       fprintf(stderr," ### WRAPPER XML RESPONSE  %s\n", (char *)response);
       bytes = -1;
        if( (bytes = send(srvFd,response,i,0) ) < 0 ) {
             fprintf(stderr, "### ERROR : servCMS : Response not send to the CMS \n");
        } 
  // write(srvFd,response,strlen(response));
  //     send(srvFd,response,strlen(response), 0); //        send the RESPONSE back
   }

   if(srvflag == Success) {
     fprintf(stderr,"\n\n PUTTING DATA IN QUEUE... ");
  //  Lock the mutex
      pthread_mutex_lock(&mutex);
      q_store(parseCmd); 
   //   Unlock the mutex
      pthread_mutex_unlock(&mutex);
   }
         
    if(recvbuffer != (char *)NULL) free((char*)recvbuffer);
    if(cxmlbuf != (char *)NULL)    free((char*)cxmlbuf);
    if(response != (char *)NULL)   free((char*)response);
    

     if(  shutdown( (int)srvFd, SHUT_RDWR) == ERROR) {
           fprintf(stderr, " ServCMS: service() Socket shutdown() fd %d not closed \n",srvFd);
     }
     if ( close( (int)srvFd) == ERROR) {
           fprintf(stderr, " ServCMS: service() Socket fd close() %d not closed \n",srvFd);
     }
    fprintf(stderr, "############ Exiting Service() THREAD [%d] ############ \n", srvId);
    pthread_exit(NULL); /* exit */
}
