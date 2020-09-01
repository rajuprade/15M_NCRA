
#ifndef _SOURCE_HEADER_

#define _SOURCE_HEADER_

typedef struct {

        char            name[12];
/* make union of double aa[17] 
*/  
        double           ra0;
        double           dec0;
        double           ep0;
        double           rad;
        double           decd;
        double           epd;
        double           raoff;
        double           dra;
        double           decoff;
        double           ddec;
        double           te0;
        double           azoff;
        double           daz;
        double           eloff;
        double           del;
        double           th0;
        double           time;
/* Added to extra para in source file. It is defined at the ABC in different struct and newtrk.c 
 * take into the account. Here azel.c calculate equivalent to newtrk.c - JPK Aug 16, 2012
 */
        double           azcorr;
        double           elcorr;
       
}               SOURCE;

typedef struct {
/* make union of double res[8] */
      double  lctr;
      double  ldayr;
      double  lcts;
      double  ldays;
      double  az;
      double  el;
      double  deltaz;
      double  deltel;
} final;

union udcoord {
        double dcoord[8];
        double          rad_ref;
        double          decd_ref;
        double          depoch_ref;
        double          rad_date;
        double          decd_date;
        double          rad_app;
        double          decd_app;   
        double          depoch_date;
};

#endif
