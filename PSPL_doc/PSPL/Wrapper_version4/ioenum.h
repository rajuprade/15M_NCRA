////////////////////////////////////////////////////////////////////////////////////////////////
// PROJECT           : GMRT
// File              : IOENUM.H
// Author            : 
// Version           :
// Last Modification : 26-11-2007
// Reason            :  
////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef __IOENUM_H__
#define __IOENUM_H__

typedef enum {OFF_MD=0,MANUAL=1,LOCAL=2,REMOTE=3} system_mode_type;
typedef enum {AZ=0,EL=1,AZ_EL=2} axis_type;
typedef enum {ready=0,interlock=1} axis_status_type;
typedef enum {normal=0,high=1} status_type;

typedef enum {STWD=0,STWING=1,STRLSING=2,STWERR=3,STRLSD_BRKED=4,TRACKING=5,POSITIONING=6,MANUAL_STT=7,LMT_RLSG=8,SERVO_CAL=9} el_antna_states;
typedef enum {_STRLSD_BRKED=0,_TRACKING=1,_POSITIONING=2,_MANUAL_STT=3,_LMT_RLSG=4,_SERVO_CAL=5} az_antna_states;
typedef enum {cw_lmt=0,ccw_lmt=1,nolmt=2} az_limit_status_type;
typedef enum {up_lmt=0,dn_lmt=1,no_lmt=2} el_limit_status_type;

typedef enum {stowed=0,stowrlsd=1,stowing=2,stowrlsg=3,stow_err=4} stow_status_type;
typedef enum {reached=0,not_reached=1} stow_posn_status_type;

typedef enum {init=0,run=1} controller_state_type;
typedef enum {XNULL=0,COLDSTRT=1,STWRLS=2,HOLD=3,POSITION=4,TRACK=5,ABRT=6,STOP=7,STOW=8,CLOSE=9,CALIBRATE=10} cmndset;

typedef enum {TMR_ON=0,TMR_OFF=1,TIME_OUT=2} TIMER_STT_TYPE;
typedef enum {no_err=0,rng_err=1,syn_err=2} error_type;

typedef enum {listen_=0,confirm_nak_ack=1,ring=2} rem_state_type;//listen changed to listen_
typedef enum {_listen=0,_wait=1} gui_cmd_state_type;
typedef enum {_idle=0,confirm_event=1} loc_state_type;
typedef enum {idle_=0,collect_confirm=1} data_state_type;
typedef enum {msg_idle=0,msg_wait_resp=1} msg_hndlr_state_type;
typedef enum {gui=0,host=1} cmd_source_type;

typedef enum {empty=0,full=1} q_stt_type;
typedef enum {pending=0,accepted=1} msg_stt_type;
typedef enum {accptd=0,irrvlnt=1,NUL=2} resp_type;

typedef enum {TXM_FREE=0,IDLE=1,XMIT=2,AWAIT_RESP=3} txm_stts;
typedef enum {FREE=0,PENDING=1,DLEX=2} msg_stts;
typedef enum {RXM_FREE=0,DLE_RXD_FREE=1,DLE_RXD_ASMBL=2,ASMBL=3,GET_SRC_ID=4,GET_DES_ID=5,GET_BCC=6} rxm_stts;


extern az_antna_states        antna_stt_az;
extern el_antna_states        antna_stt_el;
extern system_mode_type       system_mode; 
extern msg_stt_type           msg_stt;

extern controller_state_type  controller_state;

extern stow_status_type       stow_status;
extern stow_posn_status_type  stow_posn_status;
extern axis_status_type       axis_status;
extern q_stt_type             q_stt;
#endif
