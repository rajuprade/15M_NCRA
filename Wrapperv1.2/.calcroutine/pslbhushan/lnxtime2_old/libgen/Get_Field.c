/* INFORMATION		routine		int Get_Field(uchar *aa,
INFO				int nfld,uchar *dest,int buflen,
INFO				uchar rcode,fldlen)
INFO			routine extracts the nfld field in a comma
INFO			separated uchar array aa, of length
INFO			buflen, and puts string at dest. rcode 
INFO			is the command code which called routine
INFO			for error reporting.
INFO			returns  OK if OK
INFO				 ERR if field longer than specified
INFO				 length fldlen, or hit end of buffer
INFO				 before geting reqd field
*/

/* Get_Field()
   This routine get required field from string */

#include <stdio.h>

#define OK 1
#define ERR 0

int Get_Field(aa,nfld,dest,buflen,rcode,fldlen)
	unsigned char 	*aa;
	int 		nfld;
	unsigned char 	*dest;
	int 		buflen;
	unsigned char   rcode;
	int             fldlen;
{
	int i,j,istart,iend;
	i=0;
	for (j=0;j<nfld;j++)
	{
		istart=i;
		while ( aa[i] != ','&& i<buflen)
		{
			i++;
			/*if( i == buflen) {
				fprintf(stderr," ovfl err in field %d, in servo rep code %x \n",
				    nfld,rcode);
				return(ERR);
			}*/
		}
		iend=i;
		i++;
	}
	j=0;
	i=istart;
	while ( i != iend && j < (fldlen-1) )
	{
		dest[j] = aa [i];
		i++;
		j++;
	}
	dest[j]=0;

	return(OK);
}

/*xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx*/
