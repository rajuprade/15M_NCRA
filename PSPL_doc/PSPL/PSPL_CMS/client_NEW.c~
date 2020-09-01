/* tcpclient.c */

#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>


int main()

{

        int sock, bytes_recieved;  
        char send_data[1024],recv_data[1024];
        struct hostent *host;
        struct sockaddr_in server_addr;  
        int length;

        host = gethostbyname("127.0.0.1");

        if ((sock = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
            perror("Socket");
            exit(1);
        }

        server_addr.sin_family = AF_INET;     
        server_addr.sin_port = htons(5000);   
        server_addr.sin_addr = *((struct in_addr *)host->h_addr);
        bzero(&(server_addr.sin_zero),8); 

        if (connect(sock, (struct sockaddr *)&server_addr,
                    sizeof(struct sockaddr)) == -1) 
        {
            perror("Connect");
            exit(1);
        }

        while(1)
        {
        
          //bytes_recieved=recv(sock,recv_data,1024,0);
          //recv_data[bytes_recieved] = '\0';
 
          //if (strcmp(recv_data , "q") == 0 || strcmp(recv_data , "Q") == 0)
          //{
           //close(sock);
           //break;
          ///*}

          //else
           //printf("\nRecieved data = %s " , recv_data);*/
           
           //printf("\nSEND (q or Q to quit) : ");

           printf("\nEnter data:");
           gets(send_data);
           length=strlen(send_data);

           if(send_data[length-1]!='>' && send_data[length-2]!='D' && send_data[length-3]!='N' && send_data[length-4]!='E' && send_data[length-5]!='Q' && send_data[length-6]!='E' && send_data[length-7]!='R' && send_data[length-8]!='<')          
           {

             send(sock,send_data,strlen(send_data), 0);
             
            } 

          else
          {
             
             send(sock,send_data,strlen(send_data), 0);

             bytes_recieved=recv(sock,recv_data,1024,0);
             recv_data[bytes_recieved] = '\0';
             puts(recv_data);


           }





        
        }   
return 0;
}

