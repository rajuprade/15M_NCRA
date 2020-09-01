#include "invokeWrapper.h"
#include "wrapperCom.h"


/*extern void sig_child(int signo) ; */

int initRespPortCMS()
{
   int sock=ERROR;
   char *envptr;
   int  bytes_recieved;
   char hostname[128];
   struct hostent *host;
   struct sockaddr_in server_addr;

   if( ( envptr = ( char * ) getenv("RESP_PORT")) != NULL ) {
         resp_port = atoi(envptr);
   } else {   resp_port = RESP_PORT; }

   if( ( envptr = ( char * ) getenv("RESP_IP")) != NULL ) {
         strcpy(hostname,envptr);
   } else {   strcpy(hostname,RESP_IP); }


   host = gethostbyname(hostname);

   if ((sock = socket(AF_INET, SOCK_STREAM, 0)) == ERROR ) {
       perror("initRespPortCMS() ");
       return ERROR ;
   }

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(resp_port); // as client
    server_addr.sin_addr =*((struct in_addr *)host->h_addr);
    bzero(&(server_addr.sin_zero),8);

    if (connect(sock, (struct sockaddr *)&server_addr, sizeof(struct sockaddr)) == ERROR ) {
         perror("initRespPortCMS() ");
         return ERROR ;
    }
    return sock ;
}

int initServer ()
{
  extern int sockfd;
  extern struct sockaddr_in servaddr;
  extern struct sockaddr_in clientaddr;
  extern int req_port;
  char   hostname[128] ;
  unsigned int len;
  static int prv_wrpsrv ;
  int clientfd ,reuse = 1 ;
  socklen_t optval ;
  struct linger wrplinger = { 0 , 0 };
  struct hostent *wrpsrv_host;
  u_long wrpsrv_net_addr;
  char *envptr;

   
   if( ( envptr = ( char * ) getenv("REQ_PORT")) != NULL ) {
         req_port= atoi(envptr);
   } else {   req_port = REQ_PORT; }

  fprintf(stderr, " init_server() REQ_PORT %d \n",req_port);

/*
  gethostname(hostname, sizeof(hostname));
  if ((wrpsrv_host = gethostbyname(hostname)) == NULL) return ;
  addr_type = wrpsrv_host->h_addrtype; addr_len = wrpsrv_host->h_length;
  wrpsrv_net_addr = *(u_long *)wrpsrv_host->h_addr;
*/

  memset(&servaddr, 0, sizeof(servaddr));
  servaddr.sin_family = AF_INET;
  servaddr.sin_port = htons(req_port);
  servaddr.sin_addr.s_addr = htonl(INADDR_ANY);   
  bzero(&(servaddr.sin_zero),8);
 /*servaddr.sin_addr.s_addr = wrpsrv_net_addr ; */

  if( (sockfd = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0) {
    fprintf(stderr, " \n#### Error : init_server() Unable to open socket !.\n");
    return ERROR;
  }


/* get & clear the errors on socket 
 if( getsockopt(sockfd, SOL_SOCKET, SO_ERROR, NULL ,  &optval) == ERROR) 
 { perror("setsockopt-SO_ERROR"); return ERROR; }  */
 if( setsockopt(sockfd, SOL_SOCKET, SO_LINGER, &wrplinger, sizeof(wrplinger)) == ERROR)
 { perror("setsockopt-SO_LINGER"); return ERROR; } 
 if( setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &reuse, sizeof(reuse)) == ERROR)
 { perror("setsockopt-SO_REUSEADDR"); return ERROR; }

/*
 if( setsockopt(sockfd, SOL_SOCKET, SO_REUSEPORT, &reuse, sizeof(reuse)) == ERROR) 
 { perror("setsockopt-SO_REUSEPORT"); return ERROR; } 
 if( setsockopt(sockfd, SOL_SOCKET, SO_DEBUG, &reuse, sizeof(reuse)) == ERROR)
 { perror("setsockopt_SO_DEBUG"); return ERROR; }
*/

 if( setsockopt(sockfd, SOL_SOCKET, SO_KEEPALIVE, &reuse, sizeof(reuse)) == ERROR)
 { perror("setsockopt_SO_KEEPALIVE"); return ERROR; }
/*
 if( setsockopt(sockfd, SOL_SOCKET, 15, &reuse, sizeof(reuse)) == ERROR)
 { perror("setsockopt_15"); return ERROR; } */

  if (bind(sockfd, (struct sockaddr *) &servaddr, sizeof(struct sockaddr )) < 0) {
    fprintf(stderr,"init_server() : Unable to bind to REQ_PORT %d\n", req_port);
    return ERROR;
  }

  listen(sockfd,5);

  fprintf(stdout," init_server() : WRAPPER SERVER LISTENING ON PORT %d\n", req_port);

  return 0 ;
}
