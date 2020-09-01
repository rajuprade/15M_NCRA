/* calepoch_ routine */
/* Routines Used for 15m Track, extracted from the GMRT ONLINE s/w
   May 22nd, 2012 - Jitendra
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>

#include "source.h" 
#include "constant.h" 
#include "reqResp.h"
#include "devServo.h"

 
 double fangle_(char * , int *);
 void precess(SOURCE *, double [], int *);
 int getAZEL(SrvPara *);

 SOURCE sss;
 final  val;
 union udcoord ud ;

int getAZEL(SrvPara *sp)
{
/*
int  (int argc, char **argv)
    char *srcline[ ] = { "CYGA","19h57m44.99s","40d36'00.0","1950.0"};
  //char *srcline[ ] = { "CRAB","5h31m30.00s","21d58'00.0","1950.0"};
  //char *srcline[ ] = { "SAGA","17h42m30s","-28d55'00","1950.0" };
  //char *srcline[ ] = { "B0518+165","05h18m16.10s", "+16d35'27.5", "1950.0" };
*/
   extern TrkPara cmsTrk;
   char strout[12][512];
   char lststring[80]; unsigned char lsti[8];
   char *format_str = "\0";
   int *d1, *d2, *d31, *stat, i;
   double *mytime;
   int it[3];
   float *d32;
   double *d3, *epoch, *djm, ti, *lst, *t0az;
   double tz1 = TIMEZONE;
   double long1 =  LONG15M;
   double azin,azout, az15m;
   int mode; /* mode 10 Reference to Target Epoch, 11 Precesses the coordinates */

/*
 // --------------< Memory Allocation >-------------------------------//
*/
   epoch =(double *) malloc(sizeof(double));
   d32 =(float *) malloc(sizeof(float));
   for(i=0;i<3;i++) it[i] =(int *) malloc(sizeof(int));
   i=0;
   mytime= (double *)malloc(sizeof(double));
   d1 =(int *) malloc(sizeof(int));
   d2 =(int *) malloc(sizeof(int));
   d31 =(int *) malloc(sizeof(int));
   stat =(int *) malloc(sizeof(int));

   d3   =(double *) malloc(sizeof(double));
   djm  =(double *) malloc(sizeof(double));
   t0az =(double *) malloc(sizeof(double));
   lst  =(double *) malloc(sizeof(double));

//-------------------< INPUT >---------------------------//
   *d1 = 1900.0 + (double )cmsTrk.lcltm.tm_year;  // localtime_r gives 112 year for 2012 -- May 23, 2012 JPK
   *d2 = (int) cmsTrk.lcltm.tm_mon +1; // localtime_r give one month less -- May 23, 2012 JPK
   *d3 =  (int) cmsTrk.lcltm.tm_mday;

   it[0] = (int)cmsTrk.lcltm.tm_hour;
   it[1] = (int)cmsTrk.lcltm.tm_min;
   it[2] = (int )cmsTrk.lcltm.tm_sec;

   fprintf(stderr,  " ## INFO calepochc() : date %d %d %lf Time %d:%d:%d \n", (int) *d1, (int) *d2, (double) *d3, it[0],it[1],it[2]); 
   *mytime =    (double) ( (double) (it[0] + ( it[1]/60.0) + (it[2]/3600.0) ))/r2h;

   (void) fryej_(d1,d2,d3,epoch);   // Target Epoch
   fprintf(stderr, " ## INFO calepochc() : fryej_ epoch %lf ", (double) *epoch);   

/* In Radians */
     ud.dcoord[0]=sss.ra0=  cmsTrk.ra_mean;
     ud.dcoord[1]=sss.dec0= cmsTrk.dec_mean;
     ud.dcoord[2]=sss.ep0 = cmsTrk.epoch;
     ud.dcoord[7] = sss.epd =  *epoch ; /* Fortran DCOORD(8) : TARGET/REFERENCE EPOCH */
     sss.time = (float) *mytime ; 

    //if(cmsTrk.cmdid != 5 )
   
     sss.raoff = cmsTrk.ra_offset; 
     sss.dra   = cmsTrk.dra ;
     sss.decoff= cmsTrk.dec_offset;
     sss.ddec  = cmsTrk.ddec;
     if(  sss.dra != 0.0 || sss.ddec != 0.0 ) {
       sss.te0 = (float ) cmsTrk.dradec_reftime;
     }else { sss.te0 = (float )*mytime; } // If not SCAN Command;

     fprintf(stderr, " RADEC VALS : raoff %lf dra %lf decoff %lf ddec %lf te0 %lf \n", r2d * sss.raoff, r2d * sss.dra, r2d * sss.decoff, r2d * sss.ddec, r2h * sss.te0);

     sss.azoff = cmsTrk.az_offset;
     sss.daz   = cmsTrk.daz;
     sss.eloff = cmsTrk.el_offset;
     sss.del   = cmsTrk.del;

     if( sss.daz != 0.0 || sss.del != 0.0 ) {
       sss.th0 = (float ) cmsTrk.dazel_reftime;
     } else { sss.th0 = (float )*mytime; } // If not scan command

     sss.azcorr = (double ) cmsTrk.antp.azcorr;
     sss.elcorr = (double ) cmsTrk.antp.elcorr;

     fprintf(stderr, "### INFO ELAZ VALS : azoff %lf daz %lf eloff %lf del %lf th0 %lf \n", sss.azoff * r2d ,sss.daz*r2d ,sss.eloff * r2d,sss.del * r2d ,sss.th0 * r2h );

