#include <tact.h>

static char rcsid[]="$Id: e2h.c,v 1.1 1998/01/16 07:07:00 chengalu Exp $";

int e2h(Gcord *gc, Garg *ga)
/*
  converts from (ha,dec) to (alt,az)
  No correction for refraction effects or for abberation.

  input:
  ha
  dec
  tlat

  output:
  alt
  az
*/

{
  float ha,dec,tlat,az,alt;

  ha=gc->ha;
  dec=gc->dec;
  tlat=gc->tlat;
  az=gc->az;
  alt=gc->alt;
  
  sla_e2h_(&ha,&dec,&tlat,&az,&alt);
  
  gc->az=az;
  gc->alt=alt;

  return 0;
}
