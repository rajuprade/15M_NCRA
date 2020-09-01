#include <stdio.h>
#include <string.h>
#include <netdb.h>
#include <sys/socket.h>
#include <unistd.h>
#include<stdlib.h>

#define buflen 512
unsigned int portno = 5055;
char hostname[] = "192.168.30.6";

char *buf[buflen];     /* declare global to avoid stack */

void dia(char *sz) { printf("Dia %s\n", sz); }

int printFromSocket(int sd, char *buf)
  {
  int len = buflen+1;
  int continueflag=1;
  while((len >= buflen)&&(continueflag)) /* quit b4 U read an empty socket */
    {
    len = read(sd, buf, buflen);
    write(1,buf,len);
    buf[buflen-1]='\0';  /* Note bug if "Finished" ends the buffer */
    continueflag=(strstr(buf, "Finished")==NULL); /* terminate if server says "Finished" */ 
    }     
  return(continueflag);
  }


main() 
   {
   int sd = socket(AF_INET, SOCK_STREAM, 0);  /* init socket descriptor */
   struct sockaddr_in sin;
   struct hostent *host = gethostbyname(hostname);
   char buf[buflen];
   int len;

   /*** PLACE DATA IN sockaddr_in struct ***/
   memcpy(&sin.sin_addr.s_addr, host->h_addr, host->h_length);
   sin.sin_family = AF_INET;
   sin.sin_port = htons(portno);

   /*** CONNECT SOCKET TO THE SERVICE DESCRIBED BY sockaddr_in struct ***/
   if (connect(sd, (struct sockaddr *)&sin, sizeof(sin)) < 0)
     {
     perror("connecting");
     exit(1);
     }

   sleep(1);   /* give server time to reply */
   while(1)
     {
     printf("\n\n");
     if(!printFromSocket(sd, buf)) break;
     fgets(buf, buflen, stdin);   /* remember, fgets appends the newline */
     write(sd, buf, strlen(buf));
     sleep(1);               /* give server time to reply */
     }
   close(sd);
   }