//-------------------< Modified Julian Date  - MJD CALC >---------------------------//

   (void) ep2daj_((float *)&sss.ep0,d1,d2,d31,d32);   /* Epoch To YYMMDD.D conversion */

#ifdef DEBUGJ
   fprintf(stderr, " ## INFO calepochc() : ep2daj_  %d %d %d %f   ", (int) *d1, (int) *d2, (int) *d31, (float) *d32); 
#endif
   (void) slacaldj_(d1,d2,d31,&sss.ep0,stat);          // Calculation date to Reference MJD */ 
   fprintf(stderr, " ## INFO calepochc() : mjd_ref %lf %d \n", (double ) sss.ep0, (int) *stat);

   (void) ep2daj_((float *)&sss.epd,d1,d2,d31,d32);   /* Epoch To YYMMDD.D conversion */
#ifdef DEBUGJ
   fprintf(stderr, " ## INFO calepochc() : ep2daj_  %d %d %d %f   ", (int) *d1, (int) *d2, (int) *d31, (float) *d32); 
#endif
   (void) slacaldj_(d1,d2,d31,&sss.epd,stat);          // Calculation date to Target MJD */ 
   fprintf(stderr, " ## INFO calepochc() : mjd_target %lf %d \n", (double ) sss.epd, (int) *stat);

//---------------< LST calculation Part >--------------------------//
    *djm = sss.epd ;
 
     ti= *mytime+(tz1/r2h);
    *t0az = (double)*djm +(ti * r2h/24);

     (void) slagmst_(t0az,lst);  
     *lst = *lst - long1/r2d;
      if(*lst > twopi)*lst=*lst - twopi;

     i=stime_(lst,format_str,lststring);     
     fprintf(stderr," ## INFO calepochc() : LST %lf lststing %s \n", *lst, lststring); 
//------------------< PRECESSION PART >---------------------------// 
     i=0;

     mode=10;  /* REFERENCE TO TARGET EPOCH */
     precess(&sss, &ud.dcoord,&mode);
     fprintf(stderr," ## INFO calepochc() : Precessed RA %g DEC %g ref %g \n", sss.rad,sss.decd, sss.epd ); 

// --------------< Rise-Set >-------------------------------------//
    rset(&sss,&val); 
    stime_(&val.lctr,"",&strout[0][0]);
    stime_(&val.lcts,"",&strout[1][0]);
    fprintf(stderr," ## INFO calepochc() : Source rises %s  and set %s [%g:%g] \n", strout[0],strout[1],val.lctr,val.lcts);

//-----------< Azimuth and Elevation Calculation >------------------//
    sss.epd =  *djm ;  // Internally used as MJD    
    azel(&sss,&val);

//-------------------< 15m Variable Assigning to SrvPara >------------------//
    az15m=val.az;
    sp->az = val.az ; sp->el = sp->el15m = val.el;

/*
   // ANT AzEl Logic in degrees
    az15m=val.az*r2d;

    if(az15m >= 180 && az15m <=360.0) az15m = az15m - 180.0;
    else az15m = az15m + 180;

    if(az15m > 90) azin=az15m-360.0;
    else azin = az15m;

    if(az15m >= 270) azout=az15m-360.0;
    else azout = az15m;
*/
   // ------------- ANT AzEl Logic in Radians -------------------//
  if( ( az15m >= M_PI ) && (az15m <= (M_PI*2)) ) az15m=az15m-M_PI;
  else az15m=az15m+M_PI;

  if(az15m > M_PI/2.)azin=az15m-(2.*M_PI);
  else azin = az15m;

  if(az15m >= (3*M_PI/2.)) azout=az15m-(2.*M_PI);
  else azout = az15m;

    sangle_(&val.az,"",&strout[2][0]);
    sangle_(&val.el,"",&strout[3][0]);
    fprintf(stderr," ## INFO calepochc() : Source AZIMUTH %s  and ELEVATION %s [%g:%g] \n", strout[2],strout[3],val.az,val.el);

/*
   if(cmsTrk.outtrk) { sangle_(&azout,"3.0",srvTrk->data.prmvalue[2]);
   }else { sangle_(&azin,"3.0",srvTrk->data.prmvalue[2]); }
  //sangle_(&val.el,"2.0", srvTrk->data.prmvalue[3]);
*/
   /* In radian */
   if(cmsTrk.outtrk) { sp->az15m = azout; } 
   else { sp->az15m = azin; }


    fprintf(stderr," #*# time %g [%g] az15m %g el15m %g \n",   (double) (it[0] +(it[1]/60.0)+(it[2]/3600.0) ), sp->az15m *r2d, sp->el15m *r2d );
 // fprintf(stderr, " #*# time %g [%g] azin %g azout %g el %g \n",   (double) (it[0] + ( it[1]/60.0) + (it[2]/3600.0) ), az15m , azin, azout, val.el * r2d );
   return 0;
}
