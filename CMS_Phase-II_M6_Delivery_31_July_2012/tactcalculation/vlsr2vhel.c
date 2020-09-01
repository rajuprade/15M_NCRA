#include <tact.h>

int vlsr2vhel(Gcord *gc, Garg *ga)
/*
  converts from Kinematic LSR to Heliocentric Velocity.
  input:
     ra
     dec
     eprefix
     epoch
     rv      (lsr velocity)
     velsys  
  output:
    rv1      (heliocentric velocity)
    vel1sys  
*/
{ double vsun;
  float sla_rvlsrk_(float *ra, float *dec);
  float  ra,dec;

  if(gc->eprefix !='J' || gc->epoch !=2000)
  { //tact_err(__FILE__,"Input co-ordinates are not in J2000\n",NULL);
    return 1;
  }
  if(gc->velsys != LSR)
  { //tact_err(__FILE__,"Velocity must be LSR",NULL);
    return 1;
  }
  ra=gc->ra;dec=gc->dec;  vsun=sla_rvlsrk_(&ra,&dec);
  gc->rv1 = gc->rv + vsun;
  gc->vel1sys=HELIOCENTRIC;
  gc->velsys=HELIOCENTRIC; // Added This line to support LSR to HEL conversion for calculating sky frequency
  return 0;
}
