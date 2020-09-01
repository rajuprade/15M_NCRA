#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>

#include "source.h"
#include "constant.h"


void azel(SOURCE *sss, final *val)

/*
C----------------------------------------------------------------------
C
C Subroutine to find the azimuth and elevations of the source
C
C input:
C     rad in radians             right ascension of the source at time te0
C     raoff in radians            off-set in right ascension
C     dra in radians/radians      rate of change of ra
C     decd in radians             declination of the source at time t0r
C     decoff in radians           off-set in declination
C     ddec in radians/radians     rate of change of declination
C     te0 in radians              initial time at which ra,dec are specified
C     azoff in radians           off-set in azimuth
C     daz in radians/radians   rate of change of azimuth
C     eloff in radians           off-set in elevation
C     del in radians/radians   rate of change of elevation
C     time in radians            time at which azimuth,elev are calculated
C     th0 in radians             time at which azimuth,elev are required
C
C output:
C	az in radians        azimuth of the source
C	el in radians        elevation of the source            
C
C----------------------------------------------------------------------
*/
{
	double  *ra, *dec, *azim, *elev, *lat, *longd, *t0az;
	double  timezone,ti;

	ra    = (double *) malloc(sizeof(double)); dec   = (double *) malloc(sizeof(double));
        azim  = (double *) malloc(sizeof(double)); elev  = (double *) malloc(sizeof(double));
        lat   = (double *) malloc(sizeof(double)); longd = (double *) malloc(sizeof(double));
        t0az  = (double *) malloc(sizeof(double));
         
        *lat=LAT15M; *longd=LONG15M; timezone=TIMEZONE;


	*ra = sss->rad+sss->raoff+(sss->time-sss->te0)*sss->dra;
	*dec= sss->decd+sss->decoff+(sss->time-sss->te0)*sss->ddec;
	

	ti=sss->time+(timezone/(double)r2h);

        *t0az=sss->epd + (ti * ((double)r2h/24) );

/*  ra,dec,time are converted into degrees */
        *ra=  (*ra) * (double)r2d;
        *dec= (*dec)* (double)r2d;

        crdrd2ae_(ra,dec,lat,longd,t0az,azim,elev);

/*  az,el are converted into radians */
        *azim = (*azim) /(double) r2d;
        *elev = (*elev) /(double) r2d;

/* AZ , EL Corrections added JPK Aug 16, 2012 */
	val->az = (*azim)+ sss->azcorr + sss->azoff+(sss->daz*(sss->time-sss->th0));
	val->el = (*elev)+ sss->elcorr + sss->eloff+(sss->del*(sss->time-sss->th0));

        return;
}
