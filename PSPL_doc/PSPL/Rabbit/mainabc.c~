#include <stdio.h>
#include<string.h>
#include <stdlib.h>
#include <sys/types.h>
#include<unistd.h>
#include<fcntl.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include "comhlink.h"

int main(int argc ,char *argv[])
{
   struct in_addr local_address;
   struct hostent *server;
   
    if (argc < 2)
     {
        fprintf(stderr,"usage %s hostname \n", argv[0]);
        exit(0);
     }

    server = gethostbyname(argv[1]);
     
      if (server == NULL)
       {
        fprintf(stderr,"ERROR, no such host\n");
        exit(0);
       }
    
      local_address.s_addr = *((int*) (server->h_addr_list[0]));
      
 /*   bcopy((char *)&local_address ,sizeof(local_address));
    bcopy((char *)server->h_addr,(char *)&local_address.s_addr,server->h_length);*/
     open_socket(local_address);

     return 0;
} 
