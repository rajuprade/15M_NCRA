
#ifndef _INVOKE_WRAP_H_
#define _INVOKE_WRAP_H_

#include <unistd.h>    /* Symbolic Constants */
#include <fcntl.h>
#include <sys/types.h> /* Primitive System Data Types */
#include <signal.h>
#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <pthread.h>
#include <stropts.h>
#include <sys/stat.h>
#include <ctype.h>

#define ERROR (-1)
typedef unsigned char  BYTE;
typedef int            BOOL;
typedef short int      WORD;

pthread_mutex_t mutex;// mutex
pthread_mutex_t fmutex;// mutex for file
pthread_mutex_t Rmutex;// mutex for file
pid_t  current_pid;

pthread_t *thread; // pointer for a Consumer Task
pthread_t *Thread; // pointer for the Client tasks

extern void consumer(int*);// prototype for the Consumer Task which constantly Reads the Queue
#endif
