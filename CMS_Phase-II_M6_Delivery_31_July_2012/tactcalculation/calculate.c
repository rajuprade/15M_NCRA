#include<stdio.h>

#include<string.h>

#include"tact.h"


void calculate(Gcord *gc, Garg *ga)
{

	char format_string[]="3.3";
	//char lststring[80];
	//char lstangle[80];
	int i;
	int lst,precess,rise,dopset,vlsrflag;

	double ans;
	double *format;

	union{
		  double x;
		  unsigned char xx[8];
		}abc;

	int taz_calc;
	double dra1,ddec1,dal,daz;

//---------------------------------------------------------------------------------------------------------

if(gc->calculateLST==1){
	lst=lct2lst(gc,ga);

	if(!lst)
	{
	//	printf("\n LST in Rdians is %f \n",gc->lst);

	if(RAD2HRS(gc->lst)>24)       // Bhushan G 
	{
		gc->lst=gc->lst-HRS2RAD(24);
	}
	if(RAD2HRS(gc->lst)<0)       // Natasha A
	{
		gc->lst=HRS2RAD(24) + gc->lst;
	}
		abc.x=gc->lst;
		stime_(abc.xx,format_string,gc->lst_string);   // char * change
	}
	else
	{
	}
}


/*******************Precess Calculation ********************/
if(gc->calculatePrecess==1){
  gc->err_precess=1;
  precess=prec(gc,ga);
  if(!precess)
  {
	gc->err_precess=0;
    dra1=RAD2HRS(gc->ra1);
    ddec1=RAD2DEG(gc->dec1);
  }
  else
  {

  }
}

/********************************ALTITAZ******************************************/

if(gc->calculateALTAZ == 1){
	gc->err_altaz=1;
	gc->ha=gc->lst-gc->ra;
	taz_calc=altaz(gc,ga);

	if(!taz_calc)
	{
	  gc->err_altaz=0;

	  dal=RAD2DEG(gc->alt);
	  daz=RAD2DEG(gc->az);
	}
	else
	{

	}
}




/*****************RISE_SET ********************************************/
if(gc->calculateRiseSet ==1){
	gc->err_riseset=1;
	rise=rise_set(gc,ga);

	 if(!rise){
		 if(RAD2HRS(gc->rise)>24){
				gc->rise=gc->rise-HRS2RAD(24);
		 }
		 if(RAD2HRS(gc->set)>24){
			gc->set=gc->set-HRS2RAD(24);
		}
		 if(RAD2HRS(gc->rise)<0){

				gc->rise=HRS2RAD(24)+gc->rise;
		}

		 if(RAD2HRS(gc->set)<0){
				gc->set= gc->set+HRS2RAD(24);
		 }	
		 
		gc->err_riseset=0;

		abc.x=gc->rise;
		stime_(abc.xx,format_string,gc->rise_string);   // char * change

		abc.x=gc->set;

		stime_(abc.xx,format_string,gc->set_string);   // char * change
		gc->uptime=gc->set-gc->rise;

		abc.x=gc->uptime;
		stime_(abc.xx,format_string,gc->uptime_string);   // char * change
	 }
	 else
	 {
	 }
}



 /********************************************************************************/


if(gc->calculategalactic==1){
 sla_eqgal_(&gc->ra,&gc->dec,&gc->glong,&gc->glat);
}

 /**************************    DOPSET CALCULATION   ******************************************************/
if(gc->calculateDopeSet ==1){
   gc->err_dopset=1;

  // printf("\n\n DOPSET CALCULATIONS.......");

   if(gc->velsys==HELIOCENTRIC)
   {

    // Known inputs

	   // 1) Freq(Rest freq)
	   // 2) rv (Velosity of source.
	   // 3) velsys
	   // 4) veldef radio / optoical
     

		dopset=vhel2fobs(gc,ga);

		if(!dopset)
		{
			 gc->err_dopset=0;
			 vlsrflag=vhel2vlsr(gc,ga);

			 if(!vlsrflag)
			 {
			 }

			 else
			 {

			 }
		}
		else
		{
  
		}

   }
   else
   {
		vlsr2vhel(gc,ga);
		dopset=vhel2fobs(gc,ga);
       
		if(!dopset)
		{
			 gc->err_dopset=0;
			 vlsrflag=vhel2vlsr(gc,ga);
			 if(!vlsrflag)
			 {
			 }
			 else
			 {
			 }
		}
		else
		{
		}
   }

}


  return(0);


}






















