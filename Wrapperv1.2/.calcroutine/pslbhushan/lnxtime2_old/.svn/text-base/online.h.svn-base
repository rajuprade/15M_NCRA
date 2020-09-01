#include <stdio.h>
#define         MAXCHANNEL      64
#define         MAXCHANNEL_1    65
#define		MAXPROCESS	20
#define         LEN_SERVO_ANG   11
#define         MESG_LEN        80
#define         NO_ABC_MESG     10
#define         MCMCNT          16
#define 	CEBMCMCNT	64
#define         MCMSTATCNT      129			   /* MAX MCMCNT*2 +1 */
#define 	CEBABCID	19 			   
#define         SOMELEN         13
#define         ANTENNACOUNT    31
#define 	CEBABC1_ADDR     0			   /* ABC 1 in CEB has a
							    * fixed adr 0 */
#define 	CEBABC2_ADDR     31			   /* ABC  2 in CEB has a
							    * fixed adr 31 */
#define         ANTENNACOUNT_1  32
#define 	ANTENNACOUNT_3  34
#define         MAX_SUBARRAY    6
#define         NO_MAIN_MESG    10
#define         NO_COMMAND      10
#define         COMMAND_LEN     150
#define 	MAX_HISTORY	150			   /* 150 commands's
							    * summary will be
							    * available in
							    * CMD_HISTORYstruct */
#define 	MAX_HISTORY_1	151			   /* last cmd for locally
							    * gen cmds by cmd
							    * monitor1:2:96 */
#define 	CMD_BYTES	20
#define		ONLINE_VERS	"@(#)online.h 1.69 7/8/96 GMRT"	/* id and date of
								 * online.h */
#define MAX_SOURCES 7					   /* master &user0(sac0) -
							    * user5(sac 5) */
#define MAX_DESTNS 4					   /* abc,servo,mcm,fps */
#define MAX_SOURCES_1 8					   /* last extra src is for
							    * comh */
#define MAX_DESTNS_1 5					   /* last extra dest for
							    * trak */
#define MAX_DAS_SUB 6
#define MAX_LOG_FILE 10 



/* 	define addresses of sources and destins              */

#define ADDR_FIRSTMCM 0
#define ADDR_LASTMCM 13
#define ADDR_FPS  14   
#define ADDR_TALK 15
#define ADDR_SERVO 16
#define ADDR_ABC 17
#define ADDR_COMH 32
#define ADDR_CMDMON 33
#define ADDR_PKTDECODE 47
#define ADDR_UNIXHUB 48
#define ADDR_MASTER 49
#define ADDR_FIRSTUSR 50
#define ADDR_LASTUSR 55
#define ADDR_SUBMON 63
#define ADDR_MASTERSAC 64
#define ADDR_FIRSTSAC 65
#define ADDR_LASTSAC 70
#define ADDR_DASMON 72
#define ADDR_SHMSERV 90
#define ADDR_FIRSTBBMCM 100
#define ADDR_LASTBBMCM 164





typedef struct {
	unsigned char   mcmcommerrors;			   /* yellow & red allerts
							    * indicating cmd in
							    * retransmission or
							    * failure */
	int             errcnt;
	int             cmdfail;
	int             timeout;
	int             chksum;
	unsigned char   mcmcontrolinfo[2];		   /* 2 byte info sent by
							    * mcm, lower byte :
							    * link sts upper byte
							    * no of log packets. */

}               MCM_LINK;

typedef struct {
	char            thresstat[41];			   /* threshold lims char
							    * string */
	unsigned char   thresval[41];			   /* threshold lims set */
	unsigned char   threshold[5];			   /* threshold mask */
	unsigned char   scandata[MAXCHANNEL];		   /* mcms analog channel
							    * data */
	unsigned char   chn_map[MAXCHANNEL_1];		   /* channel map bet
							    * analog mask &
							    * scandata */
	unsigned char   cmd_analogmask[8];		   /* analog mask sent by
							    * command, stored in
							    * process_inp.c */
	unsigned char   analogmask[8];			   /* analog mask stored at
							    * mcm */
	unsigned char   cmd_digitalmask16[2];		   /* dig16 mask sent by
							    * command, stored in
							    * process_inp.c */
	unsigned char   digitalmask16[2];		   /* dig16 mask stored at
							    * mcm */
	unsigned char   cmd_digitalmask32[4];		   /* dig32 mask sent by
							    * command, stored in
							    * process_inp.c */
	unsigned char   digitalmask32[4];		   /* dig32 mask stored at
							    * mcm */
	unsigned char   cmd_digitalmask64[8];		   /* dig64 mask sent by
							    * command, stored in
							    * process_inp.c */
	unsigned char   digitalmask64[8];		   /* dig64  mask stored at
							    * mcm */
	int             walpat1;
	int             walpat2;
	int             walpat3;
	int             walpat4;
	int             walpat5;
}               MCM_PARA;

typedef struct {
	int             packet_no;			   /* seq no of latest mcm
	 					            * pkt */

	unsigned char   id;			           /* mcm addr */
	unsigned char   mcmversion;
	unsigned char   wiringstatus;
	unsigned char   selftestresults;		   /* mcm self test result */
	unsigned char   mode;				   /* scan or idle mode */
	unsigned char   scandatapresent;
	unsigned char   avgfact;			   /* avaraging factor in
							    * mean mode */
	unsigned char   respcode;			   /* mcm's command code */
	unsigned char   subcmd;				   /* mcm's sub command
							    * code */
	unsigned char   state;				   /* monitor state for mcm */
	char            mcmcmd[30];			   /**mcm command string*/
	MCM_LINK        lnk;
	MCM_PARA        para;
}               MCM;

