

#include <msp430.h>
#include <stdbool.h>

#define knop1 BIT5     // rood knopje op P4.5
#define knop2 BIT1     // groen knopje op P1.1

void delay_500ms() {
    __delay_cycles(500000);
}

int main(void)
{
    WDTCTL = WDTPW | WDTHOLD;
    PM5CTL0 &= ~LOCKLPM5;

    // LED pin setup
    P1DIR |= BIT0;      // groen LED
    P4DIR |= BIT6;      // rood LED
    P1OUT &= ~BIT0;
    P4OUT &= ~BIT6;

    // knop P4.5 input
    P4DIR &= ~knop1;
    P4REN |= knop1;
    P4OUT |= knop1;

    // knop P1.1 input
    P1DIR &= ~knop2;
    P1REN |= knop2;
    P1OUT |= knop2;

    bool a[4] = {0,1,1,0};   // patroon rood-groen-groen-rood
    bool b[4];

    int x = 0;
    int y =0;
    int z=0;
    // --- LED patroon afspelen ---
    for (x = 0; x < 4; x++)
    {
        if (a[x] == 1) { // groen
            P1OUT |= BIT0;
            delay_500ms();
            P1OUT &= ~BIT0;
        } else { // rood
            P4OUT |= BIT6;
            delay_500ms();
            P4OUT &= ~BIT6;
        }
        delay_500ms(); // pauze
    }

    // --- speler input ---
    for (y = 0; y < 4; y++)
    {
        // wachten tot knop wordt ingedrukt
        while ((P4IN & knop1) && (P1IN & knop2));
        {

        }
     
        if (!(P4IN & knop1)) 
        {
            b[y] = 0;               // rood knop
            while (!(P4IN & knop1)); // wacht tot losgelaten
            {

            }
        }

        if (!(P1IN & knop2)) 
        {
            b[y] = 1;               // groen knop
            while (!(P1IN & knop2));
            {

            }
        }

        delay_500ms(); // debounce
    }

    // --- check resultaat ---
    for (z = 0; z < 4; z++)
    {
        if (a[z] != b[z]) {
            P4OUT |= BIT6;   // fout → rood
            while(1);
        }
    }

    // alles is goed
    P1OUT |= BIT0;           // groen
    while(1);
}
