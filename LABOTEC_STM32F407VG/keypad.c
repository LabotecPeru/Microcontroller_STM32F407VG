/*
 * keypad.c
 *
 *  Created on: 09/05/2013
 *      Author: AMANECER
 */
#include "stm32f4xx.h"
#include "stm32f4xx_rcc.h"	//	This file contains all the functions prototypes for the RCC firmware library.
#include "stm32f4xx_gpio.h"	//	This file contains all the functions prototypes for the GPIO firmware library.
#include "lcd.h"
#include "delay.h"
#include "keypad.h"

void Keypadinit(){
	// PC0 -PC1-PC2-PC3 - FILAS
	GPIO_InitTypeDef ROW_SETUP;
	GPIO_InitTypeDef COL_SETUP;
	RCC_AHB1PeriphClockCmd(CLOCKFILAS, ENABLE);
	ROW_SETUP.GPIO_Pin   = ROW1| ROW2|ROW3|ROW4;	//	SELECCIONAMOS EL PIN
	ROW_SETUP.GPIO_Mode  = GPIO_Mode_OUT;
	ROW_SETUP.GPIO_OType = GPIO_OType_PP;
	ROW_SETUP.GPIO_Speed = GPIO_Speed_100MHz;
	ROW_SETUP.GPIO_PuPd  = GPIO_PuPd_NOPULL;
	GPIO_Init(FILAS , &ROW_SETUP);

	// PA0 -PA1-PA2-PA3 - COLUMNAS
	RCC_AHB1PeriphClockCmd(CLOCKCOL, ENABLE);
	COL_SETUP.GPIO_Pin   = COL1 |COL2|COL3|COL4;
	COL_SETUP.GPIO_Mode  = GPIO_Mode_IN;
	COL_SETUP.GPIO_OType = GPIO_OType_PP;
	COL_SETUP.GPIO_Speed = GPIO_Speed_100MHz;
	COL_SETUP.GPIO_PuPd  = GPIO_PuPd_UP;
	GPIO_Init(COLUMNAS, &COL_SETUP);

}

char keypad(){
	char letras[4][4]={	{'1','2','3','A'},
				    {'4','5','6','B'},
				    {'7','8','9','C'},
				    {'*','0','+','D'}};
	int  i=0;
	char valor=0;


	for(i=0;i<4;i++){
		if(i==0){GPIO_SetBits(FILAS,ROW4|ROW3|ROW2);GPIO_ResetBits(FILAS,ROW1);
			Delay(10);
			while ((GPIO_ReadInputDataBit(COLUMNAS, COL1)) == 0){valor=letras[0][0];}	//1
			while ((GPIO_ReadInputDataBit(COLUMNAS, COL2)) == 0){valor=letras[0][1];}	//2
			while ((GPIO_ReadInputDataBit(COLUMNAS, COL3)) == 0){valor=letras[0][2];}	//3
			while ((GPIO_ReadInputDataBit(COLUMNAS, COL4)) == 0){valor=letras[0][3];}	//A
		}

		if(i==1){GPIO_SetBits(FILAS,ROW4|ROW3|ROW1);GPIO_ResetBits(FILAS,ROW2);
			Delay(10);
			while ((GPIO_ReadInputDataBit(COLUMNAS, COL1)) == 0){valor=letras[1][0];}	//4
			while ((GPIO_ReadInputDataBit(COLUMNAS, COL2)) == 0){valor=letras[1][1];}	//5
			while ((GPIO_ReadInputDataBit(COLUMNAS, COL3)) == 0){valor=letras[1][2];}	//6
			while ((GPIO_ReadInputDataBit(COLUMNAS, COL4)) == 0){valor=letras[1][3];}	//B
		}

		if(i==2){GPIO_SetBits(FILAS,ROW4|ROW2|ROW1);GPIO_ResetBits(FILAS,ROW3);
			Delay(10);
			while ((GPIO_ReadInputDataBit(COLUMNAS, COL1)) == 0){valor=letras[2][0];}	//7
			while ((GPIO_ReadInputDataBit(COLUMNAS, COL2)) == 0){valor=letras[2][1];}	//8
			while ((GPIO_ReadInputDataBit(COLUMNAS, COL3)) == 0){valor=letras[2][2];}	//9
			while ((GPIO_ReadInputDataBit(COLUMNAS, COL4)) == 0) {valor=letras[2][3];}	//C
		}

		if(i==3){GPIO_SetBits(FILAS,ROW3|ROW2|ROW1);GPIO_ResetBits(FILAS,ROW4);
			Delay(10);
			while ((GPIO_ReadInputDataBit(COLUMNAS, COL1)) == 0){valor=letras[3][0];}	//*
			while ((GPIO_ReadInputDataBit(COLUMNAS, COL2)) == 0){valor=letras[3][1];}	//0
			while ((GPIO_ReadInputDataBit(COLUMNAS, COL3)) == 0){valor=letras[3][2];}	//+
			while ((GPIO_ReadInputDataBit(COLUMNAS, COL4)) == 0){valor=letras[3][3];}	//D
		}
	}
	return valor;
}

