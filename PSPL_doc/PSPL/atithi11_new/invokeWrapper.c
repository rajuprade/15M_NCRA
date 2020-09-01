
#include "invokeWrapper.h"
#include "wrapperCom.h"
#include "servCMS.h"
#include "consumCMS.h"

extern pthread_mutex_t mutex;// mutex
extern pthread_mutex_t fmutex;// mutex for file
extern pthread_mutex_t Rmutex;// mutex for file
extern pid_t  current_pid;

extern pthread_t *thread; // pointer for a Consumer Task
extern pthread_t *Thread; // pointer for the Client tasks


void handle_clients(void);

static int  number_clients = 0;

extern int sockfd;
extern struct sockaddr_in servaddr;
extern struct sockaddr_in clientaddr;
extern int req_port;
extern int initServer();


void sig_child(int signo) {
  pid_t pid;
  int  stat;

 /*  Might need to do it like this to be safe */
   while ((pid = wait3(&stat,WNOHANG,NULL)) > 0) {
      number_clients--;
      fprintf(stderr,"server: client %d terminated.\n", pid);
   }

/*
  pid = wait(&stat);
  number_clients--; */
  // Re-stablish the signal handler

  signal(SIGCHLD,sig_child);
  return;
}

void handle_clients(void)
{
   unsigned int len ;
   char *envptr; int clientfd;

   if( ( envptr = ( char * ) getenv("DEVICE_IP")) != NULL ) {
         strcpy(deviceIP,envptr);
   } else { strcpy(deviceIP,DEVICE_IP); }

/* TODO : Here signal must be set on thread termination clean the thread pointer 
          Check number of clients connected
 */
    while(1) 
    {
       fprintf(stderr, " handle_clients() : number_clients[%d] - Waiting for new Client.\n",number_clients);
       len = sizeof(clientaddr);
       clientfd = accept(sockfd, (struct sockaddr *) &clientaddr, (socklen_t *) &len);

       if (clientfd < 0) {
              if (errno != EINTR) {
                   fprintf(stderr, " \n#### Error : Accept error!\n");
                   fprintf(stderr, "%s\n",strerror(errno));
                   return ;
              }
       } 

       fprintf(stderr, "[%d] Received a connection from Subsystem Client on %s, port %d\n", current_pid,inet_ntoa(clientaddr.sin_addr),ntohs(clientaddr.sin_port));

       if ( !strcmp(inet_ntoa(clientaddr.sin_addr),deviceIP)) {
              thread=(pthread_t *)malloc(sizeof(pthread_t));
              pthread_create (thread, NULL, (void *) &consumer,(void*)&clientfd);// Creates the Consumer Task
              if(pthread_setschedprio(*thread,2));
              {
                 fprintf(stderr,"\n\n priority is lowered...");
              }
       } else {
               Thread=(pthread_t *)malloc(sizeof(pthread_t));
               pthread_create (Thread, NULL, (void *) &service,(void*)&clientfd); // creates new thread when New connection is formed
       }
    }
}

int main(int argc, char **argv)
{
  char *envptr ;
  if( initServer() == ERROR )  {
    fprintf(stderr, " ### ERROR : %s init_server() failed on port %d \n",argv[0], req_port); exit(1); 
  } else { handle_clients(); exit(0); }
}
