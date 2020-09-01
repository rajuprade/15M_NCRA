#include <unistd.h>     /* Symbolic Constants */
#include <sys/types.h>  /* Primitive System Data Types */
#include <errno.h>      /* Errors */
#include <stdio.h>      /* Input/Output */
#include <stdlib.h>     /* General Utilities */
#include <string.h>     /* String handling */
#include <unistd.h>
#include <errno.h>
#include "xmlParse.h"
#include "handleQue.h"

int ix,iy,iz,x,y;
char *strx, *stry, *strz;
char str1[5120], str2[5120], str3[5120];

/*
  strx=(char *)malloc(sizeof(char)*5000);
  stry=(char *)malloc(sizeof(char)*5000);
  strz=(char *)malloc(sizeof(char)*5000);
*/
char *get_timestamp(char *ptr)
{
  strx = str1;
  stry = str2;
  ix=0;   iy=0;   iz=0;   x=0;

  strncpy(strx,ptr,strlen(ptr));
  
  do
  {
    ix++;
  }while(!((strx[ix]=='>') && (strx[ix-1]=='P'||strx[ix-1]=='p')&& (strx[ix-2]=='M'||strx[ix-2]=='m')&& (strx[ix-3]=='A'||strx[ix-3]=='a')&& (strx[ix-4]=='T'||strx[ix-4]=='t')&& (strx[ix-5]=='S'||strx[ix-5]=='s')&& (strx[ix-6]=='E'||strx[ix-6]=='e')&& (strx[ix-7]=='M'||strx[ix-7]=='m')&& (strx[ix-8]=='I'||strx[ix-8]=='i')&& (strx[ix-9]=='T'||strx[ix-9]=='t')&& (strx[ix-10]=='<')));
  
  ix++;
  
  do
  {
    iy++;
  }while(!((strx[iy]=='<') && (strx[iy+1]=='/') && (strx[iy+2]=='T'||strx[iy+2]=='t')&& (strx[iy+3]=='I'||strx[iy+3]=='i')&& (strx[iy+4]=='M'||strx[iy+4]=='m')&& (strx[iy+5]=='E'||strx[iy+5]=='e')&& (strx[iy+6]=='S'||strx[iy+6]=='s') && (strx[iy+7]=='T'||strx[iy+7]=='t') && (strx[iy+8]=='A'||strx[iy+8]=='a') && (strx[iy+9]=='M'||strx[iy+9]=='m') && (strx[iy+10]=='P'||strx[iy+10]=='p') && (strx[iy+11]=='>')));
  
  for(iz=ix;iz<iy;iz++)
    str2[x++]=str1[iz];
  
  str2[x]='\0';
  return stry;
}

char *get_cmdseq(char *ptr)
{
  strx = str1;
  stry = str2;
  
  ix=0;  iy=0;  iz=0;  x=0;
  
  strncpy(strx,ptr,strlen(ptr));
  
  do
  {
    ix++;
  }while(!((strx[ix]=='>') && (strx[ix-1]=='Q'||strx[ix-1]=='q')&& (strx[ix-2]=='E'||strx[ix-2]=='e')&& (strx[ix-3]=='S'||strx[ix-3]=='s')&& (strx[ix-4]=='<')));
  
  ix++;
  
  do
  {
    iy++;
  }while(!((strx[iy]=='<') && (strx[iy+1]=='/') && (strx[iy+2]=='S'||strx[iy+2]=='s')&& (strx[iy+3]=='E'||strx[iy+3]=='e')&& (strx[iy+4]=='Q'||strx[iy+4]=='q')&& (strx[iy+5]=='>')));
  
  for(iz=ix;iz<iy;iz++)
    str2[x++]=str1[iz];
  
  str2[x]='\0';
  return stry;
}

