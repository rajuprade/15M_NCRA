
#ifndef _HANDLE_QUE_H
#define _HANDLE_QUE_H

#define MAXQUE     256
#define XMLBUFSIZE   4096

typedef struct
{
  int front, rear;
  int retrieve ;       /* Temporary */
  int store ;          /* temporary */
  int buffer_id[MAXQUE][MAXQUE] ;
  char buffer[MAXQUE][XMLBUFSIZE];
} xmlQueue;

// Queue functions
extern xmlQueue xmlQ ; /* Later make it static in handleQue.c */
extern void q_enter(void);
extern void q_list(void);

extern void q_store(char *);
extern char *q_retrieve(int );
//extern char *q_retrieve(char * );
//char *get_xmlheader(char *ptr);
extern void q_delete(void);

#endif
