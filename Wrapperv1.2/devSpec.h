
#ifndef __DEVSPEC_H__
#define __DEVSPEC_H__

#define MAXDEVCMD 24

long  cmdTimer[MAXDEVCMD];

void devSentinal(parseCMSCmd *, int *);
void devFrontend(parseCMSCmd *, int *);
void devDataserver(parseCMSCmd *, int *);
void devBackend(parseCMSCmd *, int *);
void devServo(parseCMSCmd *, int *);
void devSigcon(parseCMSCmd *, int *);

typedef enum { SENTINAL, SIGCON, FRONTEND, BACKEND, SERVO, DATASERVER, TOTALSYS } Enum_device;


/*
void devServo(parseCMSCmd *, int *);
void devBackend(parseCMSCmd *, int *);
void devSigcon(parseCMSCmd *, int *);
*/

#endif
