#include "MPU6050_I2C.h"

// Set gyro_rate, accel_rate and gyro_div, accel_div will change accordingly
uint8_t gyro_rate = G_rate; 	// 0x00 = 250*/s ; 0x08 = 500*/s ; 0x10 = 1000*/s ; 0x18 = 2000*/s
uint8_t accel_rate = A_rate;	// 0x00 = 2g ; 0x08 = 4g ; 0x10 = 8g ; 0x18 = 16g
float gyro_div;						// 250*/s = 131 ; 500*/s = 65.5 ; 1000*/s = 32.8 ; 2000*/s = 16.4
float accel_div;					// 2g = 16384 ; 4g = 8192 ; 8g = 4096 ; 16g = 2048

void What_div()
{
	switch(gyro_rate)
	{
		case 0x00:
		{
			gyro_div=131.0;
			break;
		}
		case 0x08:
		{
			gyro_div=65.5;
			break;		
		}
		case 0x10:
		{
			gyro_div=32.8;
			break;		
		}
		case 0x18:
		{
			gyro_div=16.4;
			break;		
		}
	}

	switch(accel_rate)
	{
		case 0x00:
		{
			accel_div=16384.0;
			break;
		}
		case 0x08:
		{
			accel_div=8192.0;
			break;	
		}
		case 0x10:
		{
			accel_div=4096.0;
			break;
		}
		case 0x18:
		{
			accel_div=2048.0;
			break;
		}
	}
}


int MPU6050_Init(void)
{
	uint8_t check;
	HAL_I2C_Mem_Read(&i2c_port , MPU6050_ADDRESS<<1,MPU6050_REG_WHO_AM_I,1,&check,1,100);
	if (check==MPU6050_ADDRESS)
	{
		uint8_t init_data = 0x08; 	//Init (SLEEP=0, CYCLE=0, TEMP_DIS=1, CLKSEL=000)
		uint8_t div=7; 							//Sample Rate = Gyroscope Output Rate / (1 + div)
		
		HAL_I2C_Mem_Write(&i2c_port,MPU6050_ADDRESS<<1,MPU6050_REG_PWR_MGMT_1,1,&init_data,1,100);	// Wakeup device
		HAL_I2C_Mem_Write(&i2c_port,MPU6050_ADDRESS<<1,MPU6050_REG_SMPRT_DIV,1,&div,1,100);				// Set Sample rate
		
		// Set Gyroscope
		HAL_I2C_Mem_Write(&i2c_port,MPU6050_ADDRESS<<1,MPU6050_REG_GYRO_CONFIG,1,&gyro_rate,1,100);
		
		// Set Accelerometer
		HAL_I2C_Mem_Write(&i2c_port,MPU6050_ADDRESS<<1,MPU6050_REG_ACCEL_CONFIG,1,&accel_rate,1,100);
		What_div();
		return 1;
	}
	else
	{
		return 0;
	}
}

float MPU6050_Read_Accel_X()
{
	uint8_t accel_x_h, accel_x_l;
	int16_t Accel_x;
	float X_Accel;
	HAL_I2C_Mem_Read(&i2c_port , MPU6050_ADDRESS<<1,MPU6050_REG_ACCEL_XOUT_H,1,&accel_x_h,1,100);
	HAL_I2C_Mem_Read(&i2c_port , MPU6050_ADDRESS<<1,MPU6050_REG_ACCEL_XOUT_L,1,&accel_x_l,1,100);
	Accel_x =((accel_x_h<<8)|(accel_x_l));
	
	X_Accel = (Accel_x / accel_div); // 2g = 16384 ; 4g = 8192 ; 8g = 4096 ; 16g = 2048
	return X_Accel;
}

