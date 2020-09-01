CXX = gcc -w -DCNTRL
LIBS= -L/usr/lib -lnsl
#LIBS= -L/usr/lib -lpisock -lnsl

gsblosrv::
	$(CXX) -DSERVER gsblosrv.c LoFsw.c mytime.c -o gsblosrv $(LIBS)

client::
	$(CXX) -USERVER client.c -o client $(LIBS)
clean::
	rm -rf *.o core
