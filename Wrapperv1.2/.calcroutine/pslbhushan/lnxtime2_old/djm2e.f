
	subroutine djm2e(djm,epoch)
C-----------------------------------------------------------------
C   This subroutine converts modified julian day number to 
C   epoch
C
C   input:
C	  djm(modified julian day number)  double precision
C
C   output:
C	  epoch                            double precision
C
C   called:
C	   sladjcl,frye (FRYEJ -- modified for leap yr correction    
C                        JPK )
C-----------------------------------------------------------------

	double precision djm,epoch,fd,day
	integer iy,im,id,j
	
	call sladjcl(djm,iy,im,id,fd,j)
	

	day=id+fd

	call fryej(iy,im,day,epoch)

	return
	end
