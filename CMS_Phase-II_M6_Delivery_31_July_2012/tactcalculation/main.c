

#include<stdio.h>
#include<string.h>
#include"tact.h"


int main()
{
 int cnt;
 Gcord a;
 Garg b;

a.gyear=2011;                     /* greogrian year */
a.gmonth=4;                       /* gregorian month */
a.gday=12;

a.eprefix='J';
a.epoch=2000;

a.tlong=DEG2RAD(73.49);
a.tlat=DEG2RAD(19);


// dra,0,ddec,0,dra1,0,ddec1,0,px,0,rv,0,dut,0

a.dra=0;
a.ddec=0;
a.dra1=0;
a.ddec1=0;
a.px=0;
a.rv=0;
a.dut=0;
a.equinox=1950;
a.tzone=HRS2RAD(-5.5);
a.ra=DEG2RAD(79.566);      
a.dec=DEG2RAD(16.5908); 
a.el_lim=DEG2RAD(17);
a.epoch1=2000;
a.freq=239.0; // 238.0 (Mhz)
a.height=560;  // pune height from MSL(m)
a.veldef=OPTICAL;
a.rv=8;
a.lct=HRS2RAD(19.40862);
a.veldef= RADIO;
a.velsys= LSR;

a.glat = DEG2RAD(0); 
a.glong = DEG2RAD(0);

a.lst_string=(char*)malloc(sizeof(char)*100);
a.rise_string=(char*)malloc(sizeof(char)*100);
a.set_string=(char*)malloc(sizeof(char)*100);
a.uptime_string=(char*)malloc(sizeof(char)*100);

//calculate(&a,&b);
//converteqtogal(&a,&b);

for(cnt=0;cnt<360;cnt++){
a.glat = DEG2RAD(cnt);
a.glong = DEG2RAD(cnt);
convertgaltoeq(&a,&b);
printf("\n ra :%f dec %f",RAD2DEG(a.ra1),RAD2DEG(a.dec1));
}
//convertgaltoeq(&a,&b);
printf("\n Calculations done ");
printf("\n SKY %f ",a.rv1);
printf("\n ra :%f dec %f",a.ra1,a.dec1);
free(a.lst_string);
free(a.rise_string);
free(a.set_string);
free(a.uptime_string);

return 0;


}
