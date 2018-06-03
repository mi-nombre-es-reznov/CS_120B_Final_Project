// Attempt at whole notes

#define F_CPU 8000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <stdlib.h>
#include "timer.h"
#include "io.h"
#include "io.c"


short transmit_data(unsigned short data) {
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
    
    return data;
}

// Global Variables
unsigned char count, loop, wait;
unsigned char score, pos_place, neg_place;
signed char miss;
//short Q[] = {0x0001, 0x0002, 0x0004, 0x0008, 0x0010, 0x0020, 0x0040, 0x0080, 0x0100, 0x0200, 0x0400, 0x0800, 0x1000, 0x2000,
//    0x4000, 0x8000};
short Q[] = {0x0001, 0x0000, 0x0000, 0x0000, 0x0010, 0x0000, 0x0000, 0x0000, 0x0100, 0x0000, 0x0000, 0x0000, 0x1000, 0x0000,
0x0000, 0x0000};

enum Q_States{Q_SMStart, Q_Init, Q_Cycle, Q_Wait_Message} state;

void Cyc()
{
    switch(state)
    {
        case(Q_SMStart):
        {
            state = Q_Init;
            break;
        }
        case(Q_Init):
        {
            state = Q_Cycle;
            break;
        }
        case(Q_Cycle):
        {
            state = Q_Cycle;
            break;
        }
        case(Q_Wait_Message):
        {
            break;
        }
        default:
        {
            state = Q_Init;
            break;
        }
    }
    
    switch(state)
    {
        case(Q_SMStart):
        {
            break;
        }
        case(Q_Init):
        {
            count = 0;
            loop = 0;
            score = 0;
            miss = -1;
            pos_place = 0;
            neg_place = 0;
            wait = 0;
            LCD_Cursor(1);
            LCD_String("Hit:");
            LCD_Cursor(17);
            LCD_String("Miss:");
            break;
        }
        case(Q_Cycle):
        {
            if((loop % 4) == 0)
            {
                if(count <= 15)
                {
                    transmit_data(Q[count]);
                    if((~PINA & 0x20) == 0x20 && transmit_data(Q[count]) == 0x0001)
                    {
                        LCD_Cursor(6);
                        if(score <= 8)
                        {
                            score++;
                            LCD_WriteData(score + '0');
                        }
                        else if(score >= 9 && score <= 18)
                        {
                            LCD_Cursor(6);
                            LCD_String("1");
                            LCD_Cursor(7);
                            LCD_WriteData(pos_place + '0');
                            pos_place++;
                            score++;
                        }
                        else if(score >= 19)
                        {
                            LCD_ClearScreen();
                            LCD_DisplayString(5, "WINNER!!");
                            state = Q_Wait_Message;
                        }
                    }
                    else if((~PINA & 0x20) != 0x20 && transmit_data(Q[count]) == 0x0001)
                    {
                        LCD_Cursor(23);
                        if(miss <= 8)
                        {
                            miss++;
                            LCD_WriteData(miss + '0');
                        }
                        else if(miss >= 9 && miss <= 18)
                        {
                            LCD_Cursor(23);
                            LCD_String("1");
                            LCD_Cursor(24);
                            LCD_WriteData(neg_place + '0');
                            neg_place++;
                            miss++;
                        }
                        else if(miss >= 19)
                        {
                            LCD_ClearScreen();
                            LCD_DisplayString(5, "LOSER!!!");
                            state = Q_Wait_Message;
                        }
                    }
                    
                    count++;
                }
                else
                {
                    count = 0;
                }
            }

            loop++;
            break;
        }
        case(Q_Wait_Message):
        {
            if(wait <= 80)
            {
                
            }
            else
            {
                LCD_ClearScreen();
            }
            
            wait++;
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
    DDRA = 0x07; PORTA = 0xF8;
    DDRD = 0xFF; PORTD = 0x00;
    
    LCD_Init();
    LCD_ClearScreen();
    
    TimerSet(25);
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