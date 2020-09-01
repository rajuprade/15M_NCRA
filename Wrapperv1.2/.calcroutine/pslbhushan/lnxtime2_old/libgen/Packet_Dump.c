/*INFORMATION		routine	      int Packet_Dump(uchar *ptr,int id)
INFO			routinr dumps a packet *ptr with id=id onto
INFO			disperr in hex format. disperr is external and
INFO			assumed to exist when the routine is called.
INFO			The first 2 bytes of the packet are assumed
INFO			to be the length in intel form.
INFO			packets longer than 512 are truncated to 512.
INFO
INFO			routine retuens ERR if file does not exist
*/

#include  <stdio.h>
#define OK 1
#define ERR 0

int Packet_Dump(ptr,pkt_id)
unsigned char *ptr;
int pkt_id;
{
	int 	j;
	int	psize;
	int 	charnum=0;
	int	stat;
	extern  FILE	*disperr;

	if(psize>512) psize=512;
	stat=fprintf(disperr,"error packet id no %d \n",pkt_id);
	if(stat != EOF) {
	  for (j=0; j< psize; j++) 
	  {	
		fprintf(disperr,"%2.2x ",ptr[j]);
		charnum++;
		if (charnum == 20) 
		{
		fprintf(disperr,"\n");
		charnum=0;
		}
	  }
	  fprintf(disperr,"\n");
	  return(OK);
        }
	else {
	   fprintf(stderr," Packet_Dump : pkt_id no %d : error writing dump data\n"
	    				 ,pkt_id);
           return(ERR);
	}
}
	


