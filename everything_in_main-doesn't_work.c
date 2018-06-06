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
//#include "working_parts.h"
//#include "working_parts.c"
#include "scheduler.h"

// Working Parts

// *******************************************
// *      Shift register Call Functions      *
// *******************************************
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

// ****************************************************************************
// *                           Global Variables                               *
// ****************************************************************************
unsigned char count2, start_count, x, y = 0, read_count;
unsigned char Intro_Flag = 0, Start_Screen_Flag = 0, Menu_Flag = 0, Whole_Flag = 0;
unsigned char whole, half, quarter, eighth, sixteenth, performance;
unsigned char loop, wait, score, pos_place, neg_place;
signed char miss;
unsigned short count;

// ******************************************************************************************************************************
// *                                          Arrays that will make that LED game operate                                       *
// ******************************************************************************************************************************
short W[] = {0x0001, 0x0000, 0x0000, 0x0000, 0x0010, 0x0000, 0x0000, 0x0000, 0x0100, 0x0000, 0x0000, 0x0000, 0x1000, 0x0000,
0x0000, 0x0000};

short e[] = {0x0001, 0x0000, 0x0004, 0x0000, 0x0010, 0x0000, 0x0040, 0x0000, 0x0100, 0x0000, 0x0400, 0x0000, 0x1000, 0x0000,
0x4000, 0x0000};

short S[] = {0x0001, 0x0002, 0x0004, 0x0008, 0x0010, 0x0020, 0x0040, 0x0080, 0x0100, 0x0200, 0x0400, 0x0800, 0x1000, 0x2000,
0x4000, 0x8000};

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
unsigned char reset, counter;
//--------End Shared Variables------------------------------------------------


//--------User defined FSMs---------------------------------------------------
//Enumeration of states.
enum Final_States{Fin_SMStart, Fin_Init, Fin_Intro, Fin_Start, Fin_Menu, Fin_which_game, Fin_Whole, Fin_Half, Fin_Quarter,
Fin_Eighth, Fin_Sixteenth, Fin_Performance, Fin_Performance_Wait, Fin_Game_Over};
enum Intro_LCD{Intro_SMStart, Intro_Init, Intro_Stage1, Intro_Stage2, Intro_Stage3,
    Intro_Stage4, Intro_Stage5, Intro_Stage6, Intro_Stage7, Intro_Stage8, Intro_Stage9,
Intro_Wait, Intro_Beat_Trainer, Intro_Wait2};// state;
enum states{St_SMStart, St_Init, St_Disp, St_Van, St_Wait, St_Pressed, St_Press_Wait};// state;
enum M_States {M_SMStart, M_Init, M_X, M_Y, M_Training, M_T_Wait, M_Whole, M_W_Wait, M_Half, M_H_Wait, M_Quarter, M_Q_Wait,
M_Eighth, M_E_Wait, M_Sixteenth, M_S_Wait, M_Performance, M_P_Wait, M_Release, M_R_Wait};// state;
enum W_states{W_SMStart, W_Init, W_Cycle, W_Wait_Message};// state;
enum H_States{H_SMStart, H_Init, H_Cycle, H_Wait_Message};// state;
enum Q_states{Q_SMStart, Q_Init, Q_Cycle, Q_Wait_Message};// state;
enum E_states{E_SMStart, E_Init, E_Cycle, E_Wait_Message};// state;
enum S_states{S_SMStart, S_Init, S_Cycle, S_Wait_Message};// state;


