#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>

#include "constant.h"
#include "source.h"
#include "reqResp.h"
#include "devServo.h"

void initAntPara(AntPara *);
void initTrkPara(TrkPara *);
int setAntPara(parseCMSCmd *,AntPara *);
int setTrkPara(parseCMSCmd *,TrkPara *);
void cms_hms(char *,char *);
void cms_dams(char *,char *);
double hms2sec(char *);
void checkRange(SrvPara *);
int  formServoCmd(parseCMSCmd *);

extern double fangle_(char * , int *);
extern void precess(SOURCE *, double [], int *);
extern int getAZEL(SrvPara *);

double hms2sec(char *strHMS)
{
   float hr,min,sec;
   sscanf(strHMS,"%f%*c%f%*c%f",&hr,&min,&sec);
   return (double) ( (hr*3600)+ (min*60)+ sec);
}

void cms_hms(char *dest, char *src)
{
  int hr,min; float sec;
   // format dd:dd:dd
  sscanf(src,"%d%*c%d%*c%f",&hr,&min,&sec);
  sprintf(dest,"%.2dh%.2dm%fs",hr,min,sec);
  
}

void cms_dams(char *dest, char *src)
{
  int hr,min; float sec;
   // format dd:dd:dd
  sscanf(src,"%d%*c%d%*c%f",&hr,&min,&sec);
  sprintf(dest,"%.2dd%.2d'%f\"",hr,min,sec);
}

void initAntPara(AntPara *antpara)
{
    antpara->azcorr = 0.0;
    antpara->elcorr = 0.0;

// Location
    antpara->timezone = TIMEZONE;
    antpara->lat = LAT15M;
    antpara->longitude = LONG15M;
    antpara->longcorr=0.0;  // Longitude correctionHeight

// Limits
    antpara->elmin = 18.0 ;
    antpara->elmax = 90.0 ;
    antpara->azmin = -250.0 ;
    antpara->azmax = 250.0;
 
/* Response control
    antpara.tflag = 0;  
    antpara.ton  = 0;  
*/
}

int setAntPara(parseCMSCmd *cmsAntcmd,AntPara *antptr)
{
    char *antKeys[] = { "ant_az_offset", "ant_el_offset", "elmin", "elmax", "azmin", "azmax", "trkflag", "trkon", "timezone", "longitude", "lat", "longcorr" };
    typedef enum {  ANT_AZ_OFFSET, ANT_EL_OFFSET, ELMIN, ELMAX, AZMIN, AZMAX, TRKFLAG, TRKON, STIMEZONE, LONGITUDE, LAT, LONGCORR, TOT_ANTKEYS } antparaEnum;
    int i, j, rc, key;
    DataPkt *dptr;
    dptr = &cmsAntcmd->data ;

     for(i=0; i < dptr->numpkt; i++ )
     {
          key=-1;
          for(j=0; j < TOT_ANTKEYS;j++) {
              if(!strcasecmp(dptr->prmname[i],antKeys[j])) { key=j; break; }
          }

          switch(key)
          {
             /* In arcmin */
             case ANT_AZ_OFFSET    : antptr->azcorr = (double)atof(dptr->prmvalue[i])* (M_PI/180.); 
                                     fprintf(stderr, "AZCORR %lf \n", antptr->azcorr * r2d);  break;

             case ANT_EL_OFFSET    : antptr->elcorr = (double)atof(dptr->prmvalue[i])* (M_PI/180.);
                                     fprintf(stderr, "ELCORR %lf \n", antptr->elcorr * r2d);  break;

             /* In Degree */
             case ELMIN     : antptr->elmin = atof(dptr->prmvalue[i]); break;
             case ELMAX     : antptr->elmax = atof(dptr->prmvalue[i]); break;
             case AZMIN     : antptr->azmin = atof(dptr->prmvalue[i]); break;
             case AZMAX     : antptr->azmax = atof(dptr->prmvalue[i]); break;

             case TRKFLAG   : antptr->trkflag = atoi(dptr->prmvalue[i]); break;
             case TRKON     : antptr->trkon   = atoi(dptr->prmvalue[i]); break;
             /* In degrees and meters? */
         //  case STIMEZONE  : antptr->timezone = atof(dptr->prmvalue[i]); break; // in hrs
             case LAT       : antptr->lat = atof(dptr->prmvalue[i]); break;
             case LONGITUDE : antptr->longitude = atof(dptr->prmvalue[i]); break;
             case LONGCORR  : antptr->longcorr = atof(dptr->prmvalue[i]);break;
          } 
     }
    return 0;  
}