typedef struct {
	unsigned char   fpscommerrors;			   /* mcm communication
							    * errors */
	int             errcnt;
	int             cmdfail;
	int             timeout;
	int             chksum;
	int             resetcnt;
	int             overcurntcnt;
	unsigned char   fpscontrolinfo[2];		   /* mcm control byte */
}               FPS_LINK;

/*    Why are all angles float? array for 4 standard positions */

typedef struct {
	float           encodertp;			   /* encoder count for
							    * turning point */
	unsigned int    rampuptime;			   /* rate at which rps
							    * increases in preset
							    * run or free run */
	unsigned int    rampdowntime;			   /* rate at which rps
							    * decreases in preset
							    * run or free run */
	unsigned int    lowrpmtime;
	float           lowrpmlmt;
	unsigned int    brakecnttime;			   /* the difference in
							    * current pos and
							    * target pos at which
							    * the brakes should be
							    * applied to FPS */
	unsigned int    stoptimcnt;			   /* the rate at which the
							    * rpm decreases after
							    * brakes are applied */
	unsigned int    finetunepwmcnt;			   /* the pwm count for
							    * fine tune mode */
	float           maxpwm;				   /* max val for pwm */
	float           targetpos_cmd;			   /* target pos for fps,
							    * sent by command,
							    * stored in
							    * process_inp.c */
	float           max_angle;
	float           min_angle;
        float           ua0_angle;                          /* gives last encountered
                                                             * UA0 position*/
}               FPS_PARA;

typedef struct {
	int             packet_no;			   /* seq no of latest fps
							    * pkt */
	unsigned char   fpsversion;
        unsigned char   installed_new;                     /* 0=old version 
                                                            * 1=> new version */
	char            status[70];
	unsigned char   wdogreset;
	unsigned char   overcurnt;			   /* 16:8:94 */
	unsigned char   respcode;			   /* fps's command code */
	unsigned char   subcmd;				   /* fps's sub command
							    * code */
/* unsigned char maskcmd; not used anywhere so commented */
	char            fpscmd[50];			   /* fps command string */
	unsigned char   selftestresults;		   /* self test result of
							    * fps */
	unsigned char   mode;				   /* mode of fps */
	float           curnt_rpm;
	float           curnt_pos;			   /* prev called as
							    * encodercnt */
	float           targetpos;
	FPS_LINK	lnk;
	FPS_PARA	para;

}               FPS;

typedef struct {
	float           analog_time;			   /* servo time in read
							    * analog var response */
	float           digital_time;			   /* servo time in read
							    * digital var response */
	float           para_time;			   /* servo time in other
							    * than above 3 commands */
	float           azim_pp;			   /* potentiometer azimuth
							    * position */
	float           elev_pp;			   /* potentiometer
							    * elevation position */
	float           az_tacho1;			   /* azimuth tacho 1 */
	float           az_tacho2;			   /* azimuth tacho 2 */
	float           el_tacho1;			   /* elevation tacho 1 */
	float           el_tacho2;			   /* elevation tacho 2 */
	float           wind_vel_low_limit;		   /* wind velocity low
							    * limit */
	float           wind_vel_high_limit;		   /* wind velocity high
							    * limit */
	float           az_soft_low_limit;		   /* software set low
							    * limit of az */
	float           az_soft_high_limit;		   /* software set high
							    * limit of az */
	float           az_encoder_offset;		   /* set value of az
							    * offset */
	float           az_G11;				   /* g11 */
	float           az_T11;				   /* t11 */
	float           az_T12;				   /* t11 */
	float           az_T13;				   /* t13 */
	float           az_G21;				   /* g21 */
	float           az_T21;				   /* t21 */
	float           az_T22;				   /* t22 */
	float           az_T23;				   /* t23 */
	float           el_soft_low_limit;		   /* software set low
							    * limit of el */
	float           el_soft_high_limit;		   /* software set high
							    * limit of el */
	float           el_encoder_offset;		   /* set value of el
							    * offset */
	float           el_G11;				   /* g11 */
	float           el_T11;				   /* t11 */
	float           el_T12;				   /* t11 */
	float           el_T13;				   /* t13 */
	float           el_G21;				   /* g21 */
	float           el_T21;				   /* t21 */
	float           el_T22;				   /* t22 */
	float           el_T23;				   /* t23 */

}               SERVO_VARS;


