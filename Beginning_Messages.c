// This is the first part of the LCD display that will scoll in through both sides, hard-coded.

#include <avr/io.h>
#include <avr/interrupt.h>
#include "io.c"
#include "io.h"
 
enum Intro_LCD{Intro_SMStart, Intro_Init, Intro_Stage1, Intro_Stage2, Intro_Stage3, Intro_Stage4,
    Intro_Stage5, Intro_Stage6, Intro_Stage7, Intro_Stage8, Intro_Stage9, Intro_Stage_A, Intro_StageB, Intro_StageC} Intro_state;
    

    
int main()
{
    while(1)
    {
        
    }
}