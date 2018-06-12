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
unsigned char count, count2, start_count, x, y = 0, read_count;
unsigned char Intro_Flag, Start_Screen_Flag, Menu_Flag;
unsigned char whole, half, quarter, eighth, sixteenth, performance;
unsigned char loop, wait, score, pos_place, neg_place;
signed char miss;

// ******************************************************************************************************************************
// *                                          Arrays that will make that LED game operate                                       *
// ******************************************************************************************************************************
short W[] = {0x0001, 0x0000, 0x0000, 0x0000, 0x0010, 0x0000, 0x0000, 0x0000, 0x0100, 0x0000, 0x0000, 0x0000, 0x1000, 0x0000,
0x0000, 0x0000};

short e[] = {0x0001, 0x0000, 0x0004, 0x0000, 0x0010, 0x0000, 0x0040, 0x0000, 0x0100, 0x0000, 0x0400, 0x0000, 0x1000, 0x0000,
0x4000, 0x0000};

short S[] = {0x0001, 0x0002, 0x0004, 0x0008, 0x0010, 0x0020, 0x0040, 0x0080, 0x0100, 0x0200, 0x0400, 0x0800, 0x1000, 0x2000,
0x4000, 0x8000};

// ****************************************************************************************************************************
// *                                                   Enumeration Values                                                     *
// ****************************************************************************************************************************
enum Intro_LCD{Intro_SMStart, Intro_Init, Intro_Stage1, Intro_Stage2, Intro_Stage3,
    Intro_Stage4, Intro_Stage5, Intro_Stage6, Intro_Stage7, Intro_Stage8, Intro_Stage9,
Intro_Wait, Intro_Beat_Trainer, Intro_Wait2} Intro_state;
enum St_States{St_SMStart, St_Init, St_Disp, St_Van, St_Wait, St_Pressed, St_Press_Wait} St_state;
enum M_States {M_SMStart, M_Init, M_X, M_Y, M_Training, M_T_Wait, M_Whole, M_W_Wait, M_Half, M_H_Wait, M_Quarter, M_Q_Wait,
M_Eighth, M_E_Wait, M_Sixteenth, M_S_Wait, M_Performance, M_P_Wait, M_Release, M_R_Wait} Menu_state;
enum W_states{W_SMStart, W_Init, W_Cycle, W_Wait_Message} Whole_state;
enum H_States{H_SMStart, H_Init, H_Cycle, H_Wait_Message} Half_state;
enum Q_states{Q_SMStart, Q_Init, Q_Cycle, Q_Wait_Message} Quarter_state;
enum E_states{E_SMStart, E_Init, E_Cycle, E_Wait_Message} Eighth_state;
enum S_states{S_SMStart, S_Init, S_Cycle, S_Wait_Message} Sixteenth_state;

