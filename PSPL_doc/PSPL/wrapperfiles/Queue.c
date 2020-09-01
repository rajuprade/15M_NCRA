/* Includes */
#include <unistd.h>     /* Symbolic Constants */
#include <sys/types.h>  /* Primitive System Data Types */ 
#include <errno.h>      /* Errors */
#include <stdio.h>      /* Input/Output */
#include <stdlib.h>     /* General Utilities */
#include <pthread.h>    /* POSIX Threads */
#include <string.h>     /* String handling */
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <errno.h>
#include<semaphore.h>

void service(int); // prototype for thread routine
void consumer(int);// prototype for the Consumer Task which constantly Reads the Queue

// Queue functions
void q_enter(void);

void q_list(void);
void q_store(char *ptr);


void q_delete(void);

// Global Data//
int store = 0;         // next storage position in queue[] 
int retrieve = 0;      // retrieve position in queue[] 
char *queue[100];      // this array forms the queue 

pthread_mutex_t mutex;// mutex

// Global Data//

int main()
{
	   

        pthread_t *thread; // pointer for a Consumer Task 
		pthread_t *Thread; // pointer for the Client tasks




	    int sock, connected, bytes_recieved , true = 1;  
        struct sockaddr_in server_addr,client_addr;    
        int sin_size;
        int i=0;

        if ((sock = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
            perror("Socket");
            exit(1);
        }

        if (setsockopt(sock,SOL_SOCKET,SO_REUSEADDR,&true,sizeof(int)) == -1) {
            perror("Setsockopt");
            exit(1);
        }
        
        server_addr.sin_family = AF_INET;         
        server_addr.sin_port = htons(5000);     
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
		
      
	  thread=(pthread_t *)malloc(sizeof(pthread_t));

	  pthread_create (thread, NULL, (void *) &consumer,i);// Creates the Consumer Task
	  
      while(1)
	  {

	  printf("\nTCPServer Waiting for client on port 5000");
      fflush(stdout);
      sin_size = sizeof(struct sockaddr_in);

      connected = accept(sock, (struct sockaddr *)&client_addr,&sin_size);

      printf("\n I got a connection from (%s , %d)",inet_ntoa(client_addr.sin_addr),ntohs(client_addr.sin_port));

      fflush(stdout);

	  Thread=(pthread_t *)malloc(sizeof(pthread_t));
   
      pthread_create (Thread, NULL, (void *) &service,connected); // creates new thread when New connection is formed
	 
   
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



void consumer(int i)

{
	
	while(1)
	{

	 

	 //  Lock the mutex
     pthread_mutex_lock(&mutex);

     q_delete();

     //   Unlock the mutex
     pthread_mutex_unlock(&mutex);

	 sleep(10);
    
	}


}








// Queue function starts------------------------------//

//
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
}

//
// delete data at retrieve position
//
void q_delete(void)     
{
  if (store == retrieve) { 
    //printf("\nQueue is empty!"); 
    return; 
  }

  printf("\nDATA EXTRACTED FROM QUEUE IS:   ");
  printf("%s",queue[retrieve]);
  retrieve++;   // move retrieve position to next data item 
}


// Queue function Ends------------------------------//



























