#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h> 
#include<stdlib.h>
#include<string.h>
#include "sockcommn.h"
#include "eventdef.h"

#define PORT 5000
//#define PORT 4224
int clientfd;
void error(char *msg)
{
    perror(msg);
    exit(0);
}

int main(int argc, char *argv[])
{
    int i, n;
    struct sockaddr_in serv_addr;
    struct hostent *server;

    char buffer[256];

    register_task_in(cmd_id);
    register_task_in(event_id);
    register_task_in(data_id);
    init_sockcommn_vars();
    
    if (argc < 2) {
       fprintf(stderr,"usage %s hostname port\n", argv[0]);
       exit(0);
    }
    clientfd = socket(AF_INET, SOCK_STREAM, 0);
    if (clientfd < 0)
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
    if (connect(clientfd,(struct sockaddr *)&serv_addr,sizeof(serv_addr)) < 0)
         error("ERROR connecting");

    
   for(;;)
      {
          dostuff();
        }
               return 0;
}



int dostuff ()
{
  int n,len;
  com_buf_ptr temp_ptr;
  com_buf_ptr test_ptr;
  

  printf("Reading Command from Socket\n");
  rx_mc();
  printf("\nReading Done\n");
  
  printf("\nCommand Request from Queue\n");
  test_ptr = get_from_indq(cmd_id);
  //len = strlen(temp_ptr->data);
  //printf(" Length of test_ptr-> Data is %d \n\n", len);
  if(test_ptr)
  { 
     for(n=0; n <test_ptr->length;n++)
        //  while(len )
           printf(" %02X ",test_ptr->data[n]);
  }
  else
    printf("Nothing to Read\n");
  
  printf("\nWriting Acknowledgement to the Request\n");
  temp_ptr=get_free_buff();
  temp_ptr->data[0]=ACK;
  temp_ptr->length = (BYTE)strlen(temp_ptr->data);
  temp_ptr->des_task_id = cmd_id;
  temp_ptr->src_task_id = cmd_id;
  
  put_in_req(temp_ptr);

  printf("\nWriting Done\n");

  return 0;
}
