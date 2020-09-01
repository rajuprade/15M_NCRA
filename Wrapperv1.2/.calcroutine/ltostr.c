long ltostr(number, string, width, sign)
    long number;             /*  number to be converted              */
    char *string;            /*  receiving string                    */
    long width;              /*  minimum width of numeric field      */
    long sign;               /*  if negative, forces '-' in output   */
 
/*
%%  convert long integer to string representation
    returns:  number of characters appended to string
 
    Output digits are always right-justified in the field.  If 'width' is
    positive, blank fill is used.  Leading zero fill is used when 'width'
    is negative.  If 'width' is less than the number of digits needed to
    express the number, the field will be expanded to the exact number
    of characters required.
 
    A minus sign is prefixed if either 'number' or 'sign' is negative.
    (This permits a 'signed zero' to be generated.)
    The minus sign is the first character in the string if leading zeros
    are requested, else it is the character immediately preceeding the
    most significant digit.
 
    The output string DOES NOT have a terminating null.
---
LANGUAGE:  C
ENVIRONMENT:  Any standard C.
TESTED: 3 oct 85, D. King, using Alcyon C.
::  convert   string   format
 
++$ AUDIT TRAIL
1.0  85Oct04   D. King   Initial submission.
--$
 
-*/
#define version  1.0
 
{
        register char *left, *s;
 
        char padch, tempch;
        long nch = 0;
 
    s = string;
 
    if (number < 0)
    {
        sign = -1;
        number = -number;
    }
 
    if (sign < 0L && width < 0L)
    {                    /*  leading zero format, so insert minus    */
        *s++ = '-';      /*    sign in first char of the field       */
        nch = 1;
        sign = 0;
    }
 
    left = s;
 
    if (width < 0L)                    /*  set up proper fill character  */
    {
        width = -width;
        padch = '0';
    }
    else
        padch = ' ';
 
    do {                               /*  convert number  */
        *s++ = '0' + number % 10;
        nch++;
    } while ((number /= 10) > 0);
 
    if (sign < 0 && padch == ' ')      /*  blank fill format, so put     */
    {                                  /*    minus sign in front of the  */
        *s++ = '-';                    /*    most significant digit.     */
        nch++;
    }
 
    while (nch < width)      /*  pad to fill minimum field width.    */
    {
        *s++ = padch;
        nch++;
    }
 
    s--;                     /*  point to last char                       */
    while (left < s)         /*  digits were generated in reverse order,  */
    {                        /*    so re-reverse them.                    */
        tempch = *left;
        *left++ = *s;
        *s-- = tempch;
    }
    return (nch);
}
