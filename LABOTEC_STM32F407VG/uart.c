#include "stm32f4xx_rcc.h"
#include "stm32f4xx_gpio.h"
#include "stm32f4xx_usart.h"
#include "uart.h"

void init_USART1(uint32_t baudrate){

	//	ESTRUCTURA PARA LA CONFIGURACION DEL GPIO
	GPIO_InitTypeDef GPIO_InitStruct;
	//	ESTRUCTURA PARA LA CONFIGURACION DEL USART
	USART_InitTypeDef USART_InitStruct;

	// HABILITAR CLOCK GPIOB
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);
	GPIO_InitStruct.GPIO_Pin   = GPIO_Pin_6 | GPIO_Pin_7; 		//	PB6 (TX) - PB7 (RX)
	GPIO_InitStruct.GPIO_Mode  = GPIO_Mode_AF;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStruct.GPIO_PuPd  = GPIO_PuPd_UP;
	GPIO_Init(GPIOB, &GPIO_InitStruct);

	// CONEXION MODO USART
	GPIO_PinAFConfig(GPIOB, GPIO_PinSource6, GPIO_AF_USART1); 	//	CONEXION PB6 A TX USART1
	GPIO_PinAFConfig(GPIOB, GPIO_PinSource7, GPIO_AF_USART1);	//	CONEXION PB7 A RX USART1

	//	HABILITAR CLOCK USART1
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);

	// CONFIGURACION DE LA ESTRUCTURA
	USART_InitStruct.USART_BaudRate 			= baudrate;							// BAUD
	USART_InitStruct.USART_WordLength 			= USART_WordLength_8b;				// LONGITUD DE DATOS
	USART_InitStruct.USART_StopBits 			= USART_StopBits_1;					// BIT DE STOP
	USART_InitStruct.USART_Parity 				= USART_Parity_No;					// BIT DE PARIDAD
	USART_InitStruct.USART_HardwareFlowControl 	= USART_HardwareFlowControl_None; 	// FLUJO DE CONTROL
	USART_InitStruct.USART_Mode 				= USART_Mode_Tx | USART_Mode_Rx; 	// HABILITAR TRANSMISION Y RECEPCION
	USART_Init(USART1, &USART_InitStruct);

	//	HABILITAR USART1
	USART_Cmd(USART1, ENABLE);
}

void init_ISR_USART(void){
	// HABILITAR INTERRUPCION POR RECIBO DE DATOS
	USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);
	// HABILITAR INTERRUPCION NVIC
	NVIC_EnableIRQ(USART1_IRQn);
}

//	FUNCION DE INTERRUPCION POR RECIBO DE DATOS
void USART1_IRQHandler(void){

	if( USART_GetITStatus(USART1, USART_IT_RXNE) ){
		dato_recibido = USART_ReceiveData(USART1);
	}
}


void USART_puts(USART_TypeDef* USARTx, volatile char *s){
	while(*s){
		putcharx(USARTx, *s);
		*s++;
	}
}

void putcharx(USART_TypeDef* USARTx, uint16_t Data){
	while (USART_GetFlagStatus(USARTx, USART_FLAG_TXE) == RESET);
	USART_SendData(USARTx, Data);
}

void USART_num(int_fast16_t num){ //Outputs string to LCD
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
	   putcharx(USART1, millares+48);
	   putcharx(USART1,centenas+48);
	   putcharx(USART1,decenas+48);
	   putcharx(USART1,unidades+48);
   }else{
	  if(centenas!= 0 ){
		  putcharx(USART1,centenas+48);
		  putcharx(USART1,decenas+48);
		  putcharx(USART1,unidades+48);
   	   }else{
   		   if(decenas != 0){
   			putcharx(USART1,decenas+48);
   			putcharx(USART1,unidades+48);
   		   }else{
   			putcharx(USART1,unidades+48);
   		   }
   	   }
   }
}
