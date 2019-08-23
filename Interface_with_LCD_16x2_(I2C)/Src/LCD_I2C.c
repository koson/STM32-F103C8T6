#include "LCD_I2C.h"
#include <stdio.h>

// rw=0 <=> write mode
// rw=1 <=> read mode
// rs=0 <=> command mode
// rs=1 <=> data mode
// en=1 then en=0 to lacth (HIGH-to-LOW pulse)



void LCD_SendCmd(uint8_t command)
{
	uint8_t data[4], u_data, l_data;
	
	u_data = command & 0xF0;
	l_data = (command << 4) & 0xF0 ;
	data[0] = u_data | 0x0C ;	// led, en, rw, rs = 1100 = 0x0C
	data[1] = u_data | 0x08 ;	// led, en, rw, rs = 1000 = 0x08
	data[2] = l_data | 0x0C ;
	data[3] = l_data | 0x08 ;
	HAL_I2C_Master_Transmit (&hi2c2, SLAVE_ADDRESS_LCD<<1,(uint8_t *) data, 4, 100);
}

void LCD_SendData(char command)
{
	uint8_t data[4], u_data, l_data;
	
	u_data = command & 0xF0;
	l_data = (command << 4) & 0xF0 ;
	data[0] = u_data | 0x0D ;
	data[1] = u_data | 0x09 ;
	data[2] = l_data | 0x0D ;
	data[3] = l_data | 0x09 ;
	HAL_I2C_Master_Transmit (&hi2c2, SLAVE_ADDRESS_LCD<<1,(uint8_t *) data, 4, 100);
}

void LCD_Init(void)
{
	HAL_Delay(50);
	LCD_SendCmd(0x30);
	HAL_Delay(5);
	LCD_SendCmd(0x30);
	HAL_Delay(1);
	LCD_SendCmd(0x30);
	HAL_Delay(1);
	LCD_SendCmd(0x20);
	HAL_Delay(1);
	
	LCD_SendCmd(LCD_FUNCTIONSET | LCD_4BITMODE | LCD_2LINE | LCD_5x8DOTS);
	HAL_Delay(1);
	LCD_SendCmd(LCD_DISPLAYCONTROL | LCD_DISPLAYON | LCD_CURSOROFF | LCD_BLINKOFF);
	HAL_Delay(1);
	LCD_SendCmd(LCD_ENTRYMODESET | LCD_ENTRYLEFT | LCD_ENTRYSHIFTDECREMENT);
	HAL_Delay(1);
	LCD_SendCmd(LCD_SETDDRAMADDR);
	HAL_Delay(1);
	LCD_SendCmd(LCD_CLEARDISPLAY);
	HAL_Delay(20);
}

void LCD_SetCursor(uint8_t row, uint8_t collum)
{
		switch (row)
	{
		case 0:
		{
			LCD_SendCmd(LCD_SETDDRAMADDR | 0x00 | collum);
			break;
		}
		case 1:
		{
			LCD_SendCmd(LCD_SETDDRAMADDR | 0x40 | collum);
			break;
		}
		case 2:
		{
			LCD_SendCmd(LCD_SETDDRAMADDR | 0x14 | collum);
			break;
		}
		case 3:
		{
			LCD_SendCmd(LCD_SETDDRAMADDR | 0x54 | collum);
			break;
		}
	}
}

void print_char(char *string)
{
	while (*string) 
		LCD_SendData (*string++);
}

void print_float(float input)
{
	char str[12];
	sprintf(str, "%0.2f", input);
	print_char(str);
}

void print_int(int input)
{
	char str[12];
	sprintf(str, "%d", input);
	print_char(str);
}

void LCD_Clear(void)
{
	LCD_SendCmd(LCD_CLEARDISPLAY);
	HAL_Delay(20);
}
