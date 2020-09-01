/********* 
 SerCMS.C ----> Log file code included by Raj on 18/07/2011.
 New LIB xml code to parse the xml file is also included but it is giving some I/O error.

***********/


#include "invokeWrapper.h"
#include "wrapperCom.h"
#include "handleQue.h"
#include "xmlParse.h"
#include <libxml/xmlreader.h>
#include   <libxml/xmlmemory.h>
#include   <libxml/parser.h>
#include <string.h>   //  // used for LOG generation
#include <time.h>     // used for LOG generation

#ifdef LIBXML_READER_ENABLED

void parsedata( xmlDocPtr,xmlNodePtr);
void parseparam( xmlDocPtr,xmlNodePtr);

extern pthread_mutex_t mutex;// mutex
extern pthread_mutex_t fmutex;// mutex for file
extern pthread_mutex_t Rmutex;// mutex for file
extern pid_t  current_pid;

extern pthread_t *thread; // pointer for a Consumer Task
extern pthread_t *Thread; // pointer for the Client tasks

// The Thread Task for All Clients

char *recvbuffer ;
// Working code is below 
 static void processNode(xmlTextReaderPtr reader) 
{
    const xmlChar *name,*value;
    char *str =(char *)malloc(sizeof(char)*4096);
     name = xmlTextReaderConstName(reader);
   
    if(xmlTextReaderHasValue(reader))
    {       
      value = xmlTextReaderConstValue(reader);
           // strcpy(str,value);                  // declared a char pointer variable to store separate cmds...
            printf("%s \n",value);
     // strcpy (seq,(long)value);
     q_store(value);
  
    
     } 
  
} 
// This process node print the empty nodes also
/*
static void processNode(xmlTextReaderPtr reader) 
{
    const xmlChar *name, *value;

    name = xmlTextReaderConstName(reader);
    if (name == NULL)
	name = BAD_CAST "--";

    value = xmlTextReaderConstValue(reader);

    printf("%d %d %s %d %d", 
	    xmlTextReaderDepth(reader),
	    xmlTextReaderNodeType(reader),
	    name,
	    xmlTextReaderIsEmptyElement(reader),
	    xmlTextReaderHasValue(reader));
    if (value == NULL)
	printf("\n");
    else {
        if (xmlStrlen(value) > 40)
            printf(" %.40s...\n", value);
        else
	    printf(" %s\n", value);
    }
} */
   //  name = xmlTextReaderConstName(reader);
  //  strcpy(str,name);                  // declared a char pointer variable to store separate cmds...
   //printf("%s  \n",name);
 /*  if (!(xmlStrcmp(name, (const xmlChar *) "name")))
  {
     value = xmlTextReaderConstValue(reader);
      printf("{ %s %s}\n",name,value);
    } */
 
// For the time begin 
 /*  if(xmlTextReaderHasValue(reader))
    {
       
      value = xmlTextReaderConstValue(reader);
      
     // strcpy(str,value);                  // declared a char pointer variable to store separate cmds...
      //printf("%s %s \n",name,value);
      q_store(value);
    //  printf("%s\n \n",str);
    
     } 
  } */
  
  
  static void streamBuffer(char *recvbuffer)
  {
    xmlTextReaderPtr reader;
    int ret;
    
    reader = xmlReaderForMemory(recvbuffer,strlen(recvbuffer),NULL,NULL,XML_PARSE_NOBLANKS);
    if (reader != NULL)
    {
      ret = xmlTextReaderRead(reader);
      while (ret == 1)
      {
	//printf("%d",ret);
	processNode(reader);
	ret = xmlTextReaderRead(reader);
      }
      xmlFreeTextReader(reader);
      if (ret != 0)
      {
	fprintf(stderr, "failed to parse the buffer\n");
      }
    }
    else
    {
      fprintf(stderr, "Unable to access buffer \n");
    }
  }
  
  
  void parseXmlBuff(recvbuffer)
  {
    
    char  cmdbuf[50][50], tmp[1024];
    char *fldsep;
    
    if( ( fldsep = ( char * ) getenv("CMD_FLD")) == NULL ) {
	  fldsep=" ";
	}
	LIBXML_TEST_VERSION
	
	
	streamBuffer(recvbuffer);
	xmlCleanupParser();
	xmlMemoryDump();
	
  }
  #endif


// New LIB XML code..

void parsecommand (xmlDocPtr doc, xmlNodePtr cur) {
         xmlChar *key;
         char  *buffer = malloc(20);
         cur = cur->xmlChildrenNode;
         while (cur != NULL) 
       {
              if ((!xmlStrcmp(cur->name, (const xmlChar *)"seq"))) 
                  {
                      key = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
                      printf("SEQ: %s\n", key);
                     strcpy(buffer, (char *)key);
                      printf("SEQUENCE ID  : %s\n", buffer); 
                      xmlFree(key);
                  }
  if ((!xmlStrcmp(cur->name, (const xmlChar *)"id"))) 
              {
                      key = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
                      printf("ID: %s\n", key);
                      xmlFree(key);
               }
           if ((!xmlStrcmp(cur->name, (const xmlChar *)"name"))) 
              {
                      key = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
                      printf("NAME: %s\n", key);
                      xmlFree(key);
               }

  if ((!xmlStrcmp(cur->name, (const xmlChar *)"systemid")))
              {
                      key = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
                      printf("systemid: %s\n", key);
                      xmlFree(key);
               }
  if ((!xmlStrcmp(cur->name, (const xmlChar *)"timestamp"))) 
               {
                      key = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
                      printf("Timestamp: %s\n", key);
                      xmlFree(key);
                }
  if ((!xmlStrcmp(cur->name, (const xmlChar *)"data"))) 
               {
                     parsedata(doc, cur);
                }
                  cur = cur->next;
         }
     return;
}

