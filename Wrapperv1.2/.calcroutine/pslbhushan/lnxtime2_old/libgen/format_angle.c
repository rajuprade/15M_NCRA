/*INFORMATION		routine   	void format_angle(int ang, 
INFO					char *ptr, int flag)
INFO		 	routine takes an integer ang in seconds
INFO			and converts to a string of form +ddd:mm:ss
INFO			if flag=1 the +/- sign is written
INFO			   flag=0, the sign is omitted ( for time)
INFO			The formated string is put in ptr
INFO
*/
void format_angle(lnewtime,ptr,symbol)
     int lnewtime;
     char *ptr;
     int symbol;
{
  int h,m,s;
  char atime[12];
  char signsymbol;
  
  signsymbol=32;  /* blank */
  if(symbol==1)signsymbol=43; /* plus +*/
  if (lnewtime < 0 )
    {
      lnewtime=abs(lnewtime);
      signsymbol=45; /* minus - */
    }
  h=lnewtime/3600;
  m=(lnewtime-(h*3600))/60;
  s=(lnewtime-(h*3600)-(m*60));
  sprintf(atime,"%c%03d:%02d:%02d",signsymbol,h,m,s);
  strcpy(ptr,atime);
}