char *get_cmdid(char *ptr)
{
  strx = str1;
  stry = str2;
  
  ix=0;  iy=0;  iz=0;  x=0;
 
  strncpy(strx,ptr,strlen(ptr));
  
  
  do
  {
    ix++;
  }while(!((strx[ix]=='>') && (strx[ix-1]=='D'||strx[ix-1]=='d')&& (strx[ix-2]=='I'||strx[ix-2]=='i')&& (strx[ix-3]=='<')));
  
  ix++;
  
  do
  {
    iy++;
  }while(!((strx[iy]=='<') && (strx[iy+1]=='/') && (strx[iy+2]=='I'||strx[iy+2]=='i')&& (strx[iy+3]=='D'||strx[iy+3]=='d')&& (strx[iy+4]=='>')));
  
  for(iz=ix;iz<iy;iz++)
    str2[x++]=str1[iz];
  
  str2[x]='\0';
 
  return stry;
}

char *get_sysid(char *ptr)
{
  strx = str1;
  stry = str2;
  
  ix=0;  iy=0;  iz=0;  x=0;
  strncpy(strx,ptr,strlen(ptr));
  
  do
  {
    ix++;
  }while(!((strx[ix]=='>') && (strx[ix-1]=='D'||strx[ix-1]=='d')&& (strx[ix-2]=='I'||strx[ix-2]=='i')&& (strx[ix-3]=='M'||strx[ix-3]=='m')&&  (strx[ix-4]=='E'||strx[ix-4]=='e')&&  (strx[ix-5]=='T'||strx[ix-5]=='t')&&  (strx[ix-6]=='S'||strx[ix-6]=='s')&&  (strx[ix-7]=='Y'||strx[ix-7]=='y')&&  (strx[ix-8]=='S'||strx[ix-8]=='s')&&  (strx[ix-9]=='<')));
  
  ix++;
  
  do
  {
    iy++;
  }while(!((strx[iy]=='<') && (strx[iy+1]=='/') && (strx[iy+2]=='S'||strx[iy+2]=='s')&& (strx[iy+3]=='Y'||strx[iy+3]=='y') && (strx[iy+4]=='S'||strx[iy+4]=='s')&& (strx[iy+5]=='T'||strx[iy+5]=='t') && (strx[iy+6]=='E'||strx[iy+6]=='e')&& (strx[iy+7]=='M'||strx[iy+7]=='m') && (strx[iy+8]=='I'||strx[iy+8]=='i')&& (strx[iy+9]=='D'||strx[iy+9]=='d') && (strx[iy+10]=='>')));
  
  for(iz=ix;iz<iy;iz++)
    str2[x++]=str1[iz];
  
  str2[x]='\0';
  return stry;
}

char *get_ver(char *ptr)
{

  strx = str1;
  stry = str2;
  
  ix=0;  iy=0;  iz=0;  x=0;
  
  strncpy(strx,ptr,strlen(ptr));
  
  do
  {
    ix++;
  }while(!((strx[ix]=='>') && (strx[ix-1]=='N'||strx[ix-1]=='n')&& (strx[ix-2]=='O'||strx[ix-2]=='o')&& (strx[ix-3]=='I'||strx[ix-3]=='i')&&  (strx[ix-4]=='S'||strx[ix-4]=='s')&&  (strx[ix-5]=='R'||strx[ix-5]=='r')&&  (strx[ix-6]=='E'||strx[ix-6]=='e')&&  (strx[ix-7]=='V'||strx[ix-7]=='v')&& (strx[ix-8]=='<')));
  
  ix++;
  
  do
  {
    iy++;
  }while(!((strx[iy]=='<') && (strx[iy+1]=='/') && (strx[iy+2]=='V'||strx[iy+2]=='v')&& (strx[iy+3]=='E'||strx[iy+3]=='e') && (strx[iy+4]=='R'||strx[iy+4]=='r')&& (strx[iy+5]=='S'||strx[iy+5]=='s') && (strx[iy+6]=='I'||strx[iy+6]=='i')&& (strx[iy+7]=='O'||strx[iy+7]=='o') && (strx[iy+8]=='N'||strx[iy+8]=='n')&& (strx[iy+9]=='>')));
  
  for(iz=ix;iz<iy;iz++)
    str2[x++]=str1[iz];
  
  str2[x]='\0';
  return stry;
}

