#ifndef __io_h__
#define __io_h__

void LCD_init();
void LCD_ClearScreen(void);
void LCD_WriteCommand (unsigned char Command);
void LCD_Cursor (unsigned char column);
void LCD_DisplayString(unsigned char column ,const unsigned char *string);
void delay_ms(int miliSec);

// Other code for LCD character creation
void LCD_INIT();
void LCD_Command(unsigned char);
void LCD_Char (unsigned char char_data);
void LCD_String (char *str);
void LCD_String_xy (char row, char pos, char *str);
void LCD_Clear();
void LCD_Custom_Char (unsigned char loc, unsigned char *msg);
#endif