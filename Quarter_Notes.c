/*
 * Quarter_Notes.c.c
 *
 * Created: 6/2/2018 5:51:54 PM
 * Author : xXSexyBeastXx
 */ 

#include <avr/io.h>
#include "timer.h"

void transmit_data(unsigned short data) {
    int i;
    for (i = 0; i < 16 ; ++i) {
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

// Global Variables
unsigned short count;
//short Q[] = {0x0001, 0x0002, 0x0004, 0x0008, 0x0010, 0x0020, 0x0040, 0x0080, 0x0100, 0x0200, 0x0400, 0x0800, 0x1000, 0x2000,
//    0x4000, 0x8000};
short Q[] = {0x0001, 0x0000, 0x0004, 0x0000, 0x0010, 0x0000, 0x0040, 0x0000, 0x0100, 0x0000, 0x0400, 0x0000, 0x1000, 0x0000,
    0x4000, 0x0000};

enum s{start, init, cycle} state;
    
void Cyc()
{
    switch(state)
    {
        case(start):
        {
            state = init;
            break;
        }
        case(init):
        {
            state = cycle;
            break;
        }
        case(cycle):
        {
            state = cycle;
            break;
        }
        default:
        {
            state = init;
            break;
        }
    }
    
    switch(state)
    {
        case(start):
        {
            break;
        }
        case(init):
        {
            count = 0;
            break;
        }
        case(cycle):
        {
            if(count <= 15)
            {             
                transmit_data(Q[count]);
                count++;
            }
            else
            {
                count = 0;
            }
            
            break;
        }
        default:
        {
            transmit_data(0xFF);
            break;
        }
    }
}
int main(void)
{
    DDRC = 0xFF; PORTC = 0x00;
    
    TimerSet(200);
    TimerOn();
    /* Replace with your application code */
    while (1) 
    {
        Cyc();
        
        while(!TimerFlag);
        TimerFlag = 0;
    }
    
    return 0;
}