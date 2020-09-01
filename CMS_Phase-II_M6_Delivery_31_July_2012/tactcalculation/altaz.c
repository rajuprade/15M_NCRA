#include <tact.h>

static char rcsid[]="$Id: e2h.c,v 1.1 1998/01/16 07:07:00 chengalu Exp $";

int altaz(Gcord *gc, Garg *ga)
/*
  converts from (ha,ra,dec) to (alt,az,pa)
  No correction for refraction effects or for abberation.

  input:
  ha
  dec
  tlat

  output:
  alt
  az
*/

{ double azd,azdd,eld,eldd,pad,padd;
  
  sla_altaz_(&gc->ha,&gc->dec,&gc->tlat,&gc->az,&azd,&azdd,&gc->alt,
	     &eld,&eldd,&gc->pa,&pad,&padd);
  
  return 0;
}
