/* Program to create a file and write some data the file */
#include <stdio.h>
#include <string.h>
#include <time.h>
const char SRC[100] = "/home/teleset/Desktop";  
main( )
{
     FILE *fp,*f;
    char stuff[25],filename[50]="/home/teleset/Desktop/sigcon_",docname[50]="/home/teleset/Desktop/sig_";
      //  char stuff[25];
    //    char filename[50] = "sigcon_";
     //    strcat(SRC,filename);
     int index;
     char stamp1[26], stamp2[12];
     int i;
    time_t t1;
    time(&t1);
  ctime_r(&t1, stamp1);
  if (stamp1[8] == ' ') stamp2[0] = '0';
  else stamp2[0] = stamp1[8];
  stamp2[1] = stamp1[9];
  for (i=0;i<3;i++) stamp2[i+2] = stamp1[i+4];
  for (i=0;i<2;i++) stamp2[i+5] = stamp1[i+11];
  stamp2[7] = 'h';
  stamp2[8] = '_'; 
  stamp2[9]= stamp1[22];
  stamp2[10]=stamp1[23];
  stamp2[11] = '\0'; 
   strcat(filename,stamp2);
   strcat(docname,stamp2);
      printf("Time is %s in the path %s\n\n",stamp1,SRC);
    // fp = fopen(stamp2,"w"); /* open for writing */
   
   f=fopen(filename,"a");
   fp = fopen(filename,"a"); /* open for writing */
     strcpy(stuff,"This is Start of file ");

     fprintf(fp,"##################");
      fprintf(fp,"  %s \n", stuff);
     for (index = 1; index <= 10; index++)
       {
          fprintf(f," I am the second file pointer Current TIME is  %s \n", stamp1);
        	fprintf(fp," Current TIME is  %s \n", stamp1);
      
        }
    fprintf(fp,"This is closing of file at time %s\n", stamp1);
    fprintf(fp,"##################");
     fclose(fp); /* close the file before ending program */
  
   /*  fprintf(f,"##################");
      fprintf(f,"  %s \n", stuff);
     for (index = 1; index <= 10; index++)
     	fprintf(f," I am the second file pointer Current TIME is  %s \n", stamp1);
    fprintf(f,"This is closing of file at time %s\n", stamp1);
    fprintf(f,"##################");
     fclose(f);  */
}