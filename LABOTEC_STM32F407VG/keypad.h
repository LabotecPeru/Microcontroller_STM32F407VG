/*
 * keypad.h
 *
 *  Created on: 09/05/2013
 *      Author: AMANECER
 */

#ifndef KEYPAD_H_
#define KEYPAD_H_

//----- CONFIGURACION
#define  CLOCKFILAS RCC_AHB1Periph_GPIOE
#define  FILAS 		GPIOE
#define  ROW1  		GPIO_Pin_7
#define  ROW2  		GPIO_Pin_8
#define  ROW3  		GPIO_Pin_9
#define  ROW4  		GPIO_Pin_10

#define  CLOCKCOL	RCC_AHB1Periph_GPIOE
#define  COLUMNAS	GPIOE
#define  COL1  		GPIO_Pin_11
#define  COL2  		GPIO_Pin_12
#define  COL3  		GPIO_Pin_13
#define  COL4  		GPIO_Pin_14



void Keypadinit(void);
char keypad();

#endif /* KEYPAD_H_ */
