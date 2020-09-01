#include <math.h>
#include "libvlba.h"

float gastm(mjd)     /* returns Greenwich Apparent Sidereal Time at Midnight*/
 int mjd;           /* on this MJD 
----
   Handles stuff mostly as integers to avoid the truncations inherent in
   the limited mantissas of float 

%% Greenwich Apparent Sidereal Time at Midnight UT1 
:: time
Language: C
Environment:  any
Tested:  87mar12 - got the correct gmstm and gastm for today and 
         yesterday, on the VAX

++$ Audit trail
1.0  87mar12  B. Clark     Initial submission
--$ 

*/

     {
     double tu;
     double gast;
     double longi, obliqui;
     long epoch, century, years, days;
     int i;

     tu = (mjd -51544.5)/36525.0;
     epoch = mjd - 15019;       /* minus Jan 0, 1900 */
     century = epoch/36525L;
     epoch -= century*36525L;
     years = epoch/365;
     epoch -= years*365;
     days = epoch;

     /* the next expression is the Greenwich Mean Sidereal Time
        at midnight UT1 */

     gast = fangle_("6h41m50.54841s",&i)            /* constant - see circ 163 */
           + fangle_("3m04.81287s",&i)*(century-1)  /* due to julian vs greg cent*/
           - fangle_("57.29071s",&i)*years          /* leap year term */
           + fangle_("3m56.55537",&i)*(days - 0.5)  /* 4m per day */
           + fangle_("0.09310s",&i)*tu*tu;          /* secular term */

     nutate (&tu, &longi, &obliqui);
     gast = gast + longi*cos(obliq(&tu));
     return ((float)gast);
   }

