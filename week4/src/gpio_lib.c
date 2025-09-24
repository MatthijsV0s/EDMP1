#include "...\include\gpio_lib.h"

void pinSet(uint16_t port, uint16_t bit, bool val){
    val ? (*(&P1OUT+port) |= bit) : (*(&P1OUT+port) &= ~bit);
}

void pinToggle(uint16_t port, uint16_t bit){
    *(&P1OUT+port) ^= bit;
}

bool pinGet(uint16_t port, uint16_t bit){
    return (*(&P1IN+port)&bit);
}