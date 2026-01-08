#include <msp430.h>
#include <stdint.h>
#include <stdbool.h>
#include "gpio_lib.h"

/*
 * adcValues[] wordt gevuld in de ADC interrupt
 * wanneer de hele sequence klaar is (EOSEQ).
 */
volatile uint16_t adcValues[4];
volatile bool adcDone = false;     // Flag die door interrupt wordt gezet


int main(void)
{
    /* ------------------------------
     * 1. Stop watchdog timer
     * ------------------------------ */
    WDTCTL = WDTPW | WDTHOLD;

    /* ------------------------------
     * 2. Init GPIO uit jouw library
     * ------------------------------ */
    GPIO_init();

    /* ------------------------------
     * 3. ADC PIN CONFIG
     *    A0–A3 op P1.0–P1.3
     *    Functie = tertiary
     * ------------------------------ */
    pinConfigFunction(PORT1, BIT0, tertiary);   // A0
    pinConfigFunction(PORT1, BIT1, tertiary);   // A1
    pinConfigFunction(PORT1, BIT2, tertiary);   // A2
    pinConfigFunction(PORT1, BIT3, tertiary);   // A3


    /* ------------------------------
     * 4. ADC basic setup
     * ------------------------------ */
    ADC12CTL0 &= ~ADC12ENC;                     // Uitzetten voor config
    ADC12CTL0 = ADC12SHT0_2 | ADC12ON;          // Sample time + ADC aan

    ADC12CTL1 = ADC12SHP;                       // Pulse mode (timer)
    ADC12CTL2 = ADC12RES_2;                     // 12-bit mode


    /* ------------------------------
     * 5. Multi-channel sequence config
     *    EOS = End Of Sequence bij A3
     * ------------------------------ */
    ADC12MCTL0 = 0;                             // A0
    ADC12MCTL1 = 1;                             // A1
    ADC12MCTL2 = 2;                             // A2
    ADC12MCTL3 = ADC12EOS | 3;                  // A3 + End-Of-Sequence


    /* ------------------------------
     * 6. Interrupts inschakelen
     * ------------------------------
     * BIT3 = interrupt bij A3 (EOS)
     * ------------------------------ */
    ADC12IER0 = BIT3;                           // Enable interrupt bij A3


    /* ------------------------------
     * 7. ADC en algemene interrupts aan
     * ------------------------------ */
    ADC12CTL0 |= ADC12ENC;
    __enable_interrupt();


    /* ------------------------------
     * 8. Infinite loop
     * ------------------------------ */
    while (1)
    {
        adcDone = false;                        // Reset flag

        /* Start nieuwe ADC sequence */
        ADC12CTL0 |= ADC12SC;

        /* Wacht tot interrupt sequence klaar meldt */
        while (!adcDone);

        /*
         * Nu staan de waarden klaar:
         * adcValues[0] = A0
         * adcValues[1] = A1
         * adcValues[2] = A2
         * adcValues[3] = A3
         */

        __delay_cycles(5000);
    }
}


/* ---------------------------------------------------------
 * ADC12 ISR
 * ---------------------------------------------------------
 * Deze interrupt triggert ALLEEN bij A3 omdat:
 * - A3 = laatste kanaal
 * - ADC12MCTL3 heeft ADC12EOS
 * - ADC12IER0 heeft BIT3 enabled
 * --------------------------------------------------------- */
#pragma vector = ADC12_VECTOR
__interrupt void ADC12_ISR(void)
{
    switch (__even_in_range(ADC12IV, ADC12IV__ADC12RDYIFG))
    {
        case ADC12IV__NONE:
            break;

        case ADC12IV__ADC12IFG3:   // A3 = End Of Sequence
            adcValues[0] = ADC12MEM0;
            adcValues[1] = ADC12MEM1;
            adcValues[2] = ADC12MEM2;
            adcValues[3] = ADC12MEM3;

            adcDone = true;        // Meld aan main-loop dat sequence klaar is
            break;

        default:
            break;
    }
}
