
#ifndef _HANDLE_QUE_H
#define _HANDLE_QUE_H

#define MAXQUE     256
#define XMLBUFSIZE   4096

#include "reqResp.h"

typedef struct
{
  int front, rear;
  int retrieve ;       /* Temporary */
  int store ;          /* temporary */
  int cmsCmd_id[MAXQUE];
  parseCMSCmd qCMSCmd[MAXQUE];
} xmlQueue;

// Queue functions
extern xmlQueue xmlQ ; /* Later make it static in handleQue.c */

extern void q_store(parseCMSCmd );
extern parseCMSCmd *q_retrieve(int );

//extern void q_delete(void);
//extern void printCmsStruct(parseCMSCmd *);

#endif
