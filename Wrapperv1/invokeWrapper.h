
#ifndef _INVOKE_WRAP_H_
#define _INVOKE_WRAP_H_

#include <stdio.h>
#include <unistd.h>    /* Symbolic Constants */
#include <fcntl.h>
#include <sys/types.h> /* Primitive System Data Types */
#include <errno.h>
#include <math.h>
#include <time.h>
#include <string.h>
#include <stdlib.h>
#include <setjmp.h>
#include <signal.h>
#include <pthread.h>
//#include <stropts.h>
#include <sys/stat.h>
#include <ctype.h>

#define ERROR (-1)
#define MaxBufSize  409600
#define FileNameSize 512
         

typedef enum { THRD_CMS, THRD_CONSUM, DEVNCONN, TOTAL_THREAD} Tthread_Enum;

pthread_mutex_t mutex;// mutex
pid_t  current_pid;

/*
extern pthread_t *thread; // pointer for a Consumer Task
extern pthread_t Thread; // pointer for the Client tasks
extern pthread_t *thread_timeout;  // pointer to send TIMEOUT status on monPORT of the CMS
*/
extern pthread_t *threadWrapper[TOTAL_THREAD];

extern int DeviceComm ;
extern void consumer(int*);// prototype for the Consumer Task which Reads the Queue
extern void service(int*);// prototype for the service Task which  fills the Queue
#endif
