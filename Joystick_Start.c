// This will hold the start menu for the game, which has different gameplay options
// This section will utilize the joystick and built-in button

#define F_CPU 8000000UL		/* Define CPU Frequency e.g. here its 8MHz */
#include <avr/io.h>		/* Include AVR std. library file */
#include <util/delay.h>		/* Include inbuilt defined Delay header file */
#include "io.h"
#include "io.c"
#include "timer.h"

// Created characters for LCD screen
	unsigned char Character1[] = { 0x1f,0x11,0x15,0x15,0x15,0x15,0x11,0x1f };    // Unpressed button
	unsigned char Character2[] = { 0x0,0xe,0xe,0xe,0xe,0xe,0xe,0x0 };            // Pressed button
	unsigned char Character3[] = { 0x0,0x4,0x6,0x1f,0x6,0x4,0x0,0x0 };           // Right Arrow
	unsigned char Character4[] = { 0x0,0x4,0xc,0x1f,0xc,0x4,0x0,0x0 };           // Left Arrow
	unsigned char Character5[] = { 0x4,0xe,0xe,0x1f,0x1f,0x4,0x4,0x4 };          // Up Arrow
	unsigned char Character6[] = { 0x4,0x4,0x4,0x1f,0x1f,0xe,0xe,0x4 };          // Down Arrow
	unsigned char Character7[] = { 0x11,0x11,0x11,0x11,0x1f,0x1f,0x1f,0x1f };    // Hand
	unsigned char Character8[] = { 0x1f,0x11,0x11,0x11,0x11,0x1b,0x1b,0x1b };    // Headphones
        
// Global Variables
unsigned char count;

// States
enum St_States{St_SMStart, St_Init, St_Disp, St_Van, St_Wait} St_state;

void Start_Screen()
{
    switch(St_state)
    {
        case(St_SMStart):
        {
            St_state = St_Init;
            break;
        }
        case(St_Init):
        {
            St_state = St_Disp;
            break;
        }
        case(St_Disp):
        {
            St_state = St_Wait;
            break;
        }
        default:
        {
            St_state = St_Init;
        }
    }
    
    switch(St_state)
    {
        case(St_SMStart):
        {
            break;
        }
        case(St_Init):
        {
            LCD_ClearScreen();
            count = 0;
            break;
        }
        case(St_Disp):
        {
            LCD_DisplayString(7, "Press           Start");
            break;
        }
        case(St_Wait):
        {
            if(count < 3)
            {
                
            }
            else
            {
                LCD_ClearScreen();
            }
            
            break;
        }
    }
}

int main()
{
    DDRA = 0xFF; PORTA = 0x00;
    DDRD = 0xFF; PORTD = 0x00;

	LCD_Init();
    TimerSet(500);
    TimerOn();
	
    unsigned char i;
    
	LCD_Custom_Char(0, Character1);  /* Build Character1 at position 0 */
	LCD_Custom_Char(1, Character2);  /* Build Character2 at position 1 */
	LCD_Custom_Char(2, Character3);  /* Build Character3 at position 2 */
	LCD_Custom_Char(3, Character4);  /* Build Character4 at position 3 */
	LCD_Custom_Char(4, Character5);  /* Build Character5 at position 4 */
	LCD_Custom_Char(5, Character6);  /* Build Character6 at position 5 */
	LCD_Custom_Char(6, Character7);  /* Build Character6 at position 6 */
	LCD_Custom_Char(7, Character8);  /* Build Character6 at position 7 */

	LCD_Command(0x80);		/*cursor at home position */
	//LCD_String("Custom LCD overwrite");
	LCD_DisplayString(1, "Custom LCD test");
    LCD_Command(0xc0);
	
	for(i=0;i<8;i++)		/* function will send data 1 to 8 to lcd */
	{
    	LCD_Char(i);		/* char at 'i'th position will display on lcd */
    	LCD_Char(' ');		/* space between each custom char. */
	}
	/*while(1)
    {
        Start_Screen();
        
        while(!TimerFlag);
        TimerFlag = 0;
    }*/
}