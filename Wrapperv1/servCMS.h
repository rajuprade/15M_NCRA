
#ifndef _SERVCMS_H_
#define _SERVCMS_H_

#include <poll.h>


//#define WRPR_PORT  7575
#include "reqResp.h"


// Code is For Wrapper Only
typedef enum { Success=10,
               dTimeout=11,
               xmlSyntxErr=12,
               xmlIncomplete=13,
               xmlInvalid=14,
               Reset=15,

               ErrUnknown=100 
             } WrapperCodeEnum;

extern void formWrapperAck(devResponse *, int );
extern void service(int *);
extern void Openfile(char *);
extern void deviceStatResponse( );

#endif
