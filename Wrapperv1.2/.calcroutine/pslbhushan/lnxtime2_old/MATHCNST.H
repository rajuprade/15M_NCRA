/*+
HEADER FILE:  MATHCNST.H
 
%%  Mathematical constants.
      (Physical and astronomical constants should be placed in PHYSCNST.H.)
----
 
LANGUAGE:  C
ENVIRONMENT:  Any standard C.
::  header  include   constant   math
 
NORMAL RESIDENCE:  0.INCLUDE.MATHCNST.H
 
++$  AUDIT TRAIL
  1.0   85oct31   D. King   Initial submission
  1.1   85dec19   D. King   Added some logarithmic constants.
  1.2   86jan03   D. King   Added PI/2.
--$
*/
#define mathc_version  1.2
 
 
#define PI         3.141592653589793
#define TWOPI      6.283185307179586
#define PIOVR2     1.570796326794897
#define DEGREE     0.017453292519943296          /* radians per degree       */
#define ARCMIN     0.000290888208665722          /* radians per arc-minute   */
#define ARCSEC     0.000004848136811095          /* radians per arc-second   */
#define DEG_RAD   57.29577951308232              /* degrees per radian       */
#define HOUR_RAD   3.819718634205488             /* hours (angle) per radian */
#define RAD_DEG    DEGREE
#define RAD_AMIN   ARCMIN
#define RAD_ASEC   ARCSEC
 
#define E          2.718281828459045             /* base of natural logs     */
#define LOG_E_10   2.302585092994045             /* log (base e) of 10      */
#define LOG_E_2    0.6931471805599453            /* log (base e) of 2       */
#define LOG_10_E   0.4342944819032518            /* log (base 10) of e      */
