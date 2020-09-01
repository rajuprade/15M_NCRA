/*    FANGLE - convert string to angle in radians
	!!! Fortran Callable version 
	used in localaips.a
-*/
 #include<stdio.h>
 #include<stdlib.h>

#define MAX_PARTS  3
#define UNDEFINED  0
#define ARC        1
#define TIME       2
#define SEC_TO_RAD 0.0000048481368110954
 
#define ISDIGIT(c) (('0' <= c) && (c <= '9'))

/* added 4 declarations to compile with gcc ..usha */
static int parse_ang();
static int get_units();
static int value_check();
static double to_secs();
 
    static struct angle
    {
        double value;
        int    val_type;
        char   unit;
    } ang_part[MAX_PARTS] = {0};
 
    static int
        error = 0,
/*        units[MAX_PARTS] = 0;*/
/* changed by usha for compiling with gcc */
        units[MAX_PARTS] = {0};

 
/***************************************************************************/
/*++ */
double fangle_(string,ierr)
    char *string;
    int *ierr;
/*
%%  convert a string to an angle in radian measure
 
    The null-terminated input string may be:
        <decimal #>     ** Direct input of radians **
        <decimal #><delimiter>
        <integer><delimiter><decimal # < 60>[<delimiter>]
        <int><delim><int < 60><delim><dec # < 60>[<delim>]
    The delimiters are from the set (D, d, ', ", H, h, M, m, S, s).
    They must be in descending order (e.g.: minutes before seconds), and
    arc-measure must NOT be mixed with hour-angle measure.
    A sign may immediately preceed the first digit in the string.
    Leading blanks are permitted.
    The final delimiter is optional.  It will default to the next smaller
    unit than the preceeding delimiter, in the same system of measure.
    If any error is detected in the input string, 0.0 is returned.
---
LANGUAGE:  C
ENVIRONMENT:  Any standard C.
TESTED:  85Oct04  by D. King, together with 'sangle' and 'stime'.
         85nov05  D. King  version 1.1  (compiled and ran -- Alcyon;
                   compiled but did not try to run -- Whitesmiths)
::  convert  angle  string
 
EXTERNAL REFERENCES:  None
 
++$  AUDIT TRAIL
  1.0  85Oct04   D. King   Initial submission.
  1.1  85nov05   D. King   Make Whitesmiths compiler happy by:
                             1. initializing externals (to zero);
                             2. resolving function-external name conflict.
--$
 
**
    EXAMPLES OF INPUT
 
        LEGAL
             1.234           direct input of 1.234 radians
             57d17'44.8"     converts to 1.0 radians
             12d13.6"        minutes field omitted
             12d22.8'        seconds field omitted, note that minutes
                                       may be non-integer in this case
             123.45'         if only one unit is specified, it may be
                                       non-integer and any size
             -123.45"        minus sign is allowed
             -12H13m14.56S   hour-angle, upper-lower case may be mixed
                12h13s       leading blanks are allowed
             75'15"          minutes may be greater than 60 if they are the
                                       first unit specified
             13h45.6         unspecified unit defaults to minutes (time)
             17'32.65        unspecified unit defaults to arc-seconds
 
        NOT LEGAL  (returned value will be 0.0)
             12d-13'14"      sign must be first non-blank character
             12d13m14s       arc-measure may not be mixed with time-measure
             12d13"14'       units out of order
             12d75'14"       minutes and seconds must be less than 60 (except
                                       when they are the first unit specified)
             12h13m75s       ditto
             12h 13m 14s     embedded blanks not permitted
             - 12h13m14s     ditto
             12.3h13m14s     only the last unit may have a decimal point
             12h13.5m22s     ditto
             12h13m14.5se    string MUST terminate after third delimiter
             18s46.77        unspecified unit can't default to less than second
-*/
#define version 1.1
 
#define ERROR_CHECK if (error != 0){*ierr=error; return (0.0);}


{
    int
        sign     = 1,
        nparts,
        measure;
 
    double
        radians,
        seconds,
        to_secs();
 
    error = 0;               /*  necessary, since error is static external  */
    *ierr = 0;
    while (*string == ' ' || *string == '\t')
        string++;
 
    if (*string == '+')
        string++;
    if (*string == '-')
    {
        sign = -1;
        string++;
    }
 
    nparts = parse_ang(string);
    ERROR_CHECK
 
/*
**      check for special case of radians entered
*/
    if (ang_part[0].unit == '\0')
        radians = ang_part[0].value;        /*  units are already radians   */
    else
    {
        measure = get_units(nparts);
        ERROR_CHECK
 
        value_check(nparts);
        ERROR_CHECK
 
        seconds = to_secs(nparts);
        ERROR_CHECK
        if (measure == TIME)
            seconds *= 15.0;
        radians = seconds * SEC_TO_RAD;
    }
 
    if (sign == -1)
        return (-radians);
    else {
        fprintf(stderr, "fangle_(): string %s radian %g \n",(char *)string, radians); 
        return (radians);
    }
}
 
/************************************************************************/
  static int
parse_ang(string)
    char *string;
/*
**  Parse the string into numeric values, indicators for the types
**  (integer or float) of the values, and the characters which denote
**  the units of measure.  Returns the number of elements in the
**  compound number.
**      numeric type codes:
**                  0 ==> integer;
**                  1 ==> floating.
*/
 
