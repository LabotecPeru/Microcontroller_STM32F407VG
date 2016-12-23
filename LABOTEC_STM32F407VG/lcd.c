#include <stm32f4xx.h>
#include "stm32f4xx_gpio.h"
#include "stm32f4xx_rcc.h"		 // I recommend you have a look at these in the ST firmware folder
#include "lcd.h"
#include "delay.h"

void init_ports(void){
	// PORTD
	GPIO_InitTypeDef GPIO_InitStruct;			//	DEFINIMOS LA ESTRUCTURA
	GPIO_InitTypeDef GPIO_InitStructB;

	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);

	GPIO_InitStruct.GPIO_Pin   = GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3;	//	SELECCIONAMOS EL PIN
	GPIO_InitStruct.GPIO_Mode  = GPIO_Mode_OUT;
	GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_25MHz;
	GPIO_InitStruct.GPIO_PuPd  = GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOD, &GPIO_InitStruct);

	// PORTB
	//PIO_InitTypeDef GPIO_InitStruct;			//	DEFINIMOS LA ESTRUCTURA
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);

	GPIO_InitStructB.GPIO_Pin   = GPIO_Pin_7|GPIO_Pin_6|GPIO_Pin_5|GPIO_Pin_4;	//	SELECCIONAMOS EL PIN
	GPIO_InitStructB.GPIO_Mode  = GPIO_Mode_OUT;
	GPIO_InitStructB.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructB.GPIO_Speed = GPIO_Speed_25MHz;
	GPIO_InitStructB.GPIO_PuPd  = GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOB, &GPIO_InitStructB);
}

