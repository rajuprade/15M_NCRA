/*  gmrtt : This routine is getting used for displaying 
 *  the LST in online display program ondisplay.5.
 *  This LST has the routine for nutation correction
 *  Uses 'libgen.a' library which is a one of the component
 *  of ONLINE software
 *  - JPK Jan 19th, 2009
INFO				
INFO				calculates lst and writes the time
INFO				into the online display memory
INFO
INFO			routines called     time()
INFO					    localtime()
INFO					    Calc_Lst()
*/

/* 
    This routine calculates the date and Local Sidereal Time and updates
    the values in the Online Structure
    */

#include <stdio.h>
#include "display.h"
#include <time.h>
#include <math.h>
#include "MATHCNST.H"
#define STS_UNDEFINED 4

extern  double  fangle_( char *,int *);
extern  float gastm( int);
extern  int date2mjd(char *);

/* Form_Date
This routine forms a datestring
*/

char *Form_Date(d)
struct tm *d;
{
static char datestrg[13];
char *months[12]={"jan","feb","mar","apr","may","jun","jul","aug",
          "sep","oct","nov","dec"};

if(d->tm_year < 1900) d->tm_year+=1900; /* idiosyncracy of Sun Solaris whose
                                           year starts at 1900 */
sprintf(datestrg,"%4d%3s%d",(d->tm_year),months[d->tm_mon],d->tm_mday);
return(datestrg);
}

    char *Latitude=LATITUDE;
    char *Longitude=LONGITUDE;

OBSDATE today;
SITE    site ;

void	main(int argc, char **argv)
{
    int i,j,k;
    time_t clk;
    struct tm tp;
    UCHAR *tmp_ptr;
/*C unused UCHAR NLL='\0';
char *str; */
static int currhour,prevhour=-1;
char datestring[64],lststring[64], tstring[64];

    if(argc <= 1 ) {
	clk = time(NULL);
	tp=*(localtime(&clk)); 
    }else {
       tp.tm_year = atoi(argv[1]); /* year */ 
       tp.tm_mon  = atoi(argv[2]) -1 ;  /* for Form_Date Array of month */
       tp.tm_mday =  atoi(argv[3]); /*Day */ 
       tp.tm_hour = atoi(argv[4]); /* Hour */
       tp.tm_min  = atoi(argv[5]); 
       tp.tm_sec  = atoi(argv[6]);
     }
	if (currhour != prevhour)
	{
/*  strcpy(display_mem->datestring,Form_Date(&tp));
    display_mem->datestring[12] = '\0'; 
    strcpy(display_mem->today.mdate,Form_Date(&tp)); */

	        strcpy(datestring,Form_Date(&tp));
	        datestring[12] = '\0'; 
		strcpy(today.mdate,Form_Date(&tp));

/*              display_mem->today.mjd=date2mjd(display_mem->today.mdate); 
		display_mem->today.gastm=gastm(display_mem->today.mjd); 
*/
		today.mjd=date2mjd(today.mdate);
		today.gastm=gastm(today.mjd);   /* returns Greenwich Apparent Sidereal Time at Midnight*/
	}
	prevhour=currhour;

	/* get time*/
        sprintf(tstring,"%2d:%2d:%2d", tp.tm_hour,tp.tm_min, tp.tm_sec); tstring[12] = '\0'; 

    strcpy(site.name,SITE_NAME);
    site.timezone=TIME_ZONE;
    i=0;
    site.latitude=fangle_(Latitude,&i);
    site.longitude=fangle_(Longitude,&i);
    site.sinlat=sin(site.latitude);
    site.coslat=cos(site.latitude);
    site.tzrad = (site.timezone)/HOUR_RAD;

	/* get lst */
	Calc_Lst(&site ,&today,&tp);
	rformat_(&today.lstime,lststring);
	lststring[12] = '\0';
        fprintf(stderr, " I. date string %s       mdate %s    time %s \n",datestring, today.mdate, tstring);
        fprintf(stderr, "II. MJD %d      GAST %f LST %f GAST-LST %f \n", today.mjd, today.gastm, today.lstime,(today.lstime - today.gastm) );
        fprintf(stderr, "##. LSTSTRING %s  \n", lststring);
}
