/* --COPYRIGHT--,BSD
 * Copyright (c) 2017, Texas Instruments Incorporated
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * *  Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 * *  Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * *  Neither the name of Texas Instruments Incorporated nor the names of
 *    its contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 * --/COPYRIGHT--*/
#include <msp430.h>

void main (void)
{
    WDTCTL = WDTPW | WDTHOLD;           //stop WDT

    //P1.0
    P1DIR |= BIT0;                      //set P1.0 as output
    P1OUT &= ~BIT0;                      //clear output

    PM5CTL0 &= ~LOCKLPM5;

    // Clock System Setup
    CSCTL0_H = CSKEY >> 8;                      // Unlock CS registers
    CSCTL2 |= SELA__LFXTCLK;                    // Set ACLK to external 32768 Hz crystal
    CSCTL3 |= DIVA__1;                          // Set prescaler to 1
    CSCTL0_H = 0;                               // Lock CS registers

    // Timer Setup
    TA1CTL = TASSEL__ACLK | MC__CONTINOUS | TACLR | TAIE & ~TAIFG;  // Set ACLK as source, mode continuous, clear count, Interrupt enable, clear flag.
    TA1CCTL2 = CCIE & ~CCIFG;                                       // Enable compare interrupt, clear flag.
    TA1CCR2 = 32767;                                                 // Set compare value to 50%

    __bis_SR_register(GIE);             // global interrupt enable
    __bis_SR_register(LPM0_bits);       // enter LPM0
    
}
#pragma vector=TIMER1_A0_VECTOR
__interrupt void TA0_CCR0_ISR (void) {

}

#pragma vector=TIMER1_A1_VECTOR
__interrupt void TA0_other_ISR (void) {
    switch (__even_in_range(TA1IV, 10)){
        case 0x00: break;       //None
        case 0x02: break;       //CCR1 IFG
        case 0x04:              //CCR2 IFG
            P1OUT |= BIT0;
            break;
        case 0x06: break;       //CCR3 IFG
        case 0x08: break;       //CCR4 IFG
        case 0x0A: break;       //CCR5 IFG
        case 0x0C: break;       //CCR6 IFG
        case 0x0E:              //TA1IFG Overflow
            P1OUT &= ~BIT0;
            break;
        default: _never_executed();
    }
}