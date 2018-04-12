/*******************************�ļ���Ϣ***************************************
 **  �� �� ��:    Usart1_Tx_Rx.h
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
#ifndef __USART1_TX_RX_H__
#define __USART1_TX_RX_H__

#include "config.h"



#define Usart1RxFrameStartH 0x55
#define Usart1RxFrameStartL 0xAA

#define Usart1TxFrameStartH 0xAA
#define Usart1TxFrameStartL 0x55


#define Usart1DataSize 32
#define Usart1DataBufSize 64

//extern u8 Usart1RevArkFlag;//ͨ��Ӧ���־
//extern u8 RevArkFlag;//ͨ��Ӧ���־


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

  uint8_t UartDataBuf[Usart1RxDataSize]; //ע��������С����ݴ���֡��������

}UsartRxMsg;
/*--------------------------------------------------------*/
typedef struct   
{	
	UsartRxMsg RxMessage[Usart1RxMessageSize];

	u8 UartBufCount;//֡��
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

  uint8_t UartDataBuf[Usart1TxDataSize]; //ע��������С����ݴ���֡��������

}UsartTxMsg;
/*--------------------------------------------------------*/
typedef struct   
{	
	UsartTxMsg TxMessage[Usart1TxMessageSize];

	u8 UartBufCount;//֡��
}stUsart1TxBuf;
/*--------------------------------------------------------*/
/*========================================================*/

extern stUsart1RxBuf Usart1RxBuf;
extern stUsart1TxBuf Usart1TxBuf;


extern u16 Usart1RevTimeOut;

void RxUSART1(void);
void RxUsartDeal1(void);


void DealUsart1RevData(u8* RxBuffer1);//����1�յ����ݴ���
void Usart1RxData(u8 RxData);

void SendInputOneMed(void);//�Ѱ�ҩ�͵�ָ��λ��
void SendInputRst(void);//��ҩǹ�Ѹ�λ

void SendMedInputState(u8 Stat);//���ͼ�ҩǹ״̬

void RollersRunHandle(void);

void USART1RevRes(void);
void SendArk(void);//����Ӧ��


void SendCheckMedInputState(void);//���Ͳ�ѯ��ҩǹ״̬

u8 Usart1CheckSumHandle(u8 RxBuffer1[30]);

void Usart1SendOneFrame(u8 Cmd,vu8* Data, vu16 Len);

void Usart1SendDataTest(void);

void Usart1RevRes(void);


void Usart1SendTopBoardCmd(u8 Cmd,u8 Data);

void AddDataToUsart1Buf(u8 DataBuf[],u8 DataLen);  //LenΪ��ȥ��������������ݳ���


u8 GetOneChar(u8* Cmd);


void Usart1SendDataTest(void);

		  
void Usart1SendTopBoardCmdu32(u8 Cmd,u32 Data);
void Usart1SendBottomBoardCmd(u8 Cmd,u8 Data);
void Usart1SendTimeCmd(u8 Cmd,u8 Data1,u8 Data2);

#endif


