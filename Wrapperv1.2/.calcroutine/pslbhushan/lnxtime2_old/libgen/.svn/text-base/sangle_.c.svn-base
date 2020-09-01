long sangle_ ( ffangle, format_str, out_string )
    unsigned char *ffangle;           /*  angle to be converted to string        */
    char   *format_str;      /*  format string                          */
    char   *out_string;      /*  string which receives converted angle  */
 
    /*  returned value (long) is number of characters appended to out_string,
          including the terminating null.   */
/*
%%  Convert floating (radians) to string (arc-measure)
 
    Conversion is to format  iiiidjj'kk.fff"   where jj and kk are always
    two digits.  The widths of the iiii and fff fields are controlled by
    an input format string of the form "m.n", where m sets the width of
    the degrees field and n sets the width of the decimal-fractional part
    of the seconds field.  If the first digit of m is zero, the degrees
    field will have leading zeros.  n may be zero, which will suppress the
    decimal point in the seconds field.  See detailed discussion for more
    information about the format string.
 
    The output is ROUNDED to the specified seconds-field precision.
---
LANGUAGE:  C
ENVIRONMENT:  Any standard C.
TESTED:  3 Oct 85 by D. King,  in conjunction with 'fangle' and 'stime'
::  angle   convert   string   arc-meas   format
 
EXTERNAL REFERENCES:
    EXTERNAL FUNCTIONS:
        in VLBCLIB:  ltostr
 
++$  AUDIT TRAIL
1.0  85Oct04    D. King    Initial submission.
--$
 
 
**  Converts a floating point number (which presumably contains an angle
**  in radian measure) to a string which represents an angle in conventional
**  arc measure.  The form of the output string is "iiiidjj'kk.ffff"\0".
**  The widths of the degrees (iiii) and fractional seconds (ffff) fields are
**  set by digit strings m and n which are obtained from the format string.
**  If m and/or n are not specified, they default to 3 and 1, respectively.
**
**  The format string is a null-terminated string of the general form "m.n",
**  where m and n are digit strings.  The forms "S" and "S.n" are also
**  permitted.  "S" means use the default values for both m and n; "S.n"
**  means use default for m and the supplied value for n.
**
**  The digit string m controls the width of the degrees field in the output
**  string.  The degrees field will be right-justified and at least m
**  characters wide. If the first digit of m is zero, zero fill will be used;
**  else blank fill will be used.  If m is omitted (format string looks like
**  ".n" or "."), the degrees field will be left-justified and have exactly
**  the number of characters needed to represent the value.
**
**  The digit string n controls the number of decimal places in the decimal
**  fraction portion of the seconds field.  If m is zero, no decimal point
**  will appear in the seconds field.
**
**  To summarize the format string:
**    "S", "s", or an indecipherable string -- use defaults of m = 3, n = 1;
**    "S.n" or "s.n" -- default m = 3; use supplied value for n;
**    "."            -- left-justify degrees, default n = 1;
**    ".n"           -- left-justify degrees, use supplied value for n;
**    "m" or "m."    -- use supplied value of m, default n = 1;
**    "m.n"          -- use supplied values for both m and n.
**
**  If m does not specify sufficient digits to represent the degrees, the
**  degrees field will be widened to the exact number of digits needed.
**
**  In Alcyon C, the maximum meaningful precision for the seconds field
**  is approximatly log10(50/angle).
-*/
#define version 1.0
 
 
#define ISDIGIT(c) ('0' <= c && c <= '9')
 
#define RAD_TO_DEG  57.295779513082
#define HALF_SEC     0.000002424068405548
 
#define UNSIGNED 0L
#define TRUE   1
#define FALSE  0
 
#define SEC_DEFAULT  1
#define DEG_DEFAULT  3
 
#define MIN_WIDTH  -2L
#define SEC_WIDTH  -2L
 
#define UNITS_CHARS "d'\""
 
