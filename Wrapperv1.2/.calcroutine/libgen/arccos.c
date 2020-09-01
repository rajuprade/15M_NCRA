/********************************************************************/
#include <math.h>

 double arccos(xx)
 
 double *xx;                      /* The sine of the angle */
/********************************************************************/
 
/*+
%% Subroutine to determine the angle whose cosine is the argument
---
   Taken from Hastings,C.  Approximations for Digital Computers.
   NOTE: The range is from 0 to +180 (pi) degrees.
         (The result is in radians, of course!)
         It will return 0.0 for values greater than 1.0.
 
LANGUAGE: C
ENVIRONMENT: Versatek
:: cosine
++$ AUDIT TRAIL
1.0  86nov30  R.T. Duquet  Initial Submission
     93nov24  A. Pramesh Rao	changed calling sequence to pointer to double
--$
-*/
 
{
 static double a[8] = {1.5707963050, -0.2145988016,
                       0.0889789874, -0.0501743046,
                       0.0308918810, -0.0170881256,
                       0.0066700901, -0.0012624911};
 static double pi = 3.14159265;
 
 int i;
 double acos, prod, y,x;
 
 
 x=*xx;
 y = x;
 if (x < 0.0) y = -x;
 if (y > 1.0) return(0.0);
 prod = 1.0;
 acos = 0.0;
 for (i=0;i<8;i++)
    {
     acos += a[i] * prod;
     prod *= y;
    }
 acos *= sqrt(1.0-y);
 if (y != x) return(pi - acos);
 return(acos);
}  /* END OF PROGRAM */
 
/********************************************************************/
 double arcsin(xx)
 
 double *xx;                      /* The sine of the angle */
/********************************************************************/
 
/*+
%% Subroutine to determine the angle whose sine is the argument
---
   Taken from Hastings,C  Approximations for Digital Computers
 
   NOTE: The range is from -90 (-pi/2) to +90 (pi/2) degrees.
         (The result is in radians,/of course!)
         This will return pi/2 for values greater than 1.0.

 
LANGUAGE: C
ENVIRONMENT: Versatek
:: sine
++$ AUDIT TRAIL
1.0  86nov30  R.T. Duquet  Initial Submission
--$
-*/
 
{
 static double a[8] = {1.5707963050, -0.2145988016,
                       0.0889789874, -0.0501743046,
                       0.0308918810, -0.0170881256,
                       0.0066700901, -0.0012624911};
 static double piover2 = 1.570796327;
 
 int i;
 double asine, prod, y;
 double x=*xx;
 
 
 y = x;
 if (x < 0.0) y = -x;
 if (y > 1.0) return(piover2);
 prod = 1.0;
 asine = 0.0;
 for (i=0;i<8;i++)
    {
     asine += a[i] * prod;
     prod *= y;
    }
 asine *= sqrt(1.0-y);
 if (y == x) return(piover2-asine);
 else return(asine-piover2);
}  /* END OF PROGRAM */
 
