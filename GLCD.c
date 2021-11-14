#include<LPC214X.H>
#define glcd_cs1_set IOSET1=0x01<27;
#define glcd_cs2_set IOSET1=0x01<28;
#define glcd_cs1_clr IOCLR1=0x01<27;
#define glcd_cs2_clr IOCLR1=0x01<28;
#define rs_cmd IOCLR1=0x1<<24;
#define rs_data IOSET1=0x1<<24;
#define write IOCLR1=0x1<<25;
#define en_high IOSET1=0x1<<26;
#define en_low IOCLR1=0x1<<26;
#define glcd_rst_set IOSET1=0x1<<29;
void glcd_init(void);
void glcd_clr(void);
void delay(unsigned int	t);
void glcd_cmd(unsigned char a);
void glcd_data(unsigned char a);
void page_col_select(unsigned char page,unsigned char col);


void delay(unsigned int t)
{
		unsigned int i,j;
		for(i=0;i<t;i++)
		{
			for(j=0;j<100;j++)
			{				
			}
		}
}
void glcd_cmd(unsigned char a)
{
	IOCLR1=0XFF<<16;
	rs_cmd;
	write;
	IOSET1=a<<16;
	en_high;
	delay(10);
	en_low;
	delay(10);
}

void glcd_data(unsigned char a)
{	
	IOCLR1=0xFF<<16;
	rs_data;
	write;
	IOSET1=a<<16;
	en_high;
	delay(10);
	en_low;
	delay(10);
}

void glcd_init()
{
	glcd_cs1_set;
	glcd_cs2_set;
	glcd_rst_set;
	glcd_cmd(0xB8);
	glcd_cmd(0x40);
		glcd_cmd(0x3F);
}

void page_col_select(unsigned char page,unsigned char col)
{
	if(col<64)
	{
		glcd_cs1_set;
		glcd_cs2_clr;
		glcd_cmd(0xB8|page);
		glcd_cmd(0x40|col);
	}
	else
	{
		glcd_cs1_clr;
		glcd_cs2_set;
		glcd_cmd(0xB8|page);
		glcd_cmd(0x40|col-64);
	}
}
void glcd_clr()
{
	unsigned int i,j;
	for(i=0;i<8;i++)
	{
		for(j=0;j<128;j++)
		{
			page_col_select(i,j);
			glcd_data(0x00);
		}
	}
}
int main()
{	unsigned int i,j;
	PINSEL2=0X00000000;
	IODIR1=0X3FFF<<16;
	glcd_init();
	glcd_clr();

	for(i=0;i<8;i++)
	{
		for(j=0;j<128;j++)
		{ 	   if(i==2 || i==6){
				page_col_select(i,j);
				glcd_data(0x0F); }
		}
	}
	return 0;
}
