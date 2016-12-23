#include <stm32f4xx.h>
#include "stm32f4xx_gpio.h"
#include "stm32f4xx_rcc.h"		 // I recommend you have a look at these in the ST firmware folder
#include "GPIODISCOVERY.h"

void init_DISCOVERYLed(void){
	GPIO_InitTypeDef PORTD;

	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);
	PORTD.GPIO_Pin 	 = VERDE | NARANJA | ROJO | AZUL;
	PORTD.GPIO_Mode  = GPIO_Mode_OUT;
	PORTD.GPIO_OType = GPIO_OType_PP;
	PORTD.GPIO_Speed = GPIO_Speed_100MHz;
	PORTD.GPIO_PuPd  = GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOD,&PORTD);

}

void init_DISCOVERYButton(void){
	GPIO_InitTypeDef PORTA;
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
	PORTA.GPIO_Pin 	 = BOTON;
	PORTA.GPIO_Mode  = GPIO_Mode_IN;
	PORTA.GPIO_OType = GPIO_OType_PP;
	PORTA.GPIO_Speed = GPIO_Speed_100MHz;
	PORTA.GPIO_PuPd  = GPIO_PuPd_DOWN;
	GPIO_Init(GPIOA,&PORTA);
}

void LedHIGH(uint16_t GPIO_Pin)	{	GPIOD->BSRRL = GPIO_Pin;	}
void LedLOW(uint16_t GPIO_Pin)	{	GPIOD->BSRRH = GPIO_Pin;	}

uint8_t  ButtonREAD(){
	uint8_t state;
	state = GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_0);
	return state;
}
