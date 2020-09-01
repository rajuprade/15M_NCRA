///////////////////////////////////////////////////////////////////////////
// PROJECT           : ServoWrapper
// File              : DATA_EXTRACT.H
// Author            :
// Version           :
// Last Modification : 27-01-2011
// Reason            :
///////////////////////////////////////////////////////////////////////////

#ifndef _XMLPARSE_H_
#define _XMLPARSE_H_

#define CMD_FLD ","

extern char *get_timestamp(char *ptr);
extern char *get_cmdseq(char *ptr);
extern char *get_cmdid(char *ptr);
extern char *get_sysid(char *ptr);
extern char *get_ver(char *ptr);
extern unsigned char param_cnt(char *ptr);
extern int  get_cmdparam(char *ptr, char *out);
extern char *get_xmlheader(char *ptr);

extern void parseXmlCmd(char *, char *);
extern int  formXmlResp(char *, char *, char *);

#endif
