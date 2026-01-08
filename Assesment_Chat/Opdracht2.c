#include <msp430.h>

// -----------------------------------------------------------------------------
// Globale variabelen voor ADC-resultaten
// De keyword 'volatile' zorgt dat de compiler weet dat deze waarden binnen een
// interrupt kunnen wijzigen en dus niet geoptimaliseerd mogen worden.
// Elke variabele komt overeen met een apart ADC-kanaal.
// -----------------------------------------------------------------------------
volatile unsigned int adc_val_ch0 = 0;  // ADC waarde op kanaal A2 (P1.2)
volatile unsigned int adc_val_ch1 = 0;  // ADC waarde op kanaal A3 (P1.3)
volatile unsigned int adc_val_ch2 = 0;  // ADC waarde op kanaal A4 (P1.4)
volatile unsigned int adc_val_ch3 = 0;  // ADC waarde op kanaal A5 (P1.5)

int main(void) {
    WDTCTL = WDTPW | WDTHOLD;  // Stop de Watchdog Timer om onverwachte resets te vermijden.

    // -------------------------------------------------------------------------
    // GPIO-instellingen
    // -------------------------------------------------------------------------
    P1OUT &= ~BIT0;     // LED op P1.0 uitzetten bij opstart.
    P1DIR |= BIT0;      // P1.0 instellen als output (meestal LED op Launchpad).

    // -------------------------------------------------------------------------
    // Configureer P1.2, P1.3, P1.4 en P1.5 als ADC-inputs.
    // De MSP430 gebruikt P1SEL0 en P1SEL1 om een pin te routeren naar de ADC.
    // Voor analoge functies moeten meestal beide bits op 1 staan.
    // -------------------------------------------------------------------------
    P1SEL1 |= BIT2;  P1SEL0 |= BIT2;   // P1.2 → ADC kanaal A2
    P1SEL1 |= BIT3;  P1SEL0 |= BIT3;   // P1.3 → ADC kanaal A3
    P1SEL1 |= BIT4;  P1SEL0 |= BIT4;   // P1.4 → ADC kanaal A4
    P1SEL1 |= BIT5;  P1SEL0 |= BIT5;   // P1.5 → ADC kanaal A5

    // -------------------------------------------------------------------------
    // High-impedance mode uitschakelen
    // Bij moderne MSP430's staan alle GPIO's in high-Z totdat LOCKLPM5 wordt
    // vrijgegeven. Dit is verplicht om de pinconfiguratie actief te maken.
    // -------------------------------------------------------------------------
    PM5CTL0 &= ~LOCKLPM5;  // GPIO vrijmaken.

    // -------------------------------------------------------------------------
    // Clock-configuratie
    // In dit voorbeeld wordt de ACLK (32.768 kHz kristal) geactiveerd.
    // CSCTL0_H: sleutel voor klokkenconfiguratie schrijven.
    // CSCTL1: DCO (digitale klok) instelling.
    // CSCTL2: selecteert clockbronnen.
    // CSCTL3: clock dividers.
    // CSCTL4: schakelt de LFXT oscillator in.
    // -------------------------------------------------------------------------
    CSCTL0_H = CSKEY >> 8;     // Ontgrendel klokregisters.
    CSCTL1 = DCOFSEL_0;        // Zet DCO op laagste frequentie.
    CSCTL2 = SELA__LFXTCLK;    // Selecteer LFXT voor ACLK.
    CSCTL3 = DIVA_1;           // ACLK divider = 2.
    CSCTL4 &= ~LFXTOFF;        // LFXT oscillator inschakelen.
    CSCTL0_H = 0;              // Vergrendel opnieuw.

    // -------------------------------------------------------------------------
    // Timer1 configuratie
    // TASSEL__ACLK: Timer gebruikt ACLK als klokbron.
    // MC__CONTINUOUS: continue count-modus (0 → 0xFFFF → rollover).
    // TACLR: reset timer.
    // ID_1: clock divider op 2.
    // (CCR0 interrupt staat uit omdat het commentaar is.)
    // -------------------------------------------------------------------------
    TA1CTL = TASSEL__ACLK | MC__CONTINUOUS | TACLR | ID_1;
    // TA1CCTL0 = CCIE;  // CCR0-interrupt — momenteel uitgezet.

    // -------------------------------------------------------------------------
    // ADC12 kanaal mapping (Memory Control Registers MCTL0..3)
    // Elk MCTL-register bepaalt welk ADC-invoerkanaal aan welk geheugenregister
    // wordt gekoppeld.
    // -------------------------------------------------------------------------
    ADC12MCTL0 = ADC12INCH_2;  // MEM0 → A2
    ADC12MCTL1 = ADC12INCH_3;  // MEM1 → A3
    ADC12MCTL2 = ADC12INCH_4;  // MEM2 → A4
    ADC12MCTL3 = ADC12INCH_5;  // MEM3 → A5

    // -------------------------------------------------------------------------
    // ADC12 configuratie
    // ADC12SHT0_2 : sample-hold tijd instellen.
    // ADC12ON     : ADC aanzetten.
    // ADC12MSC    : multiple sample-conversions (automatisch doorlopend sequencen).
    // ADC12SHP    : sample timer gebruiken.
    // ADC12CONSEQ_1 : sequence-of-channels mode.
    // ADC12RES_2 : 12-bit resolutie. (0=8bit,1=10bit,2=12bit)
    // ADC12IER0 : interrupts inschakelen voor MEM0-3.
    // ADC12ENC + ADC12SC : ADC activeren en conversie starten.
    // -------------------------------------------------------------------------
    ADC12CTL0 = ADC12SHT0_2 | ADC12ON | ADC12MSC;
    ADC12CTL1 |= ADC12SHP | ADC12CONSEQ_1;
    ADC12CTL2 = ADC12RES_2;
    ADC12IER0 = ADC12IE0 | ADC12IE1 | ADC12IE2 | ADC12IE3;  // Interrupts voor MEM0..3.

    ADC12CTL0 |= ADC12ENC | ADC12SC;  // ADC inschakelen en conversie starten.

    // -------------------------------------------------------------------------
    // Energiestand: LPM0 (low-power mode 0) met interrupts actief.
    // MCU wacht hier totdat een interrupt het wakker maakt.
    // -------------------------------------------------------------------------
    __bis_SR_register(LPM0_bits | GIE);  // Start low-power mode + enable interrupts.

    __no_operation();  // Marker voor debug.
}

