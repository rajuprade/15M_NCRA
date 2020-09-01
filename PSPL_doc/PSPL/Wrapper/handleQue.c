
#include "invokeWrapper.h"
//#include "wrapperCom.h"
//#include "consumCMS.h"
#include "handleQue.h"

//
// store data items in the queue
//
xmlQueue xmlQ ;

void q_store(char *ptr)
{
  if (xmlQ.store == MAXQUE ) {
    fprintf(stderr, "\nList is full!");
    return;
  }

  if(xmlQ.store==xmlQ.retrieve)
  {
    xmlQ.store = 0; xmlQ.retrieve = 0;
  }
/*
   strncpy(xmlQ.buffer[xmlQ.store], ptr,(XMLBUFSIZE-1));
   xmlQ.buffer[xmlQ.store][strlen(xmlQ.buffer[xmlQ.store][0])]  ='\0';
*/
   strcpy(xmlQ.buffer[xmlQ.store], (char *) ptr);
  // fprintf(stderr, "#### xmlQ.store id [%d] \n", xmlQ.store);
   printf ("DATA stored in the queue at the position  [%d]  is %s \n\n",xmlQ.store,(char *)xmlQ.buffer[xmlQ.store]); // It is now storing the XML file....
   xmlQ.store++;  // point to next available storage position in queue[]
  

}

char* q_retrieve(int indx)
 //char* q_retrieve(char *)
{
  fprintf(stderr, "q_retrieve() %d \n",indx);
   printf(" The q_retrieve contains the %s \n\n", (char *) xmlQ.buffer[indx]);
    return((char *) xmlQ.buffer[indx]);
  //    return ((char *)xmlQ.buffer);
}

//
// delete data at retrieve position
//
/*
void q_delete(void)
{

}
*/
