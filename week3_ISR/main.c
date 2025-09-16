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

    //P1.1
    P1DIR &= ~BIT1;                     //set P1.1 as input
    P1REN |= BIT1;                      //eneble pull-resistor
    P1OUT |= BIT1;                      //set pull-up resistor
    P1IE |= BIT1;                       //enable interrupt
    P1IES |= BIT1;                      //set detect falling edge
    P1IFG &= ~BIT1;                     //clear interrupt flag

    //P1.0
    P1DIR |= BIT0;                      //set P1.0 as output
    P1OUT |= BIT0;

    PM5CTL0 &= ~LOCKLPM5;               //enable GPIO pins

    __bis_SR_register(GIE);       //enable global interrupt

    
}

#pragma vector=PORT1_VECTOR
__interrupt void pushbutton_ISR (void) {
    switch (__even_in_range(P1IV, 0x10)) {
        case 0x00: break;       //none
        case 0x02: break;       //Pin 0
        case 0x04:              //Pin 1
        P1OUT ^= BIT0;                  //toggle P1.0 (LED)
        P1IFG &= ~BIT1;
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