void LCDsendChar(unsigned char ch){		//Sends Char to LCD
	//4 bit part
	hd44780_RS_On();
	//LDP=(ch&0b11110000);
	if ( ch & 0x10 ) {
		GPIO_SetBits( HD44780_DATAPORT, HD44780_DATABIT4 );
	} else {
		GPIO_ResetBits( HD44780_DATAPORT, HD44780_DATABIT4 );
	}
	if ( ch & 0x20 ) {
		GPIO_SetBits( HD44780_DATAPORT, HD44780_DATABIT5 );
	} else {
		GPIO_ResetBits( HD44780_DATAPORT, HD44780_DATABIT5 );
	}
	if ( ch & 0x40 ) {
		GPIO_SetBits( HD44780_DATAPORT, HD44780_DATABIT6 );
	} else {
		GPIO_ResetBits( HD44780_DATAPORT, HD44780_DATABIT6 );
	}
	if ( ch & 0x80 ) {
		GPIO_SetBits( HD44780_DATAPORT, HD44780_DATABIT7 );
	} else {
		GPIO_ResetBits( HD44780_DATAPORT, HD44780_DATABIT7 );
	}

	hd44780_EN_On();
	hd44780_EN_high_delay();
	hd44780_EN_Off();
	hd44780_init_end_delay();

	//LDP=((ch&0b00001111)<<4);
	if ( ch & 0x01 ) {
		GPIO_SetBits( HD44780_DATAPORT, HD44780_DATABIT4 );
	} else {
		GPIO_ResetBits( HD44780_DATAPORT, HD44780_DATABIT4 );
	}
	if ( ch & 0x02 ) {
		GPIO_SetBits( HD44780_DATAPORT, HD44780_DATABIT5 );
	} else {
		GPIO_ResetBits( HD44780_DATAPORT, HD44780_DATABIT5 );
	}
	if ( ch & 0x04 ) {
		GPIO_SetBits( HD44780_DATAPORT, HD44780_DATABIT6 );
	} else {
		GPIO_ResetBits( HD44780_DATAPORT, HD44780_DATABIT6 );
	}
	if ( ch & 0x08 ) {
		GPIO_SetBits( HD44780_DATAPORT, HD44780_DATABIT7 );
	} else {
		GPIO_ResetBits( HD44780_DATAPORT, HD44780_DATABIT7 );
	}

	hd44780_EN_On();//LCP = (1<<LCD_E)|(0<<LCD_RW) | (1<<LCD_RS);
	hd44780_EN_high_delay();
	hd44780_EN_Off();
	hd44780_init_end_delay(); //LCP = (0<<LCD_E)|(0<<LCD_RW) | (1<<LCD_RS);

}
void LCDsendCommand(unsigned char cmd){	//Sends Command to LCD

	hd44780_RS_Off();
	//LDP=(cmd&0b11110000);
	if ( cmd & 0x10 ) {
		GPIO_SetBits( HD44780_DATAPORT, HD44780_DATABIT4 );
	} else {
		GPIO_ResetBits( HD44780_DATAPORT, HD44780_DATABIT4 );
	}
	if ( cmd & 0x20 ) {
		GPIO_SetBits( HD44780_DATAPORT, HD44780_DATABIT5 );
	} else {
		GPIO_ResetBits( HD44780_DATAPORT, HD44780_DATABIT5 );
	}
	if ( cmd & 0x40 ) {
		GPIO_SetBits( HD44780_DATAPORT, HD44780_DATABIT6 );
	} else {
		GPIO_ResetBits( HD44780_DATAPORT, HD44780_DATABIT6 );
	}
	if ( cmd & 0x80 ) {
		GPIO_SetBits( HD44780_DATAPORT, HD44780_DATABIT7 );
	} else {
		GPIO_ResetBits( HD44780_DATAPORT, HD44780_DATABIT7 );
	}

	hd44780_EN_On();	//LCP = (1<<LCD_E)|(0<<LCD_RW) | (0<<LCD_RS);
	hd44780_EN_high_delay();
	hd44780_EN_Off();	//LCP = (0<<LCD_E)|(0<<LCD_RW) | (0<<LCD_RS);
	hd44780_init_end_delay();

	//LDP=((cmd&0b00001111)<<4);
	if ( cmd & 0x01 ) {
		GPIO_SetBits( HD44780_DATAPORT, HD44780_DATABIT4 );
	} else {
			GPIO_ResetBits( HD44780_DATAPORT, HD44780_DATABIT4 );
	}
	if ( cmd & 0x02 ) {
		GPIO_SetBits( HD44780_DATAPORT, HD44780_DATABIT5 );
	} else {
		GPIO_ResetBits( HD44780_DATAPORT, HD44780_DATABIT5 );
	}
	if ( cmd & 0x04 ) {
		GPIO_SetBits( HD44780_DATAPORT, HD44780_DATABIT6 );
	} else {
		GPIO_ResetBits( HD44780_DATAPORT, HD44780_DATABIT6 );
	}
	if ( cmd & 0x08 ) {
		GPIO_SetBits( HD44780_DATAPORT, HD44780_DATABIT7 );
	} else {
		GPIO_ResetBits( HD44780_DATAPORT, HD44780_DATABIT7 );
	}

	hd44780_EN_On();	//LCP = (1<<LCD_E)|(0<<LCD_RW) | (0<<LCD_RS);
	hd44780_EN_high_delay();
	hd44780_EN_Off();	//LCP = (0<<LCD_E)|(0<<LCD_RW) | (0<<LCD_RS);
	hd44780_init_end_delay();

}
/*
 *	FUNCIONES PARA INICIALIZAR EL LCD
 * */
void LCDinit(void){
	init_ports();
	//4 bit part
	hd44780_EN_Off();
	hd44780_RS_Off();
	hd44780_RW_Off();
	Delay(15);
	hd44780_wr_hi_nibble( HD44780_CMD_RESET );
	Delay(5);//hd44780_init_delay2();
	hd44780_wr_hi_nibble( HD44780_CMD_RESET );
	Delay(1);//hd44780_init_delay3();
	hd44780_wr_hi_nibble( HD44780_CMD_RESET );
	hd44780_wr_hi_nibble( HD44780_CMD_RESETX );
	//--------4 bit--dual line--5x8 dots---------------
	LCDsendCommand(SETLCD_4BITS_2LINE);
   //-----increment address, invisible cursor shift------
	LCDsendCommand(DISPLAY_ON_D_OFF_CB);
	//----Clear display
	LCDsendCommand(CLEAR_DISPLAY);

}

