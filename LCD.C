#include<LPC21XX.h>
void LCD_Init(void);
void LCD_write_string(unsigned char* str);
void LCD_CMD(unsigned char a);
void LCD_Data(unsigned char d);
void Msdelay(unsigned int k);
int main()
{
	unsigned char var1[]="WELCOME TO";
	unsigned char var2[]="PICT";
	PINSEL1=0X00000000;
	PINSEL2=0X00000000;
	IODIR0=0XFF<<16;
	IODIR1=0X07<<16;
	LCD_Init();
	LCD_write_string(var1);
	Msdelay(10);
	LCD_CMD(0xC0);
	LCD_write_string(var2);
	
}
void LCD_Init(void)
{
	LCD_CMD(0x38);
	Msdelay(10);
	LCD_CMD(0x01);
	Msdelay(10);
	LCD_CMD(0x0C);
	Msdelay(10);
	LCD_CMD(0x06);
	Msdelay(10);
	LCD_CMD(0x80);
	Msdelay(10);
}
void LCD_write_string(unsigned char str[])
{
	int i=0;
	while(str[i]!='\0')
	{
		LCD_Data(str[i]);
		Msdelay(10);
		i=i+1;
	}
}
void LCD_CMD(unsigned char a)
{
	IOCLR0=0XFF<<16;
	IOCLR1=0X01<<16;
	IOCLR1=0X01<<17;
	IOSET0=a<<16;
	IOSET1=0X01<<18;
	Msdelay(10);
	IOCLR1=0X01<<18;
}
void LCD_Data(unsigned char d)
{
	IOCLR0=0XFF<<16;
	IOSET1=0X01<<16;
	IOCLR1=0X01<<17;
	IOSET0=d<<16;
	IOSET1=0X01<<18;
	Msdelay(10);
	IOCLR1=0X01<<18;
}
void Msdelay(unsigned int k)
{
	unsigned int i,j;
	for(i=0;i<3000;i++)
	{
		for(j=0;j<k;j++)
		{
		}
	} 
} 