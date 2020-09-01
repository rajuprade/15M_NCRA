#include "math.h"

  double frac (arg)
    double *arg;
/*
%%  Returns fractional part of argument, with same sign as argument.
 
    This code is believed to be machine and compiler independent.
---
LANGUAGE:  C.
ENVIRONMENT:  Any standard C.
EXTERNAL REFERENCES:
    From standard C library:
        Uses 'floor' function, which returns the double representation of
        the largest integer not larger than its argument.
TESTED:  86jan09  D. King.  Various inputs from -1e6 to +1e6.
::  fraction
++$  AUDIT TRAIL
    1.0   86jan09   D. King   Initial submission
    1.0   86mar06   D. King   No change to code -- correct documentation typo
--$
-*/
#define version 1.0
 
{
    double x = fabs(*arg);
 
    x -= floor(x);
 
    return (*arg < 0  ?  -x  :  x);
}
