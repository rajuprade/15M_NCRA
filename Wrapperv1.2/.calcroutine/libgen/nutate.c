#include <math.h>
#include "libvlba.h"

void nutate (t_nowp, delt_psi, delt_eps)
    double *t_nowp;            /* time with respect to J2000, Julian Centuries*/
    double *delt_psi;        /* (output) nutation in longitude at t_now     */
    double *delt_eps;        /* (output) nutation in obliquity at t_now     */
/*
%%  Calculate the nutation in longitude and obliquity for an arbitrary time.
 
    Delta-psi and delta-epsilon are calculated using the full series expansion.
    (See the documentation for the current version of NUTPARMS.H for the
    source of the numerical values which are used.)
---
    Definition of t_now:
       ([Julian Day Number of target epoch] - 2451545.0) / 36525.0
       where the JD number includes the fractional day since 12h TDB.
 
 
LANGUAGE:  C
ENVIRONMENT:  Any Standard C.
EXTERNAL REFERENCES:
    EXTERNAL FUNCTIONS IN VLBCLIB:
        frac  rduce2p
 
::  position  pointing  nutation  longitude  obliquity
 
TEST STATUS:
    Version 1.0 tested 16 Jan 86, by D. King:
        Compiled on VAX (50+ bits of precision for type double).
        Ran for calendar year 1985, for 0 hours of each day.  The output
          values of delta-psi and delta-epsilon were converted to arc-seconds
          and rounded to three decimal places.
        Manually compared output with "The Astronomical Almanac, 1985."
        NO ERRORS were detected.
 
        Compiled on VME/10 using Alcyon C (24 bits of precision for doubles).
        Ran for calendar year 1985, as above.
        Used file compare utility to look for differences from VAX output.
        Found 25 ERRORS of plus or minus 1 in the least significant digit
          (0".001);  16 errors were in delta-psi and 9 in delta-epsilon.
 
        Ran both VAX and VME/10 for calendar years 1995, 2000, 2005, and
          2025, and file-compared to look for discrepancies.  Errors
          never exceeded 0".001, and in only two cases (both in year 2025)
          were delta-psi and delta-epsilon both in error.
        Assuming that the VAX output was completely accurate, the errors
          in the 24-bit Alcyon output are given by the following table.
 
                   YEAR   Total   Errors    Errors
                          Errors  in Psi    in Eps
                   - - - - - - - - - - - - - - - -
                   1985     25      16         9
                   1995      8       6         2
                   2000      1       1         0
                   2005     11       9         2
                   2025     50      35        15
 
        The errors are assumed to arise mostly in the calculation of
          the three fundamental arguments (l, F, and D) which have about
          1300 revolutions per century.  It is thus not surprising
          that the number of errors increases with the distance from
          year 2000.  Hopefully, we will have a compiler with more than
          24 bits of precision by the time we reach 2025.
 
++$  AUDIT TRAIL
    1.0  86jan16   D. King   Initial submission
    1.0  86jan21   D. King   Minor documentation correction -- code unchanged.
--$
-*/
#define version 1.0
 
 
#include "MATHCNST.H"
#define RAD_REV  TWOPI
 
{
#include "NUTPARMS.H"
    double
        fund_arg[5],                   /* l, l_prime, F, D, Omega           */
 
        t_power[4],
 
        psi,                 /*  holds partial sum of delta_psi      */
        eps,                 /*  holds partial sum of delta_epsilon  */
        argument,            /*  argument of nutation series term    */
	t_now,
	temp;
 
    int
        i, j;                /*  loop indices                        */
 
 
    /*
    ** Calculate the fundamental arguments for time t_now, reduced to
    **   the interval 0 <= arg < TWOPI.
    */
 
    t_now=*t_nowp;
    t_power[0] = 1.0;
    t_power[1] = t_now;
    t_power[2] = t_now * t_now;
    t_power[3] = t_power[2] * t_now;
 
    for (i = 0; i < 5; i++)
    {
        double x = 0.0;
 
        for (j = 0; j < 4; j++)
            x += farg_coef[i][j] * t_power[j];
        temp=farg_revs[i] * t_now;
        x = x * RAD_ASEC  +  frac(&temp) * RAD_REV;
        fund_arg[i] = rduce2p(&x);
/*
/*DEBUG   {char string[40]; sangle(fund_arg[i], "S", string);
/*DEBUG    printf("nutate:  fund_arg[%d] = %s\n", i, string);}
*/
    }
 
    /*
    **  Calculate the nutation series.
    **    Since all time_dependent terms are zero after term 39 (subscript
    **    38, in C-language conventions), the summation is broken into
    **    two parts, to speed the computations.
    */
 
    psi = 0.0;
    eps = 0.0;
    for (i = 0; i < LAST_T_TERM; i++)
    {
        /*
        **  Calculate the actual argument for the current term.
        */
        for (j = 0, argument = 0.0; j < 5; j++)
            argument += farg_mult[j][i] * fund_arg[j];
        /*
        **  Sum the series.
        */
        psi += (lngtd[i] + d_lngtd[i] * t_now) * sin(argument);
        eps += (obliq[i] + d_obliq[i] * t_now) * cos(argument);
    }
    for ( ; i < NTERMS; i++)
    {
        for (j = 0, argument = 0.0; j < 5; j++)
            argument += farg_mult[j][i] * fund_arg[j];
        psi += lngtd[i] * sin(argument);
        eps += obliq[i] * cos(argument);
    }
 
    /*
    **  Psi and eps are in units of 0.0001 arc-second.
    **  Convert to radians and put them into the caller's variables.
    */
/*
/*DEBUG   printf("nutate:  psi = %e, eps = %e\n", psi, eps);
*/
 
    *delt_psi = psi * 0.0001 * RAD_ASEC;
    *delt_eps = eps * 0.0001 * RAD_ASEC;
    return;
}
 void nutrotn (epsilonp, dpsip, depsp, mean_posn, true_posn)
    double *epsilonp,          /*  Mean obliquity        (radians)     */
           *dpsip,             /*  Nutation in longitude (radians)     */
           *depsp,             /*  Nutation in obliquity (radians)     */
           mean_posn[3],     /*  (input) direction cosines of
                             **    mean position of date             */
           true_posn[3];     /*  (output) direction cosines of
                             **    true (nutated) position           */
 
