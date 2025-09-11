#include <msp430.h>

unsigned long knipper_delay = 10000;

int main(void)
{
  WDTCTL = WDTPW | WDTHOLD;       // Stop WDT

  // Configure GPIO
  P1OUT &= ~0x01;                 // Clear P1.0 output latch for a defined power-on state
  P1DIR |= 0x01;                  // Set P1.0 to output direction

  P4DIR &= ~0x20;                 //Set P4.5 as input
  P4REN |= 0x20;
  P4OUT |= 0x20;

  P1DIR &= ~0x02;                 //Set P1.1 as input
  P1REN |= 0x02;
  P1OUT |= 0x02;

  PM5CTL0 &= ~LOCKLPM5;           // Disable the GPIO power-on default high-impedance mode
                                  // to activate previously configured port settings

  while(1)
  {
    P1OUT ^= BIT0;                // Toggle LED
    for(int i = 0; i < knipper_delay; i++){
      __delay_cycles(1);
    }
    
    if (!((P1IN&0x02)&&(P4IN&0x20))){
      knipper_delay = 10000;
    }
    else if ((!(P1IN&0x02)&&(P4IN&0x20))){
      knipper_delay += 10;
    }
    else if (((P1IN&0x02)&&!(P4IN&0x20))) {
      knipper_delay -= 10;
    }
  }
}
