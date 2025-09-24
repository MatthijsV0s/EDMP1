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

void pinConfigInput(uint16_t port, uint16_t bit, bool pullResistor, bool pullUP, bool IES, bool IE){
    pullResistor ? (*(&P1REN+port) |= bit) : (*(&P1REN+port) &= ~bit);
    pullUp ? (*(&P1OUT+port) |= bit) : (*(&P1OUT+port) &= ~bit);
    IES ? (*(&P1IES+port) |= bit) : (*(&P1IES+port) &= ~bit);
    IE ? (*(&P1IE+port) |= bit) : (*(&P1IE+port) &= ~bit);
}

void pinSetDir(uint16_t port, uint16_t bit, bool val){
    val ? (*(&P1DIR+port) |= bit) : (*(&P1DIR+port) &= ~bit);
}

void pinConfigFunction(uint16_t port, uint16_t bit, purposeFunction pf){
    switch (pf){
        case digital: 
            (*(&P1SEL0+port) &= ~bit); 
            (*(&P1SEL1+port) &= ~bit); 
            break;
        case primary: 
            (*(&P1SEL0+port) |= bit); 
            (*(&P1SEL1+port) &= ~bit); 
            break;
        case secondary: 
            (*(&P1SEL0+port) &= ~bit); 
            (*(&P1SEL1+port) |= bit); 
            break;
        case tertiary: 
            (*(%P1SELC+port) |= bit); 
            break;
        default: break;
    }
}