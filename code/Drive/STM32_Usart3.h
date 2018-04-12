/*******************************�ļ���Ϣ***************************************
 **  �� �� ��:    usart3.h
 **  ��    ����   V1.0
 **  ��    �ܣ�   stm32����3����
 **  ��    ����
 **  ��    �ߣ�   ����
 **  ��	   �ڣ�2011/06/21
 **----------------------------��ʷ�汾��Ϣ------------------------------------
 **  �� �� �ˣ�
 **  ��    ���� 
 **  ��  ���ڣ�
 **  ��  ������
 ******************************************************************************/
#ifndef __STM32_USART3_H__
#define __STM32_USART3_H__

#include "config.h"

#define PrintfBufSize 50//ÿ֡����ַ���
#define PrintfBufArraySize 32//���32֡���

typedef struct   
{	
	u8 UartDataBuf[PrintfBufSize];	

	u8 UartDataLen;

}stPrintfBuf;

u8 Read_NRF24L01_MODE(void);

extern volatile uint8_t Usart3SendDoneFlag;//������ɱ�־
extern volatile uint8_t Usart3RecvDoneFlag;//������ɱ�־

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










