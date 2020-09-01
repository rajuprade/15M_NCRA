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
#define PORT 5123

typedef struct _msg
{
  int length;
  unsigned char Msg[2000];
} MSG ;

int dostuff(int); /* function prototype */
void error(char *msg)
{
    perror(msg);
    exit(1);
}

int main(int argc, char *argv[])
{
    int sockfd, newsockfd,clilen;
     int n,i;
    struct sockaddr_in serv_addr, cli_addr;

      MSG *buffer;
      buffer = (MSG * ) malloc ( sizeof( MSG ));
      if ( buffer == NULL)
            exit(1);

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

         
               newsockfd = accept(sockfd, (struct sockaddr *) &cli_addr, &clilen);
                 if (newsockfd < 0) 
                 {
                   error("ERROR on accept");
                   exit(1);
                 } 
                 else 
                 {
       
                     fprintf(stderr, " Client Accepted successfully...\n");
                  }             
           
                for(i=0;i<=10;i++)
                   {
                       printf(" Enter the Commands in Capital letter\n");
                       buffer->length = sizeof(buffer->Msg);
                       fgets(buffer->Msg ,buffer->length,stdin);
 
                         n = write(newsockfd,buffer,sizeof(MSG));
                       if(n < 0 )
                           {
                                      printf("error writing to socket");
                                      
                            }
                         else
                           {
                                     printf("1.wrote:%2d %s\n",buffer->length,buffer->Msg);
                           }
 
                                sleep(1);
                                  n = read(newsockfd,buffer,sizeof(MSG));
                                       if(n < 0 ) 
                                           {
                                                  printf("error reading to socket");
                                                  
                                           } 
                                           else 
                                           {
                                                 printf("1.read:%2d %s\n",buffer->length,buffer->Msg);
                                         }
                                      return 0;
                        
                                   
                  
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
   int n;
   MSG *buffer;

   buffer = (MSG * ) malloc ( sizeof( MSG ));
   if ( buffer == NULL)
            exit(1);

 //  buffer->length = 10;
 //  strcpy(buffer->Msg ,"Hi I m the TELESET program \n");

 printf(" Enter the Commands in Capital letter\n");
  buffer->length = sizeof(buffer->Msg);
   fgets(buffer->Msg ,buffer->length,stdin);
 
   n = write(sock,buffer,sizeof(MSG));
   if(n < 0 )
     {
          printf("error writing to socket");
          free(buffer);
          close(sock);
          exit(1);

     }
    else
       {
         printf("1.wrote:%2d %s\n",buffer->length,buffer->Msg);
       }
 
     sleep(1);
     n = read(sock,buffer,sizeof(MSG));
      if(n < 0 ) 
       {
          printf("error reading to socket");
          free(buffer);
          close(sock);
          exit(1); 
       } 
      else 
       {
         printf("1.read:%2d %s\n",buffer->length,buffer->Msg);
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

