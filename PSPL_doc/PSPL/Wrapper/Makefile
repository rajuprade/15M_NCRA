########################################################################
# CMS Wrapper Server $ Version 1.0, Apr 30,2011, SRB $
# use Make -f Makefile
# This makefile is used to build targets
# invokeWrapper
#modified for Libxml inclusion.............
########################################################################
.SUFFIXES:
.SUFFIXES:	.c .o
INCLUDEDIR	=-L/usr/include/libxml2 -lxml2
HEADERS		= invokeWrapper.h wrapperCom.h handleQue.h xmlParse.h servCMS.h consumCMS.h
CC              =gcc
CFLAGS          = -Wall -g -I /usr/include/libxml2 
LIBS= -lm -lpthread -L/usr/lib -lnsl -lxml2
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


#CC     = gcc
#CFLAGS = -Wall -g -I /usr/local/libxml2-2.7.7/include
#LIBS   = -lxml2

#reader1:	reader1.o
#	$(CC) $(CFLAGS) $(LIBS) -o $@ reader1.o
