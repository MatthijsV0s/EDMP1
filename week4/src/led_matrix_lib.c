#include "C:\Users\matth\source\repos\EDMP1\week4\include\led_matrix_lib.h"

static MatrixConfig LEDMatrixConfig;
static uint8_t matrixState[MATRIX_ROWS][MATRIX_COLS];

void configLEDMatrix(IOPin *iolist){

    for (int r = 0; r < MATRIX_ROWS; r++) { // Set Matrix Rows
        LEDMatrixConfig.rowPins[r] = iolist[r];
        pinConfigFunction(iolist[r].port, iolist[r].bit, digital);
        pinSetDir(iolist[r].port, iolist[r].bit, true);
    }

    for (int c = 0; c < MATRIX_COLS; c++) { // Set Matrix Collums
        LEDMatrixConfig.colPins[c] = iolist[MATRIX_ROWS + c];
        pinConfigFunction(iolist[MATRIX_ROWS + c].port, iolist[MATRIX_ROWS + c].bit, digital);
        pinSetDir(iolist[MATRIX_ROWS + c].port, iolist[MATRIX_ROWS + c].bit, true);
    }

    setMatrix(0);   // Empty Matrix
}

void setLed(int row, int col, bool val){
    if (row < 0 || row >= MATRIX_ROWS) return;  // Check if row is compatible value
    if (col < 0 || col >= MATRIX_COLS) return;  // Check if col is compatible value
    matrixState[row][col] = val;
}

void setMatrix(bool val){
    for (int r = 0; r < MATRIX_ROWS; r++){
        for (inr c = 0; c < MATRIX_COLS; c++){
            matrixState[r][c] = val;
        }
    }
}