// *******************************************************************************************
// *                                       State Machines                                    *
// *******************************************************************************************
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
            if(count <= 120)
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
    
    switch(Menu_state)
    {
        case(M_SMStart):
        {
            Menu_state = M_Init;
            break;
        }
        case(M_Init):
        {
            Menu_state = M_Training;
            break;
        }
        case(M_Training):
        {
            Menu_state = M_T_Wait;

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
                    Menu_state = M_Whole;
                }
                else if(x >= 3*temp && x < 9*temp)
                {
                    Menu_state = M_Performance;
                }
                else
                {
                    Menu_state = M_T_Wait;
                }
            }
            
            read_count++;
            break;
        }
        case(M_Whole):
        {
            Menu_state = M_W_Wait;
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
                    Menu_state = M_Half;
                }
                else if(y >= 4*temp && y < 6*temp)
                {
                    Menu_state = M_Training;
                }
                else
                {
                    Menu_state = M_W_Wait;
                }
                
                if((~PINA & 0x20) == 0x20)
                {
                    LCD_Clear();
                    LCD_DisplayString(1, "   Whole Note       Pressed!");
                    Menu_state = M_Release;
                    whole = 1;
                    //PORTB = 0x01;
                }
            }
            
            read_count++;
            break;
        }
        case(M_Half):
        {
            Menu_state = M_H_Wait;
            
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
                    Menu_state = M_Quarter;
                }
                else if(y >= 4*temp && y < 6*temp) // Right
                {
                    Menu_state = M_Whole;
                }
                else
                {
                    Menu_state = M_H_Wait;
                }
                
                if((~PINA & 0x20) == 0x20)
                {
                    LCD_Clear();
                    LCD_DisplayString(1, "   Half  Note       Pressed!");
                    Menu_state = M_Release;
                    half = 1;
                    //PORTB = 0x02;
                }
            }
            
            read_count++;
            break;
        }
        case(M_Quarter):
        {
            Menu_state = M_Q_Wait;
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
                    Menu_state = M_Eighth;
                }
                else if(y >= 4*temp && y < 6*temp) // Down
                {
                    Menu_state = M_Half;
                }
                else
                {
                    Menu_state = M_Q_Wait;
                }
                
                if((~PINA & 0x20) == 0x20)
                {
                    LCD_Clear();
                    LCD_DisplayString(1, "  Quarter Note      Pressed!");
                    Menu_state = M_Release;
                    quarter = 1;
                    //PORTB = 0x04;
                }
            }
            
            read_count++;
            break;
        }
        case(M_Eighth):
        {
            Menu_state = M_E_Wait;
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
                    Menu_state = M_Sixteenth;
                }
                else if(y >= 4*temp && y < 6*temp) // Down
                {
                    Menu_state = M_Quarter;
                }
                else
                {
                    Menu_state = M_E_Wait;
                }
                
                if((~PINA & 0x20) == 0x20)
                {
                    LCD_Clear();
                    LCD_DisplayString(1, "  Eighth  Note      Pressed!");
                    Menu_state = M_Release;
                    eighth = 1;
                    //PORTB = 0x08;
                }
            }
            
            read_count++;
            break;
        }
        case(M_Sixteenth):
        {
            Menu_state = M_S_Wait;
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
                    Menu_state = M_Eighth;
                }
                else
                {
                    Menu_state = M_S_Wait;
                }
                
                if((~PINA & 0x20) == 0x20)
                {
                    LCD_Clear();
                    LCD_DisplayString(1, " Sixteenth Note     Pressed!");
                    Menu_state = M_Release;
                    sixteenth = 1;
                    //PORTB = 0x10;
                }
            }
            
            read_count++;
            break;
        }
        case(M_Performance):
        {
            Menu_state = M_P_Wait;
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
                    Menu_state = M_Training;
                }
                else
                {
                    Menu_state = M_P_Wait;
                }
                
                if((~PINA & 0x20) == 0x20)
                {
                    LCD_DisplayString(1, "Performance Mode    Pressed!");
                    Menu_state = M_Release;
                    performance = 1;
                    //PORTB = 0xFF;
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
                    Menu_state = M_Release;
                }
                else
                {
                    LCD_ClearScreen();
                    LCD_Cursor(1);
                    LCD_Char(7);
                    LCD_Cursor(3);
                    LCD_String("Good Choice!");
                    LCD_Cursor(16);
                    LCD_Char(7);
                    LCD_Cursor(18);
                    LCD_Char(7);
                    LCD_Cursor(20);
                    LCD_String("Good Luck!");
                    LCD_Cursor(31);
                    LCD_Char(7);
                    Menu_state = M_R_Wait;
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
                    Menu_state = M_SMStart;
                }
                
                count++;
            }
            
            read_count++;
            break;
        }
        default:
        {
            Menu_state = M_Init;
            break;
        }
    }
    
    switch(Menu_state)
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
}

