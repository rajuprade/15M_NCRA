#ifndef LOFSW_H
#define LOFSW_H

#define ERROR -1
#define baseaddress 0x378
#define CONTROL baseaddress + 2
#define STATUS baseaddress + 1
#define PMODE 00644
#define MSGFLAG   O_RDWR|O_NDELAY|O_APPEND|O_NONBLOCK|O_CREAT|O_TRUNC
#define MSGFILE  "/usr/local/gsblosrv/gsblosrvmsg.0" 



 int pattern(char ,int ,int  );
 char * Binary(int, int);
 int LoFsw(int FreqSet[]);
 int SetBit(int data[],int ref,int cnt);
 
#endif /* LOFSW_H Header */
