/* Calc_Lst
This routine calculates the local sidereal time
*/
#include "display.h"
#include "MATHCNST.H"
#include "IAUCONST.H"

void Calc_Lst(sitepointer,datepointer,tp)
SITE    *sitepointer;
OBSDATE  *datepointer;
struct tm *tp;
{
	double timehours; /* time in hours */


					/* convert to hours */
	timehours = ((tp->tm_sec)/60.0+tp->tm_min)/60.0+tp->tm_hour;
	datepointer->ltime = (double)(timehours /HOUR_RAD);

					/* calculate universal time*/
	datepointer->utime = (datepointer->ltime + sitepointer->tzrad);
					/*  calculate local siderial time */
	datepointer->lstime = (double)(datepointer->gastm + ((datepointer->
	    utime)*SID_SOLAR) - (sitepointer->longitude));
	if( datepointer->lstime > TWOPI ) datepointer->lstime -=TWOPI;
	if( datepointer->lstime < (double) 0.0 ) datepointer->lstime +=TWOPI;
} 					/* end of calclst */

