#include <msp430.h>
#include "gpio_lib.h"

void setFrequency(uint8_t f){
    int freq;
    if (f==0) {
        freq = 0;
    }
    else {
        freq = 4096/f;
        
    }
    TA0CCR0 = freq-1;
    TA0CCR1 = freq/2;
    
}

void main (void)
{
    WDTCTL = WDTPW | WDTHOLD;       // Stop WDT

    GPIO_init();

    // Klok instellingen
    CSCTL0_H = CSKEY >> 8;                      // Unlock CS registers
    CSCTL1 = DCOFSEL_0;                         // Set DCO = 1MHz
    CSCTL2 = SELA__LFXTCLK | SELS__DCOCLK | SELM__DCOCLK;
    CSCTL3 = DIVA__8 | DIVS__1 | DIVM__1;       // Set all dividers    ACLK = 2048*2 Hz
    CSCTL0_H = 0;                               // Lock CS registers 

    // Timer instellingen
    //TA0CCR0 = 1024-1;
    //TA0CCR1 = 1024/2;
    TA0CCTL1 = OUTMOD_7;                        // CCR1 reset/set
    //TA0CCTL0 = CCIE;                                // Enable CCR0 interrupt
    TA0CTL = TASSEL__ACLK | MC__UP | TACLR;    // SMCLK, up mode, clear TAR

    pinSetDir(PORT1, BIT0, true);
    pinConfigFunction(PORT1, BIT0, primary);

    //pinSetDir(PORT4, BIT5, 0);  // P4.5 input
    //pinSetDir(PORT1, BIT1, 0);  // P1.1 input
    //pinConfigInput(PORT4, BIT5, 1, 1, 1, 1);
    //pinConfigInput(PORT1, BIT1, 1, 1, 1, 1);

    //__bis_SR_register(GIE);             // Globale Interrupt enable
    uint8_t freq = 0;
    while(true){
        //setFrequency(freq);
        //freq++;
        //__delay_cycles(1000000);    // 1s delay
        //if (freq == 255){
        //    freq = 0;
        //}

        setFrequency(1);
        __delay_cycles(3000000);
        setFrequency(2);
        __delay_cycles(3000000);
        setFrequency(3);
        __delay_cycles(3000000);
        setFrequency(4);
        __delay_cycles(3000000);
        setFrequency(5);
        __delay_cycles(3000000);

    }
    //__bis_SR_register(LPM0_bits);          // Enter LPM0
    //__no_operation();                           // For debugger
}