typedef struct {
	int             packet_no;			   /* seq no of latest
							    * servo pkt */
	char            version_number[LEN_SERVO_ANG];
	char            station_number[LEN_SERVO_ANG];
	unsigned char   selftest_result[LEN_SERVO_ANG];
	char            servodate[LEN_SERVO_ANG];

	unsigned char   servostatusbyte;		   /* servo status byte
							    * 31:10:94 */
	float           time;				   /* servo time read
							    * angles response */
	float           azim_cp;			   /* current azimuth
							    * position */
	float           azim_tp;			   /* target azimuth
							    * position */
	float           elev_cp;			   /* current elevation
							    * position */
	float           elev_tp;			   /* target elevation
							    * position */
	float           az_motor1;			   /* azimuth motor1
							    * current */
	float           az_motor2;			   /* azimuth motor2
							    * current */
	float           el_motor1;			   /* elevation motor1
							    * current */
	float           el_motor2;			   /* elevation motor2
							    * current */
	float           wind_vel1;			   /* wind monitor 1 */
	float           wind_vel2;			   /* wind monitor 2 */
	float           az_stow_ang;			   /* software set value of
							    * stow angle */
	float           el_stow_ang;			   /* software set value of
							    * stow angle */
	SERVO_VARS      vars;
	unsigned char   servodigitalvar[6];		   /* digital monitor data */
	char            az_state[LEN_SERVO_ANG];	   /* current state of az
							    * axis */
	char            el_state[LEN_SERVO_ANG];	   /* current state of el
							    * axis */
}               SERVO;

typedef struct {
	unsigned char   data[30][16];
	float           time;
	unsigned char   max_states;
}               MCM_MONITOR;

typedef struct {
	float time;
        int noise_cal;
        int rf_stat;
        int wal_stat;
        int sub_band;
        float wf1,wf2;
        float n1,n2,p1,p2;
        float ref1,ref2;
	unsigned char   data[32];
}               FE_MONITOR;

typedef struct {
        float time;
        int sel_band[2];
        int sol_att[2];
        int swap_stat;
        float vp[2];
        float ve[2]; 
        float vrf[2];
        int rf_pow[2];
	unsigned char   data[64];
}               COMMN_MONITOR;

typedef struct {
	int             trk_status;
	long            lat;				   /* latitude of antenna  */
	long            longitude;			   /* longitude of antenna */
	long            sinlat;				   /* sin lat    */
	long            coslat;				   /* cos lat    */
	long            azerr;				   /* az pointing error  */
	long            elerr;				   /* elev pointing error  */
	long            elmax;				   /* software el max limit */
	long            elmin;				   /* software el min limit */
	long            azmax;				   /* software az max limit */
	long            azmin;				   /* software az min limit */
	long            stowpos;			   /* stow position of
							    * antenna */
	long            longcor;			   /* lst offset from ref
							    * pt */

	long            lst0;				   /* lst at time t0       */
	long            t0;				   /* reference time for
							    * lst */
	short           inout;				   /* 0/1 for inner/outer  */
	short           over90;				   /* 0/1 for over/under 90 */
	long            ra0;				   /* ra of source   */
	long            dec0;				   /* dec of source  */
	long            raoff;				   /* ra offset    */
	long            decoff;				   /* dec offset   */
	long            dra;				   /* rate of change of ra */
	long            ddec;				   /* rate of change of dec */
	long            trd0;				   /* reference time   */
	long            azoff;				   /* azimuth offset   */
	long            eloff;				   /* elevation offset */
	long            daz;				   /* rate of change of az */
	long            del;				   /* rate of change of el */
	long            tazel;				   /* reference time */
	long            tmax;				   /* time limit for scan  */

	long            ra;				   /* actual ra    */
	long            dec;				   /* actual dec   */
	long            azflg;				   /* flag for opt az comp */
	short           cdec;				   /* cosdec   */
	short           sdec;				   /* sindec   */
	long            slsd;				   /* sinlat*sindec  */
	long            slcd;				   /* coslat*cosdec  */
	long            clsd;				   /* coslat*sindec  */
	long            clcd;				   /* coslat*cosdec  */

	long            ha;				   /* hour angle of source */
	long            time;				   /* actual time for coord */
	long            lst;				   /* local siderail time  */
	long            az;				   /* azimuth of source  */
	long            elev;				   /* elevation of source  */
	long            offset;
	long            tot_trak_time;			   /* this will be reset to
							    * 0 initially, & will
							    * start incrementing
							    * after loc_trak =1 */
	unsigned char   status;				   /* return value of
							    * getazel25:1:96 this
							    * will be sent as an
							    * abc event */
	long            strt_trak_time;			   /* abc time at which loc
							    * trak started */
        long            delay_trak_time;                   /* delay after which modified ABC will
                                                              resume its normal tracking algo. */

}               TRAK_P;

typedef struct {
	unsigned char   src_no[5];
	unsigned char   tally_cnters;			   /* 30:12:95 whenever
							    * comh aborts abc cmd,
							    * this flag gets set
							    * only if its not
							    * already set. if cmd
							    * monitor finds this
							    * flag set for a
							    * particular abc , it
							    * will send tally
							    * cnters cmd to that
							    * abc */

	int             cmd_cnter;
	unsigned char   cmd_blocked;
	unsigned char   resp_cnter[2];
	unsigned short  tmout_cnter;
	unsigned char   cmd_aborted;


	int             servo_cmd_cnter;
	unsigned char   servo_cmd_blocked;
	unsigned char   servo_resp_cnter[2];		   /* 28:3:95 */
	unsigned short  servo_tmout_cnter;
	unsigned char   servo_cmd_aborted;

	int             loc_cmd_cnter;
	unsigned char   loc_cmd_blocked;
	unsigned char   loc_resp_cnter[2];		   /* 28:3:95 */
	unsigned short  loc_tmout_cnter;
	unsigned char   loc_cmd_aborted;

	int             mcm_cmd_cnter;
	unsigned char   mcm_cmd_blocked;
	unsigned char   mcm_resp_cnter[3];		   /* 28:3:95 */
	unsigned short  mcm_tmout_cnter;
	unsigned char   mcm_cmd_aborted;

	int             fps_cmd_cnter;
	unsigned char   fps_cmd_blocked;
	unsigned char   fps_resp_cnter[2];		   /* 28:3:95 */
	unsigned short  fps_tmout_cnter;
	unsigned char   fps_cmd_aborted;
}               ABC_CMDMON;