void initTrkPara(TrkPara *cmsTrk)
{
               cmsTrk->ra_app = 0.0; 
               cmsTrk->dec_app = 0.0;
               cmsTrk->target_epoch = 0.0;
               cmsTrk->ra_offset = cmsTrk->dra = cmsTrk->dec_offset = cmsTrk->ddec = cmsTrk->dradec_reftime = 0.0 ;
               cmsTrk->az_offset = cmsTrk->daz = cmsTrk->el_offset = cmsTrk->del = cmsTrk->dazel_reftime = 0.0 ;
               cmsTrk->curr_time = 0.0 ;
               cmsTrk->scanp.length =  0.0;
     //        cmsTrk->outtrk = 0; If somebody stops the servo track paramter changes. Hence avoiding to assign value
               cmsTrk->cmdid = -1;
               cmsTrk->trkDuration = 12.0;
               cmsTrk->scanp.dra = cmsTrk->scanp.ddec = cmsTrk->scanp.daz = cmsTrk->scanp.del = 0.0;
}

int setTrkPara(parseCMSCmd *cmsTrkCmd, TrkPara *cmsTrk)
{
     char *trkKeys [] = { "source_name", "ra_mean", "dec_mean", "epoch", "ra_app", "dec_app", "target_epoch", "ra_offset",
                          "dra","dec_offset","ddec","d_ref_time","az_offset", "daz",  "el_offset","del","ref_time_offset", "current_time","trk_duration",
                          "scan_length","scan_dra","scan_ddec","scan_daz","scan_del" };
     typedef enum { SOURCE_NAME, RA_MEAN, DEC_MEAN, EPOCH, RA_APP, DEC_APP, TARGET_EPOCH, RA_OFFSET, DRA,DEC_OFFSET,DDEC, D_REF_TIME, AZ_OFFSET, DAZ, EL_OFFSET, DEL, REF_TIME_OFFSET, CURRENT_TIME, TRK_DURATION,
                    SCAN_LENGTH,  SCAN_DRA, SCAN_DDEC, SCA_DAZ, SCAN_DEL, TOT_TRKEYS } trkEnums;
     int i, j, rc=0, key;
     char sconv[15];
     DataPkt *dptr; 

     dptr = &cmsTrkCmd->data;

     for(i=0; i < dptr->numpkt; i++ )
     {
          key=-1;
          for(j=0; j < TOT_TRKEYS;j++) {
              if(!strcasecmp(dptr->prmname[i],trkKeys[j])) { key=j; break; }
          }

          switch(key)
          {
              case SOURCE_NAME     : strcpy(cmsTrk->source_name,dptr->prmvalue[i]); break;
                                     /* In Radian : RA_MEAN, DEC_MEAN */
              case RA_MEAN         : cms_hms(&sconv,&dptr->prmvalue[i]);
                                     cmsTrk->ra_mean =(double) fangle_(&sconv, &rc);rc=0;
                                      fprintf(stderr," ###INFO setTrkPara() : RA_mean %g [%s ] \n", (double  )cmsTrk->ra_mean, sconv);
                                     break;  
              case DEC_MEAN        :  cms_dams(&sconv,&dptr->prmvalue[i]);
                                       cmsTrk->dec_mean = (double) fangle_(&sconv, &rc);rc=0;
                                       fprintf(stderr," ###INFO setTrkPara() : DEC_mean %g [%s ] \n", (double  )cmsTrk->dec_mean, sconv);
                                     break;  
              case EPOCH           : cmsTrk->epoch = (float) atof(dptr->prmvalue[i]);
                                     fprintf(stderr," ###INFO setTrkPara() : Epoch %f [%s ] \n",(float) cmsTrk->epoch, dptr->prmvalue[i]);
                                     break;  
                                     /* Temporary Making it zero */
              case RA_APP          : cmsTrk->ra_app = 0.0;  break ;  
              case DEC_APP         : cmsTrk->dec_app = 0.0; break ;  
              case TARGET_EPOCH    : cmsTrk->target_epoch = 0.0; break;

                                    /*  degrees to Radian : RA_OFFSET, DEC_OFFSET */
              case RA_OFFSET       : cmsTrk->ra_offset  = atof(dptr->prmvalue[i])*(M_PI/180.); break;// Directly in degree hence converting to radian
              case DEC_OFFSET      : cmsTrk->dec_offset = atof(dptr->prmvalue[i])*(M_PI/180.); break;

                                    /*  degrees to Radian : AZ_OFFSET, EL_OFFSET */
              case AZ_OFFSET       : cmsTrk->az_offset  = atof(dptr->prmvalue[i])*(M_PI/180.); break;
              case EL_OFFSET       : cmsTrk->el_offset  = atof(dptr->prmvalue[i])*(M_PI/180.); break;

              /* Unit yet to be decided Currently Making all zeros */


              case DRA             : cmsTrk->dra = atof(dptr->prmvalue[i]); break;
              case DDEC            : cmsTrk->ddec = atof(dptr->prmvalue[i]); break;

              case D_REF_TIME      : cmsTrk->dradec_reftime = 0.0 ; break; 
              case DAZ             : cmsTrk->daz = atof(dptr->prmvalue[i]); break;
              case DEL             : cmsTrk->del = atof(dptr->prmvalue[i]); break;
              case REF_TIME_OFFSET : cmsTrk->dazel_reftime = 0.0 ; break; 
             
          
              case CURRENT_TIME    : cmsTrk->curr_time = 0.0 ; break ; // Will be set Later 
              case TRK_DURATION    : cmsTrk->trkDuration = (double)hms2sec(&dptr->prmvalue[i])/3600.0; break ; 
            
              case SCAN_LENGTH     : cmsTrk->scanp.length =  atof(dptr->prmvalue[i]); break;
              case SCAN_DRA        : cmsTrk->scanp.dra =  atof(dptr->prmvalue[i]); break;
              case SCAN_DDEC       : cmsTrk->scanp.ddec =  atof(dptr->prmvalue[i]); break;
              case SCA_DAZ         : cmsTrk->scanp.daz =  atof(dptr->prmvalue[i]); break;
              case SCAN_DEL        : cmsTrk->scanp.del =  atof(dptr->prmvalue[i]); break;
          }
     }
}

