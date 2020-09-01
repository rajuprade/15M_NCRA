CC = gcc
CFLAGS = -Wall -g -I/usr/include/libxml2
 LIBS = -lxml2

mcm_parser:	mcm_parser.o
	$(CC) $(CFLAGS) $(LIBS) -o $@ mcm_parser.o
