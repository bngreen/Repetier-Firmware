#ifndef GPIO_H
#define GPIO_H

#include <stdint.h>

bool GPIORead(int pin);
void GPIOWrite(int pin, int v);
void GPIOSetInput(int pin, bool pullUp = false, bool pullHigh = true);
void GPIOSetOutput(int pin);
void GPIOToggle(int pin);


#endif
