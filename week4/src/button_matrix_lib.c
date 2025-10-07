#include "C:\Users\matth\source\repos\EDMP1\week4\include\button_matrix_lib.h"

void configButtonMatrix(IOPin *iolist){
    for (int r = 0; r < B_MATRIX_ROWS; r++){ // Set Matrix Rows
        pinConfigFunction(iolist[r].port, iolist[r].bit, digital);
        pinSetDir(iolist[r].port, iolist[r].bit, true);
    }

    for (int c = 0; c < B_MATRIX_COLS; c++){ // Set Matrix Collums
        pinConfigFunction(iolist[B_MATRIX_ROWS + c].port, iolist[B_MATRIX_ROWS + c].bit, digital);
        pinSetDir(iolist[B_MATRIX_ROWS + c].port, iolist[B_MATRIX_ROWS + c].bit, false);
        pinConfigInput(iolist[B_MATRIX_ROWS + c].port, iolist[B_MATRIX_ROWS + c].bit, true, false, false, true);
    }
}