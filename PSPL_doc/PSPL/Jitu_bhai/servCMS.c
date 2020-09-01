
#include "invokeWrapper.h"
#include "wrapperCom.h"
#include "handleQue.h"
#include "xmlParse.h"

extern pthread_mutex_t mutex;// mutex
extern pthread_mutex_t fmutex;// mutex for file
extern pthread_mutex_t Rmutex;// mutex for file
extern pid_t  current_pid;

extern pthread_t *thread; // pointer for a Consumer Task
extern pthread_t *Thread; // pointer for the Client tasks

// The Thread Task for All Clients
void service(int *connected)
{
 //char *buffer;
 char respheader[]=(" <responses><response>");
 char respfooter[]=("</response></responses><RESP_END>");
 char wrapperACK[]=("<event>10</event><code>10</code>");
 char *response;
 char *tempstr;
 int bytes_recieved;
 char *recvbuffer ;

 tempstr=(char *)malloc(sizeof(char)*4096);
 response=(char *)malloc(sizeof(char)*4096);
 recvbuffer=(char *)malloc(sizeof(char)*4096);

 fprintf(stderr,"\n\n Current Task no %d\n\n",*connected);

  bytes_recieved = recv(*connected,recvbuffer,XMLBUFSIZE,0); //save the data sent by client
  recvbuffer[bytes_recieved] = '\0';
  puts(recvbuffer); fflush(stdout);

  fprintf(stderr,"\nThe ACK to be sent is....\n\n");

  strcpy(response,respheader);
//puts(response);
tempstr = get_xmlheader(recvbuffer);
strcat(response,tempstr);
strcat(response,wrapperACK);
strcat(response,respfooter);

fprintf(stderr," response %s \n",response);
fprintf(stderr,"\n\nCOMPLETE COMMAND IS RECEIVED BY WRAPPER...");
send(*connected,response,strlen(response), 0); // send the RESPONSE back
fprintf(stderr,"\n\n PUTTING DATA IN QUEUE... ");

//  Lock the mutex
pthread_mutex_lock(&mutex);
q_store(recvbuffer);
fprintf(stderr,"\n\nDATA STORED IN QUEUE SUCCESSFULLY..\nClosing Seccion %d",*connected);
//   Unlock the mutex
pthread_mutex_unlock(&mutex);

 free(response);
 free(recvbuffer);
 pthread_exit(0); /* exit */

}
