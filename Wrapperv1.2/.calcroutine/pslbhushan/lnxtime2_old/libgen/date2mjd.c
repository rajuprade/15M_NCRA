/*
%% convert date string to Modified Julian Date(date2mjd) & vice versa(mjd2date)
---
:: Julian date MJD date2mjd mjd2date fdate sdate
LANGUAGE:  C
ENVIRONMENT:  Any standard C
++$ AUDIT TRAIL
1.0  85Aug29  B.Clark & D.King  Initial Submission (of sdate & fdate)
2.0  87may27  R. Heald		Combine sdate & fdate, Create mjd & date
2.1  87jun10  R. Heald          DATE2MJD converts years 0-49 to 2000-2049 &
				50-99 to 1950-1999 to conform w/ NRAO Standard, 
				MJD2DATE always returns 4-digit year
--$
-*/
static int monlen[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
static char monlist[] = "\
  JANUARY FEBRUARY    MARCH    APRIL      MAY     JUNE\
     JULY   AUGUSTSEPTEMBER  OCTOBER NOVEMBER DECEMBER";
#define ITEMLEN 9	/* length of each item in monlist[] */
#define AD 678576	/* 2,400,000 (difference between Julian Date and
		Modified Julian Date) minus # days from jan 1, 4713 BC 
		(beginning of Julian calendar) */
