#include"test_client.h"

#define MAXN 16384 /* max bytes to REQ from server */

int main(int argc ,char **argv)
{
   
    int i,j,fd,nchildren,nloops,nbytes;
    pid_t pid;
    ssize_t n;
  //  char request[MAXLINE] ,reply[MAXN];
   int write_socket(int);
   int read_socket(int); 
    if(argc != 4)
    perror("usage : client <hostname or IPaddr> <port> <#children>"
            "<#loops/child> <#bytes/request> ");
    
    nchildren = atoi(argv[3]);
   /* nloops    = atoi(argv[4]);
     nbytes    = atoi(argv[5]);
    
    snprintf(request ,sizeof(request) ,"%d\n", nbytes);*/
    
    for( i = 0; i < nchildren ;i++)
      {
         if((pid = fork()) == 0 )
         {
             fd = tcp_connect(argv[1] ,argv[2]);
             n = read_socket(fd);
             if(n < 0)
              fprintf(stderr,"Failed to read from socket");
              else
              fprintf(stderr,"Reading msg from server");
              
              n = write_socket(fd);
              if(n < 0)
              fprintf(stderr,"failed to write on socket");
              else
              fprintf(stderr,"Writing on socket");
                 
              printf("child %d done\n", i);
              exit(0);
           }
        /* parent loops around to fork() again */   
        }
    
      while( wait(NULL)  > 0);
     if(errno != ECHILD)
       perror("wait error");
       exit(0);
}
   
int tcp_connect(const char *host, const char *serv)
{
	int sockfd, n;
	struct addrinfo	hints, *res, *ressave;

	bzero(&hints, sizeof(struct addrinfo));
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;

	if ( (n = getaddrinfo(host, serv, &hints, &res)) != 0)
		perror("tcp_connect error ");
	ressave = res;

	do {
		sockfd = socket(res->ai_family, res->ai_socktype, res->ai_protocol);
		if (sockfd < 0)
			continue;	/* ignore this one */

		if (connect(sockfd, res->ai_addr, res->ai_addrlen) == 0)
			break;		/* success */

		close(sockfd);	/* ignore this one */
	} while ( (res = res->ai_next) != NULL);

	if (res == NULL)	/* errno set from final connect() */
		perror("tcp_connect error ");

	freeaddrinfo(ressave);

	return(sockfd);
}
/* end tcp_connect */

int write_socket(int sock)
{

   int n;
   MSG *buffer;

   buffer = (MSG * ) malloc ( sizeof( MSG ));
   if ( buffer == NULL)
            exit(1);

   buffer->length = sizeof(buffer->Msg);
   fgets(buffer->Msg ,buffer->length,stdin);

   n = writen(sock,buffer,sizeof(MSG));
   if(n < 0 )
     {
          printf("error writing to socket");
          free(buffer);
          close(sock);
          exit(1);

     }
    else
       {
         printf("1.wrote:%2d %s\n",buffer->length,buffer->Msg);
       }
    return 0;
}


int read_socket(int sock)
{
      int n;
      MSG *buffer;

      buffer = (MSG * ) malloc ( sizeof( MSG ));
      if ( buffer == NULL)
            exit(1);



      n = readn(sock,buffer,sizeof(MSG));
       if(n < 0 )
        {
          printf("error reading to socket");
          free(buffer);
          close(sock);
          exit(1);
        }
        else
         {
           printf("1.read:%2d %s\n",buffer->length,buffer->Msg);
         }
         return 0;
}




ssize_t readn(int fd ,void *vptr ,size_t n)
{
   size_t nleft;
   ssize_t nread;
   char *ptr;
   
   ptr = vptr;
   nleft = n;
   while(nleft > 0)
   {
       if((nread = read(fd ,ptr ,nleft))  < 0)
       {
          if(errno == EINTR)
           nread = 0;
           else
              return (-1);
        }
        else if(nread == 0)
          break;
          
         nleft -= nread;
         ptr += nread;
     }
     return (n -nleft);
}       

ssize_t  writen(int fd, const void *vptr, size_t n)
  {
      size_t nleft;
      ssize_t nwritten;
      const char *ptr;

      ptr = vptr;
      nleft = n;
     while (nleft > 0) {
         if ( (nwritten = write(fd, ptr, nleft)) <= 0) {
             if (nwritten < 0 && errno == EINTR)
                 nwritten = 0;   /* and call write() again */
             else
                 return (-1);    /* error */
          }

          nleft -= nwritten;
          ptr += nwritten;
     }
     return (n);
 }

