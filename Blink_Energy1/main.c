
#include "driverlib.h"

/*
  Blink Energy - A sketch to explore the energy used to blink an LED on a MSP430G2 LaunchPad.
  This example code is in the public domain.
*/
// the red LED is on pin 2 of the MSP430G2

int main()
{
    WDTCTL = WDTPW | WDTHOLD;       // Stop WDT

    PM5CTL0 &= ~LOCKLPM5;

    P1DIR |= BIT0;

    while (true){
        P1OUT |= BIT0;
        __delay_cycles(5000);
        P1OUT &= ~BIT0;
        __delay_cycles(95000);
    }
  
}