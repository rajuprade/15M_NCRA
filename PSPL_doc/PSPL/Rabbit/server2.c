/* A simple server in the internet domain using TCP
   This version runs forever, forking off a separate
   process for each connection
*/
#include <stdio.h>
#include<string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
 #include <sys/ioctl.h>
#define PORT 5123

typedef struct _msg
{
  int length;
  unsigned char Msg[100];
} MSG ;

int getcmd(int); /* function prototype */

int pull_socket(int );

void error(char *msg)
{
    perror(msg);
    exit(1);
}

int main(int argc, char *argv[])
{
    int sockfd, newsockfd,clilen, pid;
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
                               getcmd(newsockfd);
                               sleep(1); 
                               pull_socket(newsockfd);
                               //exit(0);
                            }
                       } 
                          
                  }
           }

      }
   } 
     return 0; /* we never get here */
}

/******** getcmd*********************
 There is a separate instance of this function
 for each connection.  It get commands from user and send it on socket 
****************************************/
int getcmd (int sock)
{
   int n,len;
   MSG *buffer;

   buffer = (MSG * ) malloc ( sizeof( MSG ));
   if ( buffer == NULL)
            exit(1);

 //  buffer->length = 10;
 //  strcpy(buffer->Msg ,"Hi I m the TELESET program \n");

 printf(" Enter the Commands in Capital letter\n");
  buffer->length = sizeof(buffer->Msg);
  memset(buffer->Msg,0x00,sizeof(MSG));
  fgets(buffer->Msg ,buffer->length,stdin);
  len = strlen(buffer->Msg);
 
   n = write(sock,buffer->Msg,len);
   if(n < 0 )
     {
          printf("error writing to socket");
          free(buffer);
          close(sock);
          exit(1);

     }
       return 0;
}

int pull_socket(int sock)
{
     int n;
     MSG *buffer;
    int  check=0, bytes;
   buffer = (MSG * ) malloc ( sizeof( MSG ));
   if ( buffer == NULL)
            exit(1);

     memset(buffer->Msg,0x00,sizeof(MSG));

    ioctl(sock, FIONREAD, &bytes);

    if (bytes > 2) 
    {
         //  while(buff!= NULL){ 
        check = read(sock, buffer->Msg,buffer->length);
          if (!check)
           return 0;
           else
             {
                   printf("reading from socket:%s\n",buffer->Msg);
             } 
       }     
  return 0;

         }
