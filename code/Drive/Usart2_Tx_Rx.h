/*******************************�ļ���Ϣ***************************************
 **  �� �� ��:    Usart2_Tx_Rx.h
 **  ��    ����   V1.0
 **  ��    �ܣ�   ����2���ͽ��մ���
 **  ��    ����
 **  ��    �ߣ�   ����
 **  ��	   �ڣ�   2013/08
 **----------------------------��ʷ�汾��Ϣ------------------------------------
 **  �� �� �ˣ�
 **  ��    ���� 
 **  ��  ���ڣ�
 **  ��  ������
 ******************************************************************************/
#ifndef __USART2_TX_RX_H__
#define __USART2_TX_RX_H__

#include "config.h"

#define USART2RxFrameStartH 0x55
#define USART2RxFrameStartL 0xAA

#define USART2TxFrameStartH 0xAA
#define USART2TxFrameStartL 0x55


#define Uart2DataSize 32
#define UartDataBufSize 64

extern u8 Usart2RevArkFlag;//ͨ��Ӧ���־


typedef struct   //---------ҩ����Ϣ������--------------
{	
	u8 UartDataBuf[UartDataBufSize][Uart2DataSize];	//�洢ҩ����Ϣ

	u8 UartBufCount;
	u8 UartDataCount;

}stUART2RxBuf;


extern stUART2RxBuf Uart2RxBuf;

extern u16 Usart2RevTimeOut;

void RxUsart2(void);
void RxUsartDeal2(void);




void RollersRunHandle(void);

void Usart2RevRes(void);



		  



#endif


