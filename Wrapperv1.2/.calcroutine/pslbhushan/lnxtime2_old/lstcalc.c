/* calepoch_ routine */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

void getString2(char** data){
  char str[10] = "Trying"; 
  printf("b4 %s\n", data[0]);
//  data[0] = "Bye";
  strcpy(data[0],str); 
  printf("after %s\n", data[0]);
  return;
}

void calclst2(char** argv, char** srcline,char** resultInfo)
{
//char** argv, char** srcline, 
	char str[10] = "Trying";
	printf("Original data %s \n", resultInfo[0]);
//	resultInfo[0] = "Trying";
	strcpy(resultInfo[0],str);
        printf("printing modified data %s \n ", resultInfo[0]); 
//	printf("B4 RT ");
//	return;
}
