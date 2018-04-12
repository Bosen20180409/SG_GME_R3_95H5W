#ifndef __STK2564_H__
#define __STK2564_H__


#include "config.h"



#define PIN_MB_SPI_CS     GPIO_Pin_4
#define PORT_MB_SPI_CS    GPIOA								 

#define PIN_MB_SPI_CLK     GPIO_Pin_5
#define PORT_MB_SPI_CLK    GPIOA								 

#define PIN_MB_SPI_MISO     GPIO_Pin_6
#define PORT_MB_SPI_MISO    GPIOA		

#define PIN_MB_SPI_MOSI     GPIO_Pin_7
#define PORT_MB_SPI_MOSI    GPIOA		



void STM32_SPI1_Init(void);
u8 SPI1_ReadWriteByte(u8 TxData);
void SPI1_SetSpeed(u8 SPI_BaudRatePrescaler);

#endif 



