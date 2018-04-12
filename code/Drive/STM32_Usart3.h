/*******************************文件信息***************************************
 **  文 件 名:    usart3.h
 **  版    本：   V1.0
 **  功    能：   stm32串口3驱动
 **  用    法：
 **  作    者：   草塘
 **  日	   期：2011/06/21
 **----------------------------历史版本信息------------------------------------
 **  修 改 人：
 **  版    本： 
 **  日  　期：
 **  描  　述：
 ******************************************************************************/
#ifndef __STM32_USART3_H__
#define __STM32_USART3_H__

#include "config.h"

#define PrintfBufSize 50//每帧最大字符数
#define PrintfBufArraySize 32//最大32帧溢出

typedef struct   
{	
	u8 UartDataBuf[PrintfBufSize];	

	u8 UartDataLen;

}stPrintfBuf;

u8 Read_NRF24L01_MODE(void);

extern volatile uint8_t Usart3SendDoneFlag;//发送完成标志
extern volatile uint8_t Usart3RecvDoneFlag;//接收完成标志

extern void Usart3Config(void);
uint16_t USART3_SendBuffer(const uint8_t* buffer, uint16_t length);
uint8_t isUSART3SendDone(void);
void Debug_Printf(const char *format, ...);
void Printf_Hex(const uint8_t* hex, uint16_t hex_length);
uint32_t USART3_RecvBuffer(uint8_t* buffer, uint32_t max_length);
uint32_t USART3_DataAvailable(void);
uint8_t isUSART3RecvDone(void);
uint32_t USART3_Flush(void);

#ifndef Printf
#define Printf	Debug_Printf
#endif

void printftest(void);
void Usart3RevHandle(void);
void DealOneCharCmd(u8 cmd);
#endif










