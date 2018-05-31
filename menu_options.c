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

// Created characters for LCD screen
unsigned char Character1[8] = { 0x1f,0x11,0x15,0x15,0x15,0x15,0x11,0x1f };    // Unpressed button
unsigned char Character2[8] = { 0x0,0xe,0xe,0xe,0xe,0xe,0xe,0x0 };            // Pressed button
unsigned char Character3[8] = { 0x0,0x4,0x6,0x1f,0x6,0x4,0x0,0x0 };           // Right Arrow
unsigned char Character4[8] = { 0x0,0x4,0xc,0x1f,0xc,0x4,0x0,0x0 };           // Left Arrow
unsigned char Character5[8] = { 0x4,0xe,0xe,0x1f,0x1f,0x4,0x4,0x4 };          // Up Arrow
unsigned char Character6[8] = { 0x4,0x4,0x4,0x1f,0x1f,0xe,0xe,0x4 };          // Down Arrow
unsigned char Character7[8] = { 0x11,0x11,0x11,0x11,0x1f,0x1f,0x1f,0x1f };    // Hand
unsigned char Character8[8] = { 0x1f,0x11,0x11,0x11,0x11,0x1b,0x1b,0x1b };    // Headphones

// Global variables
unsigned long x, y = 0;
unsigned char whole, half, quarter, eighth, sixteenth, performance;

enum M_States {M_SMStart, M_Init, M_X, M_Y, M_Training, M_T_Wait, M_Whole, M_W_Wait, M_Half, M_H_Wait, M_Quarter, M_Q_Wait,
     M_Eighth, M_E_Wait, M_Sixteenth, M_S_Wait, M_Performance, M_P_Wait} state;

