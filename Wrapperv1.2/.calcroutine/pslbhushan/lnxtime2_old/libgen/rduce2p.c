#include "math.h"
 
  double rduce2p (angle)
    double *angle;
/*
%%  Reduce an angle to the interval [ 0 <= output < TWOPI ].
 
    This code is believed to be machine and compiler independent.
 
    Note: If "angle" is large, all precision  will be lost and zero will
          be returned.  The exact value of "too large" is machine and
          compiler dependent.  For the Alcyon comiler for the MC68000,
          it is about 8 * TWOPI * 1e+6; but angles greater than 1e+5 will
          reduce to only a few bits of precision (one or two decimal digits).
---
LANGUAGE:  C.
ENVIRONMENT:  Any standard C.
TESTED:  86jan09  D. King.  Various inputs from -720 deg to +720 deg, with
                             a few larger values.  Using Alcyon C, this
                             routine shows a tendency to give too large a
                             result, about 0".1 per revolution (too small if
                             input is negative).
EXTERNAL REFERENCES:
    From standard C library:
        Uses 'floor' function, which returns the double representation of
        the largest integer not larger than its argument.
::  angle  two*pi
++$  AUDIT TRAIL
   1.0   86jan09   D. King   Initial submission.
   1.0   86Apr29   D. King   Corrected doc delimiter -- code unchanged.
--$
-*/
#define version 1.0
 
#include "MATHCNST.H"
 
{
 
    return (*angle - floor(*angle/TWOPI) * TWOPI);
}
 
