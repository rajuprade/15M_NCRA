///////////////////////////////////////////////////////////////////////////
// PROJECT           : GMRT
// File              : IO_DEF.H
// Author            : 
// Version           :
// Last Modification : 10-09-2007
// Reason            :  
///////////////////////////////////////////////////////////////////////////

#ifndef __IODEF_H__
#define __IODEF_H__

#define     NO_OF_AXIS      2
#define     max_dgtl_ips    48
#define     max_dgtl_ops    16
#define     max_anlg_ips    12
#define     max_anlg_ops    2
#define     max_stat_leds   36

#define DIP_AZSTWG        0
#define DIP_AZSTWRLSG     1
#define DIP_AZON_IP       2
#define DIP_AZSTPOS       3
#define DIP_AZM1OL        4
#define DIP_AZM2OL        5
#define DIP_AZ1BRKD       6
#define DIP_AZ2BRKD       7
#define DIP_AZFLMTCW      8
#define DIP_AZFLMTCCW     9
#define DIP_AZC1ST        10
#define DIP_AZC2ST        11
#define DIP_AZA1OL        12
#define DIP_AZA2OL        13
#define DIP_AZSTWD        14
#define DIP_AZSTRLSD      15

#define DIP_ELSTWG        16
#define DIP_ELSTRLSG      17
#define DIP_ELON_IP       18
#define DIP_ELSTPOS       19
#define DIP_ELM1OL        20
#define DIP_ELM2OL        21
#define DIP_EL1BRKD       22
#define DIP_EL2BRKD       23
#define DIP_ELFLMTUP      24
#define DIP_ELFLMTDN      25
#define DIP_ELC1ST        26
#define DIP_ELC2ST        27
#define DIP_ELA1OL        28
#define DIP_ELA2OL        29
#define DIP_ELSTWD        30
#define DIP_ELSTRLSD      31

#define DIP_AZ_CWRP_SIGN  32
#define DIP_MD_MAN_IP     33
#define DIP_MD_LOC_IP     34
#define DIP_MD_RMT_IP     35
#define DIP_PS1_OK        36
#define DIP_PS2_OK        37
#define DIP_PH3_PS_OK     38
#define DIP_SPARE39       39
#define DIP_SPARE40       40
#define DIP_EM_PARK1      41
#define DIP_IP42          42
#define DIP_CWRP          43
#define DIP_SPARE44       44
#define DIP_SPARE45       45
#define DIP_SPARE46       46
#define DIP_SPARE47       47

#define DOP_AZON_OP       0
#define DOP_AZSTW         1
#define DOP_AZSTWRLS      2
#define DOP_AZ1SIG        3
#define DOP_AZCAGE        4
#define DOP_AZPOWER_ON    5
#define DOP_AZ2SIG        6
#define DOP_ELON_OP       7
#define DOP_ELSTW         8
#define DOP_ELSTWRLSW     9
#define DOP_EL1SIG        10
#define DOP_ELCAGE        11
#define DOP_ELPOWER_ON    12
#define DOP_EL2SIG        13
#define DOP_EMPARK        14
#define DOP_SSC_OK        15

#define AIP_AZM1CRNT      0 
#define AIP_AZM2CRNT      1 
#define AIP_ELM1CRNT      2 
#define AIP_ELM2CRNT      3 
#define AIP_AZTACHO1      4 
#define AIP_AZTACHO2      5 
#define AIP_ELTACHO1      6 
#define AIP_ELTACHO2      7 
#define AIP_AZPOTPOS      8 
#define AIP_ELPOTPOS      9 
#define AIP_SPARE_10      10
#define AIP_SPARE_11      11

#define AOP_AZ_DEMSPD     0 
#define AOP_EL_DEMSPD     1 


#define STAT_EL_ENC_FAULT   0 
#define STAT_EL_RUN         1 
#define STAT_EL_UP_PLMT     2 
#define STAT_EL_UP_FLMT     3 
#define STAT_EL_DN_PLMT     4 
#define STAT_EL_DN_FLMT     5 
#define STAT_EL_AMP_OL      6 
#define STAT_EL_STW_POS     7 
#define STAT_EL_STWD        8 
#define STAT_EL_STWRLSD     9 
#define STAT_EL_BRK1        10
#define STAT_EL_BRK2        11

#define STAT_AZ_ENC_FAULT   12
#define STAT_AZ_RUN         13
#define STAT_AZ_CC_PLMT     14
#define STAT_AZ_CC_FLMT     15
#define STAT_AZ_CW_PLMT     16
#define STAT_AZ_CW_FLMT     17
#define STAT_AZ_AMP_OL      18
#define STAT_AZ_STW_POS     19   
#define STAT_AZ_STWD        20
#define STAT_AZ_STWRLSD     21
#define STAT_AZ_BRK1        22
#define STAT_AZ_BRK2        23

#define STAT_MD_MAN        24
#define STAT_MD_LOC        25
#define STAT_MD_REM        26
#define STAT_AC_OK         27
#define STAT_DC_OK         28
#define STAT_SSCOK         29
#define STAT_POSG          30
#define STAT_TRKG          31
#define STAT_SLWG          32
#define STAT_CWRP_SIGN     33
#define STAT_WND50         34
#define STAT_WND80         35

#endif


