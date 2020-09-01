
#include "math.h"
/*  Compute direction cosines from right ascension and declination.
*/
 
  void dir_cos (ra, dec, dc_vector)
    double *ra, *dec;          /*  input:  ra and dec in radians              */
    double dc_vector[3];     /*  output:  direction cosine vector
                                   x = dc_vector[0], y = dc_vector[1]       */
/*
%%  Convert equatorial (ra, dec) to rectangular (direction cosines).
 
    Z-axis is the polar axis; x-axis passes thru vernal equinox (ra = 0).
---
 
LANGUAGE:  C
ENVIRONMENT:  Any standard C.
TESTED:  6 Jan 86, D. King.  Output appears reasonable.
 
::  polar  equatorial  rectangular  xyz  coordinates  convert  direction
 
++$  AUDIT TRAIL
    1.0   86jan07   D. King   Initial submission
--$
-*/
#define version 1.0
 
{
 
    double cosdec = cos(*dec);
    register double *v = dc_vector;
 
    *v++ = cos(*ra) * cosdec;
    *v++ = sin(*ra) * cosdec;
    *v   = sin(*dec);
 
    return;
}
