/* calepoch_ routine */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "source.h" 

 
 double fangle_(char * , int *);
 extern void precess(SOURCE *, double *[], int *);


 SOURCE sss;
 final  val;
 union udcoord ud ;
 double r2h = 3.819718634205488 ;
 double r2d = 57.29577951308232;
 double twopi = 6.283185307179586 ;

int main(int argc, char **argv)
{
   char *srcline[ ] = {  "3C286","13h28m49.65s", "+30d45'58.6", "1950.0" };
   char strout[12][512];
   char lststring[80]; unsigned char lsti[8];
   char *format_str = "\0";
   int *d1, *d2, *d31, *stat, i;
   double *mytime;
   int it[3];
   float *d32;
   double *d3, *epoch, *djm, ti, *lst, *t0az;
   double tz1 = -5.5 ;
   double long1 =  -74.05; 
   double ra_Rad, dec_Rad;
   int mode; /* mode 10 Reference to Target Epoch, 11 Precesses the coordinates */

   if(argc == 1)  {
       fprintf(stderr, "Usage %s YY MM DD Hr min sec \n",argv[0]) ;
       exit(1);
   }


   epoch =(double *) malloc(sizeof(double));
   d32 =(float *) malloc(sizeof(float));

   for(i=0;i<3;i++)
   it[i] =(int *) malloc(sizeof(int));
   i=0;
   mytime= (float *)malloc(sizeof(double));

   d1 =(int *) malloc(sizeof(int));
   d2 =(int *) malloc(sizeof(int));
   d31 =(int *) malloc(sizeof(int));
   stat =(int *) malloc(sizeof(int));

   d3   =(double *) malloc(sizeof(double));
   djm  =(double *) malloc(sizeof(double));
   t0az =(double *) malloc(sizeof(double));
   lst  =(double *) malloc(sizeof(double));

   *d1 = (int) atoi(argv[1]);
   *d2 = (int) atoi(argv[2]);
   *d3 = (double ) atof(argv[3]);

   it[0] = (int) atoi(argv[4]);
   it[1] = (int) atoi(argv[5]);
   it[2] = (int ) atof(argv[6]); 

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
     
     sss.time = (float) *mytime ;    
     sss.te0 = (float ) *mytime ; 
     sss.raoff = sss.dra=sss.decoff=sss.ddec=sss.azoff=sss.daz=sss.eloff=sss.del=0.0;    

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
     precess_(&sss, &ud.dcoord,&mode);

     printf(" Precessed RA %g DEC %g ref %g \n", sss.rad,sss.decd, sss.epd ); 

// --------------< Rise-Set >-------------------------------------//

    rset_(&sss,&val); 
    stime_(&val.lctr,"",&strout[0][0]);
    stime_(&val.lcts,"",&strout[1][0]);
    printf(" Source rises %s  and set %s [%g:%g] \n", strout[0],strout[1],val.lctr,val.lcts);

//-----------< Azimuth and Elevation Calculation >------------------//
    sss.epd =  *djm ;  // Internally used as MJD    
    azel_(&sss,&val);
    sangle_(&val.az,"",&strout[2][0]);
    sangle_(&val.el,"",&strout[3][0]);
    printf(" Source AZIMUTH %s  and ELEVATION %s [%g:%g] \n", strout[2],strout[3],val.az,val.el);

}
