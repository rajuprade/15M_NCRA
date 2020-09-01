/* calepoch_ routine */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <malloc.h>


#include "source.h" 
#include "constant.h" 

 


 double fangle_(char * , int *);
 
 SOURCE sss;
 final  val;
 union udcoord ud ;


void calculateLST(char** srcline, char** argv, char** resultinfo)
{
	//printf("\nIn LST CALC\n");

	//printf("\n\n UPTO HERE .........%d.....1",bhu);

   	char lststring[40]; unsigned char lsti[8];
   	char *format_str = "\0";
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

     ra_Rad = fangle_(srcline[1],&i); // fine 6/4/11
     dec_Rad = fangle_(srcline[2],&i); //fine 6/4/11

         //ra_Rad=10.55;
		 //dec_Rad=20.09;


     	ud.dcoord[0]=sss.ra0= ra_Rad;
     	ud.dcoord[1]=sss.dec0= dec_Rad;
     	ud.dcoord[2]= sss.ep0 = atof(srcline[3]);
     	ud.dcoord[7] = sss.epd =  *epoch ;

     	sss.time = (float) *mytime ;
     	sss.te0 = (float ) *mytime ;
     	sss.raoff = sss.dra=sss.decoff=sss.ddec=sss.azoff=sss.daz=sss.del=0;

       (void) ep2daj_((float *)&sss.ep0,d1,d2,d31,d32); // fine... bhu 6/4/11
         
		//*d32=12;
		//*d31=10;
		//*d1=*d2=*d3=4;
#ifdef DEBUGJ
   fprintf(stderr, " ep2daj_  %d %d %d %f   ", (int) *d1, (int) *d2, (int) *d31, (float) *d32);
#endif
   (void) slacaldj_(d1,d2,d31,&sss.ep0,stat); //fine bhu 6/4/11

      //*stat=10.6;

   
   fprintf(stderr, " mjd_ref %lf %d \n", (double ) sss.ep0, (int) *stat);

  (void) ep2daj_((float *)&sss.epd,d1,d2,d31,d32); // fine bhu 6/4/11

#ifdef DEBUGJ
   fprintf(stderr, " ep2daj_  %d %d %d %f   ", (int) *d1, (int) *d2, (int) *d31, (float) *d32);
#endif
	(void) slacaldj_(d1,d2,d31,&sss.epd,stat); // fine bhu 6/4/11


   	fprintf(stderr, " mjd_target %lf %d \n", (double ) sss.epd, (int) *stat);
    	
	*djm = sss.epd ;

	 ti= *mytime+(tz1/r2h);
   	*t0az = (double)*djm +(ti * r2h/24);

    	(void) slagmst_(t0az,lst);  //  modified fotron file problem 6/4/11    

     	*lst = *lst - long1/r2d;


     	 if(*lst > twopi)*lst=*lst - twopi;

         i=stime_(lst,format_str,lststring); // fine..


         printf(" LST %lf lststing %s \n", *lst, lststring);

      
	  

 /* resultinfo[0]=(char *)malloc(sizeof(char)*strlen(lststring+1)); // bhushanG */
  strncpy(&resultinfo[0][0],lststring,39); resultinfo[0][39]='\0';

	// sprintf(resultinfo[1],"%5.4f", *lst);
	 //sprintf(resultinfo[2],"%5.4f", sss.epd);
	 //strcpy(resultinfo[1],*lst);
    	 //strcpy(resultinfo[2],sss.epd);

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
     


//	char str[10] = "Trying21";
//        printf("Original data %s \n", resultInfo[0]);
//        strcpy(resultInfo[0],str);
//        printf("printing modified data %s \n ", resultInfo[0]);

//      return;
}

//void getdata(char **a)
//{
 	//strcpy(a[0],"INDIA");
//}
