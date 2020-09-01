/* calepoch_ routine */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "source.h" 
#include "constant.h" 

 
 double fangle_(char * , int *);
 void precess(SOURCE *, double [], int *);

 SOURCE src;
 final  val;
 union udcoord ud ;

/*
 double r2h = 3.819718634205488 ;
 double r2d = 57.29577951308232;
 double twopi = 6.283185307179586 ;
*/

void calculatePrcessValues(char **srcline, char **argv, char** resultInfo)
{
   //char *srcline[ ] = {  "3C286","13h28m49.65s", "+30d45'58.6", "1950.0" };
   char strout[12][512];
   char lststring[80]; unsigned char lsti[8];
   char *format_str = "\0";
   int *d1, *d2, *d31, *stat, i;
   double *mytime;
   int it[3];
   float *d32;
   double *d3, *epoch, *djm, ti, *lst, *t0az;
   double tz1 = -5.5 ;
   double long1 =  (double) atof(argv[6]);//-74.05; 
   double ra_Rad, dec_Rad;
   int mode; /* mode 10 Reference to Target Epoch, 11 Precesses the coordinates */

   /*if(argc == 1)  {
       fprintf(stderr, "Usage %s YY MM DD Hr min sec \n",argv[0]) ;
       exit(1);
   }*/


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

   *d1 = (int) atoi(argv[0]);
   *d2 = (int) atoi(argv[1]);
   *d3 = (double ) atof(argv[2]);

   it[0] = (int) atoi(argv[3]);
   it[1] = (int) atoi(argv[4]);
   it[2] = (int ) atof(argv[5]); 

//-------------------< INPUT >---------------------------//
   fprintf(stderr,  "  date %d %d %lf Time %d:%d:%d \n", (int) *d1, (int) *d2, (double) *d3, it[0],it[1],it[2]); 

   *mytime =    (double) ( (double) (it[0] + ( it[1]/60.0) + (it[2]/3600.0) ))/r2h;

   (void) fryej_(d1,d2,d3,epoch);   // Target Epoch
   fprintf(stderr, " fryej_ epoch %lf ", (double) *epoch);   

     ra_Rad = fangle_(srcline[1],&i);
     dec_Rad = fangle_(srcline[2],&i);

     ud.dcoord[0]=src.ra0= ra_Rad;    /* REFERENCE RA  , DEC, EPOCH */
     ud.dcoord[1]=src.dec0= dec_Rad; 
     ud.dcoord[2]= src.ep0 = atof(srcline[3]);
     ud.dcoord[7] = src.epd =  *epoch ; /* Fortran DCOORD(8) : TARGET/REFERENCE EPOCH */
     
     src.time = (float) *mytime ;    
     src.te0 = (float ) *mytime ; 
     src.raoff = src.dra=src.decoff=src.ddec=src.azoff=src.daz=src.del=0;    

//-------------------< Modified Julian Date CALC >---------------------------//

   (void) ep2daj_((float *)&src.ep0,d1,d2,d31,d32);   /* Epoch To YYMMDD.D conversion */

#ifdef DEBUGJ
   fprintf(stderr, " ep2daj_  %d %d %d %f   ", (int) *d1, (int) *d2, (int) *d31, (float) *d32); 
#endif
   (void) slacaldj_(d1,d2,d31,&src.ep0,stat);          // Calculation date to Reference MJD */ 
   fprintf(stderr, " mjd_ref %lf %d \n", (double ) src.ep0, (int) *stat);

   (void) ep2daj_((float *)&src.epd,d1,d2,d31,d32);   /* Epoch To YYMMDD.D conversion */
#ifdef DEBUGJ
   fprintf(stderr, " ep2daj_  %d %d %d %f   ", (int) *d1, (int) *d2, (int) *d31, (float) *d32); 
#endif
   (void) slacaldj_(d1,d2,d31,&src.epd,stat);          // Calculation date to Target MJD */ 
   fprintf(stderr, " mjd_target %lf %d \n", (double ) src.epd, (int) *stat);
  
//------------------< PRECESSION PART >---------------------------// 
     i=0;
     printf(" Given RA %s DEC %s \n", srcline[1], srcline[2]);

     mode=10;  /* REFERENCE TO TARGET EPOCH */
     precess(&src, &ud.dcoord,&mode);
     printf(" Precessed RA %f DEC %f ref %f \n", src.rad,src.decd, src.epd );
	
     sprintf(resultInfo[0],"%5.7f", src.rad);
     sprintf(resultInfo[1],"%5.7f", src.decd); 
     sprintf(resultInfo[2],"%5.7f", src.epd);
	free(d1);
	free(d2);
	free(d31);
	free(stat);
	free(djm);
	free(d3);
      free(epoch);
      free(d32);
      free(t0az);
      free(mytime);
      free(lst);
   for(i=0;i<3;i++)
     {free(it[i]); }
	
	return src;

}
	