typedef struct {
	unsigned char   delaybetmcm;
	unsigned char   cycletime;
	unsigned char   mcmtrantmout;
	unsigned char   mcmrecvtmout;
	unsigned char   servoawaitoutdelay;
	unsigned char   servoinptmout;
	unsigned char   servointbyttmout;
	unsigned char   servoouttmout;
	unsigned char   servocmdperiodicity;
	unsigned char   debug_time;			   /* 4:9:95 */
	unsigned char   monitor_time;			   /* 4:9:95 */
	unsigned char   servointcmddelay;
        unsigned char   flush_evnt;
        unsigned char   trk_dly;
        unsigned char   park_dly;
        unsigned char   wait_before_move;
        unsigned char   wait_after_move;
        unsigned char   wait_after_stop;

}               ABC_PARA;

typedef struct {
	unsigned char   linkstatus;			   /* link status byte
							    * indicating abc to
							    * comh link status,
							    * currently not filled */
	unsigned char   mcmstatusbytes[12];		   /* mcm status bits
							    * indicating
							    * tmout,busy, prev cmd
							    * over status */
	char            statmcm2[MCMSTATCNT];		   /* string containing
							    * above description */

	unsigned short    mcmtimeout;
	unsigned short    mcmchksum;
	unsigned short    abctimeout;
	unsigned short    abcchksum;
	unsigned short   abcservnakcnt;
	unsigned short   abcservenqcnt;
	unsigned short   servabcnakcnt;
	unsigned short   servabcenqcnt;                      /*made 4 err cnters as integers                                                            * 15:10:97*/
	unsigned char   servoresponse; 
	unsigned short    comhtimeout;			   /* for link timeout */
	unsigned short    comhchksumerr;			   /* for link chksum */
	unsigned short    servcmdtmoutcnt;

	unsigned short    ret_link_timeouts;		   /* comh detected abc
							    * timeout i.e ret link
							    * timeouts */

	unsigned short    ret_link_chksums;		   /* comh detected anc
							    * chksum i.e ret link
							    * chksums */
	unsigned short    real_cmds_issued;		   /* comh issued those
							    * many real cmds to abc */
 	unsigned short    real_cmds_aborted;		   /* comh aborted those
							    * many real cmds for a
							    * parti. abc */
	unsigned short    br_cmds_issued;			   /* comh issued those
							    * many br cmds to abc */
	unsigned short    br_cmds_aborted;		   /* comh aborted those
							    * many br cmds for a
							    * parti. abc */
	unsigned short    large_pkt_abc;			   /* abc sent large pkt to
							    * comh */

	unsigned short    abc_not_ready;
	int             totalmcmcmds;
	int             totalservocmds;
	unsigned char   servo_op_cmds_till_abc;
	unsigned char   servo_op_cmds_issued_appln;
	unsigned char   servo_op_cmds_issued_link;
	unsigned char   op_cmds_servo_acked;
	unsigned char   local_cmds_issued_by_abc;
	unsigned char   mcm_op_cmds_till_abc;
	unsigned char   mcm_op_cmds_issued_link;
	unsigned char   abc_op_cmds_till_abc;


}               ABC_LINK;

typedef struct {
	unsigned char   no_of_cmds;			   /* no of abc cmd in comh
							    * Q 13:7:95 */
	unsigned char   head;				   /* abc cmd head cnter in
							    * comh Q */
	unsigned char   tail;				   /* abc cmd tail in comh
							    * Q */
	unsigned char   try_cnt;			   /* abc cmd rexmission
							    * cnt */
	unsigned char   br_try_cnt;			   /* abc br cmd rexmission
							    * cnter */
	unsigned char   real_xmit;			   /* abc cmd real xmit
							    * flag in comh */
	unsigned char   real_rec;			   /* abc cmd tail in comh
							    * Q */
	unsigned char   retry_req;			   /* abc cmd rexmission
							    * cnt */
	unsigned char   broadcast_flag;			   /* abc br cmd rexmission
							    * cnter */


	unsigned char   ringerr1;
	unsigned char   ringerr2;
	unsigned char   ringerr3;
	unsigned char   servo_got_resp_corrected;
	unsigned char   servo_out_free_corrected;
	unsigned char   no_of_cmds_in_servo_localq;
	unsigned char   current_cmd_no_in_localq;
	unsigned char   current_time_no_in_localq;
	unsigned char   servo_localq_blocked;
	unsigned char   generate_servoq_event;
	unsigned char   servoq_time_cnter;
	float           abc_dbg_time;			   /* hh:mm:ss: */
	float           topq_cmd_time;			   /* hh:mm:ss: */
	unsigned char   mcm_grp_head;
	unsigned char   mcm_grp_tail;
	unsigned char   tot_mcm_cmds;
	unsigned char   mcm_cmd_head;
	unsigned char   mcm_cmd_tail;
        unsigned char   crc_err;
        unsigned char   overrun_err;
        unsigned char   tx_underrun;
        unsigned char   rec_tmout;
        unsigned char   abo_detect;
        unsigned char   reset_chip_cnt;
        unsigned char   tot_abc_cmds;


}               ABC_DEBUG;