unsigned char param_cnt(char *ptr)
{
  int count,ix;
  // char str1[512];
  char *str;
  
  str = str1;
  strcpy(str,ptr); str[strlen(str)-1]='\0';
  fprintf(stderr, " =========== PARAM_CNT %s ",str);
 /* strncpy(str,ptr, strlen(ptr)); */

  count=0;
  for (ix=0;ix<strlen(str);ix++)
  {
    if((str[ix]=='>') && (str[ix-1]=='M'||str[ix-1]=='m')&& (str[ix-2]=='A'||str[ix-2]=='a')&& (str[ix-3]=='R'||str[ix-3]=='r')&&  (str[ix-4]=='A'||str[ix-4]=='a')&&  (str[ix-5]=='P'||str[ix-5]=='p')&& (str[ix-6]=='<')) count++; 
  }
 
  return count;
}

int  get_cmdparam(char *ptr, char *out)
{ int count;
  
  char *fldsep;

  if( ( fldsep = ( char * ) getenv("CMD_FLD")) == NULL ) {
         fldsep=",";
   } 
  
  ix=0;  iy=0;  iz=0; x=0;   y=0;
  strx = str1; stry = str2; strz = str3;


  strcpy(strx,ptr);
  strx[strlen(ptr)-1]='\0';
  
/* strncpy(strx,ptr,strlen(ptr)); strx[strlen(strx)]='\0'; */

  count = param_cnt(strx);

  for(y=0;y<count;y++)
  {
    do
    {
      ix++; 
    } while(!((strx[ix]=='>') && (strx[ix-1]=='E'||strx[ix-1]=='e')&& (strx[ix-2]=='U'||strx[ix-2]=='u')&& (strx[ix-3]=='L'||strx[ix-3]=='l')&&  (strx[ix-4]=='A'||strx[ix-4]=='a')&&  (strx[ix-5]=='V'||strx[ix-5]=='v')&& (strx[ix-6]=='<')));
    ix++;
    
    do
    {
      iy++; 
    }while(!((strx[iy]=='<') && (strx[iy+1]=='/') && (strx[iy+2]=='V'||strx[iy+2]=='v')&& (strx[iy+3]=='A'||strx[iy+3]=='a') && (strx[iy+4]=='L'||strx[iy+4]=='l')&& (strx[iy+5]=='U'||strx[iy+5]=='u') && (strx[iy+6]=='E'||strx[iy+6]=='e')&& (strx[iy+7]=='>')));
    
    for(iz=ix;iz<iy;iz++) strz[x++]=strx[iz];
    strz[x++]= fldsep[0];
    iy = iy+8; ix=iy;
    
/*
    for(iz=ix;iz<iy;iz++) stry[x++]=strx[iz];
    stry[x] ='\0';
    strcat(stry,",");

    y?strcat(strz,stry):strcpy(strz,stry);
    strz[strlen(strz)]='\0';
    x=0;
*/
  }
  strz[x]='\0';

  strcpy(out,strz);
  return 0;
}

