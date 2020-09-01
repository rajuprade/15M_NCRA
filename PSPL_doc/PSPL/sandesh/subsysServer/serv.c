#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <malloc.h>
#include "sockcommn.h"

//com_buf_ptr temp_ptr;

int connfd;
/*
typedef struct _msg
{
  int length;
  unsigned char Msg[100];
} MSG ;

MSG *buffer;
*/

int dostuff(void); /* function prototype */
void error(char *msg)
{
  perror(msg);
  exit(1);
}

int main(int argc, char *argv[])
{
  int sockfd,clilen, pid,i;
  struct sockaddr_in serv_addr, cli_addr;
  i =1;
  register_task_in(cmd_id);
  register_task_in(event_id);
  register_task_in(data_id);
  init_sockcommn_vars();


  
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
    serv_addr.sin_port = htons(SERV_PORT);
    
    if (setsockopt(sockfd,SOL_SOCKET,SO_REUSEADDR,&i,sizeof(int)) == -1) {
      perror("Setsockopt");
      exit(1);
    }
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
	connfd = accept(sockfd, (struct sockaddr *) &cli_addr, &clilen);
	if (connfd < 0)
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
	      dostuff();
	      
	   }
	  }
	  
	}
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
int dostuff ()
{
  int n,len;
 com_buf_ptr temp_ptr;
 com_buf_ptr test_ptr;
 
  //printf(" Enter the Commands in Capital letter\n");
  //fgets(temp_ptr->data,sizeof(temp_ptr->data),stdin);

  printf("Writing Command to Socket\n");
  temp_ptr=get_free_buff();
  temp_ptr->data[0]='F';
  temp_ptr->data[1]=',';
  temp_ptr->data[2]='A';
  
  temp_ptr->length = (BYTE)strlen(temp_ptr->data);
  //printf("length %d\n",temp_ptr->length);
  temp_ptr->des_task_id = cmd_id;
  temp_ptr->src_task_id = cmd_id;
  //printf("DATA:%s\n",temp_ptr->data);
  put_in_req(temp_ptr);
  printf("\nWriting Done\n");

  printf("Reading Socket for response\n");
 
  rx_mc();
  printf("Reading Done\n");
  test_ptr = get_from_indq(cmd_id);
  if(test_ptr)
    printf("\nReading the response from Queue : %02x\n",test_ptr->data[0]);
  else
    printf("Nothing to Read");
  
  return 0;
}
