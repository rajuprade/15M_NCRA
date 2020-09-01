#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>

#include "source.h"
#include "constant.h"

void gstrgsts(double *, double*, double *, double*, double*, double *, double *); 
void lct(double *, double *, double *, double *, double *) ;

	void rset(SOURCE *sss, final *val)
/*
C----------------------------------------------------------------------
C
C This subroutine finds the rising time and setting time of a source
C
C given the ra,dec of the source,lat and long of the place and the date
C
C
C  input:
C	ra in radians   right ascension of the source
C	dec in radians	declination of the source
C       epd             modified julian day number
C
C  output:
C	lctr in radians 	rise time of the source
C       lcts in radians 	set time of the source
C
C	ldayr gives information about the day corresponding to risetime
C               ldayr=0 rise time for the same date as the input date
C		ldayr=-1 corresponds to rise time for the earlier date
C		ldayr=1 corresponds to rise time for the next day
C
C	ldays gives information about the day corresponding to settime
C                 ldays=0 set time for the same date as the input date
C	          ldays=-1 corresponds to set time for the earlier date
C	          ldays=1 corresponds to set time for the next day
C
C  parameters:
C       lat in deg		latitude of the place
C	long in deg		longitude of the place
C       (long east is +ve and long west is -ve)
C       el in deg		elevation of the source
C	timezone in hours	timezone of the place
C
C  called:
C	  gstrgsts:finds the greenwich sidereal rise and set time
C	           of the source
C
C
C	  slagmst:This double precision function finds the greenwich
C		  sidereal time(in radians)at 0h UT,when the modified
C		  julian day of the date is given
C	(slagmst calls another double precision function sladranrm)
C
C	  lct:finds the local civil time for the given gst,timezone,
C		  gst at 0h UT
C---------------------------------------------------------------------
*/
  {
	double *longd ,*el, *gstr, *gsts;
	double  *utogst,*timezone;
        double *lat;
// Lower elevation limit changed to 18 deg on JAN 21st,09 JPK
 	double elev=ELEVLIMIT;
	double tzone=TIMEZONE;
        double lati=LAT15M;
        double longi=LONG15M;

        lat = (double *) malloc(sizeof(double));
        longd = (double *) malloc(sizeof(double));
        el = (double *) malloc(sizeof(double)); gstr = (double *) malloc(sizeof(double)); gsts = (double *) malloc(sizeof(double));
        timezone = (double *) malloc(sizeof(double));
        utogst = (double *) malloc(sizeof(double));
        
// All the variables are expressed in terms of radians
        *lat =(double ) lati/(double)r2d;
        *longd=(double ) longi/(double)r2d;
        *el=(double ) elev/(double)r2d;
        *timezone=(double ) tzone*15.0/(double)r2d;

	gstrgsts(lat,longd,el,&sss->rad,&sss->decd,gstr,gsts);

        
        (void) slagmst_(&sss->epd,utogst);


	 lct(gstr,utogst,timezone, &val->ldayr, &val->lctr);
	 lct(gsts,utogst,timezone, &val->ldays, &val->lcts);
	
	return;
 }


void gstrgsts(double *lat, double *longd, double *el, double *ra, double *dec, double *gstr, double *gsts) 
    {
/*
C*************************************************************************
C
C	gstrgsts:finds the greenwich sidereal rise and set time
C	           for the source.
C	
C	input:
C		lat in radians    latitude of the place
C		long in radians   longitude of the place
C		el in radians     elevation of the source
C		ra in radians     right ascension of the source
C		dec in radians    declination of the source
C
C	returned:
C		gstr in radians   rise time in gst
C		gsts in radians   set time in gst
C
C*************************************************************************
*/

	double  coslat,sinlat,sinel,sindec,cosdec,cosha;
	double  ha,lstr,lsts;

	coslat=cos(*lat); sinlat=sin(*lat);
	sinel=sin(*el); sindec=sin(*dec); cosdec=cos(*dec);

	cosha=(sinel-sinlat*sindec)/(coslat*cosdec);

	if(cosha <= 1.0 &&  cosha >= -1.0) {
		ha=acos(cosha);
        } else  {
	    fprintf(stderr, " this source never rises at this site ..\n");
            fprintf(stderr, "ending task \n");
		return ;
        }

	lstr= (double)twopi + (*ra) - ha;
	if(lstr >= (double)twopi) {
	    lstr=lstr- (double)twopi;
	} 

	lsts= (*ra) + ha;
	if(lsts >= (double) twopi) { 
	    lsts=lsts- (double )twopi;
	}


        *gstr=lstr+ (*longd);
	if(*gstr > (double) twopi) {
	   *gstr=*gstr- (double )twopi;
        } else if(*gstr <= 0.0)  {
	   *gstr = (*gstr) + (double ) twopi;
	}

	*gsts=lsts+ (*longd);
	if(*gsts >= (double)twopi) {
	   *gsts = (*gsts) - (double )twopi;
        }else if(*gsts <= (double)twopi) {
	   *gsts = (*gsts) + (double )twopi;
	}

       /* fprintf(stderr, " GSTR %g GSTS %g \n", *gstr  , *gsts ); OK */
	return;
  }


	void lct(double *gst, double *utogst, double *timezone, double *lday, double *ct) 
/*
C************************************************************************
C
C	  lct:finds the local civil time for the given gst,date,timezone.
C
C	input:
C		gst in radians       greenwich sidereal time
C		utogst in radians    greenwich sidereal time at 0h UT
C                                    of the date on which civil time is
C				     is required
C		timezone in radians  timezone of the place
C		
C	output:
C               ct in radians        local civil time
C
C	lday gives information about the day corresponding to civil time
C	        lday=0 civil time  for the same date as the input date
C		(here the input date means the date corresponding to the
C		utogst)
C		lday=-1 corresponds to civil time for the earlier date
C		lday=1 corresponds to civil time for the next day
C
C************************************************************************
*/
{
	double  STOUT=0.9972695663;
	double  ut,delgst;

	delgst= *gst - *utogst;

	ut= STOUT * delgst;
        *ct= ( ut  - *timezone);

        *lday=0;
	if ( *ct > (double) twopi)  {
	     *ct= *ct - (double )twopi;
	    *lday=1;
        } else if(*ct < 0.0) {
	    *ct=*ct+ (double)twopi;
	    *lday=-1;
        }
	return;
}


void msim(float x, char s ) {
      int i = (int) rint(x);

     if( i >=1 ) s='+';
     if( i <= -1) s='-';
     return;
}
