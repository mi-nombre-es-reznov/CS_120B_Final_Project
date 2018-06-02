// Testing_input_with_shift_reg.c

#include <avr/io.h>
#include "timer.h"
#include "io.c"
#include "io.h"

// Shift register
void transmit_data(unsigned char data) {
    int i;
    for (i = 0; i < 8 ; ++i) {
        // Sets SRCLR to 1 allowing data to be set
        // Also clears SRCLK in preparation of sending data
        PORTC = 0x08;
        // set SER = next bit of data to be sent.
        PORTC |= ((data >> i) & 0x01);
        // set SRCLK = 1. Rising edge shifts next bit of data into the shift register
        PORTC |= 0x02;
    }
    // set RCLK = 1. Rising edge copies data from “Shift” register to “Storage” register
    PORTC |= 0x04;
    // clears all lines in preparation of a new transmission
    PORTC = 0x00;
}

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
            
            if((~PINA & 0x20) == 0x20)
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
            
            if((~PINA & 0x20) == 0x20)
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
            
            if((~PINA & 0x20) == 0x20)
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
            
            if((~PINA & 0x20) == 0x20)
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
            
            if((~PINA & 0x20) == 0x20)
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
            if((~PINA & 0x20) == 0x00)
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
            transmit_data(0x01);
            break;
        }
        case(LED_L2):
        {
            transmit_data(0x02);
            break;
        }
        case(LED_L3):
        {
            transmit_data(0x04);
            break;
        }
        case(LED_L4):
        {
            transmit_data(0x08);
            break;
        }
        case(LED_L5):
        {
           transmit_data(0x10);
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
    DDRA = 0x07;    PORTA = 0xF8;
    DDRD = 0xFF;    PORTD = 0x00;
    DDRC = 0xFF;    PORTC = 0x00;
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