void parsedata( xmlDocPtr doc, xmlNodePtr cur) 
{
    cur = cur->xmlChildrenNode;
          while (cur != NULL) 
            {
                      if ((!xmlStrcmp(cur->name, (const xmlChar *)"param")))
                    {
                              printf("We are Having following paramateres\n");  
                              parseparam(doc, cur);
                    }
                    cur = cur->next;
         }
   return;
}

void parseparam (xmlDocPtr doc, xmlNodePtr cur) 
{
         xmlChar *key;
         cur = cur->xmlChildrenNode;
                      while (cur != NULL) 
                         {   
                                            //printf("current node is %d\n",(int)cur);
                                               if ((!xmlStrcmp(cur->name, (const xmlChar *)"name"))) 
                                                  {
                                                          key = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
                                                           printf("NAME: %s\n", key);
                                                           xmlFree(key);
                                                    }
                                            if ((!xmlStrcmp(cur->name, (const xmlChar *)"value"))) 
                                                {
                                                       key = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
                                                      printf("value: %s\n", key);
                                                      xmlFree(key);
                                                  }
                                            cur = cur->next;
                                  
                                  } 
         return; 
} 

static void parseDoc(char *docname) 
{
                  
        xmlDocPtr doc;
        xmlNodePtr cur;
        doc = xmlParseFile(docname);
        if (doc == NULL ) 
          {
                fprintf(stderr,"Document not parsed successfully. \n");
                return;
          }
        cur = xmlDocGetRootElement(doc);
        if (cur == NULL) 
           {
                fprintf(stderr,"empty document\n");
                xmlFreeDoc(doc);
                return;
          }
        if (xmlStrcmp(cur->name, (const xmlChar *) "commands")) 
              {
                 fprintf(stderr,"document of the wrong type, root node !=commands");
                 xmlFreeDoc(doc);
                 return;
              }
          cur = cur->xmlChildrenNode;
          while (cur != NULL) 
            {
                      if ((!xmlStrcmp(cur->name, (const xmlChar *)"command")))
                    {
                          parsecommand (doc, cur);
                    }
                    cur = cur->next;
         }
       xmlFreeDoc(doc);
        return;
}

void service(int *connected)
{
  int bytes_recieved,length;
  
    FILE *fp,*f;
    char stuff[25],filename[50]="/home/teleset/Desktop/Wrapper/Sentinel_";
    char docname[50]="/home/teleset/Desktop/Wrapper/command.xml";
    char stamp1[26], stamp2[12];
     int i;
    time_t t1;
    time(&t1);
  ctime_r(&t1, stamp1);
  if (stamp1[8] == ' ') stamp2[0] = '0';
  else stamp2[0] = stamp1[8];
  stamp2[1] = stamp1[9];
  for (i=0;i<3;i++) stamp2[i+2] = stamp1[i+4];
  for (i=0;i<2;i++) stamp2[i+5] = stamp1[i+11];
  stamp2[7] = 'h';
  stamp2[8] = '_'; 
  stamp2[9]= stamp1[22];
  stamp2[10]=stamp1[23];
  stamp2[11] = '\0'; 
   strcat(filename,stamp2);
   
   fp = fopen(filename,"a+");                        /* open for writing */
   f = fopen(docname,"w");
// char *buffer;
 char respheader[]=(" <responses><response>");
 char respfooter[]=("</response></responses><RESP_END>");
 char wrapperACK[]=("<event>10</event><code>10</code>");
 char *response;
 //char *tempstr;
 
 
// tempstr=(char *)malloc(sizeof(char)*4096);
 response=(char *)malloc(sizeof(char)*4096);

 recvbuffer=(char *)malloc(sizeof(char)*4096);

 fprintf(stderr,"\n\n Current Task no %d\n\n",*connected);

  bytes_recieved = recv(*connected,recvbuffer,XMLBUFSIZE,0); //save the data sent by client
  recvbuffer[bytes_recieved] = '\0';
fprintf(fp," Starting TIME is  %s \n", stamp1);
 fprintf(fp,"%s\n", recvbuffer);
 fprintf(f,"%s\n", recvbuffer);
 puts(recvbuffer); // It print the whole XML file sent from CMS client.
   fflush(stdout);
                                                    
      fprintf(fp," Closing TIME is  %s \n", stamp1);
 fclose(fp); /* close the file before ending program */
 fclose(f);
  /* length=strlen(recvbuffer);

				    for(i=0;i<length;i++)

				    {
					// printf("%c",recvbuffer[i]);
                                        fprintf(f,"  %c \n", recvbuffer[i]);
				     } */
 fprintf(stderr,"\nParsing XML data....\n\n");

//parseXmlBuff(recvbuffer);
 parseDoc(docname);

  strcpy(response,respheader);
puts(response);
//tempstr = get_xmlheader(recvbuffer);
//strcat(response,tempstr);
strcat(response,wrapperACK);
strcat(response,respfooter);

//fprintf(stderr," response %s \n",response);

fprintf(stderr,"\n\nCOMPLETE COMMAND IS RECEIVED BY WRAPPER...");
send(*connected,response,strlen(response), 0); //        send the RESPONSE back
fprintf(stderr,"\n\n PUTTING DATA IN QUEUE... ");

//  Lock the mutex
pthread_mutex_lock(&mutex);
//q_store(recvbuffer);  // Storing the Data successfully in the queue....
fprintf(stderr,"\n\nDATA STORED IN QUEUE SUCCESSFULLY..\nClosing Seccion %d",*connected);
//   Unlock the mutex
pthread_mutex_unlock(&mutex);

 //free(response);
 free(recvbuffer);
 
 pthread_exit(0); /* exit */

}
