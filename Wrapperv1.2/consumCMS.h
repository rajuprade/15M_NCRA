
#ifndef _consumCMS_H_
#define _consumCMS_H_
#include<poll.h>
//#define DEVICE_IP "192.168.3.6"
//#define MON_IP    "192.168.140.109"

//#define RESP_PORT 5000
//#define MON_PORT  9898

char deviceIP[32];
char monIP[32];
int  monFd ;

void terminateConsumer(int );   // Terminate Consumer thread..with proper Unlocking...
void printDevResp(devResponse * );
extern void checkDevEvent(devResponse *); // to check if device client is sending some Alarm/Monitoring Responses.
extern void devSpecExecute(parseCMSCmd *, devResponse *, int );  /* int to send async response in case of failure */
extern int sendSystemPkt(char *);
extern int recvSystemPkt(char *);
extern int  sendPktToCMS(char *, int );
extern void localRespToCMS(parseCMSCmd *, int );
extern void sendRespTOCMS(devResponse *);
extern void consumer(int *);

#endif
