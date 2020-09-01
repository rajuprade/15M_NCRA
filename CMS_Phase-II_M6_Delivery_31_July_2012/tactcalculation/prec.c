#include <tact.h>

static char rcsid[]="$Id: prec.c,v 1.1 1998/01/16 07:17:11 chengalu Exp $";

int prec(Gcord *gc, Garg *ga)
/*
  converts from one mean place to another mean place.
  input:
     ra
     dec
     eprefix
     epoch
     epoch1
  output:
     ra1
     dec1
     e1prefix      (set to eprefix)
     equinox1      (set to epoch1)


*/
{
  double ra,dec;

  ra=gc->ra;
  dec=gc->dec;

  switch(gc->eprefix){
  case 'B':
    
    printf("\nM at B");
    sla_preces_("FK4",&gc->epoch,&gc->epoch1,&ra,&dec,3);

    printf("\n ra =%f",ra);



	printf("\nM Returned from B");

    break;
  case 'J':
    sla_preces_("FK5",&gc->epoch,&gc->epoch1,&ra,&dec,3);
    break;
  default:
    //tact_err(__FILE__,"Illegal System %c",gc->eprefix,NULL);

    return 1;
  }
  
  /* set output co-ordinate system */
  gc->e1prefix=gc->eprefix;
  gc->ra1=ra;
  gc->dec1=dec;
  gc->equinox1=gc->epoch1;

  return 0;
}
