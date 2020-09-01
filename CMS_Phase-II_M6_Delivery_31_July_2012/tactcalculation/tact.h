#ifndef TACT_INCLUDED
#define  TACT_INCLUDED

/*
  TACT.H ID = $Id: tact.h,v 1.5 2003/06/30 10:51:55 chengalu Exp $
*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <ctype.h>
#include <malloc.h>

#define MAX_FIELD_LEN   64
#define MAX_NAME_LEN    16
#define MAX_DOC_LEN     64
#define MAX_TACT_CMD    64
#define MAX_TACT_MACRO  64
#define ANG_STR_LEN     16
#define MAX_BUFF_LEN    8192
#define MAX_MACRO_LEN   256
#define MAX_CMD_LEN     128
#define MAX_ARG         32
#define TACT_TINY       (double)1.0e-9

#ifndef TACT_SYS_DEF_FILE
#define TACT_SYS_DEF_FILE    "/usr/local/lib/tact/tactrc"
#endif

#ifndef TACT_VERSION
#define TACT_VERSION "unkown"
#endif

#ifndef PI
#define PI 3.14159265358979323846
#endif
#define LIGHTSPEED 299792458.0 /* m/s */

#define LSSEC        (double)1.0027379093 
#define RAD2DEG(x)   ((x)*180.0/PI)                      
#define DEG2RAD(x)   ((x)*PI/180.0)
#define RAD2DAY(x)   ((x)/PI*0.5)
#define DAY2RAD(x)   ((x)/0.5*PI)
#define HRS2RAD(x)   ((x)/12.0*PI)
#define RAD2HRS(x)   ((x)/PI*12.0)
#define STS2UTS(x)   ((x)/LSSEC)
#define UTS2STS(x)   ((x)/LSSEC)

/* different angle types for I/O */
enum TactAngType{
     ATP_HMS, /* hours, minutes seconds, output forced to
                 lie between 0 and 24 hours.                  */
     ATP_DMS, /* degrees, minutes, seconds, output forced
                 to lie between -180 and +180 degrees.        */
     ATP_DH,  /* decimal hours, output forced to lie between 
                 0.0 and 24.0 hours.                          */
     ATP_DD,  /* decimal degrees, output forced to lie between
                 -180 and +180 degrees.                       */
     ATP_DR,   /* decimal radians, output forced to lie between
                 -PI and +PI radians.                         */
     ATP_DLO   /* decimal longitude, output is forced to lie
                  between 0 and 360.0 degrees                 */
};

/* different possible print styles */
enum TactPrintType{
  PTP_ANG,       /* angle (double)                              */
  PTP_TIME,      /* time  (double)                              */
  PTP_REAL,      /* real number (double)                        */
  PTP_INT,       /* integer number (long)                       */
  PTP_CHAR,      /* character  (char)                           */
  PTP_STR,       /* string (char *)                             */
  PTP_NL,        /* print a newline                             */
  PTP_SP,        /* print a blank space                         */
  PTP_TB,        /* print a tab character                       */
  PTP_HELP       /* print some doccumentation                   */
};

enum VelSys{HELIOCENTRIC,TOPOCENTRIC,BARYCENTRIC,OBSERVATORY,LSR};
enum VelDef{OPTICAL,RADIO,REDSHIFT,RELATIVISTIC};

struct TactArg
{
/* Any change here should be communicated to setTstruct and shwTstruct */
  double ra;                        /* right ascention (radians)   */
  double dec;                       /* declination (radians)       */
  double dra;                       /* proper motion in ra         */
  double ddec;                      /* proper motion in dec        */
  double epoch;                     /* epoch of (ra,dec)           */
  char   eprefix;                   /* epoch prefix ('B' or 'J')   */
  double equinox;                   /* equinox of (ra,dec)         */
  double ra1;                       /* right ascention (radians)   */
  double dec1;                      /* declination (radians)       */
  double dra1;                      /* proper motion in ra1        */
  double ddec1;                     /* proper motion in dec1       */
  double px;                        /* parallax (radians)          */
  double rv;                        /* radial velocity (km/s)      */
                                    /* related defs further below  */
  double epoch1;                    /* epoch of (ra1,dec1)         */
  char   e1prefix;                  /* epoch prefix ('B' or 'J')   */
  double equinox1;                  /* equinox of (ra1,dec1)       */

  double mjd;                       /* modified julian date        */
  double gyear;                     /* greogrian year              */
  double gmonth;                    /* gregorian month             */
  double gday;                      /* gregorian day               */
  double lct;                       /* local civil time (radians)  */
  double utc;                       /* (radians)                   */
  double dut;                       /* utc+dut=ut1  (radians)      */
  double lst;                       /* LAST               (radians)*/
  double ut1;                       /* ut1 (radians)               */
  double gmst;                      /* (radians)                   */
  double gast;                      /* (radians)                   */
  double tzone;                     /* lct+tzone = utc (radians)   */

  double glong;                     /* galactic longitude (radians)*/
  double glat;                      /* galactic latitude (radians) */
  double elong;                     /* ecliptic longitude (radians)*/
  double elat;                      /* ecliptic latitude (radians) */
  double sglong;                    /* supergal longitude (radians)*/
  double sglat;                     /* supergal latitude (radians) */

