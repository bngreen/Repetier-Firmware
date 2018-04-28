//Copyright 2015 Bruno N. Green

#ifndef AT25_H
#define AT25_H

#include <stdint.h>

void AT25Init();
void AT25Read(uint16_t address, uint16_t size, volatile uint8_t* destination);
void AT25Write(uint16_t address, uint16_t size, volatile uint8_t* data);

#endif
