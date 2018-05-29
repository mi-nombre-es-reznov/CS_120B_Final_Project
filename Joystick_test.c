// Joystick code test to allow for signals of left, right, up, and down.
// The code even accepts the button press from pressing the joystick in.

#define F_CPU 8000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <stdlib.h>
#include "adc.h"
#include "adc.c"
#include "timer.h"
#include "io.h"
#include "io.c"

unsigned long x, y = 0;
enum J_States {J_SMStart, J_Init, J_X, J_Y} J_state;

int JoyStick(int state)
{
    unsigned long temp = 50;
    unsigned char tempb = 0;
    
    switch(J_state)
    {
        case J_SMStart:
        {
            state = J_Init;	
            break;
        }
        case J_Init:
        {
            state = J_X;		
            break;
        }
        case J_X:
        {
            state = J_Y;		
            break;
        }
        case J_Y:
        {
            state = J_X;		
            break;
        }
        default:
        {
            state = J_Init;	
            break;
        }
    }
    
    switch(J_state)
    {
        case J_SMStart:
        {
            break;
        }
        case J_Init:
        {
            PORTB = 0x00; 
            break;
        }
        case J_X:
        {
            x = ADC_ReadData(2);
            LCD_Cursor(1);
            if (x >= 0 && x < 2*temp)
            {
                tempb = 2;
                LCD_DisplayString(1, "Left!");
            }
            else if(x >= 4*temp && x < 6*temp)
            {
                tempb = 0x00;
                LCD_DisplayString(1, "Right!");
            }
            else if (x >= 3*temp && x < 6*temp)
            {
                tempb = 4;
                LCD_DisplayString(1, "Default!");
            }
        
            if((~PINA & 0x10) == 0x10)
            {
                PORTB = 0xF0;
                LCD_DisplayString(6, "Button");
            }
        
            break;
        }
        case J_Y:
        {
             y = ADC_ReadData(3);

             if(y < 30)
             {
                 tempb += 0x01;
                 LCD_DisplayString(1, "Up!");
             }
             else if(y >= 4*temp && y < 6*temp)
             {
                 tempb += 0x08;
                 LCD_DisplayString(1, "Down!");
             }

             if((~PINA & 0x10) == 0x10)
             {
                 PORTB = 0xF0;
                 LCD_DisplayString(6, "Button");
             }

             break;
         }
         
         PORTB = tempb;
         return state;
    } 
}

int main()
{
    DDRA = 0x03; PORTA = 0xFC;
    DDRB = 0xFF; PORTB = 0x00;
    DDRD = 0xFF; PORTD = 0x00;
    
    ADC_Init(5, 1, 1);

    // Set the timer and turn it on
    TimerSet(350);
    TimerOn();
    LCD_init();
    LCD_ClearScreen();

    unsigned short i; // Scheduler for-loop iterator

    while(1) 
    {
        JoyStick();
        
        while(!TimerFlag);
        TimerFlag = 0;
    }
    // Error: Program should not exit!
    return 0;
}