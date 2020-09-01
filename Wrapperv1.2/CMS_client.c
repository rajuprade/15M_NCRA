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
	 int count =1;
       while(count)
	   {

        int sock, bytes_recieved;  
        char *send_data;                       
		char *recv_data;                       
		char *filedata;                        
        struct hostent *host;
        struct sockaddr_in server_addr;  
        int length;
        char byte;
		int i=0;

        send_data=(char *)malloc(sizeof(char)*500000);
		recv_data=(char *)malloc(sizeof(char)*500000);
		filedata=(char *)malloc(sizeof(char)*1024);

     //  host = gethostbyname("192.168.30.4");
         host = gethostbyname("127.0.0.1");  
        if ((sock = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
            perror("Socket");
            exit(1);
        }

        server_addr.sin_family = AF_INET;     
        server_addr.sin_port = htons(8000);
        server_addr.sin_addr = *((struct in_addr *)host->h_addr);
        bzero(&(server_addr.sin_zero),8); 

        if (connect(sock, (struct sockaddr *)&server_addr,
                    sizeof(struct sockaddr)) == -1) 
        {
            perror("Connect");
            exit(1);
        }

       printf("\n\nReading Configurable file....");
	
	  FILE *file=fopen("sentinel1.xml","rb");
         // FILE *file = fopen("config.txt", "rb");
       //  FILE *file=fopen("sample.xml","rb");

      if(file==NULL)
	  {
		printf("\n\nCan't open file...");
		
		return 0;
	  }

	else
        
		while((byte=getc(file))!=EOF)
		{
			send_data[i]=byte;
			i++;
            
		}
		send_data[i]='\0';


       
       printf("\n\n CONFIGURATION FIE  DATA...\n");

	   puts(send_data);
         
       send(sock,send_data,strlen(send_data), 0);

        bytes_recieved=recv(sock,recv_data,1024,0);
        recv_data[bytes_recieved] = '\0';
        puts(recv_data);
	    close(sock);
         


       count--;

	   free(send_data);
	   free(recv_data);
	   free(filedata);


	   }

       
	   
return 0;
}

