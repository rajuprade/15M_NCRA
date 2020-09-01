
/* MAXDATA 256 DATAELN 64 CHANGED ON 9-SEP-11 */

#ifndef  _REQ_RESP_H_
#define  _REQ_RESP_H_

#define CMS_IP "192.168.3.35"

#define WRPR_PORT  9000    
#define WRPR_IP  "192.168.3.6"
   
#define RESP_PORT  5000
#define RESP_IP  "192.168.3.35"

#define EVNT_PORT 5001
#define EVNT_IP  "192.168.3.35"
  
#define MON_PORT  19999
#define MON_IP   "192.168.3.35"
      
#define SUBSYS_ID "SimulatedSys"   // SimulatedSys if not defined
#define DEVICE_IP "192.168.3.6"


typedef unsigned char  BYTE;
typedef enum { reqPORT, resPORT, evntPORT, monPORT } serverPorts;
typedef enum { PRIORITY=1 } CmdEnum;
typedef enum { WRAPPER=10, INTERMEDIATE=11, FINAL=12, ASYNCH=13, DPLOT=15, MON=99, ALARM=100 } EventEnum ;
typedef enum { SUCCESS=10, FAILED=11, SYNTX=12, INCOMPLETE=13, INVALID=14, UNKNOWNERR=100 } CodeEnum ;

//
// pragam required for the data structure aligment as per the 
// architecture based.
//  Rabbit card is one byte microprocessor
//  Whereas Linux 32 bit OS hence memory alignment required
//  padding for contiguous byte allocation for the float
//  or long bytes.
//


#define XMLBUFSIZE   204800
#define SYNTXLEN 1024

#define  MAXDATA 64   // Modified on 12/09/2011, to make compatible with rabbit //

#define DATALEN 64


#define  MSGLEN 128
#define  CMDSIZE 512

char subSysID[DATALEN];

//char CMD_FLD ;  /* Field separator for device specific command */
//char RESP_FLD ; /* Response field separator */

//
//------------------------< Response Structur >------------------------//
//

#pragma pack(push,16)

#ifdef _DATASERVER_
#define DATAPKT 8096
#define UELEM 4          // ULEM can be one only

typedef struct {
    short numpkt;
    char user[UELEM];
    char prmname[UELEM][DATALEN];
    char prmvalue[UELEM][DATAPKT];
}UserData;

#endif


typedef struct {
    short id;
    short level;
    char description[MSGLEN]; // Desciption for what?
} RespAlarm;

typedef struct {
  short numpkt;
  char prmname[MAXDATA][DATALEN];
  char prmvalue[MAXDATA][DATALEN];
} DataPkt;

  /* Basic Fields Information resued by XMLIB to form XML ACK/NACK/RESPONSE */
typedef struct {
  int seq;                  /* Sequence number of Command */
  float version;
  short priority ;
  short timeout ;
  char subsysid[DATALEN];    /* Later made it integer */
  char username[DATALEN];
  char cmdname[DATALEN]; /* command name at user level */
  char timestamp[DATALEN];
  char id[8];               /* Command ID Device Specific */

} BasicFlds; 
//----------------------------<Resp STructure >-----------------------------//

typedef struct {
    short code;
    short event ;
    char message[MSGLEN];
    RespAlarm alarm;
    DataPkt data;
#ifdef _DATASERVER_
    UserData udata;
#endif
    BasicFlds cmdelem;

 } devResponse ;
//----------------------------<REQ STructure >-----------------------------//

typedef struct
{
  char syntx[SYNTXLEN];
  BasicFlds cmdelem;
  DataPkt data;

} parseCMSCmd ;


#define DataPktSize  sizeof(DataPkt)
#define BasicFldsSize sizeof(BasicFlds)
#define parseCMSCmdSize  sizeof(parseCMSCmd)
#define devResponseSize  sizeof(devResponse)

#pragma pack(pop)


#endif // END OF _REQ_RESP_H_
