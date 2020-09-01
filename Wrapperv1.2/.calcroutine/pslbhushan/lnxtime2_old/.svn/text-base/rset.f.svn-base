

	subroutine rset(sss,val)
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

	include 'source.inc'
	include 'constant.inc'

	record/source/sss
	record/final/val

	double precision r2d
	double precision lat,long,el,gstr,gsts
	double precision lati,longi,elev
	double precision utogst,slagmst,timezone,tzone


	parameter(longi=-74.05)
C Lower elevation limit changed to 18 deg on JAN 21st,09 JPK
C	parameter(elev=17.5)
	parameter(elev=18.0)
	parameter(tzone=-5.5)
	parameter(lati=19.1)



C All the variables are expressed in terms of radians
	lat=lati/r2d
	long=longi/r2d
	el=elev/r2d
	timezone=tzone*15.0/r2d

	call gstrgsts(lat,long,el,sss.rad,sss.decd,gstr,gsts)


	utogst=slagmst(sss.epd,utogst)


	call lct(gstr,utogst,timezone,val.ldayr,val.lctr)
	call lct(gsts,utogst,timezone,val.ldays,val.lcts)
	

	return
	end




	subroutine gstrgsts(lat,long,el,ra,dec,gstr,gsts)

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

	include "constant.inc"
	double precision lat,long,el,ra,dec,gstr,gsts
	double precision coslat,sinlat,sinel,sindec,cosdec,cosha
	double precision ha,lstr,lsts

	coslat=cos(lat)
	sinlat=sin(lat)
	sinel=sin(el)
	sindec=sin(dec)
	cosdec=cos(dec)
	cosha=(sinel-sinlat*sindec)/(coslat*cosdec)
	if(cosha.le.1.d0.and.cosha.ge.-1.d0) then
		ha=acos(cosha)
	else
		write(*,*) ' this source never rises at this site'
		write(*,*) ' ending task'
		return 
	endif

	lstr=twopi+ra-ha
	if(lstr.ge.twopi)then
	    lstr=lstr-twopi
	endif

	lsts=ra+ha
	if(lsts.ge.twopi)then
	    lsts=lsts-twopi
	endif

	gstr=lstr+long
	if(gstr.ge.twopi)then
	   gstr=gstr-twopi
	elseif(gstr.le.0.0d0)then
	   gstr=gstr+twopi
	endif

	gsts=lsts+long
	if(gsts.ge.twopi)then
	   gsts=gsts-twopi
	elseif(gsts.le.twopi)then
	   gsts=gsts+twopi
	endif
	write(*,*), gstr, gsts ;
	return
	end


	subroutine lct(gst,utogst,timezone,lday,ct)

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


	include "constant.inc"
	double precision utogst,timezone,STOUT
	double precision ut,ct,delgst,gst
	double precision lday

	PARAMETER(STOUT=0.9972695663)

	delgst=gst-utogst
	ut=STOUT*delgst
 	ct=(ut-timezone)
	lday=0
	if(ct .gt. twopi) then
	    ct=ct-twopi
	    lday=1
	elseif(ct .lt. 0)then
	    ct=ct+twopi
	    lday=-1
	endif
	return
	end

      SUBROUTINE MSIM(X,CHAR)
      REAL*8 X
      CHARACTER*(*) CHAR
      INTEGER I
      I=NINT(X)
      CHAR=' '
      IF(I.GE.1)CHAR='+'
      IF(I.LE.-1)CHAR='-'
      RETURN
      END