float MPU6050_Read_Accel_Y()
{
	uint8_t accel_y_h, accel_y_l;
	int16_t Accel_y;
	float Y_Accel;
	HAL_I2C_Mem_Read(&i2c_port , MPU6050_ADDRESS<<1,MPU6050_REG_ACCEL_YOUT_H,1,&accel_y_h,1,100);
	HAL_I2C_Mem_Read(&i2c_port , MPU6050_ADDRESS<<1,MPU6050_REG_ACCEL_YOUT_L,1,&accel_y_l,1,100);
	Accel_y = ((accel_y_h<<8)|(accel_y_l));
	
	Y_Accel = (Accel_y / accel_div); // 2g = 16384 ; 4g = 8192 ; 8g = 4096 ; 16g = 2048
	return Y_Accel;
}

float MPU6050_Read_Accel_Z()
{
	uint8_t accel_z_h, accel_z_l;
	int16_t Accel_z;
	float Z_Accel;
	HAL_I2C_Mem_Read(&i2c_port , MPU6050_ADDRESS<<1,MPU6050_REG_ACCEL_ZOUT_H,1,&accel_z_h,1,100);
	HAL_I2C_Mem_Read(&i2c_port , MPU6050_ADDRESS<<1,MPU6050_REG_ACCEL_ZOUT_L,1,&accel_z_l,1,100);
	Accel_z = ((accel_z_h<<8)|(accel_z_l));
	
	Z_Accel = (Accel_z / accel_div); // 2g = 16384 ; 4g = 8192 ; 8g = 4096 ; 16g = 2048
	return Z_Accel;
}

float MPU6050_Read_Gyro_X()
{
	uint8_t gyro_x_h, gyro_x_l;
	int16_t Gyro_x;
	float X_Gyro;
	HAL_I2C_Mem_Read(&i2c_port , MPU6050_ADDRESS<<1,MPU6050_REG_GYRO_XOUT_H,1,&gyro_x_h,1,100);
	HAL_I2C_Mem_Read(&i2c_port , MPU6050_ADDRESS<<1,MPU6050_REG_GYRO_XOUT_L,1,&gyro_x_l,1,100);
	Gyro_x = ((gyro_x_h<<8)|(gyro_x_l));
	
	X_Gyro = (Gyro_x / gyro_div); // 2g = 16384 ; 4g = 8192 ; 8g = 4096 ; 16g = 2048
	return X_Gyro;
}

float MPU6050_Read_Gyro_Y()
{
	uint8_t gyro_y_h, gyro_y_l;
	int16_t Gyro_y;
	float Y_Gyro;
	HAL_I2C_Mem_Read(&i2c_port , MPU6050_ADDRESS<<1,MPU6050_REG_GYRO_YOUT_H,1,&gyro_y_h,1,100);
	HAL_I2C_Mem_Read(&i2c_port , MPU6050_ADDRESS<<1,MPU6050_REG_GYRO_YOUT_L,1,&gyro_y_l,1,100);
	Gyro_y = ((gyro_y_h<<8)|(gyro_y_l));
	
	Y_Gyro = (Gyro_y / gyro_div); // 2g = 16384 ; 4g = 8192 ; 8g = 4096 ; 16g = 2048
	return Y_Gyro;
}

float MPU6050_Read_Gyro_Z()
{
	uint8_t gyro_z_h, gyro_z_l;
	int16_t Gyro_z;
	float Z_Gyro;
	HAL_I2C_Mem_Read(&i2c_port , MPU6050_ADDRESS<<1,MPU6050_REG_GYRO_ZOUT_H,1,&gyro_z_h,1,100);
	HAL_I2C_Mem_Read(&i2c_port , MPU6050_ADDRESS<<1,MPU6050_REG_GYRO_ZOUT_L,1,&gyro_z_l,1,100);
	Gyro_z = ((gyro_z_h<<8)|(gyro_z_l));
	
	Z_Gyro = (Gyro_z / gyro_div); // 2g = 16384 ; 4g = 8192 ; 8g = 4096 ; 16g = 2048
	return Z_Gyro;
}
