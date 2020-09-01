#include "invokeWrapper.h"
#include "wrapperCom.h"   
#include "consumCMS.h"
#include "xmlResp.h"
#include "devSpec.h"

extern long  cmdTimer[MAXDEVCMD];

 void devSigcon(parseCMSCmd *cptr, int *chkexec) 
 {
         char *periodicCmd[] = {  "domon", "rawmon" };
         typedef enum { DOMON, RAWMON, TOT_DEVCMD} enumPeriodicCmd;
         char *devSigconCmd[] = { "init","set lo","set attn","set reflo"};
         typedef enum { INIT,SET_LO,SET_ATTN,SET_REFLO} enumSigconCmd;

         long CurrTime ;
         devResponse  devResp;
         static parseCMSCmd  PeriodicPkt[MAXDEVCMD];
         int i;
          
         CurrTime = time(NULL); *chkexec = 0;

         if(!strcasecmp(cptr->cmdelem.cmdname, periodicCmd[DOMON]))  {
                PeriodicPkt[DOMON] =  (parseCMSCmd) *cptr;
                if( ! atoi( (const char *)PeriodicPkt[DOMON].data.prmvalue[0]) ) {  // prmvalue[0] is the interval for domon
                    cmdTimer[DOMON] = 0;
                }else { cmdTimer[DOMON] = CurrTime ; }
                *chkexec = 1;
         }else if(!strcasecmp(cptr->cmdelem.cmdname, periodicCmd[RAWMON]))  {
                PeriodicPkt[RAWMON] =  (parseCMSCmd) *cptr;
                if( ! atoi( (const char *)PeriodicPkt[RAWMON].data.prmvalue[0]) )  {  // prmvalue[0] is the interval for rawmon
                    cmdTimer[RAWMON] = 0;
                }else { cmdTimer[RAWMON] = CurrTime ; }
                *chkexec = 1;
         } else if (!strcasecmp(cptr->cmdelem.cmdname, devSigconCmd[INIT])) // strcasecmp ---> compare two strings ignoring case
             {
               printCmdPkt(cptr);             
             devSpecExecute(cptr,&devResp,0);
             if(devResp.code == SUCCESS) DeviceComm=APPLN; // Not checking success/fail - later check
                *chkexec = 1;
         } 

           else if (!strcasecmp(cptr->cmdelem.cmdname, devSigconCmd[SET_LO])) // strcasecmp ---> compare two strings ignoring case
             {
               printCmdPkt(cptr);             
             devSpecExecute(cptr,&devResp,0);
             if(devResp.code == SUCCESS) DeviceComm=APPLN; // Not checking success/fail - later check
                *chkexec = 1;
         } 
           else if (!strcasecmp(cptr->cmdelem.cmdname, devSigconCmd[SET_ATTN])) // strcasecmp ---> compare two strings ignoring case
             {
               printCmdPkt(cptr);             
             devSpecExecute(cptr,&devResp,0);
             if(devResp.code == SUCCESS) DeviceComm=APPLN; // Not checking success/fail - later check
                *chkexec = 1;
         } 
          else if (!strcasecmp(cptr->cmdelem.cmdname, devSigconCmd[SET_REFLO])) // strcasecmp ---> compare two strings ignoring case
             {
               printCmdPkt(cptr);             
             devSpecExecute(cptr,&devResp,0);
             if(devResp.code == SUCCESS) DeviceComm=APPLN; // Not checking success/fail - later check
                *chkexec = 1;
         } 
    else {
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
             cmdTimer[i] = CurrTime+ (atoi((const char *) (PeriodicPkt[i].data.prmvalue[0]))/1000) ; // set next time
             fprintf(stderr,"  Prmvalue %d  CmdTimer %ld \n", atoi(PeriodicPkt[i].data.prmvalue[i]),  cmdTimer[i]);
           }
       }
    } 

    return ;
 }
