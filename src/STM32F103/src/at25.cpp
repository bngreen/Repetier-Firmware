//Copyright 2015 Bruno N. Green

#include "at25.h"

#include <stdbool.h>
#include "stm32f10x_spi.h"
#include "stm32f10x_gpio.h"

#define AT25WREN    6   //  0000 x110,AT25WRITE enable
#define AT25WRDI    4   //  0000 x100,AT25WRITE disable
#define AT25RDSR    5   //  0000 x101,AT25READ status register
#define AT25WRSR    1   //  0000 x001,AT25WRITE status register
#define AT25READ    3   //  0000 x011,AT25READ sequence
#define AT25WRITE   2   //  0000 x010,AT25WRITE sequence

void SPISelect(){
	GPIO_WriteBit(GPIOA, GPIO_Pin_4, Bit_RESET);
}

void SPIDeSelect(){
	GPIO_WriteBit(GPIOA, GPIO_Pin_4, Bit_SET);
}


uint8_t SPI_TransmitReceive(volatile uint8_t data){
	while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_TXE) == RESET);
	SPI_I2S_SendData(SPI1, data);
	while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_RXNE) == RESET);
	return SPI_I2S_ReceiveData(SPI1);
}

void SPI_Transmit(volatile uint8_t* data, uint32_t size){
	uint32_t i;
	for(i=0;i<size;i++){
		uint8_t dt = data[i];
		SPI_TransmitReceive(dt);
	}
}

void SPI_Receive(volatile uint8_t* buffer, uint32_t size){
	uint32_t i;
	for(i=0;i<size;i++){
		uint8_t data = SPI_TransmitReceive(0);
		buffer[i] = data;
	}
}

uint8_t AT25ReadStatus(){
	SPISelect();
	uint8_t dt = AT25RDSR;
	SPI_Transmit(&dt, 1);
	SPI_Receive(&dt, 1);
	SPIDeSelect();
	return dt;
}

bool AT25IsReady(){
	return (AT25ReadStatus()&1)==0;
}

void AT25SetStatusReg(uint8_t data){

	while(!AT25IsReady());
	uint8_t dt[2] = {AT25WREN, data&0x8c};
	SPISelect();
	SPI_Transmit(dt, 1);
	SPIDeSelect();
	dt[0] = AT25WRSR;
	SPISelect();
	SPI_Transmit(dt, 2);
	SPIDeSelect();

}


void AT25Init(){
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);


	GPIO_InitTypeDef GPIO_InitStructure;

	/* Configure SPIz pins: SCK, MISO and MOSI ---------------------------------*/
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5 | GPIO_Pin_7;
	/* Configure SCK and MOSI pins as Alternate Function Push Pull */
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;

	GPIO_Init(GPIOA, &GPIO_InitStructure);


	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;
	/* Configure MISO pin as Input Floating  */
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_Init(GPIOA, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_Init(GPIOA, &GPIO_InitStructure);

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SPI1, ENABLE);


	SPI_InitTypeDef   SPI_InitStructure;
	SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex;
	SPI_InitStructure.SPI_Mode = SPI_Mode_Master;
	SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b;
	SPI_InitStructure.SPI_CPOL = SPI_CPOL_Low;
	SPI_InitStructure.SPI_CPHA = SPI_CPHA_1Edge;
	SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;
	SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_16;
	SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;
	SPI_InitStructure.SPI_CRCPolynomial = 7;
	SPI_Init(SPI1, &SPI_InitStructure);
	SPI_Cmd(SPI1, ENABLE);

	AT25SetStatusReg(0x80);
}


void AT25Read(uint16_t address, uint16_t size, volatile uint8_t* destination){
	uint8_t buff[3] = { AT25READ, ((address & 0x0F00)>>8), (address & 0x00FF) };
	while(!AT25IsReady());
	SPISelect();
	SPI_Transmit(buff, 3);
	SPI_Receive(destination, size);
	SPIDeSelect();
}
void AT25Write(uint16_t address, uint16_t size, volatile uint8_t* data){
	uint8_t buff[3] = { AT25WREN, ((address & 0x0F00)>>8), (address & 0x00FF) };
	while(!AT25IsReady());
	SPISelect();
	SPI_Transmit(buff, 1);
	SPIDeSelect();
	buff[0] = AT25WRITE;

	SPISelect();
	SPI_Transmit(buff, 3);
	SPI_Transmit(data, size);
	SPIDeSelect();
	while(!AT25IsReady());
}
