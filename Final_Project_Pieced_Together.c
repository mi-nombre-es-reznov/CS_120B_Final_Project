// Final_Project_Pieced_Together.c


#define F_CPU 8000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <stdlib.h>
#include "adc.h"
#include "adc.c"
#include "timer.h"
#include "io.h"
#include "io.c"
#include "scheduler.h"

//--------Shared Variables----------------------------------------------------


//--------End Shared Variables------------------------------------------------

//--------User defined FSMs---------------------------------------------------
//Enumeration of states.
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


// --------END User defined FSMs-----------------------------------------------

// Implement scheduler code from PES.
int main()
{
    // Set Data Direction Registers
    // Buttons PORTA[0-7], set AVR PORTA to pull down logic
    DDRA = 0x07;    PORTA = 0xF8;
    DDRD = 0xFF;    PORTD = 0x00;
    
    LCD_Init();
    LCD_ClearScreen();
    // . . . etc

    // Period for the tasks
    unsigned long int Intro_calc = 300;
    //unsigned long int SMTick2_calc = 500;
    //unsigned long int SMTick3_calc = 1000;
    //unsigned long int SMTick4_calc = 10;

    //Calculating GCD
    unsigned long int tmpGCD = 1;
    //tmpGCD = findGCD(SMTick1_calc, SMTick2_calc);
    //tmpGCD = findGCD(tmpGCD, SMTick3_calc);
    //tmpGCD = findGCD(tmpGCD, SMTick4_calc);

    //Greatest common divisor for all tasks or smallest time unit for tasks.
    unsigned long int GCD = tmpGCD;

    //Recalculate GCD periods for scheduler
    unsigned long int intro_period = Intro_calc/GCD;
    //unsigned long int SMTick2_period = SMTick2_calc/GCD;
    //unsigned long int SMTick3_period = SMTick3_calc/GCD;
    //unsigned long int SMTick4_period = SMTick4_calc/GCD;

    //Declare an array of tasks
    static task intro;//, task2, task3, task4;
    task *tasks[] = { &intro};//, &task2};//, &task3, &task4 };
    const unsigned short numTasks = sizeof(tasks)/sizeof(task*);

    // Task 1
    intro.state = Intro_SMStart;//Task initial state.
    intro.period = intro_period;//Task Period.
    intro.elapsedTime = intro_period;//Task current elapsed time.
    intro.TickFct = &Intro;//Function pointer for the tick.

    /*
    // Task 2
    task2.state = -1;//Task initial state.
    task2.period = SMTick2_period;//Task Period.
    task2.elapsedTime = SMTick2_period;//Task current elapsed time.
    task2.TickFct = &SMTick2;//Function pointer for the tick.

    // Task 3
    task3.state = -1;//Task initial state.
    task3.period = SMTick3_period;//Task Period.
    task3.elapsedTime = SMTick3_period; // Task current elasped time.
    task3.TickFct = &SMTick3; // Function pointer for the tick.

    // Task 4
    task4.state = -1;//Task initial state.
    task4.period = SMTick4_period;//Task Period.
    task4.elapsedTime = SMTick4_period; // Task current elasped time.
    task4.TickFct = &SMTick4; // Function pointer for the tick.
    */

    // Set the timer and turn it on
    TimerSet(GCD);
    TimerOn();

    unsigned short i; // Scheduler for-loop iterator
    while(1) {
        // Scheduler code
        for ( i = 0; i < numTasks; i++ ) {
            // Task is ready to tick
            if ( tasks[i]->elapsedTime == tasks[i]->period ) {
                // Setting next state for task
                tasks[i]->state = tasks[i]->TickFct(tasks[i]->state);
                // Reset the elapsed time for next tick.
                tasks[i]->elapsedTime = 0;
            }
            tasks[i]->elapsedTime += 1;
        }
        while(!TimerFlag);
        TimerFlag = 0;
    }

    // Error: Program should not exit!
    return 0;
}
