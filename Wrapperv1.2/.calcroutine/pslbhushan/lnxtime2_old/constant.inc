	double precision pi,twopi,piovr2,degree,arcmin,arcsec,r2d,r2h,E
	double precision LOG_E_10,LOG_E_2,LOG_10_E
	parameter(pi = 3.141592653589793)
	parameter(twopi = 6.283185307179586)
	parameter(piovr2 = 1.570796326794897)
	parameter(degree = 0.017453292519943296)         
C  	(radians per degree) 

	parameter(arcmin = 0.000290888208665722)     
C	(radians per arc-minute)

	parameter(arcsec = 0.000004848136811095)  
C	(radians per arc-second)

	parameter(r2d = 57.29577951308232)    
C 	(degrees per radian)

	parameter(r2h = 3.819718634205488)       
C	(hours (angle) per radian)
 
	parameter(E = 2.718281828459045)  
C	(base of natural logs)

	parameter(LOG_E_10 = 2.302585092994045)  
C	(log (base e) of 10)

	parameter(LOG_E_2 = 0.6931471805599453)
C	(log (base e) of 2)

	parameter(LOG_10_E = 0.4342944819032518) 
C	(log (base 10) of e)

