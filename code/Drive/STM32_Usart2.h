/*******************************�ļ���Ϣ***************************************
 **  �� �� ��:    usart2.h
 **  ��    ����   V1.0
 **  ��    �ܣ�   stm32����2����
 **  ��    ����
 **  ��    �ߣ�   ����
 **  ��	   �ڣ�2011/06/21
 **----------------------------��ʷ�汾��Ϣ------------------------------------
 **  �� �� �ˣ�
 **  ��    ���� 
 **  ��  ���ڣ�
 **  ��  ������
 ******************************************************************************/
#ifndef __STM32_USART2_H__
#define __STM32_USART2_H__

#include "config.h"


extern vu8 Usart2RecvDoneFlag;//������ɱ�־

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
void DealUsart2RevData(vu8* RxBuffer2);//����2�յ����ݴ���
void Usart2RevHandle(void);
#endif










