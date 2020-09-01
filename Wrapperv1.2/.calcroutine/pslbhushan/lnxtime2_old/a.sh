rm -f libastronomycalc.so 
make clean
 make
 gcc my_main.c libastronomycalc.so
 export LD_LIBRARY_PATH=.
 ./a.out
