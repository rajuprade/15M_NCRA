///////////////////////////////////////////////////////////////////////////
// PROJECT           : SUBSYSTEM SERVER
// File              : SOCKCOMMN.H
// Author            :
// Version           :
// Last Modification : 01-02-2011
// Reason            :
///////////////////////////////////////////////////////////////////////////
#include "ioenum.h"
#ifndef _SOCKCOMMN_H_
#define _SOCKCOMMN_H_
typedef unsigned char BYTE;

#define SERV_PORT 4224

#define   NO_OF_TASKES    6
#define   TOTAL_BUFF      20

#define  cmd_id    1
#define  event_id  2
#define  data_id   3


struct com_buf_typ
{
    BYTE     data[256];
    BYTE     length;
    BYTE     src_task_id;
    BYTE     des_task_id;
    struct com_buf_typ *next;

};

typedef struct com_buf_typ *com_buf_ptr;

typedef struct
{
    com_buf_ptr  hd;
    com_buf_ptr  tl;

}frameq;

extern int connfd;

extern void send_nak(BYTE err_code);
extern void tx_mc(BYTE inv_code);
extern void rx_mc(void);
extern void register_task_in(BYTE tsk_no);
extern com_buf_ptr get_free_buff(void);
extern com_buf_ptr get_from_confq(BYTE tsk_id);
extern com_buf_ptr get_from_indq(BYTE tsk_id);
extern void put_in_req(com_buf_ptr ptr);
extern void put_free_buff(com_buf_ptr ptr);
extern void init_sockcommn_vars(void);
extern void readSock(void);

#endif
