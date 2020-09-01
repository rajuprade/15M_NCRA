
#ifndef _consumCMS_H_
#define _consumCMS_H_

#define DEVICE_IP "192.168.3.6"
#define MON_IP    "192.168.140.109"

#define RESP_PORT 5000
#define MON_PORT  9898

char deviceIP[256];
int  deviceFd ;
  
char monIP[256];
int  monFd ;


extern int sendSystemPkt(char *, char*);
extern int  sendRespToCMS(char *);
extern void consumer(int *);
#endif
