/*using the ctime function*/

#include <stdio.h>
#include <time.h>

int main()
{
  char stamp1[26], stamp2[10];
  int i;
  time_t t1;
  time(&t1);
  ctime_r(&t1, stamp1);
  // time_t tm;
   //tm = time(NULL);
// printf(ctime(&tm));
  printf("Time is %s ---",stamp1);
return 0;
}