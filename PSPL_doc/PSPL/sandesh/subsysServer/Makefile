obj= serv.o sockcommn.o 
subsysserv: $(obj) 
	cc -o subsysserv sockcommn.o serv.o 
	@echo "make complete."
sockcommn.o:
serv.o:
clean:
	rm subsysserv $(obj)
	@echo "subsysserv, $(obj) files are removed."
