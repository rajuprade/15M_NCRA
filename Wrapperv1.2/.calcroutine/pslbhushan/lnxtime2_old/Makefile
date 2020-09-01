#
# Makefile For LST and the Source RA-DEC Precession, Equitorial to Horizontal Coordinate system conversion
# , Rise & Set time calculution - Jitendra Dec 2nd, 2010
#
.SUFFIXES:
.SUFFIXES:	.c .f .o

CC=cc
F77=gf4 
OPT=-c -fPIC ${DEBUG}
LINK= ${F77}
SOOPT=-shared

HEADERS		= source.h constant.h
INCLUDEDIR=
LIBPATH=
LIBS=-lm
SLALIB=libsla.a

#azel.f rset.f
#risesetwrapper.c precesswrapper.c lst.c
CFILES0	 = jnaprecesswrapper.c jnacalculation.c azelwrapper.c lstwrapper.c lstcalculation.c lstcalc.c risesetwrapper.c precesswrapper.c calepochc.c precess.c rset.c azel.c stime_.c ltostr.c fangle_.c sangle_.c  
FFILES0		= fryej.f ep2daj.f crdprec.f crdrd2ae.f slagmst_.f slacaldj.f slacldj.f sladranrm.f djm2e.f \
slapreces.f sladjcl.f sladmxv.f slaprec.f sladcc2s.f sladcs2c.f slaprebn.f map.f 	


COBJECT		= ${CFILES0:.c=.o}
FOBJECT		= ${FFILES0:.f=.o}

TARGET=		libastronomycalc.so

#all: ${HEADERS} ${TARGET}

.c.o:
	${CC} ${OPT} -o ${<:.c=.o} $<

.f.o: 
	${F77} ${OPT} -o ${<:.f=.o} $<

#calepochc : ${HEADER} ${COBJECT} ${FOBJECT} 
#	${LINK} ${COBJECT} ${FOBJECT} ${SLALIB} -o $@

${TARGET} : ${HEADER} ${COBJECT} ${FOBJECT} 
	${LINK} ${COBJECT} ${FOBJECT} ${SLALIB} ${SOOPT} -o $@

#calepochc : ${HEADER} ${COBJECT} ${FOBJECT} ${LINK} ${COBJECT} ${FOBJECT} ${SLALIB} ${TARGET} -o $@

#my_main : ${HEADER} ${COBJECT} ${FOBJECT} ${LINK} ${COBJECT} ${FOBJECT} ${SLALIB} ${TARGET} -o $@


	
clean :
	/bin/rm -rf *.o core
