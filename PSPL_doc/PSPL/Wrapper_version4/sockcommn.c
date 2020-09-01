//////////////////////////////////////////////////////////////////////////
// PROJECT           : GMRT
// File              : SOCKCOMMN.C
// Author            :
// Version           :
// Last Modification : 01-02-2011
// Reason            :  
///////////////////////////////////////////////////////////////////////////
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <malloc.h>
#include "ioenum.h"
#include "sockcommn.h"
#include "eventdef.h"

rxm_stts  rxm_stt;
txm_stts  txm_stt;

frameq  ind_frameq[NO_OF_TASKES];
frameq  conf_frameq[NO_OF_TASKES];
frameq  req_frameq;

struct com_buf_typ  free_pool_block[TOTAL_BUFF];

com_buf_ptr  rx_buff,tx_buff;
com_buf_ptr  free_buff_pool[TOTAL_BUFF];
BYTE  rxd_char[256];
BYTE  txd_char[512];
BYTE  rxd_char_hd,rxd_char_tl;
BYTE txd_char_len;

BYTE  free_pool_indx;
BYTE  last_resp,rx_bcc,rx_indx;
BYTE  act_tsk_lst[NO_OF_TASKES];
BYTE  no_buff;

extern int connfd;

void register_task_in(BYTE tsk_no)
{

  act_tsk_lst[tsk_no]= 1;
}

void put_free_buff(com_buf_ptr ptr)
{
  free_pool_indx++;
  free_buff_pool[free_pool_indx] = ptr;
  no_buff = 0;
}


com_buf_ptr get_free_buff(void)
{
  if (free_pool_indx == 0)
  {
    return(NULL);
  }
  else
    return(free_buff_pool[free_pool_indx--]);
}

void put_in_req(com_buf_ptr ptr)
{
  if (req_frameq.hd == NULL)
    req_frameq.hd = ptr;
  else req_frameq.tl->next = ptr;
  req_frameq.tl = ptr;
  req_frameq.tl->next= NULL;
  if (txm_stt == TXM_FREE)
    //printf("CALLING TX_MC(0)");
     tx_mc(0);
}

com_buf_ptr get_from_indq(BYTE tsk_id)
{

 com_buf_ptr tptr;
  if (ind_frameq[tsk_id].hd != NULL)
  {
    tptr = ind_frameq[tsk_id].hd;
    ind_frameq[tsk_id].hd = ind_frameq[tsk_id].hd->next;  
    return(tptr);
  }
  else
    return (NULL);
}


com_buf_ptr get_from_confq(BYTE tsk_id)
{
  com_buf_ptr tptr;
  
  if (conf_frameq[tsk_id].hd != NULL)
  {
    tptr = conf_frameq[tsk_id].hd;
    conf_frameq[tsk_id].hd=conf_frameq[tsk_id].hd->next;
    return(tptr);
  }
  else 
    return (NULL);
}


void compile(void)
{
  int i;
  BYTE b,j,bcc;
  
  i=0;
  
  b = tx_buff->length;
  txd_char[i++] = tx_buff->src_task_id;
  txd_char[i++] = tx_buff->des_task_id;
  
  for (j=0;j<b;j++)
  {
    txd_char[i++] = tx_buff->data[j];
  }
  txd_char_len = i;
  for (j=0;j<i;j++)
    printf(" ( %02x ) ",txd_char[j]);
 
}

void tx_mc(BYTE inv_code)
{
  //printf("ENtered TX_MC");
BYTE b;
BOOL done;

  done = false;
  while(!done)
  {
     switch (txm_stt)
       {
           case TXM_FREE:if (req_frameq.hd== NULL)
	                     done = true;
	 	         else 
                             txm_stt= IDLE;
		         break;

           case IDLE:  if (req_frameq.hd== NULL) 
                            txm_stt = TXM_FREE;
		       else
		         {
		               tx_buff = req_frameq.hd;
			       compile();
			       //printf("{%02x %02x %02x %s} ",tx_buff->src_task_id,tx_buff->des_task_id,tx_buff->length,tx_buff->data);
		               req_frameq.hd = req_frameq.hd->next;
		               txm_stt = XMIT;
                         }
                      break;

           case XMIT:    txm_stt = TXM_FREE;
	     	         done = true;
			 printf("\n\n\t\tConnected id  %d\n\n",(int *)connected);
		         b = send(connected,txd_char,txd_char_len,0);

			 printf("\nNo of bytes written: %d\n",b);

			 if(b < 0 )
			 {
		             printf("error writing to socket");
			     close(connected);
			     exit(1);
			 }
                         break;
      }
  }
}

void readSock(void)
{
  int i,n;
  
  n = recv(connected,rxd_char,sizeof(rxd_char),0);
  //printf("no of bytes read : %d\n",n);
  
  if(n < 0 )
  {
    printf("error reading to socket");
    close(connected);
    exit(1);
  }
  else
    
    //printf(" RXD CHAR : %d",strlen(rxd_char));
  for(i=0;i<strlen(rxd_char);i++)
    printf(" %02x ",rxd_char[i]);
  
}

void rx_mc()
{
  BOOL done;
  int i,j;
  
  i=0;
  
  readSock();
  done =false;
  while(!done)
  {
    switch (rxm_stt)
    {
      
      case GET_SRC_ID: 
                       rx_buff->src_task_id = rxd_char[i++];
                       rxm_stt = GET_DES_ID;
                       break;
      case GET_DES_ID: 
                       rx_buff->des_task_id = rxd_char[i++];
                       rxm_stt = ASMBL;
                       break;
      
      case ASMBL:      
                       //printf(" \n RXD CHAR : %d\n",strlen(rxd_char));
                       for(i=2;i<strlen(rxd_char);i++)
	                     rx_buff->data[rx_indx++]=rxd_char[i];
                       rx_buff->length=rx_indx;
                       if (ind_frameq[rx_buff->des_task_id].hd == NULL)
	                           ind_frameq[rx_buff->des_task_id].hd= rx_buff;
                       else
	                           ind_frameq[rx_buff->des_task_id].tl->next= rx_buff;
                       ind_frameq[rx_buff->des_task_id].tl= rx_buff;
                       ind_frameq[rx_buff->des_task_id].tl->next= NULL;
                       rx_buff = get_free_buff();
                       if(rx_buff == NULL)
	                    no_buff = 1;
                       done = true;
                      rxm_stt = GET_SRC_ID;
                      break;
      
    }
  }
}


void init_sockcommn_vars(void)
{
BYTE b,i;

  
  for (i=0;  i < TOTAL_BUFF; i++)
     free_buff_pool[i]= &free_pool_block[i];
  no_buff=0;
  rx_buff = free_buff_pool[TOTAL_BUFF-1];
  for (b=0; b<NO_OF_TASKES-1; b++)
  {
    ind_frameq[b].hd = NULL;
    ind_frameq[b].tl = NULL;
  }
  for (b=0; b<NO_OF_TASKES-1; b++)
  {
    conf_frameq[b].hd = NULL;
    conf_frameq[b].tl = NULL;
    act_tsk_lst[b] = 0;
  }
  req_frameq.hd = NULL;
  req_frameq.tl = NULL;
  free_pool_indx = TOTAL_BUFF-2;
  txm_stt = TXM_FREE;

  rxm_stt = GET_SRC_ID;
}


