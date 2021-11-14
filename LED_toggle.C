#include<LPC214x.h>
void delay(unsigned int c);
void main()
{
   unsigned int i,val,sw0,sw1,x;
	
   PINSEL0=0x00000000;
   PINSEL1=0x00000000;
   PINSEL2=0x00000000;
   IODIR1=0XFFFFFFFF;

   while(1)
   {
   sw0= (IOPIN0&0X00008000);
   sw1= (IOPIN0&0X00010000);
   if(sw0==0)
   {
   	val=1;
   }
   if(sw1==0)
   {
   	val=2;
   }
   if(val==1)
   {
       
	   for(x=16;x<=23;x++)
	   {		
	   			//LED chase from Right to Left
	  	     	IOSET1=1<<x;
				delay(500);
				IOCLR1=1<<x;
				delay(500);
		}
	}
	if(val==2)
	{
	  for(x=23;x>=16;x--)
	   {		
	   			//LED chase from Left to Right
	   	     	IOSET1=1<<x;
				delay(500);
				IOCLR1=1<<x;
				delay(500);
		}
	}
  }			               
}
void delay(unsigned int c)
{
	int i,j;
	for(i=0;i<c;i++)
	{
		for(j=0;j<500;j++)
		{
		}
	}
}