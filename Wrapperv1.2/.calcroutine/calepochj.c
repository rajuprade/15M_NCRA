/* calepoch_ routine */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>

#include "source.h" 
#include "constant.h" 

 
 double fangle_(char * , int *);
 void precess(SOURCE *, double [], int *);

 SOURCE sss;
 final  val;
 union udcoord ud ;

/*
 double r2h = 3.819718634205488 ;
 double r2d = 57.29577951308232;
 double twopi = 6.283185307179586 ;
*/

int main(int argc, char **argv)
{
     
   // char *srcline[ ] = { "353COOL","17h03m00.00s","22d00'00.00","2000.0"};
  // char *srcline[ ] = { "3C147","05h38m43.50s","49d49'57.00","1950.0"};
  // char *srcline[ ] = { "CYGA","19h57m44.99s","40d36'00.0","1950.0"};
  // char *srcline[ ] = { "CYGB","16h41m57.00s","42d28'54.0","2000.0"};
      
 //  char *srcline[ ] = { "CYGA","19h57m44.99s","40d36'00.0","1950.0"};
     char *srcline[ ] = { "CRAB","5h31m30.00s","21d58'00.0","1950.0"};
 //  char *srcline[ ] = {"virgoa","12h28m18.00s","12d40'00.0","1950.0"};
 //  char *srcline[ ] = {"casa","23h21m11.00s","58d33'00.0","1950.0"};
  //char *srcline[ ] = { "SAGA","17h42m30s","-28d55'00","1950.0" };
  //char *srcline[ ] = { "B0518+165","05h18m16.10s", "+16d35'27.5", "1950.0" };
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
   double ra_Rad, dec_Rad;
   double azin,azout, az15m;
   float scaz,scel,scanr;
   int mode; /* mode 10 Reference to Target Epoch, 11 Precesses the coordinates */

   if(argc == 1)  {
       fprintf(stderr, "Usage %s YY MM DD Hr min sec ScanLength(deg) ElScanRate AzScanRate (deg/min) \n",argv[0]) ;
       exit(1);
   }

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

   *d1 = (int) atoi(argv[1]);    // year
   *d2 = (int) atoi(argv[2]);    // mm
   *d3 = (double ) atof(argv[3]); //dd

   it[0] = (int) atoi(argv[4]);  // hh
   it[1] = (int) atoi(argv[5]);  // mm
   it[2] = (int ) atof(argv[6]);  // sec

//-------------------< INPUT >---------------------------//
   fprintf(stderr,  "  date %d %d %lf Time %d:%d:%d \n", (int) *d1, (int) *d2, (double) *d3, it[0],it[1],it[2]); 

   *mytime =    (double) ( (double) (it[0] + ( it[1]/60.0) + (it[2]/3600.0) ))/r2h;

   (void) fryej_(d1,d2,d3,epoch);   // Target Epoch
   fprintf(stderr, " fryej_ epoch %lf ", (double) *epoch);   

     ra_Rad = fangle_(srcline[1],&i); 
     dec_Rad = fangle_(srcline[2],&i);

     ud.dcoord[0]=sss.ra0= ra_Rad;    /* REFERENCE RA  , DEC, EPOCH */
     ud.dcoord[1]=sss.dec0= dec_Rad; 
     ud.dcoord[2]= sss.ep0 = atof(srcline[3]);
     ud.dcoord[7] = sss.epd =  *epoch ; /* Fortran DCOORD(8) : TARGET/REFERENCE EPOCH */
     sss.raoff = sss.dra=sss.decoff=sss.ddec=sss.azoff=sss.daz=sss.del=0;    
     sss.te0 = 0;

     sss.time = (float) *mytime ;    

     sss.del = (double ) atof(argv[8]) * 4.0;     // Elevation scan rate
     sss.daz = (double ) atof(argv[9]) * 4.0;     // Azimuth scan rate
     
     scaz = sss.daz; if(scaz < 0.0) scaz = scaz * -1.0;
     scel = sss.del; if(scel < 0.0) scel = scel * -1.0;

     if(scaz != 0.0 || scel != 0.0 ) {
        if(scaz < scel && scaz !=0.0) scanr=scaz;   // Az is lesser
        else if ( scel != 0.0 ) scanr = scel; // elevation lesser
        else scanr = scaz; // az more
     }else scanr = 0.0;

     if( scanr != 0.0 ) 
     { sss.th0 = (double ) *mytime + (double) ( ( (atof(argv[7]) * 0.5)/r2d)/scanr ); } // Scan Length in degrees to radian. 0.5 multiplied to note the expected peak is at length/2
     else { sss.th0 = (double ) *mytime; }
     
     fprintf(stderr, " ----> th0 %lf [%lf] %lf %lf \n", sss.th0 * r2h, *mytime * r2h, sss.del/4.0, sss.daz/4.0);
    /* type (1 * (3.14/180)) / ( (1/60) * 15 * (3.14/180) ) => 1d ( d-> radian) /1m (m-> hr->  deg -> radian) */
//-------------------< Modified Julian Date CALC >---------------------------//

   (void) ep2daj_((float *)&sss.ep0,d1,d2,d31,d32);   /* Epoch To YYMMDD.D conversion */

#ifdef DEBUGJ
   fprintf(stderr, " ep2daj_  %d %d %d %f   ", (int) *d1, (int) *d2, (int) *d31, (float) *d32); 
#endif
   (void) slacaldj_(d1,d2,d31,&sss.ep0,stat);          // Calculation date to Reference MJD */ 
   fprintf(stderr, " mjd_ref %lf %d \n", (double ) sss.ep0, (int) *stat);

   (void) ep2daj_((float *)&sss.epd,d1,d2,d31,d32);   /* Epoch To YYMMDD.D conversion */
#ifdef DEBUGJ
   fprintf(stderr, " ep2daj_  %d %d %d %f   ", (int) *d1, (int) *d2, (int) *d31, (float) *d32); 
#endif
   (void) slacaldj_(d1,d2,d31,&sss.epd,stat);          // Calculation date to Target MJD */ 
   fprintf(stderr, " mjd_target %lf %d \n", (double ) sss.epd, (int) *stat);

//---------------< LST calculation Part >--------------------------//
    *djm = sss.epd ;
 
     ti= *mytime+(tz1/r2h);
    *t0az = (double)*djm +(ti * r2h/24);

     (void) slagmst_(t0az,lst);  
     *lst = *lst - long1/r2d;
      if(*lst > twopi)*lst=*lst - twopi;

     i=stime_(lst,format_str,lststring);     
     printf(" LST %lf lststing %s \n", *lst, lststring); 

    
//------------------< PRECESSION PART >---------------------------// 
     i=0;
     printf(" Given RA %s DEC %s \n", srcline[1], srcline[2]);

     mode=10;  /* REFERENCE TO TARGET EPOCH */
     precess(&sss, &ud.dcoord,&mode);
     printf(" Precessed RA %g DEC %g ref %g \n", sss.rad,sss.decd, sss.epd ); 

// --------------< Rise-Set >-------------------------------------//
    rset(&sss,&val); 
    stime_(&val.lctr,"",&strout[0][0]);
    stime_(&val.lcts,"",&strout[1][0]);
    printf(" Source rises %s  and set %s [%g:%g] \n", strout[0],strout[1],val.lctr,val.lcts);

//-----------< Azimuth and Elevation Calculation >------------------//
    sss.epd =  *djm ;  // Internally used as MJD    
    azel(&sss,&val);
    az15m=val.az;

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
   // ANT AzEl Logic in Radians
  if( ( az15m >= M_PI ) && (az15m <= (M_PI*2)) ) az15m=az15m-M_PI;
  else az15m=az15m+M_PI;

  if(az15m > M_PI/2.)azin=az15m-(2.*M_PI);
  else azin = az15m;

  if(az15m >= (3*M_PI/2.)) azout=az15m-(2.*M_PI);
  else azout = az15m;

    sangle_(&val.az,"",&strout[2][0]);
    sangle_(&val.el,"",&strout[3][0]);
    printf(" Source AZIMUTH %s  and ELEVATION %s [%g:%g] \n", strout[2],strout[3],val.az,val.el);
 // fprintf(stderr, " #*# time %g [%g] azin %g azout %g el %g \n",   (double) (it[0] + ( it[1]/60.0) + (it[2]/3600.0) ), az15m , azin, azout, val.el * r2d );
    fprintf(stderr, " #*# time %g [%g] azin %g azout %g el %g \n",   (double) (it[0] +(it[1]/60.0)+(it[2]/3600.0) ), az15m , azin*r2d, azout*r2d, val.el*r2d );
}
