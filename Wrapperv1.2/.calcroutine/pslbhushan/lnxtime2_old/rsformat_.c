/***************

	Needs to be fully debugged for compatibility with FORTRAN
	Calling parameters different from what is described in document

						Pramesh
						3 March 92
								  */

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

static char *retasc2();
static char *retasc3();
static char *retascf();
/*=================================================================*/
void rformat_(barg,s1)     /* returns pointer to ascii string   */
unsigned char  *barg;                    /* in form shhh:mm:ss.s   arg in rad */
char s1[];
/*=================================================================*/

{
char *retasc2(), *retasc3(), *retascf();
double fabs();
double arg;

short i, j, k;
union{
    double x;
    unsigned char xx[8];
}xxx;

for(i=0;i<8;i++)xxx.xx[i]=*(barg+i);
arg = xxx.x * HRSPRAD;                        /* convert to hours    */
/* printf("*barg = %f , arg= %f\n",*barg,arg); */
arg = (arg >= 0.0) ? arg + .000014 : arg - .000014;
i = (short) arg;                            /* i is integer hours  */
k = abs(i);
arg = fabs(arg);
arg = SIXTY * (arg - (double) k);
j = (short) arg;                            /* j is integer min    */
arg = SIXTY * (arg - (double) j);            /* arg is float secs   */

MOVECH(retasc2(i), &s1[0], 2);              /* hours to string     */
MOVECH(retasc2(j), &s1[3], 2);              /* minutes to string   */
MOVECH(retascf(arg), &s1[6], 4);            /* seconds to string   */
s1[2] = COLON;
s1[5] = COLON;
s1[11] = '\0';
return;
}

/*=================================================================*/
void sformat_(barg,s1)/* returns pointer to ascii string        */
unsigned char *barg;              /* in form sddd:mm:ss.s    arg in radians  */
char s1[];
/*=================================================================*/

{
char *retasc2(), *retasc3(), *retascf();
double fabs();
double arg;

short i, j, k;

union{
    double x;
    unsigned char xx[8];
}xxx;

for(i=0;i<8;i++)xxx.xx[i]=*(barg+i);
arg = xxx.x* DEGPRAD;                   /* convert to degrees       */
arg = (arg >= 0.0) ? arg + .000014 : arg - .000014;
i = (short) arg;                       /* i is integer degrees     */
k = abs(i);
arg = fabs(arg);
arg = SIXTY * (arg - (double) k);
j = (short)arg;                        /* j is integer minutes     */
arg = SIXTY * (arg - (double) j);       /* arg is float seconds     */

MOVECH(retasc3(i), &s1[0], 4);         /* degrees to string        */
MOVECH(retasc2(j), &s1[5], 2);         /* minutes to string        */
MOVECH(retascf(arg), &s1[8], 4);       /* seconds to string        */
s1[4] = COLON;
s1[7] = COLON;
s1[12] = '\0';
return;
}

/*=================================================================*/
static char *retasc2(arg)    /* returns pointer to ascii string    */
short arg;                   /* of 2 chars, null                   */
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
static char *retasc3(arg)    /* returns pointer to ascii string    */
short arg;                   /* of sign, 3 chars, null             */
/*=================================================================*/

{
int i;
char sign, plus = '+', minus = '-';
static char s1[5];
if(arg < 0)
    {
    arg = -arg;
    sign = minus;
    }
else
    {
    sign = plus;
    }

if(arg > 999)  return("****");    /* invalid arg return */

for(i = 0; i < 4; i++)  s1[i] = ' ';

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
static char *retascf(arg)    /* returns pointer to ascii string    */
double arg;                   /* of 2 chars, period, char           */
/*=================================================================*/

{
static char s1[4];
short k;

k = (short) arg;
if(k < 0  |  k > 99)  return("****");  /* invalid arg return */
s1[1] = k % 10 + AZERO;                /* make ascii */
s1[0] = k / 10 + AZERO;                /*     "      */
k = (short) ((arg - (short) arg) * 10.0);
s1[3] = k + AZERO;                     /*     "      */    
s1[2] = '.';
return(s1);
}
