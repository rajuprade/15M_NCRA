/*INFORMATION		routine 	int intel_short(uchar *a,
INFO					uint *loc,int flag)
INFO				
INFO			routine takes an unsigned (short) intel integer
INFO			from a[*loc] and returns a SUN integer
INFO			if flag=0	the pointer *loc is untouched
INFO			   flag=1	*loc is moved over the integer
INFO
*/

int intel_short(arr,loc,ptr_incr)
     unsigned char arr[];
     unsigned int *loc;
     int ptr_incr;
{
  union  {
    unsigned short ii;
    unsigned char aa[2];
  }  tt;
  tt.aa[1]=arr[*loc];
  tt.aa[0]=arr[*loc+1];
  if(ptr_incr==1) *loc=*loc+2;
  return( (int) tt.ii);
}
