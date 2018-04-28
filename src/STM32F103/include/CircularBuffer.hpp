//Copyright 2015 Bruno N. Green

#ifndef CIRCULARBUFFER_HPP
#define CIRCULARBUFFER_HPP

#include <stdint.h>
#include "defs.h"

template<typename T, int BSize>
class CircularBuffer{
private:
	T volatile Buffer[BSize];
	volatile uint32_t WritePos;
	volatile uint32_t ReadPos;
public:
	CircularBuffer() : WritePos(0), ReadPos(0){}
	bool Write(T value){
		if(!IsFull()){
			Buffer[WritePos] = value;
			WritePos = (WritePos+1) % BSize;
			return true;
		}
		return false;
	}
	T Read(){
		T data;
		if(!IsEmpty()){
			data = Buffer[ReadPos];
			ReadPos = (ReadPos + 1) % BSize;
		}
		return data;
	}

	bool Read(T* outv){
		if(!IsEmpty()){
			*outv = Buffer[ReadPos];
			ReadPos = (ReadPos + 1) % BSize;
			return true;
		}
		return false;
	}

	uint32_t GetMaxWriteSize(){
		return min<uint32_t>(BSize-GetAvailable()-1, BSize-WritePos-1);
	}

	T* volatile BeginWrite(){
		return (T* volatile)(Buffer + WritePos);
	}
	void EndWrite(uint32_t size){
		WritePos = (WritePos+size) % BSize;
	}
	uint32_t GetAvailable() {
		if(ReadPos > WritePos)
			return (BSize - ReadPos) + WritePos;
		else
			return WritePos - ReadPos;
	}
	bool IsFull() { return GetAvailable() >= BSize - 1; }
	bool IsEmpty() { return GetAvailable() == 0; }
};

#endif
