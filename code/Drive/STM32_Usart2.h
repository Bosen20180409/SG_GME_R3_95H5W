/*******************************文件信息***************************************
 **  文 件 名:    usart2.h
 **  版    本：   V1.0
 **  功    能：   stm32串口2驱动
 **  用    法：
 **  作    者：   草塘
 **  日	   期：2011/06/21
 **----------------------------历史版本信息------------------------------------
 **  修 改 人：
 **  版    本： 
 **  日  　期：
 **  描  　述：
 ******************************************************************************/
#ifndef __STM32_USART2_H__
#define __STM32_USART2_H__

#include "config.h"


extern vu8 Usart2RecvDoneFlag;//接收完成标志

#define RING_SIZE 1024
typedef struct   
{	
    u16 start;
    u16 end;
    u8 buffer[RING_SIZE];
}UART_RX_MANAGE;

void Usart2GpioConfig(void);
void Usart2Config(void);

u16 USART2_SendBuffer(vu8* buffer, vu16 length);

void Usart2RevHandle(void);
void Usart2SendData(u8 Cmd,vu8* Data, vu16 Len);	
void Usart2SendTest(void);
void DealUsart2RevData(vu8* RxBuffer2);//串口2收到数据处理
void Usart2RevHandle(void);
#endif










