// ----------------------------------------------------------------------------
// main.c  (for lab_07c_initPorts project) ('FR5969 Launchpad)
// ----------------------------------------------------------------------------

//***** Header Files **********************************************************
#include <driverlib.h>
#include "myClocks.h"
#include "initPorts.h"


//***** Prototypes ************************************************************
void initGPIO(void);


//***** Defines ***************************************************************
#define ONE_SECOND    myMCLK_FREQUENCY_IN_HZ
#define HALF_SECOND   myMCLK_FREQUENCY_IN_HZ / 2


//***** Global Variables ******************************************************


//*****************************************************************************
// Main
//*****************************************************************************
void main (void)
{
    // Stop watchdog timer
    WDT_A_hold( WDT_A_BASE );

    // Initialize GPIO Ports
    initPorts();

    // Initialize GPIO
    initGPIO();

    // Initialize clocks
    initClocks();

    // Enter Low Power Mode 3 (LPM3)
    __low_power_mode_3();

//    while(1) {
//        // Turn on LED
//        GPIO_setOutputHighOnPin( GPIO_PORT_P1, GPIO_PIN0 );
//
//        // Wait about a second
//        __delay_cycles( HALF_SECOND );
//
//        // Turn off LED
//        GPIO_setOutputLowOnPin( GPIO_PORT_P1, GPIO_PIN0 );
//
//        // Wait another second
//        __delay_cycles( HALF_SECOND );
//    }
}

//*****************************************************************************
// Initialize GPIO
//*****************************************************************************
void initGPIO(void) {

    // Set pin P1.0 to output direction and turn LED off
    GPIO_setAsOutputPin( GPIO_PORT_P1, GPIO_PIN0 );                             // Green LED (LED2)
    GPIO_setOutputLowOnPin( GPIO_PORT_P1, GPIO_PIN0 );

    // Set pin P9.7 to output direction and turn LED off
    GPIO_setAsOutputPin( GPIO_PORT_P4, GPIO_PIN6 );                             // Red LED (LED1)
    GPIO_setOutputLowOnPin( GPIO_PORT_P4, GPIO_PIN6 );

    // Unlock pins (required for most FRAM devices)
    // Unless waking from LPMx.5, this should be done before clearing and enabling GPIO port interrupts
    PMM_unlockLPM5();

    // Set LFXT (low freq crystal pins) to crystal input (rather than GPIO)
    // Since HFXT is not used, we don't need to set these pins. But for the 
    // record, they are:
    //              GPIO_PIN6                            // HFXTIN on PJ.6
    //              GPIO_PIN7                            // HFXOUT on PJ.7
    GPIO_setAsPeripheralModuleFunctionInputPin(
                    GPIO_PORT_PJ,
                    GPIO_PIN4 +                          // LFXIN  on PJ.4
                    GPIO_PIN5 ,                          // LFXOUT on PJ.5
                    GPIO_PRIMARY_MODULE_FUNCTION
    );

//  Output the ACLK and SMCLK signals to their respective pins to allow watching them with logic analyzer
//    GPIO_setAsPeripheralModuleFunctionOutputPin(
//                    GPIO_PORT_P2,
//                    GPIO_PIN0 +                          // ACLK on P2.0
//                    GPIO_PRIMARY_MODULE_FUNCTION
//    );
//    GPIO_setAsPeripheralModuleFunctionOutputPin(
//                    GPIO_PORT_P3,
//                    GPIO_PIN4 +                          // SMCLK on P3.4
//                    GPIO_PRIMARY_MODULE_FUNCTION
//    );
}

