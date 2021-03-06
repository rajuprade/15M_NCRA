#include <unistd.h>     /* Symbolic Constants */
#include <sys/types.h>  /* Primitive System Data Types */
#include <errno.h>      /* Errors */
#include <stdio.h>      /* Input/Output */
#include <stdlib.h>     /* General Utilities */
#include <string.h>     /* String handling */
#include <unistd.h>
#include <errno.h>

typedef unsigned char BYTE;

char *get_timestamp(char *ptr)
{
  BYTE ix,iy,iz,x;
  static char str1[512],str2[100];
  char *str,*strx;
  str = str1;
  strx = str2;
  
  ix=0;
  iy=0;
  iz=0;
  x=0;
  strcpy(str,ptr);
  
  do
  {
    ix++;
  }while(!((str[ix]=='>') && (str[ix-1]=='P'||str[ix-1]=='p')&& (str[ix-2]=='M'||str[ix-2]=='m')&& (str[ix-3]=='A'||str[ix-3]=='a')&& (str[ix-4]=='T'||str[ix-4]=='t')&& (str[ix-5]=='S'||str[ix-5]=='s')&& (str[ix-6]=='E'||str[ix-6]=='e')&& (str[ix-7]=='M'||str[ix-7]=='m')&& (str[ix-8]=='I'||str[ix-8]=='i')&& (str[ix-9]=='T'||str[ix-9]=='t')&& (str[ix-10]=='<')));
  
  ix++;
  
  do
  {
    iy++;
  }while(!((str[iy]=='<') && (str[iy+1]=='/') && (str[iy+2]=='T'||str[iy+2]=='t')&& (str[iy+3]=='I'||str[iy+3]=='i')&& (str[iy+4]=='M'||str[iy+4]=='m')&& (str[iy+5]=='E'||str[iy+5]=='e')&& (str[iy+6]=='S'||str[iy+6]=='s') && (str[iy+7]=='T'||str[iy+7]=='t') && (str[iy+8]=='A'||str[iy+8]=='a') && (str[iy+9]=='M'||str[iy+9]=='m') && (str[iy+10]=='P'||str[iy+10]=='p') && (str[iy+11]=='>')));
  
  for(iz=ix;iz<iy;iz++)
    str2[x++]=str1[iz];
  
  str2[x]='\0';
  return strx;
}

char *get_cmdseq(char *ptr)
{
  BYTE ix,iy,iz,x;
  static char str1[512],str2[100];
  char *str,*strx;
  str = str1;
  strx = str2;
  
  ix=0;
  iy=0;
  iz=0;
  x=0;
  strcpy(str,ptr);
  
  do
  {
    ix++;
  }while(!((str[ix]=='>') && (str[ix-1]=='Q'||str[ix-1]=='q')&& (str[ix-2]=='E'||str[ix-2]=='e')&& (str[ix-3]=='S'||str[ix-3]=='s')&& (str[ix-4]=='<')));
  
  ix++;
  
  do
  {
    iy++;
  }while(!((str[iy]=='<') && (str[iy+1]=='/') && (str[iy+2]=='S'||str[iy+2]=='s')&& (str[iy+3]=='E'||str[iy+3]=='e')&& (str[iy+4]=='Q'||str[iy+4]=='q')&& (str[iy+5]=='>')));
  
  for(iz=ix;iz<iy;iz++)
    str2[x++]=str1[iz];
  
  str2[x]='\0';
  return strx;
}

char  *get_cmdid(char *ptr)
{
  BYTE ix,iy,iz,x;
  static char str1[512],str2[100];
  char *str,*strx;
  str = str1;
  strx = str2;
  
  ix=0;
  iy=0;
  iz=0;
  x=0;
  strcpy(str,ptr);
  
  do
  {
    ix++;
  }while(!((str[ix]=='>') && (str[ix-1]=='D'||str[ix-1]=='d')&& (str[ix-2]=='I'||str[ix-2]=='i')&& (str[ix-3]=='<')));
  
  ix++;
  
  do
  {
    iy++;
  }while(!((str[iy]=='<') && (str[iy+1]=='/') && (str[iy+2]=='I'||str[iy+2]=='i')&& (str[iy+3]=='D'||str[iy+3]=='d')&& (str[iy+4]=='>')));
  
  for(iz=ix;iz<iy;iz++)
    str2[x++]=str1[iz];
  
  str2[x]='\0';
  return strx;
}

char *get_sysid(char *ptr)
{
  BYTE ix,iy,iz,x;
  static char str1[512],str2[100];
  char *str,*strx;
  str = str1;
  strx = str2;
  
  ix=0;
  iy=0;
  iz=0;
  x=0;
  strcpy(str,ptr);
  
  do
  {
    ix++;
  }while(!((str[ix]=='>') && (str[ix-1]=='D'||str[ix-1]=='d')&& (str[ix-2]=='I'||str[ix-2]=='i')&& (str[ix-3]=='M'||str[ix-3]=='m')&&  (str[ix-4]=='E'||str[ix-4]=='e')&&  (str[ix-5]=='T'||str[ix-5]=='t')&&  (str[ix-6]=='S'||str[ix-6]=='s')&&  (str[ix-7]=='Y'||str[ix-7]=='y')&&  (str[ix-8]=='S'||str[ix-8]=='s')&&  (str[ix-9]=='<')));
  
  ix++;
  
  do
  {
    iy++;
  }while(!((str[iy]=='<') && (str[iy+1]=='/') && (str[iy+2]=='S'||str[iy+2]=='s')&& (str[iy+3]=='Y'||str[iy+3]=='y') && (str[iy+4]=='S'||str[iy+4]=='s')&& (str[iy+5]=='T'||str[iy+5]=='t') && (str[iy+6]=='E'||str[iy+6]=='e')&& (str[iy+7]=='M'||str[iy+7]=='m') && (str[iy+8]=='I'||str[iy+8]=='i')&& (str[iy+9]=='D'||str[iy+9]=='d') && (str[iy+10]=='>')));
  
  for(iz=ix;iz<iy;iz++)
    str2[x++]=str1[iz];
  
  str2[x]='\0';
  return strx;
}

