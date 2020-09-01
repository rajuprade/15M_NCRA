#include  <stdio.h>
#include  <stdlib.h>
#include  <signal.h>



void  SIGhandler(int);             /* SIGUSR1 handler    */

void sig_handler(int);


void  SIGhandler(int sig)
{
     printf("\nReceived a SIGUSR1. \n" );
     exit(0);
}
   
void sig_handler(int sig)  
{ 
     printf("\nReceived a SIGUSR2. \n" );
     exit(0);
}


int  main(void)
{
     long  fact= -2;
     
      signal(SIGUSR1, SIGhandler); 
      signal(SIGUSR2,sig_handler);
              if (fact < 0)           
               raise(SIGUSR1);    
          else
               raise(SIGUSR2); 
    }
     
