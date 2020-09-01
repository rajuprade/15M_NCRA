
//#include "invokeWrapper.h"
#include <stdio.h>
#include "handleQue.h"
#include<strings.h>
//#include "xmlParse.h"
//#include "wrapperCom.h"
//#include "consumCMS.h"


//
// store data items in the queue
//
xmlQueue xmlQ ;


void q_store(parseCMSCmd iQelmnt )
{
  if (xmlQ.store == MAXQUE ) {
    fprintf(stderr, "\nList is full!");
    return;
  }

  if(xmlQ.store==xmlQ.retrieve)
  {
    xmlQ.store = 0; xmlQ.retrieve = 0;
  }
    bzero(&xmlQ.qCMSCmd[xmlQ.store], parseCMSCmdSize);
    xmlQ.qCMSCmd[xmlQ.store] = iQelmnt ; 
  // printCmsStruct( (parseCMSCmd *) &xmlQ.qCMSCmd[xmlQ.store]);
    xmlQ.store++;  // point to next available storage position in queue[]
    fprintf(stderr, " e_store End %d \n", xmlQ.store);
}

parseCMSCmd * q_retrieve(int indx)
{

  fprintf(stderr, "q_retrieve() %d structureSize %d \n",indx, sizeof ((parseCMSCmd *) &xmlQ.qCMSCmd[indx]) );
 //printCmsStruct( (parseCMSCmd *) &xmlQ.qCMSCmd[indx]);
  return((parseCMSCmd *) &xmlQ.qCMSCmd[indx]); 
}



/*
void q_delete(void)
{
}
*/
