#include <stdio.h>
#include <string.h>

static const char *digits = "0123456789";

/*******  convert float to a string. Max keep 6 digits *****/

static int multab[] =
{
    1, 10, 100, 1000, 10000, 100000, 1000000, 10000000
};

const char *ftoa(float f, int n)
{
    static char buf[33];
    register char *fbuf;
    static int nmax = sizeof(multab) / sizeof(multab[0]);
    int i, sign = 0;
    register float ff;
    register int fi, ffi, l;

    if (n >= nmax || n < 0)
		n = nmax - 1;

    if (f < 0) {
		f = -f;
		sign = '-';
	}

    f += 0.05 / multab[n];	/* rounding */
    fi = f;
    ff = f - fi;

    *(fbuf = buf + n + 2) = '.';

    if (ff < 1.0 / multab[n]) {
		*++fbuf = '0';
    }
    else {
		for (i = 1; i <= n; i++) {
		    *++fbuf = *(digits + (ffi = (ff *= 10.0)));
		    ff = ff - ffi;
		}
    }
    *++fbuf = '\0';
    /* covert the interal part */

    fbuf = buf + n + 2;
    while (fi >= 10) {
		*--fbuf = *(digits + (fi - (l = fi / 10) * 10));
		fi = l;
    }
    *--fbuf = *(digits + fi);
    if (sign)
		*--fbuf = sign;

    return fbuf;
}
