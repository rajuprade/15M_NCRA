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
   int n,len,l;
   
    MSG *tx_buffer,*rx_buffer;

   tx_buffer = (MSG * ) malloc ( sizeof( MSG ));
      if (tx_buffer == NULL)
            exit(1);

      rx_buffer = (MSG *) malloc(sizeof(MSG));
  char  strx[] =("<COMMANDS>  <TIMESTAMP>12345678901234567890</TIMESTAMP>  <COMMAND>  <SEQ>1</SEQ>  <ID>80</ID>  <NAME>POSITION</NAME>  <SYSTEMID>007</SYSTEMID> <version>1.0</version> <DATA> <PARAM>  <NAME>AX</NAME>  <VALUE>IF MON</VALUE>  </PARAM>  <PARAM>  <NAME>ANG1</NAME>  <VALUE></VALUE>  </PARAM>  </DATA>  </COMMAND>  </COMMANDS>  <REQ_END>");
  char  *temp;
  temp = (char *)malloc(sizeof(char)*50);
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
//  printf("CMD PARAM:%s\n",temp);
  l = strlen(temp);
   memset(tx_buffer->Msg,0x00,sizeof(MSG));
 
   // memset(temp,0x00,sizeof(MSG));
   
   strncpy(tx_buffer->Msg ,temp,l);
   //bzero(temp);
   memset(temp,0x00,sizeof(temp));
  // printf("tx_buf->Msg is : %s",tx_buffer->Msg);
   
   len = strlen(tx_buffer->Msg);
  // tx_buffer->Msg[len]= '\0';
   n = write(sock,tx_buffer->Msg,sizeof(MSG));
   if(n < 0 )
     {
          printf("error writing to socket");
          free(tx_buffer);
          close(sock);
          exit(1);

     }
    // memset(tx_buffer->Msg,0x00,sizeof(MSG));
    /*  else 
       {
         printf("\nWRITING ON socket:%s\n",tx_buffer->Msg);
       } */
     sleep(2);
     memset(rx_buffer->Msg,0x00,sizeof(MSG));
     n = read(sock,rx_buffer->Msg,500);
      if(n < 0 ) 
      {
          printf("error reading to socket");
          free(rx_buffer);
          close(sock);
          exit(1); 
       } 
     else 
       {
         printf("reading from socket:%s\n",rx_buffer->Msg);
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

