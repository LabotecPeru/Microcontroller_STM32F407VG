#include "adc.h"
#include "stm32f4xx_rcc.h"
#include "stm32f4xx_gpio.h"
#include "stm32f4xx_adc.h"

void init_adc_singlemode(void){
	ADC_InitTypeDef 		ADC_SETUP;
	GPIO_InitTypeDef 		PORTA;
	GPIO_InitTypeDef 		PORTB;
	ADC_CommonInitTypeDef   ADC_CommonInitStructure;

	// ENALED CLOCK ADC1
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1,ENABLE); // 0.3us
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC2,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC3,ENABLE);
	// ENABLED CLOCK GPIOA
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA,ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB,ENABLE);
	// PB0 - ADC1 CHANNEL8
	// PB1 - ADC1 CHANNEL9
	// PA4 - ADC2 CHANNEL4
	// PA5 - ADC2 CHANNEL5
	// PA2 - ADC3 CHANNEL2
	// PA3 - ADC3 CHANNEL3
	//----------------------	PORTA
	PORTA.GPIO_Pin   = GPIO_Pin_2 | GPIO_Pin_3| GPIO_Pin_4 | GPIO_Pin_5;
	PORTA.GPIO_Mode  = GPIO_Mode_AN;
	PORTA.GPIO_OType = GPIO_OType_PP;
	PORTA.GPIO_PuPd  = GPIO_PuPd_NOPULL;
	PORTA.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_Init(GPIOA,&PORTA);

	//----------------------	PORTB
	PORTB.GPIO_Pin   = GPIO_Pin_0 | GPIO_Pin_1;
	PORTB.GPIO_Mode  = GPIO_Mode_AN;
	PORTB.GPIO_OType = GPIO_OType_PP;
	PORTB.GPIO_PuPd  = GPIO_PuPd_NOPULL;
	PORTB.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_Init(GPIOB,&PORTB);

	// SELECCIONO ESE MODO PORQUE SOLO ESTOY TRABAJANDO CON EL CANAL A
	ADC_CommonInitStructure.ADC_Mode 	         = ADC_Mode_Independent;
	// DIVIDO LA FRECUENCIA APB2/2 = 42MHz
	ADC_CommonInitStructure.ADC_Prescaler 	     = ADC_Prescaler_Div2;
	// SIN ACCESO AL DMA
	ADC_CommonInitStructure.ADC_DMAAccessMode    = ADC_DMAAccessMode_Disabled;
	// DELAY PARA LA SIGUIENTE MUESTRA
	ADC_CommonInitStructure.ADC_TwoSamplingDelay = ADC_TwoSamplingDelay_5Cycles;
	ADC_CommonInit(&ADC_CommonInitStructure);

	//------------------------------------------------	ADC1
	//----------------------------------------------------------
	// ALINEO A LA DERECHA
	ADC_SETUP.ADC_DataAlign  		  	= ADC_DataAlign_Right;
	// RESOLUCION A 12 BITS
	ADC_SETUP.ADC_Resolution 		  	= ADC_Resolution_12b;
	// MODO CONTINUO HABILITADO
	ADC_SETUP.ADC_ContinuousConvMode 	= ENABLE;
	// SIN EVENTO EXTERNO
	ADC_SETUP.ADC_ExternalTrigConv   	= 0;
	// SIN FLANCO DE EVENTO EXTERNO
	ADC_SETUP.ADC_ExternalTrigConvEdge 	= ADC_ExternalTrigConvEdge_None;
	// NUMERO DE CONVERSIONES4
	ADC_SETUP.ADC_NbrOfConversion      	= 1;
	ADC_SETUP.ADC_ScanConvMode 			= DISABLE ; // modo multiCANAL
	ADC_Init(ADC1,&ADC_SETUP);
	// ENABLED ADC
	ADC_Cmd(ADC1,ENABLE);
}

uint16_t read_ADC(ADC_TypeDef* ADCx, uint8_t channel){
	ADC_RegularChannelConfig(ADCx, channel, 1, ADC_SampleTime_15Cycles);
	ADC_SoftwareStartConv(ADC1);
	while(ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC) == RESET);
	return ADC_GetConversionValue(ADC1);
}

