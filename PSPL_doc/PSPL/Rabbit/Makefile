abc: mainabc.o comhlink.o 
	gcc $(CFLAGS) -o  abc  mainabc.o comhlink.o

mainabc.o: mainabc.c comhlink.h
	gcc $(CFLAGS) -c mainabc.c

comhlink.o: comhlink.c comhlink.h
	gcc $(CFLAGS) -c comhlink.c

clean: 
	rm -f *.o abc