{
    double
        round = HALF_SEC,
	angle;
 
    int
        end_flag  = FALSE,
        lzero_flag = FALSE;
 
    long
        deg_field = DEG_DEFAULT,
        sec_field = SEC_DEFAULT;
 
    static char units_ch[] = UNITS_CHARS;
 
 
    double
        fabs();
 
    long
        ltostr(),
        i,
        degrees,
        minutes,
        seconds,
        sign;
 
    char
        *str_start;

    union{
      double x;
      unsigned char xx[8];
    }xxx;
 
 
/*
*****    DECODE THE FORMAT STRING    *****
*/
    for(i=0;i<8;i++)xxx.xx[i]=*(ffangle+i);
    angle=xxx.x;
	/*angle=*ffangle; */
    switch (*format_str)
    {
      default:           /*  indecipherable or null string -- default all  */
      case '\0':
        end_flag = TRUE;
        break;
      case 'S':          /*  default degrees field, maybe seconds too      */
      case 's':
        format_str++;        /*  point to next char, which must be '.' if  */
        break;               /*  seconds precision is to be specified      */
      case '.':          /*  left-justify degrees                          */
        deg_field = 0;
        break;
      case '0':          /*  zero fill                                     */
        lzero_flag = TRUE;    /*  FALL-THRU to                             */
      case '1':          /*  extract degree field width from digit string  */
      case '2':
      case '3':
      case '4':
      case '5':
      case '6':
      case '7':
      case '8':
      case '9':
        deg_field = 0;
        while (ISDIGIT(*format_str))
        {
            deg_field = deg_field * 10 + *format_str - '0';
            format_str++;
        }
        break;
    }
 
    /*
    **  The format string pointer is now at the separator between fields,
    **  which must be '.' followed by a digit if there is a seconds-field
    **  format specified.
    */
 
    if ( !end_flag  &&  (*format_str++ == '.'))
    {
        if (ISDIGIT(*format_str))
        {
            sec_field = 0;
            while (ISDIGIT(*format_str))
            {
                sec_field = sec_field * 10 + *format_str - '0';
                format_str++;
            }
        }
        else
            ;      /*  no seconds-field digit string, use default   */
    }
 
/*
*****    ROUND OFF AND CONVERT RADIANS TO DEGREES, MINUTES, SECONDS    *****
*/
 
    if (angle < 0.0)                   /* save sign, work with abs value   */
    {
        sign = -1;
        angle = fabs(angle);
    }
    else
        sign = 1;
 
    for (i = 0; i < sec_field;  i++)   /* round off                        */
        round /= 10.0;
    angle += round;
 
    angle    *= RAD_TO_DEG;            /* convert                          */
    degrees   = angle;                 /*   note use of truncation         */
 
    angle     = (angle - degrees) * 60.0;
    minutes   = angle;
 
    angle     = (angle - minutes) * 60.0;
    seconds   = angle;
    angle    -= seconds;               /* angle = fractional part of secs  */
 
/*
*****    APPEND RESULT TO STRING    *****
*/
    str_start = out_string;
 
    if (lzero_flag)
        deg_field = -deg_field;
    out_string += ltostr (degrees, out_string, deg_field, sign);
    *out_string++ = units_ch[0];
 
    out_string += ltostr (minutes, out_string, MIN_WIDTH, UNSIGNED);
    *out_string++ = units_ch[1];
 
    out_string += ltostr (seconds, out_string, SEC_WIDTH, UNSIGNED);
    if (sec_field != 0)
    {
        *out_string++ = '.';
        for (i = 0; i < sec_field; i++)
            angle *= 10.0;
        seconds = angle;               /* decimal fraction is in 'seconds' */
        out_string += ltostr (seconds, out_string, -sec_field, UNSIGNED);
                                       /* use '-sec_field' to get left zeros */
    }
 
    *out_string++ = units_ch[2];
    *out_string++ = '\0';
 
    return (out_string - str_start);
}
