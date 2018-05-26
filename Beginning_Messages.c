// This is the first part of the LCD display that will scoll in through both sides, hard-coded.

#include <avr/io.h>
#include <avr/interrupt.h>
#include "io.c"
#include "io.h"
 
enum Intro_LCD{Intro_SMStart, Intro_Init, Intro_Stage1, Intro_Stage2, Intro_Stage3, Intro_Stage4,
    Intro_Stage5, Intro_Stage6, Intro_Stage7, Intro_Stage8, Intro_Stage9, Intro_Stage_A, Intro_StageB, Intro_StageC} Intro_state;
    
Intro()
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
        case(Intro_Stage5)
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
            Intro_state = Intro_Stage_A;
            break;
        }
        case(Intro_Stage_A):
        {
            Intro_state = Intro_StageB;
            break;
        }
        case(Intro_StageB):
        {
            Intro_state = Intro_StageC;
            break;
        }
        case(Intro_StageC):
        {
            break;
        }
        default:
        {
            Intro_state = Intro_Init;
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