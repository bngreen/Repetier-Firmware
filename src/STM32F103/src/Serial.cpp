//Copyright 2015 Bruno N. Green
#include "Serial.h"

#include "stm32f10x_usart.h"

Serial* serial;

bool Serial::available(){
	return !ReadBuffer.IsEmpty();
}
uint8_t Serial::read(){
	while(!Serial::available());
	uint8_t data = ReadBuffer.Read();
	if(readDisabled && !ReadBuffer.IsFull())
		USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);
	return data;
}
void Serial::write(uint8_t b){
	while(WriteBuffer.IsFull());
	WriteBuffer.Write(b);
	if(writeDisabled)
		USART_ITConfig(USART1, USART_IT_TXE, ENABLE);
}

Serial* Serial::Instance = 0;

Serial::Serial(uint32_t baudrate) : readDisabled(false), writeDisabled(true){
	Serial::Instance = this;

	USART_InitTypeDef USART_config;
	GPIO_InitTypeDef GPIO_config;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_AFIO, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);

	NVIC_InitTypeDef NVIC_InitStructure;
	/* Configure the NVIC Preemption Priority Bits */
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0);

	/* Enable the USARTy Interrupt */
	NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 4;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);


	// Configure TX pin

	GPIO_config.GPIO_Pin = GPIO_Pin_9;
	GPIO_config.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_config.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_Init(GPIOA, &GPIO_config);

	// Configure RX pin

	GPIO_config.GPIO_Pin = GPIO_Pin_10;
	GPIO_config.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_config.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_Init(GPIOA, &GPIO_config);

	// Configure USART

	USART_StructInit(&USART_config);
	USART_config.USART_BaudRate = baudrate;
	USART_Init(USART1, &USART_config);

	USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);

	// Enable USART

	USART_Cmd(USART1, ENABLE);
}

void Serial::HandleInterrupt(){
	if(USART_GetITStatus(USART1, USART_IT_RXNE) != RESET)
	{
		ReadBuffer.Write(USART_ReceiveData(USART1));
		if(ReadBuffer.IsFull()){
			USART_ITConfig(USART1, USART_IT_RXNE, DISABLE);
			readDisabled = true;
		}
	}

	if(USART_GetITStatus(USART1, USART_IT_TXE) != RESET)
	{
		if(WriteBuffer.IsEmpty())
		{
			USART_ITConfig(USART1, USART_IT_TXE, DISABLE);
			writeDisabled = true;
			return;
		}
		USART_SendData(USART1, WriteBuffer.Read());
	}
}

extern "C" void USART1_IRQHandler(void)
{
	Serial::GetInstance() -> HandleInterrupt();
}