char *get_xmlheader(char *ptr)
{

  strx = str1;
  stry = str2;
  //printf("Entered");
  ix=0;  iy=0;  iz=0;  x=0;
  strncpy(strx,ptr,strlen(ptr));
  
  //printf("Processing");
  do
  {
    ix++;
  }while(!((strx[ix]=='>') && (strx[ix-1]=='D'||strx[ix-1]=='d')&& (strx[ix-2]=='N'||strx[ix-2]=='n')&& (strx[ix-3]=='A'||strx[ix-3]=='a')&& (strx[ix-4]=='M'||strx[ix-4]=='m')&& (strx[ix-5]=='M'||strx[ix-5]=='m')&& (strx[ix-6]=='O'||strx[ix-6]=='o')&& (strx[ix-7]=='C'||strx[ix-7]=='c')&& (strx[ix-8]=='<')));
  
  ix++;
  
  do
  {
    iy++;
  }while(!((strx[iy]=='<') && (strx[iy+1]=='D'||strx[iy+1]=='d')&& (strx[iy+2]=='A'||strx[iy+2]=='a')&& (strx[iy+3]=='T'||strx[iy+3]=='t')&& (strx[iy+4]=='A'||strx[iy+4]=='a')&& (strx[iy+5]=='>')));
  
  for(iz=ix;iz<iy;iz++)
    str2[x++]=str1[iz];
  //printf("done");
  str2[x]='\0';
  return stry;
}
/*-----------------------------------------------------------------------------*/

void parseXmlCmd(char *xmlcmd, char *devCmd)
{

  char  cmdbuf[1024], tmp[1024];
  char *fldsep;

  if( ( fldsep = ( char * ) getenv("CMD_FLD")) == NULL ) {
         fldsep=",";
   } 

  fprintf(stderr, "----------- parseXmlCmd %s \n", xmlcmd);
  sprintf(cmdbuf,"%s%s",get_cmdid(xmlcmd),fldsep);  /* command */
  fprintf(stderr, "----------- get_cmdid  %s\n", cmdbuf);

  get_cmdparam(xmlcmd, tmp);
  fprintf(stderr, "----------- get_cmdparm   %s \n", tmp);
  strcat(cmdbuf,tmp);
  fprintf(stderr, "----------- cmdbuf   %s \n", cmdbuf);

  strcpy(devCmd, cmdbuf);
  devCmd[strlen(devCmd)]='\0';
  fprintf(stderr, "----------- devCmd   %s \n", devCmd);
}

int formXmlResp(char *buff, char *xmlCmdBuf, char *devResp)
{
 char buffer[4096];
 char exbuffer[4096];
 char finalbuffer[1024], ACKdata[1024];
 char xmlFinalResp[4096];
 char resp1[]=(" <responses><response>");
 char resp2[]=("</response></responses><RESP_END>");
 char ID[128];
 char *respbuffer;
 char *ACK;

 char byte; int i=0; int j=0; int commandflag=0;

 sprintf(ACKdata,"<event>%x</event><code>10</code><data></data><message></message>",buff[0]);
 strcpy(buffer,xmlCmdBuf);
 
  fprintf(stderr, " Buffer [%d] Extracted %s \n", xmlQ.retrieve, xmlQ.buffer[xmlQ.retrieve]);

 /* Get exbuffer */
  for(i=0;i<strlen(buffer);i++) {
      if( buffer[i]=='<' && (buffer[i+1]=='C'||buffer[i+1]=='c')&& (buffer[i+2]=='O'||buffer[i+2]=='o')&& (buffer[i+3]=='M'||buffer[i+3]=='m' )&& (buffer[i+4]=='M'||buffer[i+4]=='m') && (buffer[i+5]=='A'||buffer[i+5]=='a') && (buffer[i+6]=='N'||buffer[i+6]=='n' )&& (buffer[i+7]=='D'||buffer[i+7]=='d')&& buffer[i+8]=='>')
      { i=i+9; commandflag=1; } 

      if(commandflag) { exbuffer[j]=buffer[i]; j++; }
 }
  exbuffer[j]='\0';
  fprintf(stderr,"\nThe extracted data\n\t\tPutting Extracted data\n");
  fprintf(stderr, "%s \n",exbuffer);

/* Get Final Buffer */
  j=0;
  for(i=0;i<strlen(exbuffer);i++)  {
     if((exbuffer[i]=='<' && (exbuffer[i+1]=='D'||exbuffer[i+1]=='d')&& (exbuffer[i+2]=='A'||exbuffer[i+2]=='a' )&& (exbuffer[i+3]=='T'||exbuffer[i+3]=='t' )&& (exbuffer[i+4]=='A'||exbuffer[i+4]=='a' )&& exbuffer[i+5]=='>')||(exbuffer[i]=='<' && exbuffer[i+1]=='/' && (exbuffer[i+2]=='C'||exbuffer[i+2]=='c') && (exbuffer[i+3]=='O'||exbuffer[i+3]=='o' )&& (exbuffer[i+4]=='M'||exbuffer[i+4]=='m')&& (exbuffer[i+5]=='M'||exbuffer[i+5]=='m')))
          { break; }
     finalbuffer[j++]=exbuffer[i]; 
  }
  finalbuffer[j]='\0';
  fprintf(stderr, "\n\n Exact data is as below....\t\t the Extracted Data\n");
  fprintf(stderr, "%s\n",finalbuffer);

  /* Get ID */
  j=0;
  for(i=0;i<strlen(finalbuffer);i++) {
        if(finalbuffer[i]=='<' && (finalbuffer[i+1]=='I'||finalbuffer[i+1]=='i')&& (finalbuffer[i+2]=='D'||finalbuffer[i+2]=='d')&& (finalbuffer[i+3]=='>')) {
      i=i+4;
     while(finalbuffer[i]!='<') { ID[j++]=finalbuffer[i++]; }
     break;
    }
  }
  ID[j]='\0';

  bzero(xmlFinalResp,4095);
 sprintf(xmlFinalResp,"%s %s %s %s",resp1,finalbuffer,ACKdata,resp2);
/*devResp = (char *) malloc(strlen(xmlFinalResp) * sizeof(char)); */
 strncpy(devResp,xmlFinalResp, strlen(xmlFinalResp));
 fprintf(stderr, " ------------ formXmlResp %s \n",  devResp);

 return 0;
}

