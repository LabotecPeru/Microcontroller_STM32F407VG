#ifndef __DAC__
#define __DAC__

#include "stm32f4xx_dac.h"

void init_dac(void);
void set_DAC1( uint16_t i );
void set_DAC2( uint16_t i );

#endif
