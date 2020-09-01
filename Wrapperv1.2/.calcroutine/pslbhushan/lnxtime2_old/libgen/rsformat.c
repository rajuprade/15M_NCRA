#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define DEGPRAD 57.29577951          /* degrees per radian         */
#define HRSPRAD DEGPRAD / 15.0       /* hours per radian           */
#define COLON ':'
#define SIXTY 60.0            
#define AZERO 48            /* digits to ascii converter */
#define MOVECH(xx,yy,zz) strncpy(yy,xx,zz)

/*++
%% Returns pointer to ascii string containing time (ra, ha) or
   angular position (dec); useful for printing.
---

LANGUAGE:  C

ENVIRONMENT:  VME or VERSAdos

:: convert ascii

++$ AUDIT TRAIL

1.0  88 apr29  B. Meredith  Initial submission.

--$
-*/

/*=================================================================*/
char *rformat(ark)     /* returns pointer to ascii string   */
double *ark;
/*=================================================================*/

{
char *retasc2(short ), *retasc3(short ), *retascf(double *);

static char s1[13];
short i, j, k;
double arg=*ark;

for(i=0;i<13;i++)s1[i]='\0';
arg = arg * HRSPRAD;                        /* convert to hours    */
arg = (arg >= 0.0) ? arg + .000014 : arg - .000014;
i = (short) arg;                            /* i is integer hours  */
k = abs(i);
if(arg < 0.) arg=0.;
arg = SIXTY * (arg - (float) k);
j = (short) arg;                            /* j is integer min    */
arg = SIXTY * (arg - (float) j);            /* arg is float secs   */

MOVECH(retasc3(i), &s1[0], 4);              /* hours to string     */
MOVECH(retasc2(j), &s1[5], 2);              /* minutes to string   */
MOVECH(retascf(&arg), &s1[8], 4);            /* seconds to string   */
s1[4] = COLON;
s1[7] = COLON;
s1[12] = '\0';
if(s1[1] == '0')             /* if degs only 2 digits, change ptr  */
    {
    s1[1] = s1[0];
    s1[0] = ' ';
    return(&s1[1]);
    }
return(s1);
}

/*=================================================================*/
char *sformat(ark)/* returns pointer to ascii string        */
double *ark;
/*=================================================================*/

{
char *retasc2(short ), *retasc3(short ), *retascf(double *);

static char s1[13];
short i, j, k;
double arg=*ark;
arg = arg * DEGPRAD;                   /* convert to degrees       */
arg = (arg >= 0.0) ? arg + .000014 : arg - .000014;
i = (short) arg;                       /* i is integer degrees     */
k = abs(i);
if(arg < 0.) arg=0.;
arg = SIXTY * (arg - (float) k);
j = (short)arg;                        /* j is integer minutes     */
arg = SIXTY * (arg - (float) j);       /* arg is float seconds     */

MOVECH(retasc3(i), &s1[0], 4);         /* degrees to string        */
MOVECH(retasc2(j), &s1[5], 2);         /* minutes to string        */
MOVECH(retascf(&arg), &s1[8], 4);       /* seconds to string        */
s1[4] = COLON;
s1[7] = COLON;
s1[12] = '\0';
if(s1[1] == '0')             /* if degs only 2 digits, change ptr  */
    {
    s1[1] = s1[0];
    s1[0] = ' ';
    return(&s1[1]);
    }
return(s1);
}

/*=================================================================*/
char *retasc2(arg)    /* returns pointer to ascii string    */
short arg;
/*=================================================================*/

{
static char s1[3];
if(arg < 0  |  arg > 99)  return("**");     /* invalid arg return */
s1[1] = arg % 10 + AZERO;                   /* make ascii */
s1[0] = arg / 10 + AZERO;                   /*     "      */
s1[2] = '\0';
return(s1);
}

/*=================================================================*/
char *retasc3(arg)    /* returns pointer to ascii string    */
short arg;
/*=================================================================*/

{
int i;
char sign, space = ' ', minus = '-';
static char s1[5];
if(arg < 0)
    {
    arg = -arg;
    sign = minus;
    }
else
    {
    sign = space;
    }

if(arg > 999)  return("****");    /* invalid arg return */

for(i = 0; i < 4; i++)  s1[i] = space;

s1[4] = '\0';

for(i = 0; i < 4; i++)
    {
    s1[3 - i] = arg % 10 + AZERO;      /* make ascii */
    arg = arg / 10;
    }
s1[0] = sign;
return(s1);
}

/*=================================================================*/
char *retascf(arg)    /* returns pointer to ascii string    */
double *arg;
/*=================================================================*/

{
static char s1[4];
short k;

k = (short) *arg;
if(k < 0  |  k > 99)  return("****");  /* invalid arg return */
s1[1] = k % 10 + AZERO;                /* make ascii */
s1[0] = k / 10 + AZERO;                /*     "      */
k = (short) ((*arg - (short) *arg) * 10.0);
s1[3] = k + AZERO;                     /*     "      */    
s1[2] = '.';
return(s1);
}
