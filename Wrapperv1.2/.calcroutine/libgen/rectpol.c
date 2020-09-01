#include "math.h"
#include "MATHCNST.H"
  void rectpol (dir_vector, ra, dec)
    double dir_vector[3];        /*  input, xyz co-ordinates             */
    double *ra, *dec;            /*  output, ra and dec in radians       */
/*
%%  Convert from rectangular to polar co-ordinates.
 
    If the z-axis coincides with the polar axis, and the x-axis passes thru
    the vernal equinox, then this routine converts to the equatorial system
    of right ascension and declination (as is implied by the nomenclature
    of the formal parameters).
---
PROGRAMMING NOTES:
    Note added for version 1.1:
    	'atan2' is compiler-dependent!  In Alcyon C for VERSAdos, the output
    	of atan2 can range from -pi/2 to pi/2, while in VAX C it ranges from
    	-pi to pi.  Thus, we use 'atan' to compute the ra.  It is valid to
    	use 'atan2' to compute the dec because the second argument is
	constrained to be positive, thus eliminating the second and third
    	quadrants.
 
LANGUAGE:  C
ENVIRONMENT:  Alcyon C  (Any standard C with appropriate modification of
                             the parameter TOO_SMALL.)
TESTED:  6 Jan 86, D. King.  A program which uses this gives reasonable output.
    	 13 Oct 86, D. King. Used a special test program which converted ra
    		and dec to direction cosines, put the result into this
    		function, then printed the final resulting ra and dec.
 
++$  AUDIT TRAIL
    1.0   86jan07   D. King   Initial submission.
    1.1   86oct13   D. KIng   'atan2' gave problems, see programming note. 
--$
-*/
#define version 1.1
 
#define TOO_SMALL  1.0e-9    /* should be square root of smallest nonzero
                             **   value that compiler can handle.           */
 
{
 
    double  x = dir_vector[0],
            y = dir_vector[1],
            z = dir_vector[2],
            fabsx ,
            fabsy ;
 
    fabsx=x;if(x<0.)fabsx=-x;
    fabsy=y;if(y<0.)fabsy=-y;
    /*  Take care of the special case of input = a pole                  */
 
    if (fabsx < TOO_SMALL  &&  fabsy < TOO_SMALL)
    {
        *ra = 0.0;
        *dec = (z > 0) ? PIOVR2 : -PIOVR2;
        return;
    }
 
    /*  Calculate the declination                                        */
 
    *dec = atan2 (z, sqrt(x*x + y*y));
 
    /*  Take care of special cases of x = 0 or y = 0                     */
 
    if (fabsx < TOO_SMALL)
    {
         *ra = (y > 0) ? PIOVR2 : PIOVR2 + PI;
        return;
    }
    if (fabsy < TOO_SMALL)
{
         *ra = (x > 0) ? 0.0 : PI;
         return;
}
 
    /*  Calculate right ascension, in the range 0 <= ra < TWOPI          */
 
    *ra = atan (y / x) +
                 (x < 0.0 ? PI : (y < 0.0 ? TWOPI : 0.0));
    return;
}
