#include <msp430.h>

int knipper_delay = 10000;

int main(void)
{
  WDTCTL = WDTPW | WDTHOLD;       // Stop WDT
  PM5CTL0 &= ~LOCKLPM5;           // Disable the GPIO power-on default high-impedance mode
                                  // to activate previously configured port settings

  // Configure GPIO
  P1OUT &= ~0x01;                 // Clear P1.0 output latch for a defined power-on state
  P4DIR |= BIT6;                  // Set P1.0 to output direction

  P4DIR &= ~0x20;                 //Set P4.5 as input
  P4REN |= 0x20;
  P4OUT |= 0x20;

  //P1DIR &= ~0x02;                 //Set P1.1 as input
  P1REN |= 0x02;
  P1OUT |= 0x02;

  

  while(1)
  {
    P4OUT ^= BIT6;                // Toggle LED

    for(int i = knipper_delay; i > 0; i--){
      __delay_cycles(1);
    }
    
    if (((P1IN&0x02)&&!(P4IN&0x20))){
      knipper_delay -= 1000;
    }
    else if ((!(P1IN&0x02)&&(P4IN&0x20))){
      knipper_delay += 1000;
    }
    else if (!((P1IN&0x02)&&(P4IN&0x20))) {
      knipper_delay = 10000;
    }
  }
}
