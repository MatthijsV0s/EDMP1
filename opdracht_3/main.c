#include <msp430.h>
#include "gpio_lib.h"

volatile int teller = 0;
volatile bool counting = false;

int main(void){
    
    WDTCTL = WDTPW | WDTHOLD;       // Stop WDT

    GPIO_init();

    // Klok instellingen
    CSCTL0_H = CSKEY >> 8;                      // Unlock CS registers
    CSCTL1 = DCOFSEL_0;                         // Set DCO = 1MHz
    CSCTL2 = SELA__LFXTCLK | SELS__DCOCLK | SELM__DCOCLK;
    CSCTL3 = DIVA__16 | DIVS__1 | DIVM__1;       // Set all dividers    ACLK = 2048 Hz
    CSCTL0_H = 0;                               // Lock CS registers 

    // Timer instellingen
    TA1CCR0 = 1000-1;
    TA1CCTL0 = CCIE;                                // Enable CCR0 interrupt
    TA1CTL = TASSEL__SMCLK | MC__STOP | TACLR;    // SMCLK, up mode, clear TAR

    pinSetDir(PORT4, BIT5, 0);  // P4.5 input
    pinSetDir(PORT1, BIT1, 0);  // P1.1 input
    pinConfigInput(PORT4, BIT5, 1, 1, 1, 1);
    pinConfigInput(PORT1, BIT1, 1, 1, 1, 1);

    __bis_SR_register(GIE);             // Globale Interrupt enable

    while(1){
        __bis_SR_register(LPM0_bits);     // LPM0, ADC12_ISR will force exit
    }

}

#pragma vector=TIMER1_A0_VECTOR
__interrupt void TA0_CCR0_ISR (void) {
    teller++;
}

#pragma vector=PORT4_VECTOR
__interrupt void pushbutton4_ISR (void) {
    switch (__even_in_range(P4IV, 0x10)) {
        case 0x00: break;       //none
        case 0x02: break;       //Pin 0
        case 0x04: break;       //Pin 1
        case 0x06: break;       //Pin 2
        case 0x08: break;       //Pin 3
        case 0x0A: break;       //Pin 4
        case 0x0C:              //Pin 5
            if (counting == false) {
                teller = 0;
                pinConfigInput(PORT4, BIT5, 1, 1, 0, 1);
                TA1CTL |= MC__UP | TACLR;       //Start
                counting = true;
            }
            else {
                pinConfigInput(PORT4, BIT5, 1, 1, 1, 1);
                TA1CTL |= MC__STOP ;       //Stop
                teller;
                counting = false;
            }
            
            __bic_SR_register_on_exit(LPM0_bits); // Exit active CPU
            break;       
        case 0x0E: break;       //Pin 6
        case 0x10: break;       //Pin 7
        default: _never_executed();
    }

    
}

#pragma vector=PORT1_VECTOR
__interrupt void pushbutton1_ISR (void) {
    switch (__even_in_range(P1IV, 0x10)) {
        case 0x00: break;       //none
        case 0x02: break;       //Pin 0
        case 0x04:              //Pin 1
            TA1CTL &= ~MC__UP;      //Stop
            __bic_SR_register_on_exit(LPM0_bits); // Exit active CPU
            break;       
        case 0x06: break;       //Pin 2
        case 0x08: break;       //Pin 3
        case 0x0A: break;       //Pin 4
        case 0x0C: break;       //Pin 5
        case 0x0E: break;       //Pin 6
        case 0x10: break;       //Pin 7
        default: _never_executed();
    }

    
}
