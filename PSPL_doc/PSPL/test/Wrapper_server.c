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
#include <netdb.h>
typedef unsigned char  BYTE;

# define REQ_PORT  5000
# define RESP_PORT 4000

void service(int*);                            // prototype for thread routine
void consumer(int*);                       // prototype for the Consumer Task which constantly Reads the Queue

// Queue functions
void q_enter(void);

void q_list(void);
void q_store(char *ptr);


void q_delete(void);

// Data extraction functions

char *get_timestamp(char *);
char *get_cmdseq(char *);
char  *get_cmdid(char *);
char *get_sysid(char *);
char *get_ver(char *);
BYTE param_cnt(char *);
char *get_cmdparam(char *);


// Global Data//
int store = 0;         // next storage position in queue[] 
int retrieve = 0;      // retrieve position in queue[] 
char *queue[1000000];      // this array forms the queue 

pthread_mutex_t mutex;// mutex
pthread_mutex_t fmutex;// mutex for file
pthread_mutex_t Rmutex;// mutex for file

FILE *file;
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
       server_addr.sin_port = htons(REQ_PORT);     
          // server_addr.sin_port = htons(RESP_PORT); 
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

	  pthread_create (thread, NULL, (void *) &consumer,(void *)&i);// Creates the Consumer Task
	  if(pthread_setschedprio(*thread,2));

	  {
		 printf("\n\n priority is lowered...");

	  }

      while(1)
	  {

	    printf("\nTCPServer Waiting for client on port 5000");
            fflush(stdout);
            sin_size = sizeof(struct sockaddr_in);

            connected = accept(sock, (struct sockaddr *)&client_addr,&sin_size);
  
          printf("\n I got a connection from (%s , %d)",inet_ntoa(client_addr.sin_addr), ntohs(client_addr.sin_port));

          fflush(stdout);

      /* Thread is create for every client getting connected to the server.....new SOCKET FD is passed in the thread_fucntion() ...*/

	   Thread=(pthread_t *)malloc(sizeof(pthread_t));
   
           pthread_create (Thread, NULL, (void *) &service,(void*)&connected); // creates new thread when New connection is formed
	 
   
	   }
       exit(0); // It should never come here



} /* main() */




// The Thread Task for All Clients

