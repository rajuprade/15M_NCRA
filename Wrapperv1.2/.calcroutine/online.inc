        integer MAXCHANNEL
        parameter(MAXCHANNEL=64)
        integer MAXCHANNEL_1
        parameter(MAXCHANNEL_1=65)
        integer MAXPROCESS
        parameter(MAXPROCESS=20)
        integer LEN_SERVO_ANG
        parameter(LEN_SERVO_ANG=11)
        integer MESG_LEN
        parameter(MESG_LEN=80)
        integer NO_ABC_MESG
        parameter(NO_ABC_MESG=10)
        integer MCMCNT
        parameter(MCMCNT=16)
        integer CEBMCMCNT
        parameter(CEBMCMCNT=64)
        integer MCMSTATCNT
        parameter(MCMSTATCNT=129)
        integer CEBABCID
        parameter(CEBABCID=19)
        integer SOMELEN
        parameter(SOMELEN=13)
        integer ANTENNACOUNT
        parameter(ANTENNACOUNT=31)
        integer CEBABC1_ADDR
        parameter(CEBABC1_ADDR=0)
        integer CEBABC2_ADDR
        parameter(CEBABC2_ADDR=31)
        integer ANTENNACOUNT_1
        parameter(ANTENNACOUNT_1=32)
        integer ANTENNACOUNT_3
        parameter(ANTENNACOUNT_3=34)
        integer MAX_SUBARRAY
        parameter(MAX_SUBARRAY=6)
        integer NO_MAIN_MESG
        parameter(NO_MAIN_MESG=10)
        integer NO_COMMAND
        parameter(NO_COMMAND=10)
        integer COMMAND_LEN
        parameter(COMMAND_LEN=150)
        integer MAX_HISTORY
        parameter(MAX_HISTORY=150)
        integer MAX_HISTORY_1
        parameter(MAX_HISTORY_1=151)
        integer CMD_BYTES
        parameter(CMD_BYTES=20)
        character*80 ONLINE_VERS
        parameter(ONLINE_VERS="@(#)online.h 1.69 7/8/96 GMRT"	)
        integer MAX_SOURCES
        parameter(MAX_SOURCES=7)
        integer MAX_DESTNS
        parameter(MAX_DESTNS=4)
        integer MAX_SOURCES_1
        parameter(MAX_SOURCES_1=8)
        integer MAX_DESTNS_1
        parameter(MAX_DESTNS_1=5)
        integer MAX_DAS_SUB
        parameter(MAX_DAS_SUB=6)
        integer MAX_LOG_FILE
        parameter(MAX_LOG_FILE=10)
        integer ADDR_FIRSTMCM
        parameter(ADDR_FIRSTMCM=0)
        integer ADDR_LASTMCM
        parameter(ADDR_LASTMCM=13)
        integer ADDR_FPS
        parameter(ADDR_FPS=14)
        integer ADDR_TALK
        parameter(ADDR_TALK=15)
        integer ADDR_SERVO
        parameter(ADDR_SERVO=16)
        integer ADDR_ABC
        parameter(ADDR_ABC=17)
        integer ADDR_COMH
        parameter(ADDR_COMH=32)
        integer ADDR_CMDMON
        parameter(ADDR_CMDMON=33)
        integer ADDR_PKTDECODE
        parameter(ADDR_PKTDECODE=47)
        integer ADDR_UNIXHUB
        parameter(ADDR_UNIXHUB=48)
        integer ADDR_MASTER
        parameter(ADDR_MASTER=49)
        integer ADDR_FIRSTUSR
        parameter(ADDR_FIRSTUSR=50)
        integer ADDR_LASTUSR
        parameter(ADDR_LASTUSR=55)
        integer ADDR_SUBMON
        parameter(ADDR_SUBMON=63)
        integer ADDR_MASTERSAC
        parameter(ADDR_MASTERSAC=64)
        integer ADDR_FIRSTSAC
        parameter(ADDR_FIRSTSAC=65)
        integer ADDR_LASTSAC
        parameter(ADDR_LASTSAC=70)
        integer ADDR_DASMON
        parameter(ADDR_DASMON=72)
        integer ADDR_SHMSERV
        parameter(ADDR_SHMSERV=90)
        integer ADDR_FIRSTBBMCM
        parameter(ADDR_FIRSTBBMCM=100)
        integer ADDR_LASTBBMCM
        parameter(ADDR_LASTBBMCM=164)


        structure /MCM_LINK/
        byte mcmcommerrors 
        integer errcnt 
        integer cmdfail 
        integer timeout 
        integer chksum 
        byte mcmcontrolinfo(0:2-1) 
        end structure



        structure /MCM_PARA/
        character*(41) thresstat 
        byte thresval(0:41-1) 
        byte threshold(0:5-1) 
        byte scandata(0:MAXCHANNEL-1) 
        byte chn_map(0:MAXCHANNEL_1-1) 
        byte cmd_analogmask(0:8-1) 
        byte analogmask(0:8-1) 
        byte cmd_digitalmask16(0:2-1) 
        byte digitalmask16(0:2-1) 
        byte cmd_digitalmask32(0:4-1) 
        byte digitalmask32(0:4-1) 
        byte cmd_digitalmask64(0:8-1) 
        byte digitalmask64(0:8-1) 
        integer walpat1 
        integer walpat2 
        integer walpat3 
        integer walpat4 
        integer walpat5 
        end structure



        structure /MCM/
        integer packet_no 
        byte id 
        byte mcmversion 
        byte wiringstatus 
        byte selftestresults 
        byte mode 
        byte scandatapresent 
        byte avgfact 
        byte respcode 
        byte subcmd 
        byte state 
        character*(30) mcmcmd 
        record / MCM_LINK /lnk 
        record / MCM_PARA /para 
        end structure



        structure /FPS_LINK/
        byte fpscommerrors 
        integer errcnt 
        integer cmdfail 
        integer timeout 
        integer chksum 
        integer resetcnt 
        integer overcurntcnt 
        byte fpscontrolinfo(0:2-1) 
        end structure



        structure /FPS_PARA/
        real encodertp 
        integer rampuptime 
        integer rampdowntime 
        integer lowrpmtime 
        real lowrpmlmt 
        integer brakecnttime 
        integer stoptimcnt 
        integer finetunepwmcnt 
        real maxpwm 
        real targetpos_cmd 
        real max_angle 
        real min_angle 
        real ua0_angle 
        end structure



        structure /FPS/
        integer packet_no 
        byte fpsversion 
        byte installed_new 
        character*(70) status 
        byte wdogreset 
        byte overcurnt 
        byte respcode 
        byte subcmd 
        character*(50) fpscmd 
        byte selftestresults 
        byte mode 
        real curnt_rpm 
        real curnt_pos 
        real targetpos 
        record / FPS_LINK /lnk 
        record / FPS_PARA /para 
        end structure



        structure /SERVO_VARS/
        real analog_time 
        real digital_time 
        real para_time 
        real azim_pp 
        real elev_pp 
        real az_tacho1 
        real az_tacho2 
        real el_tacho1 
        real el_tacho2 
        real wind_vel_low_limit 
        real wind_vel_high_limit 
        real az_soft_low_limit 
        real az_soft_high_limit 
        real az_encoder_offset 
        real az_G11 
        real az_T11 
        real az_T12 
        real az_T13 
        real az_G21 
        real az_T21 
        real az_T22 
        real az_T23 
        real el_soft_low_limit 
        real el_soft_high_limit 
        real el_encoder_offset 
        real el_G11 
        real el_T11 
        real el_T12 
        real el_T13 
        real el_G21 
        real el_T21 
        real el_T22 
        real el_T23 
        end structure



        structure /SERVO/
        integer packet_no 
        character*(LEN_SERVO_ANG) version_number 
        character*(LEN_SERVO_ANG) station_number 
        byte selftest_result(0:LEN_SERVO_ANG-1) 
        character*(LEN_SERVO_ANG) servodate 
        byte servostatusbyte 
        real time 
        real azim_cp 
        real azim_tp 
        real elev_cp 
        real elev_tp 
        real az_motor1 
        real az_motor2 
        real el_motor1 
        real el_motor2 
        real wind_vel1 
        real wind_vel2 
        real az_stow_ang 
        real el_stow_ang 
        record / SERVO_VARS /vars 
        byte servodigitalvar(0:6-1) 
        character*(LEN_SERVO_ANG) az_state 
        character*(LEN_SERVO_ANG) el_state 
        end structure



        structure /MCM_MONITOR/
        byte data(0:16-1,0:30-1) 
        real time 
        byte max_states 
        end structure



        structure /FE_MONITOR/
        real time 
        integer noise_cal 
        integer rf_stat 
        integer wal_stat 
        integer sub_band 
        real wf1,wf2 
        real n1,n2,p1,p2 
        real ref1,ref2 
        byte data(0:32-1) 
        end structure



        structure /COMMN_MONITOR/
        real time 
        integer sel_band(0:2-1) 
        integer sol_att(0:2-1) 
        integer swap_stat 
        real vp(0:2-1) 
        real ve(0:2-1) 
        real vrf(0:2-1) 
        integer rf_pow(0:2-1) 
        byte data(0:64-1) 
        end structure



        structure /TRAK_P/
        integer trk_status 
        integer lat 
        integer longitude 
        integer sinlat 
        integer coslat 
        integer azerr 
        integer elerr 
        integer elmax 
        integer elmin 
        integer azmax 
        integer azmin 
        integer stowpos 
        integer longcor 
        integer lst0 
        integer t0 
        integer*2 inout 
        integer*2 over90 
        integer ra0 
        integer dec0 
        integer raoff 
        integer decoff 
        integer dra 
        integer ddec 
        integer trd0 
        integer azoff 
        integer eloff 
        integer daz 
        integer del 
        integer tazel 
        integer tmax 
        integer ra 
        integer dec 
        integer azflg 
        integer*2 cdec 
        integer*2 sdec 
        integer slsd 
        integer slcd 
        integer clsd 
        integer clcd 
        integer ha 
        integer time 
        integer lst 
        integer az 
        integer elev 
        integer offset 
        integer tot_trak_time 
        byte status 
        integer strt_trak_time 
        integer delay_trak_time 
        end structure



        structure /ABC_CMDMON/
        byte src_no(0:5-1) 
        byte tally_cnters 
        integer cmd_cnter 
        byte cmd_blocked 
        byte resp_cnter(0:2-1) 
        integer*2 tmout_cnter 
        byte cmd_aborted 
        integer servo_cmd_cnter 
        byte servo_cmd_blocked 
        byte servo_resp_cnter(0:2-1) 
        integer*2 servo_tmout_cnter 
        byte servo_cmd_aborted 
        integer loc_cmd_cnter 
        byte loc_cmd_blocked 
        byte loc_resp_cnter(0:2-1) 
        integer*2 loc_tmout_cnter 
        byte loc_cmd_aborted 
        integer mcm_cmd_cnter 
        byte mcm_cmd_blocked 
        byte mcm_resp_cnter(0:3-1) 
        integer*2 mcm_tmout_cnter 
        byte mcm_cmd_aborted 
        integer fps_cmd_cnter 
        byte fps_cmd_blocked 
        byte fps_resp_cnter(0:2-1) 
        integer*2 fps_tmout_cnter 
        byte fps_cmd_aborted 
        end structure



        structure /ABC_PARA/
        byte delaybetmcm 
        byte cycletime 
        byte mcmtrantmout 
        byte mcmrecvtmout 
        byte servoawaitoutdelay 
        byte servoinptmout 
        byte servointbyttmout 
        byte servoouttmout 
        byte servocmdperiodicity 
        byte debug_time 
        byte monitor_time 
        byte servointcmddelay 
        byte flush_evnt 
        byte trk_dly 
        byte park_dly 
        byte wait_before_move 
        byte wait_after_move 
        byte wait_after_stop 
        end structure



        structure /ABC_LINK/
        byte linkstatus 
        byte mcmstatusbytes(0:12-1) 
        character*(MCMSTATCNT) statmcm2 
        integer*2 mcmtimeout 
        integer*2 mcmchksum 
        integer*2 abctimeout 
        integer*2 abcchksum 
        integer*2 abcservnakcnt 
        integer*2 abcservenqcnt 
        integer*2 servabcnakcnt 
        integer*2 servabcenqcnt 
        byte servoresponse 
        integer*2 comhtimeout 
        integer*2 comhchksumerr 
        integer*2 servcmdtmoutcnt 
        integer*2 ret_link_timeouts 
        integer*2 ret_link_chksums 
        integer*2 real_cmds_issued 
        integer*2 real_cmds_aborted 
        integer*2 br_cmds_issued 
        integer*2 br_cmds_aborted 
        integer*2 large_pkt_abc 
        integer*2 abc_not_ready 
        integer totalmcmcmds 
        integer totalservocmds 
        byte servo_op_cmds_till_abc 
        byte servo_op_cmds_issued_appln 
        byte servo_op_cmds_issued_link 
        byte op_cmds_servo_acked 
        byte local_cmds_issued_by_abc 
        byte mcm_op_cmds_till_abc 
        byte mcm_op_cmds_issued_link 
        byte abc_op_cmds_till_abc 
        end structure



        structure /ABC_DEBUG/
        byte no_of_cmds 
        byte head 
        byte tail 
        byte try_cnt 
        byte br_try_cnt 
        byte real_xmit 
        byte real_rec 
        byte retry_req 
        byte broadcast_flag 
        byte ringerr1 
        byte ringerr2 
        byte ringerr3 
        byte servo_got_resp_corrected 
        byte servo_out_free_corrected 
        byte no_of_cmds_in_servo_localq 
        byte current_cmd_no_in_localq 
        byte current_time_no_in_localq 
        byte servo_localq_blocked 
        byte generate_servoq_event 
        byte servoq_time_cnter 
        real abc_dbg_time 
        real topq_cmd_time 
        byte mcm_grp_head 
        byte mcm_grp_tail 
        byte tot_mcm_cmds 
        byte mcm_cmd_head 
        byte mcm_cmd_tail 
        byte crc_err 
        byte overrun_err 
        byte tx_underrun 
        byte rec_tmout 
        byte abo_detect 
        byte reset_chip_cnt 
        byte tot_abc_cmds 
        end structure



        structure /ANT_STATE/
        byte rffeed(0:2-1) 
        integer rfbox(0:2-1,0:2-1) 
        byte rfnoise(0:2-1) 
        byte rfnoisemod(0:2-1) 
        byte walshpat(0:2-1) 
        byte walshstat(0:2-1) 
        byte rfpolswap(0:2-1) 
        byte rfatten(0:2-1,0:2-1) 
        byte rfnoiselev(0:2-1,0:6-1) 
        integer lofreq(0:2-1,0:2-1) 
        byte ifpreattn(0:2-1,0:2-1) 
        byte ifpostattn(0:2-1,0:2-1) 
        byte ifbandwidth(0:2-1,0:2-1) 
        byte ifalc(0:2-1,0:2-1) 
        byte bbattn(0:2-1,0:4-1) 
        integer bbband(0:2-1,0:4-1) 
        byte bbalc(0:2-1,0:4-1) 
        byte sts(0:40-1) 
        end structure



        structure /ANT_DEFAULT/
        character*(4) name 
        byte mcms(0:17-1) 
        byte scan_mask(0:8-1,0:CEBMCMCNT-1) 
        integer fpsposn(0:4-1) 
        integer el_offset 
        integer az_offset 
        byte if_pre_attn(0:2-1,0:6-1) 
        byte if_post_attn(0:2-1,0:6-1) 
        end structure



        structure /ABC/
        integer abcid 
        character*(17) progver 
        byte new_version 
        integer packet_no 
        real abctime 
        byte mode 
        byte linkstatus 
        byte trak_mode 
        byte park_sts 
        byte debugmode 
        byte maxmcms 
        byte mcmscnt 
        integer mcmsactive(0:CEBMCMCNT-1) 
        integer mesg_no 
        character*(MESG_LEN) mesg(0:NO_ABC_MESG-1) 
        character*(40) abctalk 
        integer talkenable 
        byte subarray 
        record / ABC_PARA /para 
        record / ABC_LINK /lnk 
        record / ABC_DEBUG /dbg 
        record / ABC_CMDMON /cm 
        record / MCM_MONITOR /monitor(0:3-1) 
        record / FE_MONITOR /fe_mon(0:6-1) 
        record / COMMN_MONITOR /commn_mon 
        record / ANT_STATE /ant_state 
        record / ANT_DEFAULT /ant_default 
        record / MCM /mcmarray(0:MCMCNT-1) 
        record / FPS /fpsunit 
        record / SERVO /servounit 
        record / TRAK_P /trak_p 
        end structure



        structure /CEBABC/
        integer abcid 
        character*(17) progver 
        byte new_version 
        integer packet_no 
        real abctime 
        byte mode 
        byte linkstatus 
        byte trak_mode 
        byte park_sts 
        byte debugmode 
        byte maxmcms 
        byte mcmscnt 
        integer mcmsactive(0:CEBMCMCNT-1) 
        integer mesg_no 
        character*(MESG_LEN) mesg(0:NO_ABC_MESG-1) 
        character*(40) abctalk 
        integer talkenable 
        byte subarray 
        record / ABC_PARA /para 
        record / ABC_LINK /lnk 
        record / ABC_DEBUG /dbg 
        record / ABC_CMDMON /cm 
        record / MCM_MONITOR /monitor(0:3-1) 
        record / ANT_STATE /ant_state 
        record / ANT_DEFAULT /ant_default 
        record / MCM /mcmarray(0:CEBMCMCNT-1) 
        end structure



        structure /COMH_CMDMON/
        integer cmd_cnter 
        byte cmd_blocked 
        byte resp_cnter 
        integer*2 tmout_cnter 
        byte cmd_aborted 
        end structure



        structure /COMH_PARA/
        byte fromabcdly 
        byte abcibdly 
        byte abcswdly 
        byte unixibdly 
        byte fromunixdly 
        byte debug_time 
        end structure



        structure /COMH_LINK/
        integer*2 abctimeoutcnt 
        integer*2 abcchksumerrcnt 
        integer*2 unixtranserrcnt 
        integer*2 unixrecverrcnt 
        byte abcscnt 
        integer*2 unixcomcnt 
        integer cmdforcomh 
        integer pktfromabc 
        integer pkttounix 
        integer unixabccmdcnt 
        integer abcnotrdycnt 
        integer transtimeout 
        integer br_cmds_issued 
        integer pkts_to_abc 
        end structure



        structure /COMH_DEBUG/
        integer*2 cmdoverflowerr 
        byte ringbuferr1 
        byte ringbuferr2 
        byte ringbuferr3 
        byte no_of_br_cmds_in_q 
        byte br_cmd_sent 
        integer*2 crc_err 
        integer*2 tx_underrun 
        integer*2 abo_det 
        integer*2 rec_tmout 
        integer*2 reset_chip_cnt 
        integer*2 xmit_tmout 
        integer*2 overrun_err 
        end structure



        structure /COMHSTAT/
        character*(17) progver 
        byte debugmode 
        byte cycletime 
        record / COMH_PARA /para 
        record / COMH_LINK /lnk 
        record / COMH_DEBUG /dbg 
        record / COMH_CMDMON /cm 
        end structure



        structure /SITE/
        character*(SOMELEN) name 
        double precision longitude 
        double precision latitude 
        double precision sinlat 
        double precision coslat 
        real timezone 
        real tzrad 
        end structure



        structure /OBSDATE/
        character*(12) mdate 
        integer mjd 
        double precision ltime 
        double precision utime 
        real gastm 
        double precision lstime 
        end structure



        structure /SOURCE/
        character*(12) name 
        real ra_ref 
        real dec_ref 
        real epoch_ref 
        real ra_date 
        real dec_date 
        real epoch_date 
        real ra_off 
        real dra_off 
        real dec_off 
        real ddec_off 
        real tradec_ref 
        real az_off 
        real daz_off 
        real el_off 
        real del_off 
        real tazel_ref 
        real time_calc 
        double precision rad_ref 
        double precision decd_ref 
        double precision depoch_ref 
        double precision rad_date 
        double precision decd_date 
        double precision rad_app 
        double precision decd_app 
        double precision depoch_date 
        end structure



        structure /FLAGS/
        integer debuglevel 
        integer nodecode 
        integer generalerrors 
        integer ant_specific_info 
        integer slog 
        integer mlog 
        integer abcmesg 
        integer testmodemcm 
        end structure



        structure /RFSTAT/
        integer rffe_r(0:2-1) 
        integer attn_r(0:2-1) 
        integer noise_r(0:2-1) 
        integer noise_attn_r(0:2-1) 
        integer poln_r(0:2-1) 
        integer rffe(0:2-1) 
        integer attn(0:2-1) 
        integer noise_attn(0:2-1) 
        integer noise(0:2-1) 
        integer poln(0:2-1) 
        end structure



        structure /IFSTAT/
        integer lofreq_r(0:2-1) 
        integer attn_r(0:2-1) 
        integer alcs_r(0:2-1) 
        integer band_r(0:2-1) 
        integer lofreq(0:2-1) 
        integer attn(0:2-1) 
        integer alcs(0:2-1) 
        integer band(0:2-1) 
        end structure



        structure /BBSTAT/
        integer lofreq_r(0:2-1) 
        integer attn_r(0:2-1) 
        integer alcs_r(0:2-1) 
        integer band_r(0:2-1) 
        integer lofreq(0:2-1) 
        integer attn(0:2-1) 
        integer alcs(0:2-1) 
        integer band(0:2-1) 
        end structure



        structure /TURRSTAT/
        integer mode 
        integer feed_r 
        integer posn_r 
        integer calstat 
        end structure



        structure /FCONSTAT/
        integer mcm5_stat(0:2-1) 
        integer walsh_stat(0:2-1) 
        integer walsh_grp(0:2-1) 
        integer noise_attn(0:2-1) 
        integer walsh_pat 
        end structure



        structure /CMD_INFO/
        integer cmd_no 
        integer sts 
        byte src_id 
        byte fail_summary(0:ANTENNACOUNT_1-1) 
        byte failed_level(0:ANTENNACOUNT_1-1) 
        byte failure_code(0:ANTENNACOUNT_1-1) 
        byte subcmd_no 
        byte cmd_bytes(0:CMD_BYTES-1) 
        end structure



        structure /CMD_HISTORY/
        record / CMD_INFO /cmd_info(0:MAX_HISTORY_1-1) 
        end structure



        structure /QSTATUS/
        byte qdepth 
        byte no_of_cmds 
        end structure



        structure /CMD_MONITOR/
        byte enable_flag 
        byte service_src_no 
        byte service_dest_no 
        byte debug_mode 
        byte time_offset 
        byte rst_comh 
        byte rst_abc 
        end structure



        structure /POL_FLUX/
        real i 
        real q 
        real u 
        real v 
        end structure



        structure /SourceParType/
        character*(32) object 
        record / POL_FLUX /flux 
        double precision mjd0 
        double precision ra_app, dec_app, ra_date, dec_date, dra,ddec 
        double precision freq(0:2-1) 
        double precision first_lo(0:2-1) 
        double precision bb_lo(0:2-1) 
        double precision rest_freq(0:2-1) 
        double precision lsrvel(0:2-1) 
        double precision ch_width 
        integer id 
        integer net_sign(0:4-1) 
        integer mode 
        integer dum1 
        integer antmask 
        integer*2 bandmask,dum2 
        integer*2 calcode, qual 
        end structure



        structure /ProjectType/
        character*(8) code 
        character*(32) observer 
        character*(32) title 
        integer antmask 
        integer*2 bandmask,seq 
        end structure



        structure /ScanInfoType/
        integer status 
        real t 
        record / ProjectType /proj 
        record / SourceParType /source 
        end structure



        structure /DAS_SUB_CNTL/
        character*(80) datafile 
        integer das_sub_state 
        integer cmd_no 
        record / ScanInfoType /cntl 
        end structure



        structure /DAS_CNTL/
        character*(80) config_file 
        integer msg_id 
        integer das_state 
        integer das_sub_state(0:MAX_DAS_SUB-1) 
        record / DAS_SUB_CNTL /sub_cntl(0:MAX_DAS_SUB-1) 
        end structure



        structure /SUBARRAY/
        byte useflag 
        integer packet_no 
        integer update_flag 
        character*(17) program_id 
        integer ipcid 
        byte state 
        real track_till 
        real tol_az 
        real tol_el 
        real time_ist 
        record / SOURCE /source 
        real az_target 
        real el_target 
        byte sub_req 
        byte sub_connect 
        byte no_ant 
        byte ant_id(0:ANTENNACOUNT_1-1) 
        character*(12) usr_host 
        byte usr_req 
        byte usr_connect 
        byte no_pant 
        byte pant_id(0:ANTENNACOUNT_1-1) 
        byte pant_addr(0:ANTENNACOUNT_1-1) 
        integer pantmask 
        integer cmd_retry 
        real az_error(0:ANTENNACOUNT_1-1) 
        real el_error(0:ANTENNACOUNT_1-1) 
        real az_offset 
        real el_offset 
        byte status(0:ANTENNACOUNT_1-1,0:10-1) 
        character*(1) innertrk 
        record / RFSTAT /rfstat 
        record / IFSTAT /ifstat 
        record / BBSTAT /bbstat 
        record / FCONSTAT /fconstat 
        record / TURRSTAT /turrstat 
        end structure



        structure /PROCESS/
        character*(20) name 
        integer tcpport 
        integer online_id 
        character*(4) rights 
        integer pid 
        integer debuglevel 
        integer sock_id(0:2-1) 
        integer status(0:2-1) 
        integer tcp_pkt_no(0:2-1) 
        integer tcp_local_err(0:2-1) 
        integer tcp_remote_err(0:2-1) 
        end structure



        structure /PROCESS_TABLE/
        character*(80) configfile 
        character*(80) version 
        character*(12) hostname 
        integer max_process 
        integer max_auto_process 
        byte rev_map(0:256-1) 
        record / PROCESS /process(0:MAXPROCESS-1) 
        end structure



        structure /LOG_TABLE/
        integer plogopen 
        character*(80) filename(0:MAX_LOG_FILE-1) 
        byte owner(0:MAX_LOG_FILE-1) 
        integer file_pointer(0:MAX_LOG_FILE-1) 
        end structure



        structure /ONLINE/
        character*(40) program_id 
        character*(40) struct_id 
        character*(80) online_path 
        record / OBSDATE /today 
        record / SITE /site 
        character*(SOMELEN) tstring 
        integer btime 
        character*(SOMELEN) datestring 
        character*(SOMELEN) lststring 
        integer shm_status 
        integer packet_no 
        integer log_time 
        integer main_mesg_no 
        character*(MESG_LEN) main_mesg(0:NO_MAIN_MESG-1) 
        integer response_no 
        character*(MESG_LEN) response_text(0:NO_MAIN_MESG-1) 
        integer command_no 
        byte command(0:COMMAND_LEN-1,0:NO_COMMAND-1) 
        integer abcsactive(0:ANTENNACOUNT_1-1) 
        record / ABC /abcarray(0:ANTENNACOUNT-1) 
        record / CEBABC /cebabc(0:2-1) 
        record / COMHSTAT /comhstat 
        record / SUBARRAY /subarray(0:MAX_SUBARRAY-1) 
        record / FLAGS /flags 
        record / CMD_HISTORY /cmd_history 
        record / CMD_MONITOR /cmd_monitor 
        integer decodeerr 
        integer talkdata 
        integer cmd_file 
        record / QSTATUS /qsts(0:MAX_DESTNS_1-1,0:MAX_SOURCES_1-1) 
        record / DAS_CNTL /das_cntl 
        record / PROCESS_TABLE /p_table 
        record / LOG_TABLE /log_table 
        end structure

