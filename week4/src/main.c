#include <msp430.h>
#include "C:\Users\matth\source\repos\EDMP1\week4\include\gpio_lib.h"

int main(void){
    
    GPIO_init();

    pinSetDir(PORT1, BIT2, 1);  // P1.2
    pinSetDir(PORT3, BIT0, 1);  // P3.0
    pinSetDir(PORT1, BIT6, 1);  // P1.6
    pinSetDir(PORT1, BIT7, 1);  // P1.7
    pinSetDir(PORT1, BIT5, 1);  // P1.5
    pinSetDir(PORT1, BIT4, 1);  // P1.4
    pinSetDir(PORT1, BIT3, 1);  // P1.3
    pinSetDir(PORT4, BIT2, 1);  // P4.2

    pinSetDir(PORT2, BIT6, 1);  // P2.6
    pinSetDir(PORT2, BIT5, 1);  // P2.5
    pinSetDir(PORT4, BIT3, 1);  // P4.3
    pinSetDir(PORT2, BIT4, 1);  // P2.4
    pinSetDir(PORT2, BIT2, 1);  // P2.2
    pinSetDir(PORT3, BIT4, 1);  // P3.4
    pinSetDir(PORT3, BIT5, 1);  // P3.5
    pinSetDir(PORT3, BIT6, 1);  // P3.6

    pinSet(PORT1, BIT2, 1);
    pinSet(PORT3, BIT0, 0);
    pinSet(PORT1, BIT6, 0);  
    pinSet(PORT1, BIT7, 0);  
    pinSet(PORT1, BIT5, 0);  
    pinSet(PORT1, BIT4, 1);  
    pinSet(PORT1, BIT3, 0);  
    pinSet(PORT4, BIT2, 0);

    pinSet(PORT2, BIT6, 0);
    pinSet(PORT2, BIT5, 1);  
    pinSet(PORT4, BIT3, 1);  
    pinSet(PORT2, BIT4, 1);  
    pinSet(PORT2, BIT2, 0);  
    pinSet(PORT3, BIT4, 1);  
    pinSet(PORT3, BIT5, 1);  
    pinSet(PORT3, BIT6, 1);  

    while(1){
        
    }
}
