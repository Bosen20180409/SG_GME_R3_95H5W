/*******************************文件信息***************************************
 **  文 件 名:    Usart1_Tx_Rx.h
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
#ifndef __USART1_TX_RX_H__
#define __USART1_TX_RX_H__

#include "config.h"



#define Usart1RxFrameStartH 0x55
#define Usart1RxFrameStartL 0xAA

#define Usart1TxFrameStartH 0xAA
#define Usart1TxFrameStartL 0x55


#define Usart1DataSize 32
#define Usart1DataBufSize 64

//extern u8 Usart1RevArkFlag;//通信应答标志
//extern u8 RevArkFlag;//通信应答标志


extern u8 RevA20PowOn;
extern u8 DefTrackDrawMode;
extern u8 UdMoveIndex;
extern u8 LrMoveIndex;
extern u8 TurnOverFlag;
extern u8 SaturationIndex;
extern u8 BrightnessIndex;
extern u8 ContrastIndex;
extern u8 SharpnessIndex;
extern u8 LogoEn;
extern u32 ResourceIndex;

extern u8 CopyFileToFpgaDoneFlag;

#define DEFINE_HT 1
#define DEFINE_CZY 2
extern u8 DEFAULT_SW;

extern u8 PosRoFlag;

extern u8 MoveCursorFlag;

extern u8 MenuOptFlag;

#define DefTrackDrawMode1 0x01
#define DefTrackDrawMode2 0x02


extern u32 nCountTime;
extern u8 DisFlag;
extern u8 A20PowerOn;
extern u8 A20_OSD_LOADING;
extern u8 MosaicFlag;
/*========================================================*/
/*--------------------------------------------------------*/
#define Usart1RxDataSize     12
#define Usart1RxMessageSize  8

typedef struct
{
  uint8_t UartDataLen;     

  uint8_t UartDataBuf[Usart1RxDataSize]; //注意此数组大小需根据串口帧长度设置

}UsartRxMsg;
/*--------------------------------------------------------*/
typedef struct   
{	
	UsartRxMsg RxMessage[Usart1RxMessageSize];

	u8 UartBufCount;//帧数
}stUsart1RxBuf;
/*--------------------------------------------------------*/
/*========================================================*/


/*========================================================*/
/*--------------------------------------------------------*/
#define Usart1TxDataSize     12
#define Usart1TxMessageSize  16

typedef struct
{
  uint8_t UartDataLen;     

  uint8_t UartDataBuf[Usart1TxDataSize]; //注意此数组大小需根据串口帧长度设置

}UsartTxMsg;
/*--------------------------------------------------------*/
typedef struct   
{	
	UsartTxMsg TxMessage[Usart1TxMessageSize];

	u8 UartBufCount;//帧数
}stUsart1TxBuf;
/*--------------------------------------------------------*/
/*========================================================*/

extern stUsart1RxBuf Usart1RxBuf;
extern stUsart1TxBuf Usart1TxBuf;


extern u16 Usart1RevTimeOut;

void RxUSART1(void);
void RxUsartDeal1(void);


void DealUsart1RevData(u8* RxBuffer1);//串口1收到数据处理
void Usart1RxData(u8 RxData);

void SendInputOneMed(void);//已把药送到指定位置
void SendInputRst(void);//加药枪已复位

void SendMedInputState(u8 Stat);//发送加药枪状态

void RollersRunHandle(void);

void USART1RevRes(void);
void SendArk(void);//发送应答


void SendCheckMedInputState(void);//发送查询加药枪状态

u8 Usart1CheckSumHandle(u8 RxBuffer1[30]);

void Usart1SendOneFrame(u8 Cmd,vu8* Data, vu16 Len);

void Usart1SendDataTest(void);

void Usart1RevRes(void);


void Usart1SendTopBoardCmd(u8 Cmd,u8 Data);

void AddDataToUsart1Buf(u8 DataBuf[],u8 DataLen);  //Len为除去命令外的其他数据长度


u8 GetOneChar(u8* Cmd);


void Usart1SendDataTest(void);

		  
void Usart1SendTopBoardCmdu32(u8 Cmd,u32 Data);
void Usart1SendBottomBoardCmd(u8 Cmd,u8 Data);
void Usart1SendTimeCmd(u8 Cmd,u8 Data1,u8 Data2);

#endif


