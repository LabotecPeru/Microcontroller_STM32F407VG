//--------------------------------------------------------------
// File     : stm32_ub_spi2.h
//--------------------------------------------------------------

//--------------------------------------------------------------
#ifndef __SPI__
#define __SPI__

//--------------------------------------------------------------
// Includes
//--------------------------------------------------------------
#include "stm32f4xx.h"
#include "stm32f4xx_gpio.h"
#include "stm32f4xx_rcc.h"
#include "stm32f4xx_spi.h"

#define SPI2_VORTEILER     SPI_BaudRatePrescaler_64  // Frq = 656.2 kHz
uint8_t SPI_SendByte(uint8_t dato);

#endif
