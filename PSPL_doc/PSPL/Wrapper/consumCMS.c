

#include "invokeWrapper.h"
#include "wrapperCom.h"
#include "consumCMS.h"
#include "handleQue.h"
#include "xmlParse.h"

extern pthread_mutex_t mutex;// mutex
extern pthread_mutex_t fmutex;// mutex for file
extern pthread_mutex_t Rmutex;// mutex for file
extern pid_t  current_pid;

extern pthread_t *thread; // pointer for a Consumer Task
extern pthread_t *Thread; // pointer for the Client tasks

extern int deviceFd ; //  Device descriptor
extern xmlQueue xmlQ ;

int sendSystemPkt(char* ptr, char *devResp)
{
/* com_buf_ptr temp_ptr, test_ptr; */
  int len,count,ix,iy,bytes;
  static char devCmd[1024];  char buff[512];
  ix=0;iy=0;

//  parseXmlCmd(ptr, devCmd);
  fprintf(stderr,"sendSystemPkt() : parseXmlCmd[%d] %s \n", strlen(devCmd), devCmd);

 // send the RESPONSE back
 if( send(deviceFd,(BYTE*)devCmd, strlen((BYTE*)devCmd), 0) < 0) 
  {
      fprintf(stderr, "### Error: sendSystemPkt() Command Failed !!\n");    
      return 1;
  } else if ( (bytes = recv(deviceFd,&buff,4,0)) < 0 ) {
      fprintf(stderr, "### Error : sendSystemPkt() Response not received !!\n");
      return 1;
  } else {
    buff[bytes] = '\0';
    fprintf(stderr, "sendSystemPkt From ServoCLI %x \n ", buff[0]);
    if(formXmlResp(buff,ptr,devResp) ) {
       fprintf(stderr, "### Error : formXmlResp :Pkt err \n");
       return 1;
    }
    fprintf(stderr, "RXXXXXXXXXXXXX formXmlResp() : %s \n", devResp);
   }

  return 0;
}

int sendRespToCMS(char *devResp) 
{
   int respFd ;

   if( (respFd = initRespPortCMS()) == ERROR )  {
     fprintf(stderr, "### Error : sendRespToCMS () Could not connect to CMS ..\n");
     return 1;
   } else if(send(respFd,devResp,strlen(devResp),0) < 0 ) {
       fprintf(stderr, "### Error : sendRespToCMS () Respond not send to CMS ..\n"); 
       return 1;
   }

   return 0 ;
}

void consumer(int* connected)
{
  static char devResp[4096];
  char *resp_ptr;
  printf (" I m in Consumer thread \n \n \n " );
  deviceFd = *connected ;

   while(1)
   {
         int i;
          if ((int) (xmlQ.store) > (int) xmlQ.retrieve) {
            //  Lock the mutex
            pthread_mutex_lock(&mutex);
           // for( i = 0;i < (int)xmlQ.store; i++)
         //   {
            resp_ptr = (char *) q_retrieve((int)xmlQ.retrieve);
             // resp_ptr = (char *) q_retrieve(xmlQ.retrieve);
            fprintf(stderr,"Retriving Data from %d Queue : %s \n",xmlQ.retrieve, resp_ptr);
               write(deviceFd,resp_ptr,strlen( resp_ptr));
        //    if(! sendSystemPkt(resp_ptr,devResp)) {
           //   if( ! sendRespToCMS(devResp) ) {
                xmlQ.retrieve++; /* q_delete function will be here */
            //     fprintf(stderr, " ##### xmlQ.retrieve %d \n", xmlQ.retrieve);
           //    }
          //    }
            //}           
            //  Unlock the mutex
            pthread_mutex_unlock(&mutex);
              fprintf(stderr, " ##### xmlQ store [%d] rertrieve [%d] \n", xmlQ.store, xmlQ.retrieve);
          } 
          usleep(500000);
   }
}
