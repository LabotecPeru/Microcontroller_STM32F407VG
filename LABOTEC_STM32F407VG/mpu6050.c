#include <stdio.h>
#include <stm32f4xx.h>
#include "stm32f4xx_rcc.h"
#include "stm32f4xx_gpio.h"
#include "stm32f4xx_i2c.h"
#include "i2c.h"
#include "mpu6050.h"

void init_mpu6050(void){

	I2C_start(I2C1, ( SLAVE_ADDRESS ) , I2C_Direction_Transmitter);
	I2C_write(I2C1, 0x6B);	//	REGISTRO Power Management 1 PWR_MGMT_1
	I2C_write(I2C1, 0x00);	//	CONFIGURACION POR DEFECTO
	I2C_stop(I2C1);
}

void mpu6050_read(void){
	int16_t  	gxH=0,gxL=0,gyH=0,gyL=0,gzH=0,gzL=0,TempH=0,TempL=0;
	int16_t acelx=0,acely=0,acelz=0,TempT=0;

	I2C_start(I2C1, SLAVE_ADDRESS, I2C_Direction_Transmitter);
	I2C_write(I2C1, 0x3B); 	//	ESCRIBE UN BYTE EN EL SLAVE
	I2C_stop(I2C1); 		// 	DETIENE LA TRANSMISION

	I2C_start(I2C1, SLAVE_ADDRESS, I2C_Direction_Receiver);
    gxH		=	I2C_read_ack(I2C1);
    gxL		=	I2C_read_ack(I2C1);
    gyH		=	I2C_read_ack(I2C1);
    gyL		=	I2C_read_ack(I2C1);
    gzH		=	I2C_read_ack(I2C1);
    gzL		=	I2C_read_ack(I2C1);
    TempH 	= 	I2C_read_ack(I2C1);
    TempL 	= 	I2C_read_nack(I2C1); // nack
    I2C_stop(I2C1);

    acelx= (gxH<<8)+gxL; 	// ACELERACION EN EL EJE X
    acely= (gyH<<8)+gyL; 	// ACELERACION EN EL EJE Y
    acelz= (gzH<<8)+gzL; 	// ACELERACION EN EL EJE Z
    TempT = ((TempH<<8)+TempL);

    printf("x:%f-y:%f-z:%f-Temp:%f\r\n",acelx/SENS,acely/SENS,acelz/SENS,(TempT/340.0) + 36.53);
}
