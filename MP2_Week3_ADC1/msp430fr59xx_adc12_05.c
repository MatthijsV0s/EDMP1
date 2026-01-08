//******************************************************************************
//  MSP430FR59xx Demo - ADC12, Using an External Reference
//
//  Description: This example shows how to use an external positive reference for
//  the ADC12.The external reference is applied to the VeREF+ pin. AVss is used
//  for the negative reference. A single conversion is performed on channel A0.
//  The conversion results are stored in ADC12MEM0. Test by applying a voltage
//  to channel A0, then setting and running to a break point at the "_NOP()"
//  instruction. To view the conversion results, open an SFR window in debugger
//  and view the contents of ADC12MEM0 or from the variable ADCvar.
//  NOTE: VeREF+ range: 1.4V (min) to AVCC (max)
//        VeREF- range: 0V (min) to 1.2V (max)
//        Differential ref voltage range: 1.4V(min) to AVCC(max)
//          (see datasheet for device specific information)
//
//                MSP430FR5969
//             -------------------
//         /|\|                   |
//          | |                   |
//          --|RST                |
//            |                   |
//     Vin -->|P1.0/A0            |
//            |                   |
//     REF -->|P1.1/VREF+/VeREF+  |
//            |                   |
//
//   Lixin Chen 
//   Texas Instruments Inc.
//   Feburary 2020
//   Built with IAR Embedded Workbench V7.12.4 & Code Composer Studio V9.3
//******************************************************************************
#include <msp430.h>

#define CALADC12_12V_30C  *((unsigned int *)0x1A1A)   // Temperature Sensor Calibration-30 C
                                                      //See device datasheet for TLV table memory mapping
#define CALADC12_12V_85C  *((unsigned int *)0x1A1C)   // Temperature Sensor Calibration-85 C

unsigned int temp;
volatile float temperatureDegC;

volatile unsigned int ADCvar;

int main(void)
{
  WDTCTL = WDTPW | WDTHOLD;                 // Stop WDT

  // Configure GPIO
  P1DIR |= 0xff;
  P2DIR |= 0xff;
  P3DIR |= 0xff;
  P4DIR |= 0xff;

  // Disable the GPIO power-on default high-impedance mode to activate
  // previously configured port settings
  PM5CTL0 &= ~LOCKLPM5;

  // Configure internal reference
    while(REFCTL0 & REFGENBUSY);              // If ref generator busy, WAIT
    REFCTL0 |= REFVSEL_0 | REFON;             // Select internal ref = 1.2V
                                              // Internal Reference ON
    while(!(REFCTL0 & REFGENRDY));            // Wait for reference generator
                                              // to settle


  /* Initialize ADC12_A */
  ADC12CTL0 &= ~ADC12ENC;                   // Disable ADC12
  ADC12CTL0 = ADC12SHT0_8 + ADC12ON;        // Set sample time
  ADC12CTL1 = ADC12SHP;                     // Enable sample timer
  ADC12CTL3 = ADC12TCMAP;                   // Enable internal temperature sensor
  ADC12MCTL0 = ADC12VRSEL_1 + ADC12INCH_30; // ADC input ch A30 => temp sense
  ADC12CTL0 |= ADC12ENC;                    // Enable ADC12

  while(1)
  {
    ADC12CTL0 |= ADC12SC;                   // Sampling and conversion start
    while (!(ADC12IFGR0 & BIT0));           // Wait for conversion ready
    temp = ADC12MEM0;
    // Temperature in Celsius
    temperatureDegC = (float)(((long)temp - CALADC12_12V_30C) * (85 - 30)) /
            (CALADC12_12V_85C - CALADC12_12V_30C) + 30.0f;
    if (temperatureDegC > 30.0f) {
      P4OUT |= BIT6;
      P1OUT &= ~BIT0;
    }
    else {
      P4OUT &= ~BIT6;
      P1OUT |= BIT0;
    }
    __no_operation();
  }

}
