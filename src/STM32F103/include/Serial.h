//Copyright 2015 Bruno N. Green
#ifndef SERIAL_H
#define SERIAL_H

#include <stdint.h>

#include "CircularBuffer.hpp"



class Serial{
private:
	volatile bool readDisabled;
	volatile bool writeDisabled;
	CircularBuffer<uint8_t, 2048> ReadBuffer;
	CircularBuffer<uint8_t, 2048> WriteBuffer;
	static Serial* Instance;
public:
	Serial(uint32_t baudrate);
	bool available();
	uint8_t read();
	void write(uint8_t b);
	static Serial* GetInstance() { return Instance; }
	void HandleInterrupt();
};

extern Serial* serial;

#endif
