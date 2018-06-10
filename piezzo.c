#include <avr/io.h>
#include "timer.h"

void ADC_init() {
    ADCSRA |= (1 << ADEN) | (1 << ADSC) | (1 << ADATE);
    // ADEN: setting this bit enables analog-to-digital conversion.
    // ADSC: setting this bit starts the first conversion.
    // ADATE: setting this bit enables auto-triggering. Since we are
    //        in Free Running Mode, a new conversion will trigger whenever
    //        the previous conversion completes.
}

        
int main(void)
{
    DDRB = 0xFF; PORTB = 0x00;
    DDRA = 0x00; PORTA = 0xFF;
    
    TimerSet(500);
    TimerOn();
    
    ADC_init();
    unsigned short temp;
    /* Replace with your application code */
    while (1) 
    {
        temp = ADC;
        
        if((temp <= 130 && temp >= 70) && PORTB == 0x00)
        {
            PORTB = 0xFF;
        }
        else if((temp <= 130 && temp >= 70) && PORTB == 0xFF)
        {
            PORTB = 0x00;
        }
    }
    
    return 0;
}v