  double alt;                       /* altitude (radians)          */
  double az;                        /* azimuth (radians)           */
  double ha;                        /* hour angle (radians)        */
  double pa;                        /* parallactic angle (radians) */
  double tlat;                      /* terrestrial lat (radians)   */
  double tlong;                     /* terestrial lon (radians)    */
  double height;                    /* height above MSL (m)        */

  double rise;                      /* rise time (radians)         */
  double set;                       /* set time (radians)          */
  double el_lim;                    /* elevation limit (radians)   */

  double rv1;                       /* Output radial velocity      */
  int    velsys;                    /* Input Velocity Ref Frame    */
  int    vel1sys;                   /* Output Velocity Ref Frame   */
  int    veldef;                    /* Common Vel Def (Rad/Opt...) */
  double freq;                      /* Input Frequency (MHz)       */
  int    freqsys;                   /* Input Frequency Frame       */
  double freq1;                     /* Output Frequency (MHz)      */
  double freq1sys;                  /* Output Frequency Frame      */
  char *lst_string;
  char *rise_string;
  char *set_string;
  char *uptime_string;	
  double uptime;


  int  err_precess;               /* flag for presess calculation */
  int  err_altaz;                 /* flag for Altitude-Azimuth calculation */
  int  err_riseset;               /* flag for riseser calculation*/
  int  err_dopset;                /* flag for dopset calculation */ 
  int calculateLST;
  int calculatePrecess;
  int calculateALTAZ;
  int calculateRiseSet;
  int calculategalactic;
  int calculateDopeSet;

};
typedef struct TactArg Gcord;

struct TactArg2
{
  //char ca[MAX_BUFF_LEN];            /* command arguments          */
 // struct TactMacro *tm;             /* tact macro sturcture       */
  int    nm;                        /* number of macros           */
 // struct TactCmd   *tc;             /* tact command structure     */
  int    nc;                        /* number of commands         */
 // FILE   *ofp;                      /* file pointer for output    */
  //FILE   *hfp;                      /* file pointer for help      */
 // FILE   *efp;                      /* file pointer for errors    */
};
typedef struct TactArg2 Garg;

/* macros */

struct TactMacro
{
  char name[MAX_NAME_LEN];          //* name of the macro         
  char doc[MAX_DOC_LEN];            //* one line doccumentation   
  char mc[MAX_MACRO_LEN];           //* macro commands            
};

/* generalized time/co-ordinate transformation command structure*/ 
struct TactCmd{
  char   name[MAX_NAME_LEN];          //* name of the command      
  int    (*gtf)(Gcord *gc, Garg *ga); //* pointer to the command   
  char   doc[MAX_DOC_LEN];            //* one line doccumentation  
};


int altaz      (Gcord *gc, Garg *ga);
int b2j        (Gcord *gc, Garg *ga);
int e2h        (Gcord *gc, Garg *ga);
int eq2ec      (Gcord *gc, Garg *ga);
int ec2eq      (Gcord *gc, Garg *ga);
int fhel2fobs  (Gcord *gc, Garg *ga);
int fobs2fhel  (Gcord *gc, Garg *ga);
int fobs2vhel  (Gcord *gc, Garg *ga);
int h2e        (Gcord *gc, Garg *ga);
int ha2lst     (Gcord *gc, Garg *ga);
int j2b        (Gcord *gc, Garg *ga);
int j2l        (Gcord *gc, Garg *ga);
int l2j        (Gcord *gc, Garg *ga);
int lct2lst    (Gcord *gc, Garg *ga);
int lct2utc    (Gcord *gc, Garg *ga);
int lst2ha     (Gcord *gc, Garg *ga);
int m2a        (Gcord *gc, Garg *ga);
int par_curve  (Gcord *gc, Garg *ga);
int gal2sup    (Gcord *gc, Garg *ga);
int getmdoc    (Gcord *gc, Garg *ga);
int prec       (Gcord *gc, Garg *ga);
int resetcrd   (Gcord *gc, Garg *ga);
int resetep    (Gcord *gc, Garg *ga);
int rise_set   (Gcord *gc, Garg *ga);
int setTstruct (Gcord *gc, Garg *ga);
int shwTstruct (Gcord *gc, Garg *ga);
int solcol     (Gcord *gc, Garg *ga);
int sup2gal    (Gcord *gc, Garg *ga);
int tact_print (Gcord *gc, Garg *ga);
int vhel2fobs  (Gcord *gc, Garg *ga);
int vhel2vlsr  (Gcord *gc, Garg *ga);
int vlsr2vhel  (Gcord *gc, Garg *ga);

double sla_gmst_(double *mjd);
double sla_eqeqx_(double *mjd);

int a2s(double a, char *st, int ty);
int dms2a(char *s, double *a);
int initTbuf(char *cb, char *cfl);
//int excTcmd(char *cb, long *bp, Garg *ga, Gcord *gc, struct TactCmd *tcs, //bhu
//		int *nc, struct TactMacro *tms, int *nm);                       
int getcarg(char *cb, long *bp, char *ca);
int getcmd(char *buff, long *bp, char *cm, char *ca);
int getmdef(char *cb, long *bp, char *ca);
int prarg(char *ca, char *aw[]);
int s2a(char *s, double *a);
//int setTcmd(struct TactCmd tcs[]); //bhu
int tact_err(char *s1,char *s2,...);
int getargm(char *a, char *am);


#endif