{
    int  np  = 0;
    register char *s;
    double  value, power;
 
    s = string;
 
    while (np < MAX_PARTS)
    {
        if (!ISDIGIT(*s) && (*s != '.'))
        {                       /*  ERROR CODE 1                            */
            error = 1;          /*      unexpected non-numeric character    */
            return (np);
        }
        value = 0.0;
        power = 0.0;
        while (ISDIGIT(*s))
            value = value * 10.0 + (*s++ - '0');
        if (*s == '.')
        {
            s++;
            power = 1.0;
            while(ISDIGIT(*s))
            {
                value = value * 10.0 + (*s++ - '0');
                power *= 10.0;
            }
            value /= power;
        }
 
        ang_part[np].value = value;
        if (power == 0.0)
            ang_part[np].val_type = 0;
        else
            ang_part[np].val_type = 1;
        ang_part[np].unit = *s;
 
        np++;
        if (*s == '\0')
            break;          /*  end of string detected after number         */
        s++;
        if (*s == '\0')
            break;          /*  end of string detected after character      */
    }
    if (*s != '\0')
    {                           /*  ERROR CODE 2                            */
        error = 2;              /*      string does not end after           */
        return (np);            /*      MAX_PARTS delimiting characters     */
    }   
    return (np);
}
 
/****************************************************************************/
  static int
get_units(np)
    int np;             /*  number of parts to the compound number          */
/*
**  Encode the delimiting characters into the global 'unit' array.
**      Codes:  1 ==> degrees or hours;
**              2 ==> minutes;
**              3 ==> seconds.
**  Check for:
**      1.  Proper order of units (a smaller unit may not preceed a larger).
**      2.  Consistent system of measurement (time and arc may not be mixed).
**      3.  Improper defaulting (can't default to a unit smaller than seconds).
**
**  Returns code for the system of measurement.
*/
{
    int measure[MAX_PARTS],
        i;
 
    for (i = 0; i < np; i++)
    {
        switch (ang_part[i].unit)
        {
          case 'D':
          case 'd':
            units[i] = 1;
            measure[i] = ARC;
            break;
          case 'H':
          case 'h':
            units[i] = 1;
            measure[i] = TIME;
            break;
          case '\'':
            units[i] = 2;
            measure[i] = ARC;
            break;
          case 'M':
          case 'm':
            units[i] = 2;
            measure[i] = TIME;
            break;
          case '"':
            units[i] = 3;
            measure[i] = ARC;
            break;
          case 'S':
          case 's':
            units[i] = 3;
            measure[i] = TIME;
            break;
 
          default:
            error = 11;         /*  ERROR CODE 11                           */
            return (0);         /*      delimiter not valid                 */
            break;
 
          case '\0':
            if (i == 0)         /*  case of single element and null         */
            {                   /*      delimiter should have been handled  */
                units[0] = UNDEFINED;   /*  before we got here, but do it   */
                measure[0] = UNDEFINED; /*  anyway.                         */
            }
            else
            {
                units[i] = 1 + units[i - 1];    /*  default to next smaller */
                measure[i] = measure[i - 1];    /*    unit & same measure   */
            }
            break;
        }
    }
 
    /*
    **  Check for improper unit characters
    **      Note that if there is only 1 element, no check is needed.
    */
    for (i = 1; i < np; i++)
    {
        /*  Check that units are in order                                   */
 
        if (units[i] <= units[i-1])
        {                           /*  ERROR CODE 12                       */
            error = 12;             /*    units out of order                */
            return (UNDEFINED);     /*      e.g.:  seconds before minutes   */
        }
 
        /*  Check that system of measure is consistent.                     */
 
        if (measure[i] != measure[i-1])
        {                           /*  ERROR CODE 13                       */
            error = 13;             /*      time and arc measure are mixed  */
            return (UNDEFINED);
        }
 
        /*  Check for improper default units.                               */
 
        if (units[i] > MAX_PARTS)
        {                           /*  ERROR CODE 14                       */
            error = 14;             /*    attempt to default beyond seconds */
            return (UNDEFINED);
        }
    }
 
    return (measure[0]);
}
 
/****************************************************************************/
  static int
value_check(np)
    int np;     /*  number of elements in compound number  */
/*
**  Check for valid numeric values.
**      1.  Only the last number may be floating.
**      2.  Seconds and minutes are required to be less than 60.0
**              (except when string contains only seconds or minutes).
*/
{
    int i, sum = 0;
 
    for (i = 1; i < np; i++)
        if (ang_part[i].value >= 60.0)
        {                       /*  ERROR CODE 21                           */
            error = 21;         /*      minutes or seconds >= 60.0          */
            return;
        }
 
    for (i = 0; i < np; i++)
        sum += ang_part[i].val_type;
    if (sum > 1)                /*  ERROR CODE 22                           */
        error = 22;             /*      too many floating point numbers     */
    if (sum == 1 && (ang_part[np-1].val_type != 1))
        error = 23;             /*  ERROR CODE 23                           */
                                /*      floating number in wrong place      */
    return;
}
 
/****************************************************************************/
  static double
to_secs(np)
    int np;     /*  number of elements in compound number  */
/*
**  Convert the compound number to seconds
**      without regard to the system of measure.
*/
{
    int i;
 
    double
        seconds = 0;
    static double
        conv_factor[4] = {  0,      /*   not used               */
                         3600,      /*   deg (hr) to seconds    */
                           60,      /*   minutes to seconds     */
                            1};     /*   seconds to seconds     */
 
    for (i = 0; i < np; i++)
        seconds += conv_factor[units[i]] * ang_part[i].value;
 
    return (seconds);
}
 
