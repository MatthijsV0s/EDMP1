#include "C:\Users\matth\source\repos\EDMP1\weekX_ButtonMatrix_PWM\include\button_matrix_lib.h"

static MatrixConfig ButtonMatrixConfig;
//static bool buttonState[B_MATRIX_ROWS][B_MATRIX_COLS];
bool colState[B_MATRIX_COLS];

void configButtonMatrix(IOPin *iolist){
    for (int r = 0; r < B_MATRIX_ROWS; r++){ // Set Matrix Rows
        ButtonMatrixConfig.rowPins[r] = iolist[r];
        pinConfigFunction(iolist[r].port, iolist[r].bit, digital);
        pinSetDir(iolist[r].port, iolist[r].bit, true);
        pinSet(iolist[r].port, iolist[r].bit, 0);   // Default low
    }

    for (int c = 0; c < B_MATRIX_COLS; c++){ // Set Matrix Collums
        ButtonMatrixConfig.colPins[c] = iolist[B_MATRIX_ROWS + c];
        pinConfigFunction(iolist[B_MATRIX_ROWS + c].port, iolist[B_MATRIX_ROWS + c].bit, digital);
        pinSetDir(iolist[B_MATRIX_ROWS + c].port, iolist[B_MATRIX_ROWS + c].bit, false);
        pinConfigInput(iolist[B_MATRIX_ROWS + c].port, iolist[B_MATRIX_ROWS + c].bit, true, false, false, true);
    }

    __bis_SR_register(GIE);     // Enable Global Interrupt
}

int getButton(void){
    
    for (int r = 0; r < B_MATRIX_ROWS; r++){
        pinSet(ButtonMatrixConfig.rowPins[r].port, ButtonMatrixConfig.rowPins[r].bit, 1);

        for (int c = 0; c < B_MATRIX_COLS; c++){
            if (colState[c]){
                colState[c] = false;
                return ((r + 1) * B_MATRIX_COLS + (c + 1));
            }
        }

        pinSet(ButtonMatrixConfig.rowPins[r].port, ButtonMatrixConfig.rowPins[r].bit, 0);
    }
    return 0;
}

#pragma vector=PORT1_VECTOR
__interrupt void buttonMatrix_ISR (void) {
    switch (__even_in_range(P1IV, 0x10)) {
        case 0x00: break;       // none
        case 0x02: break;       // Pin 0
        case 0x04: break;       // Pin 1
        case 0x06: break;       // Pin 2
        case 0x08:              // Pin 3    Col 1
            colState[0] = true;
            break;       
        case 0x0A:              // Pin 4    Col 2
            colState[1] = true;
            break;       
        case 0x0C:              // Pin 5    Col 3
            colState[2] = true;
            break;       
        case 0x0E: break;       // Pin 6
        case 0x10:              // Pin 7    Col 4
            colState[3] = true;
            break;       
        default: _never_executed();
    }
}
