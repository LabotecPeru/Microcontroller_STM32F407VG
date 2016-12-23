#ifndef __UART__
#define __UART__

void init_USART1(uint32_t baudrate);
void USART_puts(USART_TypeDef* USARTx, volatile char *s);
void putcharx(USART_TypeDef* USARTx, uint16_t Data);
void USART_num(int_fast16_t num);
void init_ISR_USART(void);

char dato_recibido;

#endif