/*
 * All variables are 2d arrays. The second dimension contains the prev
 * value of the parameter.
 * Status array tells the status of the current cmd executed. It has the follo.
 * convention. 
 * =0 => requested,command accepted and verified =1 => requested and command
 * accepted =2 => requested but command not accepted ( being executed or
 * failed) =3 => requested but command could not be issued
 * 
 */
typedef struct {
	unsigned char   rffeed[2];		      /* [0]=0 feed calib;idle
						       * 1 150 MHz 2 325 MHz 
						       * 3 610/235 MHz 
						       * 4 1420 MHz 
						       * 5 uncalib */
        unsigned int rfbox[2][2];                     /*One Variable for each
						       * pol channel 
						       * 0 nothing connected 
						       * 1 50 MHz 
						       * 2 150 MHz 
						       * 3 235 MHz
						       * 4 325 MHz 
						       * 5 610 MHz 
						       * 6 1060 MHz 
						       * 7 1170 MHz
						       * 8 1280 MHz
						       * 9 1390 MHz */

	unsigned char   rfnoise[2];		      /* [0]=0 noise off 1
						       * noise on */
	unsigned char   rfnoisemod[2];

	unsigned char   walshpat[2];

	unsigned char   walshstat[2];

	unsigned char   rfpolswap[2];		      /* [0]=0 straight 
						       *     1 swapped
						       */ 
        unsigned char   rfatten[2][2];  	       /*[0]=0 No atten 
						       *     1 14db Sol Attn 
						       *     2 30db Sol Attn 
						       *     3 44db Sol Attn 
						       *     4 Terminated 
						       */
	unsigned char   rfnoiselev[6][2];	      /* 6 variables
						       * correspond to 6
						       * frequencies
						       * 70,150,235,325,610,142
						       * 0 =0 Low cal =1 Med
						       * Cal =2 High cal =3
						       * Extra Hi cal =4 RF
						       * Off
						       * 
						       */
	unsigned int 	lofreq[2][2];		      /* Value of Lo freq in
						       * Hz */

	unsigned char   ifpreattn[2][2];	      /* [0]=attn set */

	unsigned char   ifpostattn[2][2];	      /* [0]=attn set */

	unsigned char   ifbandwidth[2][2];	      /* [0]=selected band in
						       * MHz */

	unsigned char   ifalc[2][2];		      /* [0]=0 ALC Off 1 ALC
						       * On */


	unsigned char   bbattn[4][2];		      /* [0]= atten in db */

	unsigned int   bbband[4][2];		      /* [0] 0=>16000 KHz 
					               * 1=>8000 KHz 
						       * 2=> 4000 KHz
						       * 3=> 2000 KHz 
						       * 4=> 1000 KHz 
						       * 5=>  500 KHz 
						       * 6=>  250 KHz 
						       * 7=>  125 KHz 
						       * 8=>   64 KHz 
                                                       * per antenna 2 sidebands                                                       * 2 polarisations*/

	unsigned char   bbalc[4][2];		      /* [0]=0 ALC Off 
						       *    =1 ALC On */
        unsigned char sts[40];			      /* each byte corro.
 						       * to single para.*/
}               ANT_STATE;

typedef struct {
        char 		name[4];
	unsigned char	mcms[17];		      /* no of mcms followed
						    	 by their numbers */
        unsigned char   scan_mask[CEBMCMCNT][8];
        int  		fpsposn[4];
	int		el_offset;
	int		az_offset;
        unsigned char	if_pre_attn[6][2];
        unsigned char	if_post_attn[6][2];
        
}               ANT_DEFAULT;

typedef struct {
	int             abcid;
	char            progver[17];			   /* abc prog version */
        unsigned char   new_version;                       /* abc new version will 
                                                              currently support new tracking 
                                                              logic : for testing */
	int             packet_no;
	float           abctime;			   /* hh:mm:ss: */
	unsigned char   mode;				   /* =0 kernel mode,=1
							    * =>in abc reset
							    * mode,=2=> abc init
							    * mode */
	unsigned char   linkstatus;			   /* test   */
	unsigned char   trak_mode;			   /* =0 =>no trak,=1=> loc
							    * trak,=2 => rem trak */
	unsigned char   park_sts;			   /* antenna parking
							    * status */

	unsigned char   debugmode;			   /* abc debug mode */
	unsigned char 	maxmcms;
	unsigned char   mcmscnt;			   /* no of mcmc configured */
	int             mcmsactive[CEBMCMCNT];		   /* array of configured
							    * mcms */
	int             mesg_no;
	char            mesg[NO_ABC_MESG][MESG_LEN];
	char            abctalk[40];			   /* talk mesg */
	int             talkenable;			   /* talk mode */
	unsigned char   subarray;			   /* which subarray antenna
							    * belongs to */
	ABC_PARA        para;				   /* ABC timing/comm paras */
	ABC_LINK        lnk;				   /* ABC link details with
							    * servo,mcm and fps */
	ABC_DEBUG       dbg;				   /* abc debug info */
	ABC_CMDMON      cm;				   /* command mon info of
							    * ABC*/
        MCM_MONITOR     monitor[3];
        FE_MONITOR 	    fe_mon[6];  	   		   /* FE monitor data */
        COMMN_MONITOR 	commn_mon;	     		   /* common Box  monitor data */
        ANT_STATE       ant_state;
        ANT_DEFAULT     ant_default;                       /* struct containing
                                                            * default values of 
							    * abc */
							   /* common struct for
							    * abc  & cebabc ends
							    * here.DO NOT modify
							    * ABC struct after 
							    * this */
	MCM             mcmarray[MCMCNT];
	FPS             fpsunit;
	SERVO           servounit;
	TRAK_P          trak_p;				   /* 2:2:96 structure for
							    * loc trak paras 
							    * default values  */
}ABC;


