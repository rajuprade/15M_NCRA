/* 
 * section:  Tree
 * synopsis: Creates a tree
 * purpose:  Shows how to create document, nodes and dump it to stdout or file.
 * usage:    tree2 <filename>  -Default output: stdout
 * test:     tree2 > tree2.tmp ; diff tree2.tmp tree2.res ; rm tree2.tmp
 * author:   Lucas Brasilino <brasilino@recife.pe.gov.br>
 * copy:     see Copyright for the status of this software
 */

#include <stdio.h>
#include <libxml/parser.h>
#include <libxml/tree.h>

#if defined(LIBXML_TREE_ENABLED) && defined(LIBXML_OUTPUT_ENABLED)

/*
 *To compile this file using gcc you can type
 *gcc `xml2-config --cflags --libs` -o tree2 tree2.c
 */

/* A simple example how to create DOM. Libxml2 automagically 
 * allocates the necessary amount of memory to it.
*/
int
main(int argc, char **argv)
{
    xmlDocPtr doc = NULL;       /* document pointer */
    xmlNodePtr root_node = NULL, node = NULL, node1 = NULL, node2 = NULL;/* node pointers */
    xmlDtdPtr dtd = NULL;       /* DTD pointer */
    char buff[256],  final_xml[1000];
    int i, j;

    LIBXML_TEST_VERSION;

    /* 
     * Creates a new document, a node and set it as a root node
     */
    doc = xmlNewDoc(BAD_CAST "1.0");
    root_node = xmlNewNode(NULL, BAD_CAST "responses");
    xmlDocSetRootElement(doc, root_node);

    /*
     * Creates a DTD declaration. Isn't mandatory. 
     */
    dtd = xmlCreateIntSubset(doc, BAD_CAST "responses", NULL, BAD_CAST "tree2.dtd");

    /* 
     * xmlNewChild() creates a new node, which is "attached" as child node
     * of root_node node. 
     */
    xmlNewChild(root_node, NULL, BAD_CAST "timestamp",
                BAD_CAST "123456789");
    /* 
     * The same as above, but the new child node doesn't have a content 
     */
   // xmlNewChild(root_node, NULL, BAD_CAST "response", NULL);

    /* 
     * xmlNewProp() creates attributes, which is "attached" to an node.
     * It returns xmlAttrPtr, which isn't used here.
     */
    node = xmlNewNode(NULL, BAD_CAST "response");

    xmlAddChild(root_node, node);
    
    xmlNewChild(node, NULL, BAD_CAST "seq",
		BAD_CAST "123");

    xmlNewChild(node, NULL, BAD_CAST "id",
                BAD_CAST "01");
    xmlNewChild(node, NULL, BAD_CAST "name",
                BAD_CAST "SIGCON");
    xmlNewChild(node, NULL, BAD_CAST "systemid",
			    BAD_CAST "1");
    xmlNewChild(node, NULL, BAD_CAST "code",
                BAD_CAST "10");
    xmlNewChild(node, NULL, BAD_CAST "event",
			    BAD_CAST "10");
    

    node1 = xmlNewNode(NULL, BAD_CAST "data");

    xmlAddChild(node, node1);

    for(i=0;i<6;i++)
    {
      node2 = xmlNewNode(NULL, BAD_CAST "param");
      
      xmlAddChild(node1, node2);
      sprintf(buff,"val%d",i);
      xmlNewChild(node2, NULL, BAD_CAST "name",
		  BAD_CAST buff);
      xmlNewChild(node2, NULL, BAD_CAST "value",
	          BAD_CAST buff);
    }
    
     /* 
     * Dumping document to stdio or file
     */
  //  xmlSaveFormatFileEnc(argc > 1 ? argv[1] : "-", doc, "UTF-8", 1);

  /*** Dumping the Doc file to a RESPONSE.xml file *****/
     xmlSaveFormatFileEnc("/home/teleset/Desktop/RESPONSE.xml",doc, "UTF-8", 1);
  //  strcpy(final_xml,"RESPONSE.xml");
    //printf("I am printing the document ----> %s\n", final_xml);
    // strcpy(final_xml,(char) doc);
   
   //xmlSaveFormatFileEnc((Response.xml): "-", doc, "UTF-8", 1);
  // printf("I am printing the document ----> %s\n",doc);

    /*free the document */
    xmlFreeDoc(doc);

    /*
     *Free the global variables that may
     *have been allocated by the parser.
     */
    xmlCleanupParser();

    /*
     * this is to debug memory for regression tests
     */
    xmlMemoryDump();
    return(0);
}
#else
int main(void) {
    fprintf(stderr, "tree support not compiled in\n");
    exit(1);
}
#endif
