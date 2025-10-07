/**
 * @file
 * button_matrix_lib.h
 *
 * Created on: 07-10-2025
 *     Author: M. Vos
 */

 #ifndef BUTTON_MATRIX_LIB
 #define BUTTON_MATRIX_LIB

#include <msp430.h>

#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>

#include "gpio_lib.h"
#include "led_matrix_lib.h"

#define B_MATRIX_ROWS 4
#define B_MATRIX_COLS 4

/**
 * This function configures the GPIO for the Button-Matrix using an iolist.
 * @brief Configures the GPIO for the Button-Matrix.
 * @param[in] iolist: The list of pins used for the Button-Matrix.
 * 
 */
void configButtonMatrix(IOPin *iolist);

 #endif /* BUTTON_MATRIX_LIB */
