#include "invokeWrapper.h"
#include "wrapperCom.h"   
#include "consumCMS.h"
#include "xmlResp.h"
#include "devSpec.h"
#include "devServo.h"
#include "constant.h"


 extern long  cmdTimer[MAXDEVCMD];
 TrkPara cmsTrk;
 char srvinfo[MSGLEN];
 long totTrktime;

 void createSrvCmd(parseCMSCmd *,int );
 void closePrvTrk(parseCMSCmd *,int ); // close previous track command transaction if any for the CMS
 void issueTrk(time_t *, parseCMSCmd *);
 void newTrk( parseCMSCmd *,int, int );
  
 /*
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
*/

 void createSrvCmd(parseCMSCmd *srvCmd, int SrvId)
 {
    typedef enum { TRACK=68, HOLD=70, BRAKE=72,  ABORT=80 } srvCmdEnum ;
    struct tm ct ; time_t t = time(NULL);

     localtime_r(&t,&ct);
     sprintf(srvCmd->cmdelem.timestamp,"%.4d-%.2d-%.2dT%.2d:%.2d%.2d+05:30",ct.tm_year+1900,ct.tm_mon,ct.tm_mday,
                                                                           ct.tm_hour,ct.tm_min,ct.tm_sec);
      sprintf(srvCmd->cmdelem.subsysid,"%s","servo");
      srvCmd->cmdelem.seq = 0;
      srvCmd->cmdelem.priority = 1;

     switch(SrvId)
     {
         case TRACK :
          
             sprintf(srvCmd->cmdelem.cmdname,"%s","track");
             sprintf(srvCmd->cmdelem.id,"%d", TRACK);
             srvCmd->data.numpkt = 4;   // AXIS, TARGET_TIME, ANG1, ANG2
             sprintf(srvCmd->data.prmname[0],"%s","ax");
             sprintf(srvCmd->data.prmname[1],"%s","time");
             sprintf(srvCmd->data.prmname[2], "ang1");  // AZ
             sprintf(srvCmd->data.prmname[3], "ang2"); // EL
             sprintf(srvCmd->data.prmvalue[0],"%s","B");  // B for both axis compulsary
             break;

        case HOLD :
             sprintf(srvCmd->cmdelem.cmdname,"%s","hold");
             sprintf(srvCmd->cmdelem.id,"%d",HOLD);
             srvCmd->data.numpkt = 1;   // AXIS, TARGET_TIME, ANG1, ANG2
             sprintf(srvCmd->data.prmname[0],"%s","ax");
             sprintf(srvCmd->data.prmvalue[0],"%s","B");  // B for both axis compulsary
             break;
        case BRAKE :
             sprintf(srvCmd->cmdelem.cmdname,"%s","stop");
             sprintf(srvCmd->cmdelem.id,"%d",BRAKE);
             srvCmd->data.numpkt = 1;   // AXIS, TARGET_TIME, ANG1, ANG2
             sprintf(srvCmd->data.prmname[0],"%s","ax");
             sprintf(srvCmd->data.prmvalue[0],"%s","B");  // B for both axis compulsary
             break;

        case ABORT :
             sprintf(srvCmd->cmdelem.cmdname,"%s","abort");
             sprintf(srvCmd->cmdelem.id,"%d",ABORT);
             srvCmd->data.numpkt = 0;  
             break;
     }
 }
 
 void closePrvTrk(parseCMSCmd *trk15m, int TRKTM)
  {
      if(cmdTimer[TRKTM] > 0 ) // Closing the track period command by event 12
       localRespToCMS(trk15m, SUCCESS); 

       return;
  }

