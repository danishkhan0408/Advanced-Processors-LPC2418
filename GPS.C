 #include <lpc214x.h> 

#define RS (1<<16)

#define RW (1<<17)

#define E (1<<18)

void LCD_command(unsigned char command);

void delay_ms(unsigned char time);

void LCD_data(unsigned char data);

void LCD_write_string(unsigned char *string);

void LCD_init() ;

void uart1Init();

unsigned char uart1Getch();



int main(void)

{ unsigned char string1[] = "GPGGA";

   unsigned char i, flag=0;
 unsigned char cmd_data[5], time_data[15], latitude[15], longitude[15];
    IODIR1= 0x07<<16; //Configure P1.18, P1.17, P1.16 as output
    IODIR0= 0xFF<<16;  //Configure P0.23 - P0.16 as output
    LCD_init();    //Initialize LCD 16x2
    LCD_command(0x01); 
  uart1Init(); 
  LCD_write_string("Welcome to PICT");
  LCD_command(0xc0);  //second line 1st position
  LCD_write_string("PUNE");
  delay_ms(1000) ;

 while(1)
 {
 if(uart1Getch()=='$')
  {
   for (i=0; i<5; i++)
   { 
   flag=0;
   cmd_data[i]=uart1Getch();
   if (cmd_data[i]!= string1[i])
    {
     flag = 1;
     break;
    }
   }
   if (flag == 0)										  
   {
   for (i=0; i<12; i++)
   { 
    time_data[i]=uart1Getch();
   } 
   time_data[12]='\0';
   
   for (i=0; i<12; i++)
   { 
    latitude[i]=uart1Getch();
   }
   latitude[11]='\0';
   
   for (i=0; i<12; i++)
   { 
    longitude[i]=uart1Getch();
   }
   longitude[12]='\0';
   LCD_command(0x01);
   LCD_write_string("GPS sent:");
   LCD_write_string(cmd_data);
   LCD_command(0xC0);
   LCD_write_string("UTC:");
   LCD_write_string(time_data);
   delay_ms(2000);
   LCD_command(0x01);
   LCD_write_string("Lt:");
   LCD_write_string(latitude);
   LCD_command(0xC0);
   LCD_write_string("Ln:");
   LCD_write_string(longitude);
   delay_ms(1000);
   }
  }
 }   
}
//Function to generate software delay
//Calibrated to 1ms
void  delay_ms(unsigned char time)    
{  
 unsigned int  i, j;
 for (j=0; j<time; j++)
 {
  for(i=0; i<8002; i++)
  {
  }
}
}

void LCD_command(unsigned char command)
{
 IOCLR0 = 0xFF<<16; // Clear LCD Data lines
 IOCLR1=RS;     // RS=0 for command
 IOCLR1=RW;     // RW=0 for write
 IOSET0=command<<16; // put command on data line
 IOSET1=E;   // en=1 
 delay_ms(10) ;   // delay
 IOCLR1=E;    // en=0
}

void LCD_data(unsigned char data)
{
 IOCLR0 = 0xFF<<16; // Clear LCD Data lines
 IOSET1=RS;     // RS=1 for data
 IOCLR1=RW;     // RW=0 for write
 IOSET0= data<<16;  // put command on data line
 IOSET1=E;   //en=1 
 delay_ms(10) ;    //delay
 IOCLR1=E;   //en=0
 }

void LCD_init()
{
 LCD_command(0x38); //8bit mode and 5x8 dotes (function set)
 delay_ms(10) ;   // delay
 LCD_command(0x0c); //display on, cursor off, cursor char blinking off(display on/off)
 delay_ms(10) ;   // delay
 LCD_command(0x0e);  //cursor increment and display shift(entry mode set)
 delay_ms(10) ;   // delay
 LCD_command(0x01);  //clear lcd (clear command)
 delay_ms(10) ;   // delay
 LCD_command(0x80); 
 delay_ms(10) ;//set cursor to 0th location 1st lne
}
void LCD_write_string(unsigned char *string)
{
int i=0;
  while(string[i]!='\0')//Check for End of String
  {   
  LCD_data(string[i]);
  i=i+1;  
}
}
void uart1Init(void)      
{
    PINSEL0=0x00050005;// port 0 tx P0.1 and rx P0.0 selected
    U1LCR=0x83; //8bit data, no parity, 1 stop bit
    U1DLL=97;// 9600 baud rate @15Mhz Pclk
    U1LCR=0x03;// DLAB=0
}

unsigned char uart1Getch(void)
{
    while(!(U1LSR & 0x01)); //RDR=0 then FIFO is empty then only this will rx character
    return(U1RBR);  // return this data
}
	
