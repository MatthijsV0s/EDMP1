#include <msp430.h>
#include "C:\Users\matth\source\repos\EDMP1\weekX_ButtonMatrix_PWM\include\gpio_lib.h"
#include "C:\Users\matth\source\repos\EDMP1\weekX_ButtonMatrix_PWM\include\led_matrix_lib.h"
#include "C:\Users\matth\source\repos\EDMP1\weekX_ButtonMatrix_PWM\include\button_matrix_lib.h"

int main(void){
    WDTCTL = WDTPW | WDTHOLD;       // Stop WDT

    // Klok configuration
    CSCTL0_H = CSKEY >> 8;                      // Unlock CS registers
    CSCTL1 = DCOFSEL_1;                         // Set DCO = 1MHz
    CSCTL2 = SELA__VLOCLK | SELS__DCOCLK | SELM__DCOCLK;
    CSCTL3 = DIVA__1 | DIVS__1 | DIVM__1;       // Set all dividers
    CSCTL0_H = 0;                               // Lock CS registers

    // Timer configuration
    TA0CCR0 = 1000-1;                           // TA0 PWM Period CCR0
    TA0CCTL1 = OUTMOD_5 & ~CCIE & ~CCIFG;       // TA0 CCR1 Reset
    TA0CCR1 = 500;                              // TA0 CCR1 PWM duty cycle
    TA1CCR0 = 1000-1;                           // TA1 PWM Period CCR0
    TA1CCTL1 = OUTMOD_5 & ~CCIE & ~CCIFG;       // TA1 CCR1 Reset
    TA1CCR1 = 500;                              // TA1 CCR1 PWM duty cycle
    TA0CTL = TASSEL__SMCLK | MC__UP | TACLR & ~TAIE & ~TAIFG;    // SMCLK, up mode, clear TAR
    TA1CTL = TASSEL__SMCLK | MC__UP | TACLR & ~TAIE & ~TAIFG;    // SMCLK, up mode, clear TAR

    pinSetDir(PORT1, BIT0, true);   // P1.0
    pinSetDir(PORT1, BIT2, true);   // P1.2 wired to P4.6
    pinConfigFunction(PORT1, BIT0, primary);
    pinConfigFunction(PORT1, BIT2, primary);

    GPIO_init();

    IOPin iolist_Button[B_MATRIX_ROWS + B_MATRIX_COLS] = {
        /* Rows */
        {PORT2, BIT2}, {PORT3, BIT4}, {PORT3, BIT5}, {PORT3, BIT6},
        /* Collums */
        {PORT1, BIT3}, {PORT1, BIT4}, {PORT1, BIT5}, {PORT1, BIT7}
    };

    configButtonMatrix(iolist_Button);

    while(1){
        switch (getButton()){
            case 0: break;  // No Button Pressed
            case 5:         // Button 1.1 Pressed   Enable LED1
                TA0CCTL1 = OUTMOD_7;
                break;
            case 6:         // Button 1.2 Pressed   Disable LED1
                TA0CCTL1 = OUTMOD_5;
                break;
            case 7:         // Button 1.3 Pressed   Setknipperen LED1
                pinConfigFunction(PORT1, BIT0, digital);
                TA0CTL = TASSEL__SMCLK | MC__UP | TACLR | TAIE & ~TAIFG;
                //TA0CCTL1 = OUTMOD_5 | CCIE & ~CCIFG;
                break;
            case 8:         // Button 1.4 Pressed   Setdimmen LED1
                pinConfigFunction(PORT1, BIT0, primary);
                TA0CTL = TASSEL__SMCLK | MC__UP | TACLR & ~TAIE & ~TAIFG;
                //TA0CCTL1 = OUTMOD_5 & ~CCIE & ~CCIFG;
                break;
            case 9:         // Button 2.1 Pressed   Increase PWM dutycycle LED1 by 5%
                TA0CCR1 += 50;
                break;
            case 10:        // Button 2.2 Pressed   Increase PWM dutycycle LED1 by 10%
                TA0CCR1 += 100;
                break;
            case 11:        // Button 2.3 Pressed   Decrease PWM dutycycle LED1 by 5%
                TA0CCR1 -= 50;
                break;
            case 12:        // Button 2.4 Pressed   Decrease PWM dutycycle LED1 by 10%
                TA0CCR1 -= 100;
                break;
            case 13:        // Button 3.1 Pressed   Enable LED2
                TA1CCTL1 = OUTMOD_7;
                break;
            case 14:        // Button 3.2 Pressed   Disable LED2
                TA1CCTL1 = OUTMOD_5;
                break;
            case 15:        // Button 3.3 Pressed   Setknipperen LED2
                pinConfigFunction(PORT1, BIT2, digital);
                TA1CTL = TASSEL__SMCLK | MC__UP | TACLR | TAIE & ~TAIFG;
                //TA1CCTL1 = OUTMOD_5 | CCIE & ~CCIFG;
                break;
            case 16:        // Button 3.4 Pressed   Setdimmen LED2
                pinConfigFunction(PORT1, BIT2, primary);
                TA1CTL = TASSEL__SMCLK | MC__UP | TACLR & ~TAIE & ~TAIFG;
                //TA1CCTL1 = OUTMOD_5 & ~CCIE & ~CCIFG;
                break;
            case 17:        // Button 4.1 Pressed   Increase PWM dutycycle LED2 by 5%
                TA1CCR1 += 50;
                break;
            case 18:        // Button 4.2 Pressed   Increase PWM dutycycle LED2 by 10%
                TA1CCR1 += 100;
                break;
            case 19:        // Button 4.3 Pressed   Decrease PWM dutycycle LED2 by 5%
                TA1CCR1 -= 50;
                break;
            case 20:        // Button 4.4 Pressed   Decrease PWM dutycycle LED2 by 10%
                TA1CCR1 -= 100;                
                break;
            default: break; // Incompatible value
        }
    }
}

#pragma vector=TIMER1_A0_VECTOR
__interrupt void TA1_CCR0_ISR (void) {

}

#pragma vector=TIMER1_A1_VECTOR
__interrupt void TA1_other_ISR (void) {
    switch (__even_in_range(TA1IV, 10)){
        case 0x00: break;       //None
        case 0x02: break;       //CCR1 IFG
        case 0x04: break;       //CCR2 IFG
        case 0x06: break;       //CCR3 IFG
        case 0x08: break;       //CCR4 IFG
        case 0x0A: break;       //CCR5 IFG
        case 0x0C: break;       //CCR6 IFG
        case 0x0E:              //TA1IFG Overflow
            pinToggle(PORT1, BIT2);
            break;
        default: _never_executed();
    }
}

#pragma vector=TIMER0_A0_VECTOR
__interrupt void TA0_CCR0_ISR (void) {

}

#pragma vector=TIMER0_A1_VECTOR
__interrupt void TA0_other_ISR (void) {
    switch (__even_in_range(TA0IV, 10)){
        case 0x00: break;       //None
        case 0x02: break;       //CCR1 IFG
        case 0x04: break;       //CCR2 IFG
        case 0x06: break;       //CCR3 IFG
        case 0x08: break;       //CCR4 IFG
        case 0x0A: break;       //CCR5 IFG
        case 0x0C: break;       //CCR6 IFG
        case 0x0E:              //TA1IFG Overflow
            pinToggle(PORT1, BIT0);
            break;
        default: _never_executed();
    }
}
