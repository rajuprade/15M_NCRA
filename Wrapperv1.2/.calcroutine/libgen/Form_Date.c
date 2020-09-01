/* Form_Date
This routine forms a datestring 

*/
#include <time.h>

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