int Final(int state)
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
            //LCD_DisplayString(1, "MenuScreen!!!!");
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
        case(Fin_Game_Over):
        {
            //LCD_ClearScreen();
            //LCD_DisplayString(1, "Game Over!");
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
            //LCD_ClearScreen();
            reset = 0;
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
            if(Whole_Flag == 1)
            {
                //Intro_Flag = 0;
                //Start_Screen_Flag = 0;
                //Menu_Flag = 0;
                Whole_Flag = 0;
                //Final();
            }
            else
            {
                state = Fin_Whole;
            }
            
            break;
        }
        case(Fin_Half):
        {
            break;
        }
        case(Fin_Quarter):
        {
            break;
        }
        case(Fin_Eighth):
        {
            break;
        }
        case(Fin_Sixteenth):
        {
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
            break;
        }
        case(Fin_Performance_Wait):
        {
            if(counter <= 120)
            {
                state = Fin_Performance_Wait;
            }
            else
            {
                state = Fin_Game_Over;
                Menu_Flag = 0;
                performance = 0;
                reset = 1;
                //LCD_ClearScreen();
            }
            
            counter++;
            break;
        }
        case(Fin_Game_Over):
        {
            state = Fin_Menu;
            
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

int Intro(int state)
{
    switch(state)
    {
        case(Intro_SMStart):
        {
            state = Intro_Init;
            break;
        }
        case(Intro_Init):
        {
            state = Intro_Stage1;
            break;
        }
        case(Intro_Stage1):
        {
            break;
        }
        case(Intro_Stage2):
        {
            break;
        }
        case(Intro_Stage3):
        {
            break;
        }
        case(Intro_Stage4):
        {
            break;
        }
        case(Intro_Stage5):
        {
            break;
        }
        case(Intro_Stage6):
        {
            break;
        }
        case(Intro_Stage7):
        {
            break;
        }
        case(Intro_Stage8):
        {
            break;
        }
        case(Intro_Stage9):
        {
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
            state = Intro_Init;
            break;
        }
    }
    
    switch(state)
    {
        case(Intro_SMStart):
        {
            break;
        }
        case(Intro_Init):
        {
            count = 0;
            count2 = 20;
            LCD_ClearScreen();
            Intro_Flag = 0;
            break;
        }
        case(Intro_Stage1):
        {
            if((count % 20) == 0)
            {
                LCD_DisplayString(1, "e                              t");
                state = Intro_Stage2;
                count = 0;
            }
            else
            {
                state = Intro_Stage1;
            }
            
            count++;
            break;
        }
        case(Intro_Stage2):
        {
            if((count % 20) == 0)
            {
                LCD_DisplayString(1, "me                            to");
                state = Intro_Stage3;
                count = 0;
            }
            else
            {
                state = Intro_Stage2;
            }
            
            count++;
            break;
        }
        case(Intro_Stage3):
        {
            if((count % 20) == 0)
            {
                LCD_DisplayString(1, "ome                          to ");
                state = Intro_Stage4;
                count = 0;
            }
            else
            {
                state = Intro_Stage3;
            }
            
            count++;
            break;
        }
        case(Intro_Stage4):
        {
            if((count % 20) == 0)
            {
                LCD_DisplayString(1, "come                        to t");
                state = Intro_Stage5;
                count = 0;
            }
            else
            {
                state = Intro_Stage4;
            }
            
            count++;
            break;
        }
        case(Intro_Stage5):
        {
            if((count % 20) == 0)
            {
                LCD_DisplayString(1, "lcome                      to th");
                state = Intro_Stage6;
                count = 0;
            }
            else
            {
                state = Intro_Stage5;
            }
            
            count++;
            break;
        }
        case(Intro_Stage6):
        {
            if((count % 20) == 0)
            {
                LCD_DisplayString(1, "elcome                    to the");
                state = Intro_Stage7;
                count = 0;
            }
            else
            {
                state = Intro_Stage6;
            }
            
            count++;
            break;
        }
        case(Intro_Stage7):
        {
            if((count % 20) == 0)
            {
                LCD_DisplayString(1, "Welcome                  to the");
                state = Intro_Stage8;
                count = 0;
            }
            else
            {
                state = Intro_Stage7;
            }
            
            count++;
            break;
        }
        case(Intro_Stage8):
        {
            if((count % 20) == 0)
            {
                LCD_DisplayString(1, " Welcome                to the");
                state = Intro_Stage9;
                count = 0;
            }
            else
            {
                state = Intro_Stage8;
            }
            
            count++;
            break;
        }
        case(Intro_Stage9):
        {
            if((count % 20) == 0)
            {
                LCD_DisplayString(1, "  Welcome              to the");
                state = Intro_Wait;
                count = 0;
            }
            else
            {
                state = Intro_Stage9;
            }
            
            count++;
            break;
        }
        case(Intro_Wait):
        {
            if(count <= 40)
            {
                
            }
            else
            {
                LCD_ClearScreen();
                state = Intro_Beat_Trainer;
                count = 0;
            }
            
            count++;
            break;
        }
        case(Intro_Beat_Trainer):
        {
            if(count <= 240)
            {
                if((count2 % 20) == 0)
                {
                    LCD_DisplayString(7, "Beat          Trainer!");
                }
                else
                {
                    if((count2 % 39) == 0)
                    {
                        LCD_ClearScreen();
                        count2 = 0;
                    }
                }
                
                count2++;
            }
            else
            {
                state = Intro_Wait2;
                count = 0;
            }
            
            count++;
            break;
        }
        case(Intro_Wait2):
        {
            if(count <= 120)
            {
                
            }
            else
            {
                LCD_ClearScreen();
                Intro_Flag = 1;
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
    
    return state;
}

int Start_Screen(int state)
{
    switch(state)
    {
        case(St_SMStart):
        {
            state = St_Init;
            break;
        }
        case(St_Init):
        {
            state = St_Disp;
            break;
        }
        case(St_Disp):
        {
            state = St_Wait;
            break;
        }
        case(St_Wait):
        {
            state = St_Wait;
            break;
        }
        case(St_Pressed):
        {
            break;
        }
        case(St_Press_Wait):
        {
            break;
        }
        default:
        {
            state = St_Init;
            break;
        }
    }
    
    switch(state)
    {
        case(St_SMStart):
        {
            break;
        }
        case(St_Init):
        {
            LCD_ClearScreen();
            count = 0;
            start_count = 0;
            Start_Screen_Flag = 0;
            break;
        }
        case(St_Disp):
        {
            LCD_DisplayString(3, "Press Start!");
            break;
        }
        case(St_Wait):
        {
            if((start_count % 20) == 0)
            {
                LCD_Cursor(24);
                
                if(count % 2)
                {
                    LCD_Char(0);
                }
                else
                {
                    LCD_Char(1);
                }
                
                if((~PINA & 0x20) == 0x20)
                {
                    LCD_ClearScreen();
                    state = St_Pressed;
                }
                count++;
            }

            start_count++;
            break;
        }
        case(St_Pressed):
        {
            LCD_DisplayString(6, "Button         Pressed!");
            state = St_Press_Wait;
            count = 0;
            break;
        }
        case(St_Press_Wait):
        {
            if((start_count % 20) == 0)
            {
                if(count <= 4)
                {
                    
                }
                else
                {
                    LCD_ClearScreen();
                    Start_Screen_Flag = 1;
                }
                
                count++;
            }

            start_count++;
            break;
        }
        default:
        {
            LCD_ClearScreen();
            LCD_DisplayString(6, "ERROR");
            break;
        }
    }
    
    return state;
}

int Menu(int state)
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
            
            if(read_count % 14 == 0)
            {
                x = ADC_ReadData(3);
                y = ADC_ReadData(4);
                
                if((x >= 3*temp && x < 6*temp) && (y >= 30 && y < 3*temp))
                {
                    
                }
                else if((y < 30))
                {
                    state = M_Whole;
                }
                else if(x >= 3*temp && x < 9*temp)
                {
                    state = M_Performance;
                }
                else
                {
                    state = M_T_Wait;
                }
            }
            
            read_count++;
            break;
        }
        case(M_Whole):
        {
            state = M_W_Wait;
            break;
        }
        case(M_W_Wait):
        {
            if(read_count % 14 == 0)
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
                    state = M_W_Wait;
                }
                
                if((~PINA & 0x20) == 0x20)
                {
                    LCD_Clear();
                    LCD_DisplayString(1, "   Whole Note       Pressed!");
                    state = M_Release;
                    whole = 1;
                    PORTB = 0x01;
                }
            }
            
            read_count++;
            break;
        }
        case(M_Half):
        {
            state = M_H_Wait;
            
            break;
        }
        case(M_H_Wait):
        {
            if(read_count % 14 == 0)
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
                    state = M_H_Wait;
                }
                
                if((~PINA & 0x20) == 0x20)
                {
                    LCD_Clear();
                    LCD_DisplayString(1, "   Half  Note       Pressed!");
                    state = M_Release;
                    half = 1;
                    PORTB = 0x02;
                }
            }
            
            read_count++;
            break;
        }
        case(M_Quarter):
        {
            state = M_Q_Wait;
            break;
        }
        case(M_Q_Wait):
        {
            if(read_count % 14 == 0)
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
                    state = M_Q_Wait;
                }
                
                if((~PINA & 0x20) == 0x20)
                {
                    LCD_Clear();
                    LCD_DisplayString(1, "  Quarter Note      Pressed!");
                    state = M_Release;
                    quarter = 1;
                    PORTB = 0x04;
                }
            }
            
            read_count++;
            break;
        }
        case(M_Eighth):
        {
            state = M_E_Wait;
            break;
        }
        case(M_E_Wait):
        {
            if(read_count % 14 == 0)
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
                    state = M_E_Wait;
                }
                
                if((~PINA & 0x20) == 0x20)
                {
                    LCD_Clear();
                    LCD_DisplayString(1, "  Eighth  Note      Pressed!");
                    state = M_Release;
                    eighth = 1;
                    PORTB = 0x08;
                }
            }
            
            read_count++;
            break;
        }
        case(M_Sixteenth):
        {
            state = M_S_Wait;
            break;
        }
        case(M_S_Wait):
        {
            if(read_count % 14 == 0)
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
                    state = M_S_Wait;
                }
                
                if((~PINA & 0x20) == 0x20)
                {
                    LCD_Clear();
                    LCD_DisplayString(1, " Sixteenth Note     Pressed!");
                    state = M_Release;
                    sixteenth = 1;
                    PORTB = 0x10;
                }
            }
            
            read_count++;
            break;
        }
        case(M_Performance):
        {
            state = M_P_Wait;
            break;
        }
        case(M_P_Wait):
        {
            if(read_count % 14 == 0)
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
                    state = M_P_Wait;
                }
                
                if((~PINA & 0x20) == 0x20)
                {
                    LCD_DisplayString(1, "Performance Mode    Pressed!");
                    state = M_Release;
                    performance = 1;
                    PORTB = 0xFF;
                }
            }
            
            read_count++;
            break;
        }
        case(M_Release):
        {
            if(read_count % 14 == 0)
            {
                if((~PINA & 0x20) == 0x20)
                {
                    state = M_Release;
                }
                else
                {
                    LCD_DisplayString(1, "  Good Shit!!!    Good Luck!!!");
                    state = M_R_Wait;
                }
            }
            
            read_count++;
            break;
        }
        case(M_R_Wait):
        {
            if(read_count % 14 == 0)
            {
                if(count <= 10)
                {
                    
                }
                else
                {
                    Menu_Flag = 1;
                }
                
                count++;
            }
            
            read_count++;
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
            LCD_ClearScreen();
            whole = 0;
            half = 0;
            quarter = 0;
            eighth = 0;
            sixteenth = 0;
            performance = 0;
            count = 0;
            read_count = 0;
            Menu_Flag = 0;
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
        case(M_Release):
        {
            break;
        }
        case(M_R_Wait):
        {
            break;
        }
        default:
        {
            LCD_DisplayString(4, "ERROR!");
            break;
        }
    }
    
    return state;
}