/*  Note that "true position" does not include the "E-terms of aberration,"
**    in accordance with J2000 conventions.                          */
 
/*
%%  rotate the coordinate system to account for nutation
 
    Both approximate and exact algorithms for the nutation matrix are
    provided.  The approximate method works better with the 24-bit precision
    of Alcyon C, and is acceptable on the VAX (see Test Status, below).
 
    This version (1.0) uses the approximate method.  To use the exact
    method, parameter APPROXIMATE must be undefined.
---
    SOURCES:
        Taff, L. G.  1981.  "Computational Spherical Astronomy"
            John Wiley & Sons, page 81.
        Emerson, B. 1973.  Royal Obs Bul 178, pg 299-300.
 
 
::    pointing   nutation    position
 
LANGUAGE:  C
ENVIRONMENT:  Any standard C.
EXTERNAL REFERENCES:
    In VLBCLIB:
        ROTATE3
TEST STATUS:
  86feb04, D. King:
        The matrices produced by these algorithms were post-multiplied by
    the precession matrices produced by the algorithm used in "PRCESJ2."
    The results were compared with those in "The Astronomical Almanac" for
    1985 January 0 thru February 15, plus a few more randomly chosen dates
    in 1985.
        For the VAX (50+ bits of precision) four errors of plus or minus
    1e-8 were seen in off-diagonal elements, when the exact algorithm for
    the nutation matrix was used.  These errors are presumed to be due to
    differences in computational precision and round-off from the Almanac.
        When the approximate algorithm was used on the VAX, most
    dates had one or two errors of 1e-8, including a few in the
    diagonal elements.  The approximate method thus seems adequate if a
    nutation matrix precision of 1e-8 is adequate.
        For the VME/10 using Alcyon C (24 bits of precision),  errors of
    up to 15e-8 were seen in the diagonal elements, when the approximate
    algorithm for the nutation matrix was used.  Off-diagonal elements
    showed about one error per matrix, usually of only 1e-8, and never more
    than 5e-8.  Since 24 bits can express a number of order 1.0 to only
    about 6e-8, these results seem reasonable.
        When the exact algoritm was used with Alcyon C, results were worse.
    Errors in the diagonal elements were larger, up to 23e-8.  In addition,
    elements 2,3 and 3,2 were always in error -- usually more than 5e-8,
    and sometimes in excess of 20e-8.  The reason for the poorer performance
    of the exact algorithm is unknown.  It was not possible to get similar
    results on the VAX by declaring the appropriate variables to be 'float',
    (although accuracy of the final digit of all elements was degraded).
    (Perhaps the Alcyon sine and cosine routines are not good enough.)
 
++$  AUDIT TRAIL
    1.0   86feb04     D. King    Initial submission.
--$
-*/
#define version 1.0
 
 
#define APPROXIMATE  1       /*  Use the APPROXIMATE MATRIX          */
 
