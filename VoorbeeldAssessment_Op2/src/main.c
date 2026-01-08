#include <msp430.h>
#include "C:\Users\matth\source\repos\EDMP1\VoorbeeldAssessment_Op2\include\gpio_lib.h"

#define ADC_METING 0.001            // Sample frequentie in s
#define KLOK_FREQUENTIE 1000000     // Klokfrequentie in Hz

volatile unsigned int adc_res = 0;
volatile float adc_procent = 0;
volatile int teller = 0;

int main(void){
    WDTCTL = WDTPW | WDTHOLD;       // Stop WDT

    

    pinConfigFunction(PORT4, BIT2, tertiary);    // Set 4.2 to A10
    pinSetDir(PORT4, BIT5, 0);                  // Set P4.5 as Input S1
    pinConfigInput(PORT4, BIT5, true, true, true, true);
    pinSetDir(PORT4, BIT3, true);               // Set P4.3 as Dout

    // Configure ADC12
    ADC12CTL0 = ADC12SHT0_2 | ADC12ON;        // Sampling time, S&H=16, ADC12 on
    ADC12CTL1 = ADC12SHP;                     // Use sampling timer
    ADC12CTL2 |= ADC12RES_2;                  // 12-bit conversion results
    ADC12MCTL0 |= ADC12INCH_10;               // A10 ADC input select; Vref=AVCC
    ADC12IER0 |= ADC12IE0;                    // Enable ADC conv complete interrupt

    // Configure Timer0_A
    TA1CCR0 = (ADC_METING * KLOK_FREQUENTIE) - 1;   // Set CCR0 to sample frequentie
    TA1CCTL0 = CCIE;                                // Enable CCR0 interrupt
    TA1CTL = TASSEL__SMCLK | MC__STOP | TACLR | TAIE & ~TAIFG;    // SMCLK, stop mode, clear TAR

    GPIO_init();

    __bis_SR_register(GIE);             // Globale Interrupt enable

    __bis_SR_register(LPM0_bits);     // LPM0, ADC12_ISR will force exit
    __no_operation();                       // For debugger


}

#pragma vector=PORT4_VECTOR
__interrupt void pushbutton_ISR (void) {
    switch (__even_in_range(P4IV, 0x10)) {
        case 0x00: break;       //none
        case 0x02: break;       //Pin 0
        case 0x04: break;       //Pin 1
        case 0x06: break;       //Pin 2
        case 0x08: break;       //Pin 3
        case 0x0A: break;       //Pin 4
        case 0x0C:              //Pin 5
            P4IFG &= ~BIT5;                             // Clear knop interrupt flag
            TA1CTL |= MC__UP | TACLR;                   // Reset Timer
            teller = 0;                                 // Reset teller
            pinSet(PORT4, BIT3, true);  // Set Dout
            break;       
        case 0x0E: break;       //Pin 6
        case 0x10: break;       //Pin 7
        default: _never_executed();
    }

    
}

#pragma vector=TIMER1_A0_VECTOR
__interrupt void TA0_CCR0_ISR (void) {
    ADC12CTL0 |= ADC12ENC | ADC12SC;        // Start sampling/conversion
    teller++;
}

#pragma vector=TIMER1_A1_VECTOR
__interrupt void TA0_other_ISR (void) {
    switch (__even_in_range(TA1IV, 10)){
        case 0x00: break;       //None
        case 0x02: break;       //CCR1 IFG
        case 0x04: break;       //CCR2 IFG
        case 0x06: break;       //CCR3 IFG
        case 0x08: break;       //CCR4 IFG
        case 0x0A: break;       //CCR5 IFG
        case 0x0C: break;       //CCR6 IFG
        case 0x0E:              //TA1IFG Overflow
//            ADC12CTL0 |= ADC12ENC | ADC12SC;        // Start sampling/conversion
            break;
        default: _never_executed();
    }
}

