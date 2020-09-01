
#include "invokeWrapper.h"
#include "wrapperCom.h"
#include "servCMS.h"
#include "consumCMS.h"


extern pthread_mutex_t mutex;// mutex
extern pid_t  current_pid;

pthread_t *threadWrapper[TOTAL_THREAD];
/*
pthread_t *thread; // pointer for a Consumer Task
pthread_t Thread; // pointer for the Client tasks
pthread_t *thread_timeout; // pointer to send TIMEOUT status on monPORT of the CMS
*/

static jmp_buf set_pt ;  /* typedef int */
static void wrapper_sighandler( int ) ;


static int  number_clients;
int  DeviceComm=TIMEOUT;

extern int sockfd;
extern struct sockaddr_in servaddr;
extern struct sockaddr_in clientaddr;

void handle_clients(void);
extern int req_port;
extern int initServer();
extern void terminateConsumer(int);

 static void wrapper_sighandler(int sys_signal ) {
     longjmp(set_pt, sys_signal);
  }

/*
void sig_child(int signo) {
  pid_t pid;
  int  stat;

 //  Might need to do it like this to be safe //
   while ((pid = wait3(&stat,WNOHANG,NULL)) > 0) {
      number_clients--;
      fprintf(stderr,"server: client %d terminated.\n", pid);
   }


// pid = wait(&stat);
// number_clients--; 
  // Re-stablish the signal handler

  signal(SIGCHLD,sig_child);
  return;
}
 */

