/*+
HEADER FILE:  IAUCONST.H
 
%%  IAU (1976) System of Astronomical Constants
 
    SOURCE:  USNO Circular # 163 (1981dec10)
---
 
    CAUTION TO USERS OF ALCYON C:  The dynamic range of the Alcyon C compiler
    (for the Motorola 68000) is e-19 to e19.  Certain of these constants
    exceed that range and will not compile properly.  If it is necessary to
    use them, their definitions should be scaled and the algorithms in which
    they are used should be modified to take the scaling into account.
 
    ALL ITEMS ARE DEFINED IN THE SI (MKS) SYSTEM OF UNITS  
 
LANGUAGE:  C
ENVIRONMENT:  Any standard C (but see caveat for Alcyon C, above).
::  header  include  constants  IAU
 
 
 
++$  AUDIT TRAIL
   1.0   85dec17   D. King   Initial submission.
--$
-*/
#define iau_version  1.0
 
#define GAUSS_GRAV     0.01720209895   /*  Gaussian gravitational constant  */
#define C_LIGHT        299792458.      /*  Speed of light; m/s              */
#define TAU_A          499.004782      /*  Light time for one a.u.; sec     */
#define E_EQ_RADIUS    6378137.        /*  Earth's Equatorial Radius, meters
                                                 (IUGG value)               */
#define E_FORM_FCTR    0.00108263      /*  Earth's dynamical form factor    */
#define GRAV_GEO       3.986005e14     /*  Geocentric gravitational constant;
                                                 (m^3)(s^-2)                */
#define GRAV_CONST     6.672e-11       /*  Constant of gravitation;
                                                 (m^3)(kg^-1)(s^-2)         */
#define LMASS_RATIO    0.01230002      /*  Ratio of mass of Moon to mass
                                                 of Earth                   */
#define PRECESS        5029.0966       /*  General precession in longitude;
                                                 arcsec per Julian century
                                                 at standard epoch J2000    */
#define OBLIQUITY      84381.448       /*  Obliquity of the ecliptic at
                                                 epoch J2000; arcsec        */
#define NUTATE         9.2025          /*  Constant of nutation at
                                                 epoch J2000; arcsec        */
#define ASTR_UNIT      1.49597870e11   /*  Astronomical unit; meters        */
#define SOL_PRLX       8.794148        /*  Solar parallax; arcsec           */
#define ABERRATE       20.49552        /*  Constant of aberration at
                                                 epoch J2000; arcsec        */
#define E_FLAT-FCTR    0.00335281      /*  Earth's flattening factor        */
#define GRAV_HELIO     1.32712438e20   /*  Heliocentric gravitational constant
                                                 (m^3)(s^-2)                */
#define S_E_RATIO      332946.0        /*  Ratio of mass of Sun to
                                                 mass of Earth              */
#define S_EMOON_RATIO  328900.5        /*  Ratio of mass of sun to
                                                 mass of Earth plus Moon    */
#define SOLAR_MASS     1.9891e30       /*  Mass of Sun; kg                  */
 
 
#define JD_J2000       2451545.0       /*  Julian Day Number of 2000jan1.5  */
#define BES_YEAR       365.242198781   /*  Length of Besselian Year in days
                                             at B1900.0 (JD 2415020.31352)  */
#define SOLAR_SID   0.997269566329084  /*  Ratio of Solar time interval to
                                             Sidereal time interval at J2000 */
#define SID_SOLAR   1.002737909350795  /*  Ratio of Sidereal time interval
                                             to Solar time interval at J2000 */
         /*  NOTE:  If the time interval between two events is t_sid sidereal
         ** time units, then that same interval is t_sol = (t_sid * SOLAR_SID)
         **  solar time units.  Similarly,  t_sid = (t_sol * SID_SOLAR).    */
