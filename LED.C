#include<LPC214x.h>
void delay(int t);
int main()
{
  //All LED's blinking
  PINSEL1=0x00000000;
  IODIR0=0X00FF0000;
  while(1)
  {
    IOSET0=0x00FF0000;
    delay(500);
    IOCLR0=0x00FF0000;
    delay(500);
  }
  return(0);
}
void delay(int t)
{
  int i,j;
  for(i=0;i<t;i++)
	 {
	 	for(j=0;j<710;j++)
		{}
	}
}