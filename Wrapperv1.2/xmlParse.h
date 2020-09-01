///////////////////////////////////////////////////////////////////////////
// PROJECT           : CMS Wrapper
// File              : xml_parser.H
// Author            : RajSingh
// Version           :
// Modification : 25-07-2011
// Reason            : XMLIB Based Parser
///////////////////////////////////////////////////////////////////////////

#ifndef _XMLPARSE_H_
#define _XMLPARSE_H_

#include <libxml/xmlreader.h>
#include <libxml/xmlmemory.h>
#include <libxml/parser.h>

#define CMD_FLD " "

typedef enum { Seq, Id, Name, Systemid, Username, Version, Timestamp, Priority, Timeout, Data, Param, Pname, Pvalue, Syntx, TXE } xmlEnum ;

extern int parsedata( xmlDocPtr,xmlNodePtr);
extern int parseparam( xmlDocPtr,xmlNodePtr);
extern int parseDoc(char *);



extern int  parseCmdStore(int, char *, xmlDocPtr , xmlNodePtr );
extern int  parsedataStore(int, char *);



#endif
