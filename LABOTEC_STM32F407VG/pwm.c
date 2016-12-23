#include "stm32f4xx_gpio.h"
#include <stm32f4xx_rcc.h>
#include "stm32f4xx_tim.h"
#include "pwm.h"

void init_pwm(void){
	GPIO_InitTypeDef 		GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef	SETUPTIMER;
	TIM_OCInitTypeDef		SETUPPWM;

	// ENABLED CLOCK GPIOD
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);

	// CONFIGURACION DEL GPIO
	GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_12|GPIO_Pin_13|GPIO_Pin_14|GPIO_Pin_15;
	GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_AF;	// CONFIGURACION AF
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOD, &GPIO_InitStructure);

	// CONEXION DEL GPIO CON LOS PINES PARA PWM
	GPIO_PinAFConfig(GPIOD, GPIO_PinSource12, GPIO_AF_TIM4);
	GPIO_PinAFConfig(GPIOD, GPIO_PinSource13, GPIO_AF_TIM4);
	GPIO_PinAFConfig(GPIOD, GPIO_PinSource14, GPIO_AF_TIM4);
	GPIO_PinAFConfig(GPIOD, GPIO_PinSource15, GPIO_AF_TIM4);

	//	ENABLED CLOCK TIMER4
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4,ENABLE);
	//	CONFIGURACION DEL TIMER4
	// 	F = FAPB1/(PRESCALER + 1)(PERIODO + 1) = 1KHZ
	//  f = 84mHZ/(2000)(42) = 1KHZ
	SETUPTIMER.TIM_Period	 	 = 2000 -1;
	SETUPTIMER.TIM_Prescaler 	 = 42 - 1;
	SETUPTIMER.TIM_ClockDivision = 0;
	SETUPTIMER.TIM_CounterMode	 = TIM_CounterMode_Up;
	TIM_TimeBaseInit(TIM4,&SETUPTIMER);

	// CONFIGURACION DEL PWM
	SETUPPWM.TIM_OCMode 	 = TIM_OCMode_PWM1;
	SETUPPWM.TIM_OutputState = TIM_OutputState_Enable;
	SETUPPWM.TIM_Pulse 		 = 100;
	SETUPPWM.TIM_OCPolarity  = TIM_OCPolarity_High;
	TIM_OC1Init(TIM4,&SETUPPWM);
	// CONFIGURACION PARA EL CANAL2
	TIM_OC2Init(TIM4,&SETUPPWM);
	// CONFIGURACION DEL CANAL3
	TIM_OC3Init(TIM4,&SETUPPWM);
	// CONFIGURACION DEL CANAL4
	TIM_OC4Init(TIM4,&SETUPPWM);

	// HABILITAR TIMER4
	TIM_Cmd(TIM4,ENABLE);

}

void duty_cycle1(uint16_t duty){	TIM_SetCompare1(TIM4, duty);	}
void duty_cycle2(uint16_t duty){	TIM_SetCompare2(TIM4, duty);	}
void duty_cycle3(uint16_t duty){	TIM_SetCompare3(TIM4, duty);	}
void duty_cycle4(uint16_t duty){	TIM_SetCompare4(TIM4, duty);	}


