#include <unistd.h>     /* Symbolic Constants */
#include <sys/types.h>  /* Primitive System Data Types */
#include <errno.h>      /* Errors */
#include <stdio.h>      /* Input/Output */
#include <stdlib.h>     /* General Utilities */
#include <string.h>     /* String handling */
#include <unistd.h>
#include <errno.h>
//#include   <libxml/parser.h>
#include "reqResp.h"
#include "xmlParse.h"
#include "handleQue.h"
#define ERROR (-1)

char *xmlKeyWords[] = { "seq", "id", "name", "systemid", "version", "timestamp", "priority", "timeout", "data", "param", "name", "value" };


  int parseData( xmlDocPtr,xmlNodePtr);
  int parseparam( xmlDocPtr,xmlNodePtr);
  int parseDoc(char *docname) ;
  int parseCmdStore(int, char *, xmlDocPtr , xmlNodePtr );

  extern  parseCMSCmd parseCmd ;

 int parseData( xmlDocPtr doc, xmlNodePtr cur) 
 {
     xmlChar *key; char argName[DATALEN], argData[DATAPKT];
     int i=0;
     xmlNodePtr ParentCur ;
     DataPkt *dpkt = (DataPkt *)&parseCmd.data ;

     cur = cur->xmlChildrenNode;
     ParentCur = cur;

     while (cur != NULL) 
     {
                i=0; bzero(&argName,DATALEN);  bzero(&argData,DATAPKT); 

                if ((!xmlStrcmp(cur->name, (const xmlChar *)"param")))
                {
                     key = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
                     cur = cur->xmlChildrenNode;

                     if ( !xmlStrcmp(cur->name, (const xmlChar *)xmlKeyWords[Pname]) )  {
                           key = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
                           if(strlen( ( const char *)key) > 0 ) {
                               sprintf(argName,"%s",key);
                           } else { argName[0]='\0'; }
                           i++;      
                     }
                     cur = cur->next;

                     if ( !xmlStrcmp(cur->name, (const xmlChar *)xmlKeyWords[Pvalue]) )  {
                           key = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
                           if( strlen( ( const char *)key) > 0 ) {
                               sprintf(argData,"%s",key);
                           } else { argData[0]='\0';}
                           i++;
                     }
                     
                     if(i == 2) {
                          // ---------- Check Over Flow 28 jul 11
                          if(dpkt->numpkt >= MAXDATA) {
                               fprintf(stderr, " ### ERROR : parseData() : Max No. of Argument %d Exceeded \n",dpkt->numpkt);
                               return ERROR ;
                          }
                          if(strlen (argName) > 0) {
                            strcpy(dpkt->prmname[dpkt->numpkt], argName);
                            dpkt->prmname[dpkt->numpkt][strlen(argName)]='\0';
                          }
                          if(strlen(argData) > 0) {
                             strcpy(dpkt->prmvalue[dpkt->numpkt], argData);
                             dpkt->prmvalue[dpkt->numpkt][strlen(argData)]='\0';
                          }
                         fprintf(stderr, "@@@@@@ %d name %s value %s \n",dpkt->numpkt , dpkt->prmname[dpkt->numpkt], dpkt->prmvalue[dpkt->numpkt]);
                          dpkt->numpkt = (int ) dpkt->numpkt + 1  ;  

                     } else { return ERROR; };
                }
                cur = ParentCur->next;
                ParentCur = cur ;
    }

   return 0;
 }

  int parseCmdStore(int xmlKey, char *xmlData, xmlDocPtr doc, xmlNodePtr cur)
  {
      BasicFlds *cmde = (BasicFlds *)&parseCmd.cmdelem ;

      switch(xmlKey)
      {
         case Seq :  cmde->seq = atol(xmlData); break;
         case Id  :  strcpy(cmde->id,xmlData);  break;
         case Name :  strcpy(cmde->cmdname,xmlData);  break;
         case Systemid : strcpy(cmde->subsysid,xmlData);  break;
         case Version :  break;
         case Timestamp : strcpy(cmde->timestamp,xmlData);  break;
         case Priority : break;
         case Timeout :  break;

         case Data    :  parseCmd.data.numpkt = 0 ;
                         return  parseData(doc, cur);
                         break;

         default : return ERROR ;    
      }
  
      return 0 ;
  }

  int parsecommand (xmlDocPtr doc, xmlNodePtr cur)
  {
         int i;
         xmlChar *key;

      cur = cur->xmlChildrenNode;

      while (cur != NULL) 
       {

             for( i= 0; i < TXE ; i++)
               {
                  if ((!xmlStrcmp(cur->name, (const xmlChar *)xmlKeyWords[i])))  
                  {
                       key = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
                       if( parseCmdStore(i,(char *)key,doc,cur) == ERROR ) 
                       {
                           fprintf(stderr, "parseCmdStore() : %s : %s Storing problem ..\n", xmlKeyWords[i],key);
                           return ERROR;
                       }

                       break;
                 }
              }
              cur = cur->next;
       }

     return 0;
 }

 int parseDoc(char *xmlDoc) 
 {
     const char *xmlContent = (const char *)xmlDoc;
    /*
     * this initialize the library and check potential ABI mismatches
     * between the version it was compiled for and the actual shared
     * library used.
     */
    LIBXML_TEST_VERSION

        xmlDocPtr doc;
        xmlNodePtr cur;

//       doc = xmlParseFile(docname);
/* 26-SEP-11 ---Directly reading xmlcontent from memory buffer ( cxmlbuffer of servCMS.c ) in xmlReadMemory */

        doc = xmlReadMemory(xmlContent, strlen(xmlContent), "noname.xml", "UTF-8", 0);


        if (doc == NULL ) 
        {
                fprintf(stderr,"Document not parsed successfully. \n");
                return ERROR;
        }  

        cur = xmlDocGetRootElement(doc);
        if (cur == NULL) 
         {
                fprintf(stderr,"empty document\n");
                xmlFreeDoc(doc);
                return ERROR;
        }


        if (xmlStrcmp(cur->name, (const xmlChar *) "commands")) 
        {
                 fprintf(stderr,"document of the wrong type, root node !=commands");
                 xmlFreeDoc(doc);
                 return ERROR;
        }
        cur = cur->xmlChildrenNode;

        while (cur != NULL) 
        {
            if ((!xmlStrcmp(cur->name, (const xmlChar *)"command")))
             {
                if ( parsecommand (doc, cur) == ERROR) { xmlFree(doc); return ERROR; }; 
             }
             cur = cur->next;
         }

     if(doc != (xmlDocPtr)NULL) {
        xmlFreeDoc(doc);
        xmlCleanupParser();
     }
       
        return 0 ;
 }

