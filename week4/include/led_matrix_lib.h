/**
 * @file
 * led_matrix_lib.h
 *
 * Created on: 01-10-2025
 *     Author: M. Vos
 */

#ifndef LED_MATRIX_LIB_H
#define LED_MATRIX_LIB_H

#include <msp430.h>
#include <stdint.h>
#include <stdbool.h>

#include "gpio_lib.h"

#define MATRIX_ROWS 8
#define MATRIX_COLS 8

typedef struct{
    uint16_t port;
    uint16_t bit;
} IOPin;

typedef struct{
    IOPin rowPins[MATRIX_ROWS];
    IOPins colPins[MATRIX_COLS];
} MatrixConfig;



#endif /* LED_MATRIX_LIB_H */
