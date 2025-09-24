#include "...\include\gpio_lib.h"

void pinSet(uint16_t port, uint16_t bit, bool val){
    val ? (*(&0x0202+port) |= bit) : (*(&0x0202+port) &= ~bit);
}