void init_adc_injectmode(void){
	ADC_InitTypeDef ADC_SETUP;
	GPIO_InitTypeDef PORTA;
	GPIO_InitTypeDef PORTB;
	ADC_CommonInitTypeDef   ADC_CommonInitStructure;
	NVIC_InitTypeDef 		NVIC_InitStructure;

	// ENALED CLOCK ADC1
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC2,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC3,ENABLE);
	// ENABLED CLOCK GPIOA
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA,ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB,ENABLE);
	// PB0 - ADC1 CHANNEL8
	// PB1 - ADC1 CHANNEL9
	// PA4 - ADC2 CHANNEL4
	// PA5 - ADC2 CHANNEL5
	// PA2 - ADC3 CHANNEL2
	// PA3 - ADC3 CHANNEL3
	//----------------------	PORTA
	PORTA.GPIO_Pin   = GPIO_Pin_2 | GPIO_Pin_3| GPIO_Pin_4 | GPIO_Pin_5;
	PORTA.GPIO_Mode  = GPIO_Mode_AN;
	PORTA.GPIO_OType = GPIO_OType_PP;
	PORTA.GPIO_PuPd  = GPIO_PuPd_NOPULL;
	PORTA.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_Init(GPIOA,&PORTA);

	//----------------------	PORTB
	PORTB.GPIO_Pin   = GPIO_Pin_0 | GPIO_Pin_1;
	PORTB.GPIO_Mode  = GPIO_Mode_AN;
	PORTB.GPIO_OType = GPIO_OType_PP;
	PORTB.GPIO_PuPd  = GPIO_PuPd_NOPULL;
	PORTB.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_Init(GPIOB,&PORTB);


	// SELECCIONO ESE MODO PORQUE SOLO ESTOY TRABAJANDO CON EL CANAL A
	ADC_CommonInitStructure.ADC_Mode 	         = ADC_TripleMode_InjecSimult;
	// DIVIDO LA FRECUENCIA APB2/2 = 42MHz
	ADC_CommonInitStructure.ADC_Prescaler 	     = ADC_Prescaler_Div2;
	// SIN ACCESO AL DMA
	ADC_CommonInitStructure.ADC_DMAAccessMode    = ADC_DMAAccessMode_Disabled;
	// DELAY PARA LA SIGUIENTE MUESTRA
	ADC_CommonInitStructure.ADC_TwoSamplingDelay = ADC_TwoSamplingDelay_5Cycles;
	ADC_CommonInit(&ADC_CommonInitStructure);

	//------------------------------------------------	ADC1
	//----------------------------------------------------------
	// ALINEO A LA DERECHA
	ADC_SETUP.ADC_DataAlign  		  	= ADC_DataAlign_Right;
	// RESOLUCION A 12 BITS
	ADC_SETUP.ADC_Resolution 		  	= ADC_Resolution_12b;
	// MODO CONTINUO HABILITADO
	ADC_SETUP.ADC_ContinuousConvMode 	= ENABLE;
	// SIN EVENTO EXTERNO
	ADC_SETUP.ADC_ExternalTrigConv   	= 0;
	// SIN FLANCO DE EVENTO EXTERNO
	ADC_SETUP.ADC_ExternalTrigConvEdge 	= ADC_ExternalTrigConvEdge_None;
	// NUMERO DE CONVERSIONES4
	ADC_SETUP.ADC_NbrOfConversion      	= 2;
	ADC_SETUP.ADC_ScanConvMode 			= ENABLE;
	ADC_Init(ADC1,&ADC_SETUP);
	// ENABLED ADC
	ADC_Cmd(ADC1,ENABLE);

	//------------------------------------------------	ADC2
	//----------------------------------------------------------
	// ALINEO A LA DERECHA
	ADC_SETUP.ADC_DataAlign  		  	= ADC_DataAlign_Right;
	// RESOLUCION A 12 BITS
	ADC_SETUP.ADC_Resolution 		  	= ADC_Resolution_12b;
	// MODO CONTINUO HABILITADO
	ADC_SETUP.ADC_ContinuousConvMode 	= ENABLE;
	// SIN EVENTO EXTERNO
	ADC_SETUP.ADC_ExternalTrigConv   	= 0;
	// SIN FLANCO DE EVENTO EXTERNO
	ADC_SETUP.ADC_ExternalTrigConvEdge 	= ADC_ExternalTrigConvEdge_None;
	// NUMERO DE CONVERSIONES4
	ADC_SETUP.ADC_NbrOfConversion      	= 2;
	ADC_SETUP.ADC_ScanConvMode 			= ENABLE;
	ADC_Init(ADC2,&ADC_SETUP);
	// ENABLED ADC
	ADC_Cmd(ADC2,ENABLE);
	//------------------------------------------------	ADC3
	//----------------------------------------------------------
	// ALINEO A LA DERECHA
	ADC_SETUP.ADC_DataAlign  		  	= ADC_DataAlign_Right;
	// RESOLUCION A 12 BITS
	ADC_SETUP.ADC_Resolution 		  	= ADC_Resolution_12b;
	// MODO CONTINUO HABILITADO
	ADC_SETUP.ADC_ContinuousConvMode 	= ENABLE;
	// SIN EVENTO EXTERNO
	ADC_SETUP.ADC_ExternalTrigConv   	= 0;
	// SIN FLANCO DE EVENTO EXTERNO
	ADC_SETUP.ADC_ExternalTrigConvEdge 	= ADC_ExternalTrigConvEdge_None;
	// NUMERO DE CONVERSIONES4
	ADC_SETUP.ADC_NbrOfConversion      	= 2;
	ADC_SETUP.ADC_ScanConvMode 			= ENABLE;
	ADC_Init(ADC3,&ADC_SETUP);
	// ENABLED ADC
	ADC_Cmd(ADC3,ENABLE);

	//------------------------------------------------	HABILITAR INTERRUPT
	ADC_ITConfig(ADC1,ADC_IT_JEOC, ENABLE);
	ADC_ITConfig(ADC2,ADC_IT_JEOC, ENABLE);
	ADC_ITConfig(ADC3,ADC_IT_JEOC, ENABLE);
	//------------------------------------------------	MODO INJECT
	// LONGITUS DE LOS CANALES
	ADC_InjectedSequencerLengthConfig(ADC1, 2);	// CANTIDAD DE CANALES A LEER POR CADA ADC
	ADC_InjectedSequencerLengthConfig(ADC2, 2);
	ADC_InjectedSequencerLengthConfig(ADC3, 2);
	// SELECCION DE LOS CANALES
	ADC_InjectedChannelConfig(ADC1,ADC_Channel_8, 1,ADC_SampleTime_15Cycles);
	ADC_InjectedChannelConfig(ADC1,ADC_Channel_9, 2,ADC_SampleTime_15Cycles);

	ADC_InjectedChannelConfig(ADC2,ADC_Channel_4, 1,ADC_SampleTime_15Cycles);
	ADC_InjectedChannelConfig(ADC2,ADC_Channel_5, 2,ADC_SampleTime_15Cycles);

	ADC_InjectedChannelConfig(ADC3,ADC_Channel_2,1,ADC_SampleTime_15Cycles);
	ADC_InjectedChannelConfig(ADC3,ADC_Channel_3,2,ADC_SampleTime_15Cycles);

	ADC_SoftwareStartInjectedConv(ADC1);
	ADC_SoftwareStartInjectedConv(ADC2);
	ADC_SoftwareStartInjectedConv(ADC3);
	/* Configure and enable ADC interrupt */
	NVIC_InitStructure.NVIC_IRQChannel 					 = ADC_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority 		 = 0;
	NVIC_InitStructure.NVIC_IRQChannelCmd 				 = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
}

