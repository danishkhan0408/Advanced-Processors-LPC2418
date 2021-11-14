#include<LPC214x.h>
void UART_init()
{
	U0LCR=0x83;
	U0DLL=0x61;
	U0DLM=0x00;
	U0LCR=0x03;
}

void Tx_byte(unsigned char c)
{
	while(!(U0LSR&0x40));
	U0THR=c;
}
void Tx_string(unsigned char *str)
{
	unsigned int i=0;
	while(str[i]!='\0')
	{
		Tx_byte(str[i]);
		i++;
	}
}

unsigned char Rx_byte()
{
	while(!(U0LSR&0x01));
	return U0RBR;
}

int main()
{
	unsigned char str1[]={"\r\nWelcome\r\n"};
	unsigned char str2[]={"\r\nPICT\r\n"};
	unsigned char Rx[20];
	unsigned char a;
	unsigned int i=0;
	PINSEL0=0x00000005;
	UART_init();
    
	Tx_byte('A');	

	Tx_string(str1);
    Tx_string(str2);

	for(i=0;i<10;i++)
	{
		Rx[i] = Rx_byte();
	}
	Rx[10]='\0';

	

}