typedef struct {
        int             abcid;
        char            progver[17];                       /* abc prog version */
        unsigned char   new_version;                       /* abc new version will
                                                              currently support new tracking
                                                              logic : for testing */
        int             packet_no;
        float           abctime;                           /* hh:mm:ss: */
        unsigned char   mode;                              /* =0 kernel mode,=1
                                                            * =>in abc reset
                                                            * mode,=2=> abc init
                                                            * mode */
        unsigned char   linkstatus;                        /* test   */
        unsigned char   trak_mode;                         /* =0 =>no trak,=1=> loc
                                                            * trak,=2 => rem trak */
        unsigned char   park_sts;                          /* antenna parking
                                                            * status */
 
        unsigned char   debugmode;                         /* abc debug mode */
        unsigned char   maxmcms;
        unsigned char   mcmscnt;                           /* no of mcmc configured */
        int             mcmsactive[CEBMCMCNT];             /* array of configured
                                                            * mcms */
        int             mesg_no;
        char            mesg[NO_ABC_MESG][MESG_LEN];
        char            abctalk[40];                       /* talk mesg */
        int             talkenable;                        /* talk mode */
        unsigned char   subarray;                          /* which subarray antenna
                                                            * belongs to */
        ABC_PARA        para;                              /* ABC timing/comm paras */
        ABC_LINK        lnk;                               /* ABC link details with
                                                            * servo,mcm and fps */
        ABC_DEBUG       dbg;                               /* abc debug info */
        ABC_CMDMON      cm;                                /* command mon info of
                                                            * ABC*/
        MCM_MONITOR     monitor[3];
        ANT_STATE       ant_state;
        ANT_DEFAULT     ant_default;                       /* struct containing
                                                            * default values of
                                                            * abc */
                                                           /* common struct for
                                                            * abc  & cebabc ends
                                                            * here.DO NOT modify
                                                            * ABC struct after
                                                            * this */
        MCM             mcmarray[CEBMCMCNT];
      
}               CEBABC;
 

typedef struct {


	int             cmd_cnter;
	unsigned char   cmd_blocked;
	unsigned char   resp_cnter;
	unsigned short  tmout_cnter;
	unsigned char   cmd_aborted;

}               COMH_CMDMON;

typedef struct {
	unsigned char   fromabcdly;
	unsigned char   abcibdly;
	unsigned char   abcswdly;
	unsigned char   unixibdly;
	unsigned char   fromunixdly;
	unsigned char   debug_time;


}               COMH_PARA;

typedef struct {
	unsigned short    abctimeoutcnt;			   /* abc comh timeout */
	unsigned short    abcchksumerrcnt;
	unsigned short    unixtranserrcnt;
	unsigned short    unixrecverrcnt;
	unsigned char   abcscnt;
	unsigned short    unixcomcnt;
	unsigned int    cmdforcomh;
	unsigned int    pktfromabc;
	unsigned int    pkttounix;
	unsigned int    unixabccmdcnt;
	unsigned int    abcnotrdycnt;
	unsigned int    transtimeout;
	unsigned int    br_cmds_issued;
	unsigned int    pkts_to_abc;			   /* total no of packets
							    * sent to all abcs */


}               COMH_LINK;

typedef struct {
	unsigned short    cmdoverflowerr;
	unsigned char   ringbuferr1;
	unsigned char   ringbuferr2;
	unsigned char   ringbuferr3;
	unsigned char   no_of_br_cmds_in_q;		   /* no of cmds in comh br
							    * cmd buff */
	unsigned char   br_cmd_sent;			   /* br cmd_sent flag */
        unsigned short crc_err;
        unsigned short tx_underrun;
        unsigned short abo_det;
        unsigned short rec_tmout;
        unsigned short reset_chip_cnt;
        unsigned short xmit_tmout;
        unsigned short overrun_err;


}               COMH_DEBUG;


typedef struct {
	char            progver[17];
	unsigned char   debugmode;
	unsigned char   cycletime;
	COMH_PARA       para;
	COMH_LINK       lnk;
	COMH_DEBUG      dbg;
	COMH_CMDMON     cm;
}               COMHSTAT;


/* site of observation */
typedef struct {
	char            name[SOMELEN];
	double          longitude;
	double          latitude;
	double          sinlat;
	double          coslat;
	float           timezone;
	float           tzrad;
}               SITE;
/* all fields are in radians */

