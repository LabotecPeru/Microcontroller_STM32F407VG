#include "spi.h"

uint8_t SPI_SendByte(uint8_t dato){

  uint8_t dato_recibido = 0;

  //	ESPERA A QUE LA TRANSMISION SE HA COMPLETADO
  while (SPI_I2S_GetFlagStatus(SPI2, SPI_I2S_FLAG_TXE) == RESET);

  //	BYTE ENVIADO
  SPI_I2S_SendData(SPI2, dato);

  //	ESPERA A QUE LA RECEPCION SE HA COMPLETADO
  while (SPI_I2S_GetFlagStatus(SPI2, SPI_I2S_FLAG_RXNE) == RESET);

  //	DATO RECIBIDO
  dato_recibido = SPI_I2S_ReceiveData( SPI2 );

  return( dato_recibido );
}

