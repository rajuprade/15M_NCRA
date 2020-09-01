/*
 **** gsblosrv program to communicate with bblocli running on ONLINE
      machine. Uses LoFsw.c module to set GSB LO  Jitendra 3/6/2010
 */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <ctype.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <sys/wait.h>
#include <signal.h>
#include <pwd.h>     
#include <errno.h>  

#define PORT "2003" // the port users will be connecting to
#define BACKLOG 10 // how many pending connections queue will hold
#define MAXDATASIZE 100

#include "LoFsw.h"

/*--------------------------------------*/
enum { BbID=0, Lo5Id=1, Accept=2, Success=3, Fail=4 };
char *resp_str[] = { "Connected to BB", "Connected to LO5", "Cmd Accept", "Cmd Successful", "Cmd Failed" };
/*--------------------------------------*/
int sockfd, new_fd, numbytes; // listen on sock_fd(server), new connection on new_fd (client)
/*--------------------------------------*/

extern char *mytime(void);

void sigchld_handler(int s)
{
while(waitpid(-1, NULL, WNOHANG) > 0);
}

// get sockaddr, IPv4 or IPv6:

 void *get_in_addr(struct sockaddr *sa)
 {
 if (sa->sa_family == AF_INET) {
 return &(((struct sockaddr_in*)sa)->sin_addr);
 }
 return &(((struct sockaddr_in6*)sa)->sin6_addr);
 }

 
 int server() 
 {
   struct addrinfo hints, *servinfo, *p;
   int rv; 
   int yes=1;
    
      memset(&hints, 0, sizeof hints);
      hints.ai_family = AF_UNSPEC;
      hints.ai_socktype = SOCK_STREAM;
      hints.ai_flags = AI_PASSIVE; // use my IP

      if ((rv = getaddrinfo(NULL, PORT, &hints, &servinfo)) != 0) {
        fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(rv));
        return 1;
      }

      // loop through all the results and bind to the first we can
      for(p = servinfo; p != NULL; p = p->ai_next)
      {
           if ((sockfd = socket(p->ai_family, p->ai_socktype, p->ai_protocol)) == -1) {
               perror("server: socket");
               continue;
            }

            if (setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int)) == -1) {
               perror("setsockopt");
               return(1);
            }

            if (bind(sockfd, p->ai_addr, p->ai_addrlen) == -1) {
              close(sockfd);
              perror("server: bind");
              continue;
            }
            break;
     }

     if (p == NULL) {
         fprintf(stderr, "server: failed to bind\n"); return 2;
     }
     freeaddrinfo(servinfo); // all done with this structure
     return 0;
 }

 void handle_client() 
 {
     struct sockaddr_storage their_addr; // connector's address information
     socklen_t sin_size;
     char s[INET6_ADDRSTRLEN]; 
     char buf[MAXDATASIZE], buftok[MAXDATASIZE], cmnd[16][256], *ptr;
     int  freqset[2];
     int i, res;
 

     while(1)
     { // main accept() loop
        sin_size = sizeof their_addr;
        new_fd = accept(sockfd, (struct sockaddr *)&their_addr, &sin_size);
        if (new_fd == -1) { perror("accept"); continue; }
        inet_ntop(their_addr.ss_family,
        get_in_addr((struct sockaddr *)&their_addr), s, sizeof s);
        fprintf(stderr,"server: got connection from %s\n", s);
        if (!fork()) { // this is the child process
             close(sockfd); // child doesn't need the listener
             
             if (send(new_fd, resp_str[Lo5Id], strlen(resp_str[Lo5Id]), 0) == -1) perror("send");

           while(1)
           {
              if( (numbytes = recv(new_fd,buf,MAXDATASIZE-1,0)) == -1) { perror("recv"); break ; }
              else if (numbytes) {

                 buf[numbytes] = '\0';
                 fprintf(stderr,"GSBLO[%s] : received %d bytes '%s' \n", (char *)mytime(), numbytes, buf); 
                 if(send(new_fd, resp_str[Accept], strlen(resp_str[Accept]), 0) == -1) perror("send");
                 res=1;
                 if( strncasecmp(buf,"init",4) == 0 )  { // Nothing to init, just send Success //
                     res = 0; 
                 }else if (strstr(buf,"SET") ) {
                       strcpy(buftok, buf);
                       ptr = strtok(buftok," ,");
                       i=0;  while(ptr!=NULL) { sprintf(cmnd[i],"%s",ptr); i++; ptr=strtok(NULL," ,"); };
                       freqset[0]=cmnd[3];
                       freqset[1]=cmnd[4];
                       res= LoFsw(freqset);
                }

                if(send(new_fd, resp_str[res?Fail:Success], strlen(resp_str[res?Fail:Success]), 0) == -1) perror("send");

                if(!strncasecmp(buf,"quit",4)) { fprintf(stderr," Closing client \n"); close(new_fd); break;} 
              } else {
                  fprintf(stderr, "GSBLO[%s] : received 0 bytes, closing connection..\n",(char*)mytime());
                  exit(1);
              }
          }
     }
     close(new_fd); // parent doesn't need this.. client new_fd
    }
 }

 int main(void)
 {

     pid_t pid; int dbgmsg ;
     struct sigaction sa; int fd;
  
    
  if( (pid = fork()) == 0 )
  {

     if(setsid() == -1 ) {
         fprintf(stderr, " Process is not running as a group leader or session leader\n");
     }

     if( fork() == 0 ) {
            chdir("/");
            umask(0);

               for(dbgmsg = 1 ; dbgmsg < 3 ; dbgmsg++)
               if ( (fd = open((const char *)MSGFILE,MSGFLAG,PMODE)) == ERROR ) {
                     perror(MSGFILE);
               }else{
                     if ( close(dbgmsg) == ERROR || dup(fd) == ERROR  || close(fd) == ERROR ) {
                      perror(MSGFILE);
                     }
               }
               
               if(server()) exit(1);
               if (listen(sockfd, BACKLOG) == -1) {
                   perror("listen"); exit(1);
               }
               
               sa.sa_handler = sigchld_handler; // reap all dead processes
               sigemptyset(&sa.sa_mask);
               sa.sa_flags = SA_RESTART;
               if (sigaction(SIGCHLD, &sa, NULL) == -1) {
                   perror("sigaction"); exit(1);
               }
               fprintf(stderr,"server: waiting for connections...\n");
               
               handle_client();
     } else if (pid == -1 ) {
            fprintf(stderr, "Process can not run as a daemon \n");
            exit(1);
     }else { _exit(0); }
 }
 else if (pid == -1 ) {
     fprintf(stderr, "Process can not run as a daemon \n");
     exit(1);
 }
 else 
 {   _exit(0);  }
}
