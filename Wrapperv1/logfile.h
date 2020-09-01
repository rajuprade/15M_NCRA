#ifndef H_LOGFILE_H
#define H_LOGFILE_H

#include <unistd.h>     /* Symbolic Constants */
#include <sys/types.h>  /* Primitive System Data Types */
#include <errno.h>      /* Errors */
#include <stdio.h>      /* Input/Output */
#include <stdlib.h>     /* General Utilities */
#include <string.h>     /* String handling */
#include <unistd.h>
#include <errno.h>
#include <string.h>   //  // used for LOG generation
#include <time.h>     // used for LOG generation


extern FILE  *fp,*f;
extern void OpenFile( char *);
extern  void TimeStamp();
extern  void Renew();
extern  int NewFileTim;
extern   time_t StartTim;
extern  void CloseFile();
extern char filename[512],docname[512];               


#endif //H_LOGFILE_H