void checkRange(SrvPara *sp)
{
    AntPara *ap = &cmsTrk.antp;
  fprintf(stderr, "### CheckRange AZ %g [%g-%g] EL %g [%g-%g] \n", sp->az15m*r2d,ap->azmin,ap->azmax,sp->el15m*r2d, ap->elmin,ap->elmax);
    if( (sp->el15m * r2d) <= ap->elmin)
    {  sp->el15m = ap->elmin * (M_PI/180.); }

    if( (sp->el15m * r2d) >= ap->elmax)
    {  sp->el15m = ap->elmax * (M_PI/180.); }

    if( (sp->az15m * r2d) <= ap->azmin)
    {  sp->az15m = ap->azmin * (M_PI/180.); }
    
    if( (sp->az15m * r2d) >= ap->azmax)
    {  sp->az15m = ap->azmax * (M_PI/180.); }
    
   return ;
}

int formServoCmd(parseCMSCmd *srvTrk)
{
    static SrvPara servop;
    int i;
    struct tm mytime;
    time_t t;
    t= time(NULL);
    localtime_r(&t, &mytime);

     switch(cmsTrk.cmdid)
     {     case 1 : // TRACKOBJECT
           case 3 : // TRACKOFFAZEL
           case 4 : // TRACKOFFRADEC
           case 5 : // SCAN
                   getAZEL(&servop); break;
           // RAWTRACK
           case 2 :   break;
     }

     checkRange(&servop);
     memcpy(&cmsTrk.latestTrk,&servop,SrvParaSize);

     sprintf(srvTrk->data.prmvalue[1],"%.2d:%.2d:%.2d", cmsTrk.lcltm.tm_hour, cmsTrk.lcltm.tm_min, cmsTrk.lcltm.tm_sec);
                           // M.N, N=0
     sangle_(&servop.az15m,"3.0",srvTrk->data.prmvalue[2]);
     sangle_(&servop.el15m,"2.0",srvTrk->data.prmvalue[3]);

     i=strlen(&srvTrk->data.prmvalue[2]); while(srvTrk->data.prmvalue[2][i--] == ' '); srvTrk->data.prmvalue[2][i]='\0';

     i=strlen(&srvTrk->data.prmvalue[3]); while(srvTrk->data.prmvalue[3][i--] == ' '); srvTrk->data.prmvalue[3][i]='\0';

     fprintf(stderr, " -> TRK TIME ######  CURRENT %.2d:%.2d:%.2d TARGET [%s] [%s] [%s] \n", mytime.tm_hour, mytime.tm_min, mytime.tm_sec,
     srvTrk->data.prmvalue[1], srvTrk->data.prmvalue[2], srvTrk->data.prmvalue[3]);
     return 0 ;
}
