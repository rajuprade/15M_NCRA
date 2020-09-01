
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


void  send_qmessage(int *);
void service(int); // prototype for thread routine
void consumer(int);// prototype for the Consumer Task which constantly Reads the Queue

// Queue functions
void q_enter(void);

void q_list(void);
void q_store(char *ptr);


void q_delete(int);

// Global Data//
static int store = 0;         // next storage position in queue[] 
static int retrieve = 0;      // retrieve position in queue[] 

char *queue[100];      // this array forms the queue 

pthread_mutex_t mutex;// mutex
pthread_t *thread; // pointer for a Consumer Task 
pthread_t *Thread; // pointer for the Client tasks

// Global Data//
static pid_t  current_pid;
static int current_fd = 0;
// -----------------------------------------------------------------------------
// Client time-out alarm
// -----------------------------------------------------------------------------

void sig_alarm(int signo) {
  printf("[%d] Client timed out.\n",current_pid);
  close(current_fd);
  exit(0);
}

int main()
{

	int sock, connected, bytes_recieved , true = 1;  
        struct sockaddr_in server_addr,client_addr;    
        int sin_size;
        int i=0;
        int ret;

        if ((sock = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
            perror("Socket");
            exit(1);
        }

        if (setsockopt(sock,SOL_SOCKET,SO_REUSEADDR,&true,sizeof(int)) == -1) {
            perror("Setsockopt");
            exit(1);
        }
        
        server_addr.sin_family = AF_INET;         
        server_addr.sin_port = htons(2000);     
        server_addr.sin_addr.s_addr = INADDR_ANY; 
        bzero(&(server_addr.sin_zero),8); 

        if (bind(sock, (struct sockaddr *)&server_addr, sizeof(struct sockaddr))
                                                                       == -1) {
            perror("Unable to bind");
            exit(1);
        }

        if (listen(sock, 5) == -1) {
            perror("Listen");
            exit(1);
        }
		
       
	  
    while(1)
    {
      printf("\nTCPServer Waiting for client on port 2000");
      fflush(stdout);
      sin_size = sizeof(struct sockaddr_in);
      connected = accept(sock, (struct sockaddr *)&client_addr,&sin_size);
      printf("\n I got a connection from (%s , %d)",inet_ntoa(client_addr.sin_addr),ntohs(client_addr.sin_port));
      fflush(stdout);

        
        if(!strcmp(inet_ntoa(client_addr.sin_addr),"192.168.30.4") ) {
         
         /* if (fork())  
            signal(SIGCHLD,SIG_IGN);
            close(sock);
            current_pid = getpid();
            current_fd = connected;
            signal(SIGALRM,sig_alarm);   */

            printf("[%d] Received a connection from %s, port %d\n", current_pid,
            inet_ntoa(client_addr.sin_addr), ntohs(client_addr.sin_port));
            thread=(pthread_t *)malloc(sizeof(pthread_t));
            pthread_create (thread, NULL, (void *) &consumer,connected);// Creates the Consumer Task
            if(!fork()){   // #### here copy of thread-child is wait to over the thread
                           //      *thread data is valid since copied from parent
            ret = pthread_join(*thread, NULL);
            printf( "thread Return status %d \n",ret);
       //   consumer(store);
            close(connected);
            printf("[%d] client terminated.\n", current_pid);
            exit(0);
            }
        } else {
             Thread=(pthread_t *)malloc(sizeof(pthread_t));
             pthread_create (Thread, NULL, (void *) &service,connected); // creates new thread when New connection is formed
       }

    }
    exit(0); // It should never come here
} /* main() */




// The Thread Task for All Clients

void service(int connected) 
{
    int flag=1;
    int length,i,lengthM;
    char recv_data[1024]; 
    int bytes_recieved;
    char MasterBuffer[5000];  
     char send_data []="<RESPONSES><RESPONSE><CODE>10</CODE><EVENT>10</EVENT><MESSAGE>SUCCESS</MESSAGE></RESPONSE></RESPONSES><RESP_END>"; 
    // This is Sample Responce but Wrapper can send other responces acording to its Alorithm

	printf("\n\n Current Task no %d\n\n",connected); // Shows how many connections are Created

    while(flag)
    {
                               
                     bytes_recieved = recv(connected,recv_data,1024,0); //save the data sent by client
                     fflush(stdout);
                     recv_data[bytes_recieved] = '\0';
                     fflush(stdout);
                     length=strlen(recv_data);

				    for(i=0;i<length;i++)

				    {
					 printf("%c",recv_data[i]);

				     }

                               
                     strcat(MasterBuffer, recv_data);

                     //Continue till the Client send <REQ_END> 
                     if( recv_data[length-1]=='>' && recv_data[length-2]=='D'&& recv_data[length-3]=='N'&& recv_data[length-4]=='E' && recv_data[length-5]=='_' && recv_data[length-6]=='Q'&& recv_data[length-7]=='E'&& recv_data[length-8]=='R' && recv_data[length-9]=='<')

                     {
                       printf("\n\nCOMPLETE COMMAND IS RECEIVED BY WRAPPER...");
                       flag=0;
                       send(connected, send_data,strlen(send_data), 0); // send the Responce back
                     }
     }
                          
       printf("\n\n PUTTING DATA IN QUEUE... ");
	   //  Lock the mutex
       pthread_mutex_lock(&mutex);
       q_store(MasterBuffer);
       printf("\n\nDATA STORED IN QUEUE SUCCESSFULLY..\nClosing Seccion %d",connected);
       //   Unlock the mutex
       pthread_mutex_unlock(&mutex);
       pthread_exit(0); /* exit */
}



void consumer(int connected)
{
/*
pthread_t tid;
int ret;
int status;
        thread=(pthread_t *)malloc(sizeof(pthread_t));
        pthread_create (thread, NULL, (void *) &send_qmessage,&store);// Creates the Consumer Task
// waiting to join thread "tid" with status //
//       tid = pthread_self();
        printf(" Waiting for the thread to end \n");
        ret = pthread_join(*thread, NULL);
        printf( "thread Return status %d \n",ret);
; */
    while(1)
    {
      printf(" I am in while store [%d] retrieve [%d] \n",store, retrieve);
	 //  Lock the mutex
     pthread_mutex_lock(&mutex);
      q_delete(connected);
     //   Unlock the mutex
     pthread_mutex_unlock(&mutex);
     sleep(1 );
    }
  return;
}

// Queue function starts------------------------------//
// store data items in the queue 
//
void q_store(char *ptr)
{   
  if (store == 100) { 
    printf("\nList is full!");  
    return; 
  }
  
  if(store==retrieve)
  {
    store = 0;         
    retrieve = 0;  
   
   }
   queue[store] = ptr;
   store++;  // point to next available storage position in queue[] 
   printf( "###  store %d \n",store);
}

//
// delete data at retrieve position
//
void q_delete(int connected)
{
   //char send_data []="<RESPONSES><RESPONSE><CODE>10</CODE><EVENT>10</EVENT><MESSAGE>SUCCESS</MESSAGE></RESPONSE></RESPONSES><RESP_END>"; 
  if (store == retrieve) {
    //printf("\nQueue is empty!");
    return;
  }

  printf("\nDATA EXTRACTED FROM QUEUE IS:   ");
  printf("%s",queue[retrieve]);
  // send message on network
  printf("Sending to Connected client %d \n", connected);
  send(connected, queue[retrieve],strlen(queue[retrieve]), 0); // send the Responce back
  retrieve++;   // move retrieve position to next data item
}

void send_qmessage(int *i)     
{
    while(1)
    {
//  Lock the mutex
  printf(" I am in qmessage retrieve store %d [%d] retreive %d \n", store, (int) *i, retrieve);
 if (store == retrieve) { sleep(1); continue; }

  pthread_mutex_lock(&mutex);

  printf("\nDATA EXTRACTED FROM QUEUE IS:   ");
  printf("%s",queue[retrieve]);

  retrieve++;   // move retrieve position to next data item 
  pthread_mutex_unlock(&mutex);     //   Unlock the mutex

    sleep(1 );
   }
  return;
}
// Queue function Ends------------------------------//