void service(int *connected) 
{
    
 char *buffer;                                  
 char *exbuffer;                               
 char *finalbuffer;                             
 char *respfile;                                
 char resp1[]=(" <responses><response>"); 
 char resp2[]=("</response></responses><RESP_END>");
 char ACKdata[]=("<event>10</event><code>10</code>");
 char *ACK;                                     
 char *ID;   
//char  *temp; 
//char str[10000];                                   
	                                 
 char byte;
 int i=0;
 int j=0;
 int commandflag=0;
 int bytes_recieved;

 buffer=(char *)malloc(sizeof(char)*5000);
 exbuffer=(char *)malloc(sizeof(char)*5000);
 finalbuffer=(char *)malloc(sizeof(char)*5000);
 respfile=(char *)malloc(sizeof(char)*5000);
 ACK=(char *)malloc(sizeof(char)*5000);
 ID=(char *)malloc(sizeof(char)*10);




	printf("\n\n Current Task no %d\n\n",*connected); 

			  
                               
                     bytes_recieved = recv(*connected,buffer,5000,0); //save the data sent by client
                     fflush(stdout);
                     buffer[bytes_recieved] = '\0';
                     fflush(stdout);
                     puts(buffer);
					 for(i=0;i<strlen(buffer);i++)

 {

	 if( buffer[i]=='<' && (buffer[i+1]=='C'||buffer[i+1]=='c')&& (buffer[i+2]=='O'||buffer[i+2]=='o')&& (buffer[i+3]=='M'||buffer[i+3]=='m')&& (buffer[i+4]=='M'||buffer[i+4]=='m')&& (buffer[i+5]=='A'||buffer[i+5]=='a')&& (buffer[i+6]=='N'||buffer[i+6]=='n')&& (buffer[i+7]=='D'||buffer[i+7]=='d')&& buffer[i+8]=='>')
        
	 {
		 i=i+9;

		 commandflag=1;

     }

     if(commandflag)

	 {
		 exbuffer[j]=buffer[i];
		 j++;

	 }



 }

exbuffer[j]='\0';





printf("\nThe extracted data\n\n");

puts(exbuffer);
j=0;
for(i=0;i<strlen(exbuffer);i++)
{
  if((exbuffer[i]=='<' && (exbuffer[i+1]=='D'||exbuffer[i+1]=='d')&& (exbuffer[i+2]=='A'||exbuffer[i+2]=='a' )&& (exbuffer[i+3]=='T'||exbuffer[i+3]=='t') && (exbuffer[i+4]=='A'||exbuffer[i+4]=='a' )&& exbuffer[i+5]=='>')||(exbuffer[i]=='<' && exbuffer[i+1]=='/' && (exbuffer[i+2]=='C'||exbuffer[i+2]=='c' )&& (exbuffer[i+3]=='O'||exbuffer[i+3]=='o' )&& (exbuffer[i+4]=='M'||exbuffer[i+4]=='m')&& (exbuffer[i+5]=='M'||exbuffer[i+5]=='m')))

  {
	 break;
  }
  
  finalbuffer[j]=exbuffer[i];
  j++;


}

finalbuffer[j]='\0';

printf("\n\n Exact data is as below....\n");


puts(finalbuffer);


printf("\nThe ACK to be sent is....\n\n");

strcpy(ACK,resp1);
strcat(ACK,finalbuffer);
strcat(ACK,ACKdata);
strcat(ACK,resp2);
puts(ACK);
printf("\n\nCOMPLETE COMMAND IS RECEIVED BY WRAPPER...");
                                    
send(*connected,ACK,strlen(ACK), 0); // send the RESPONSE back

printf("\n\n PUTTING DATA IN QUEUE... ");

//  Lock the mutex

pthread_mutex_lock(&mutex);

q_store(buffer);

//printf(" Data stored in the Queue is %s ", buffer);

printf("\n\nDATA STORED IN QUEUE SUCCESSFULLY..\nClosing Seccion %d",*connected);
       
//   Unlock the mutex
       
pthread_mutex_unlock(&mutex);

// Data Extraction Code 

/*  strcpy(str,buffer);
  temp=  get_timestamp(str);
  printf("TimeStamp:%s\t",temp);
  puts(temp);
 temp=  get_cmdseq(ptr);
  printf("CMD SEQ:%s\t",temp);
  temp= get_sysid(ptr);
  printf("SYS ID:%s\t",temp);
  temp= get_cmdid(ptr);
  printf("CMD ID:%s\t",temp);
  temp= get_ver(ptr);
  printf("VERSION:%s\t",temp);
  temp= get_cmdparam(ptr);
  printf("CMD PARAM:%s\n",temp); */
 
 free(exbuffer);
 free(finalbuffer);
 free(respfile);
 free(ACK);
 free(ID);
 


 //free(buffer);
 pthread_exit(0); /* exit */

}



void consumer(int* i)

{
	
	while(1)
	{

	 

	 //  Lock the mutex
     pthread_mutex_lock(&mutex);

     q_delete();

     //   Unlock the mutex
     pthread_mutex_unlock(&mutex);

	 sleep(1);
    
	}


}








// Queue function starts------------------------------//

