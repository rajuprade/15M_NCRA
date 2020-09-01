#include <stdio.h>
#include <unistd.h>    /* Symbolic Constants */
#include <fcntl.h>
#include <sys/types.h> /* Primitive System Data Types */
#include <errno.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>
#include <setjmp.h>
#include <signal.h>
#include <pthread.h>


#include "deviceClient.h"


int reqFd ;

void   formDeviceResp(parseCMSCmd *, devResponse *);

void  formDeviceResp(parseCMSCmd *cmdptr, devResponse *drptr)
{
      char tstcmd[64];
      char devCmd[CMDSIZE];
      static int sTemp=20, rawcnt=125;
         
      strcpy(devCmd,formDeviceCmd(cmdptr));
      fprintf(stderr, "### CMD %s \n",devCmd);
      sscanf(devCmd,"%s",tstcmd); // originally here it was &tstcmd ,but it was giving warning so changed it to tstcmd 27.3.12


     // Get the basic Command structure
      drptr->cmdelem = cmdptr->cmdelem;

         // validate command
         // get response
         // Fill Response

      if( !strcasecmp(tstcmd,"init")) {
           printf("tstcmd -%s \n", tstcmd);
           drptr->code = SUCCESS; drptr->event = INTERMEDIATE;
           strcpy(drptr->message,"CMD VLD : Accepted\n");
           sendRespPkt(&reqFd,drptr);
           sleep(1);
           drptr->code = SUCCESS; drptr->event = FINAL;
           strcpy(drptr->message,"CMD SUCCEED \n");
           sendRespPkt(&reqFd,drptr);
      }else 
      if( !strcasecmp(tstcmd,"setcmd")) {
           printf("tstcmd -%s \n", tstcmd);
           drptr->code = SUCCESS; drptr->event = INTERMEDIATE;
           strcpy(drptr->message,"CMD VLD : Accepted\n");
           sendRespPkt(&reqFd,drptr);
           sleep(6);
           drptr->code = FAILED; drptr->event = FINAL;
           strcpy(drptr->message,"CMD FAILED \n");
           sendRespPkt(&reqFd,drptr);
      }else 
      if( !strcasecmp(tstcmd,"domon")) {
           printf("tstcmd -%s \n", tstcmd);
           strcpy(drptr->cmdelem.cmdname,"Monitoring_Data");
           drptr->code = SUCCESS; drptr->event = INTERMEDIATE;
           strcpy(drptr->message,"CMD VLD : Accepted\n");
           sendRespPkt(&reqFd,drptr);

           drptr->data.numpkt=5;
           strcpy(drptr->data.prmname[0],"time");
           sprintf(drptr->data.prmvalue[0],"%s","16:04:00");

           strcpy(drptr->data.prmname[1],"status");
           sprintf(drptr->data.prmvalue[1],"%s","TEST");

           strcpy(drptr->data.prmname[2],"temp");
           sprintf(drptr->data.prmvalue[2],"%d",sTemp+=5);

           strcpy(drptr->data.prmname[3],"chan");
           strcpy(drptr->data.prmvalue[3],"0");

           strcpy(drptr->data.prmname[4],"rawcnt");
           sprintf(drptr->data.prmvalue[4],"%d",rawcnt+=3);

           if(sTemp > 35) {
                drptr->code = FAILED; drptr->event = ALARM;
                strcpy(drptr->message,"TEMPERATURE HIGH \n");
// Alarm structure
                drptr->alarm.id=903;
                drptr->alarm.level=5;
                strcpy(drptr->alarm.description,"ALARM TEMPERATURE HIGH \n");
                sTemp=20; rawcnt=125;
                 
           } else {
                sleep(6);
                drptr->code = SUCCESS; drptr->event = MON;
                strcpy(drptr->message,"Simulated Temperature \n");
           }

           sendRespPkt(&reqFd,drptr);

      }else  { printf( " tstcmd-%s \n", "command not found"); 
           printf("tstcmd -%s \n", tstcmd);
           drptr->code = INVALID; drptr->event = FINAL;
           strcpy(drptr->message,"Invalid CMD");
           sendRespPkt(&reqFd,drptr);
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

 static void signal_handler(int sys_signal ) {
//    extern jump_buf set_pt;

     longjmp(set_pt, sys_signal);
  }


int main(int argc, char *argv[])
{
    extern int reqFd ;
    parseCMSCmd *cmdptr;
    devResponse *respptr;
    int len =-1; 
    int rc;
    static int return_from_longjmp_to_setjmp ;


 
    if (  allocComBuf() == ERROR ) {
        fprintf(stderr, "allocComBuf() : could not malloc buffer..\n");
        exit(1) ;
    }

  /* To catch the consumCMS termination so that  DeviceComm can be reset */
           (void) signal(SIGHUP,SIG_IGN); (void) signal(SIGINT,SIG_IGN);
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

  /* setjmp return 0 if success */
   if((return_from_longjmp_to_setjmp = setjmp(set_pt)) == 0 )
   {

  do {

    if( (reqFd = initClientConn(reqPORT)) == ERROR ) {
        fprintf(stderr, "### ERROR : deviceClient() reqFd %d: could not connect to RequestPort %d \n", reqFd, reqPORT);
    }else {
        fprintf(stderr, "deviceClient() : Successfully connected to RequestPort %d \n", reqPORT);
    }
    sleep(1);
  } while (reqFd < 0 );
 

      while(1)
      {
           len =0;
           bzero(cmdptr,parseCMSCmdSize); 
           
           if(!(len = recvCmdPkt(&reqFd,cmdptr))  ) 
           {
              fprintf(stderr, "---------------------------- \n");
              printCmdPkt(cmdptr); 
              formDeviceResp(cmdptr, respptr);

           }

           usleep(500000);

      } 
   }
   else 
   {
          rc = return_from_longjmp_to_setjmp ;
          fprintf(stderr, " \n#### singal_handler() :: Catched  signal %d \n",rc);
           //  Unlock the mutex
          switch(rc)
          {
               case SIGHUP  :   /* Hang up signal */
               case SIGINT  :   /* interrupt (rubout) */
               case SIGQUIT :   /* quit (ASCII FS) */
               case SIGABRT :   /* used by abort, replace SIGIOT in the future */
               case SIGKILL :   /* kill (cannot be caught or ignored) */
               case SIGBUS  :   /* bus error */
               case SIGSEGV :   /* segmentation violation */
               case SIGTERM :   /* software termination signal from kill */
               case SIGTSTP :   /* user stop requested from tty */
               case SIGPIPE :
   
                    break;
           }
    }

        return 0;
}