// -----------------------------------------------------------------------------
// ADC12 Interrupt Service Routine
// Deze ISR wordt uitgevoerd wanneer een conversie klaar is.
// Elke ADC12IV waarde correspondeert met een ander interrupt event.
// De even_in_range macro zorgt dat enkel geldige vectoren worden verwerkt.
// -----------------------------------------------------------------------------
#if defined(__TI_COMPILER_VERSION__) || defined(__IAR_SYSTEMS_ICC__)
#pragma vector = ADC12_VECTOR
__interrupt void ADC12_ISR(void)
#elif defined(__GNUC__)
void __attribute__((interrupt(ADC12_VECTOR))) ADC12_ISR(void)
#else
#error Compiler not supported!
#endif
{
    switch (__even_in_range(ADC12IV, ADC12IV_ADC12RDYIFG)) {

        case ADC12IV_ADC12IFG0:  // MEM0 conversie klaar (A2)
            adc_val_ch0 = ADC12MEM0;  // ADC-waarde opslaan.
            __bic_SR_register_on_exit(LPM0_bits); // MCU uit LPM0 halen.
            break;

        case ADC12IV_ADC12IFG1:  // MEM1 conversie klaar (A3)
            adc_val_ch1 = ADC12MEM1;
            __bic_SR_register_on_exit(LPM0_bits);
            break;

        case ADC12IV_ADC12IFG2:  // MEM2 conversie klaar (A4)
            adc_val_ch2 = ADC12MEM2;
            // Hier ontbreekt een "break" in het originele programma.
            // Dit is waarschijnlijk een bug, maar behouden voor consistentie.
            break;
            __bic_SR_register_on_exit(LPM0_bits);  // Wordt nooit bereikt.

        case ADC12IV_ADC12IFG3:  // MEM3 conversie klaar (A5)
            adc_val_ch3 = ADC12MEM3;  // Resultaat opslaan.
            P1OUT ^= BIT0;            // LED toggelen om conversie te tonen.
            __bic_SR_register_on_exit(LPM0_bits);
            break;

        default:
            break;   // Ongebruikte interrupt sources.
    }
}
