#include 	<time.h>
/*------------------------------DEFINE ------------------------------------*/
#define		OK		0
#define		ERR		-1
#define		NOOFPAT		4
#define 	MAXRETRIES	3 
#define 	MINROWS		25
#define 	MINCOLS   	80
#define 	NAMELEN   	80
#define		DISPERRLOG	"./disp.err"
#define		ABCEVENT	"./abc.event"
#define		MAXINPBUFF	200
#define 	VERS          '|'  
#define 	HORS	     '-' 
#define		MAXARGS         270	/*9:9:97 increased from 256 for LO mon event*/
#define		MAXDEBUG        50
#define		MAXBUFFERSIZE	4000 /*16:9:97 */
#define		LARGEIPCDELAY	100
#define		DISPINITERR	2
#define		MALLOCERR	3
#define		FILEERR		4
#define		DEBUGLOG	1
#define		DEBUGNOLOG	2
#define		DEBUGALL	3
#define		NODEBUG		4
#define		DEBUGSERVO	5
#define		DEBUGNOSERVO	6
#define		DEBUGMCM	7
#define		DEBUGNOMCM	8
#define		MCMDEFA		0
#define		ABCDEFA		0
#define		MCMCHANDEFA	22
#define		INPID		0x3c
#define		COMHID		0x20
#define		MAXINPSIZE	256
#define		LEN_SERVO_REAL  10
#define		LEN_SERVO_SHORT_REAL  5
#define		LEN_SERVO_VEL  	4
#define		ABC_TIME_LEN	10
#define		WINDEFA		5
#define		SHMKEY		69
#define		PACKETLG	"/home/online/data/packet.log"
#define		COMHDELAY	7
#define		TASKSTREAM	1
#define		TASKFILE	2
#define		TASKDEBUG	3
#define		TASKSUN1E	4
#define		TWOPOWEREIGHT	256
#define		MESGPRIOR	'1'
#define		SCODELEN	10
#define		MAXDMESG	50	
#define		TALKMCM		15
#define		CMDMONID	33
#define		KERN_ID		34/*18:7:95*/
#define 	UCHAR		unsigned char
#define		SITE_NAME	"khodad"
#define		LATITUDE	"19d6'"
#define		LONGITUDE	"-74d03'"
#define		TIME_ZONE	-5.5
/***********definition for FPS*********/
#define Pcal 270 /*calibrated position is assumed to be at 270 deg for feed system. If its changed to 271 or 272 ...etc this Pcal should be changed accordingly*/
/********definition of subac *******/

#define		program_id_bit	0x1
#define		state_bit	0x2
#define		tol_az_bit	0x4
#define		tol_el_bit	0x8
#define		time_ist_bit	0x10
#define		source_bit	0x20
#define		ra_target_bit	0x0040
#define		dec_target_bit	0x0080
#define		az_target_bit	0x0100
#define		el_target_bit	0x0200
#define		no_ant_bit	0x0400
#define		ant_id_bit	0x0800
#define		az_error_bit	0x1000
#define		el_error_bit	0x2000
#define		status_bit	0x4000

/*********definitions for subac over*****/


/*********definitions for cmd monitor****/

#define comh_ofset 0
#define abc_ofset 1
#define servo_ofset 31
#define mcm_ofset 61
#define fps_ofset 91
#define trak_ofset 121

/*21:6:95 these ofset nos will be used in forming cmd monitor packet for unixhub*/

/*********definitions for cmd monitor over ****/

#define	SETIDLE "MCM: IDLE MODE SET ."
#define	SETSCAN "MCM: SCAN MODE SET ."
#define	SETAMSK "MCM: ANAL MASK SET ."
#define	SETDM16 "MCM: DM16 MASK SET ."
#define	SETDM32 "MCM: DM32 MASK SET ."
#define	REDAMSK "MCM: ANAL MASK READ."
#define	REDDM16 "MCM: DM16 MASK READ."
#define	REDDM32 "MCM: DM32 MASK READ."
#define	REDMCMM "MCM: MCM  MODE READ."
#define	REDMCMV "MCM: MCM  VERS READ."
#define	MCMDEBU "MCM: MCM  DEBU READ."

#include 	"online.h"
typedef  struct { long type;char buff[256];} msgtag;

int     Abc_First_Pkt( ONLINE *, UCHAR *, int *, ABC *);
void 	Form_Servo_Err_Mesg( ONLINE *, ABC *, char * , int );
void	Get_DateTime( ONLINE * );
int 	Get_Field(UCHAR *,int ,char *,int,UCHAR,int);
int 	Packet_Decode( ONLINE *, UCHAR * );
int     Parse_Logical_Pkt( ONLINE *, UCHAR *, int *, int ,int );
int	Parse_Abc( ONLINE *, ABC *,UCHAR *, int *, int );
void    Parse_Fps_Comm_Err( ONLINE  *,ABC *, FPS *) ;
void    Parse_Fps_First_Log( FPS*, UCHAR *, int * );
int     Parse_Fps_Log( ONLINE *, FPS *,  int , UCHAR *, int *,int);
void	Parse_Mcm_Comm_Err( ONLINE *, ABC *, MCM *);
int 	Parse_Mcm_Log( ONLINE *, ABC * , MCM * , int , UCHAR *, int *);
int	Parse_Mcm_Status( ONLINE *, ABC *);
int	Process_Abc( ONLINE *, ABC * , UCHAR *, int *, int  );
int     Process_Comh( ONLINE *, UCHAR *, int *, int) ;
void    Process_Fps( ONLINE  *, ABC *,  UCHAR *, int *pos );
int	Process_Inp( ONLINE *, UCHAR *, int * , int );
int	Process_Mcm( ONLINE *, ABC *, int ,  UCHAR *, int *i , int  );
int 	Process_Servo( ONLINE *, ABC *, UCHAR *, int *, int );
int	Debug_Print(char *, int , char * , UCHAR * , int );
int	Parse_Str_Sec(char*);
float 	form_Fps_angle(unsigned int);
void    Calculate_Walsh_Pattern(MCM_PARA *);
void 	get_channel_map(unsigned char *,unsigned char *);
/*	dispmain  */

void	Form_Abc_Mesg( ABC  *, char *, int , int);
void	Form_Share_Mem_Mesg( ONLINE  *, char *, int );
void	Form_Cmd_Mesg(ONLINE *,UCHAR *,int);
void	Form_Response_Msg(int,ONLINE *,char *);
void    Init_Online_Structure( ONLINE  *,long *);
int	Init_Share_Mem( int , ONLINE **, int);
ONLINE *init_online_shm_(int *,int *,long *);
void form_mapping_(ONLINE *,long *);
int	rem_shm_(void);
void    del_online_shm_(void);
/*ONLINE *init_share_mem_(int *,int *);*/
ONLINE *init_share_mem_(int *,int *,int *);
void    clrstring( char *, int );
void format_time(int,unsigned char *);
void check_monitor_data(ABC *abcarray,int abcnum,int mcmnum);
unsigned char check_state(unsigned char *,unsigned char);
/*	dispmod4 */


int	Debug_Print(char *,int,char *,UCHAR *,int);
int 	Packet_Dump(UCHAR *,int);
void	Print_Err(char *);

void Scct_Msg_Win_Disp(int,UCHAR *,int,int);

int create_msgq_(int );
int  sndmsgq_(msgtag *);
int wrt_scan_hdr_(char *,ScanInfoType *,int *);
#include "libvlba.h"
