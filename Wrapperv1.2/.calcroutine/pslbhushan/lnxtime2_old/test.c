#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char **argv){
 double d = 5.830509;
// char str[50];
   char str[sizeof(d)];
 sprintf(str,"%g",d);
 printf("val  %s",str);
// printf(" Given %s \n", str);
}
