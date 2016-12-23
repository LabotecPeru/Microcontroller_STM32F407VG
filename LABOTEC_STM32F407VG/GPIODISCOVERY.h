#ifndef __GPIODISCOVERY__
#define __GPIODISCOVERY__

#define VERDE	GPIO_Pin_12
#define NARANJA	GPIO_Pin_13
#define ROJO	GPIO_Pin_14
#define AZUL	GPIO_Pin_15
#define BOTON	GPIO_Pin_0

void init_DISCOVERYLed(void);
void init_DISCOVERYButton(void);
void LedHIGH(uint16_t GPIO_Pin);
void LedLOW(uint16_t GPIO_Pin);
uint8_t  ButtonREAD();

#endif
