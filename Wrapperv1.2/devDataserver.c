#include "invokeWrapper.h"
#include "wrapperCom.h"   
#include "consumCMS.h"
#include "xmlResp.h"
#include "devSpec.h"

extern long  cmdTimer[MAXDEVCMD];

 void devDataserver(parseCMSCmd *cptr, int *chkexec) 
 {
         char *periodicCmd[] = {  "domon", "rawmon","stopdomon", "stoprawmon", "startspectplot", "startpulsarplot", "stopspectplot", "stoppulsarplot" };
         typedef enum { DOMON, RAWMON, STOPDOMON, STOPRAWMON, STARTSPECTPLOT, STARTPULSARPLOT,STOPSPECTPLOT,STOPPULSARPLOT,   TOT_DEVCMD} enumPeriodicCmd;
         char *devDataservercmd[] = { "init" };
         typedef enum { INIT } enumSentinalCmd;

         long CurrTime ;
         devResponse  devResp;
         static parseCMSCmd  PeriodicPkt[MAXDEVCMD];
         int i;
          
         CurrTime = time(NULL); *chkexec = 0;

         if(!strcasecmp(cptr->cmdelem.cmdname, periodicCmd[DOMON]))  {
                PeriodicPkt[DOMON] =  (parseCMSCmd) *cptr;
                if( ! atoi( (int)PeriodicPkt[DOMON].data.prmvalue[0]) ) {  // prmvalue[0] is the interval for domon
                    cmdTimer[DOMON] = 0;
                }else { cmdTimer[DOMON] = CurrTime ; }
                *chkexec = 1;
         }else if(!strcasecmp(cptr->cmdelem.cmdname, periodicCmd[RAWMON]))  {
                PeriodicPkt[RAWMON] =  (parseCMSCmd) *cptr;
                if( ! atoi( (int)PeriodicPkt[RAWMON].data.prmvalue[0]) )  {  // prmvalue[0] is the interval for rawmon
                    cmdTimer[RAWMON] = 0;
                }else { cmdTimer[RAWMON] = CurrTime ; }
                *chkexec = 1;
         } else if (!strcasecmp(cptr->cmdelem.cmdname, devDataservercmd[INIT]))  {
             printCmdPkt(cptr);             
             devSpecExecute(cptr,&devResp,0);
             if(devResp.code == SUCCESS) DeviceComm=APPLN; // Not checking success/fail - later check
                *chkexec = 1;
         } else {
                  fprintf(stderr, ".");
         }
          
    if(!cptr->cmdelem.priority) 
    {
  //
  //  Periodic command
  //
       bzero( (char *)&devResp,devResponseSize);
       for(i = 0 ; i < TOT_DEVCMD; i++ ) {

          if( ( (cmdTimer[i] > 0) && (!abs(cmdTimer[i] - CurrTime))) || ((cmdTimer[i] > 0) && (CurrTime > cmdTimer[i])) )
           { 
             fprintf(stderr, "### DevSentinal cmdTimer [%ld] - currentTime [%ld] \n", cmdTimer[i], CurrTime);
             printCmdPkt((parseCMSCmd *)&PeriodicPkt[i]);             
             devSpecExecute(&PeriodicPkt[i],&devResp,ASYNCH);
             bzero( (char *)&devResp,devResponseSize);
             // NOTE : Argument should be zero here
             cmdTimer[i] = CurrTime+ (atoi((int) (PeriodicPkt[i].data.prmvalue[0]))/1000) ; // set next time
             fprintf(stderr,"  Prmvalue %d  CmdTimer %ld \n", atoi(PeriodicPkt[i].data.prmvalue[i]),  cmdTimer[i]);
           }
       }
    } 

    return ;
 }
