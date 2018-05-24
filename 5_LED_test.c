/*
 * npere017_FP_LED_Lights_with_electro-things.c
 *
 * Created: 5/22/2018 10:22:22 AM
 * Author : xXSexybeastXx
 */ 

#include <avr/io.h>
#include "timer.h"
#include "io.c"
#include "io.h"

// Values
unsigned char curr;
unsigned char score = 0;

enum LED_States{LED_SMStart, LED_Init, LED_L1, LED_L2, LED_L3, LED_L4, LED_L5, LED_Wrong, LED_Right, LED_Release} LED_state;
    
void LEDs()
{
    switch(LED_state)
    {
        case(LED_SMStart):
        {
            LED_state = LED_Init;
            break;
        }
        case(LED_Init):
        {
            LED_state = LED_L1;
            break;
        }
        case(LED_L1):
        {
            curr = LED_state;
            
            if((~PINA & 0x04) == 0x04)
            {
                LED_state = LED_Wrong;
            }
            else
            {
                LED_state = LED_L2;
            }
            
            break;
        }
        case(LED_L2):
        {
            curr = LED_state;
            
            if((~PINA & 0x04) == 0x04)
            {
                LED_state = LED_Right;
            }
            else
            {
                LED_state = LED_L3;
            }
            
            break;
        }
        case(LED_L3):
        {
            curr = LED_state;
            
            if((~PINA & 0x04) == 0x04)
            {
                LED_state = LED_Wrong;
            }
            else
            {
                LED_state = LED_L4;
            }
            
            break;
        }
        case(LED_L4):
        {
            curr = LED_state;
            
            if((~PINA & 0x04) == 0x04)
            {
                LED_state = LED_Right;
            }
            else
            {
                LED_state = LED_L5;
            }
            
            break;
        }
        case(LED_L5):
        {
            curr = LED_state;
            
            if((~PINA & 0x04) == 0x04)
            {
                LED_state = LED_Wrong;
            }
            else
            {
                LED_state = LED_L1;
            }
            
            break;
        }
        case(LED_Wrong):
        {
            LED_state = LED_Release;
            break;
        }
        case(LED_Right):
        {
            LED_state = LED_Release;
            break;
        }
        case(LED_Release):
        {
            if((~PINA & 0x04) == 0x00)
            {
                LED_state = curr;
            }
            else
            {
                LED_state = LED_Release;
            }
            
            break;
        }
        default:
        {
            LED_state = LED_Init;
        }
    }
    
    switch(LED_state)
    {
        case(LED_SMStart):
        {
            break;
        }
        case(LED_Init):
        {
            score = 0;
            curr = LED_Init;
            LCD_Cursor(1);
            LCD_WriteData(score + '0');
            break;
        }
        case(LED_L1):
        {
            PORTB = 0x01;
            break;
        }         
        case(LED_L2):
        {
            PORTB = 0x02;
            break;
        }   
        case(LED_L3):
        {
            PORTB = 0x04;
            break;
        }
        case(LED_L4):
        {
            PORTB = 0x08;
            break;
        }
        case(LED_L5):
        {
            PORTB = 0x10;
            break;
        }
        case(LED_Wrong):
        {
            if(score > 0)
            {
                score = (score - 1);
            }
            LCD_Cursor(1);
            LCD_WriteData(score + '0');
            break;
        }
        case(LED_Right):
        {
            if(score < 20)
            {
                score = (score + 1);
            }
            LCD_Cursor(1);
            LCD_WriteData(score + '0');
            break;
        }
        case(LED_Release):
        {
            break;
        }
        default:
        {
            LCD_DisplayString(6, "ERROR");
            break;
        }
    }
}

int main(void)
{
    DDRA = 0x03;    PORTA = 0xFC;
    DDRD = 0xFF;    PORTD = 0x00;
    DDRB = 0xFF;    PORTB = 0x00;
    LCD_init();
    LCD_ClearScreen();
    
    TimerSet(100);
    TimerOn();
    /* Replace with your application code */
    while (1) 
    {
        LEDs();
        
        while(!TimerFlag);
        TimerFlag = 0;
    }
}