/*
void main(void)
{
  char *buffer;
  char *temp;
  int cnt;
  int len;
  buffer=(char *)malloc(sizeof(char)*5000);
  
  buffer ="<COMMANDS>  <TIMESTAMP>12345678901234567890</TIMESTAMP>  <COMMAND>  <SEQ>1</SEQ>  <ID>80</ID>  <NAME>POSITION</NAME>  <SYSTEMID>007</SYSTEMID> <version>1.0</version> <DATA> <PARAM>  <NAME>AX</NAME>  <VALUE>A</VALUE>  </PARAM>  <PARAM>  <NAME>time</NAME>  <VALUE>1.5</VALUE>  </PARAM> <PARAM>  <NAME>ANG1</NAME>  <VALUE>10</VALUE>  </PARAM>  <PARAM>  <NAME>ANG2</NAME>  <VALUE>20</VALUE>  </PARAM> <PARAM>  <NAME>ANG2</NAME>  <VALUE>0.005</VALUE>  </PARAM> </DATA>  </COMMAND>  </COMMANDS>  <REQ_END>\0";
  //len = strlen(buffer);
  printf("Received Buffer of len %d: ",strlen(buffer));
  //buffer[++len] = '\0';
  puts(buffer);
  printf("\n");
  
  temp= get_timestamp(buffer);
  printf("TimeStamp:%s\n",temp);
  
  temp= get_cmdseq(buffer);
  printf("CMD SEQ:%s\n",temp);
  temp= get_sysid(buffer);
  printf("SYS ID:%s\n",temp);
  temp= get_cmdid(buffer);
  printf("CMD ID:%s\n",temp);
  temp= get_ver(buffer);
  printf("VERSION:%s\n",temp);
  //cnt = param_cnt(buffer);
  //printf("COUNT:%d\n",cnt);
  temp= get_cmdparam(buffer);
  printf("CMD PARAM:%s\n",temp);
 // temp= get_xmlheader(buffer);
 // printf("XML HEADER:%s\n",temp);
  
}*/
