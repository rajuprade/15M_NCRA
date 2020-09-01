#include   <stdio.h>
#include   <string.h>
#include   <stdlib.h>
#include   <libxml/xmlmemory.h>
#include   <libxml/parser.h>
void parseStory (xmlDocPtr doc, xmlNodePtr cur) {
         xmlChar *key;
        // char  *buffer = malloc(20);
         cur = cur->xmlChildrenNode;
         while (cur != NULL) {
              if ((!xmlStrcmp(cur->name, (const xmlChar *)"id"))) {
                      key = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
                      printf("ID: %s\n", key);
                    /*  strcpy(buffer, (char *)key);
                      printf("Author: %s\n", buffer); */
                      xmlFree(key);
                  }
  if ((!xmlStrcmp(cur->name, (const xmlChar *)"data"))) {
                      key = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
                      printf("data: %s\n", key);
                      xmlFree(key);
               }
           if ((!xmlStrcmp(cur->name, (const xmlChar *)"keyword"))) {
                      key = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
                      printf("keyword: %s\n", key);
                      xmlFree(key);
               }

  if ((!xmlStrcmp(cur->name, (const xmlChar *)"headline"))) {
                      key = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
                      printf("headline: %s\n", key);
                      xmlFree(key);
               }
  if ((!xmlStrcmp(cur->name, (const xmlChar *)"para"))) {
                      key = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
                      printf("para: %s\n", key);
                      xmlFree(key);
               }
         cur = cur->next;
         }
     return;
}
static void
parseDoc(char *docname) {
                       
        xmlDocPtr doc;
        xmlNodePtr cur;
        doc = xmlParseFile(docname);
        if (doc == NULL ) {
                fprintf(stderr,"Document not parsed successfully. \n");
                return;
        }
        cur = xmlDocGetRootElement(doc);
        if (cur == NULL) {
                fprintf(stderr,"empty document\n");
                xmlFreeDoc(doc);
                return;
        }
        if (xmlStrcmp(cur->name, (const xmlChar *) "mcm")) {
                fprintf(stderr,"document of the wrong type, root node != story");
                xmlFreeDoc(doc);
                return;
        }
        cur = cur->xmlChildrenNode;
        while (cur != NULL) {
                if ((!xmlStrcmp(cur->name, (const xmlChar *)"cmd"))){
                          parseStory (doc, cur);
                }
        cur = cur->next;
        }
        xmlFreeDoc(doc);
        return;
}
int
main(int argc, char **argv) {
        char *docname;
        if (argc <= 1) {
                printf("Usage: %s docname\n", argv[0]);
                return(0);
        }
        docname = argv[1];
        parseDoc (docname);
        return (1);
}
