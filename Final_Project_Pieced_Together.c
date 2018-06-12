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
#include "working_parts.h"
#include "working_parts.c"
#include "scheduler.h"

// Created characters for LCD screen
unsigned char Character1[8] = { 0x1f,0x11,0x15,0x15,0x15,0x15,0x11,0x1f };    // Unpressed button
unsigned char Character2[8] = { 0x0,0xe,0xe,0xe,0xe,0xe,0xe,0x0 };            // Pressed button
unsigned char Character3[8] = { 0x0,0x4,0x6,0x1f,0x6,0x4,0x0,0x0 };           // Right Arrow
unsigned char Character4[8] = { 0x0,0x4,0xc,0x1f,0xc,0x4,0x0,0x0 };           // Left Arrow
unsigned char Character5[8] = { 0x4,0xe,0xe,0x1f,0x1f,0x4,0x4,0x4 };          // Up Arrow
unsigned char Character6[8] = { 0x4,0x4,0x4,0x1f,0x1f,0xe,0xe,0x4 };          // Down Arrow
unsigned char Character7[8] = { 0x11,0x11,0x11,0x11,0x1f,0x1f,0x1f,0x1f };    // Hand
unsigned char Character8[8] = { 0x1f,0x11,0x11,0x11,0x11,0x1b,0x1b,0x1b };    // Headphones

//--------Global Variables----------------------------------------------------
unsigned char Fin_count;
//--------End Shared Variables------------------------------------------------


//--------User defined FSMs---------------------------------------------------
//Enumeration of states.
enum Final_States{Fin_SMStart, Fin_Init, Fin_Intro, Fin_Start, Fin_Menu, Fin_which_game, Fin_Whole, Fin_Half, Fin_Quarter,
Fin_Eighth, Fin_Sixteenth, Fin_Performance, Fin_Performance_Wait, Fin_comp_loop};

int Final(unsigned int state)
{
    switch(state)
    {
        case(Fin_SMStart):
        {
            state = Fin_Init;
            break;
        }
        case(Fin_Init):
        {
            state = Fin_Intro;
            break;
        }
        case(Fin_Intro):
        {
            Intro();
            break;
        }
        case(Fin_Start):
        {
            Start_Screen();
            break;
        }
        case(Fin_Menu):
        {
            Menu();
            break;
        }
        case(Fin_which_game):
        {
            if(whole == 1)
            {
                state = Fin_Whole;
            }
            else if(half == 1)
            {
                state = Fin_Half;
            }
            else if(quarter == 1)
            {
                state = Fin_Quarter;
            }
            else if(eighth == 1)
            {
                state = Fin_Eighth;
            }
            else if(sixteenth == 1)
            {
                state = Fin_Sixteenth;
            }
            else if(performance == 1)
            {
                state = Fin_Performance;
            }
            else
            {
                state = Fin_Menu;
            }
            
            break;
        }
        case(Fin_Whole):
        {
            Whole();
            break;
        }
        case(Fin_Half):
        {
            Half();
            break;
        }
        case(Fin_Quarter):
        {
            Quarter();
            break;
        }
        case(Fin_Eighth):
        {
            Eighth();
            break;
        }
        case(Fin_Sixteenth):
        {
            Sixteenth();
            break;
        }
        case(Fin_Performance):
        {
            state = Fin_Performance_Wait;
            break;
        }
        case(Fin_Performance_Wait):
        {
            break;
        }
        case(Fin_comp_loop):
        {
            state = Fin_Menu;
            break;
        }
        default:
        {
            state = Fin_Init;
            break;
        }
    }
    
    switch(state)
    {
        case(Fin_SMStart):
        {
            break;
        }
        case(Fin_Init):
        {
            LCD_ClearScreen();
            Fin_count = 0;
            break;
        }
        case(Fin_Intro):
        {
            if(Intro_Flag == 1)
            {
                state = Fin_Start;
            }
            else
            {
                state = Fin_Intro;
            }
            
            break;
        }
        case(Fin_Start):
        {
            if(Start_Screen_Flag == 1)
            {
                state = Fin_Menu;
            }
            else
            {
                state = Fin_Start;
            }
            
            break;
        }
        case(Fin_Menu):
        {
            if(Menu_Flag == 1)
            {
                state = Fin_which_game;
            }
            else
            {
                state = Fin_Menu;
            }
            
            break;
        }
        case(Fin_which_game):
        {
            break;
        }
        case(Fin_Whole):
        {
            if(whole == 0)
            {
                Menu_Flag = 0;
                state = Fin_Menu;
            }
            
            break;
        }
        case(Fin_Half):
        {
            if(half == 0)
            {
                Menu_Flag = 0;
                state = Fin_Menu;
            }
            
            break;
        }
        case(Fin_Quarter):
        {
            if(quarter == 0)
            {
                Menu_Flag = 0;
                state = Fin_Menu;
            }
            
            break;
        }
        case(Fin_Eighth):
        {
            if(eighth == 0)
            {
                Menu_Flag = 0;
                state = Fin_Menu;
            }
            
            break;
        }
        case(Fin_Sixteenth):
        {
            if(sixteenth == 0)
            {
                Menu_Flag = 0;
                state = Fin_Menu;
            }
            
            break;
        }
        case(Fin_Performance):
        {
            LCD_ClearScreen();
            LCD_Cursor(3);
            LCD_Char(7);
            LCD_Cursor(5);
            LCD_String("Not  Yet");
            LCD_Cursor(14);
            LCD_Char(7);
            LCD_Cursor(18);
            LCD_Char(7);
            LCD_Cursor(20);
            LCD_String("Available!");
            LCD_Cursor(31);
            LCD_Char(7);
            performance = 0;
            
            break;
        }
        case(Fin_Performance_Wait):
        {
            if(Fin_count <= 120)
            {
                
            }
            else
            {
                if(performance == 0)
                {
                    Menu_Flag = 0;
                    state = Fin_Menu;
                }
            }
            
            Fin_count++;
            break;
        }
        case(Fin_comp_loop):
        {
            LCD_ClearScreen();
            LCD_DisplayString(1, "Entered loop state");
            break;
        }
        default:
        {
            LCD_DisplayString(1, "ERROR!!!");
            break;
        }
    }
    
    return state;
}
// --------END User defined FSMs-----------------------------------------------

// Implement scheduler code from PES.
int main()
{
    // Set Data Direction Registers
    // Buttons PORTA[0-7], set AVR PORTA to pull down logic
    DDRA = 0x07;    PORTA = 0xF8;
    DDRD = 0xFF;    PORTD = 0x00;
    DDRC = 0xFF;    PORTC = 0x00;
    DDRB = 0x00;    PORTB = 0xFF;
    
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
    // . . . etc

    // Period for the tasks
    unsigned long int Final_calc = 25;

    //Calculating GCD
    unsigned long int tmpGCD = 1;

    //Greatest common divisor for all tasks or smallest time unit for tasks.
    unsigned long int GCD = tmpGCD;

    //Recalculate GCD periods for scheduler
    unsigned long int Final_period = Final_calc/GCD;
    //Declare an array of tasks
    static task finale;
    task *tasks[] = { &finale};
    const unsigned short numTasks = sizeof(tasks)/sizeof(task*);

    // Task 1
    finale.state = Fin_SMStart;//Task initial state.
    finale.period = Final_period;//Task Period.
    finale.elapsedTime = Final_period;//Task current elapsed time.
    finale.TickFct = &Final;//Function pointer for the tick.

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

    LCD_ClearScreen();
    LCD_DisplayString(1, "Program has exited!");
    // Error: Program should not exit!
    return 0;
}