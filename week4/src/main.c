#include <msp430.h>
#include "C:\Users\matth\source\repos\EDMP1\week4\include\gpio_lib.h"
#include "C:\Users\matth\source\repos\EDMP1\week4\include\led_matrix_lib.h"

int main(void) {
    
    WDTCTL = WDTPW | WDTHOLD;       // Stop WDT

    GPIO_init();

    IOPin iolist[MATRIX_ROWS + MATRIX_COLS] = {
        /* Rows */
        {PORT1, BIT2}, {PORT3, BIT0}, {PORT1, BIT6}, {PORT1, BIT7},
        {PORT1, BIT5}, {PORT1, BIT4}, {PORT1, BIT3}, {PORT4, BIT2},
        /* Collums */
        {PORT2, BIT6}, {PORT2, BIT5}, {PORT4, BIT3}, {PORT2, BIT4},
        {PORT2, BIT2}, {PORT3, BIT4}, {PORT3, BIT5}, {PORT3, BIT6}
    };

    configLEDMatrix(iolist);

    setLed(0,0,true);
    setLed(6,7,true);
    //setMatrix(true);

    while(1){
        refreshMatrix();
    }
}
