
#ifndef __ADC__
#define __ADC__

#include "stm32f4xx_adc.h"

#define	CANAL0		ADC_Channel_0
#define	CANAL1		ADC_Channel_1
#define CANAL2		ADC_Channel_2
#define CANAL3		ADC_Channel_3
#define CANAL4		ADC_Channel_4
#define CANAL5		ADC_Channel_5
#define CANAL6		ADC_Channel_6
#define CANAL7		ADC_Channel_7
#define CANAL8		ADC_Channel_8
#define CANAL9		ADC_Channel_9
#define CANAL10		ADC_Channel_10
#define CANAL11		ADC_Channel_11
#define CANAL12		ADC_Channel_12
#define CANAL13		ADC_Channel_13
#define CANAL14		ADC_Channel_14
#define CANAL15		ADC_Channel_15
#define CANAL16		ADC_Channel_16
#define CANAL17		ADC_Channel_17
#define CANAL18		ADC_Channel_18


void init_adc_singlemode(void);
void init_ISR_ADC(void);
void init_adc_injectmode(void);
uint16_t read_ADC(ADC_TypeDef* ADCx, uint8_t channel);
void read_singlemode(void);
void read_injectmode(void);

int16_t ADC1canal[6];

#endif
