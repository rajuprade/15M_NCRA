C
C	National Radio Astronomy Observatory, Socorro, NM 87801
C	Software Development Environment (SDE)
C++
C
      SUBROUTINE CRDRD2AE (RA, DEC, LAT, LON, TIME, AZ, EL)
C
C Get AZ, El given RA, DEC, LAT, and TIME
C
C   RA		DBLE	input	Right Ascension (degrees)
C   DEC		DBLE	input	Declination (degrees)
C   LAT         REAL    input   Latitude of location (degrees)
C   TIME(long)  DBLE    input   Longitude of location (degrees)
C   DAY(time)   REAL    input   MJD of observation
C   UT          REAL    input   Universal Time (degrees)
C   AZ          REAL    output   Azimuth (degrees)
C   EL          REAL    output   Elevation (degrees)
C
C Audit trail:
C
C===================================================================
C
      DOUBLE PRECISION  RA, DEC
      DOUBLE PRECISION  LAT, LON
      DOUBLE PRECISION	TIME
      DOUBLE PRECISION  AZ, EL
C
      CHARACTER*(*)	ROUTINE
      PARAMETER		(ROUTINE = 'CRDRD2AE')
C
      DOUBLE PRECISION  COSLAT, SINLAT, COSDEC, SINDEC, COSHA, SINHA
      DOUBLE PRECISION  HA, LST, D2R,R2D, SINAZ, COSAZ, SINEL
C     DOUBLE PRECISION	SLAGMST
C===================================================================
C
C      IF (ERROR) GO TO 999
C
C We work in degrees
C
      D2R = ATAN(1.0D0)/45.0D0
      R2D = 57.29577951308232;
C

C     LST = SLAGMST(TIME,LST) / D2R - LON
      CALL SLAGMST(TIME,LST)
      WRITE(*,*)" iLST ",(LST - LON/R2D)
      LST = LST / D2R - LON
      WRITE(*,*)" LST -",LST
      
      HA = LST - RA
      COSLAT = COS(D2R*LAT)
      SINLAT = SIN(D2R*LAT)
C
      COSHA = COS(D2R*HA)
      SINHA = SIN(D2R*HA)
      COSDEC = COS(D2R*DEC)
      SINDEC = SIN(D2R*DEC)
      SINEL = SINLAT * SINDEC + COSLAT * COSDEC * COSHA
      EL = ASIN(SINEL) / D2R
C
C These next two terms actually ignore cos(el) which cancels
C
      COSAZ = (COSLAT * SINDEC - SINLAT * COSDEC * COSHA)
      SINAZ = - COSDEC * SINHA
      AZ = ATAN2(SINAZ, COSAZ) / D2R

	if (az.lt.0.0)then
	     az=az+360.0
	endif
C
 999  CONTINUE
      END




