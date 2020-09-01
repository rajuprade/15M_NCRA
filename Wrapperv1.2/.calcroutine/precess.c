#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>

#include "source.h"
#include "constant.h"

void precess(SOURCE *sss, double dcoord[], int *mode) 
/*
C This subroutine finds the ra,dec at one epoch,given ra,dec at another
C epoch
C
C      input:
C           ra0 in radians    right ascension at the initial epoch
C           dec0 in radians   declination at the initial epoch
C           ep0(say,2000.0d0)   initial epoch
C           epd               final epoch
C
C      output:
C           rad in radians    right ascension at the final epoch
C           decd in radians   declination at the final epoch
C          
C      called:
C           crdprec
C      (input ra,dec and output ra,dec  to crdprec are in degrees)
C           sla_map
C      (input ra,dec and output ra,dec  to crdprec are in radians)  !!
*/
{
      double  *rai,*deci,*epi,*raf,*decf,*epf,*raa,*deca,*ram,*decm;
      double  *epoch0,*epochd,*epoch2000;
      double *dummy[4];
      int  i ;

   /*---------------< Fort routines work with the C Pointers >---------------------------*/
      epoch0 = (double *)malloc(sizeof(double)); epochd = (double *)malloc(sizeof(double)); epoch2000= (double *)malloc(sizeof(double)); // Epoch
      rai = (double *)malloc(sizeof(double));  deci = (double *)malloc(sizeof(double)); epi = (double *)malloc(sizeof(double));  // Given

      raf = (double *)malloc(sizeof(double));  decf = (double *)malloc(sizeof(double)); epf = (double *)malloc(sizeof(double)); // Final
      raa =  (double *)malloc(sizeof(double));  deca = (double *)malloc(sizeof(double));
      ram =  (double *)malloc(sizeof(double));  decm = (double *)malloc(sizeof(double));
       *epoch2000=2000.0027379;  // After uncommenting this like tact, cms and calepochc - AZ EL matching within arc sec JNC/JPK 14 MARCH 2013

      for(i=0;i<4;i++) { dummy[i]= (double *)malloc(sizeof(double)); *dummy[i]=0.0;} i=0;
    
   /*-------------------------------------------------------------------------------------*/
       

      djm2e_(&sss->ep0,epoch0);
      djm2e_(&sss->epd,epochd);

      fprintf(stderr, " MJD ref %g  target %g : YEAR Ref %g Target %g  \n",sss->ep0,sss->epd,*epoch0,*epochd);

      if( (*mode) == 10 ) {
            *rai = sss->ra0; *deci = sss->dec0; *epi = *epoch0; *epf = *epochd; 
      } else  {
            *rai = sss->rad; *deci = sss->decd; *epi = *epochd; *epf = *epoch0; 
      }
      
      if(abs (rint(*epi - *epoch2000) * 100 ) != 0 ) {
    /* If not J2000, precess to J2000, convert rai, deci into degrees */
           *rai = *rai * (double )r2d ;
           *deci = *deci * (double )r2d;
            crdprec_(rai,deci,epi,epoch2000,raf,decf);
            *epi=*epoch2000; // jnc 02/mar/2013

      }else {
           *raf = *rai * (double )r2d;
           *decf = *deci * (double )r2d;
      }
           crdprec_(raf,decf,epi,epf,ram,decm);
           *ram = *ram/(double) r2d;
           *decm = *decm/(double)r2d;
           *raf = *raf/(double)r2d;
           *decf = *decf/(double)r2d;

/**  Given:
*     SUBROUTINE sla_MAP (RM, DM, PR, PD, PX, RV, EQ, DATE, RA, DA)
*     RM,DM    dp     mean RA,Dec (rad)
*     PR,PD    dp     proper motions:  RA,Dec changes per Julian year
*     PX       dp     parallax (arcsec)
*     RV       dp     radial velocity (km/sec, +ve if receding)
*     EQ       dp     epoch and equinox of star data (Julian)
*     DATE     dp     TDB for apparent place (JD-2400000.5)
*
*  Returned:
*     RA,DA    dp     apparent RA,Dec (rad) */

      fprintf(stdout, "sla-Map : ram %g decm %g Epch2000 %g epD %g ra app %g  decapp %g \n", *ram * (double)r2d,*decm *( double)r2d, *epoch2000, sss->epd, *raa, *deca);
      fflush(stdout);
            slamap_(raf,decf,dummy[0],dummy[1],dummy[2],dummy[3],epoch2000, &sss->epd, raa, deca);

      if(*mode == 10 ) {
         sss->rad = *raa;
         sss->decd = *deca; 

        dcoord[0]= sss->ra0;
        dcoord[1]= sss->dec0;
        dcoord[3]= *raa;
        dcoord[4]= *deca;
        dcoord[5]= *ram;
        dcoord[6]= *decm;

        fprintf(stderr," Precess out %4.14g %4.14g %4.14g %4.14g \n %4.14g %4.14g %4.14g %4.14g \n", dcoord[0], dcoord[1],dcoord[2],dcoord[3], dcoord[4],dcoord[5],dcoord[6],dcoord[7]) ; 

      }else {  sss->ra0 = *raf; sss->dec0 = *decf; }

/* Free the pointers */
      free(epoch0); free(epochd); free(epoch2000);
      free(rai); free(deci); free(epi);
      free(raf); free(decf); free(epf);
      free(raa); free(deca); free(ram); free(decm); 
      for(i=0;i<4;i++) { free(dummy[i]); }
      return ;
}
