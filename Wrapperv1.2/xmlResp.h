#ifndef H_RESPXML_H
#define H_RESPXML_H

#define RESP_END "<RESP_END>"

#include <libxml/xmlreader.h>
#include <libxml/xmlmemory.h>
#include <libxml/parser.h>



extern void formBasicXmlResp(xmlNodePtr, BasicFlds *);
extern void formAnsXmlResp(xmlNodePtr , devResponse *);
void formDataXmlResp(xmlNodePtr, devResponse *);
extern char *formRespXML(devResponse *);

#endif