/* date of observation */
typedef struct {
	char            mdate[12];			   /* system date */
	int             mjd;				   /* modified julian date */
	double          ltime;				   /* local time */
	double          utime;				   /* universal time */
	float           gastm;				   /* greenwich apparent
							    * siderial time at
							    * midnight */
	double          lstime;				   /* local siderial time */
}               OBSDATE;

typedef struct {
	char            name[12];
	float           ra_ref;
	float           dec_ref;
	float           epoch_ref;
	float           ra_date;
	float           dec_date;
	float           epoch_date;
	float           ra_off;
	float           dra_off;
	float           dec_off;
	float           ddec_off;
	float           tradec_ref;
	float           az_off;
	float           daz_off;
	float           el_off;
	float           del_off;
	float           tazel_ref;
	float           time_calc;
        double		rad_ref;
        double 		decd_ref;
        double          depoch_ref;
        double 		rad_date;
        double		decd_date;
        double      rad_app;
        double      decd_app;
        double          depoch_date;
}               SOURCE;

typedef struct {
	int             debuglevel;
	int             nodecode;
	int             generalerrors;
	int             ant_specific_info;
	int             slog;
	int             mlog;
	int             abcmesg;
	int             testmodemcm;
}               FLAGS;

typedef struct {
	int             rffe_r[2];
	int             attn_r[2];
	int             noise_r[2];
	int             noise_attn_r[2];
	int             poln_r[2];
	int             rffe[2];
	int             attn[2];
	int             noise_attn[2];
	int             noise[2];
	int             poln[2];
}               RFSTAT;

typedef struct {
	int             lofreq_r[2];
	int             attn_r[2];
	int             alcs_r[2];
	int             band_r[2];
	int             lofreq[2];
	int             attn[2];
	int             alcs[2];
	int             band[2];
}               IFSTAT;

typedef struct {
	int             lofreq_r[2];
	int             attn_r[2];
	int             alcs_r[2];
	int             band_r[2];
	int             lofreq[2];
	int             attn[2];
	int             alcs[2];
	int             band[2];
}               BBSTAT;

typedef struct {
	int             mode;
	int             feed_r;
	int             posn_r;
	int             calstat;
}               TURRSTAT;

typedef struct {
	int             mcm5_stat[2];
	int             walsh_stat[2];
	int             walsh_grp[2];
	int             noise_attn[2];
	int             walsh_pat;
}               FCONSTAT;

typedef struct {
	int             cmd_no;				   /* unique cmd no between
							    * unixhub & scctask */
	int             sts;				   /* =0 => cmd
							    * successful,1=>1
							    * waiting @
							    * cmd_monitor,2=>waiting
							    * for resp,3=>cmd
							    * aborted */
	unsigned char   src_id;				   /* cmd source */
	unsigned char   fail_summary[ANTENNACOUNT_1];	   /* 1st byte gives no of
							    * failed ant, rest of
							    * the bytes give ant
							    * adr */
	unsigned char   failed_level[ANTENNACOUNT_1];	   /* 1st byte gives no of
							    * failed ants, next
							    * onwards specify the
							    * dest @ which cmd
							    * failed */
	unsigned char   failure_code[ANTENNACOUNT_1];	   /* 1st byte gives no of
							    * ants failed, next
							    * specify the failure
							    * reason */
	unsigned char   subcmd_no;			   /* in case of qed
							    * commands, this will
							    * tell , to which
							    * subcmd no the rest of
							    * the info belongs it
							    * will be 0xff if cmd
							    * is non qed cmd */
	unsigned char   cmd_bytes[CMD_BYTES];		   /* 1st 20 bytes of the
							    * command */
}               CMD_INFO;

typedef struct {
	CMD_INFO        cmd_info[MAX_HISTORY_1];
}               CMD_HISTORY;

typedef struct {
	unsigned char   qdepth;
	unsigned char   no_of_cmds;
}               QSTATUS;

typedef struct {
	unsigned char   enable_flag;			   /* if enabled cmd-resp
							    * checking will take
							    * place */
	unsigned char   service_src_no;
	unsigned char   service_dest_no;		   /* currently which dest
							    * is being serviced :
							    * cmd monitor */
	unsigned char   debug_mode;			   /* debug mode of cmd
							    * monitor */
	unsigned char   time_offset;			   /* time offset for
							    * setting ABC time wrt
							    * Unix time */
	unsigned char   rst_comh;			   /* rst comh cmd-resp
							    * cnters */
	unsigned char   rst_abc;			   /* rst abc cmd-resp
							    * cnters */
}               CMD_MONITOR;
/*
typedef struct {
	char            last_cmd[12];
	float           integ;
	float           f_step;
	char            extr_file_name[64];
	unsigned int    antmask;
	unsigned short  bandmask;
	unsigned short  response_no;
	short           status;
	char            status_text[64];
}               DAS_SUB_RESP;
*/
typedef struct {
        float i;
        float q;
        float u;
        float v;
}    		POL_FLUX;


typedef struct { 
  char object[32];
  POL_FLUX flux;
  double mjd0;
  double ra_app, dec_app, ra_date, dec_date, dra,ddec; /* rad, rad/s */
  double freq[2];
  double first_lo[2];
  double bb_lo[2];
  double rest_freq[2];
  double lsrvel[2];  /* Hz, km/s  */
  double ch_width;  /* Hz */
  int id; 
  int net_sign[4]; 
  int mode;
  int dum1;
  unsigned int antmask;
  unsigned short bandmask,dum2;
  short calcode, qual;
} SourceParType;


