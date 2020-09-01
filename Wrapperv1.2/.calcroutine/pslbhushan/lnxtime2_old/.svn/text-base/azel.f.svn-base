

	subroutine azel(sss,val)

	include 'source.inc'
	include 'constant.inc'

	record/source/sss
	record/final/val

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


	double precision ra,dec,azim,elev
	double precision lat,long,t0az,timezone,ti	

	parameter(lat=19.1)
	parameter(long=-74.05)
	parameter(timezone=-5.5)


	ra=sss.rad+sss.raoff+(sss.time-sss.te0)*sss.dra
	dec=sss.decd+sss.decoff+(sss.time-sss.te0)*sss.ddec
	

	ti=sss.time+(timezone/r2h)

C	WRITE(*,*)" EPOCH ", sss.epd, "  TIME ", ti
 	t0az=sss.epd+(ti*r2h/24)

C  ra,dec,time are converted into degrees
	ra=ra*r2d
	dec=dec*r2d

	WRITE(*,*)" RADEC CALC",ra,dec,t0az,lat,long

	call crdrd2ae(ra,dec,lat,long,t0az,azim,elev)

	WRITE(*,*)" AZEL CALC",azim,elev

C  az,el are converted into radians
	azim=azim/r2d
	elev=elev/r2d

	val.az=azim+sss.azoff+(sss.daz*(sss.time-sss.th0))
	val.el=elev+sss.eloff+(sss.del*(sss.time-sss.th0))


        return
	end 

