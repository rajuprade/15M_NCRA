#PREFIX=/home/

#LIBDIR=$(PREFIX)/lib/tact/
#BINDIR=$(PREFIX)/bin/
#MANDIR=$(PREFIX)/man/man1/

#
# Should not need to make modifications below this line
#
CFLAGS= -DTACT_SYS_DEF_FILE=\"/astro/config/tactrc\" -DTACT_VERSION=\"1.03\"
TACTINC=.
SLALIB=libsla.a
CC=gcc -g -fPIC
f=gfortran -fno-second-underscore -g
c=$f $(CFLAGS) -I$(TACTINC)
.c.o:
	$c -c $<

TOBJ= lct2lst.o lct2utc.o prec.o stime.o stime_.o ltostr.o rise_set.o e2h.o lst2ha.o altaz.o calculate.o galactic.o vlsr2vhel.o vhel2vlsr.o vhel2fobs.o gal2eq.o
libtact.so: $(TOBJ) tact.h
	$f  $(TOBJ) -shared -o $@ $(SLALIB)

static: $(TOBJ) tact.h
	$f  $(TOBJ) -o tact $(STATIC_SLALIB)

install:tact
	\cp tact $(BINDIR)
	\cp tactrc $(LIBDIR)
	\cp tact.1 $(MANDIR)

clean:
	/bin/rm -rf *.o core