void newTrk(parseCMSCmd *trk15m,int TRKTM, int trkid)
{
     devResponse  devResp;
     parseCMSCmd  srvCmd;
     time_t CurrTime  = time(NULL);

         // If already track=68 command send to servo -
         // Issue Abort command to servo to discard servo track queue.
     if( (cmdTimer[TRKTM] > 0) && ( (CurrTime - (cmdTimer[TRKTM]-TRK_INTERVAL)) < 0) )
     {
         fprintf(stderr,"### NEWTRK(): Aborting Servo Track Queue \n");
         createSrvCmd(&srvCmd,80); // ABORT=80
         devSpecExecute(&srvCmd, &devResp, 0);
         sendRespToCMS(&devResp);
     } 

    // Hold both axis before track command fired.
     createSrvCmd(&srvCmd,70); // HOLD=70
     devSpecExecute(&srvCmd, &devResp, 0);
     sendRespToCMS(&devResp);

     cmsTrk.cmdid = trkid; setTrkPara(trk15m,&cmsTrk);
     cmdTimer[TRKTM]=0 ; issueTrk(&cmdTimer[TRKTM], trk15m);
     totTrktime=cmdTimer[TRKTM];
     cmdTimer[TRKTM]+=TRK_INTERVAL; issueTrk(&cmdTimer[TRKTM], trk15m);

}

 void issueTrk(time_t *trkTime, parseCMSCmd *trk15m)
 {
   devResponse  devResp;
   static parseCMSCmd  srvCmd;

   bzero( (char *)&devResp,devResponseSize);

   if(! (*trkTime))    // First TrackCmd 29th or 59th sec
   {
       *trkTime = time(NULL);
       localtime_r(trkTime, &cmsTrk.lcltm);
       if (cmsTrk.lcltm.tm_sec < 29) {*trkTime+= (29-cmsTrk.lcltm.tm_sec); }
       else { *trkTime += (59-cmsTrk.lcltm.tm_sec); }
       createSrvCmd(&srvCmd,68); // TRACK=68;
   }

   localtime_r(trkTime, &cmsTrk.lcltm); // reseting Trk Time after 29/59 correction
   formServoCmd(&srvCmd);

   // Servo track event already send, now responding again to
   // actual CMS command issued.
   
   printCmdPkt(&srvCmd);
   devSpecExecute(&srvCmd, &devResp, ASYNCH); // device will send servo command response with final response 12 from pc104
   devResp.cmdelem = trk15m->cmdelem;
   devResp.event=ASYNCH; // As trackobject command is periodic command
   sprintf(devResp.message,"TRK %s %s %s %s # %s",srvCmd.data.prmvalue[1], srvCmd.data.prmvalue[0],srvCmd.data.prmvalue[2],srvCmd.data.prmvalue[3],srvinfo);
   devResp.message[strlen(devResp.message)-1]='\0';
   
   sendRespToCMS(&devResp);

   return;

 }
 

 void devServo(parseCMSCmd *cptr, int *chkexec) 
 {
       // Do not make Periodic or enumServCmd variables global as it may clash with other device command
         char *periodicCmd[] = {  "track15m", "domon", "rawmon" };  // Note : First priority to track command
         typedef enum { TRACK15M , DOMON, RAWMON, TOT_DEVCMD} enumPeriodicCmd;
         char *devServoCmd[] = { "init", "trackobject", "ldsrcpara", "trackoffazel", "trackoffradec", "scan", "stoptrack", "stop",
                                 "goout", "goin", "setantpara", "ldantcorrect"};
                              // 1           2           3             4           5 
         typedef enum { INIT, TRACKOBJECT, LDSRCPARA, TRACKOFFAZEL, TRACKOFFRADEC, SCAN, STOPTRACK, STOP,
                        GOOUT, GOIN, SETANTPARA, LDANTCORR,  TOT_SRVCMD } enumServcmd;

         /* Do Not make above variables and enum array global as they may get clash with other device
            programs - May 26, 2012 JPK 
          */
         time_t CurrTime ;
         devResponse  devResp;
         static parseCMSCmd  PeriodicPkt[MAXDEVCMD];
         parseCMSCmd  srvCmd; // To enable Stop
         float scanradec, scanazel;
         extern long totTrktime;
         int i;
          
        *chkexec = 0;
         bzero( (char *)&devResp,devResponseSize);
         CurrTime = time(NULL); 

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
         } else if (!strcasecmp(cptr->cmdelem.cmdname, devServoCmd[INIT]))  {
             printCmdPkt(cptr);             
             initAntPara(&cmsTrk.antp); initTrkPara(&cmsTrk);
             devSpecExecute(cptr,&devResp,0);
             fprintf(stderr, " ############ INFO Response from INIT %d \n",devResp.code);
             if(devResp.code == SUCCESS) { DeviceComm=APPLN; } // Not checking success/fail - later check
                *chkexec = 1;
          // TRACKOBJECT, RAWTRACK, TRACKOFFAZEL, TRACKOFFRADEC, SCAN is Nothing but original servo track command
          // ?? Whether reseting track structure or keeping the values for next calc need to be decide ??
         } else if ( !strcasecmp(cptr->cmdelem.cmdname, devServoCmd[TRACKOBJECT])) {
                     closePrvTrk(&PeriodicPkt[TRACK15M],TRACK15M); memcpy(&PeriodicPkt[TRACK15M], cptr, parseCMSCmdSize);
                     sprintf(srvinfo,"TRACK");
                     newTrk(&PeriodicPkt[TRACK15M],TRACK15M, TRACKOBJECT); *chkexec = 1;
         } else if ( !strcasecmp(cptr->cmdelem.cmdname, devServoCmd[TRACKOFFAZEL])) {
                     closePrvTrk(&PeriodicPkt[TRACK15M],TRACK15M);  memcpy(&PeriodicPkt[TRACK15M], cptr, parseCMSCmdSize);
                     sprintf(srvinfo,"TRKOFFAZEL");
                     newTrk(&PeriodicPkt[TRACK15M],TRACK15M, TRACKOFFAZEL); *chkexec = 1;
         } else if ( !strcasecmp(cptr->cmdelem.cmdname, devServoCmd[TRACKOFFRADEC]) ) {
                     closePrvTrk(&PeriodicPkt[TRACK15M],TRACK15M);  memcpy(&PeriodicPkt[TRACK15M], cptr, parseCMSCmdSize);
                     sprintf(srvinfo,"TRKOFFRADEC");
                     newTrk(&PeriodicPkt[TRACK15M],TRACK15M, TRACKOFFRADEC); *chkexec = 1;

         } else if ( !strcasecmp(cptr->cmdelem.cmdname, devServoCmd[SCAN]) ) {
                     closePrvTrk(&PeriodicPkt[TRACK15M],TRACK15M);  memcpy(&PeriodicPkt[TRACK15M], cptr, parseCMSCmdSize);
                     newTrk(&PeriodicPkt[TRACK15M],TRACK15M, SCAN); *chkexec = 1;

                     if((float) cmsTrk.scanp.daz != 0.0 || (float) cmsTrk.scanp.del != 0.0 )  {

                              if( (float) cmsTrk.scanp.daz != 0.0 && cmsTrk.latestTrk.el15m < M_PI/2. ) {
                                   cmsTrk.scanp.daz = (float)cmsTrk.scanp.daz/(float)cos(cmsTrk.latestTrk.el15m); // el15m in radian
                                    fprintf(stderr, " AZ Scan rate %lf up by cos El %lf [EL %lf] \n",  cmsTrk.scanp.daz, 1.0/(float)cos(cmsTrk.latestTrk.el15m), cmsTrk.latestTrk.el15m * r2d);
                              }

                              cmsTrk.daz = cmsTrk.scanp.daz = cmsTrk.scanp.daz * 4.0 ; // Multiplified by 4 for 1deg/1m- Radian conversion unit- 1/cos(elev) will be required.
                              cmsTrk.del = cmsTrk.scanp.del = cmsTrk.scanp.del * 4.0 ;

                              if(cmsTrk.scanp.del < 0) cmsTrk.scanp.del = cmsTrk.scanp.del * (-1.0);
                              if(cmsTrk.scanp.daz < 0) cmsTrk.scanp.daz = cmsTrk.scanp.daz * (-1.0);
                              
                        // Length / ( 2 * sqrt ( elrate^2 + azrate^2)  JNC SEP 20, 2012
                              if( cmsTrk.scanp.daz < cmsTrk.scanp.del && cmsTrk.scanp.daz != 0.0 )
                                 scanazel = cmsTrk.scanp.daz;  // Az leser
                              else if (cmsTrk.scanp.del != 0.0) scanazel = cmsTrk.scanp.del; // El lesser
                              else  scanazel = cmsTrk.scanp.daz; // AZ more
                              

                      }else { scanazel = 0.0 ; }
                               // In radian
                               
                       if( scanazel != 0.0 ) {
                          // Do I need to account for delay of the newtrk i.e. curr+2*TRK_INTERVAL--- TRK_INTERVAL*2 implimented.
                          cmsTrk.dazel_reftime = (double) ( ( (float)cmsTrk.lcltm.tm_hour +  ((float)cmsTrk.lcltm.tm_min/60.0) +((float)cmsTrk.lcltm.tm_sec/3600.0) + ((TRK_INTERVAL*2.0)/3600.0)  )/r2h) + (double) ( ( (cmsTrk.scanp.length*0.5)/r2d)/ scanazel) ; // Scan Length in degrees to radian (3.14 * 2/24)
                              sprintf(srvinfo, "SCAN: Peak %lf [Start %lf] Hrs Scanazel [%lf] %lf %lf deg/min\n",cmsTrk.dazel_reftime  * r2h, (double) ((float)cmsTrk.lcltm.tm_hour + ((float)cmsTrk.lcltm.tm_min/60.0) +((float)cmsTrk.lcltm.tm_sec/3600.0) + ((TRK_INTERVAL*2.0)/3600.0) ) , scanazel, cmsTrk.scanp.del/4.0, cmsTrk.scanp.daz/4.0);
                              fprintf(stderr, "# INFO: Peak-time %lf [start-time %lf] scanazel [%lf] %lf %lf \n",cmsTrk.dazel_reftime  * r2h, (double) ((float)cmsTrk.lcltm.tm_hour + ((float)cmsTrk.lcltm.tm_min/60.0) +((float)cmsTrk.lcltm.tm_sec/3600.0) + ((TRK_INTERVAL*2.0)/3600.0) ) , scanazel, cmsTrk.scanp.del/4.0, cmsTrk.scanp.daz/4.0);
                       }else { cmsTrk.dazel_reftime = (double) ((float)cmsTrk.lcltm.tm_hour + ((float)cmsTrk.lcltm.tm_min/60.0) +((float)cmsTrk.lcltm.tm_sec/3600.0))/r2h; }
                       
                      /* dra, ddec in degrees  */
                      if( (float) cmsTrk.scanp.dra != 0.0 || (float) cmsTrk.scanp.ddec != 0.0 )   {
                      
                              cmsTrk.dra  = cmsTrk.scanp.dra =  cmsTrk.scanp.dra * 1.0/r2h;
                              cmsTrk.ddec = cmsTrk.scanp.ddec =  cmsTrk.scanp.ddec * 4.0 ;
                              
                              if(cmsTrk.scanp.dra < 0) cmsTrk.scanp.dra = cmsTrk.scanp.dra * (-1);
                              if(cmsTrk.scanp.ddec < 0) cmsTrk.scanp.ddec = cmsTrk.scanp.ddec * (-1);
                              
                              if( cmsTrk.scanp.dra < cmsTrk.scanp.ddec &&  cmsTrk.scanp.dra != 0.0 ) scanradec = cmsTrk.scanp.dra;
                              else if ( cmsTrk.scanp.ddec != 0.0 )  scanradec = cmsTrk.scanp.ddec; 
                              else scanradec = cmsTrk.scanp.dra ;
                      } else {scanradec = 0.0 ; }

                      if (scanradec != 0.0 ) {
                              cmsTrk.dradec_reftime = (double)  ( ( (float)cmsTrk.lcltm.tm_hour +  ((float)cmsTrk.lcltm.tm_min/60.0) +((float)cmsTrk.lcltm.tm_sec/3600.0) + ((TRK_INTERVAL*2.0)/3600.0) )/r2h) + (double) ( ( (cmsTrk.scanp.length*0.5)/r2d)/ scanradec) ;
                              sprintf(srvinfo, "SCAN: Peak %lf [Start %lf] Hrs Scanradec [%lf] %lf %lf \n",cmsTrk.dradec_reftime  * r2h, (double) ((float)cmsTrk.lcltm.tm_hour+((float)cmsTrk.lcltm.tm_min/60.0)+((float)cmsTrk.lcltm.tm_sec/3600.0) + ((TRK_INTERVAL*2.0)/3600.0) ) , scanradec, cmsTrk.scanp.ddec/4.0, cmsTrk.scanp.dra*r2h);
                              fprintf(stderr, "# INFO : Peak-time %lf [%lf] scanradec [%lf] %lf %lf \n",cmsTrk.dradec_reftime  * r2h, (double) ((float)cmsTrk.lcltm.tm_hour+((float)cmsTrk.lcltm.tm_min/60.0)+((float)cmsTrk.lcltm.tm_sec/3600.0) + ((TRK_INTERVAL*2.0)/3600.0) ) , scanradec, cmsTrk.scanp.ddec/4.0, cmsTrk.scanp.dra*r2h);

                      } else { cmsTrk.dradec_reftime = (double) ((float)cmsTrk.lcltm.tm_hour + ((float)cmsTrk.lcltm.tm_min/60.0) +((float)cmsTrk.lcltm.tm_sec/3600.0))/r2h;  }
                     
         } else if  (  !strcasecmp(cptr->cmdelem.cmdname, devServoCmd[STOPTRACK]) ) {
                      closePrvTrk(&PeriodicPkt[TRACK15M],TRACK15M); cmdTimer[TRACK15M]=0; initTrkPara(&cmsTrk);
                      createSrvCmd(&srvCmd,72); // BRAKE=72
                      devSpecExecute(&srvCmd, &devResp, 0);
                      localRespToCMS(cptr,SUCCESS); *chkexec = 1;
         } else if ( !strcasecmp(cptr->cmdelem.cmdname, devServoCmd[LDSRCPARA])  )  {
                      setTrkPara(cptr,&cmsTrk);  //  newTrk(&PeriodicPkt[TRACK15M],TRACK15M, LDSRCPARA);
                      localRespToCMS(cptr,SUCCESS); *chkexec = 1;
         } else if ( !strcasecmp(cptr->cmdelem.cmdname, devServoCmd[GOOUT]) )  {
                      cmsTrk.outtrk = 1 ;
                      localRespToCMS(cptr,SUCCESS); *chkexec = 1;
         } else if ( !strcasecmp(cptr->cmdelem.cmdname, devServoCmd[GOIN]) ) {
                      cmsTrk.outtrk = 0 ;
                      localRespToCMS(cptr,SUCCESS); *chkexec = 1;
         } else if ( !strcasecmp(cptr->cmdelem.cmdname, devServoCmd[SETANTPARA]) ) {
                      setAntPara(cptr,&cmsTrk.antp);
                      localRespToCMS(cptr,SUCCESS); *chkexec = 1;
         } else if ( !strcasecmp(cptr->cmdelem.cmdname, devServoCmd[LDANTCORR]) ) {
                      setAntPara(cptr,&cmsTrk.antp);
                      localRespToCMS(cptr,SUCCESS); *chkexec = 1;
         } else {
                  fprintf(stderr, ".");
         }

          // Total Track Time not exceeded, cmdTimer enabled, 30 sec boundry crossed.
        if( (cmsTrk.trkDuration > ( (float)(cmdTimer[TRACK15M]-totTrktime)/3600.0)) &&
           (cmdTimer[TRACK15M] > 0) && ( ( CurrTime - (cmdTimer[TRACK15M]-TRK_INTERVAL) ) >= 0)  ) {
             cmdTimer[TRACK15M] = cmdTimer[TRACK15M] + ( (long)( (CurrTime - (cmdTimer[TRACK15M]- (TRK_INTERVAL*2)) ) /TRK_INTERVAL) * TRK_INTERVAL); // If Curr time jmp
             issueTrk(&cmdTimer[TRACK15M], &PeriodicPkt[TRACK15M] );
        } 
             fprintf(stderr, " ### DEBUG INFO : cmdTimer %ld CurrTime %ld [diff %ld]\n", cmdTimer[TRACK15M], CurrTime, ( CurrTime - (cmdTimer[TRACK15M]-TRK_INTERVAL)) );

  //
  //  Periodic command otherthan Track
  //
    if(!cptr->cmdelem.priority) 
    {
       bzero( (char *)&devResp,devResponseSize);
       for(i = 1 ; i < TOT_DEVCMD; i++ ) {

          if( ( (cmdTimer[i] > 0) && (!abs(cmdTimer[i] - CurrTime))) || ((cmdTimer[i] > 0) && (CurrTime >= cmdTimer[i])) )
           { 
             fprintf(stderr, "### Device cmdTimer [%ld] - currentTime [%ld] \n", cmdTimer[i], CurrTime);
             printCmdPkt((parseCMSCmd *)&PeriodicPkt[i]);             
             devSpecExecute(&PeriodicPkt[i],&devResp,ASYNCH);
             bzero( (char *)&devResp,devResponseSize);
             cmdTimer[i] = CurrTime+ (atoi((const char *) (PeriodicPkt[i].data.prmvalue[0]))/1000) ; break ;// set next time
             fprintf(stderr,"  Prmvalue %d  CmdTimer %ld \n", atoi(PeriodicPkt[i].data.prmvalue[i]),  cmdTimer[i]);
          }
       }
    } 

    return ;
 }