void Menu()
{
    unsigned long temp = 50;
    unsigned char tempb = 0;
    
    switch(state)
    {
        case(M_SMStart):
        {
            state = M_Init;
            break;
        }
        case(M_Init):
        {
            state = M_X;
            break;
        }
        case(M_X):
        {
            state = M_Y;
            break;
        }
        case(M_Y):
        {
            state = M_Training;
            break;
        }
        case(M_Training):
        {
            state = M_T_Wait;

            break;
        }
        case(M_T_Wait):
        {
            x = ADC_ReadData(3);
            y = ADC_ReadData(4);
            
            if((x >= 3*temp && x < 6*temp) && (y >= 30 && y < 4*temp))
            {
                
            }
            else if((y < 30))
            {
                state = M_Whole;
            }
            else if(x >= 4*temp && x < 6*temp)
            {
                state = M_Performance;
            }
            else
            {
                state = M_Training;
            }
            
            break;
        }
        case(M_Whole):
        {
            state = M_W_Wait;
            break;
        }
        case(M_W_Wait):
        {
            x = ADC_ReadData(3);
            y = ADC_ReadData(4);
            
            if((x >= 3*temp && x < 6*temp) && (y >= 30 && y < 4*temp))
            {
                
            }
            else if((y < 30))
            {
                state = M_Half;
            }
            else if(y >= 4*temp && y < 6*temp)
            {
                state = M_Training;
            }
            else
            {
                state = M_Whole;
            }
            
            break;
        }
        case(M_Half):
        {
            state = M_H_Wait;
            
            break;
        }
        case(M_H_Wait):
        {
            x = ADC_ReadData(3);
            y = ADC_ReadData(4);
            
            if((x >= 3*temp && x < 6*temp) && (y >= 30 && y < 4*temp))
            {
                
            }
            else if((y < 30)) // Up
            {
                state = M_Quarter;
            }
            else if(y >= 4*temp && y < 6*temp) // Right
            {
                state = M_Whole;
            }
            else
            {
                state = M_Half;
            }
            
            break;
        }
        case(M_Quarter):
        {
            state = M_Q_Wait;
            break;
        }
        case(M_Q_Wait):
        {
            x = ADC_ReadData(3);
            y = ADC_ReadData(4);
            
            if((x >= 3*temp && x < 6*temp) && (y >= 30 && y < 4*temp))
            {
                
            }
            else if((y < 30)) // Up
            {
                state = M_Eighth;
            }
            else if(y >= 4*temp && y < 6*temp) // Down
            {
                state = M_Half;
            }
            else
            {
                state = M_Quarter;
            }
            
            break;
        }
        case(M_Eighth):
        {       
            state = M_E_Wait;
            break;
        }
        case(M_E_Wait):
        {
            x = ADC_ReadData(3);
            y = ADC_ReadData(4);
            
            if((x >= 3*temp && x < 6*temp) && (y >= 30 && y < 4*temp))
            {
                
            }
            else if((y < 30)) // Up
            {
                state = M_Sixteenth;
            }
            else if(y >= 4*temp && y < 6*temp) // Down
            {
                state = M_Quarter;
            }
            else
            {
                state = M_Eighth;
            }
            
            break;
        }
        case(M_Sixteenth):
        {
            state = M_S_Wait;
            break;
        }
        case(M_S_Wait):
        {
            x = ADC_ReadData(3);
            y = ADC_ReadData(4);
            
            if((x >= 3*temp && x < 6*temp) && (y >= 30 && y < 4*temp))
            {
                
            }
            else if(y >= 4*temp && y < 6*temp) // Down
            {
                state = M_Eighth;
            }
            else
            {
                state = M_Sixteenth;
            }
            
            break;
        }
        case(M_Performance):
        {
            state = M_P_Wait;
            break;
        }
        case(M_P_Wait):
        {
            x = ADC_ReadData(3);
            y = ADC_ReadData(4);
            
            if((x >= 3*temp && x < 6*temp) && (y >= 30 && y < 4*temp))
            {
                
            }
            else if(x >= 0 && x < 2*temp)
            {
                state = M_Training;
            }
            else
            {
                state = M_Performance;
            }
            
            break;
        }
        default:
        {
            state = M_Init;
            break;
        }
    }
    
    switch(state)
    {
        case(M_SMStart):
        {
            break;
        }
        case(M_Init):
        {
            PORTB = 0x00;
            //whole = 0;
            //half = 0;
            //quarter = 0;
            //eighth = 0;
            //sixteenth = 0;
            //performance = 0;
            LCD_Clear();
            break;
        }
        case(M_X):
        {
            x = ADC_ReadData(3);
            if (x >= 0 && x < 2*temp)
            {
                //pos = left;
                LCD_DisplayString(1,"Left!!");
            }
            else if(x >= 4*temp && x < 6*temp)
            {
                //pos = right;
                LCD_DisplayString(1, "Right!!");
            }
            else if (x >= 3*temp && x < 6*temp)
            {
                //pos = same;
                LCD_DisplayString(1, "Center!!");
            }
            
            if((~PINA & 0x20) == 0x20)
            {
                //pos = start;
            }
            
            break;
        }
        case(M_Y):
        {
            y = ADC_ReadData(4);

            if(y < 30)
            {
                LCD_DisplayString(1, "up!!!");
                //pos = up;
            }
            else if(y >= 30 && y < 4*temp)
            {
                LCD_DisplayString(1, "Zero-y!!!");
                //pos = same;
            }
            else if(y >= 4*temp && y < 6*temp)
            {
                LCD_DisplayString(1, "down!!");
                //pos = down;
            }

            if((~PINA & 0x20) == 0x20)
            {
                //pos = start;
            }
            
            break;
        }
        case(M_Training):
        {
            LCD_Clear();
            LCD_DisplayString(4,"Training??");
            LCD_Cursor(17);
            LCD_Char(4);
            LCD_Cursor(32);
            LCD_Char(2);

            break;
        }
        case(M_T_Wait):
        {
            break;
        }
        case(M_Whole):
        {
            LCD_Clear();
            LCD_String("  Whole Notes!");
            LCD_Cursor(17);
            LCD_Char(4);
            LCD_Cursor(32);
            LCD_Char(5);
            
            break;
        }
        case(M_W_Wait):
        {
            break;
        }
        case(M_Half):
        {
            LCD_Clear();
            LCD_String("  Half Notes!!");
            LCD_Cursor(17);
            LCD_Char(4);
            LCD_Cursor(32);
            LCD_Char(5);
            
            break;
        }
        case(M_H_Wait):
        {
            break;
        }
        case(M_Quarter):
        {
            LCD_Clear();
            LCD_String(" Quarter Notes!");
            LCD_Cursor(17);
            LCD_Char(4);
            LCD_Cursor(32);
            LCD_Char(5);
            
            break;
        }
        case(M_Q_Wait):
        {
            break;
        }
        case(M_Eighth):
        {
            LCD_Clear();
            LCD_String(" Eighth Notes!!");
            LCD_Cursor(17);
            LCD_Char(4);
            LCD_Cursor(32);
            LCD_Char(5);
            
            break;
        }
        case(M_E_Wait):
        {
            break;
        }
        case(M_Sixteenth):
        {
            LCD_Clear();
            LCD_String("Sixteenth Notes!");
            LCD_Cursor(32);
            LCD_Char(5);
            
            break;
        }
        case(M_S_Wait):
        {
            break;
        }
        case(M_Performance):
        {
            LCD_Clear();
            LCD_String(" Performance???");
            LCD_Cursor(17);
            LCD_Char(3);
            
            break;
        }
        case(M_P_Wait):
        {
            break;
        }
        default:
        {
            LCD_DisplayString(4, "ERROR!");
            break;
        }
    }
}

int main()
{
    //DDRA = 0x07; PORTA = 0xF8;
    DDRB = 0xFF; PORTB = 0x00;
    DDRD = 0xFF; PORTD = 0x00;
    
    // Set the timer and turn it on
    TimerSet(500);
    TimerOn();
    LCD_Init();
    LCD_ClearScreen();
    
    ADC_Init(5, 1, 1);

    LCD_Custom_Char(0, Character1);  /* Build Character1 at position 0 */
    LCD_Custom_Char(1, Character2);  /* Build Character2 at position 1 */
    LCD_Custom_Char(2, Character3);  /* Build Character3 at position 2 */
    LCD_Custom_Char(3, Character4);  /* Build Character4 at position 3 */
    LCD_Custom_Char(4, Character5);  /* Build Character5 at position 4 */
    LCD_Custom_Char(5, Character6);  /* Build Character6 at position 5 */
    LCD_Custom_Char(6, Character7);  /* Build Character6 at position 6 */
    LCD_Custom_Char(7, Character8);  /* Build Character6 at position 7 */

    LCD_Command(0x80);		/*cursor at home position */
    LCD_Command(0xc0);

    unsigned short i; // Scheduler for-loop iterator

    while(1)
    {
        Menu();
        
        while(!TimerFlag);
        TimerFlag = 0;
    }
    // Error: Program should not exit!
    return 0;
}