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

void pinSet(uint16_t port, uint16_t bit, bool val);         // Set port.bit to val
void pinToggle(uint16_t port, uint16_t bit);                // Toggle port.bit
bool pinGet(uint16_t port, uint16_t bit);                   // Get digital value of port.bit
void pinConfigInput(uint16_t port, uint16_t bit, bool pullResistor, bool pullUP, bool IES, bool IE);    // Set pin configuration for port.bit
void pinSetDir(uint16_t port, uint16_t bit, bool val);      // Set direction of port.bit to val
void pinConfigFunction(uint16_t port, uint16_t bit, purposeFunction pf);

#endif /* GPIO_LIB_H */