void LCDstring(unsigned char* data, unsigned char nBytes){	//Outputs string to LCD
	register unsigned char i=0;

	for(i=0; i<nBytes; i++){	// print data
		LCDsendChar(data[i]);
	}
}

void LCDGotoXY(unsigned char x, unsigned char y){		//Cursor to X Y position
	register uint8_t DDRAMAddr;

	switch(y){		// remap lines into proper order
	case 0: DDRAMAddr = LCD_LINE0_DDRAMADDR+x; break;
	case 1: DDRAMAddr = LCD_LINE1_DDRAMADDR+x; break;
	case 2: DDRAMAddr = LCD_LINE2_DDRAMADDR+x; break;
	case 3: DDRAMAddr = LCD_LINE3_DDRAMADDR+x; break;
	default: DDRAMAddr =LCD_LINE0_DDRAMADDR+x;break;
	}
	LCDsendCommand(1<<LCD_DDRAM|DDRAMAddr);	// set data address
}

//  Funcion para escribir en la CGRAM
 //	DATASHEET HD44780U (LCD-II) (Dot Matrix Liquid Crystal Display Controller/Driver)
 //	page 19.
 //
void LCDdefinechar(unsigned char *car,unsigned char CGRAM_dir){
	uint8_t i=0,a=0;
	a=(CGRAM_dir<<3)|(1<<LCD_CGRAM);		//	posiciona en la CGRAM address
	for(i=0;i<8;i++){
		LCDsendCommand(a++);			//	incrementa la direccion para la data
		LCDsendChar(car[i]);			//	escribe caracter
	}
}

void LCDsend_var(int16_t num){ //Outputs string to LCD
   int8_t millares=0,centenas = 0, decenas = 0, unidades = 0;

   while (num >= 1000){
	   num-=1000;millares++;
   }
   while (num >= 100){
      num-=100;centenas++;
   }
   while (num >= 10) {
      num-=10;decenas++;
   }
   unidades = num;
   if(millares!= 0 ){
	   LCDsendChar(millares+48);LCDsendChar(centenas+48);
   	   LCDsendChar(decenas+48);LCDsendChar(unidades+48);
   }else{
	   if(centenas!= 0 ){
		   LCDsendChar(0+48);
		   //
		   LCDsendChar(centenas+48);LCDsendChar(decenas+48);
		   LCDsendChar(unidades+48);
	   }else{
		   if(decenas != 0){
			   LCDsendChar(0+48);LCDsendChar(0+48);
			   //
			   LCDsendChar(decenas+48);LCDsendChar(unidades+48);
		   }else{
			   LCDsendChar(0+48);LCDsendChar(0+48);
			   LCDsendChar(0+48);
			   //
			   LCDsendChar(unidades+48);
		   }
	   }
   }
}

void hd44780_wr_hi_nibble( unsigned char data )
{
	if ( data & 0x10 ) {
		GPIO_SetBits( HD44780_DATAPORT, HD44780_DATABIT4 );
	} else {
		GPIO_ResetBits( HD44780_DATAPORT, HD44780_DATABIT4 );
	}
	if ( data & 0x20 ) {
		GPIO_SetBits( HD44780_DATAPORT, HD44780_DATABIT5 );
	} else {
		GPIO_ResetBits( HD44780_DATAPORT, HD44780_DATABIT5 );
	}
	if ( data & 0x40 ) {
		GPIO_SetBits( HD44780_DATAPORT, HD44780_DATABIT6 );
	} else {
		GPIO_ResetBits( HD44780_DATAPORT, HD44780_DATABIT6 );
	}
	if ( data & 0x80 ) {
		GPIO_SetBits( HD44780_DATAPORT, HD44780_DATABIT7 );
	} else {
		GPIO_ResetBits( HD44780_DATAPORT, HD44780_DATABIT7 );
	}

    /* set the EN signal */
    hd44780_EN_On();
    /* wait */
    hd44780_EN_high_delay();
    /* reset the EN signal */
    hd44780_EN_Off();
}

void hd44780_Delay(unsigned long del){
	unsigned long i=0;
	while(i<del)
		i++;
}
