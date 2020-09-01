/*INFORMATION		routine	 	int Debug_Print(char *name,
INFO					int lev,char *str,uchar pkt,
INFO					int pktcnt)
INFO				routine writes an error mesg *str,
INFO				from program name, if pri >0.
INFO				if pri<5 the erroneous packet is dumped
INFO				on a file
INFO				pktcnt is an identifier for the packet
INFO				ususally, the sequential pkt no
INFO
INFO				to put more intelligence ito give
INFO				selective printouts based on name
INFO				and lev
*/
#include	<stdio.h>
#define	OK 1

int	Debug_Print(pgname,debuglevel,dstr,pkt,pktcnt)
char	*pgname;
int	debuglevel;
char	*dstr;
unsigned char *pkt;
int	pktcnt;
{
	int 	stat;

	
	if(debuglevel <= 0) return(OK);
	fprintf(stderr,"Pkt no %d: %s : %s\n",pktcnt,pgname,dstr);
	if(debuglevel<-5) stat=Packet_Dump(pkt,pktcnt);
	return(OK);
}
