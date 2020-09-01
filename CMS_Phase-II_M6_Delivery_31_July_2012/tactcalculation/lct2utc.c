#include <tact.h>

static char rcsid[]="$Id: lct2utc.c,v 1.1 1998/01/16 07:15:09 chengalu Exp $";

int lct2utc(Gcord *gc, Garg *ga)
{

 
/*
  converts the local civil time to universal co-ordinated time
  input:
       lct    
       gyear
       gmonth
       gday
  output:
       mjd
       utc
  NOTE:The mjd is a date and *not* an integer day. gc->mjd can hence
       be used for all the time transforming sla functions. gc->utc 
       has already been added to gc->mjd (calculated for 0h UT on the
       specified Gregorian date) on output from this program.

*/
  int gy,gm,gd,ierr;
  
  
  gc->utc=gc->lct+gc->tzone;

  /* convert to MJD */
  ierr=0;
 gy=(int)floor(gc->gyear);
 gm=(int)floor(gc->gmonth);
 gd=(int)floor(gc->gday);

  
 


 sla_cldj_(&gy,&gm,&gd,&gc->mjd,&ierr);



  if(ierr)
    return ierr;
    
  /* ignore difference in length between UT1 and UTC seconds */
  gc->mjd +=RAD2DAY(gc->utc);
    
  return 0;

}
