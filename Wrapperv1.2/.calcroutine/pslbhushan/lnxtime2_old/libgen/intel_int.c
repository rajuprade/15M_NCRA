/*INFORMATION		routine 	int intel_int(uchar *a,
INFO					uint *loc,int flag)
INFO				
INFO			routine takes an intel long integer
INFO			from a[*loc] and returns a SUN integer
INFO			if flag=0	the pointer *loc is untouched
INFO			   flag=1	*loc is moved over the integer
INFO
*/

int intel_int(arr,loc,ptr_incr)
     unsigned char arr[];
     unsigned int *loc;
     int ptr_incr;
{
  union {
    int ii;
    unsigned char aa[4];
  }  tt;
  tt.aa[3]=arr[*loc];
  tt.aa[2]=arr[*loc+1];
  tt.aa[1]=arr[*loc+2];
  tt.aa[0]=arr[*loc+3];
  if(ptr_incr==1) *loc=*loc+4;
  return ((int)tt.ii);
}

