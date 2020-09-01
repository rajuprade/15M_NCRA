/* A simple server in the internet domain using TCP
   This version runs forever, forking off a separate
   process for each connection
*/

/* It's working fine...It gets connected to the Client1.c on port 5123.....

It send whatever it receive on STDIN ...to the client and get the ACK from client.

*/
#include <stdio.h>
#include<string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include "header.h"
#define PORT 5123

typedef struct _msg
{
  int length;
  unsigned char Msg[100];
} MSG ;

int dostuff(int); /* function prototype */
void error(char *msg)
{
    perror(msg);
    exit(1);
}

int main(int argc, char *argv[])
{
    int sockfd, newsockfd,clilen, pid,true =1;
    struct sockaddr_in serv_addr, cli_addr;

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) 
     {
       error("ERROR opening socket");
       exit(1);
     }
     else 
     {
       fprintf(stderr, " Sockfd : %d \n", sockfd);

       bzero((char *) &serv_addr, sizeof(serv_addr));
       serv_addr.sin_family = AF_INET;
       serv_addr.sin_addr.s_addr = INADDR_ANY;
       serv_addr.sin_port = htons(PORT);

     if (setsockopt(sockfd,SOL_SOCKET,SO_REUSEADDR,&true,sizeof(int)) == -1) {
            perror("Setsockopt");
            exit(1);
        }
     if (bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) 
      {
       error("ERROR on binding");
      } 
      else 
      {
          listen(sockfd,5);
          clilen = sizeof(cli_addr);

          fprintf(stderr, " Waiting for Client ....\n");

          while (1)
           {
              newsockfd = accept(sockfd, (struct sockaddr *) &cli_addr, &clilen);
                 if (newsockfd < 0) 
                 {
                   error("ERROR on accept");
                   exit(1);
                 } 
                 else 
                 {
       
                    fprintf(stderr, " Client Accepted successfully...\n");
                    pid = fork();
                    if (pid < 0) 
                      {
                         error("ERROR on fork");
                      }
                     else if (pid == 0)  
                      {
                           for(;;)
                           {
                               dostuff(newsockfd);
                                //  close(newsockfd);
                               //exit(0);
                           }
                       } 
                          
                  }
           }

      }
   } 
     return 0; /* we never get here */
}

/******** DOSTUFF() *********************
 There is a separate instance of this function
 for each connection.  It handles all communication
 once a connnection has been established.
 *****************************************/
int dostuff (int sock)
{
   int n,len;
   MSG *buffer;

   buffer = (MSG * ) malloc ( sizeof( MSG ));
   if ( buffer == NULL)
            exit(1);

 char  strx[] =("<COMMANDS>  <TIMESTAMP>12345678901234567890</TIMESTAMP>  <COMMAND>  <SEQ>1</SEQ>  <ID>80</ID>  <NAME>POSITION</NAME>  <SYSTEMID>007</SYSTEMID> <version>1.0</version> <DATA> <PARAM>  <NAME>AX</NAME>  <VALUE>IF MON</VALUE>  </PARAM>  <PARAM>  <NAME>ANG1</NAME>  <VALUE>10</VALUE>  </PARAM>  </DATA>  </COMMAND>  </COMMANDS>  <REQ_END>");
  char  *temp;
  temp = (char *)malloc(sizeof(char)*5000);
 // puts(strx);
 // temp= get_timestamp(strx);
 // printf("TimeStamp:%s\t",temp);
 // temp= get_cmdseq(strx);
// printf("CMD SEQ:%s\t",temp);
//  temp= get_sysid(strx);
 // printf("SYS ID:%s\t",temp);
 /* temp= get_cmdid(strx);
  printf("CMD ID:%s\t",temp);
  temp= get_ver(strx);
  printf("VERSION:%s\t",temp); */
  temp= get_cmdparam(strx);
  printf("CMD PARAM:%s\n",temp);

 //  buffer->length = 10;
  memset(buffer->Msg,0x00,sizeof(MSG));
 
   strcpy(buffer->Msg ,temp);
 bzero(temp,sizeof(temp)); 
 /*  printf(" Enter the Commands in Capital letter\n");
   buffer->length = sizeof(buffer->Msg);
   memset(buffer->Msg,0x00,sizeof(MSG));
   fgets(buffer->Msg ,buffer->length,stdin); */
    len = strlen(buffer->Msg); 
 
   write(sock,buffer->Msg,len);
   printf("wrote on the socket:%s\n", buffer->Msg);
  
  sleep(1);
    memset(buffer->Msg,0x00,sizeof(MSG));
     n = read(sock,buffer->Msg,25);
      if(n < 0 ) 
       {
          printf("error reading to socket");
          free(buffer);
          close(sock);
          exit(1); 
       } 
     else 
       {
         printf("reading from socket:%s\n",buffer->Msg);
       } 
       return 0;
}

/* ssize_t  writen(int fd, const void *vptr, size_t n)
  {
      size_t nleft;
      ssize_t nwritten;
      const char *ptr;

      ptr = vptr;
      nleft = n;
     while (nleft > 0) {
         if ( (nwritten = write(fd, ptr, nleft)) <= 0) {
             if (nwritten < 0 && errno == EINTR)
                 nwritten = 0;  
             else
                 return (-1);  

      }

          nleft -= nwritten;
          ptr += nwritten;
     }
     return (n);
 } */

