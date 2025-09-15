#include <msp430.h>

int main(void)
{
WDTCTL = WDTPW | WDTHOLD;                   // Stop WDT

// Configure GPIO
P1DIR |= BIT0 | BIT1;                       // P1.0 and P1.1 output
P1SEL0 |= BIT0 | BIT1;                      // P1.0 and P1.1 options
//select

PM5CTL0 &= ~LOCKLPM5;

// Klok instellingen
CSCTL0_H = CSKEY >> 8;                      // Unlock CS registers
CSCTL1 = DCOFSEL_6;                         // Set DCO = 8MHz
CSCTL2 = SELA__VLOCLK | SELS__DCOCLK | SELM__DCOCLK;
CSCTL3 = DIVA__8 | DIVS__8 | DIVM__8;       // Set all dividers
CSCTL0_H = 0;                               // Lock CS registers

// Configure Timer0_A
TA0CCR0 = 1000-1;                           // PWM Period CCR0
TA0CCTL1 = OUTMOD_7;                        // CCR1 reset/set
TA0CCR1 = 750;                              // CCR1 PWM duty cycle
TA0CCTL2 = OUTMOD_7;                        // CCR2 reset/set
TA0CCR2 = 250;                              // CCR2 PWM duty cycle
TA0CTL = TASSEL__SMCLK | MC__UP | TACLR;    // SMCLK, up mode, clear TAR
while (1) {
    TA0CCR1 += 10;
    __delay_cycles(100000);
    if (TA0CCR1 == 1000) {
        TA0CCR1 = 0;
    }
}

// Sleep and do nothing
__bis_SR_register(LPM0_bits);          // Enter LPM0
__no_operation();                           // For debugger
}
