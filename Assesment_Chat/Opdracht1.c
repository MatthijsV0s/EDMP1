
#include <msp430.h>
#include <stdbool.h>

void delay_500ms() {
    __delay_cycles(500000); // 0.5s @ 1 MHz default
}

int main(void)
{
    WDTCTL = WDTPW | WDTHOLD;
        PM5CTL0 &= ~LOCKLPM5; 

    // LED pin setup
    P1DIR |= BIT0;      // P1.0 = groen
    P4DIR |= BIT6;      // P4.5 = rood
    P1OUT &= ~BIT0;
    P4OUT &= ~BIT6;


    bool a[4] = {0,1,1,0};   // patroon rood-groen-groen-rood

    int x = 0;


    // --- LED patroon afspelen ---
    while (x < 4)
    {
        if (a[x] == 1) {     // groen
            P1OUT |= BIT0;
            delay_500ms();
            P1OUT &= ~BIT0;
        } else {             // rood
            P4OUT |= BIT6;
            delay_500ms();
            P4OUT &= ~BIT6;
        }

        delay_500ms();       // pauze
        x++;
    }

    while(1);
}
