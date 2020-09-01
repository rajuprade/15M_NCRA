///////////////////////////////////////////////////////////////////////////
// PROJECT           : ETHSIMULATOR
// File              : EVENTDEF.H
// Author            : 
// Version           :
// Last Modification : 22-01-2011
// Reason            :  
///////////////////////////////////////////////////////////////////////////

#ifndef __EVENTDEF_H__
#define __EVENTDEF_H__


#define angles_code            0x30
#define anlg_code              0x32
#define dgtl_code              0x34
#define rd_setparam_code       0x36
#define antna_stt_code         0x38
#define version_code           0x3a
#define err_stat_code          0x3c

#define cld_strt_cmd           0x40
#define posn_cmd               0x42
#define track_cmd              0x44
#define hold_cmd               0x46
#define stop_cmd               0x48
#define close_cmd              0x4a
#define stow_cmd               0x4c
#define strls_cmd              0x4e
#define abort_cmd              0x50
#define tod_code               0x52
#define stwpos_code            0x54
#define shlmt_code             0x56
#define sllmt_code             0x58
#define wndvel_code            0x5a
#define cur_code               0x5c
#define spd_code               0x5e

#define hw_rst_cmd             0x6c

#define start_datalog_cmd      0x70
#define stop_datalog_cmd       0x71

#define start_calibration_cmd  0x80
#define stop_calibration_cmd   0x81

#define update_axisparam_cmd       0x90
#define update_cppparam_cmd        0x91
#define update_compensparam_cmd    0x92
#define write_param_to_file_cmd    0x93


//		{appln layer codes}
#define ACK                    0x10

#define NAK                    0x11
#define timout                 0x51
#define irrelevant             0x52
#define syntax                 0x53
#define illegal_cmd            0x54

#define RESP_MESS              0x12
#define success_az             0x10
#define failed_az              0x12
#define aborted_az             0x14
#define success_el             0x11
#define failed_el              0x13
#define aborted_el             0x15

#define ev_ax_interlock_az     0x2c
#define ev_axis_on_az          0x2e
#define ev_axis_off_az         0x30
#define ev_cwlmt_az            0x32
#define ev_ccwlmt_az           0x34
#define ev_lmtexit_az          0x36
#define ev_currents_high_az    0x38
#define ev_taco_high_az        0x3a
#define ev_trkq_discared_az    0x3c
#define ev_axis_fault_az       0x3e

#define ev_stwerr_el           0x21
#define ev_stowed_el           0x23
#define ev_stwrlsd_el          0x25
#define ev_stwg_el             0x27
#define ev_stwrlsg_el          0x29
#define ev_stposn_el           0x2b

#define ev_ax_interlock_el     0x2d
#define ev_axis_on_el          0x2f
#define ev_axis_off_el         0x31
#define ev_uplmt_el            0x33
#define ev_dnlmt_el            0x35
#define ev_lmtexit_el          0x37
#define ev_currents_high_el    0x39
#define ev_taco_high_el        0x3b
#define ev_trkq_discared_el    0x3d
#define ev_axis_fault_el       0x3f

#define ev_wv_high             0x50
#define ev_empark_wind         0x51
#define ev_mode_change_man     0x52
#define ev_mode_change_loc     0x53
#define ev_mode_change_rmt     0x54
#define ev_mode_change_off     0x55

#define ev_ssc_reset           0x56
#define ev_ssc_not_ok          0x57

#endif