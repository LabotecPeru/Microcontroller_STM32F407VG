#include "stm32f4xx.h"

extern __IO uint32_t TimmingDelay;

void Delayinit(){
	SysTick_Config(SystemCoreClock/1000);
}

void Delay(__IO uint32_t time)
{
  TimmingDelay = time;
  while(TimmingDelay !=0);
}

__IO uint32_t TimmingDelay;
void SysTick_Handler(void)
{
  if(TimmingDelay !=0)
  {
    TimmingDelay --;
   }
}