int Whole(int state)
{
    switch(state)
    {
        case(W_SMStart):
        {
            state = W_Init;
            break;
        }
        case(W_Init):
        {
            state = W_Cycle;
            break;
        }
        case(W_Cycle):
        {
            state = W_Cycle;
            break;
        }
        case(W_Wait_Message):
        {
            break;
        }
        default:
        {
            state = W_Init;
            break;
        }
    }
    
    switch(state)
    {
        case(W_SMStart):
        {
            break;
        }
        case(W_Init):
        {
            LCD_ClearScreen();
            Whole_Flag = 0;
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
        case(W_Cycle):
        {
            if((loop % 4) == 0)
            {
                if(count <= 15)
                {
                    transmit_data(W[count]);
                    if((~PINA & 0x20) == 0x20 && transmit_data(W[count]) == 0x0001)
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
                            LCD_Cursor(5);
                            LCD_String("WINNER!!");
                            LCD_Cursor(18);
                            LCD_String("TRY 1/2 NOTES?");
                            state = W_Wait_Message;
                        }
                    }
                    else if((~PINA & 0x20) != 0x20 && transmit_data(W[count]) == 0x0001)
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
                            LCD_Cursor(5);
                            LCD_String("LOSER!!!");
                            LCD_Cursor(20);
                            LCD_String("TRY AGAIN?");
                            state = W_Wait_Message;
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
        case(W_Wait_Message):
        {
            if(wait <= 120)
            {
                
            }
            else
            {
                LCD_ClearScreen();
                LCD_WriteData(Whole_Flag + '0');
                Whole_Flag = 1;
                whole = 0;
                LCD_WriteData(Whole_Flag + '0');
                LCD_WriteData(whole + '0');
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
    
    return state;
}

int Half(int state)
{
    switch(state)
    {
        case(H_SMStart):
        {
            state = H_Init;
            break;
        }
        case(H_Init):
        {
            state = H_Cycle;
            break;
        }
        case(H_Cycle):
        {
            state = H_Cycle;
            break;
        }
        case(H_Wait_Message):
        {
            break;
        }
        default:
        {
            state = H_Init;
            break;
        }
    }
    
    switch(state)
    {
        case(H_SMStart):
        {
            break;
        }
        case(H_Init):
        {
            LCD_ClearScreen();
            count = 0;
            loop = 0;
            score = 0;
            miss = -2;
            pos_place = 0;
            neg_place = 0;
            wait = 0;
            LCD_Cursor(1);
            LCD_String("Hit:");
            LCD_Cursor(17);
            LCD_String("Miss:");
            break;
        }
        case(H_Cycle):
        {
            if((loop % 4) == 0)
            {
                if(count <= 15)
                {
                    transmit_data(W[count]);
                    if((~PINA & 0x20) == 0x20 && (transmit_data(W[count]) == 0x0001 || transmit_data(W[count]) == 0x0100))
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
                            LCD_Cursor(5);
                            LCD_String("WINNER!!");
                            LCD_Cursor(18);
                            LCD_String("TRY 1/4 NOTES?");
                            state = H_Wait_Message;
                        }
                    }
                    else if((~PINA & 0x20) != 0x20 && (transmit_data(W[count]) == 0x0001 || transmit_data(W[count]) == 0x0100))
                    {
                        LCD_Cursor(23);
                        if(miss < 0)
                        {
                            miss++;
                        }
                        else if(miss <= 8)
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
                            LCD_Cursor(5);
                            LCD_String("LOSER!!!");
                            LCD_Cursor(20);
                            LCD_String("TRY AGAIN?");
                            state = H_Wait_Message;
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
        case(H_Wait_Message):
        {
            if(wait <= 120)
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
    
    return state;
}

int Quarter(int state)
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
            LCD_ClearScreen();
            count = 0;
            loop = 0;
            score = 0;
            miss = -4;
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
                    transmit_data(W[count]);
                    if((~PINA & 0x20) == 0x20 && (transmit_data(W[count]) == 0x0001 || transmit_data(W[count]) == 0x0010 || transmit_data(W[count]) == 0x0100 || transmit_data(W[count]) == 0x1000))
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
                            LCD_Cursor(5);
                            LCD_String("WINNER!!");
                            LCD_Cursor(18);
                            LCD_String("TRY 1/8 NOTES?");
                            state = Q_Wait_Message;
                        }
                    }
                    else if((~PINA & 0x20) != 0x20 && (transmit_data(W[count]) == 0x0001 || transmit_data(W[count]) == 0x0010 || transmit_data(W[count]) == 0x0100 || transmit_data(W[count]) == 0x1000))
                    {
                        LCD_Cursor(23);
                        if(miss < 0)
                        {
                            miss++;
                        }
                        else if(miss <= 8)
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
                            LCD_Cursor(5);
                            LCD_String("LOSER!!!");
                            LCD_Cursor(20);
                            LCD_String("TRY AGAIN?");
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
            if(wait <= 120)
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
    
    return state;
}

int Eighth(int state)
{
    switch(state)
    {
        case(E_SMStart):
        {
            state = E_Init;
            break;
        }
        case(E_Init):
        {
            state = E_Cycle;
            break;
        }
        case(E_Cycle):
        {
            state = E_Cycle;
            break;
        }
        case(E_Wait_Message):
        {
            break;
        }
        default:
        {
            state = E_Init;
            break;
        }
    }
    
    switch(state)
    {
        case(E_SMStart):
        {
            break;
        }
        case(E_Init):
        {
            LCD_ClearScreen();
            count = 0;
            loop = 0;
            score = 0;
            miss = -8;
            pos_place = 0;
            neg_place = 0;
            wait = 0;
            LCD_Cursor(1);
            LCD_String("Hit:");
            LCD_Cursor(17);
            LCD_String("Miss:");
            break;
        }
        case(E_Cycle):
        {
            if((loop % 4) == 0)
            {
                if(count <= 15)
                {
                    transmit_data(e[count]);
                    if((~PINA & 0x20) == 0x20 && (transmit_data(e[count]) == 0x0001 || transmit_data(e[count]) == 0x0004 || transmit_data(e[count]) == 0x0010 || transmit_data(e[count]) == 0x0040 ||
                    transmit_data(e[count]) == 0x0100 || transmit_data(e[count]) == 0x0400 || transmit_data(e[count]) == 0x1000 || transmit_data(e[count]) == 0x4000))
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
                            LCD_Cursor(5);
                            LCD_String("WINNER!!");
                            LCD_Cursor(18);
                            LCD_String("TRY 1/16 NOTES??");
                            state = E_Wait_Message;
                        }
                    }
                    else if((~PINA & 0x20) != 0x20 && (transmit_data(e[count]) == 0x0001 || transmit_data(e[count]) == 0x0004 || transmit_data(e[count]) == 0x0010 || transmit_data(e[count]) == 0x0040 ||
                    transmit_data(e[count]) == 0x0100 || transmit_data(e[count]) == 0x0400 || transmit_data(e[count]) == 0x1000 || transmit_data(e[count]) == 0x4000))
                    {
                        LCD_Cursor(23);
                        if(miss < 0)
                        {
                            miss++;
                        }
                        else if(miss <= 8)
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
                            LCD_Cursor(5);
                            LCD_String("LOSER!!!");
                            LCD_Cursor(20);
                            LCD_String("TRY AGAIN?");
                            state = E_Wait_Message;
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
        case(E_Wait_Message):
        {
            if(wait <= 120)
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
    
    return state;
}

int Sixteenth(int state)
{
    switch(state)
    {
        case(S_SMStart):
        {
            state = S_Init;
            break;
        }
        case(S_Init):
        {
            state = S_Cycle;
            break;
        }
        case(S_Cycle):
        {
            state = S_Cycle;
            break;
        }
        case(S_Wait_Message):
        {
            break;
        }
        default:
        {
            state = S_Init;
            break;
        }
    }
    
    switch(state)
    {
        case(S_SMStart):
        {
            break;
        }
        case(S_Init):
        {
            LCD_ClearScreen();
            count = 0;
            loop = 0;
            score = 0;
            miss = -16;
            pos_place = 0;
            neg_place = 0;
            wait = 0;
            LCD_Cursor(1);
            LCD_String("Hit:");
            LCD_Cursor(17);
            LCD_String("Miss:");
            break;
        }
        case(S_Cycle):
        {
            if((loop % 5) == 0)
            {
                if(count <= 15)
                {
                    transmit_data(S[count]);
                    if((~PINA & 0x20) == 0x20 && (transmit_data(S[count]) == 0x0001 || transmit_data(S[count]) == 0x0002 || transmit_data(S[count]) == 0x0004 || transmit_data(S[count]) == 0x0008 ||
                    transmit_data(S[count]) == 0x0010 || transmit_data(S[count]) == 0x0020 || transmit_data(S[count]) == 0x0040 || transmit_data(S[count]) == 0x0080 ||
                    transmit_data(S[count]) == 0x0100 || transmit_data(S[count]) == 0x0200 || transmit_data(S[count]) == 0x0400 || transmit_data(S[count]) == 0x0800 ||
                    transmit_data(S[count]) == 0x1000 || transmit_data(S[count]) == 0x2000 || transmit_data(S[count]) == 0x4000 || transmit_data(S[count]) == 0x4000))
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
                            LCD_Cursor(5);
                            LCD_String("WINNER!!");
                            LCD_Cursor(18);
                            LCD_String("GO PERFORM!!!!!!");
                            state = S_Wait_Message;
                        }
                    }
                    else if((~PINA & 0x20) != 0x20 && (transmit_data(S[count]) == 0x0001 || transmit_data(S[count]) == 0x0002 || transmit_data(S[count]) == 0x0004 || transmit_data(S[count]) == 0x0008 ||
                    transmit_data(S[count]) == 0x0010 || transmit_data(S[count]) == 0x0020 || transmit_data(S[count]) == 0x0040 || transmit_data(S[count]) == 0x0080 ||
                    transmit_data(S[count]) == 0x0100 || transmit_data(S[count]) == 0x0200 || transmit_data(S[count]) == 0x0400 || transmit_data(S[count]) == 0x0800 ||
                    transmit_data(S[count]) == 0x1000 || transmit_data(S[count]) == 0x2000 || transmit_data(S[count]) == 0x4000 || transmit_data(S[count]) == 0x4000))
                    {
                        LCD_Cursor(23);
                        if(miss < 0)
                        {
                            miss++;
                        }
                        else if(miss <= 8)
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
                            LCD_Cursor(5);
                            LCD_String("LOSER!!!");
                            LCD_Cursor(20);
                            LCD_String("TRY AGAIN?");
                            state = S_Wait_Message;
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
        case(S_Wait_Message):
        {
            if(wait <= 120)
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
    unsigned long int Intro_calc = 25;
    unsigned long int Start_calc = 25;
    unsigned long int Menu_calc = 25;

    //Calculating GCD
    unsigned long int tmpGCD = 1;
    tmpGCD = findGCD(Final_calc, Intro_calc);
    tmpGCD = findGCD(tmpGCD, Start_calc);
    tmpGCD = findGCD(tmpGCD, Menu_calc);

    //Greatest common divisor for all tasks or smallest time unit for tasks.
    unsigned long int GCD = tmpGCD;

    //Recalculate GCD periods for scheduler
    unsigned long int Final_period = Final_calc/GCD;
    unsigned long int Intro_period = Intro_calc/GCD;
    unsigned long int Start_period = Start_calc/GCD;
    unsigned long int Menu_period = Menu_calc/GCD;
    //Declare an array of tasks
    static task finale, intro, start, menu;
    task *tasks[] = { &finale, &intro, &start, &menu};
    const unsigned short numTasks = sizeof(tasks)/sizeof(task*);

    // Task 1
    finale.state = -1;//Task initial state.
    finale.period = Final_period;//Task Period.
    finale.elapsedTime = Final_period;//Task current elapsed time.
    finale.TickFct = &Final;//Function pointer for the tick.
    
    intro.state = -1;//Task initial state.
    intro.period = Intro_period;//Task Period.
    intro.elapsedTime = Intro_period;//Task current elapsed time.
    intro.TickFct = &Intro;//Function pointer for the tick.
        
    start.state = -1;//Task initial state.
    start.period = Start_period;//Task Period.
    start.elapsedTime = Start_period;//Task current elapsed time.
    start.TickFct = &Start_Screen;//Function pointer for the tick.
    
    menu.state = -1;//Task initial state.
    menu.period = Menu_period;//Task Period.
    menu.elapsedTime = Menu_period;//Task current elapsed time.
    menu.TickFct = &Menu;//Function pointer for the tick.

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
