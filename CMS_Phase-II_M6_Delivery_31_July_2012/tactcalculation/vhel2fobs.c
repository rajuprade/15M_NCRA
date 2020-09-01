#include <tact.h>

int vhel2fobs(Gcord *gc, Garg *ga)
/*
  converts from Heliocentric Velocity to Observed Frequency
  input:
     ra
     dec
     eprefix
     epoch
     tlat
     tlong
     height
     rv      (heliocentric velocity)
     velsys  
     veldef  (radio/optical)
     freq    (rest freq)
     date
  output:
    freq1    (observed freq)
*/
{ double s[3],vbar[3],pbar[3],vhel[3],phel[3];
  double deqx,pv[6],vsky;
  double c=LIGHTSPEED;
  double sla_epj_(double *mjd); 
  double sla_dvdv_(double *v1, double *v2);
  void   sla_dcs2c_(double *ra, double *dec, double *s);
  void   sla_pvobs_(double *tlat,double *height,double *lst,double *pv);
  void   sla_evp_(double *mjd, double *deqx, double *vbar,double *pbar,
		  double *vhel,double *phel);


  deqx=-1.0; /* velocity vectors refered to mean equator and equinox at mjd*/
  if(gc->eprefix !='J' || gc->epoch !=2000)
  { //tact_err(__FILE__,"Input co-ordinates are not in J2000\n",NULL);
    return 1;
  }
  if(gc->velsys != HELIOCENTRIC)
  { //tact_err(__FILE__,"Velocity must be HELIOCENTRIC",NULL);
    return 1;
  }
  lct2lst(gc,ga); /* compute lst and mjd */
  gc->epoch1=sla_epj_(&gc->mjd); 
  prec(gc,ga); /* precess co-ordinates to mjd */
  sla_dcs2c_(&gc->ra1,&gc->dec1,&s); /* unit vector along source direction */
  sla_evp_(&gc->mjd,&deqx,vbar,pbar,vhel,phel); /* heliocentric velocity of earth's center */
  sla_pvobs_(&gc->tlat,&gc->height,&gc->lst,pv); /* Obs pv in true equator equinox of date */
  vhel[0] += pv[3];  vhel[1] += pv[4];  vhel[2] += pv[5]; /* topocentric velocity of obs +
							     heliocentric velocity of earth center*/
  vsky = gc->rv*1.0e3 -sla_dvdv_(vhel,s)*149.597870e9; /* from AU/s to m/s */
  if(gc->veldef==OPTICAL)
  { gc->freq1 = gc->freq/(1.0+vsky/c); gc->freq1sys=OBSERVATORY; return 0;}
  if(gc->veldef==RADIO)
  { gc->freq1 = gc->freq*(1.0-vsky/c); gc->freq1sys=OBSERVATORY; return 0;}
  
  //tact_err(__FILE__,"Velocity Defenition must be RADIO or OPTICAL\n",NULL);
  return 1;

}
