#
# Makefile For LST and the Source RA-DEC Precession, Equitorial to Horizontal Coordinate system conversion
# , Rise & Set time calculution - Jitendra Dec 2nd, 2010
#
.SUFFIXES:
.SUFFIXES:	.c .f .o
CC=cc -g -fPIC
#f=gfortran -fno-second-underscore -g 
F77=gfortran -fno-second-underscore -fPIC -g
#F77=gf4   lib gfortran for acer laptop
OPT=-c ${DEBUG}
LINK= ${F77}

HEADERS		= source.h constant.h
INCLUDEDIR=
LIBPATH=
LIBS=-lm

#SLALIB=/usr/local/lib/libsla.a    For myacer laptop
SLALIB=libsla.a

#JNIPATH=-shared -I/usr/lib/jvm/java-6-sun/include -I//usr/lib/jvm/java-6-sun/include/linux/ 
## For 15m Wrapper Tracking no JNI Path needed.
JNIPATH=

#azel.f rset.f

CFILES0		= calepochc.c precess.c rset.c azel.c stime_.c ltostr.c fangle_.c sangle_.c  
FFILES0		= fryej.f ep2daj.f crdprec.f crdrd2ae.f slagmst_.f slacaldj.f slacldj.f sladranrm.f djm2e.f \
slapreces.f sladjcl.f sladmxv.f slaprec.f sladcc2s.f sladcs2c.f slaprebn.f map.f


COBJECT		= ${CFILES0:.c=.o}
FOBJECT		= ${FFILES0:.f=.o}

LIBRARY=libcalcepochc.a
TARGET=${LIBRARY}
#TARGET=calepochc
all: ${HEADERS} ${TARGET}

.c.o:
	${CC} ${OPT} -o ${<:.c=.o} $<

.f.o: 
	${F77} ${OPT} -o ${<:.f=.o} $<

#${TARGET} : ${HEADER} ${COBJECT} ${FOBJECT}
#${LINK} ${COBJECT} ${FOBJECT} ${SLALIB} -o $@

${LIBRARY} : ${HEADER} ${COBJECT} ${FOBJECT} 
	 ar -rv ${LIBRARY} ${COBJECT} ${FOBJECT} ${SLALIB} ${JNIPATH} 

clean :
	/bin/rm -rf *.o core
