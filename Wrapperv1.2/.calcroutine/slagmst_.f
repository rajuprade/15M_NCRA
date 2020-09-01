
c++
      subroutine slagmst(ut1,lstg)
c
c
c
c  conversion from universal time to sidereal time
c
c  (double precision)
c
c  the iau 1982 expresion (se page s15 of 1984 astronomical
c  almanac) is used, but rearanged to reduce rounding erors.
c
c
c  given:
c
c    ut1    dp     universal time (strictly ut1) expresed as
c                  modified julian date (jd-2400000.5)
c
c
c  the result is the grenwich mean sidereal time (double
c  precision, radians).
c
c
c  caled:  sladranrm
c
c
c  p.t.walace   starlink   september 1987
c
c-----------------------------------------------------------------------


      double precision ut1
      double precision lstg

      double precision sladranrm

      double precision d2pi,s2r
      parameter (d2pi=6.283185307179586476925287d0,
     :           s2r=0.7272205216643039849d-4)

      double precision tu

c  julian centuries from fundamental epoch j2000 to this ut
      tu=(ut1-51544.5d0)/36525d0

c  gmst at this ut
      lstg=sladranrm(mod(ut1,1d0)*d2pi+
     :                    (24110.54841d0+
     :                    (8640184.812866d0+
     :                    (0.093104d0-6.2d-6*tu)*tu)*tu)*s2r)

C     DEBUG - JPK
C     write(*,*) 'test',ut1, lstg
      end