//
// store data items in the queue 
//
void q_store(char  *ptr)
{  
   char  *temp; 
   char str[10000];

 // temp = (char *)malloc(sizeof(char)*5000);
  //str = (char *)malloc(sizeof(*ptr));
  if (store == 1000) { 
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

  // printf(" Complete string Before Strcpy is :%s\t",ptr);
   // strcpy(str,ptr);
    //puts(" String copied properly ");
   //  puts(str);
  
/*  temp=  get_timestamp(str);
  printf("TimeStamp:%s\t",temp);
  puts(temp);
  temp=  get_cmdseq(ptr);
  printf("CMD SEQ:%s\t",temp);
  temp= get_sysid(ptr);
  printf("SYS ID:%s\t",temp);
  temp= get_cmdid(ptr);
  printf("CMD ID:%s\t",temp);
  temp= get_ver(ptr);
  printf("VERSION:%s\t",temp);
  temp= get_cmdparam(ptr);
  printf("CMD PARAM:%s\n",temp); */
  
 //   puts(ptr); 
   // printf(" I m here ");
}

//
// delete data at retrieve position
//
void q_delete(void)     
{

 char *buffer;                                  
 char *exbuffer;                               
 char *finalbuffer;                             
 char *respfile;                                
 char resp1[]=(" <responses><response>"); 
 char resp2[]=("</response></responses><RESP_END>");
 char ACKdata[]=("<event>12</event><code>10</code><data></data><message></message>");
 char *ACK;                                     
 char *ID;
 char *final_data;
 

 char *respbuffer;
	                                 
 char byte;
 int i=0;
 int j=0;
 int commandflag=0;


 buffer=(char *)malloc(sizeof(char)*5000);
 exbuffer=(char *)malloc(sizeof(char)*5000);
 finalbuffer=(char *)malloc(sizeof(char)*1024);
 respfile=(char *)malloc(sizeof(char)*1024);
 ACK=(char *)malloc(sizeof(char)*1024);
 ID=(char *)malloc(sizeof(char)*5);
 respbuffer=(char *)malloc(sizeof(char)*5000);

 



  if (store == retrieve) { 
    printf("\nQueue is empty!"); 
    return; 
  }

        int sock, bytes_recieved;  
       
		
        struct hostent *host;
        struct sockaddr_in server_addr;  
        host = gethostbyname("127.0.0.1");

        if ((sock = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
            perror("Socket");
            exit(1);
        }

        server_addr.sin_family = AF_INET;     
        server_addr.sin_port = htons(RESP_PORT); // as client  
        server_addr.sin_addr =*((struct in_addr *)host->h_addr);
        bzero(&(server_addr.sin_zero),8); 

        if (connect(sock, (struct sockaddr *)&server_addr,
                    sizeof(struct sockaddr)) == -1) 
        {
            perror("Connect");
            exit(1);
        }


  printf("\nDATA EXTRACTED FROM QUEUE IS:   ");
  sprintf(buffer,"%s",queue[retrieve]);

  free(queue[retrieve]);

  printf("\n\n\nYOU MUST SEE THIS :");

  puts(buffer);
  for(i=0;i<strlen(buffer);i++)

 {

	 if( buffer[i]=='<' && (buffer[i+1]=='C'||buffer[i+1]=='c')&& (buffer[i+2]=='O'||buffer[i+2]=='o')&& (buffer[i+3]=='M'||buffer[i+3]=='m' )&& (buffer[i+4]=='M'||buffer[i+4]=='m') && (buffer[i+5]=='A'||buffer[i+5]=='a') && (buffer[i+6]=='N'||buffer[i+6]=='n' )&& (buffer[i+7]=='D'||buffer[i+7]=='d')&& buffer[i+8]=='>')
        
	 {
		 i=i+9;

		 commandflag=1;

     }

     if(commandflag)

	 {
		 exbuffer[j]=buffer[i];
		 j++;

	 }



 }

exbuffer[j]='\0';

printf("\nThe extracted data\n\n");

puts(exbuffer);
j=0;
for(i=0;i<strlen(exbuffer);i++)
{
  if((exbuffer[i]=='<' && (exbuffer[i+1]=='D'||exbuffer[i+1]=='d')&& (exbuffer[i+2]=='A'||exbuffer[i+2]=='a' )&& (exbuffer[i+3]=='T'||exbuffer[i+3]=='t' )&& (exbuffer[i+4]=='A'||exbuffer[i+4]=='a' )&& exbuffer[i+5]=='>')||(exbuffer[i]=='<' && exbuffer[i+1]=='/' && (exbuffer[i+2]=='C'||exbuffer[i+2]=='c') && (exbuffer[i+3]=='O'||exbuffer[i+3]=='o' )&& (exbuffer[i+4]=='M'||exbuffer[i+4]=='m')&& (exbuffer[i+5]=='M'||exbuffer[i+5]=='m')))

  {
	 break;
  }
  
  finalbuffer[j]=exbuffer[i];
  j++;


}

finalbuffer[j]='\0';

printf("\n\n Exact data is as below....\n");


puts(finalbuffer);

j=0;
for(i=0;i<strlen(finalbuffer);i++)
{
  
	if(finalbuffer[i]=='<' && (finalbuffer[i+1]=='I'||finalbuffer[i+1]=='i')&& (finalbuffer[i+2]=='D'||finalbuffer[i+2]=='d')&& (finalbuffer[i+3]=='>'))
	{
      i=i+4;
	  while(finalbuffer[i]!='<')
	  {
		  ID[j]=finalbuffer[i];
		  j++;
		  i++;
       }

     break;
    }

}
 ID[j]='\0';
 strcpy(ACK,resp1);         // formation of packet 
 strcat(ACK,finalbuffer);
 strcat(ACK,ACKdata);
 strcat(ACK,resp2);


 send(sock,ACK,strlen(ACK), 0); // final responce is sent..

 retrieve++;   // move retrieve position to next data item

 free(buffer);
 free(exbuffer);
 free(finalbuffer);
 free(respfile);
 free(ACK);
 free(ID);

}


// Queue function Ends------------------------------//


// Data extraction code start here....

char *get_timestamp(char *ptr)
{
  BYTE ix,iy,iz,x;
  static char str1[512],str2[100];
  char *str,*strx;
  str = str1;
  strx = str2;
  
 // printf("String in the get_timestamp function is : %s\t",ptr);
  ix=0;
  iy=0;
  iz=0;
  x=0;
  strcpy(str,ptr);
  
  do
  {
    ix++;
  }while(!((str[ix]=='>') && (str[ix-1]=='P'||str[ix-1]=='p')&& (str[ix-2]=='M'||str[ix-2]=='m')&& (str[ix-3]=='A'||str[ix-3]=='a')&& (str[ix-4]=='T'||str[ix-4]=='t')&& (str[ix-5]=='S'||str[ix-5]=='s')&& (str[ix-6]=='E'||str[ix-6]=='e')&& (str[ix-7]=='M'||str[ix-7]=='m')&& (str[ix-8]=='I'||str[ix-8]=='i')&& (str[ix-9]=='T'||str[ix-9]=='t')&& (str[ix-10]=='<')));
  
  ix++;
  
  do
  {
    iy++;
  }while(!((str[iy]=='<') && (str[iy+1]=='/') && (str[iy+2]=='T'||str[iy+2]=='t')&& (str[iy+3]=='I'||str[iy+3]=='i')&& (str[iy+4]=='M'||str[iy+4]=='m')&& (str[iy+5]=='E'||str[iy+5]=='e')&& (str[iy+6]=='S'||str[iy+6]=='s') && (str[iy+7]=='T'||str[iy+7]=='t') && (str[iy+8]=='A'||str[iy+8]=='a') && (str[iy+9]=='M'||str[iy+9]=='m') && (str[iy+10]=='P'||str[iy+10]=='p') && (str[iy+11]=='>')));
  
  for(iz=ix;iz<iy;iz++)
    str2[x++]=str1[iz];
  
  str2[x]='\0';

// printf("Return string from the timestamp fucntion is :%s\t",strx);

  return strx;
}

char *get_cmdseq(char *ptr)
{
  BYTE ix,iy,iz,x;
  static char str1[512],str2[100];
  char *str,*strx;
  str = str1;
  strx = str2;
  
  ix=0;
  iy=0;
  iz=0;
  x=0;
  strcpy(str,ptr);
  
  do
  {
    ix++;
  }while(!((str[ix]=='>') && (str[ix-1]=='Q'||str[ix-1]=='q')&& (str[ix-2]=='E'||str[ix-2]=='e')&& (str[ix-3]=='S'||str[ix-3]=='s')&& (str[ix-4]=='<')));
  
  ix++;
  
  do
  {
    iy++;
  }while(!((str[iy]=='<') && (str[iy+1]=='/') && (str[iy+2]=='S'||str[iy+2]=='s')&& (str[iy+3]=='E'||str[iy+3]=='e')&& (str[iy+4]=='Q'||str[iy+4]=='q')&& (str[iy+5]=='>')));
  
  for(iz=ix;iz<iy;iz++)
    str2[x++]=str1[iz];
  
  str2[x]='\0';
  return strx;
}

char *get_cmdid(char *ptr)
{
  BYTE ix,iy,iz,x;
  static char str1[512],str2[100];
  char *str,*strx;
  str = str1;
  strx = str2;
  
  ix=0;
  iy=0;
  iz=0;
  x=0;
  strcpy(str,ptr);
  
  do
  {
    ix++;
  }while(!((str[ix]=='>') && (str[ix-1]=='D'||str[ix-1]=='d')&& (str[ix-2]=='I'||str[ix-2]=='i')&& (str[ix-3]=='<')));
  
  ix++;
  
  do
  {
    iy++;
  }while(!((str[iy]=='<') && (str[iy+1]=='/') && (str[iy+2]=='I'||str[iy+2]=='i')&& (str[iy+3]=='D'||str[iy+3]=='d')&& (str[iy+4]=='>')));
  
  for(iz=ix;iz<iy;iz++)
    str2[x++]=str1[iz];
  
  str2[x]='\0';
  return strx;
}

char *get_sysid(char *ptr)
{
  BYTE ix,iy,iz,x;
  static char str1[512],str2[100];
  char *str,*strx;
  str = str1;
  strx = str2;
  
  ix=0;
  iy=0;
  iz=0;
  x=0;
  strcpy(str,ptr);
  
  do
  {
    ix++;
  }while(!((str[ix]=='>') && (str[ix-1]=='D'||str[ix-1]=='d')&& (str[ix-2]=='I'||str[ix-2]=='i')&& (str[ix-3]=='M'||str[ix-3]=='m')&&  (str[ix-4]=='E'||str[ix-4]=='e')&&  (str[ix-5]=='T'||str[ix-5]=='t')&&  (str[ix-6]=='S'||str[ix-6]=='s')&&  (str[ix-7]=='Y'||str[ix-7]=='y')&&  (str[ix-8]=='S'||str[ix-8]=='s')&&  (str[ix-9]=='<')));
  
  ix++;
  
  do
  {
    iy++;
  }while(!((str[iy]=='<') && (str[iy+1]=='/') && (str[iy+2]=='S'||str[iy+2]=='s')&& (str[iy+3]=='Y'||str[iy+3]=='y') && (str[iy+4]=='S'||str[iy+4]=='s')&& (str[iy+5]=='T'||str[iy+5]=='t') && (str[iy+6]=='E'||str[iy+6]=='e')&& (str[iy+7]=='M'||str[iy+7]=='m') && (str[iy+8]=='I'||str[iy+8]=='i')&& (str[iy+9]=='D'||str[iy+9]=='d') && (str[iy+10]=='>')));
  
  for(iz=ix;iz<iy;iz++)
    str2[x++]=str1[iz];
  
  str2[x]='\0';
  return strx;
}

char *get_ver(char *ptr)
{
  BYTE ix,iy,iz,x;
  static char str1[512],str2[100];
  char *str,*strx;
  str = str1;
  strx = str2;
  
  ix=0;
  iy=0;
  iz=0;
  x=0;
  strcpy(str,ptr);
  
  do
  {
    ix++;
  }while(!((str[ix]=='>') && (str[ix-1]=='N'||str[ix-1]=='n')&& (str[ix-2]=='O'||str[ix-2]=='o')&& (str[ix-3]=='I'||str[ix-3]=='i')&&  (str[ix-4]=='S'||str[ix-4]=='s')&&  (str[ix-5]=='R'||str[ix-5]=='r')&&  (str[ix-6]=='E'||str[ix-6]=='e')&&  (str[ix-7]=='V'||str[ix-7]=='v')&& (str[ix-8]=='<')));
  
  ix++;
  
  do
  {
    iy++;
  }while(!((str[iy]=='<') && (str[iy+1]=='/') && (str[iy+2]=='V'||str[iy+2]=='v')&& (str[iy+3]=='E'||str[iy+3]=='e') && (str[iy+4]=='R'||str[iy+4]=='r')&& (str[iy+5]=='S'||str[iy+5]=='s') && (str[iy+6]=='I'||str[iy+6]=='i')&& (str[iy+7]=='O'||str[iy+7]=='o') && (str[iy+8]=='N'||str[iy+8]=='n')&& (str[iy+9]=='>')));
  
  for(iz=ix;iz<iy;iz++)
    str2[x++]=str1[iz];
  
  str2[x]='\0';
  return strx;
}

BYTE param_cnt(char *ptr)
{
  int count,ix;
  char str1[512];
  char *str;
  
  str = str1;
  strcpy(str,ptr);
  count=0;
  
  for (ix=0;ix<strlen(str);ix++)
  {
    if((str[ix]=='>') && (str[ix-1]=='M'||str[ix-1]=='m')&& (str[ix-2]=='A'||str[ix-2]=='a')&& (str[ix-3]=='R'||str[ix-3]=='r')&&  (str[ix-4]=='A'||str[ix-4]=='a')&&  (str[ix-5]=='P'||str[ix-5]=='p')&& (str[ix-6]=='<'))
      count++;
  }
  return count;
}

char *get_cmdparam(char *ptr)
{
  static int ix,iy,iz,x;
  static char str1[512],str2[100],str3[100];
  char *str,*strx,*stry;
  str = str1;
  strx = str2;
  stry = str3;
  int y;
  ix=0;  iy=0;  iz=0;
  x=0;   y=0;
  
  strcpy(str,ptr);
  
  for(y=0;y<param_cnt(str1);y++)
  {
    do
    {
      ix++;
    }while(!((str[ix]=='>') && (str[ix-1]=='E'||str[ix-1]=='e')&& (str[ix-2]=='U'||str[ix-2]=='u')&& (str[ix-3]=='L'||str[ix-3]=='l')&&  (str[ix-4]=='A'||str[ix-4]=='a')&&  (str[ix-5]=='V'||str[ix-5]=='v')&& (str[ix-6]=='<')));
    
    ix++;
    
    do
    {
      iy++;
    }while(!((str[iy]=='<') && (str[iy+1]=='/') && (str[iy+2]=='V'||str[iy+2]=='v')&& (str[iy+3]=='A'||str[iy+3]=='a') && (str[iy+4]=='L'||str[iy+4]=='l')&& (str[iy+5]=='U'||str[iy+5]=='u') && (str[iy+6]=='E'||str[iy+6]=='e')&& (str[iy+7]=='>')));
    
    
    
    for(iz=ix;iz<iy;iz++)
      str2[x++]=str1[iz];
    
    strcat(strx,",");
    strcat(stry,strx);
    iy = iy+8;
    ix=iy;
    x=0;
    
  }
  return stry;
}



























