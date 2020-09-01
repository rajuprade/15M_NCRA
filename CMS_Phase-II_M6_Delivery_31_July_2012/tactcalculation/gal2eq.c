#include<stdio.h>

#include<string.h>

#include"tact.h"


void convertgaltoeq(Gcord *gc, Garg *ga)
{

 sla_galeq_(&gc->glong,&gc->glat,&gc->ra1,&gc->dec1);

 printf("\n new Galactic Long =%f\n",gc->glong);
 printf("\n new Galactic Latitude =%f\n",gc->glat);



 /***************************************************************************************/
  return(0);

}
