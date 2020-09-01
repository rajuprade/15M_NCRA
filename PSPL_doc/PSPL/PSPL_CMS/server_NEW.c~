/* tcpserver.c */

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>


int main()
{
        int sock, connected, bytes_recieved , true = 1;  
        char recv_data[1024]; 
        char MasterBuffer[5000];  
        char send_data []=" <XML> file will be here <RESP_END>";    
	    //char send_data []="a"; 
		int flag=1;
		int length;


        struct sockaddr_in server_addr,client_addr;    
        int sin_size;
        int i;

       while(1)
     {

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
		
	printf("\nTCPServer Waiting for client on port 5000");
        fflush(stdout);


        
         

              sin_size = sizeof(struct sockaddr_in);

              connected = accept(sock, (struct sockaddr *)&client_addr,&sin_size);

              printf("\n I got a connection from (%s , %d)",
                   inet_ntoa(client_addr.sin_addr),ntohs(client_addr.sin_port));

           
           /***********************************************************************************************/
              while(flag)

			  {
                               bytes_recieved = recv(connected,recv_data,1024,0);

                               recv_data[bytes_recieved] = '\0';
              
                 

                               //fflush(stdout);
                 
				    length=strlen(recv_data);

				    for(i=0;i<length;i++)

				    {
					 printf("%c",recv_data[i]);

				     }

                               
                               strcat(MasterBuffer, recv_data);


                               if( recv_data[length-1]=='>' && recv_data[length-2]=='D'&& recv_data[length-3]=='N'&& recv_data[length-4]=='E' && recv_data[length-5]=='_' && recv_data[length-6]=='Q'&& recv_data[length-7]=='E'&& recv_data[length-8]=='R' && recv_data[length-9]=='<')

                                 {


                                    printf("\n\nI GOT COMPLETE COMMAND");
                                    
                                    flag=0;

                                    send(connected, send_data,strlen(send_data), 0);

                                   }


                                      

                            }
                          
                           printf("\n\nComplete DATA is : ");
                           puts(MasterBuffer);

                           printf("\n\nServer is breaking connection now...");
                           sleep(5);

                           close(sock);

   }
      return 0;
} 

