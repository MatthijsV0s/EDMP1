#include <msp430.h>
#include "C:\Users\matth\source\repos\EDMP1\weekX_ButtonMatrix_PWM\include\gpio_lib.h"
#include "C:\Users\matth\source\repos\EDMP1\weekX_ButtonMatrix_PWM\include\led_matrix_lib.h"
#include "C:\Users\matth\source\repos\EDMP1\weekX_ButtonMatrix_PWM\include\button_matrix_lib.h"

int main(void){
    WDTCTL = WDTPW | WDTHOLD;       // Stop WDT

    GPIO_init();

    IOPin iolist_Button[B_MATRIX_ROWS + B_MATRIX_COLS] = {
        /* Rows */
        {PORT2, BIT2}, {PORT3, BIT4}, {PORT3, BIT5}, {PORT3, BIT6},
        /* Collums */
        {PORT1, BIT3}, {PORT1, BIT4}, {PORT1, BIT5}, {PORT1, BIT7}
    };

    configButtonMatrix(iolist_Button);

    while(1){
        
    }
}