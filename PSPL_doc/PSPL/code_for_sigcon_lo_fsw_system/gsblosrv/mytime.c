/* char * ctime(),struct tm *localtime(time),*gmtime(time),where long time=myclk  */
#include <stdio.h>
#include <sys/types.h>
#include <time.h> 

static char *Months[ ] ={ "JAN","FEB","MAR","APR","MAY","JUN","JUL","AUG","SEP","OCT","NOV","DEC" };

char *mytime(void)
{ 
  FILE *fp;
  struct tm *timeh_v,*timeh_l;  /* to get the adress of struct tm which in time.h */
  long myclk;
  int rc = 0;
  char mytime[128];
  extern struct tm *localtime();

	  myclk = time(NULL);  /* long time by time() */
	/* char * c_tm = ctime(&myclk); */
          timeh_l  = localtime(&myclk);

	  sprintf(mytime,"%d%s%.2d_%.2d:%.2d:%.2d", (timeh_l->tm_year+1900) ,Months[timeh_l->tm_mon],timeh_l->tm_mday,timeh_l->tm_hour,timeh_l->tm_min,timeh_l->tm_sec); 
          return mytime;
}
