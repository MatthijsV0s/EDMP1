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
    IOPin colPins[MATRIX_COLS];
} MatrixConfig;

/**
 * This function configures the GPIO for the LED-Matrix using an iolist.
 * @brief Configures the GPIO for the LED-Matrix.
 * @param[in] iolist: The list of pins used for the LED-Matrix.
 * 
 */
void configLEDMatrix(IOPin *iolist);

/**
 *
 * @brief Sets a specific LED in the LED-Matrix.
 * @param[in] row:  The row of the LED.
 * @param[in] col:  The collum of the LED.
 * @param[in] val:  The value the LED gets.
 *
 */
 void setLed(int row, int col, bool val);

#endif /* LED_MATRIX_LIB_H */