void Whole()
{
    switch(Whole_state)
    {
        case(W_SMStart):
        {
            Whole_state = W_Init;
            break;
        }
        case(W_Init):
        {
            Whole_state = W_Cycle;
            break;
        }
        case(W_Cycle):
        {
            Whole_state = W_Cycle;
            break;
        }
        case(W_Wait_Message):
        {
            break;
        }
        default:
        {
            Whole_state = W_Init;
            break;
        }
    }
    
    switch(Whole_state)
    {
        case(W_SMStart):
        {
            break;
        }
        case(W_Init):
        {
            LCD_ClearScreen();
            whole = 1;
            count = 0;
            loop = 0;
            score = 0;
            miss = -1;
            pos_place = 0;
            neg_place = 0;
            wait = 0;
            LCD_Cursor(1);
            LCD_String("Hit:");
            LCD_Cursor(6);
            LCD_WriteData('0');
            LCD_Cursor(17);
            LCD_String("Miss:");
            LCD_Cursor(23);
            LCD_WriteData('0');
            break;
        }
        case(W_Cycle):
        {
            if((loop % 4) == 0)
            {
                if(count <= 15)
                {
                    transmit_data(W[count]);
                    if((~PINB & 0x01) == 0x01 && transmit_data(W[count]) == 0x0001)
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
                            Whole_state = W_Wait_Message;
                        }
                    }
                    else if((~PINB & 0x01) != 0x01 && transmit_data(W[count]) == 0x0001)
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
                            Whole_state = W_Wait_Message;
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
                whole = 0;
                Whole_state = W_SMStart;
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
}

void Half()
{
    switch(Half_state)
    {
        case(H_SMStart):
        {
            Half_state = H_Init;
            break;
        }
        case(H_Init):
        {
            Half_state = H_Cycle;
            break;
        }
        case(H_Cycle):
        {
            Half_state = H_Cycle;
            break;
        }
        case(H_Wait_Message):
        {
            break;
        }
        default:
        {
            Half_state = H_Init;
            break;
        }
    }
    
    switch(Half_state)
    {
        case(H_SMStart):
        {
            break;
        }
        case(H_Init):
        {
            LCD_ClearScreen();
            half = 1;
            count = 0;
            loop = 0;
            score = 0;
            miss = -2;
            pos_place = 0;
            neg_place = 0;
            wait = 0;
            LCD_Cursor(1);
            LCD_String("Hit:");
            LCD_Cursor(6);
            LCD_WriteData('0');
            LCD_Cursor(17);
            LCD_String("Miss:");
            LCD_Cursor(23);
            LCD_WriteData('0');
            break;
        }
        case(H_Cycle):
        {
            if((loop % 4) == 0)
            {
                if(count <= 15)
                {
                    transmit_data(W[count]);
                    if((~PINB & 0x01) == 0x01 && (transmit_data(W[count]) == 0x0001 || transmit_data(W[count]) == 0x0100))
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
                            Half_state = H_Wait_Message;
                        }
                    }
                    else if((~PINB & 0x01) != 0x01 && (transmit_data(W[count]) == 0x0001 || transmit_data(W[count]) == 0x0100))
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
                            Half_state = H_Wait_Message;
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
                half = 0;
                Half_state = H_SMStart;
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
}

void Quarter()
{
    switch(Quarter_state)
    {
        case(Q_SMStart):
        {
            Quarter_state = Q_Init;
            break;
        }
        case(Q_Init):
        {
            Quarter_state = Q_Cycle;
            break;
        }
        case(Q_Cycle):
        {
            Quarter_state = Q_Cycle;
            break;
        }
        case(Q_Wait_Message):
        {
            break;
        }
        default:
        {
            Quarter_state = Q_Init;
            break;
        }
    }
    
    switch(Quarter_state)
    {
        case(Q_SMStart):
        {
            break;
        }
        case(Q_Init):
        {
            LCD_ClearScreen();
            quarter = 1;
            count = 0;
            loop = 0;
            score = 0;
            miss = -4;
            pos_place = 0;
            neg_place = 0;
            wait = 0;
            LCD_Cursor(1);
            LCD_String("Hit:");
            LCD_Cursor(6);
            LCD_WriteData('0');
            LCD_Cursor(17);
            LCD_String("Miss:");
            LCD_Cursor(23);
            LCD_WriteData('0');
            break;
        }
        case(Q_Cycle):
        {
            if((loop % 4) == 0)
            {
                if(count <= 15)
                {
                    transmit_data(W[count]);
                    if((~PINB & 0x01) == 0x01 && (transmit_data(W[count]) == 0x0001 || transmit_data(W[count]) == 0x0010 || transmit_data(W[count]) == 0x0100 || transmit_data(W[count]) == 0x1000))
                    {
                        LCD_Cursor(6);
                        if(score <= 8)
                        {
                            score++;
                            LCD_Cursor(6);
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
                        else if(score >= 19 && score <= 28)
                        {
                            if(score == 19)
                            {
                                pos_place = 0;
                            }
                            
                            LCD_Cursor(6);
                            LCD_String("2");
                            LCD_Cursor(7);
                            LCD_WriteData(pos_place + '0');
                            pos_place++;
                            score++;                           
                        }
                        else if(score >= 29)
                        {
                            LCD_ClearScreen();
                            LCD_Cursor(5);
                            LCD_String("WINNER!!");
                            LCD_Cursor(18);
                            LCD_String("TRY 1/8 NOTES?");
                            Quarter_state = Q_Wait_Message;
                        }
                    }
                    else if((~PINB & 0x01) != 0x01 && (transmit_data(W[count]) == 0x0001 || transmit_data(W[count]) == 0x0010 || transmit_data(W[count]) == 0x0100 || transmit_data(W[count]) == 0x1000))
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
                        else if(miss >= 19 && miss <= 28)
                        {                
                            if(miss == 19)
                            {
                                neg_place = 0;
                            }       
                                                       
                            LCD_Cursor(23);
                            LCD_String("2");
                            LCD_Cursor(24);
                            LCD_WriteData(neg_place + '0');
                            neg_place++;
                            miss++;                         
                        }
                        else if(miss >= 29)
                        {
                            LCD_ClearScreen();
                            LCD_Cursor(5);
                            LCD_String("LOSER!!!");
                            LCD_Cursor(20);
                            LCD_String("TRY AGAIN?");
                            Quarter_state = Q_Wait_Message;
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
                quarter = 0;
                Quarter_state = Q_SMStart;
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
}

void Eighth()
{
    switch(Eighth_state)
    {
        case(E_SMStart):
        {
            Eighth_state = E_Init;
            break;
        }
        case(E_Init):
        {
            Eighth_state = E_Cycle;
            break;
        }
        case(E_Cycle):
        {
            Eighth_state = E_Cycle;
            break;
        }
        case(E_Wait_Message):
        {
            break;
        }
        default:
        {
            Eighth_state = E_Init;
            break;
        }
    }
    
    switch(Eighth_state)
    {
        case(E_SMStart):
        {
            break;
        }
        case(E_Init):
        {
            LCD_ClearScreen();
            eighth = 1;
            count = 0;
            loop = 0;
            score = 0;
            miss = -8;
            pos_place = 0;
            neg_place = 0;
            wait = 0;
            LCD_Cursor(1);
            LCD_String("Hit:");
            LCD_Cursor(6);
            LCD_WriteData('0');
            LCD_Cursor(17);
            LCD_String("Miss:");
            LCD_Cursor(23);
            LCD_WriteData('0');
            break;
        }
        case(E_Cycle):
        {
            if((loop % 4) == 0)
            {
                if(count <= 15)
                {
                    transmit_data(e[count]);
                    if((~PINB & 0x01) == 0x01 && (transmit_data(e[count]) == 0x0001 || transmit_data(e[count]) == 0x0004 || transmit_data(e[count]) == 0x0010 || transmit_data(e[count]) == 0x0040 ||
                    transmit_data(e[count]) == 0x0100 || transmit_data(e[count]) == 0x0400 || transmit_data(e[count]) == 0x1000 || transmit_data(e[count]) == 0x4000))
                    {
                        LCD_Cursor(6);
                        if(score <= 8)
                        {
                            score++;
                            LCD_Cursor(6);
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
                        else if(score >= 19 && score <= 28)
                        {
                            if(score == 19)
                            {
                                pos_place = 0;
                            }
                            
                            LCD_Cursor(6);
                            LCD_String("2");
                            LCD_Cursor(7);
                            LCD_WriteData(pos_place + '0');
                            pos_place++;
                            score++;
                        }
                        else if(score >= 29 && score <= 38)
                        {
                            if(score == 29)
                            {
                                pos_place = 0;
                            }
                            
                            LCD_Cursor(6);
                            LCD_String("3");
                            LCD_Cursor(7);
                            LCD_WriteData(pos_place + '0');
                            pos_place++;
                            score++;
                        }
                        else if(score >= 39 && score <= 48)
                        {
                            if(score == 39)
                            {
                                pos_place = 0;
                            }
                            
                            LCD_Cursor(6);
                            LCD_String("4");
                            LCD_Cursor(7);
                            LCD_WriteData(pos_place + '0');
                            pos_place++;
                            score++;
                        }
                        else if(score >= 49 && score <= 58)
                        {
                            if(score == 49)
                            {
                                pos_place = 0;
                            }
                            
                            LCD_Cursor(6);
                            LCD_String("5");
                            LCD_Cursor(7);
                            LCD_WriteData(pos_place + '0');
                            pos_place++;
                            score++;
                        }
                        else if(score >= 59)
                        {
                            LCD_ClearScreen();
                            LCD_Cursor(5);
                            LCD_String("WINNER!!");
                            LCD_Cursor(18);
                            LCD_String("TRY 1/16 NOTES??");
                            Eighth_state = E_Wait_Message;
                        }
                    }
                    else if((~PINB & 0x01) != 0x01 && (transmit_data(e[count]) == 0x0001 || transmit_data(e[count]) == 0x0004 || transmit_data(e[count]) == 0x0010 || transmit_data(e[count]) == 0x0040 ||
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
                        else if(miss >= 19 && miss <= 28)
                        {
                            if(miss == 19)
                            {
                                neg_place = 0;
                            }
                            
                            LCD_Cursor(23);
                            LCD_String("2");
                            LCD_Cursor(24);
                            LCD_WriteData(neg_place + '0');
                            neg_place++;
                            miss++;
                        }
                        else if(miss >= 29 && miss <= 38)
                        {
                            if(miss == 29)
                            {
                                neg_place = 0;
                            }
                            
                            LCD_Cursor(23);
                            LCD_String("3");
                            LCD_Cursor(24);
                            LCD_WriteData(neg_place + '0');
                            neg_place++;
                            miss++;
                        }
                        else if(miss >= 39 && miss <= 48)
                        {
                            if(miss == 39)
                            {
                                neg_place = 0;
                            }
                            
                            LCD_Cursor(23);
                            LCD_String("4");
                            LCD_Cursor(24);
                            LCD_WriteData(neg_place + '0');
                            neg_place++;
                            miss++;
                        }
                        else if(miss >= 49 && miss <= 58)
                        {
                            if(miss == 49)
                            {
                                neg_place = 0;
                            }
                            
                            LCD_Cursor(23);
                            LCD_String("5");
                            LCD_Cursor(24);
                            LCD_WriteData(neg_place + '0');
                            neg_place++;
                            miss++;
                        }
                        else if(miss >= 59)
                        {                             
                             LCD_ClearScreen();
                             LCD_Cursor(5);
                             LCD_String("LOSER!!!");
                             LCD_Cursor(20);
                             LCD_String("TRY AGAIN?");
                             Eighth_state = E_Wait_Message;
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
                eighth = 0;
                Eighth_state = E_SMStart;
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
}

void Sixteenth()
{
    switch(Sixteenth_state)
    {
        case(S_SMStart):
        {
            Sixteenth_state = S_Init;
            break;
        }
        case(S_Init):
        {
            Sixteenth_state = S_Cycle;
            break;
        }
        case(S_Cycle):
        {
            Sixteenth_state = S_Cycle;
            break;
        }
        case(S_Wait_Message):
        {
            break;
        }
        default:
        {
            Sixteenth_state = S_Init;
            break;
        }
    }
    
    switch(Sixteenth_state)
    {
        case(S_SMStart):
        {
            break;
        }
        case(S_Init):
        {
            LCD_ClearScreen();
            sixteenth = 1;
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
                    if((~PINB & 0x01) == 0x01 && (transmit_data(S[count]) == 0x0001 || transmit_data(S[count]) == 0x0002 || transmit_data(S[count]) == 0x0004 || transmit_data(S[count]) == 0x0008 ||
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
                        else if(score >= 19 && score <= 28)
                        {
                            if(score == 19)
                            {
                                pos_place = 0;
                            }
                            
                            LCD_Cursor(6);
                            LCD_String("2");
                            LCD_Cursor(7);
                            LCD_WriteData(pos_place + '0');
                            pos_place++;
                            score++;
                        }
                        else if(score >= 29 && score <= 38)
                        {
                            if(score == 29)
                            {
                                pos_place = 0;
                            }
                            
                            LCD_Cursor(6);
                            LCD_String("3");
                            LCD_Cursor(7);
                            LCD_WriteData(pos_place + '0');
                            pos_place++;
                            score++;
                        }
                        else if(score >= 39 && score <= 48)
                        {
                            if(score == 39)
                            {
                                pos_place = 0;
                            }
                            
                            LCD_Cursor(6);
                            LCD_String("4");
                            LCD_Cursor(7);
                            LCD_WriteData(pos_place + '0');
                            pos_place++;
                            score++;
                        }
                        else if(score >= 49 && score <= 58)
                        {
                            if(score == 49)
                            {
                                pos_place = 0;
                            }
                            
                            LCD_Cursor(6);
                            LCD_String("5");
                            LCD_Cursor(7);
                            LCD_WriteData(pos_place + '0');
                            pos_place++;
                            score++;
                        }
                        else if(score >= 59 && score <= 68)
                        {
                            if(score == 59)
                            {
                                pos_place = 0;
                            }
                            
                            LCD_Cursor(6);
                            LCD_String("6");
                            LCD_Cursor(7);
                            LCD_WriteData(pos_place + '0');
                            pos_place++;
                            score++;
                        }
                        else if(score >= 69 && score <= 78)
                        {
                            if(score == 69)
                            {
                                pos_place = 0;
                            }
                            
                            LCD_Cursor(6);
                            LCD_String("7");
                            LCD_Cursor(7);
                            LCD_WriteData(pos_place + '0');
                            pos_place++;
                            score++;
                        }
                        else if(score >= 79 && score <= 88)
                        {
                            if(score == 79)
                            {
                                pos_place = 0;
                            }
                            
                            LCD_Cursor(6);
                            LCD_String("8");
                            LCD_Cursor(7);
                            LCD_WriteData(pos_place + '0');
                            pos_place++;
                            score++;
                        }
                        else if(score >= 89 && score <= 98)
                        {
                            if(score == 89)
                            {
                                pos_place = 0;
                            }
                            
                            LCD_Cursor(6);
                            LCD_String("9");
                            LCD_Cursor(7);
                            LCD_WriteData(pos_place + '0');
                            pos_place++;
                            score++;
                        }
                        else if(score >= 99)
                        {
                            LCD_ClearScreen();
                            LCD_Cursor(5);
                            LCD_String("WINNER!!");
                            LCD_Cursor(18);
                            LCD_String("GO PERFORM!!!!!!");
                            Sixteenth_state = S_Wait_Message;
                        }
                    }
                    else if((~PINB & 0x01) != 0x01 && (transmit_data(S[count]) == 0x0001 || transmit_data(S[count]) == 0x0002 || transmit_data(S[count]) == 0x0004 || transmit_data(S[count]) == 0x0008 ||
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
                        else if(miss >= 19 && miss <= 28)
                        {
                            if(miss == 19)
                            {
                                neg_place = 0;
                            }
                            
                            LCD_Cursor(23);
                            LCD_String("2");
                            LCD_Cursor(24);
                            LCD_WriteData(neg_place + '0');
                            neg_place++;
                            miss++;
                        }
                        else if(miss >= 29 && miss <= 38)
                        {
                            if(miss == 29)
                            {
                                neg_place = 0;
                            }
                            
                            LCD_Cursor(23);
                            LCD_String("3");
                            LCD_Cursor(24);
                            LCD_WriteData(neg_place + '0');
                            neg_place++;
                            miss++;
                        }
                        else if(miss >= 39 && miss <= 48)
                        {
                            if(miss == 39)
                            {
                                neg_place = 0;
                            }
                            
                            LCD_Cursor(23);
                            LCD_String("4");
                            LCD_Cursor(24);
                            LCD_WriteData(neg_place + '0');
                            neg_place++;
                            miss++;
                        }
                        else if(miss >= 49 && miss <= 58)
                        {
                            if(miss == 49)
                            {
                                neg_place = 0;
                            }
                            
                            LCD_Cursor(23);
                            LCD_String("5");
                            LCD_Cursor(24);
                            LCD_WriteData(neg_place + '0');
                            neg_place++;
                            miss++;
                        }
                        else if(miss >= 59 && miss <= 68)
                        {
                            if(miss == 59)
                            {
                                neg_place = 0;
                            }
                            
                            LCD_Cursor(23);
                            LCD_String("6");
                            LCD_Cursor(24);
                            LCD_WriteData(neg_place + '0');
                            neg_place++;
                            miss++;
                        }
                        else if(miss >= 69 && miss <= 78)
                        {
                            if(miss == 69)
                            {
                                neg_place = 0;
                            }
                            
                            LCD_Cursor(23);
                            LCD_String("7");
                            LCD_Cursor(24);
                            LCD_WriteData(neg_place + '0');
                            neg_place++;
                            miss++;
                        }
                        else if(miss >= 79 && miss <= 88)
                        {
                            if(miss == 79)
                            {
                                neg_place = 0;
                            }
                            
                            LCD_Cursor(23);
                            LCD_String("8");
                            LCD_Cursor(24);
                            LCD_WriteData(neg_place + '0');
                            neg_place++;
                            miss++;
                        }
                        else if(miss >= 89 && miss <= 98)
                        {
                            if(miss == 89)
                            {
                                neg_place = 0;
                            }
                            
                            LCD_Cursor(23);
                            LCD_String("9");
                            LCD_Cursor(24);
                            LCD_WriteData(neg_place + '0');
                            neg_place++;
                            miss++;
                        }                        
                        else if(miss >= 99)
                        {
                            LCD_ClearScreen();
                            LCD_Cursor(5);
                            LCD_String("LOSER!!!");
                            LCD_Cursor(20);
                            LCD_String("TRY AGAIN?");
                            Sixteenth_state = S_Wait_Message;
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
                sixteenth = 0;
                Sixteenth_state = S_SMStart;
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
}