void init_ISR_ADC(void){
	NVIC_InitTypeDef 		NVIC_InitStructure;

	ADC_ITConfig(ADC1, ADC_IT_EOC, ENABLE);

	// SELECCION DEL CANAL - Canal8 - PB0
	ADC_RegularChannelConfig(ADC1,ADC_Channel_8,1,ADC_SampleTime_15Cycles);

	NVIC_InitStructure.NVIC_IRQChannel 					 = ADC_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority 		 = 0;
	NVIC_InitStructure.NVIC_IRQChannelCmd 				 = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
	// ENABLED ADC
	ADC_Cmd(ADC1,ENABLE);
	ADC_SoftwareStartConv(ADC1);
}

// FUNCION DE INTERRUPCION PARA EL ADC
void ADC_IRQHandler(void){
	//read_singlemode();
	read_injectmode();
}

void read_singlemode(void){
	ADC1canal[0] = ADC_GetConversionValue(ADC1);
}

void read_injectmode(void){
	if( ADC_GetITStatus(ADC3, ADC_IT_JEOC) == SET){
		ADC1canal[0] = ADC_GetInjectedConversionValue(ADC1,ADC_InjectedChannel_1);
		ADC1canal[1] = ADC_GetInjectedConversionValue(ADC1,ADC_InjectedChannel_2);

		ADC1canal[2] = ADC_GetInjectedConversionValue(ADC2,ADC_InjectedChannel_1);
		ADC1canal[3] = ADC_GetInjectedConversionValue(ADC2,ADC_InjectedChannel_2);

		ADC1canal[4] = ADC_GetInjectedConversionValue(ADC3,ADC_InjectedChannel_1);
		ADC1canal[5] = ADC_GetInjectedConversionValue(ADC3,ADC_InjectedChannel_2);

		ADC_ClearFlag(ADC1, ADC_FLAG_JEOC);
		ADC_ClearFlag(ADC2, ADC_FLAG_JEOC);
		ADC_ClearFlag(ADC3, ADC_FLAG_JEOC);

		ADC_SoftwareStartInjectedConv(ADC1);
		ADC_SoftwareStartInjectedConv(ADC2);
		ADC_SoftwareStartInjectedConv(ADC3);
	}
}
