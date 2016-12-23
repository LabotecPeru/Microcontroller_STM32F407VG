#include "dac.h"
#include "stm32f4xx_rcc.h"
#include "stm32f4xx_gpio.h"
#include "stm32f4xx_dac.h"

void init_dac(void){

	GPIO_InitTypeDef GPIO_InitStructure;
	DAC_InitTypeDef  DAC_InitStructure;

	// HABILITAR CLOCK GPIOA
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
	// HABILITAR CLOCK DAC
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_DAC, ENABLE);

	//	CANAL1 = PA.4
	//	CANAL2 = PA.5
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4 | GPIO_Pin_5;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AN;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOA, &GPIO_InitStructure);

	//-----------------------------------------------------------------
    //-----	CONFIGURACION DAC CANAL1
	//-----------------------------------------------------------------
    DAC_InitStructure.DAC_Trigger 			= DAC_Trigger_None;
    DAC_InitStructure.DAC_WaveGeneration 	= DAC_WaveGeneration_None;
    DAC_InitStructure.DAC_OutputBuffer 		= DAC_OutputBuffer_Enable;
    DAC_Init(DAC_Channel_1, &DAC_InitStructure);
    // HABILITO DAC CANAL 1
    DAC_Cmd(DAC_Channel_1, ENABLE);
    // SETEAR DAC1 A NIVEL 4000
    DAC_SetChannel1Data(DAC_Align_12b_R, 4000);

    //-----------------------------------------------------------------
    //-----	CONFIGURACION DAC CANAL2
    //-----------------------------------------------------------------
    DAC_InitStructure.DAC_Trigger 			= DAC_Trigger_None;
    DAC_InitStructure.DAC_WaveGeneration 	= DAC_WaveGeneration_None;
    DAC_InitStructure.DAC_OutputBuffer 		= DAC_OutputBuffer_Enable;
    DAC_Init(DAC_Channel_2, &DAC_InitStructure);
    // HABILITO DAC CANAL 2
    DAC_Cmd(DAC_Channel_2, ENABLE);
    // SETEAR DAC2 A NIVEL 4000
    DAC_SetChannel2Data(DAC_Align_12b_R, 4000);
}

void set_DAC1( uint16_t i ){
	DAC_SetChannel1Data(DAC_Align_12b_R,i);
}

void set_DAC2( uint16_t i ){
	DAC_SetChannel2Data(DAC_Align_12b_R,i);
}
