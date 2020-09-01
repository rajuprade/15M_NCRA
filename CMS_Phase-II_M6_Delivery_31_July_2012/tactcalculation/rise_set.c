#include "tact.h"

#define TIME_ERR HRS2RAD((1.0/3600.0))
#define MAX_ITER 16

int rise_set(Gcord *gc, Garg *ga)
/*
  converts from equitoral(J2000) to ecliptic co-ordinates

  input:
  ra
  dec
  mjd    (Note: should be TDB, instead is UTC)
  
*/
{ double lst0,u[2],l[2],el0,el1,el2,el_lim,dt,h,m;
  int    i,n,na;
  char  *aw[MAX_ARG],am[MAX_CMD_LEN];

  el_lim=gc->el_lim;
  lst0=gc->lst; 
  lst2ha(gc,ga);
  e2h(gc,ga);  el0=el1=(gc->alt-el_lim);
  dt=0.1;



 printf("\n MJD here is %f",gc->mjd);


  for(n=0,h=dt;h<24.0;h+=dt) /* find approx rise, set times */
  { gc->lst=lst0+HRS2RAD(h); lst2ha(gc,ga); e2h(gc,ga);
  

    el2=(gc->alt-el_lim);
    if(el2*el1<0.0)
    { switch(n)
      { case 0: u[0]=HRS2RAD(h); l[0]=HRS2RAD(h-dt); n++;break;
        case 1: u[1]=HRS2RAD(h); l[1]=HRS2RAD(h-dt); n++;break;


       default:
		       printf("\n Returning from here....");
		       return -1;
      }
    }
    if(n==2)break;
    el1=el2;
  }
  
  if(n==1) /* check if rise/set time is just before 0 hr */
  { gc->lst=lst0-HRS2RAD(dt); lst2ha(gc,ga); e2h(gc,ga);
    el2=(gc->alt-el_lim);
    if(el2*el0<0.0){l[1]=-HRS2RAD(dt); u[1]=0.0;n=2;}
  }
  if(n!=2)
  { //tact_err(__FILE__,"SRC not visibile from the telescope site!\n",NULL);

     
    return -1;
  }
  
  for(i=0;i<2;i++) /* refine the rise/set times by bisection */
  { n=0;
    while(fabs(u[i]-l[i])>TIME_ERR && n < MAX_ITER)
    { m=0.5*(u[i]+l[i]);
      gc->lst=lst0+u[i];lst2ha(gc,ga); e2h(gc,ga);el1=(gc->alt-el_lim);
      gc->lst=lst0+m;lst2ha(gc,ga); e2h(gc,ga);el2=(gc->alt-el_lim);
      if(el1*el2<0.0)l[i]=m;else u[i]=m;
      n++;
    }
    //if(n==MAX_ITER)
      //tact_err(__FILE__,"WARNING: root find didn't converge\n",NULL);
  }
  if(u[0]<0.0)u[0]+=HRS2RAD(24.0);
  if(u[1]<0.0)u[1]+=HRS2RAD(24.0);
  m=0.5*(u[0]+u[1]); /* work out which is rise and which is set time */
  gc->lst=lst0+m;lst2ha(gc,ga); e2h(gc,ga);el1=(gc->alt-el_lim);
  if(el1>0.0){gc->rise=gc->lct+u[0]/LSSEC;gc->set=gc->lct+u[1]/LSSEC;}
  else
  { /* settime == yesterday's track; subtract 3m56s for today's set*/
    gc->rise=gc->lct+u[1]/LSSEC;
    gc->set=gc->lct+u[0]/LSSEC-HRS2RAD((3.0/60+56.0/3600));
  }
  gc->lst=lst0;


  return 0;
}


#undef TIME_ACCURACY 
#undef MAX_ITER 

