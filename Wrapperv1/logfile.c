/******** Log file is separated out in a file...

All module belonging to Log file and command file is written here dt.26/07/11 

Modifying Logfile.c so that logfile can be generated for every day....Dt.12.10.11

**********/


#include "logfile.h"
#include <string.h>   //  // used for LOG generation
#include <time.h>     // used for LOG generation

FILE *fp,*f;
char filename[512],docname[512];
void Openfile(char *);
void CloseFile();

void Openfile(char *xmlbuffer)
 {
     char *envptr;  
   //  char *xmlbuffer=(char *)malloc(sizeof(char)*4096); 
    // char stuff[25] ;                             
     char stamp1[26], stamp2[12];
     int i;
     time_t t1;

    if( ( envptr = ( char * ) getenv("LOGPATH")) != NULL )  // It takes the LOGPATH from conf file.
         {
                strcpy(filename,envptr);
         }
        else
         {
             fprintf(stderr,"LOGPATH is not defined is the conf file\n\n");
          } 

   if( ( envptr = ( char * ) getenv("COMMANDPATH")) != NULL )     // It takes the COMMANDPATH from conf file.
            {
                   strcpy(docname,envptr);
            }
            else
         {
             fprintf(stderr,"COMMANDPATH is not defined is the conf file\n\n");
          } 



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

   if ( (FILE *) (fp = fopen(filename,"a+")) == (FILE *) NULL )  { 
             fprintf(stderr, " File %s : Could not open \n", filename); 
             return;
   }

   if ( (FILE *) (f = fopen(docname,"w")) == (FILE *) NULL ) { 
             fprintf(stderr, " File %s : Could not open \n", filename); 
             return;
   } 
    fprintf(fp," Starting TIME is  %s \n", stamp1);

     fprintf(fp,"%s\n",xmlbuffer);
     fprintf(f,"%s\n",xmlbuffer);

 }



void CloseFile()
{ 
    char stamp1[26];
    time_t t1;
    time(&t1);
    ctime_r(&t1, stamp1);
    fprintf(fp," Closing TIME is  %s \n", stamp1);
    fclose(fp); /* close the file before ending program */
    fclose(f);
}
