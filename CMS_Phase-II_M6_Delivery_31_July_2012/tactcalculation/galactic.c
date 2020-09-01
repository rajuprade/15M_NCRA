#include<stdio.h>

#include<string.h>

#include"tact.h"


void converteqtogal(Gcord *gc, Garg *ga)
{

 sla_eqgal_(&gc->ra,&gc->dec,&gc->glong,&gc->glat);

 printf("\n new Galactic Long =%f\n",gc->glong);
 printf("\n new Galactic Latitude =%f\n",gc->glat);



 /***************************************************************************************/
  return(0);

}
