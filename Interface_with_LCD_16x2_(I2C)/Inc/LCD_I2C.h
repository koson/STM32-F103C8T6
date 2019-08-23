#include "stm32f1xx_hal.h"

// i2c port and lcd address
extern I2C_HandleTypeDef hi2c2;
#define SLAVE_ADDRESS_LCD 0x27

// commands
#define LCD_CLEARDISPLAY 0x01
#define LCD_RETURNHOME 0x02
#define LCD_ENTRYMODESET 0x04
#define LCD_DISPLAYCONTROL 0x08
#define LCD_CURSORSHIFT 0x10
#define LCD_FUNCTIONSET 0x20
#define LCD_SETCGRAMADDR 0x40
#define LCD_SETDDRAMADDR 0x80

// flags for display entry mode,	use with(LCD_ENTRYMODESET)
#define LCD_ENTRYRIGHT 0x00
#define LCD_ENTRYLEFT 0x02
#define LCD_ENTRYSHIFTINCREMENT 0x01
#define LCD_ENTRYSHIFTDECREMENT 0x00

// flags for display on/off control,	use_with(LCD_DISPLAYCONTROL)
#define LCD_DISPLAYON 0x04
#define LCD_DISPLAYOFF 0x00
#define LCD_CURSORON 0x02
#define LCD_CURSOROFF 0x00
#define LCD_BLINKON 0x01
#define LCD_BLINKOFF 0x00

// flags for display/cursor shift, 	use_with(LCD_CURSORSHIFT)
#define LCD_DISPLAYMOVE 0x08
#define LCD_CURSORMOVE 0x00
#define LCD_MOVERIGHT 0x04
#define LCD_MOVELEFT 0x00

// flags for function set,	use with(LCD_FUNCTIONSET)
#define LCD_8BITMODE 0x10
#define LCD_4BITMODE 0x00
#define LCD_2LINE 0x08
#define LCD_1LINE 0x00
#define LCD_5x10DOTS 0x04
#define LCD_5x8DOTS 0x00

// flags for backlight control
#define LCD_BACKLIGHT 0x08
#define LCD_NOBACKLIGHT 0x00


#define LCD_Print(data) _Generic((data), 	\
		int: print_int, 											\
		float: print_float,										\
		char: print_char, 										\
		default: print_char 									\
		)(data)

void LCD_Init(void);
void LCD_SendData(char command);
void LCD_SendCmd(uint8_t command);
void LCD_SetCursor(uint8_t row, uint8_t collum);
void print_char(char *string);
void LCD_Clear(void);
	
void print_float(float input);
void print_int(int input);
void print_char(char *string);
		