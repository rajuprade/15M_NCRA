/* calepoch_ routine */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "source.h" 
#include "constant.h" 

 
 double fangle_(char * , int *);

 SOURCE sss;
 final  val;
 union udcoord ud ;

void calculateazel(char **srcline, char **argv,char** resultInfo)
{
  // char *srcline[ ] = {  "3C286","13h28m49.65s", "+30d45'58.6", "1950.0" };
   char strout[12][512];
   char lststring[80]; unsigned char lsti[8];
   char *format_str = "\0";
   int *d1, *d2, *d31, *stat, i;
   double *mytime;
   int it[3];
   float *d32;
   double *d3, *epoch, *djm, ti, *lst, *t0az;
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
   *d3 = (double) atof(argv[2]);

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

     ud.dcoord[0]=sss.ra0= ra_Rad;    /* REFERENCE RA  , DEC, EPOCH */
     ud.dcoord[1]=sss.dec0= dec_Rad; 
     ud.dcoord[2]= sss.ep0 = atof(srcline[3]);
     ud.dcoord[7] = sss.epd =  *epoch ; /* Fortran DCOORD(8) : TARGET/REFERENCE EPOCH */
     
     sss.time = (float) *mytime ;    
     sss.te0 = (float ) *mytime ; 
     sss.raoff = sss.dra=sss.decoff=sss.ddec=sss.azoff=sss.daz=sss.del=0;    

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

//-----------< Azimuth and Elevation Calculation >------------------//
    sss.epd =  *djm ;  // Internally used as MJD    
    azel(&sss,&val);
    sangle_(&val.az,"",&strout[2][0]);
    sangle_(&val.el,"",&strout[3][0]);
    printf(" Source AZIMUTH %s  and ELEVATION %s [%g:%g] \n", strout[2],strout[3],val.az,val.el);
    
    strcpy(resultInfo[0],strout[2]);
    strcpy(resultInfo[1],strout[3]);	
    sprintf(resultInfo[2],"%5.4f",val.az );
    sprintf(resultInfo[3],"%5.4f", val.el);   

    free(d1);
    free(d2);
    free(d31);
    free(stat);
    free(d3);
    free(t0az);
    free(lst);
    free(epoch);
    free(d32);
    free(mytime);
    free(djm);
    for(i=0;i<3;i++)
    {
        free(it[i]);
    }
 
}
