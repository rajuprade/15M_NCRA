/* Program to set GSB 5th LO using parallel port Apr 29,2005
   author - D. K. Nanaware 
*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/io.h>
#include <getopt.h>
#include <time.h>
#include <ctype.h>

#include "LoFsw.h"

unsigned int data=0x00;
unsigned int x=0x00;
unsigned int y=0x00;
unsigned int clk_h=0x01;
unsigned int clk_l=0x00;

int LoFsw(int FreqSet[ ])
{
  int c,i,synthNo;
  char* refFreq= NULL;
  int pattern(char,int,int);

/*
    if(argc==1) {
        fprintf(stderr,"HELP: lofsw synth1_Freq synth2_Freq\n" ); return 1;
    }
     FreqSet[0]=atoi(argv[1]);
     FreqSet[1]=atoi(argv[2]);
      
     if(FreqSet[0]<110000 || FreqSet[0]>240000) {
            fprintf(stderr,"Synth 1 Range is 110 MHz - 240 MHz\n"); exit(1);
     }   
     if(FreqSet[1]<110000 || FreqSet[1]>240000) {
              fprintf(stderr,"Synth 2 Range is 110 MHz - 240 MHz\n"); exit(1);
     }  
*/
       for(i=0;i<2;i++)
          if( pattern('K',FreqSet[i],i ) != 0 ) {
            fprintf(stderr, "\n### Error: LoFsw() : in Setting\n"); return 1 ; 
          } else { fprintf(stderr, "\n### LoFsw() : Successfully Set \n"); return 0 ; }
 } 


char* Binary(int num, int BinSize)
{
 int i;
 char bits[BinSize];
 bzero(bits,BinSize);
 for(i=BinSize-1;i>=0; --i){
    bits[i] = (num % 2 == 0 ? '0' : '1');
    num>>=1;
    //This is equal to num=num/2;
 }
   bits[BinSize]='\0';
  return bits;
}


/*  SetBit arguments: binary digits corresponding to freq. length of binary 
 *  number, synthesizer number. 
 *
 *
 *
 */  

int SetBit(int data[],int ref,int cnt)
{

        int len,dbit,portStatus;
        struct timespec ts;

      #ifdef DEBUG 
        fprintf(stderr,"cnt  %d %x %x \n",cnt,baseaddress,CONTROL);
      #endif

      portStatus=ioperm(baseaddress,3,1);//On success it returns zero
        if(portStatus<0) { fprintf(stderr,"Parallel Port Access denied %d",portStatus); return 1; }

        outb(0x00,CONTROL); //  strobe line goes high 
	outb(clk_l,baseaddress);
                //outb(en_h|clk_l,baseaddress);
        usleep(90);
        outb(0x01+cnt,CONTROL); //strobe low for 1st synth
        outb(clk_l,baseaddress);
	usleep(3);
        for(len=0;len<ref;len++)
                {
                        if(data[len]==48)
                                dbit=0x00;
                        else
                                dbit=0x02;

                        y=clk_l|dbit;
			outb(y,baseaddress);
                        usleep(1);
                        y=clk_h|dbit;
			outb(y,baseaddress);
                        usleep(2000);
                        y=clk_l|dbit;
			outb(y,baseaddress);
                        usleep(5);
                }
                ts.tv_sec=0;
                ts.tv_nsec=100;
                        nanosleep(&ts,NULL);
			outb(0x00,CONTROL); //Strobe goes high at the end.
                        outb(clk_l,baseaddress);
			usleep(2);
                	usleep(100);
              /* We don't need the ports anymore */
  if (ioperm(baseaddress, 3, 0)) {perror("ioperm"); return 1; }

  return 0 ;

}


int pattern(char P,int in,int count )  
// Char is M/K i.e mega or kilo, freq to be set synthesizer count. 
{                 
	   	  char str[15];
                  char *k;
                  unsigned int i,m,j=0;
                  int d,s;
                  int f[100];
                  int hex[2];
               

                    hex[0]=0x00;
                    hex[1]=0x10;
		//  here string is required
		//  in=in/1000;
                // fprintf(stderr,"\n Freq %d KHz ",in);
                if(in==0)  { fprintf(stderr,"Freq 0 can't set for synth %d ",++count);return 1; }
                    sprintf(str,"%C%08x",P,in);   
                 #ifdef DEBUG   
                     fprintf(stderr,"%s %d \n",str,strlen(str) ); 
	         #endif 
                 	
                 m=strlen(str);
                 //for(i=0;i<m;i++)
                 // fprintf(stderr,"%02x ",toupper(str[i]));
	        for(i=0;i<m;i++)
		{
                     k = Binary(str[i],8);                    
                      
                   #ifdef DEBUG
                     { 
                       fprintf(stderr,"str[%d] Hex :  %03d ==> ",i,str[i]);
                       fprintf(stderr,"binary string %s \n",k); 
                     }
                   #endif 	          
			for(s=0;s<8;++s)
                                {
                                        if(k!=NULL)
                                         {
			                        f[j]=k[s];
                                                j++;
                                         }

                                }

                    }

                  #ifdef DEBUG
                  {   d=7; 
                   for(i=0;i<72;++i)
                    {   
                      fprintf(stderr,"%c",f[i]);
                   
                      { if(i%d==0 && i!=0)
                        {
                         fprintf(stderr,"\n");
                         d=d+8;
                        }
                       } 
                    }
                  }  
                 #endif      
     return SetBit(f,72,count); //Here 72 is fixed for binary bit length.

}