/*++********************************************************************/
long date2mjd(datestr)	/* convert date string to MJD */
char *datestr;	/* input date string pointer */
/***********************************************************************/
/*  DATE2MJD decodes the given date string <datestr> and returns the 
equivalent Modified Julian Date.  The string may be either in the form 
yymmmdd (e.g. 85may03) or yyyymmmdd.  If the string cannot be decoded 
correctly zero is returned.  
---
If the year is less than 100, years 0 to 49 are converted to 2000 to 
2049, while years 50-99 are converted to 1950 to 1999.  Months need not 
be three characters - they may be as much as the full month name or as 
little as needed to ensure uniqueness.  If they are not unique, zero 
will be returned.  The year and month are required, but the day is 
optional (0 is assumed).  Leading blanks are ignored.  String is 
terminated by first unreconized character.

EXAMPLES:
      date-string   returned MJD
      -----------   ------------
	85may03		46188 (year assumed 1985)
	11may03		55684 (year assumed 2011)
	00may03		51667 (year assumed 2000)
	2000may03	51667 (same)
	85f1		46097 (1985feb01)
	85feb		46096 (MJD for feb 0 = jan 31)
	85november	46369 (MJD for nov 0 = oct 31)

ILLEGAL:
	1985    (month is required -- use 1985jan to get 1985jan0)
	85ma03  ('ma' is not unique -- could be mar or may)
	may03   (year is required)  
-*/
{
    char monstr[20], *monptr;
    int i, iyr, iday, imon, leap;
    long jd;

    /* ignore leading blanks */
    while(*datestr == ' ')datestr++;

    /* get year from string setting iyr = integer year */
    iyr = 0;
    if(*datestr < '0' || *datestr > '9')return(0);  /* year is required */
    while(*datestr >= '0' && *datestr <= '9')
	iyr = iyr * 10 + *datestr++ -'0';

    /* if year < 100 add its assumed prefix */
    if(iyr < 50)iyr += 2000;
    if(iyr < 100)iyr += 1900;

    /* set leap = 1 if current year is leapyear, otherwise = 0 */
    leap = (iyr % 4 == 0) ? 1 : 0;
    if(iyr % 100 == 0)leap = 0;
    if(iyr % 400 == 0)leap = 1;

    /* get month from string setting monstr = month string */
    monptr = monstr;
    while(*datestr >= 'a' && *datestr <= 'z'
	|| *datestr >= 'A' && *datestr <= 'Z')*monptr++ = *datestr++;
    if(monptr == monstr)return(0);		/* month is required */

    /* convert month name to integer (jan=0) */
    *monptr = '\0';
    cvrtuc(monstr);		/* convert to upper-case */
    if((imon = srclist(monstr, monlist, ITEMLEN)) < 0)return(0);  /* no match */

    /* get day from string setting iday = integer day */
    iday = 0;
    while(*datestr >= '0' && *datestr <= '9')
	iday = iday * 10 + *datestr++ -'0';

    /* check for day > month allows */
    if(imon != 1 && iday > monlen[imon])return(0);
    if(imon == 1 && iday > monlen[1] + leap)return(0);
 
    /* calculate the number of days up to this year */
    iyr--;
    jd = iyr * 365L + iyr / 4 - iyr / 100 + iyr / 400;

    /* calculate number of days in this year */
    for(i = 0; i < imon; i++)jd += monlen[i];
    if(imon >= 2)jd += leap;

    return(jd + iday - AD);
}
/*++********************************************************************/
char *mjd2date(mjd, datestr)	/* convert MJD to date string */
long mjd;	/* given Modified Julian Date */
char *datestr;	/* returned date string ('\0' terminated) */
/***********************************************************************/
/*  MJD2DATE converts the given date <mjd> to the form yyyymondd and 
stores it in the string <datestr>.  The string will be nine characters 
in length plus a '\0' terminator.  If the date does not fall between 
0001JAN01 AD (MJD = -678,575) and 10000JAN00 AD (MJD = 2,973,483) the 
string "*********" (9 *'s plus terminator) will be returned.  MJD2DATE 
returns the original pointer to the date string.  
---
-*/
{
    char *rtn_ptr, *p;
    int icen4, icen, iyr4, iyr, imon, iday, i;

#define oops {\
for(i = 0;i < 9; i++)*datestr++ = '*';\
*datestr = '\0';\
return;\
}
    /* save string pointer for return */
    rtn_ptr = datestr;

    /* calc days since jan 1 1 AD (Gregorian Calendar) */
    if((mjd += AD - 1) < 0)oops;

    /* calc number of fours of Gregorian centuries */
    if((icen4 = mjd / 146097) > 24)oops;

    /* calc number of centuries since last 
	fours of Gregorian centuries (e.g. since 1600 or 2000) */
    mjd -= (icen4 * 146097);
    if((icen = mjd / 36524) == 4)icen = 3; 

    /* calc number of quadrenia(four years) since jan 1, 1901 */
    mjd -= (icen * 36524);
    iyr4 = mjd / 1461;

    /* calc number of years since last quadrenia */
    mjd -= (iyr4 * 1461);
    if((iyr = mjd / 365) == 4)iyr = 3;

    /* calc number of months, days since jan 1 of current year */
    iday = mjd - iyr * 365;
    for(imon = 0; iday >= 0; imon++)
	iday -= monlen[imon] + ((iyr == 3 && imon == 1) ? 1 : 0);
    imon--;		/* restore imon, iday to last loop value */
    iday += monlen[imon] + ((iyr == 3 && imon == 1) ? 1 : 0);

    /* calc year */
    iyr = icen4 * 400 + icen * 100 + iyr4 * 4 + iyr + 1;

    /* pack year into the string */
    *datestr++ = iyr / 1000 + '0';
    *datestr++ = (iyr % 1000) / 100 + '0';
    *datestr++ = (iyr % 100) / 10 + '0';
    *datestr++ = (iyr % 10) + '0';

    /* pack month into the string */
    for(p = imon * ITEMLEN + monlist; *p == ' '; p++);  /* get to 1st char */
    for(i = 0; i < 3; i++)*datestr++ = *p++;	/* just 3 chars */

    /* pack day into the string */
    *datestr++ = ++iday / 10 + '0';	/* iday was # days since 1st of month */
    *datestr++ = iday % 10 + '0';
    *datestr++ = '\0';            /* all done now */

    return(rtn_ptr);
}
/*++********************************************************************/
