#ifndef __MPU6050__
#define __MPU6050__

#define SLAVE_ADDRESS	0xD0 	// DIRECCION DEL ESCLAVO 68 << 1 -> D0
#define SENS 16384.0

void init_mpu6050(void);
void mpu6050_read(void);

#endif
