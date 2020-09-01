#include <math.h> 
#include "libvlba.h"
  double position (ra_j2000p, dec_j2000p, t_nowp, pos_now)
    double *ra_j2000p,         /*  J2000 right ascension                      */
           *dec_j2000p,        /*  J2000 declination                          */
           *t_nowp,            /*  Current time with respect to j2000,
                             **    in Julian centuries.                     */
           pos_now[3];       /*  (output) Direction cosines of
                             **    current corrected position.              */
    /*  RETURNS:  equation of equinoxes (delta _psi * cos(mean_obliquity)),
    **              in seconds of time                                      */
/*
%%  Calculates current geocentric apparent position from J2000 position.

    This routine does NOT include calculations for proper motion or parallax.
    Version 1.0 does not include topocentric corrections. 
---

LANGUAGE:  C
ENVIRONMENT:  Any standard C
::  pointing  position  apparent  J2000  geocentric  equinox  equation
TEST STATUS:
  Version 1.0, 3 Apr 86, D. King.
    The output from this module appears reasonable.  The validity of this
    module depends upon the external routines which it calls.
 
++$  AUDIT TRAIL
    1.0  86apr03  D. King   Initial submission.
    1.1  87mar12  D. King   Add "equinox" and "equation" to keyword list
--$
-*/
#define VERSION 1.1
 
 
#include "MATHCNST.H"
 
{
    double
        pos_j2000[3],        /*  direction cosines of J2000 position        */
        pos_mean[3],         /*  dir-cosines of mean position of date       */
        pos_aber[3],         /*  d-c of mean pos of date, corrected for
                             **    aberration and relativistic deflection   */
        pos_app[3],          /*  d-c of apparent (geocentric) position      */
        pos_topo[3],         /*  dir-cosines of topocentric position        */
        mean_obliq,          /*  mean obliquity of date                     */
        delta_psi,           /*  nutation in longitude                      */
        delta_eps,           /*  nutation in obliquity                      */
        eqn_eqnx;            /*  equation of equinoxes                      */
    double
	ra_j2000,dec_j2000,t_now,
        temp;
 
    int i;                   /*  loop index                                 */
 
/*+ EXTERNAL FUNCTIONS:

    void
        dir_cos(double *,double *,double *),
        prcesj2(double *,double *,double *),
        aberrat(double *,double *,double *,double *),
        nutate(double *,double *,double *),
        nutrotn(double *,double *,double *,double *,double *);
    double
        obliq(double *);

-*/
 
 
    /* Convert input ra, dec to direction cosines
    */
    ra_j2000=*ra_j2000p;
    dec_j2000=*dec_j2000p;
    t_now=*t_nowp;

    dir_cos (&ra_j2000, &dec_j2000, pos_j2000);
 
    /* Precess from J2000 to t_now
    */
    prcesj2 (&t_now, pos_j2000, pos_mean);
 
    /* Correct for aberration and general relativistic deflection.
    */
    mean_obliq = obliq(&t_now);
    aberrat(&t_now, &mean_obliq, pos_mean, pos_aber);
 
    /* Correct for nutation
    */
    nutate (&t_now, &delta_psi, &delta_eps);
    nutrotn (&mean_obliq, &delta_psi, &delta_eps, pos_aber, pos_app);
 
    /*   Topocentric corrections go here
    **     (Currently, there are no topocentric corrections,
    **     so copy the apparent position into the topocentric position.)
    */
    for (i = 0; i < 3; i++)
    {
        temp = pos_app[i];             /*  'temp' nonsense because of       */
        pos_topo[i] = temp;            /*     bug in Alcyon compiler.       */
    }
 
    /* Load the final position into the caller's variable, then return.
    */
    for (i = 0; i < 3; i++)
        pos_now[i] = pos_topo[i];
    eqn_eqnx = delta_psi * cos(mean_obliq) / (RAD_ASEC * 15.);
    return (eqn_eqnx);
}
