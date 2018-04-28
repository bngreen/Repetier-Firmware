#include "delay.h"

volatile uint64_t tickCounter;

uint64_t millis(){
	return tickCounter;
}

void delay(long v){
	uint64_t start = tickCounter;
	while((tickCounter-start) < v);
}


extern "C" void SysTick_Handler(void)
{
	tickCounter++;
}
