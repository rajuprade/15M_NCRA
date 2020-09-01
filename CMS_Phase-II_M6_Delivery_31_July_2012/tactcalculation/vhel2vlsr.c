#include "tact.h"

int vhel2vlsr(Gcord *gc, Garg *ga)
/*
  converts from Heliocentric Velocity to Kinematic LSR
  input:
     ra
     dec
     eprefix
     epoch
     rv      (heliocentric velocity)
     velsys  
  output:
    rv1      (lsr velocity)
    vel1sys  
*/
{ double vsun;
  float sla_rvlsrk_(float *ra, float *dec);
  float  ra,dec;
  if(gc->eprefix !='J' || gc->epoch !=2000)
  { 
    return 1;
  }
  if(gc->velsys != HELIOCENTRIC)
  { 
    return 1;
  }
  ra=gc->ra;dec=gc->dec;  vsun=sla_rvlsrk_(&ra,&dec);
  gc->rv1 = gc->rv - vsun;
  gc->vel1sys=LSR;
  
  return 0;
}
