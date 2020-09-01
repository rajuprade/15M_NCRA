# include <stdio.h>
# include <stdlib.h>
# include <math.h>
# include <ctype.h>
# include <string.h>
# include <time.h>
# include <unistd.h>

extern void calculateLST(char**  , char**  , char** );

int main (int argc, char **argv)
{
    char *mysrc[] = { "3c286", "13h28m49.65s", "+30d45'58.6", "1950.0" };
    char *timedate[7];
    char **resultinfo ;
    int i=0;
    struct tm *timeh_l; time_t myclk ;

       if ( (resultinfo = (char **) calloc(3, sizeof(char *))) ==  NULL) {
           fprintf(stderr, "Error ### %s : calloc failed..\n",argv[0]);
           return -1;
        }
      for(i=0;i<3;i++){
                resultinfo[i] = malloc(sizeof(char) * 40);
        }
  for(i=0;i<8;i++) timedate[i]=(char*)malloc(sizeof(char)*40);

  strcpy(timedate[6],"-74.5");

  while (1) {
   myclk = time(NULL); timeh_l = localtime(&myclk);
   sprintf(timedate[0],"%d",(timeh_l->tm_year+1900));
   sprintf(timedate[1],"%d",timeh_l->tm_mon+1);
   sprintf(timedate[2],"%d",timeh_l->tm_mday);
   sprintf(timedate[3],"%d",timeh_l->tm_hour);
   sprintf(timedate[4],"%d",timeh_l->tm_min);
   sprintf(timedate[5],"%d",timeh_l->tm_sec);

   calculateLST(mysrc,(char **)timedate,resultinfo);
   fprintf(stderr, " LST is %s \n",resultinfo[0]);
   usleep(1000000);
 }
  return 0 ;
}
