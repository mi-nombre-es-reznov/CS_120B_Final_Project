// This is the first part of the LCD display that will scoll in through both sides, hard-coded.
#include <avr/io.h>
#include <avr/interrupt.h>
#include "timer.h"
#include "io.c"
#include "io.h"

unsigned char count = 0;
enum Intro_LCD{Intro_SMStart, Intro_Init, Intro_Stage1, Intro_Stage2, Intro_Stage3, 
    Intro_Stage4, Intro_Stage5, Intro_Stage6, Intro_Stage7, Intro_Stage8, Intro_Stage9, 
    Intro_StageA, Intro_StageB, Intro_Wait, Intro_Beat_Trainer, Intro_Wait2} Intro_state;

void Intro()
{
    switch(Intro_state)
    {
        case(Intro_SMStart):
        {
            Intro_state = Intro_Init;
            break;
        }
        case(Intro_Init):
        {
            Intro_state = Intro_Stage1;
            break;
        }
        case(Intro_Stage1):
        {
            Intro_state = Intro_Stage2;
            break;
        }
        case(Intro_Stage2):
        {
            Intro_state = Intro_Stage3;
            break;
        }
        case(Intro_Stage3):
        {
            Intro_state = Intro_Stage4;
            break;
        }
        case(Intro_Stage4):
        {
            Intro_state = Intro_Stage5;
            break;
        }
        case(Intro_Stage5):
        {
            Intro_state = Intro_Stage6;
            break;
        }
        case(Intro_Stage6):
        {
            Intro_state = Intro_Stage7;
            break;
        }
        case(Intro_Stage7):
        {
            Intro_state = Intro_Stage8;
            break;
        }
        case(Intro_Stage8):
        {
            Intro_state = Intro_Stage9; 
            break;
        }
        case(Intro_Stage9):
        {
            Intro_state = Intro_Wait;
            break;
        }
        case(Intro_Wait):
        {
            break;
        }
        case(Intro_Beat_Trainer):
        {
            break;
        }
        case(Intro_Wait2):
        {
            break;
        }
        default:
        {
            Intro_state = Intro_Init;
            break;
        }
    }
    
    switch(Intro_state)
    {
        case(Intro_SMStart):
        {
            break;
        }
        case(Intro_Init):
        {
            LCD_ClearScreen();
            break;
        }
        case(Intro_Stage1):
        {
            LCD_DisplayString(1, "e                              t");
            break;
        }
        case(Intro_Stage2):
        {
            LCD_DisplayString(1, "me                            to");
            break;
        }
        case(Intro_Stage3):
        {
            LCD_DisplayString(1, "ome                          to ");
            break;
        }
        case(Intro_Stage4):
        {
            LCD_DisplayString(1, "come                        to t");
            break;
        }
        case(Intro_Stage5):
        {
            LCD_DisplayString(1, "lcome                      to th");
            break;
        }
        case(Intro_Stage6):
        {
            LCD_DisplayString(1, "elcome                    to the");
            break;
        }
        case(Intro_Stage7):
        {
            LCD_DisplayString(1, "Welcome                  to the");
            break;
        }
        case(Intro_Stage8):
        {
            LCD_DisplayString(1, " Welcome                to the");
            break;
        }
        case(Intro_Stage9):
        {
            LCD_DisplayString(1, "  Welcome              to the");
            break;
        }
        case(Intro_Wait):
        {
            if(count < 1)
            {
                
            }
            else
            {
                LCD_ClearScreen();
                Intro_state = Intro_Beat_Trainer;
                count = 0;
            }
            
            count++;
            break;
        }
        case(Intro_Beat_Trainer):
        {
            count++;
            if(count <= 9)
            {
                if(count % 2 == 0)
                {
                    LCD_DisplayString(7, "Beat          Trainer!");
                }
                else
                {
                    LCD_ClearScreen();
                }
            }
            else
            {
                LCD_DisplayString(7, "Beat          Trainer!");
                Intro_state = Intro_Wait2;
                count = 0;
            }   
            
            break;
        }
        case(Intro_Wait2):
        {
            if(count <= 2)
            {
                
            }
            else
            {
                LCD_ClearScreen();
            }
            
            count++;
            break;
        }
        default:
        {
            LCD_DisplayString(5, "Error!!!");
            break;
        }
    }
}

int main()
{
    DDRA = 0x03;    PORTA = 0xFC;
    DDRD = 0xFF;    PORTD = 0x00;
    
    LCD_init();
    LCD_ClearScreen();
    
    TimerSet(650);
    TimerOn();
    
    while(1)
    {
        Intro();
        
        while(!TimerFlag);
        TimerFlag = 0;
    }
    
    return 0;
}