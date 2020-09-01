/* calepoch_ routine */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

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

void calculateriseset(char **srcline, char **argv, char** resultInfo,int* lenrisestring, int* lensetstring, int* lenuptimestring,int* lenrisedouble, int* lensetdouble, int* lenuptimedouble)
{
   //char *srcline[ ] = {  "3C286","13h28m49.65s", "+30d45'58.6", "1950.0" };
   char strout[12][512];
   char lststring[80]; unsigned char lsti[8];
   char *format_str = "\0";
   int *d1, *d2, *d31, *stat, i;
   double *mytime;
 char uptime_str[512];	  
   int *it[3];
   float *d32;
   double *d3, *epoch, *djm, ti, *lst, *t0az;
   double tz1 = -5.5 ;
   double long1 = (double)atof(argv[6]);//-74.05; 
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

   *it[0] = (int) atoi(argv[3]);
   *it[1] = (int) atoi(argv[4]);
   *it[2] = (int ) atof(argv[5]); 
//-------------------< INPUT >---------------------------//
   fprintf(stderr,  "  date %d %d %lf Time %d:%d:%d \n", (int) *d1, (int) *d2, (double) *d3, *it[0],*it[1],*it[2]); 

   *mytime =    (double) ( (double) (*it[0] + (*it[1]/60.0) + (*it[2]/3600.0) ))/r2h;

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

// --------------< Rise-Set >-------------------------------------//
    rset(&sss,&val); 
    if(&val.flag!=-1) 
    {
    stime_(&val.lctr,"",&strout[0][0]);
    stime_(&val.lcts,"",&strout[1][0]);
    val.lctu=val.lcts-val.lctr;  //uptime=settime-risetime  -by psl
     stime_(&val.lctu,"",uptime_str);
	
    } 

 printf(" Source rises %s  and set %s  uptime %s [%g:%g:%g] \n", strout[0],strout[1],uptime_str,val.lctr,val.lcts,val.lctu); 
    
     resultInfo[0] = (char*) malloc(sizeof(char)*20);
     resultInfo[1] = (char*) malloc(sizeof(char)*20);
     resultInfo[2] = (char*) malloc(sizeof(char)*20);
     resultInfo[3] = (char*) malloc(sizeof(char)*20);
     resultInfo[4] = (char*) malloc(sizeof(char)*20);
     resultInfo[5] = (char*) malloc(sizeof(char)*20);

    strcpy(resultInfo[0],strout[0]);
    strcpy(resultInfo[1],strout[1]);
    strcpy(resultInfo[2],uptime_str);
    sprintf(resultInfo[3],"%g", val.lctr);
    sprintf(resultInfo[4],"%g", val.lcts);
    sprintf(resultInfo[5],"%g", val.lctu);


     *lenrisestring = strlen(resultInfo[0]);
     *lensetstring = strlen(resultInfo[1]);
     *lenuptimestring = strlen(resultInfo[2]);
     *lenrisedouble = strlen(resultInfo[3]);
     *lensetdouble = strlen(resultInfo[4]);
     *lenuptimedouble = strlen(resultInfo[5]);


    free(d1);free(d2);free(d31);free(stat);free(djm);free(d3); 	
      free(epoch);
      free(d32);
      free(t0az);
      free(mytime);
      free(lst);
    for(i=0;i<3;i++)
     {free(it[i]); }	
	
	return;

}
