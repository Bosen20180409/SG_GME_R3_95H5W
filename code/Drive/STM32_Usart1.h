/*******************************�ļ���Ϣ***************************************
 **  �� �� ��:    usart1.h
 **  ��    ����   V1.0
 **  ��    �ܣ�   stm32����1����
 **  ��    ����
 **  ��    �ߣ�   ����
 **  ��	   �ڣ�2011/06/21
 **----------------------------��ʷ�汾��Ϣ------------------------------------
 **  �� �� �ˣ�
 **  ��    ���� 
 **  ��  ���ڣ�
 **  ��  ������
 ******************************************************************************/
#ifndef __STM32_USART1_H__
#define __STM32_USART1_H__

#include "config.h"

#define PrintfBufSize 50//ÿ֡����ַ���
#define PrintfBufArraySize 32//���32֡���

typedef struct   
{	
	u8 UartDataBuf[PrintfBufSize];	

	u8 UartDataLen;

}stPrintfBuf;

u8 Read_NRF24L01_MODE(void);

extern volatile uint8_t Usart1SendDoneFlag;//������ɱ�־
extern volatile uint8_t Usart1RecvDoneFlag;//������ɱ�־

extern void Usart1Config(void);
uint16_t USART1_SendBuffer(const uint8_t* buffer, uint16_t length);
uint8_t isUSART1SendDone(void);
void Debug_Printf(const char *format, ...);
void Printf_Hex(const uint8_t* hex, uint16_t hex_length);
uint32_t USART1_RecvBuffer(uint8_t* buffer, uint32_t max_length);
uint32_t USART1_DataAvailable(void);
uint8_t isUSART1RecvDone(void);
uint32_t USART1_Flush(void);

#ifndef Printf
//#define Printf	Debug_Printf
#define Printf	printf
#endif

void printftest(void);
void Usart1RevHandle(void);
void DealOneCharCmd(u8 cmd);
#endif











