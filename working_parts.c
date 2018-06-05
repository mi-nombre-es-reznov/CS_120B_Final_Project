// Working Parts

//--------Global Variables----------------------------------------------------
unsigned char count, count2;
//--------End Shared Variables------------------------------------------------

//--------User defined FSMs---------------------------------------------------
//Enumeration of states.
unsigned char count = 0;
unsigned char count, start_count;
unsigned char Intro_Flag;

enum Intro_LCD{Intro_SMStart, Intro_Init, Intro_Stage1, Intro_Stage2, Intro_Stage3,
    Intro_Stage4, Intro_Stage5, Intro_Stage6, Intro_Stage7, Intro_Stage8, Intro_Stage9,
    Intro_Wait, Intro_Beat_Trainer, Intro_Wait2} Intro_state;
enum St_States{St_SMStart, St_Init, St_Disp, St_Van, St_Wait, St_Pressed, St_Press_Wait} St_state;

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