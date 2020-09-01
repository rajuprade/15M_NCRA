#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "source.h"


 

int  main()
{
  

 int bhu=1;

 char *srcInfo[]= {"3C286","13h28m49.65s", "+30d45'58.6", "1950.0"};
 char *timeInfo[]={"11", "03", "21", "10", "56", "30","-74.05"};

 char *lstdata[5];




 
 
for(bhu=1;bhu<5;bhu++)
{

 printf("\n COUNT= %d",bhu);

 calculateLST(srcInfo,timeInfo,lstdata);


}
 printf("\n\n Called the SLA function successfully..\n\n");
 printf("The Output in C: %s\n\n",lstdata[0]);
 return(0);

}


