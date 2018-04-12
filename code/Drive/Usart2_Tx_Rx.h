/*******************************文件信息***************************************
 **  文 件 名:    Usart2_Tx_Rx.h
 **  版    本：   V1.0
 **  功    能：   串口2发送接收处理
 **  用    法：
 **  作    者：   草塘
 **  日	   期：   2013/08
 **----------------------------历史版本信息------------------------------------
 **  修 改 人：
 **  版    本： 
 **  日  　期：
 **  描  　述：
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

extern u8 Usart2RevArkFlag;//通信应答标志


typedef struct   //---------药盒信息缓冲区--------------
{	
	u8 UartDataBuf[UartDataBufSize][Uart2DataSize];	//存储药格信息

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


