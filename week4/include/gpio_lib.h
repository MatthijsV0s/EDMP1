#ifndef GPIO_LIB_H
#define GPIO_LIB_H

void pinSet(uint16_t port, uint16_t bit, bool val);         // Set port.bit to val
void pinToggle(uint16_t port, uint16_t bit);                // Toggle port.bit

#endif /* GPIO_LIB_H */