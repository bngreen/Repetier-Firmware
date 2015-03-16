//Copyright 2015 Bruno N. Green
#include "GPIO.h"

#include "stm32f10x_gpio.h"

#define __bit(x) (1 << x)
uint32_t PinToBitMapper[49] = {
		0,//0
		0,//1
		__bit(13),//2
		0,//3
		0,//4
		0,//5
		0,//6
		0,//7
		0,//8
		0,//9
		__bit(0),//10
		__bit(1),//11
		__bit(2),//12
		__bit(3),//13
		__bit(4),//14
		__bit(5),//15
		__bit(6),//16
		__bit(7),//17
		__bit(0),//18
		__bit(1),//19
		__bit(2),//20
		__bit(10),//21
		__bit(11),//22
		0,//23
		0,//24
		__bit(12),//25
		__bit(13),//26
		__bit(14),//27
		__bit(15),//28
		__bit(8),//29
		__bit(9),//30
		__bit(10),//31
		__bit(11),//32
		__bit(12),//33
		__bit(13),//34
		0,//35
		0,//36
		__bit(14),//37
		__bit(15),//38
		__bit(3),//39
		__bit(4),//40
		__bit(5),//41
		__bit(6),//42
		__bit(7),//43
		0,//44
		__bit(8),//45
		__bit(9),//46
		0,//47
		0,//48
};

GPIO_TypeDef EmptyHW;
GPIO_TypeDef* PinToHWMapper[49] = {
		&EmptyHW,
		&EmptyHW,
		GPIOC,
		&EmptyHW,
		&EmptyHW,
		&EmptyHW,
		&EmptyHW,
		&EmptyHW,
		&EmptyHW,
		&EmptyHW,
		GPIOA,
		GPIOA,
		GPIOA,
		GPIOA,
		GPIOA,
		GPIOA,
		GPIOA,
		GPIOA,
		GPIOB,
		GPIOB,
		GPIOB,
		GPIOB,
		GPIOB,
		&EmptyHW,
		&EmptyHW,
		GPIOB,
		GPIOB,
		GPIOB,
		GPIOB,
		GPIOA,
		GPIOA,
		GPIOA,
		GPIOA,
		GPIOA,
		GPIOA,
		&EmptyHW,
		&EmptyHW,
		GPIOA,
		GPIOA,
		GPIOB,
		GPIOB,
		GPIOB,
		GPIOB,
		GPIOB,
		&EmptyHW,
		GPIOB,
		GPIOB,
		&EmptyHW,
		&EmptyHW,
};

bool GPIORead(int pin){
	GPIO_TypeDef* gp = PinToHWMapper[pin];
	if(gp != &EmptyHW)
		return (((gp->IDR) & PinToBitMapper[pin]) != 0);
	return false;
}

void GPIOWrite(int pin, int v){
	if(v)
		PinToHWMapper[pin]->BSRR = PinToBitMapper[pin];
	else
		PinToHWMapper[pin]->BRR = PinToBitMapper[pin];
}

void GPIO_Init_Mode(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin, GPIOMode_TypeDef mode) {
      GPIO_InitTypeDef GPIO_InitStructure;
      GPIO_InitStructure.GPIO_Pin = GPIO_Pin;
      GPIO_InitStructure.GPIO_Mode = mode;
      GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
      GPIO_Init(GPIOx, &GPIO_InitStructure);
}

void GPIOSetInput(int pin, bool pullUp, bool pullHigh){
	GPIO_TypeDef* gp = PinToHWMapper[pin];
	if(gp != &EmptyHW){
		GPIO_Init_Mode(gp, PinToBitMapper[pin], pullUp?(pullHigh?GPIO_Mode_IPU:GPIO_Mode_IPD):GPIO_Mode_IN_FLOATING);
	}
}

void GPIOSetOutput(int pin){
	GPIO_TypeDef* gp = PinToHWMapper[pin];
	if(gp != &EmptyHW){
		GPIO_Init_Mode(gp, PinToBitMapper[pin], GPIO_Mode_Out_PP);
	}
}

void GPIOToggle(int pin){
	GPIO_TypeDef* gp = PinToHWMapper[pin];
	uint32_t mpin = PinToBitMapper[pin];
	if((gp->ODR & mpin) != 0)//is set?
		gp->BRR = mpin;//reset
	else
		gp->BSRR = mpin;//set
}
