///////////////////////////////////////////////////////////////////////////
// PROJECT           : ServoWrapper
// File              : DATA_EXTRACT.H
// Author            :
// Version           :
// Last Modification : 27-01-2011
// Reason            :
///////////////////////////////////////////////////////////////////////////

#include "types.h"
#include "iodef.h"
#include "ioenum.h"


#ifndef __DATAEXTRACT_H__
#define __DATAEXTRACT_H__


extern char *get_timestamp(char *ptr);
extern char *get_cmdseq(char *ptr);
extern char *get_cmdid(char *ptr);
extern char *get_sysid(char *ptr);
extern char *get_ver(char *ptr);
extern BYTE param_cnt(char *ptr);
extern char *get_cmdparam(char *ptr);
extern char *get_xmlheader(char *ptr);

#endif