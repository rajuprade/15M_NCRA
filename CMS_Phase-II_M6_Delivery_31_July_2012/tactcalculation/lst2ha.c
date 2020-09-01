#include <tact.h>

static char rcsid[]="$Id: lst2ha.c,v 1.1 1998/01/16 07:15:35 chengalu Exp $";

int lst2ha(Gcord *gc, Garg *ga)
/*
  converts from (lst,ra) to ha

  input:
  lst
  ra (assumed apparent ra)

  output:
  ha
*/

{

  gc->ha=gc->lst-gc->ra;

  return 0;
}
