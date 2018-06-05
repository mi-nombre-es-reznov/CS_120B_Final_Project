// Working Parts

//--------Global Variables----------------------------------------------------
unsigned char count, count2;
//--------End Shared Variables------------------------------------------------

//--------User defined FSMs---------------------------------------------------
//Enumeration of states.
unsigned char start_count;
unsigned char Intro_Flag, Start_Screen_Flag;
unsigned long x, y = 0, read_count;
unsigned char whole, half, quarter, eighth, sixteenth, performance;

enum Intro_LCD{Intro_SMStart, Intro_Init, Intro_Stage1, Intro_Stage2, Intro_Stage3,
    Intro_Stage4, Intro_Stage5, Intro_Stage6, Intro_Stage7, Intro_Stage8, Intro_Stage9,
    Intro_Wait, Intro_Beat_Trainer, Intro_Wait2} Intro_state;
enum St_States{St_SMStart, St_Init, St_Disp, St_Van, St_Wait, St_Pressed, St_Press_Wait} St_state;
enum M_States {M_SMStart, M_Init, M_X, M_Y, M_Training, M_T_Wait, M_Whole, M_W_Wait, M_Half, M_H_Wait, M_Quarter, M_Q_Wait,
               M_Eighth, M_E_Wait, M_Sixteenth, M_S_Wait, M_Performance, M_P_Wait, M_Release, M_R_Wait} state;

// State Machines
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
                Intro_state = Intro_Stage2;
                count = 0;
            }
            else
            {
                Intro_state = Intro_Stage1;
            }
            
            count++;
            break;
        }
        case(Intro_Stage2):
        {
            if((count % 20) == 0)
            {
                LCD_DisplayString(1, "me                            to");
                Intro_state = Intro_Stage3;
                count = 0;
            }
            else
            {
                Intro_state = Intro_Stage2;
            }
            
            count++;
            break;
        }
        case(Intro_Stage3):
        {
            if((count % 20) == 0)
            {
                LCD_DisplayString(1, "ome                          to ");
                Intro_state = Intro_Stage4;
                count = 0;
            }
            else
            {
                Intro_state = Intro_Stage3;
            }
            
            count++;
            break;
        }
        case(Intro_Stage4):
        {
            if((count % 20) == 0)
            {
                LCD_DisplayString(1, "come                        to t");
                Intro_state = Intro_Stage5;
                count = 0;
            }
            else
            {
                Intro_state = Intro_Stage4;
            }
            
            count++;
            break;
        }
        case(Intro_Stage5):
        {
            if((count % 20) == 0)
            {
                LCD_DisplayString(1, "lcome                      to th");
                Intro_state = Intro_Stage6;
                count = 0;
            }
            else
            {
                Intro_state = Intro_Stage5;
            }
            
            count++;
            break;
        }
        case(Intro_Stage6):
        {
            if((count % 20) == 0)
            {
                LCD_DisplayString(1, "elcome                    to the");
                Intro_state = Intro_Stage7;
                count = 0;
            }
            else
            {
                Intro_state = Intro_Stage6;
            }
            
            count++;
            break;
        }
        case(Intro_Stage7):
        {
            if((count % 20) == 0)
            {
                LCD_DisplayString(1, "Welcome                  to the");
                Intro_state = Intro_Stage8;
                count = 0;
            }
            else
            {
                Intro_state = Intro_Stage7;
            }
            
            count++;
            break;
        }
        case(Intro_Stage8):
        {
            if((count % 20) == 0)
            {
                LCD_DisplayString(1, " Welcome                to the");
                Intro_state = Intro_Stage9;
                count = 0;
            }
            else
            {
                Intro_state = Intro_Stage8;
            }
            
            count++;
            break;
        }
        case(Intro_Stage9):
        {
            if((count % 20) == 0)
            {
                LCD_DisplayString(1, "  Welcome              to the");
                Intro_state = Intro_Wait;
                count = 0;
            }
            else
            {
                Intro_state = Intro_Stage9;
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
                Intro_state = Intro_Beat_Trainer;
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
                Intro_state = Intro_Wait2;
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
}

void Start_Screen()
{
    switch(St_state)
    {
        case(St_SMStart):
        {
            St_state = St_Init;
            break;
        }
        case(St_Init):
        {
            St_state = St_Disp;
            break;
        }
        case(St_Disp):
        {
            St_state = St_Wait;
            break;
        }
        case(St_Wait):
        {
            St_state = St_Wait;
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
            St_state = St_Init;
            break;
        }
    }
    
    switch(St_state)
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
                    St_state = St_Pressed;
                }
                count++;
            }

            start_count++;
            break;
        }
        case(St_Pressed):
        {
            LCD_DisplayString(6, "Button         Pressed!");
            St_state = St_Press_Wait;
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
}

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
                    state = M_Init;
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
            PORTB = 0x00;
            whole = 0;
            half = 0;
            quarter = 0;
            eighth = 0;
            sixteenth = 0;
            performance = 0;
            count = 0;
            read_count = 0;
            LCD_Clear();
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
}