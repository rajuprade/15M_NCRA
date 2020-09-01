#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h> 
#include<stdlib.h>
#include<string.h>
#define PORT 8000
void error(char *msg)
{
    perror(msg);
    exit(0);
}

int main(int argc, char *argv[])
{
    int sockfd, portno, n;
    struct sockaddr_in serv_addr;
    struct hostent *server;

    char buffer[255];
    if (argc < 2) {
       fprintf(stderr,"usage %s hostname port\n", argv[0]);
       exit(0);
    }
   // portno = atoi(argv[2]);
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) 
        error("ERROR opening socket");
    server = gethostbyname(argv[1]);
    if (server == NULL) {
        fprintf(stderr,"ERROR, no such host\n");
        exit(0);
    }
    bzero((char *) &serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    bcopy((char *)server->h_addr, (char *)&serv_addr.sin_addr.s_addr,server->h_length);
         serv_addr.sin_port = htons(PORT);
    if (connect(sockfd,(struct sockaddr *)&serv_addr,sizeof(serv_addr)) < 0) 
         error("ERROR connecting");
       else
              printf(" Connected to the server \n");
     
       for(;;)
      {
                read(sockfd,buffer,1000);
                printf("this is the message from server\n");
                    printf("%s\n",buffer);

                   //  printf("Please enter the message: ");
                     bzero(buffer,255);
                   // fgets(buffer,255,stdin);
                 strcpy(buffer,"ACK");
                   write(sockfd,buffer,strlen(buffer));
                  bzero(buffer,255);
        }
               return 0;
}
