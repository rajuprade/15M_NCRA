// Simple FTP client

#include <stdio.h>
#include <sys/types.h>
#include <dirent.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>  // Primitive System Data Types 
#include <arpa/inet.h>
#include <errno.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <ctype.h>
#include <signal.h>
#include <sys/wait.h>
#include <sys/resource.h>
#include <sys/time.h>
#include <netdb.h> 
#include <pthread.h>    // POSIX Threads 
#include<semaphore.h> 


void service(int); // prototype for thread routine
// Global Data//
static pid_t  current_pid;
static int current_fd = 0;

// The Thread Task for All Clients

void service(int connected) 
{
    int flag=1;
    int length,i,lengthM;
    char recv_data[1024]; 
    int bytes_recieved;
    char MasterBuffer[5000];  
//   char send_data []="<RESPONSES><RESPONSE><CODE>10</CODE><EVENT>10</EVENT><MESSAGE>SUCCESS</MESSAGE></RESPONSE></RESPONSES><RESP_END>"; 
    // This is Sample Responce but Wrapper can send other responces acording to its Alorithm

	printf("\n\n Current Task no %d\n\n",connected); // Shows how many connections are Created

    while(1)
    {
                               
                     bytes_recieved = recv(connected,recv_data,1024,0); //save the data sent by client
                     fflush(stdout);
                     recv_data[bytes_recieved] = '\0';
                     fflush(stdout);
                     length=strlen(recv_data);

		   for(i=0;i<length;i++)

		   {
		        printf("%c",recv_data[i]);

		    } printf("\n");

                     strcat(MasterBuffer, recv_data);
                     //Continue till the Client send <REQ_END> 
                     if( recv_data[length-1]=='>' && recv_data[length-2]=='D'&& recv_data[length-3]=='N'&& recv_data[length-4]=='E' && recv_data[length-5]=='_' && recv_data[length-6]=='Q'&& recv_data[length-7]=='E'&& recv_data[length-8]=='R' && recv_data[length-9]=='<')

                     {
                       printf("\n\nCOMPLETE COMMAND IS RECEIVED BY WRAPPER..\n");
                       flag=0;
                     }
     }
}


int main(int argc, char **argv) {
  int      sockfd;
  struct   sockaddr_in servaddr;
  struct   hostent *host;

  if (argc != 3) {
    printf("usage : client hostname port\n");
    exit(1);
  }
  sockfd = socket(AF_INET, SOCK_STREAM, 0);
  memset(&servaddr,0,sizeof(servaddr));
  servaddr.sin_family = AF_INET;
  servaddr.sin_port = htons(atoi(argv[2]));
  if ((host = gethostbyname(argv[1])) == (NULL)) {
    printf("Unknown host : %s\n", argv[1]);
    exit(1);
  }
  memcpy(&servaddr.sin_addr,host->h_addr,host->h_length);
  
  if (connect(sockfd, (struct sockaddr *) &servaddr, sizeof(servaddr)) < 0) {
    printf("Unable to connect with the server.\n");
    exit(1);
  }
  printf("Connected to %s\n", argv[1]);

  service(sockfd);

}