#if defined(__TI_COMPILER_VERSION__) || defined(__IAR_SYSTEMS_ICC__)
#pragma vector = ADC12_VECTOR
__interrupt void ADC12_ISR(void)
#elif defined(__GNUC__)
void __attribute__ ((interrupt(ADC12_VECTOR))) ADC12_ISR (void)
#else
#error Compiler not supported!
#endif
{
  switch(__even_in_range(ADC12IV, ADC12IV_ADC12RDYIFG))
  {
    case ADC12IV_NONE:        break;        // Vector  0:  No interrupt
    case ADC12IV_ADC12OVIFG:  break;        // Vector  2:  ADC12MEMx Overflow
    case ADC12IV_ADC12TOVIFG: break;        // Vector  4:  Conversion time overflow
    case ADC12IV_ADC12HIIFG:  break;        // Vector  6:  ADC12BHI
    case ADC12IV_ADC12LOIFG:  break;        // Vector  8:  ADC12BLO
    case ADC12IV_ADC12INIFG:  break;        // Vector 10:  ADC12BIN
    case ADC12IV_ADC12IFG0:                 // Vector 12:  ADC12MEM0 Interrupt
        adc_res = ADC12MEM0;
        adc_procent = ((float)adc_res / 4096.0f) * 100.0f;
        if ((teller == 1000) || (adc_procent >= 63)){
            TA1CTL &= ~MC__UP;
            pinSet(PORT4, BIT3, false);
        }

        ADC12CTL0 &= ~ADC12ENC;                 // Stop ADC, voorkomt automatische retrigger
        ADC12IFGR0 &= ~ADC12IFG0;                   // Clear ADC interrupt flag

        __bic_SR_register_on_exit(LPM0_bits); // Exit active CPU
        break;                              
    case ADC12IV_ADC12IFG1:   break;        // Vector 14:  ADC12MEM1
    case ADC12IV_ADC12IFG2:   break;        // Vector 16:  ADC12MEM2
    case ADC12IV_ADC12IFG3:   break;        // Vector 18:  ADC12MEM3
    case ADC12IV_ADC12IFG4:   break;        // Vector 20:  ADC12MEM4
    case ADC12IV_ADC12IFG5:   break;        // Vector 22:  ADC12MEM5
    case ADC12IV_ADC12IFG6:   break;        // Vector 24:  ADC12MEM6
    case ADC12IV_ADC12IFG7:   break;        // Vector 26:  ADC12MEM7
    case ADC12IV_ADC12IFG8:   break;        // Vector 28:  ADC12MEM8
    case ADC12IV_ADC12IFG9:   break;        // Vector 30:  ADC12MEM9
    case ADC12IV_ADC12IFG10:  break;        // Vector 32:  ADC12MEM10
    case ADC12IV_ADC12IFG11:  break;        // Vector 34:  ADC12MEM11
    case ADC12IV_ADC12IFG12:  break;        // Vector 36:  ADC12MEM12
    case ADC12IV_ADC12IFG13:  break;        // Vector 38:  ADC12MEM13
    case ADC12IV_ADC12IFG14:  break;        // Vector 40:  ADC12MEM14
    case ADC12IV_ADC12IFG15:  break;        // Vector 42:  ADC12MEM15
    case ADC12IV_ADC12IFG16:  break;        // Vector 44:  ADC12MEM16
    case ADC12IV_ADC12IFG17:  break;        // Vector 46:  ADC12MEM17
    case ADC12IV_ADC12IFG18:  break;        // Vector 48:  ADC12MEM18
    case ADC12IV_ADC12IFG19:  break;        // Vector 50:  ADC12MEM19
    case ADC12IV_ADC12IFG20:  break;        // Vector 52:  ADC12MEM20
    case ADC12IV_ADC12IFG21:  break;        // Vector 54:  ADC12MEM21
    case ADC12IV_ADC12IFG22:  break;        // Vector 56:  ADC12MEM22
    case ADC12IV_ADC12IFG23:  break;        // Vector 58:  ADC12MEM23
    case ADC12IV_ADC12IFG24:  break;        // Vector 60:  ADC12MEM24
    case ADC12IV_ADC12IFG25:  break;        // Vector 62:  ADC12MEM25
    case ADC12IV_ADC12IFG26:  break;        // Vector 64:  ADC12MEM26
    case ADC12IV_ADC12IFG27:  break;        // Vector 66:  ADC12MEM27
    case ADC12IV_ADC12IFG28:  break;        // Vector 68:  ADC12MEM28
    case ADC12IV_ADC12IFG29:  break;        // Vector 70:  ADC12MEM29
    case ADC12IV_ADC12IFG30:  break;        // Vector 72:  ADC12MEM30
    case ADC12IV_ADC12IFG31:  break;        // Vector 74:  ADC12MEM31
    case ADC12IV_ADC12RDYIFG: break;        // Vector 76:  ADC12RDY
    default: break;
  }
}