{
    double
        nutmatrix[3][3],     /*  rotation matrix for nutation        */
        temp,
	epsilon=*epsilonp,
	dpsi=*dpsip,
	deps=*depsp;
 
    /*
    **    Construct the rotation matrix
    **      Note that subscripts run 0-2, rather than 1-3, because of
    **      the usual C language conventions.
    */
 
#ifdef APPROXIMATE           /*      approximate matrix              */
        /*  ----APPROXIMATE MATRIX----
        **  SOURCE:  Taff, L. G.  1981.  "Computational Spherical Astronomy"
        **           John Wiley & Sons, page 81.
        */
    double
        cos_eps = cos(epsilon),
        sin_eps = sin(epsilon),
        deps_sq = deps * deps,
        dmu,
        dNU;                 /* upper case NU to distinguish from mu */
 
    dmu = dpsi * cos_eps;
    dNU = dpsi * sin_eps;
 
    nutmatrix [0][0] = 1. - .5 * dpsi * dpsi;
    nutmatrix [1][1] = 1. - .5 * ( deps_sq - dmu * dmu );
    nutmatrix [2][2] = 1. - .5 * ( deps_sq + dNU * dNU );
 
    nutmatrix [0][1] = -dmu;
    nutmatrix [1][0] =  dmu - deps * dNU;
 
    nutmatrix [0][2] = -dNU;
    nutmatrix [2][0] =  dNU - deps * dmu;
 
    temp = -.5 * dmu * dNU;
    nutmatrix [1][2] = temp - deps;
    nutmatrix [2][1] = temp + deps;
 
#else                        /*     exact matrix                     */
        /*  ----EXACT MATRIX----
        **  SOURCE:  Emerson, B. 1973.  Royal Obs Bul 178, pg 299-300.
        */
    double
        eps0,                /*   MEAN obliquity                     */
        cos_eps,
        sin_eps,
        cos_eps0,
        sin_eps0,
        cos_dpsi,
        sin_dpsi;
 
    sin_eps0 = sin(eps0);
    cos_eps0 = cos(eps0);
 
    epsilon = eps0 + deps;   /*  'epsilon' is now TRUE obliquity     */
    cos_eps = cos(epsilon);
    sin_eps = sin(epsilon);
 
    sin_dpsi = sin(dpsi);
    cos_dpsi = cos(dpsi); 
 
 
    nutmatrix [0][0] = cos_dpsi;
 
    nutmatrix [0][1] = -sin_dpsi * cos_eps0;
    nutmatrix [1][0] =  sin_dpsi * cos_eps;
 
    nutmatrix [0][2] = -sin_dpsi * sin_eps0;
    nutmatrix [2][0] =  sin_dpsi * sin_eps;
 
    temp = cos_dpsi * cos_eps0;
    nutmatrix [1][1] = temp * cos_eps + sin_eps0 * sin_eps;
    nutmatrix [2][1] = temp * sin_eps - sin_eps0 * cos_eps;
 
    temp = cos_dpsi * sin_eps0;
    nutmatrix [1][2] = temp * cos_eps - cos_eps0 * sin_eps;
    nutmatrix [2][2] = temp * sin_eps + cos_eps0 * cos_eps;
 
#endif
 
 
    /*
    **  Rotate the mean co-ordinates to get the true position.
    */
 
    rotate3 (true_posn, nutmatrix, mean_posn);
}
  double obliq (t_nowp)
    double *t_nowp;       /* time with respect to J2000, in Julian centuries  */
 
/*  returns:  mean obliquity at t_now, in radians.         */
 
/*
%%  Calculate the MEAN obliquity at an arbitrary time, in radians.
 
    SOURCE:  United States Naval Observatory; Circular number 163
                   (1981dec10), page A3
 
    To obtain the TRUE obliquity:  To the value returned by this function,
    add delta-epsilon, which is calculated by "nutate".
---
    Definition of t_now:
       ([Julian Day Number of target epoch] - 2451545.0) / 36525.0
       where the JD number includes the fractional day since 12h TDB.
 
LANGUAGE:  C
ENVIRONMENT:  Any standard C
::  obliquity  position  pointing
TEST STATUS:
  (Version 1.0, tested 21 Jan 86, by D. King)
    VAX (50+ bits of precision):
        Output of this routine was combined with the Nutation in Obliquity
        from routine NUTATE, and the result compared to the "Astronomical
        Almanac" for each day of 1985.
           ONE DISCREPANCY, of +0".001, was found (for 85aug18).  The VAX
        result for this date was then printed to 9 decimals and found to
        be xxx".187500056.  The discrepancy is thus thought to be attrib-
        utable to differences in machine precision and round-off algorithms
        between the VAX and the machine used by the compilers of the Almanac.
    Alcyon C for Motorola MC68000 (VME/10) (24 bits of precision):
           The true obliquity was calculated, as above, for each day of 1985.
        The following results were obtained:
                    34 days:  exact match with almanac;
                   197 days:  VME/10 results were greater than almanac;
                   135 days:    "       "     "   less      "     "   ;
                   extreme deviations were plus and minus 0".010;
                   mean deviation was +0".000795;
                   RMS deviation was 0".004032.
        Since 24 bits can express the obliquity (about 84300 arc-seconds) to
        a precision of only about 0".005, the above results are considered
        to be quite acceptable.
  (End of test status for version 1.0, 23 jan 86.)
 
 
++$  AUDIT TRAIL
    1.0   86jan23   D. King   Initial Submission
    1.0   86apr29   D. King   Corrected documentation -- code unchanged.
--$
-*/
#define version 1.0
 
#include "MATHCNST.H"
 
{
    double obl;
    double t_now=*t_nowp;
 
    obl = (( 0.001813 * t_now - 0.00059 ) * t_now - 46.8150 ) * t_now +
          84381.448;
    return (obl * RAD_ASEC);
}
