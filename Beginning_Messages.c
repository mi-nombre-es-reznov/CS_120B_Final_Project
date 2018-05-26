// This is the first part of the LCD display that will scoll in through both sides, hard-coded.

#include <avr/io.h>
#include <avr/interrupt.h>
#include "io.c"
#include "io.h"

enum Intro_LCD{Intro_SMStart, Intro_Init, Intro_Stage1, Intro_Stage2, Intro_Stage3, Intro_Stage4,
Intro_Stage5, Intro_Stage6, Intro_Stage7, Intro_Stage8, Intro_Stage9, Intro_StageA, Intro_StageB} Intro_state;

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
            Intro_state = Intro_StageA;
            break;
        }
        case(Intro_StageA):
        {
            Intro_state = Intro_StageB;
            break;
        }
        case(Intro_StageB):
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
      case(Intro_StageA):
        {
             LCD_DisplayString(1, "   Welcome            to the");
             break;
        }
      case(Intro_StageB):
        {
             LCD_DisplayString(1, "    Welcome          to the");
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
    while(1)
    {
        
    }
}