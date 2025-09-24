/**
 * @file
 * gpio_lib.h
 *
 * Created on: 23-09-2025
 *     Author: M. Vos
 */

#ifndef GPIO_LIB_H
#define GPIO_LIB_H

#define PORT1 0x0000
#define PORT2 0x0001
#define PORT3 0x0020
#define PORT4 0x0021

typedef enum {
    digital, 
    primary, 
    secondary, 
    tertiary
} purposeFunction;

/**
 *
 * @brief Sets an output to a pin.
 * @param[in] port: The port register address.
 * @param[in] bit:  The specific pin to toggle on that port.
 * @param[in] val:  The value that the pin gets.
 *
 */
void pinSet(uint16_t port, uint16_t bit, bool val);

/**
 *
 * @brief Toggles a pin.
 * @param[in] port: The port register address.
 * @param[in] bit:  The specific pin to toggle on that port.
 *
 */
void pinToggle(uint16_t port, uint16_t bit);

/**
 *
 * @brief Gets an value of a pin.
 * @param[in] port: The port register address.
 * @param[in] bit:  The specific pin to toggle on that port.
 * @returns The value of the pin.
 *
 */
bool pinGet(uint16_t port, uint16_t bit);

/**
 * Sets all the input configurations of a pin except the direction and function of the pin.
 * @brief Sets the input configuration of a pin.
 * @param[in] port:         The port register address.
 * @param[in] bit:          The specific pin to toggle on that port.
 * @param[in] pullResistor: Indicates if the pin gets a pullresistor.
 * @param[in] pullUP:       Indicates which resistor the pin get: 1 Up/0 Down.
 * @param[in] IES:          Indicates on which edge an interrupt is triggerd.
 * @param[in] IE:           Indicates if interrupt is enabled.
 *
 */
void pinConfigInput(uint16_t port, uint16_t bit, bool pullResistor, bool pullUP, bool IES, bool IE);

/**
 *
 * @brief Sets the direction of a pin.
 * @param[in] port: The port register address.
 * @param[in] bit:  The specific pin to toggle on that port.
 * @param[in] val:  The direction of the pin: 1 OUTPUT/0 INPUT.
 *
 */
void pinSetDir(uint16_t port, uint16_t bit, bool val);

/**
 * Sets the function of a pin to Digital/Primary/Secondary/Teriary.
 * @brief Sets the function of a pin.
 * @param[in] port: The port register address.
 * @param[in] bit:  The specific pin to toggle on that port.
 * @param[in] pf:   The function of the pin.
 *
 */
void pinConfigFunction(uint16_t port, uint16_t bit, purposeFunction pf);

#endif /* GPIO_LIB_H */