void handle_clients(void)
{
   unsigned int len ;
   char *envptr; int clientfd; int cmsfd;
   char cmsIP[32];
   struct timeval tv;
   int cthreadid=-1;
   static int return_from_longjmp_to_setjmp ;
   int rc = 0, ts=0;

   if( ( envptr = ( char * ) getenv("DEVICE_IP")) != NULL ) {
         strcpy(deviceIP,envptr);
   } else { strcpy(deviceIP,DEVICE_IP); }

   if( ( envptr = ( char * ) getenv("CMS_IP")) != NULL ) {
         strcpy(cmsIP,envptr);
   } else { strcpy(cmsIP,CMS_IP); }


   if( ( envptr = ( char * ) getenv("SUBSYS_ID")) != NULL ) {
         strcpy(subSysID,envptr);
   } else { strcpy(subSysID,SUBSYS_ID); }


/* TODO : Here signal must be set on thread termination clean the thread pointer 
          Check number of clients connected
 */
     // This thread continuously check the device connection and if it is Timeout
     // send the message by default per 10 sec.

        threadWrapper[DEVNCONN]=(pthread_t *)realloc( NULL, sizeof(pthread_t)); 
        pthread_create (threadWrapper[DEVNCONN], NULL, (void *) &deviceStatResponse,NULL);


           (void) signal(SIGHUP,wrapper_sighandler); //(void) signal(SIGINT,SIG_IGN);
           (void) signal(SIGQUIT,wrapper_sighandler); (void) signal(SIGILL,wrapper_sighandler);
           (void) signal(SIGTERM,wrapper_sighandler);
           (void) signal(SIGTRAP,wrapper_sighandler); (void) signal(SIGKILL,wrapper_sighandler);
           (void) signal(SIGFPE,wrapper_sighandler);  (void) signal(SIGBUS,wrapper_sighandler);
           (void) signal(SIGSEGV,wrapper_sighandler); (void) signal(SIGPIPE,wrapper_sighandler);


    while(1) 
    {

      if((return_from_longjmp_to_setjmp = setjmp(set_pt)) == 0 )
       {
       fprintf(stderr, " \n\n ########  handle_clients() : number_clients[%d] - Waiting for new Client.\n",number_clients);
       len = sizeof(clientaddr);
       clientfd = accept(sockfd, (struct sockaddr *) &clientaddr, (socklen_t *) &len);
        
       if (clientfd < 0) {
              if (errno != EINTR) {
                   fprintf(stderr, " \n#### Error : Accept error!\n");
                   fprintf(stderr, "%s\n",strerror(errno));
                   continue ;
              }
       }  else {
            int opt=1;

            tv.tv_sec = 5; // seconds //
            tv.tv_usec = 0; 
        //  ioctl(clientfd, FIONBIO, &opt);
              

             if( setsockopt(clientfd, SOL_SOCKET, SO_KEEPALIVE, &opt, sizeof(opt)) == ERROR)
             { perror("setsockopt_SO_KEEPALIVE"); }

             if(setsockopt(clientfd, SOL_SOCKET, SO_SNDTIMEO, &tv, sizeof(tv)) < 0)
	     {  fprintf(stderr,"Cannot Set SO_SNDTIMEO for socket\n"); }
/*
	     if(setsockopt(clientfd, SOL_SOCKET, SO_RCVTIMEO, &tv, sizeof(tv)) < 0) 
	     {  fprintf(stderr,"Cannot Set SO_RCVTIMEO for socket\n"); }
*/
  
       fprintf(stderr, "[%d] Received a connection from Subsystem Client on %s, port %d\n", current_pid,inet_ntoa(clientaddr.sin_addr),ntohs(clientaddr.sin_port));

       if ( !strcmp(inet_ntoa(clientaddr.sin_addr),deviceIP)) {

            if(DeviceComm) { // DeviceComm is already in RESET or APPLN Mode
                    terminateConsumer(TIMEOUT);
/* Avoiding cancel as it doesn't free the memory 20 oct 2011 */
                 if( ! (cthreadid=pthread_cancel(threadWrapper[THRD_CONSUM])) ) {
                     
                     fprintf(stderr, " ### INFO : invokerWrapper:Consumer() thread Cancelled Successfully.\n");
                     DeviceComm=TIMEOUT;
                 }

             }  

             if(!DeviceComm) {
                  DeviceComm=RESET;  // so_block(clientfd,1);
                  fprintf(stderr, " ###### invokeWrapper:Consumer() : DeviceComm %d %s - %s\n",
                          DeviceComm, deviceIP, inet_ntoa(clientaddr.sin_addr));
          /*       thread=(pthread_t *)malloc(sizeof(pthread_t)); */
               if ( (threadWrapper[THRD_CONSUM]=(pthread_t *)realloc(NULL, sizeof(pthread_t))) == NULL )
               { perror("servCMS:handle_client(): ");
                 fprintf(stderr, "### ERROR : servCMS: threadWrapper[%d] realloc() Error\n, THRD_CONSUM") ;
               }else {
                   bzero(threadWrapper[THRD_CONSUM], sizeof(pthread_t));
                   ts= pthread_create (&threadWrapper[THRD_CONSUM], NULL, (void *) &consumer,(void*)&clientfd);// Creates the Consumer Task
                   if(ts) {
                      fprintf(stderr,"### ERROR invokeWrapper:  consumer: return code from pthread_create is %d \n", ts);
                   } else {
                      fprintf(stderr,"### invokeWrapper: ServCMS : consumer threads invoke successfully %d \n", ts);
                          if(pthread_setschedprio(threadWrapper[THRD_CONSUM],2));
                          {
                             fprintf(stderr,"\n\n priority is lowered...");
                          }
                   } // creates new thread when New connection is formed
               }
             }
            
       } else if ( !strcmp(inet_ntoa(clientaddr.sin_addr),cmsIP)) {
              fprintf(stderr, " ###### invokeWrapper:Service() : DeviceComm %d %s - %s \n", DeviceComm,inet_ntoa(clientaddr.sin_addr), deviceIP);
               if ( (threadWrapper[THRD_CMS]=(pthread_t *)realloc(NULL, sizeof(pthread_t))) == NULL )
               { perror("servCMS:handle_client(): ");
                 fprintf(stderr, "### ERROR : servCMS: threadWrapper[%d] realloc() Error\n, THRD_CMS") ;
               }else {
                   bzero(threadWrapper[THRD_CMS], sizeof(pthread_t));
                   cmsfd = clientfd ;
                   ts = pthread_create(&threadWrapper[THRD_CMS],NULL, (void *) &service,(void*)&cmsfd);
                   if(ts) {
                      fprintf(stderr,"### ERROR invokeWrapper:  ServCMS: return code from pthread_create is %d \n", ts);
                   } else {
                      fprintf(stderr,"### invokeWrapper: ServCMS : service threads invoke successfully %d \n", ts);
                   } // creates new thread when New connection is formed
              }
       } else {
              fprintf(stderr, " ###### invokeWrapper:Service() :  Invalid Client : %s  \n", inet_ntoa(clientaddr.sin_addr));
                    if(  shutdown(clientfd, SHUT_RDWR) == ERROR) {
                           fprintf(stderr, " consumeCMS: invokeServer() Socket fd %d not closed \n",clientfd);
                     }
                     if ( close(clientfd) == ERROR) {
                           fprintf(stderr, " consumeCMS: invokeServer() Socket fd %d not closed \n",clientfd);
                     }
       }

    }
      usleep(300000);

   }
   else
   {
          rc = return_from_longjmp_to_setjmp ;
          fprintf(stderr, " \n#### wrapper_sighandler() :: Catched  signal %d \n",rc);
           //  Unlock the mutex

          switch(rc)
          {
               case SIGINT  :   /* interrupt (rubout) */
               case SIGQUIT :   /* quit (ASCII FS) */
               case SIGABRT :   /* used by abort, replace SIGIOT in the future */
               case SIGKILL :   /* kill (cannot be caught or ignored) */
               case SIGSEGV :   /* segmentation violation */
               case SIGTERM :   /* software termination signal from kill */
               case SIGPIPE :
               case SIGHUP  :   /* Hang up signal */

        
                 if(DeviceComm)  {
                       fprintf(stderr, " ### WARNING Signal %d : invokerWrapper:Consumer() thread alive \n",rc);
                      if( ! (pthread_cancel(threadWrapper[THRD_CONSUM])) ) {
                          fprintf(stderr, " ### INFO Signal %d invokerWrapper:Consumer() thread Cancelled Successfully.\n", rc);
                          DeviceComm=TIMEOUT;
                      }
                  }

/*
                  if( ! (pthread_cancel(*thread_timeout)) )  {
                    fprintf(stderr, " ### INFO : invokerWrapper:thread_stat() Cancelled Successfully.\n");
                  }
*/
          }
   }

  }
}

int main(int argc, char **argv)
{
 
        if( initServer() == ERROR )  {
          fprintf(stderr, " ### ERROR : %s init_server() failed on port %d \n",argv[0], req_port); exit(1); 
        } else { handle_clients(); // pthread_exit(NULL); If used it keeps on running other threads...
              exit(0); // will never come?
        }
}
