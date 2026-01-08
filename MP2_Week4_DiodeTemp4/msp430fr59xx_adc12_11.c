#include <msp430.h>

//#define CALADC12_12V_30C  *((unsigned int *)0x1A1A)   // Temperature Sensor Calibration-30 C
                                                      //See device datasheet for TLV table memory mapping
//#define CALADC12_12V_85C  *((unsigned int *)0x1A1C)   // Temperature Sensor Calibration-85 C

#define CALDIODE_12V_14C   1970  // 14 ‘C    
#define CALDIODE_12V_43C   1750  // 43 ‘C    

#define CALDIODE_12V_19C    2765
#define CALDIODE_12V_32C    2705


unsigned long temp;
unsigned int gemtemp;
unsigned int Atemp[100];
unsigned int positie;
volatile float temperatureDegC;
volatile float temperatureDegF;
volatile int a;

int main(void)
{
  WDTCTL = WDTPW | WDTHOLD;                 // Stop WDT

  // Configure GPIOs to it's lowest power state
  P1OUT = 0;                                // All P1.x reset
  P1DIR = 0b11111011;                       // All P1.x outputs --> P1.2 input
  P2OUT = 0;                                // All P2.x reset
  P2DIR = 0xFF;                             // All P2.x outputs
  P3OUT = 0x00;                             // All P3.x reset --> P3.0 Hoog
  P3DIR = 0xFF;                             // All P3.x outputs
  P4OUT = 0;                                // All P4.x reset
  P4DIR = 0xFF;                             // All P4.x outputs
  PJOUT = 0;                                // All PJ.x reset
  PJDIR = 0xFFFF;                           // All PJ.x outputs

  P3REN |= BIT0;
  //P3OUT |= BIT0;

  P1SELC |= BIT2;                           // P1.2 --> A2

  // Set up XT1
  PJSEL0 = BIT4 | BIT5;                     // For XT1

  // Disable the GPIO power-on default high-impedance mode to activate
  // previously configured port settings
  PM5CTL0 &= ~LOCKLPM5;

  // Clock System Setup
  CSCTL0_H = CSKEY >> 8;                    // Unlock CS registers
  CSCTL1 = DCOFSEL_0;                       // Set DCO to 1MHz
  CSCTL2 = SELA__LFXTCLK | SELS__DCOCLK | SELM__DCOCLK;
  CSCTL3 = DIVA__1 | DIVS__1 | DIVM__1;     // Set all dividers
  CSCTL4 &= ~LFXTOFF;

  do
  {
    CSCTL5 &= ~LFXTOFFG;                    // Clear XT1 fault flag
    SFRIFG1 &= ~OFIFG;
  } while (SFRIFG1 & OFIFG);                // Test oscillator fault flag

  ADC12CTL0 = ADC12SHT0_0 | ADC12ON;        // Sampling time, S&H=4, ADC12 on
  // Use TA0.1 to trigger, and repeated-single-channel
  ADC12CTL1 = ADC12SHP;
  
  //ADC12CTL3 = ADC12TCMAP;                   // Enable internal temperature sensor
  ADC12MCTL0 = ADC12VRSEL_1 + ADC12INCH_2; // ADC input ch A30 => temp sense


  ADC12IER0 |= ADC12IE0;                    // Enable ADC interrupt
  //ADC12CTL0 |= ADC12ENC | ADC12SC;          // Start sampling/conversion

  // Configure internal reference
  while(REFCTL0 & REFGENBUSY);              // If ref generator busy, WAIT
  REFCTL0 |= REFVSEL_0|REFON;               // Select internal ref = 2.5V
                                            // Internal Reference ON
  while(!(REFCTL0 & REFGENRDY));            // Wait for reference generator
                                            // to settle

  // Configure Timer0_A3 to periodically trigger the ADC12
  TA0CCR0 = 2048-1;                         // PWM Period
  TA0CCTL0 = CCIE & ~CCIFG;
  TA0CCTL1 = OUTMOD_3;                      // TACCR1 set/reset
  TA0CCR1 = 2047;                           // TACCR1 PWM Duty Cycle
  TA0CTL = TASSEL__ACLK | MC__UP;           // ACLK, up mode
  

  while (1){
    __bis_SR_register(LPM3_bits | GIE);       // Enter LPM3, enable interrupts
    TA0CTL &= ~MC__UP;                    // stop timer
    temp = 0;
    for (int i = 0; i < 100; i++){
      temp += Atemp[i]; 
    }
    gemtemp = temp / 100;

    // Temperature in Celsius. See the Device Descriptor Table section in the
    // System Resets, Interrupts, and Operating Modes, System Control Module
    // chapter in the device user's guide for background information on the
    // used formula.
    temperatureDegC = (float)(((long)gemtemp - CALDIODE_12V_19C) * (32 - 19)) / (CALDIODE_12V_32C - CALDIODE_12V_19C) + 19.0f;

    // Temperature in Fahrenheit Tf = (9/5)*Tc + 32
    temperatureDegF = temperatureDegC * 9.0f / 5.0f + 32.0f;
    a++;
    __no_operation();

    if (temperatureDegC > 30.0f) {
      P4OUT |= BIT6;
      P1OUT &= ~BIT0;
    }
    else {
      P4OUT &= ~BIT6;
      P1OUT |= BIT0;
    }
    TA0CTL |= MC__UP;                     // resume timer
  }

  return 0;
}

#pragma vector=TIMER0_A0_VECTOR
__interrupt void TA0_CCR0_ISR (void) {
  P3OUT |= BIT0;
  __delay_cycles(100);
  ADC12CTL0 |= ADC12ENC | ADC12SC;        // Start sampling/conversion
}

// ADC12 interrupt service routine
#if defined(__TI_COMPILER_VERSION__) || defined(__IAR_SYSTEMS_ICC__)
#pragma vector=ADC12_VECTOR
__interrupt void ADC12ISR (void)
#elif defined(__GNUC__)
void __attribute__ ((interrupt(ADC12_VECTOR))) ADC12ISR (void)
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
      //temp = ADC12MEM0;
      
      Atemp[positie] = ADC12MEM0;
      positie++;

      if (positie == 100){
        positie = 0;
        __bic_SR_register_on_exit(LPM3_bits);
      }
      P3OUT &= ~BIT0;
      __no_operation();
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
