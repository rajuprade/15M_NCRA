#include <tact.h>

static char rcsid[]="$Id: lct2lst.c,v 1.1 1998/01/16 07:14:42 chengalu Exp $";

int lct2lst(Gcord *gc, Garg *ga)
/*
  converts the local civil time to local siderial time
  input:
       lct
       dut
       tlong
  output:
       lst
       gmst
       gast
       utc
       ut1
       mjd

  Note: The mjd is a date and *not* an integer day. gc->mjd can hence
        be used for all the time transforming sla functions. IT is NOT
        neccesary to add gc->utc to the existing gc->mjd, this has
        already been done in lct2utc()
*/
{

  /* compute UTC from LCT */
      if(lct2utc(gc,ga)){
     // tact_err(__FILE__,"Error computing UTC\n",NULL);

     printf("\n Error here at LCT to utc");
      return 1;
 }

  /* compute UT1 from UTC */
  gc->ut1=gc->utc+gc->dut;
  gc->mjd += RAD2DAY(gc->dut);

  /* compute GMST from UT1 */
  gc->gmst=sla_gmst_(&gc->mjd);

  /* compute equation of the equinoxes 
     (ignore change to TDB) */
  gc->gast=gc->gmst + sla_eqeqx_(&gc->mjd);

  
  /* compute LAST from GAST */
  gc->lst=gc->gast+gc->tlong;
  
  /* all done */
  return 0;
}
