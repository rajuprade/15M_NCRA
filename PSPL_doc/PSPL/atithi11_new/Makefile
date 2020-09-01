########################################################################
# CMS Wrapper Server $ Version 1.0, Apr 14,2011, JPK $
# use Make -f Makefile
# This makefile is used to build targets
# invokeWrapper
########################################################################
.SUFFIXES:
.SUFFIXES:	.c .o
INCLUDEDIR	=
HEADERS		= invokeWrapper.h wrapperCom.h handleQue.h xmlParse.h servCMS.h consumCMS.h

CFLAGS		= -D_GNU_SOURCE -UDEBUGJ ${INCLUDEDIR} 
CC = gcc -Wall -g -I. ${LIBS}
LIBS= -lm -lpthread -L/usr/lib -lnsl
LINK = gcc -g 

CFILES0		= invokeWrapper.c wrapperCom.c handleQue.c xmlParse.c servCMS.c consumCMS.c
#FFILES1		= mon.c
#FFILES2		= record.c recsubs.c corrsub.c sort.c
#FFILES3		= agcorr.c recsubs.c corrsub.c sort.c
#FFILES4		= dasstat.c
OBJECT0			= ${CFILES0:.c=.o}
#OBJECT1			= ${CFILES1:.c=.o}
#OBJECT2			= ${CFILES2:.c=.o}
#OBJECT3			= ${CFILES3:.c=.o}
#OBJECT4			= ${CFILES4:.c=.o} 

TARGET		= invokeWrapper
####################################################
all:	${HEADERS} ${TARGET}

.c.o:
	${CC} -c ${CFLAGS} -o ${<:.c=.o} $<

invokeWrapper:	${HEADER} ${OBJECT0}
		${LINK} ${OBJECT0} ${LIBS} -o $@ 

clean:
	/bin/rm -f ${OBJECT0} ${TARGET}
