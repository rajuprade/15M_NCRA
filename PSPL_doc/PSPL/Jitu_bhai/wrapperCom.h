
#ifndef _WRAPPER_COM_H_
#define _WRAPPER_COM_H_

//-------  Unet --------//
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <dirent.h>
#include <sys/wait.h>
#include <sys/resource.h>
#include <sys/time.h>
#include <netdb.h>

#define REQ_PORT  9000
#define RESP_PORT  5000

#define DEVICE_IP "192.168.3.6"
#define RESP_IP  "127.0.0.1"
#define MON_IP   "127.0.0.1"

struct sockaddr_in servaddr;
struct sockaddr_in clientaddr;
int addr_type, addr_len, caddr_len;
int  req_port, resp_port, mon_port;
int sockfd;

extern int initServer(void);
extern int initRespPortCMS(void);

#endif
