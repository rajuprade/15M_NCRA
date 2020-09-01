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

void getStringInfo(char** myString){
//  myString = (char** ) malloc(sizeof(int)*3);
  printf("size %d\n", sizeof(myString[0]));  
  myString[0] = (char*) malloc(sizeof(char)*20);
  myString[0] = "stringdata0";
  myString[1] = (char*) malloc(sizeof(char)*20);
  myString[1] = "stringdata1";
  myString[2] = (char*) malloc(sizeof(char)*20);
  myString[2] = "stringdata2";
  printf("str data %s \n", *myString);
  printf("size %d\n", sizeof(myString[0]));

  printf("address1 %d length %d", &myString[0],strlen(myString[0]));
  printf("address2 %d length %d", &myString[1], strlen(myString[1]));
  printf("address3 %d length %d", &myString[2],strlen(myString[2]));


  return ;
}

void getStringFromByte(char* Result){
   Result = "Test";
   printf("test data %s",Result);	 
//   Result[1] = "Test Again";
//   Result[2] = "Test Test Test Test Test Test";
   return;
}
void getStringByReference(char* Result){
   Result = "Test";
   printf("test data %s",Result);
//   Result[1] = "Test Again";
//   Result[2] = "Test Test Test Test Test Test";
   return;
}

void calculateLST1(char** srcline, char** argv,char** resultInfo,int* lenlststring, int* lenlstdouble, int* lenjddouble)
{
	printf("In LST CALC");
   	char lststring[80]; unsigned char lsti[8];
   	char *format_str = "\0";
        char jdval[20], lstval[20];
	int *d1, *d2, *d31, *stat, i;
   	double *mytime;
   	int *it[3];
   	float *d32;
   	double *d3, *epoch, *djm, ti, *lst, *t0az;
   	double tz1 = -5.5 ;
   	double long1 = (double)atof(argv[6]);// -74.05;
   	double ra_Rad, dec_Rad;
   	int mode;
	epoch =(double *) malloc(sizeof(double));
   	d32 =(float *) malloc(sizeof(float));
   	for(i=0;i<3;i++){
        	it[i] =(int *) malloc(sizeof(int));
   	}
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
   	*it[0] = (int ) atoi(argv[3]);
   	*it[1] = (int ) atoi(argv[4]);
   	*it[2] = (int ) atof(argv[5]);
   	fprintf(stderr,  "  date %d %d %lf Time %d:%d:%d \n", (int) *d1, (int) *d2, (double) *d3, *it[0],*it[1],*it[2]);

   	*mytime =    (double) ( (double) (*it[0] + ( *it[1]/60.0) + (*it[2]/3600.0) ))/r2h;
       
        (void) fryej_(d1,d2,d3,epoch);
   	fprintf(stderr, " fryej_ epoch %lf ", (double) *epoch);

     	ra_Rad = fangle_(srcline[1],&i);
     	dec_Rad = fangle_(srcline[2],&i);

     	ud.dcoord[0]=sss.ra0= ra_Rad;
     	ud.dcoord[1]=sss.dec0= dec_Rad;
     	ud.dcoord[2]= sss.ep0 = atof(srcline[3]);
     	ud.dcoord[7] = sss.epd =  *epoch ;

     	sss.time = (float) *mytime ;
  	sss.te0 = (float ) *mytime ;
     	sss.raoff = sss.dra=sss.decoff=sss.ddec=sss.azoff=sss.daz=sss.del=0;

   	(void) ep2daj_((float *)&sss.ep0,d1,d2,d31,d32);

#ifdef DEBUGJ
   fprintf(stderr, " ep2daj_  %d %d %d %f   ", (int) *d1, (int) *d2, (int) *d31, (float) *d32);
#endif
   (void) slacaldj_(d1,d2,d31,&sss.ep0,stat);
   fprintf(stderr, " mjd_ref %lf %d \n", (double ) sss.ep0, (int) *stat);

   (void) ep2daj_((float *)&sss.epd,d1,d2,d31,d32);
#ifdef DEBUGJ
   fprintf(stderr, " ep2daj_  %d %d %d %f   ", (int) *d1, (int) *d2, (int) *d31, (float) *d32);
#endif
	(void) slacaldj_(d1,d2,d31,&sss.epd,stat);
   	fprintf(stderr, " mjd_target %lf %d \n", (double ) sss.epd, (int) *stat);
    	
	*djm = sss.epd ;

	 ti= *mytime+(tz1/r2h);
   	*t0az = (double)*djm +(ti * r2h/24);

    	(void) slagmst_(t0az,lst);

     	*lst = *lst - long1/r2d;
     	 if(*lst > twopi)*lst=*lst - twopi;

         i=stime_(lst,format_str,lststring);
   
	 printf(" LST %lf lststing %s \n", *lst, lststring);
	 printf(" JD %d\n", sss.epd);
	 printf(" lst double %f\n",*lst);

	 resultInfo[0] = (char*) malloc(sizeof(char)*20);
   	 resultInfo[1] = (char*) malloc(sizeof(char)*20);
  	 resultInfo[2] = (char*) malloc(sizeof(char)*20);


	 sprintf(jdval,"%5.4f", sss.epd);
         sprintf(lstval,"%5.4f", *lst);
         
	 strcpy(resultInfo[0],lststring);
         strcpy(resultInfo[1],jdval);
	 strcpy(resultInfo[2],lstval);
	
	*lenlststring = strlen(resultInfo[0]);
	*lenlstdouble = strlen(resultInfo[1]);
	*lenjddouble = strlen(resultInfo[2]);
 
//	 sprintf(jdval,"%5.4f", *lst);
//	 sprintf(lstval,"%5.4f", sss.epd);
  	 
/*	 printf("address1 %d length %d\n", resultInfo[0],strlen(resultInfo[0]));
	 printf("address2 %d length %d\n", resultInfo[1], strlen(resultInfo[1]));
	 printf("address3 %d length %d\n", resultInfo[2],strlen(resultInfo[2]));
 
         printf("val1 %d \n", &resultInfo[0]);
         printf("val2 %d \n", &resultInfo[1]);
         printf("val3 %d \n", &resultInfo[2]);
         printf("base val %d\n", resultInfo);
         printf("base val addr %d\n", &resultInfo);
*/
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

