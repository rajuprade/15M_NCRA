
#ifndef _DEVICE_CLIENT_H_
#define _DEVICE_CLIENT_H_

#define ERROR (-1)
#include "wrapperCom.h"

extern char *formDeviceCmd(parseCMSCmd *);
extern void formDeviceResp(parseCMSCmd *, devResponse *);


#endif
