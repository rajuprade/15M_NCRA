#include"server_test.h"
#include"thread_01.h"


#include <sys/resource.h>
#include<pthread.h>
#ifndef HAVE_GETRUSAGE_PROTO
   int   getrusage(int, struct rusage *);
#endif

pthread_mutex_t mlock = PTHREAD_MUTEX_INITIALIZER;

int main(int argc ,char **argv)
{
    int i,buf[4],j;
    void sig_int(int) ,thread_make(int);
    //unsigned char tmp[8] = {1,0,0,0,1,1,0,0};
      unsigned char  mask[8] ,tmp[32];
    if(argc == 2)
    listenfd = tcp_listen(NULL,argv[1] ,&addrlen);
    else   if (argc == 3)
    listenfd = tcp_listen(argv[1] ,argv[2] ,&addrlen);
    
    else
        perror("Usage:serv[<host> <port#> <#threads>");
        
        /*nthreads = atoi(argv[argc -1]);
         for(i = 0 ;i<8;i++)
          nthreads = (1 & tmp[i]) ;
       atoi() function converts the initial portion of the string pointed to by nptr to int........*/
     printf("Enter 4 number in hexadecimal\n");
     for(i=0;i < 4 ;i++)
     {
      scanf("%x",&buf[i]);
     }
        
         for(j= 0 ; j < 4 ;j++)
        printf("value in buf[%d] is %x\n",j,buf[j]);

         for(j = 0 ; j< 4 ;j++)
         {

           for(i=0; i<8; i++)
           if(buf[j] & (1<<i))
            mask[i] = 1;
             else
             mask[i] = 0;

              switch(j)
              {

               case 0:
                      for(i = 0 ;i < 8;i++)
                      tmp[i] = mask[i];
                      break;

               case 1:
                      for(i = 0 ;i < 8;i++)
                      tmp[i+8] = mask[i];
                      break;

               case 2:
                      for(i = 0 ;i < 8;i++)
                      tmp[i+16] = mask[i];
                      break;

                case 3:
                      for(i = 0 ;i < 8;i++)
                      tmp[i+24] = mask[i];
               }
          }



  
         for(i = 0 ;i < 32;i++)
          if(tmp[i] == 1) 
            nthreads++;
         printf("%d\n",nthreads); 
        tptr = calloc(nthreads ,sizeof(Thread));
        for(i = 0 ; i < 32 ; i++)
         if(tmp[i] == 1)
         thread_make(i); /*only main thread returns */
         
         signal(SIGINT ,sig_int);
         for(; ; )
          pause(); /* everything done by threads */
}

void thread_make(int i)
{
   pthread_attr_t attr;
   void *thread_main(void *);
   /* Initialize and set thread joinable attribute */
    pthread_attr_init(&attr);
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);
    pthread_create(&tptr[i].thread_tid ,NULL ,&thread_main,(void *) i);
    /* Free attribute and join with worker threads */
    pthread_attr_destroy(&attr);
   // pthread_join(tptr[i].thread_tid,NULL);
   return; /* main thread returns */
}


void *thread_main(void *arg)
{
   int connfd;
   void web_child(int);
   socklen_t clilen;
   struct sockaddr *cliaddr;
  
   cliaddr = malloc(addrlen);
   
   printf("Opening thread for  Anteena  %d\n",(int)arg);
   
   for( ; ;)
   {
      clilen = addrlen;
      pthread_mutex_lock(&mlock);
      connfd = accept(listenfd ,cliaddr ,&clilen);
      pthread_mutex_unlock(&mlock);
      tptr[(int) arg].thread_count++;
      web_child(connfd);
      close(connfd);
    }
}

void   pr_cpu_time(void)
{
       double user, sys;
       struct rusage myusage, childusage;

     if (getrusage(RUSAGE_SELF, &myusage) < 0)
         perror("getrusage error");
     if (getrusage(RUSAGE_CHILDREN, &childusage) < 0)
         perror("getrusage error");

     user = (double) myusage.ru_utime.tv_sec +
         myusage.ru_utime.tv_usec / 1000000.0;
     user += (double) childusage.ru_utime.tv_sec +
         childusage.ru_utime.tv_usec / 1000000.0;
     sys = (double) myusage.ru_stime.tv_sec +
         myusage.ru_stime.tv_usec / 1000000.0;
     sys += (double) childusage.ru_stime.tv_sec +
         childusage.ru_stime.tv_usec / 1000000.0;

     printf("\nuser time = %g, sys time = %g\n", user, sys);
    }

void sig_int(int signo)
 {
     void    pr_cpu_time(void);

     pr_cpu_time();
     exit(0);
 }

void  web_child(int sockfd)
{
    int write_socket(int);
    int read_socket(int);
    int r;
    
    r = write_socket(sockfd);
    if(r < 0)
    fprintf(stderr,"Failed to write on socket");
    else
    fprintf(stderr,"Writing on socket\n");
    
    r = read_socket(sockfd);
    if(r < 0)
    fprintf(stderr,"Failed to read from socket");
    else
    fprintf(stderr,"Reading from socket");    
   
}

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



      n = readline(sock,buffer,sizeof(MSG));
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


ssize_t  readline(int fd, void *vptr, size_t maxlen)
  {
      ssize_t n, rc;
      char    c, *ptr;

      ptr = vptr;
      for (n = 1; n < maxlen; n++) {
       again:
         if ( (rc = read(fd, &c, 1)) == 1) {
             *ptr++ = c;
             if (c == '\n')
                 break;          /* newline is stored, like fgets() */
         } else if (rc == 0) {
             *ptr = 0;
             return (n - 1);     /* EOF, n - 1 bytes were read */
         } else {
             if (errno == EINTR)
                 goto again;
             return (-1);        /* error, errno set by read() */
         }
     }

     *ptr = 0;                   /* null terminate like fgets() */
     return (n);
}


tcp_listen(const char *host, const char *serv, socklen_t *addrlenp)
 {
      int      listenfd, n;
      const int on = 1;
      struct addrinfo hints, *res, *ressave;

      bzero(&hints, sizeof (struct addrinfo)) ;
      hints.ai_flags = AI_PASSIVE;
     hints.ai_family = AF_UNSPEC;
     hints.ai_socktype = SOCK_STREAM;

     if ( (n = getaddrinfo (host, serv, &hints, &res)) != 0)
         perror("tcp_listen error ") ;
     ressave = res;

     do {
         listenfd = socket(res->ai_family, res->ai_socktype, res->ai_protocol);
         if (listenfd < 0)
             continue;            /* error, try next one */

         setsockopt(listenfd, SOL_SOCKET, SO_REUSEADDR, &on, sizeof (on) ) ;
         if (bind(listenfd, res->ai_addr, res->ai_addrlen) == 0)
             break;               /* success */

         close (listenfd);        /* bind error, close and try next one */
      } while ( (res = res->ai_next) != NULL);

      if (res == NULL)            /* errno from final socket () or bind () */
          perror("tcp_listen error");
          
           listen (listenfd, LISTENQ);

      if (addrlenp)
          *addrlenp = res->ai_addrlen;     /* return size of protocol address */

      freeaddrinfo (ressave);
      return (listenfd);
 }