typedef struct {
  char code[8];
  char observer[32];
  char title[32];
  unsigned int antmask;
  unsigned short bandmask,seq;
} ProjectType;

typedef struct {
  int status;
  float t;  /* program dependent meaning ! */
  ProjectType proj;
  SourceParType source;
} ScanInfoType;



typedef struct {
        char datafile[80];
        int  das_sub_state;
        int  cmd_no;
        ScanInfoType cntl;
}		DAS_SUB_CNTL;


typedef struct {
        char   config_file[80];
        int    msg_id;
        int    das_state;
        int    das_sub_state[MAX_DAS_SUB];
        DAS_SUB_CNTL sub_cntl[MAX_DAS_SUB];
}               DAS_CNTL;

typedef struct {
	unsigned char   useflag;
	int             packet_no;
	unsigned int    update_flag;			   /* for each of field
							    * updates */
	char            program_id[17];
	int             ipcid;
	unsigned char   state;				   /* subarray state */
	float           track_till;
	float           tol_az;
	float           tol_el;
	float           time_ist;
	SOURCE          source;
	float           az_target;
	float           el_target;
	unsigned char   sub_req;                           /* not reqd delete*/
	unsigned char   sub_connect;                       /* not reqd */
	unsigned char   no_ant;
	unsigned char   ant_id[ANTENNACOUNT_1];
	char            usr_host[12];                      /* not reqd*/
	unsigned char   usr_req;                            /* not used  remove*/
	unsigned char   usr_connect;
	unsigned char   no_pant;
	unsigned char   pant_id[ANTENNACOUNT_1];
	unsigned char   pant_addr[ANTENNACOUNT_1];			   /* reverse mapping bet
							    * ant addr & ant id */
        int		pantmask;
        int 		cmd_retry;                          /* No. of times cmd will be retried
                                                             * at subarray level */
	float           az_error[ANTENNACOUNT_1];
	float           el_error[ANTENNACOUNT_1];
	float           az_offset;
	float           el_offset;
        unsigned char   status[10][ANTENNACOUNT_1];
        char            innertrk;
        RFSTAT          rfstat;
        IFSTAT          ifstat;
        BBSTAT          bbstat;
        FCONSTAT        fconstat;
        TURRSTAT        turrstat;
 
}               SUBARRAY;
/*      info about online unix process */
 
typedef struct
  {
     char name[20];
     int  tcpport;
     int  online_id;
     char rights[4];
     int  pid;
     int  debuglevel;
     int  sock_id[2];           /* 0=process->unixhub, 1=unixhub->process*/
     int  status[2];            /* 0=requested, 1=actual(1=active,0=not started,-1=failed*/
     int  tcp_pkt_no[2];
     int  tcp_local_err[2];     /* 0=send error;1=recv error*/
     int  tcp_remote_err[2];    /* 0=send error;1=recv error*/
  } PROCESS;
 
typedef struct{
     char configfile[80];
     char version[80];
     char hostname[12];
     int  max_process;
     int  max_auto_process;
     unsigned char rev_map[256];
     PROCESS process[MAXPROCESS];
  } PROCESS_TABLE;
 
 
typedef struct {
        int            plogopen;
        char           filename[MAX_LOG_FILE][80];
        unsigned char  owner[MAX_LOG_FILE];
        int            file_pointer[MAX_LOG_FILE];
  } LOG_TABLE;
 
/* general shared memory data structure */
 
typedef struct {
        char            program_id[40];                    /* id and version
of
                                                            * program */
        char            struct_id[40];                     /* id and date of
                                                            * online.h */

        char            online_path[80];                   /* path of onconfig.def */
        OBSDATE         today;
        SITE            site;
        char            tstring[SOMELEN];
        long            btime;                             /* added for time
in
                                                            * long from time
*/
        char            datestring[SOMELEN];
        char            lststring[SOMELEN];
        int             shm_status;			/* =1 when active*/
        int             packet_no;
        int             log_time;
        int             main_mesg_no;
        char            main_mesg[NO_MAIN_MESG][MESG_LEN];
        int             response_no;
        char            response_text[NO_MAIN_MESG][MESG_LEN];
        int             command_no;
        unsigned char   command[NO_COMMAND][COMMAND_LEN];
        int             abcsactive[ANTENNACOUNT_1];
        ABC             abcarray[ANTENNACOUNT];          /* kept 3 ABC structs extra to alloca
                                                            * te enough space for 64 MCMs of CEB
                                                            * ABC */
        CEBABC	        cebabc[2];                          /*created a struct for cebabc, just after abcarray
                                                          * 29:1:98*/
        COMHSTAT        comhstat;
        SUBARRAY        subarray[MAX_SUBARRAY];
        FLAGS           flags;
        CMD_HISTORY     cmd_history;
        CMD_MONITOR     cmd_monitor;
        int             decodeerr;
        int             talkdata;
        int 		cmd_file;                          /* file pointer to store cmds @ pktdecode 16:10:97*/
        QSTATUS         qsts[MAX_SOURCES_1][MAX_DESTNS_1]; /* last extra src for
                                                            * comh & last extra
                                                            * dest for trak */
        DAS_CNTL        das_cntl;
        PROCESS_TABLE   p_table;
        LOG_TABLE       log_table;
}               ONLINE;
