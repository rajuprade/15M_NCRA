/*
	CONVERT A  STRING OF LENGTH LEN TO LOWER CASE LETTERS

*/

#include <ctype.h>

void tolower_(str,len)
char *str;
int *len;
{
   int i;
   for(i=0;i<*len;i++)
   {
     if(isupper(*str)) *str+=32;
     str++;
   }
}
