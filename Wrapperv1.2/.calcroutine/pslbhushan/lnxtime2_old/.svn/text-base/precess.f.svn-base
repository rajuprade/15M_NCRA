      subroutine precess(sss,dcoord,mode)
C**********************************************************************
C This subroutine finds the ra,dec at one epoch,given ra,dec at another
C epoch
C
C      input:
C           ra0 in radians    right ascension at the initial epoch
C           dec0 in radians   declination at the initial epoch
C           ep0(say,2000.0d0)   initial epoch
C           epd               final epoch
C
C      output:
C           rad in radians    right ascension at the final epoch
C           decd in radians   declination at the final epoch
C
C      called:
C           crdprec
C      (input ra,dec and output ra,dec  to crdprec are in degrees)
C           sla_map
C      (input ra,dec and output ra,dec  to crdprec are in radians)  !!
C*********************************************************************

      include 'source.inc'
      include 'constant.inc'

      record/source/sss
c      record/final/val

      double precision dcoord(*)

      double precision r2d,rai,deci,epi,raf,decf,epf,raa,deca,ram,decm
      double precision epoch0,epochd,epoch2000/2000.0027379/
      integer mode,i

      

      call djm2e(sss.ep0,epoch0)
      call djm2e(sss.epd,epochd)
   
      write(*,*)"Epoch"
      write(*,*) sss.ep0,sss.epd,epoch0,epochd

      if(mode.eq.10)then
           rai=sss.ra0
           deci=sss.dec0
           epi=epoch0
           epf=epochd
      else
           rai=sss.rad
           deci=sss.decd
           epi=epochd
           epf=epoch0
      endif


 
      if(abs(nint((epi-epoch2000)*100)) .ne. 0) then
C      			if not J2000. precess to J2000
C convert rai,deci into degrees
          rai=rai*r2d
          deci=deci*r2d
          call crdprec(rai,deci,epi,epoch2000,raf,decf)
          epi=epoch2000
      else
          raf=rai*r2d
          decf=deci*r2d
      endif	
      call crdprec(raf,decf,epi,epf,ram,decm)
        ram=ram/r2d
        decm=decm/r2d
        raf=raf/r2d
        decf=decf/r2d
      call sla_map(raf,decf,0.d0,0.d0,0.d0,0.d0,epoch2000,sss.epd,
     1  raa,deca)



      if(mode.eq.10)then
          sss.rad=raa
          sss.decd=deca

          dcoord(1)=sss.ra0
          dcoord(2)=sss.dec0
          dcoord(4)=raa
          dcoord(5)=deca
          dcoord(6)=ram
          dcoord(7)=decm
          write(*,*)"Precess out"
          write(*,*) (dcoord(i),i=1,8)
      else
          sss.ra0=raf
          sss.dec0=decf
      endif

      return
      end