char *get_ver(char *ptr)
{
  BYTE ix,iy,iz,x;
  static char str1[512],str2[100];
  char *str,*strx;
  str = str1;
  strx = str2;
  
  ix=0;
  iy=0;
  iz=0;
  x=0;
  strcpy(str,ptr);
  
  do
  {
    ix++;
  }while(!((str[ix]=='>') && (str[ix-1]=='N'||str[ix-1]=='n')&& (str[ix-2]=='O'||str[ix-2]=='o')&& (str[ix-3]=='I'||str[ix-3]=='i')&&  (str[ix-4]=='S'||str[ix-4]=='s')&&  (str[ix-5]=='R'||str[ix-5]=='r')&&  (str[ix-6]=='E'||str[ix-6]=='e')&&  (str[ix-7]=='V'||str[ix-7]=='v')&& (str[ix-8]=='<')));
  
  ix++;
  
  do
  {
    iy++;
  }while(!((str[iy]=='<') && (str[iy+1]=='/') && (str[iy+2]=='V'||str[iy+2]=='v')&& (str[iy+3]=='E'||str[iy+3]=='e') && (str[iy+4]=='R'||str[iy+4]=='r')&& (str[iy+5]=='S'||str[iy+5]=='s') && (str[iy+6]=='I'||str[iy+6]=='i')&& (str[iy+7]=='O'||str[iy+7]=='o') && (str[iy+8]=='N'||str[iy+8]=='n')&& (str[iy+9]=='>')));
  
  for(iz=ix;iz<iy;iz++)
    str2[x++]=str1[iz];
  
  str2[x]='\0';
  return strx;
}

BYTE param_cnt(char *ptr)
{
  int count,ix;
  char str1[512];
  char *str;
  
  str = str1;
  strcpy(str,ptr);
  count=0;
  
  for (ix=0;ix<strlen(str);ix++)
  {
    if((str[ix]=='>') && (str[ix-1]=='M'||str[ix-1]=='m')&& (str[ix-2]=='A'||str[ix-2]=='a')&& (str[ix-3]=='R'||str[ix-3]=='r')&&  (str[ix-4]=='A'||str[ix-4]=='a')&&  (str[ix-5]=='P'||str[ix-5]=='p')&& (str[ix-6]=='<'))
      count++;
  }
  return count;
}

char *get_cmdparam(char *ptr)
{
  static int ix,iy,iz,x;
  static char str1[512],str2[100],str3[100];
  char *str,*strx,*stry;
  str = str1;
  strx = str2;
  stry = str3;
  int y;
  ix=0;  iy=0;  iz=0;
  x=0;   y=0;
  
  strcpy(str,ptr);
  
  for(y=0;y<param_cnt(str1);y++)
  {
    do
    {
      ix++;
    }while(!((str[ix]=='>') && (str[ix-1]=='E'||str[ix-1]=='e')&& (str[ix-2]=='U'||str[ix-2]=='u')&& (str[ix-3]=='L'||str[ix-3]=='l')&&  (str[ix-4]=='A'||str[ix-4]=='a')&&  (str[ix-5]=='V'||str[ix-5]=='v')&& (str[ix-6]=='<')));
    
    ix++;
    
    do
    {
      iy++;
    }while(!((str[iy]=='<') && (str[iy+1]=='/') && (str[iy+2]=='V'||str[iy+2]=='v')&& (str[iy+3]=='A'||str[iy+3]=='a') && (str[iy+4]=='L'||str[iy+4]=='l')&& (str[iy+5]=='U'||str[iy+5]=='u') && (str[iy+6]=='E'||str[iy+6]=='e')&& (str[iy+7]=='>')));
    
    
    
    for(iz=ix;iz<iy;iz++)
      str2[x++]=str1[iz];
    str2[x] = '\0';
    strcat(strx," ");
    strcat(stry,strx);
    iy = iy+8;
    ix=iy;
    x=0;
    
  }
  return stry;
}


void main(void)
{
  char  strx[] =("<COMMANDS>  <TIMESTAMP>12345678901234567890</TIMESTAMP>  <COMMAND>  <SEQ>1</SEQ>  <ID>80</ID>  <NAME>POSITION</NAME>  <SYSTEMID>007</SYSTEMID> <version>1.0</version> <DATA> <PARAM>  <NAME>AX</NAME>  <VALUE>A</VALUE>  </PARAM>  <PARAM>  <NAME>ANG1</NAME>  <VALUE>10</VALUE>  </PARAM>  </DATA>  </COMMAND>  </COMMANDS>  <REQ_END>");
  char *temp;
  puts(strx);
  temp= get_timestamp(strx);
  printf("TimeStamp:%s\t",temp);
  temp= get_cmdseq(strx);
  printf("CMD SEQ:%s\t",temp);
  temp= get_sysid(strx);
  printf("SYS ID:%s\t",temp);
  temp= get_cmdid(strx);
  printf("CMD ID:%s\t",temp);
  temp= get_ver(strx);
  printf("VERSION:%s\t",temp);
  temp= get_cmdparam(strx);
  printf("CMD PARAM:%s\n",temp);
}