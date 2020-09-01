/*+
HEADER FILE:  ASTRCNST.H
 
%%  Astronomical constants.  (See also IAUCONST.H)
 
    Definitions:
         Floating:
             JUL_YEAR
         Integer:
             JUL_CENT        SEC_DAY
----
 
    The following constants are expressed as INTEGERS, so that they may
    be used in integer calculations.  If extensively used in floating-point
    computations, unnecessary run-time type conversions may be avoided by
    declaring a variable of type double which is set to the desired constant.
    For example:
                   double jul_cent = JUL_CENT;.
 
         JUL_CENT
         SEC_DAY
 
 
LANGUAGE:  C
ENVIRONMENT:  Any standard C.
::  header  include   constant   astronom
 
NORMAL RESIDENCE:  0.INCLUDE.ASTRCNST.H
 
++$  AUDIT TRAIL
  1.0   85dec19   D. King   Initial submission
  1.0   86feb07   D. King   Documentation correction -- code unchanged
--$
*/
#define astrc_version  1.0
 
 
  /*  CONSTANTS CONTAINING  A DECIMAL POINT  */
 
#define JUL_YEAR   365.25              /* Days per Julian year              */
 
 
  /*  INTEGER CONSTANTS  (See documentation, above.)   */
 
#define SEC_DAY    86400               /* Seconds per day                   */
#define JUL_CENT   36525               /* Days per Julian century           */
