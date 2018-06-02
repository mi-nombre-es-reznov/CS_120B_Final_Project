// This is a bounded adder/subtracter that can max out at 255 and min out at 0.
// There are two buttons. One increments the count by 1, the other decrements by 1.

#include <avr/io.h>
#include "timer.h"

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

// variables
unsigned char count = 0;

enum T_States{T_SMStart, T_Init, T_Wait, T_Release} state;

void counter()
{
    switch(state)
    {
        case(T_SMStart):
        {
            state = T_Init;
            break;
        }
        case(T_Init):
        {
            state = T_Wait;
            break;
        }
        case(T_Wait):
        {
            if((~PINA & 0x60) == 0x20 && count <= 254)
            {
                count++;
                state = T_Release;
            }
            else if((~PINA & 0x60) == 0x40 && count >= 1)
            {
                count--;
                state = T_Release;
            }
            else if((~PINA & 0x60) == 0x60)
            {
                count = 0;
                state = T_Release;
            }
            
            break;
        }
        case(T_Release):
        {
            if((~PINA & 0x60) == 0x00)
            {
                state = T_Wait;
            }
            else
            {
                state = T_Release;
            }
            
            break;
        }
        default:
        {
            state = T_Init;
            break;
        }
    }
    
    switch(state)
    {
        case(T_SMStart):
        {
            break;
        }
        case(T_Init):
        {
            count = 0;
            transmit_data(count);
            break;
        }
        case(T_Wait):
        {
            break;
        }         
        case(T_Release):
        {
            transmit_data(count);
            break;
        }
        default:
        {
            transmit_data(0xAA);
            break;
        }
    }        
}

int main(void)
{
    DDRC = 0xFF; PORTC = 0xFF;
    DDRA = 0x00; PORTA = 0xFF;
    
    TimerSet(100);
    TimerOn();
    /* Replace with your application code */
    while (1)
    {
        counter();
        
        while(!TimerFlag);
        TimerFlag = 0;
    }
}