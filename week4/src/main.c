#include <msp430.h>
#include "C:\Users\matth\source\repos\EDMP1\week4\include\gpio_lib.h"
#include "C:\Users\matth\source\repos\EDMP1\week4\include\led_matrix_lib.h"
#include "C:\Users\matth\source\repos\EDMP1\week4\include\button_matrix_lib.h"

int main(void) {
    
    WDTCTL = WDTPW | WDTHOLD;       // Stop WDT

    GPIO_init();

    IOPin iolist_Led[MATRIX_ROWS + MATRIX_COLS] = {
        /* Rows */
        {PORT1, BIT2}, {PORT3, BIT0}, {PORT1, BIT6}, {PORT1, BIT7},
        {PORT1, BIT5}, {PORT1, BIT4}, {PORT1, BIT3}, {PORT4, BIT2},
        /* Collums */
        {PORT2, BIT6}, {PORT2, BIT5}, {PORT4, BIT3}, {PORT2, BIT4},
        {PORT2, BIT2}, {PORT3, BIT4}, {PORT3, BIT5}, {PORT3, BIT6}
    };

    IOPin iolist_Button[B_MATRIX_ROWS + B_MATRIX_COLS] = {
        /* Rows */
        {PORT2, BIT2}, {PORT3, BIT4}, {PORT3, BIT5}, {PORT3, BIT6},
        /* Collums */
        {PORT1, BIT3}, {PORT1, BIT4}, {PORT1, BIT5}, {PORT1, BIT7}
    };

    configButtonMatrix(iolist_Button);
    //pinSetDir(PORT1, BIT1, 0);
    //pinConfigInput(PORT1, BIT1, true, true, false, false);

    //configLEDMatrix(iolist_Led);
    //bool rij[8] = {1,1,1,1,1,1,1,1};
    //int LED = 00;
    //int ROW = 0;

    //setLed(0,0,true);
    //setLed(6,7,true);
    //setMatrix(true);
    //setLedRow(5, rij);
    //setLedCol(5, rij);

    volatile int buttonValue = 0;

    while(1){
        buttonValue = getButton();
        buttonValue;
/*        refreshMatrix();
        switch (LED){                       // Opdracht 25
            case 00: 
                setMatrix(false);
                setLed(0,0,true);
                if(pinGet(PORT1, BIT1)==0){
                    LED = 01;
                    __delay_cycles(1000000);
                }
                break;
            case 01: 
                setMatrix(false);
                setLed(0,1,true);
                if(pinGet(PORT1, BIT1)==0){
                    LED = 02;
                    __delay_cycles(1000000);
                }
                break;
            case 02: 
                setMatrix(false);
                setLed(0,2,true);
                if(pinGet(PORT1, BIT1)==0){
                    LED = 03;
                    __delay_cycles(1000000);
                }
                break;
            case 03: 
                setMatrix(false);
                setLed(0,3,true);
                if(pinGet(PORT1, BIT1)==0){
                    LED = 04;
                    __delay_cycles(1000000);
                }
                break;
            case 04: 
                setMatrix(false);
                setLed(0,4,true);
                if(pinGet(PORT1, BIT1)==0){
                    LED = 05;
                    __delay_cycles(1000000);
                }
                break;
            case 05: 
                setMatrix(false);
                setLed(0,5,true);
                if(pinGet(PORT1, BIT1)==0){
                    LED = 06;
                    __delay_cycles(1000000);
                }
                break;
            case 06: 
                setMatrix(false);
                setLed(0,6,true);
                if(pinGet(PORT1, BIT1)==0){
                    LED = 07;
                    __delay_cycles(1000000);
                }
                break;
            case 07: 
                setMatrix(false);
                setLed(0,7,true);
                if(pinGet(PORT1, BIT1)==0){
                    LED = 10;
                    __delay_cycles(1000000);
                }
                break;
            case 10: 
                setMatrix(false);
                setLed(1,0,true);
                if(pinGet(PORT1, BIT1)==0){
                    LED = 11;
                    __delay_cycles(1000000);
                }
                break;
            case 11: 
                setMatrix(false);
                setLed(1,1,true);
                if(pinGet(PORT1, BIT1)==0){
                    LED = 12;
                    __delay_cycles(1000000);
                }
                break;
            case 12: 
                setMatrix(false);
                setLed(1,2,true);
                if(pinGet(PORT1, BIT1)==0){
                    LED = 13;
                    __delay_cycles(1000000);
                }
                break;
            case 13: 
                setMatrix(false);
                setLed(1,3,true);
                if(pinGet(PORT1, BIT1)==0){
                    LED = 14;
                    __delay_cycles(1000000);
                }
                break;
            case 14: 
                setMatrix(false);
                setLed(1,4,true);
                if(pinGet(PORT1, BIT1)==0){
                    LED = 15;
                    __delay_cycles(1000000);
                }
                break;
            case 15: 
                setMatrix(false);
                setLed(1,5,true);
                if(pinGet(PORT1, BIT1)==0){
                    LED = 16;
                    __delay_cycles(1000000);
                }
                break;
            case 16: 
                setMatrix(false);
                setLed(1,6,true);
                if(pinGet(PORT1, BIT1)==0){
                    LED = 17;
                    __delay_cycles(1000000);
                }
                break;
            case 17: 
                setMatrix(false);
                setLed(1,7,true);
                if(pinGet(PORT1, BIT1)==0){
                    LED = 20;
                    __delay_cycles(1000000);
                }
                break;
            case 20: 
                setMatrix(false);
                setLed(2,0,true);
                if(pinGet(PORT1, BIT1)==0){
                    LED = 21;
                    __delay_cycles(1000000);
                }
                break;
            case 21: 
                setMatrix(false);
                setLed(2,1,true);
                if(pinGet(PORT1, BIT1)==0){
                    LED = 22;
                    __delay_cycles(1000000);
                }
                break;
            case 22: 
                setMatrix(false);
                setLed(2,2,true);
                if(pinGet(PORT1, BIT1)==0){
                    LED = 23;
                    __delay_cycles(1000000);
                }
                break;
            case 23: 
                setMatrix(false);
                setLed(2,3,true);
                if(pinGet(PORT1, BIT1)==0){
                    LED = 24;
                    __delay_cycles(1000000);
                }
                break;
            case 24: 
                setMatrix(false);
                setLed(2,4,true);
                if(pinGet(PORT1, BIT1)==0){
                    LED = 25;
                    __delay_cycles(1000000);
                }
                break;
            case 25: 
                setMatrix(false);
                setLed(2,5,true);
                if(pinGet(PORT1, BIT1)==0){
                    LED = 26;
                    __delay_cycles(1000000);
                }
                break;
            case 26: 
                setMatrix(false);
                setLed(2,6,true);
                if(pinGet(PORT1, BIT1)==0){
                    LED = 27;
                    __delay_cycles(1000000);
                }
                break;
            case 27: 
                setMatrix(false);
                setLed(2,7,true);
                if(pinGet(PORT1, BIT1)==0){
                    LED = 30;
                    __delay_cycles(1000000);
                }
                break;
            case 30: 
                setMatrix(false);
                setLed(3,0,true);
                if(pinGet(PORT1, BIT1)==0){
                    LED = 31;
                    __delay_cycles(1000000);
                }
                break;
            case 31: 
                setMatrix(false);
                setLed(3,1,true);
                if(pinGet(PORT1, BIT1)==0){
                    LED = 32;
                    __delay_cycles(1000000);
                }
                break;
            case 32: 
                setMatrix(false);
                setLed(3,2,true);
                if(pinGet(PORT1, BIT1)==0){
                    LED = 33;
                    __delay_cycles(1000000);
                }
                break;
            case 33: 
                setMatrix(false);
                setLed(3,3,true);
                if(pinGet(PORT1, BIT1)==0){
                    LED = 34;
                    __delay_cycles(1000000);
                }
                break;
            case 34: 
                setMatrix(false);
                setLed(3,4,true);
                if(pinGet(PORT1, BIT1)==0){
                    LED = 35;
                    __delay_cycles(1000000);
                }
                break;
            case 35: 
                setMatrix(false);
                setLed(3,5,true);
                if(pinGet(PORT1, BIT1)==0){
                    LED = 36;
                    __delay_cycles(1000000);
                }
                break;
            case 36: 
                setMatrix(false);
                setLed(3,6,true);
                if(pinGet(PORT1, BIT1)==0){
                    LED = 37;
                    __delay_cycles(1000000);
                }
                break;
            case 37: 
                setMatrix(false);
                setLed(3,7,true);
                if(pinGet(PORT1, BIT1)==0){
                    LED = 40;
                    __delay_cycles(1000000);
                }
                break;
            case 40: 
                setMatrix(false);
                setLed(4,0,true);
                if(pinGet(PORT1, BIT1)==0){
                    LED = 41;
                    __delay_cycles(1000000);
                }
                break;
            case 41: 
                setMatrix(false);
                setLed(4,1,true);
                if(pinGet(PORT1, BIT1)==0){
                    LED = 42;
                    __delay_cycles(1000000);
                }
                break;
            case 42: 
                setMatrix(false);
                setLed(4,2,true);
                if(pinGet(PORT1, BIT1)==0){
                    LED = 43;
                    __delay_cycles(1000000);
                }
                break;
            case 43: 
                setMatrix(false);
                setLed(4,3,true);
                if(pinGet(PORT1, BIT1)==0){
                    LED = 44;
                    __delay_cycles(1000000);
                }
                break;
            case 44: 
                setMatrix(false);
                setLed(4,4,true);
                if(pinGet(PORT1, BIT1)==0){
                    LED = 45;
                    __delay_cycles(1000000);
                }
                break;
            case 45: 
                setMatrix(false);
                setLed(4,5,true);
                if(pinGet(PORT1, BIT1)==0){
                    LED = 46;
                    __delay_cycles(1000000);
                }
                break;
            case 46: 
                setMatrix(false);
                setLed(4,6,true);
                if(pinGet(PORT1, BIT1)==0){
                    LED = 47;
                    __delay_cycles(1000000);
                }
                break;
            case 47: 
                setMatrix(false);
                setLed(4,7,true);
                if(pinGet(PORT1, BIT1)==0){
                    LED = 50;
                    __delay_cycles(1000000);
                }
                break;
            case 50: 
                setMatrix(false);
                setLed(5,0,true);
                if(pinGet(PORT1, BIT1)==0){
                    LED = 51;
                    __delay_cycles(1000000);
                }
                break;
            case 51: 
                setMatrix(false);
                setLed(5,1,true);
                if(pinGet(PORT1, BIT1)==0){
                    LED = 52;
                    __delay_cycles(1000000);
                }
                break;
            case 52: 
                setMatrix(false);
                setLed(5,2,true);
                if(pinGet(PORT1, BIT1)==0){
                    LED = 53;
                    __delay_cycles(1000000);
                }
                break;
            case 53: 
                setMatrix(false);
                setLed(5,3,true);
                if(pinGet(PORT1, BIT1)==0){
                    LED = 54;
                    __delay_cycles(1000000);
                }
                break;
            case 54: 
                setMatrix(false);
                setLed(5,4,true);
                if(pinGet(PORT1, BIT1)==0){
                    LED = 55;
                    __delay_cycles(1000000);
                }
                break;
            case 55: 
                setMatrix(false);
                setLed(5,5,true);
                if(pinGet(PORT1, BIT1)==0){
                    LED = 56;
                    __delay_cycles(1000000);
                }
                break;
            case 56: 
                setMatrix(false);
                setLed(5,6,true);
                if(pinGet(PORT1, BIT1)==0){
                    LED = 57;
                    __delay_cycles(1000000);
                }
                break;
            case 57: 
                setMatrix(false);
                setLed(5,7,true);
                if(pinGet(PORT1, BIT1)==0){
                    LED = 60;
                    __delay_cycles(1000000);
                }
                break;
            case 60: 
                setMatrix(false);
                setLed(6,0,true);
                if(pinGet(PORT1, BIT1)==0){
                    LED = 61;
                    __delay_cycles(1000000);
                }
                break;
            case 61: 
                setMatrix(false);
                setLed(6,1,true);
                if(pinGet(PORT1, BIT1)==0){
                    LED = 62;
                    __delay_cycles(1000000);
                }
                break;
            case 62: 
                setMatrix(false);
                setLed(6,2,true);
                if(pinGet(PORT1, BIT1)==0){
                    LED = 63;
                    __delay_cycles(1000000);
                }
                break;
            case 63: 
                setMatrix(false);
                setLed(6,3,true);
                if(pinGet(PORT1, BIT1)==0){
                    LED = 64;
                    __delay_cycles(1000000);
                }
                break;
            case 64: 
                setMatrix(false);
                setLed(6,4,true);
                if(pinGet(PORT1, BIT1)==0){
                    LED = 65;
                    __delay_cycles(1000000);
                }
                break;
            case 65: 
                setMatrix(false);
                setLed(6,5,true);
                if(pinGet(PORT1, BIT1)==0){
                    LED = 66;
                    __delay_cycles(1000000);
                }
                break;
            case 66: 
                setMatrix(false);
                setLed(6,6,true);
                if(pinGet(PORT1, BIT1)==0){
                    LED = 67;
                    __delay_cycles(1000000);
                }
                break;
            case 67: 
                setMatrix(false);
                setLed(6,7,true);
                if(pinGet(PORT1, BIT1)==0){
                    LED = 70;
                    __delay_cycles(1000000);
                }
                break;
            case 70: 
                setMatrix(false);
                setLed(7,0,true);
                if(pinGet(PORT1, BIT1)==0){
                    LED = 71;
                    __delay_cycles(1000000);
                }
                break;
            case 71: 
                setMatrix(false);
                setLed(7,1,true);
                if(pinGet(PORT1, BIT1)==0){
                    LED = 72;
                    __delay_cycles(1000000);
                }
                break;
            case 72: 
                setMatrix(false);
                setLed(7,2,true);
                if(pinGet(PORT1, BIT1)==0){
                    LED = 73;
                    __delay_cycles(1000000);
                }
                break;
            case 73: 
                setMatrix(false);
                setLed(7,3,true);
                if(pinGet(PORT1, BIT1)==0){
                    LED = 74;
                    __delay_cycles(1000000);
                }
                break;
            case 74: 
                setMatrix(false);
                setLed(7,4,true);
                if(pinGet(PORT1, BIT1)==0){
                    LED = 75;
                    __delay_cycles(1000000);
                }
                break;
            case 75: 
                setMatrix(false);
                setLed(7,5,true);
                if(pinGet(PORT1, BIT1)==0){
                    LED = 76;
                    __delay_cycles(1000000);
                }
                break;
            case 76: 
                setMatrix(false);
                setLed(7,6,true);
                if(pinGet(PORT1, BIT1)==0){
                    LED = 77;
                    __delay_cycles(1000000);
                }
                break;
            case 77: 
                setMatrix(false);
                setLed(7,7,true);
                if(pinGet(PORT1, BIT1)==0){
                    LED = 00;
                    __delay_cycles(1000000);
                }
                break;
            default: break;
        }
        switch (ROW){                       // Opdracht 26
            case 0:
                setLedRow(0, rij);
                if (pinGet(PORT1, BIT1)==0){
                    setMatrix(false);
                    __delay_cycles(300000);
                    ROW = 1;
                }
                break;
            case 1:
                setLedRow(1, rij);
                if (pinGet(PORT1, BIT1)==0){
                    setMatrix(false);
                    __delay_cycles(300000);
                    ROW = 2;
                }
                break;
            case 2:
                setLedRow(2, rij);
                if (pinGet(PORT1, BIT1)==0){
                    setMatrix(false);
                    __delay_cycles(300000);
                    ROW = 3;
                }
                break;
            case 3:
                setLedRow(3, rij);
                if (pinGet(PORT1, BIT1)==0){
                    setMatrix(false);
                    __delay_cycles(300000);
                    ROW = 4;
                }
                break;
            case 4:
                setLedRow(4, rij);
                if (pinGet(PORT1, BIT1)==0){
                    setMatrix(false);
                    __delay_cycles(300000);
                    ROW = 5;
                }
                break;
            case 5:
                setLedRow(5, rij);
                if (pinGet(PORT1, BIT1)==0){
                    setMatrix(false);
                    __delay_cycles(300000);
                    ROW = 6;
                }
                break;
            case 6:
                setLedRow(6, rij);
                if (pinGet(PORT1, BIT1)==0){
                    setMatrix(false);
                    __delay_cycles(300000);
                    ROW = 7;
                }
                break;
            case 7:
                setLedRow(7, rij);
                if (pinGet(PORT1, BIT1)==0){
                    setMatrix(false);
                    __delay_cycles(300000);
                    ROW = 0;
                }
                break;
            default: break;
        }*/
    }
}
