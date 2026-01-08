
#include <msp430.h>

/*
  Blink Energy - A sketch to explore the energy used to blink an LED on a MSP430G2 LaunchPad.
  This example code is in the public domain.
*/
// the red LED is on pin 2 of the MSP430G2

int main()
{
    WDTCTL = WDTPW | WDTHOLD;       // Stop WDT

    PM5CTL0 &= ~LOCKLPM5;

    P1DIR = 0xFF;
    P2DIR = 0xFF;
    P3DIR = 0xFF;
    P4DIR = 0xFF;

    P1OUT = 0x00;
    P2OUT = 0x00;
    P3OUT = 0x00;
    P4OUT = 0x00;

    // Klok instellingen
CSCTL0_H = CSKEY >> 8;                      // Unlock CS registers
//CSCTL1 = DCOFSEL_6;                         // Set DCO = 8MHz
CSCTL2 = SELA__VLOCLK | SELS__DCOCLK | SELM__DCOCLK;
//CSCTL3 = DIVA__8 | DIVS__8 | DIVM__8;       // Set all dividers
CSCTL0_H = 0;                               // Lock CS registers

// Configure Timer0_A
TA0CCR0 = 5000;                           // PWM Period CCR0
//TA0CCTL1 = OUTMOD_7;                        // CCR1 reset/set
//TA0CCR1 = 750;                              // CCR1 PWM duty cycle
//TA0CCTL2 = OUTMOD_7;                        // CCR2 reset/set
//TA0CCR2 = 250;                              // CCR2 PWM duty cycle
TA0CTL = TASSEL__ACLK | MC__UP | TACLR;    // SMCLK, up mode, clear TAR
TA0CCTL0 = CCIE;


__bis_SR_register(GIE);             // global interrupt enable
__bis_SR_register(LPM3_bits);          // Enter LPM0
__no_operation();                           // For debugger
  
}

#pragma vector=TIMER0_A0_VECTOR
__interrupt void TA0_CCR0_ISR (void) {
  P1OUT ^= BIT0;
  TA0CTL |= TACLR;
  TA0CCTL0 &= ~CCIFG;
}
