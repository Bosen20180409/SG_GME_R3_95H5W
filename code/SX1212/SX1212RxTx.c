#include "SX1212RxTx.h"

#include <stdbool.h>		//避免bool错误

/*******************************************************************
** Global variables declaration                                   **
*******************************************************************/
u8 RFbuffer[RF_BUFFER_SIZE];       // RF buffer
u8 RFbufferSize;          // RF buffer size
u8 EnableMaster = true;   // Master/Slave selection   //false
u8 SendNextPacket = true; // Indicates when to send the next frame

/*******************************************************************
** OnMasterWireless :                                                     **
********************************************************************
** In  : -                                                        **
** Out : -                                                        **
*******************************************************************/


extern u32 CpuID[3];
extern u8 Freq;
extern void Get165Data(u8 DataBuf[]);
u16 TimeTable[40] = { 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
											0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
											0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
											0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
											0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00};

u8 ButtonCurDataTable[40] = {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
														0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
														0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
														0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
														0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00};

u8 ButtonDataTable[40] = { 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
											0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
											0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
											0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
											0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00};														

u8 ButtonLastDataTable[40] = {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
														0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
														0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
														0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
														0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00};	

u8 ButtonSrcDataTable[40] = {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
														0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
														0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
														0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
														0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00};															

//=================================================================	
//HC165检测到的原始数据序列	
//以下定义针对双人控台														
#define SRC_MASK_BIT_START1   3
#define SRC_MASK_BIT_UP1      2
#define SRC_MASK_BIT_DOWN1    1
#define SRC_MASK_BIT_LEFT1    4
#define SRC_MASK_BIT_RIGHT1   5
#define SRC_MASK_BIT_A1       6   //圈
#define SRC_MASK_BIT_B1       7   //叉
#define SRC_MASK_BIT_C1       35  //三角
#define SRC_MASK_BIT_D1       34  //框
#define SRC_MASK_BIT_E1       33  //L1
#define SRC_MASK_BIT_F1       36  //L2
														
#define SRC_MASK_BIT_L1       37  //R1
#define SRC_MASK_BIT_R1       38  //R2
#define SRC_MASK_BIT_SELECT1  27
#define SRC_MASK_BIT_COIN1    11  //PAUSE
#define SRC_MASK_BIT_HOME1    39	
#define SRC_MASK_BIT_MODE1    15	//DPAD/LS													
//-----------------------------------------------------------------
#define SRC_MASK_BIT_START2   23
#define SRC_MASK_BIT_UP2      22
#define SRC_MASK_BIT_DOWN2    21
#define SRC_MASK_BIT_LEFT2    20
#define SRC_MASK_BIT_RIGHT2   16
#define SRC_MASK_BIT_A2       17  //圈
#define SRC_MASK_BIT_B2       18  //叉
#define SRC_MASK_BIT_C2       19  //三角
#define SRC_MASK_BIT_D2       31  //框
#define SRC_MASK_BIT_E2       30  //L1
#define SRC_MASK_BIT_F2       29  //L2

#define SRC_MASK_BIT_L2       28  //R1
#define SRC_MASK_BIT_R2       24  //R2
#define SRC_MASK_BIT_SELECT2  26
#define SRC_MASK_BIT_COIN2    10  //PAUSE
#define SRC_MASK_BIT_HOME2    25
#define SRC_MASK_BIT_MODE2    14  //DPAD/LS
//-----------------------------------------------------------------

void DataConversationUsb(u8* SrcBuf,u8* DesBuf)
{

//	u8 SrcDataBuf[40];		
	
	u8 i = 0;
//	u8 j = 0;
											
	for(i=0;i<40;i++)
	{
		DesBuf[i] = 0xff;
	}											
											
//=================================================================		
	DesBuf[MASK_BIT_START1]  = SrcBuf[SRC_MASK_BIT_START1];
	DesBuf[MASK_BIT_UP1]     = SrcBuf[SRC_MASK_BIT_UP1];
	DesBuf[MASK_BIT_DOWN1]   = SrcBuf[SRC_MASK_BIT_DOWN1];
	DesBuf[MASK_BIT_LEFT1]   = SrcBuf[SRC_MASK_BIT_LEFT1];
	DesBuf[MASK_BIT_RIGHT1]  = SrcBuf[SRC_MASK_BIT_RIGHT1];
	DesBuf[MASK_BIT_A1]      = SrcBuf[SRC_MASK_BIT_A1];
	DesBuf[MASK_BIT_B1]      = SrcBuf[SRC_MASK_BIT_B1];
	DesBuf[MASK_BIT_C1]      = SrcBuf[SRC_MASK_BIT_C1];
	DesBuf[MASK_BIT_D1]      = SrcBuf[SRC_MASK_BIT_D1];
	DesBuf[MASK_BIT_E1]      = SrcBuf[SRC_MASK_BIT_E1];
	DesBuf[MASK_BIT_F1]      = SrcBuf[SRC_MASK_BIT_F1];
	DesBuf[MASK_BIT_L1]      = SrcBuf[SRC_MASK_BIT_L1];
	DesBuf[MASK_BIT_R1]      = SrcBuf[SRC_MASK_BIT_R1];
	DesBuf[MASK_BIT_SELECT1] = SrcBuf[SRC_MASK_BIT_SELECT1];
	DesBuf[MASK_BIT_COIN1]   = SrcBuf[SRC_MASK_BIT_COIN1];	
	DesBuf[MASK_BIT_HOME1]   = SrcBuf[SRC_MASK_BIT_HOME1];
	DesBuf[MASK_BIT_MODE1]   = SrcBuf[SRC_MASK_BIT_MODE1];		
//-----------------------------------------------------------------	
	DesBuf[MASK_BIT_START2] = SrcBuf[SRC_MASK_BIT_START2];
	DesBuf[MASK_BIT_UP2]    = SrcBuf[SRC_MASK_BIT_UP2];
	DesBuf[MASK_BIT_DOWN2]  = SrcBuf[SRC_MASK_BIT_DOWN2];
	DesBuf[MASK_BIT_LEFT2]  = SrcBuf[SRC_MASK_BIT_LEFT2];
	DesBuf[MASK_BIT_RIGHT2] = SrcBuf[SRC_MASK_BIT_RIGHT2];
	DesBuf[MASK_BIT_A2]     = SrcBuf[SRC_MASK_BIT_A2];
	DesBuf[MASK_BIT_B2]     = SrcBuf[SRC_MASK_BIT_B2];
	DesBuf[MASK_BIT_C2]     = SrcBuf[SRC_MASK_BIT_C2];
	DesBuf[MASK_BIT_D2]     = SrcBuf[SRC_MASK_BIT_D2];
	DesBuf[MASK_BIT_E2]     = SrcBuf[SRC_MASK_BIT_E2];
	DesBuf[MASK_BIT_F2]     = SrcBuf[SRC_MASK_BIT_F2];
	DesBuf[MASK_BIT_L2]      = SrcBuf[SRC_MASK_BIT_L2];
	DesBuf[MASK_BIT_R2]      = SrcBuf[SRC_MASK_BIT_R2];
	DesBuf[MASK_BIT_SELECT2] = SrcBuf[SRC_MASK_BIT_SELECT2];
	DesBuf[MASK_BIT_COIN2]   = SrcBuf[SRC_MASK_BIT_COIN2];	
	DesBuf[MASK_BIT_HOME2]   = SrcBuf[SRC_MASK_BIT_HOME2];
	DesBuf[MASK_BIT_MODE2]   = SrcBuf[SRC_MASK_BIT_MODE2];	
//=================================================================				
}

void DataConversation(u8* SrcBuf,u8* DesBuf)
{

	u8 SrcDataBuf[40];		
	
	u8 i = 0;
	u8 j = 0;
											
	for(i=0;i<40;i++)
	{
		SrcDataBuf[i] = 0xff;
	}											
											
//=================================================================		
	SrcDataBuf[MASK_BIT_START1]  = SrcBuf[SRC_MASK_BIT_START1];
	SrcDataBuf[MASK_BIT_UP1]     = SrcBuf[SRC_MASK_BIT_UP1];
	SrcDataBuf[MASK_BIT_DOWN1]   = SrcBuf[SRC_MASK_BIT_DOWN1];
	SrcDataBuf[MASK_BIT_LEFT1]   = SrcBuf[SRC_MASK_BIT_LEFT1];
	SrcDataBuf[MASK_BIT_RIGHT1]  = SrcBuf[SRC_MASK_BIT_RIGHT1];
	SrcDataBuf[MASK_BIT_A1]      = SrcBuf[SRC_MASK_BIT_A1];
	SrcDataBuf[MASK_BIT_B1]      = SrcBuf[SRC_MASK_BIT_B1];
	SrcDataBuf[MASK_BIT_C1]      = SrcBuf[SRC_MASK_BIT_C1];
	SrcDataBuf[MASK_BIT_D1]      = SrcBuf[SRC_MASK_BIT_D1];
	SrcDataBuf[MASK_BIT_E1]      = SrcBuf[SRC_MASK_BIT_E1];
	SrcDataBuf[MASK_BIT_F1]      = SrcBuf[SRC_MASK_BIT_F1];
	SrcDataBuf[MASK_BIT_L1]      = SrcBuf[SRC_MASK_BIT_L1];
	SrcDataBuf[MASK_BIT_R1]      = SrcBuf[SRC_MASK_BIT_R1];
	SrcDataBuf[MASK_BIT_SELECT1] = SrcBuf[SRC_MASK_BIT_SELECT1];
	SrcDataBuf[MASK_BIT_COIN1]   = SrcBuf[SRC_MASK_BIT_COIN1];	
	SrcDataBuf[MASK_BIT_HOME1]   = SrcBuf[SRC_MASK_BIT_HOME1];
	SrcDataBuf[MASK_BIT_MODE1]   = SrcBuf[SRC_MASK_BIT_MODE1];		
//-----------------------------------------------------------------	
	SrcDataBuf[MASK_BIT_START2] = SrcBuf[SRC_MASK_BIT_START2];
	SrcDataBuf[MASK_BIT_UP2]    = SrcBuf[SRC_MASK_BIT_UP2];
	SrcDataBuf[MASK_BIT_DOWN2]  = SrcBuf[SRC_MASK_BIT_DOWN2];
	SrcDataBuf[MASK_BIT_LEFT2]  = SrcBuf[SRC_MASK_BIT_LEFT2];
	SrcDataBuf[MASK_BIT_RIGHT2] = SrcBuf[SRC_MASK_BIT_RIGHT2];
	SrcDataBuf[MASK_BIT_A2]     = SrcBuf[SRC_MASK_BIT_A2];
	SrcDataBuf[MASK_BIT_B2]     = SrcBuf[SRC_MASK_BIT_B2];
	SrcDataBuf[MASK_BIT_C2]     = SrcBuf[SRC_MASK_BIT_C2];
	SrcDataBuf[MASK_BIT_D2]     = SrcBuf[SRC_MASK_BIT_D2];
	SrcDataBuf[MASK_BIT_E2]     = SrcBuf[SRC_MASK_BIT_E2];
	SrcDataBuf[MASK_BIT_F2]     = SrcBuf[SRC_MASK_BIT_F2];
	SrcDataBuf[MASK_BIT_L2]      = SrcBuf[SRC_MASK_BIT_L2];
	SrcDataBuf[MASK_BIT_R2]      = SrcBuf[SRC_MASK_BIT_R2];
	SrcDataBuf[MASK_BIT_SELECT2] = SrcBuf[SRC_MASK_BIT_SELECT2];
	SrcDataBuf[MASK_BIT_COIN2]   = SrcBuf[SRC_MASK_BIT_COIN2];	
	SrcDataBuf[MASK_BIT_HOME2]   = SrcBuf[SRC_MASK_BIT_HOME2];
	SrcDataBuf[MASK_BIT_MODE2]   = SrcBuf[SRC_MASK_BIT_MODE2];	
//=================================================================	
	for(i=0; i<5; i++)
	{
		for(j=0; j<8; j++)
		{
			if(SrcDataBuf[i*8+j] == 0)
			{
				DesBuf[i] &= ~(1<<j);
			}
			else
			{
				DesBuf[i] |= (1<<j);
			}
		}
	}			
}

#define RF_STOP_WORK_TIME 4000
#define USB_STOP_WORK_TIME 50000


#define RF_WORK_MAX_TIME 8000
#define USB_WORK_MAX_TIME 100000
u32 nCountTimeHeartBeatRx = 0;
//#define RX_DEBUG
void OnMasterWireless(void)
{	
	u8 ReturnCode = 0xff;
	u8 ChangeFlag = 0;
//	u16 nCount = 0;
	static u32 Data = 0;
//	static u8 LastDataBuf[6];
	u8 CurDataBuf[6];
	static u32 nCountChange = 0;
	u8 i = 0;
//	u8 j = 0;
	static u32 nCountTimeHeartBeatRxTemp = 0;
	
	Get165Data(ButtonCurDataTable);

	ChangeFlag = 0;
	for(i=0;i<40;i++)
	{
		if(ButtonLastDataTable[i] != ButtonCurDataTable[i])
		{
			ChangeFlag = i;
			ButtonLastDataTable[i] = ButtonCurDataTable[i];
		}
	}	
	
	if(ChangeFlag > 0)
	{
		if(nCountTimeHeartBeatRx == 0)
		{
			nCountChange = RF_WORK_MAX_TIME;
		}
		else
		{
			nCountChange = USB_WORK_MAX_TIME;
		}
	#ifdef RX_DEBUG
		printf("[%s:%d]rev data...change_idx:%d\r\n",__FUNCTION__,__LINE__,ChangeFlag);
		printf("00 01 02 03 04 05 06 07 08 09 10 11 12 13 14 15 16 17 18 19");
		printf("\r\n");
		for(i=0;i<20;i++)
		{
			printf("%x  ",ButtonCurDataTable[i]);			
		}	
		printf("\r\n");
		
		printf("20 21 22 23 24 25 26 27 28 29 30 31 32 33 34 35 36 37 38 39");
		printf("\r\n");
		for(i=20;i<40;i++)
		{
			printf("%x  ",ButtonCurDataTable[i]);			
		}		
		printf("\r\n\r\n");
	#endif
	}
//return;
//	printf("%x %x %x %x %x\r\n",DataBuf[0],DataBuf[1],DataBuf[2],DataBuf[3],DataBuf[4]);	
	
	Data ++;
	if(Freq == F315M)
	{
		CurDataBuf[5] = 0x55;
	}
	else
	{
		CurDataBuf[5] = 0xaa;
	}

	for(i=0;i<40;i++)
	{
		if(TimeTable[i] > 0)
		{		
			ButtonSrcDataTable[i] = 0;				
		}
		else
		{
			ButtonSrcDataTable[i] = 1;		
		}
	}

	DataConversation(ButtonSrcDataTable,CurDataBuf);
	
	RFbuffer[0] = CurDataBuf[0];
	
	RFbuffer[1] = CurDataBuf[1];
	RFbuffer[2] = CurDataBuf[2];
	RFbuffer[3] = CurDataBuf[3];
	RFbuffer[4] = CurDataBuf[4];
	
	RFbuffer[5] = CurDataBuf[5];
	
//	printf("[%s:%d]SendId...%x  %x  %x  %x  %x\r\n",__FUNCTION__,__LINE__,RFbuffer[0],RFbuffer[1],RFbuffer[2],RFbuffer[3],RFbuffer[4]);
//	delay_ms(1);
	Usart2RevHandle( );	
	if(nCountTimeHeartBeatRx > 0)
	{
		nCountTimeHeartBeatRx --;		
	}
	
	if(nCountChange > 0)
	{
		nCountChange --;
		if(nCountChange == 0)
		{
			printf("[%s:%d]standby...\r\n",__FUNCTION__,__LINE__);
			Led0_Off;
			SetRFMode(RF_STANDBY);
			WKUP_Init( );
			nCountChange = RF_STOP_WORK_TIME;
//			Usart1Config();//调试
			NVIC_SystemReset();// 复位	
//			printf("[%s:%d]exit standby...\r\n",__FUNCTION__,__LINE__);
		}
	}
		
	if(nCountChange > 0)//长时间不操作，不发送数据
	{
		if(nCountTimeHeartBeatRx == 0)
		{
			if(nCountTimeHeartBeatRxTemp != 0)
			{
				printf("[%s:%d]wireless...\r\n",__FUNCTION__,__LINE__);
			}			
			
			SendRfFrame(RFbuffer, 6, &ReturnCode);
		}
		else
		{
//			if(nCountTimeHeartBeatRx == 499)
//			{
//				printf("[%s:%d]usb...\r\n",__FUNCTION__,__LINE__);
//			}
			Usart2SendData(0x02,RFbuffer, 6);
			delay_ms(5);
		}
	}
	else if(nCountChange == RF_STOP_WORK_TIME)
	{
		SetRFMode(RF_STANDBY);
	}
	
	nCountTimeHeartBeatRxTemp = nCountTimeHeartBeatRx;
}
extern void Ps3SendButtonData(void);
//#define RX_DEBUG
void OnMasterUsbPC(void)
{	
//	u8 ReturnCode = 0xff;
	u8 ChangeFlag = 0;
	static u16 nCount = 0;
//	static u32 Data = 0;
//	static u8 LastDataBuf[6];
//	u8 CurDataBuf[6];
//	static u32 nCountChange = 0;
	u8 i = 0;
//	u8 j = 0;
	
	Get165Data(ButtonCurDataTable);

	ChangeFlag = 0;
	for(i=0;i<40;i++)
	{
		if(ButtonLastDataTable[i] != ButtonCurDataTable[i])
		{
			ChangeFlag = i;
			ButtonLastDataTable[i] = ButtonCurDataTable[i];
		}
	}	
	
	if(ChangeFlag > 0)
	{
//		if(nCountTimeHeartBeatRx == 0)
//		{
//			nCountChange = RF_WORK_MAX_TIME;
//		}
//		else
//		{
//			nCountChange = USB_WORK_MAX_TIME;
//		}
	#ifdef RX_DEBUG
		printf("[%s:%d]rev data...change_idx:%d\r\n",__FUNCTION__,__LINE__,ChangeFlag);
		printf("00 01 02 03 04 05 06 07 08 09 10 11 12 13 14 15 16 17 18 19");
		printf("\r\n");
		for(i=0;i<20;i++)
		{
			printf("%x  ",ButtonCurDataTable[i]);			
		}	
		printf("\r\n");
		
		printf("20 21 22 23 24 25 26 27 28 29 30 31 32 33 34 35 36 37 38 39");
		printf("\r\n");
		for(i=20;i<40;i++)
		{
			printf("%x  ",ButtonCurDataTable[i]);			
		}		
		printf("\r\n\r\n");
	#endif
		
		
		for(i=0;i<40;i++)
		{
			if(TimeTable[i] > 0)
			{		
				ButtonSrcDataTable[i] = 0;				
			}
			else
			{
				ButtonSrcDataTable[i] = 1;		
			}
		}
		DataConversationUsb(ButtonSrcDataTable,ButtonDataTable);
		Ps3ParseSrcData(ButtonDataTable);
		Ps3SendButtonData( );	
	}


	nCount ++;
	if(nCount > 0)
	{
		nCount = 0;
		Ps3SendButtonData( );
	}		
}

void SX1212SendData(u32 Data)
{
	u8 ReturnCode = 0xff;
	u16 nCount = 0;
	u32 DataTemp = 0;

	
	DataTemp = Data;
	
	RFbuffer[0] = (u8)(CpuID[0]>>24);
	RFbuffer[1] = (u8)(CpuID[0]>>16);
	RFbuffer[2] = (u8)(CpuID[0]>>8);
	RFbuffer[3] = (u8)(CpuID[0]>>0);
	RFbuffer[4] = 0x04;
	
	RFbuffer[5] = 0x05;
	
	RFbuffer[6] = *((u8*)(&DataTemp) + 3);
	RFbuffer[7] = *((u8*)(&DataTemp) + 2);
	RFbuffer[8] = *((u8*)(&DataTemp) + 1);
	RFbuffer[9] = *((u8*)(&DataTemp) + 0);
	
//	printf("[%s:%d]SendId...%x  %x  %x  %x\r\n",__FUNCTION__,__LINE__,RFbuffer[0],RFbuffer[1],RFbuffer[2],RFbuffer[3]);
	
	SendRfFrame(RFbuffer, 10, &ReturnCode);		
	while(1)
	{
		if(ReturnCode == OK)
		{
			Led0_Reverse( );
//			printf("[%s:%d]ReturnCode:%d\r\n",__FUNCTION__,__LINE__,ReturnCode);
			break;
		}
		else
		{
			nCount ++;
			if(nCount > 5)
			{
				nCount = 0;
				break;
			}
			delay_ms(100);
		}
	}
}

/*******************************************************************
** OnSlave :                                                      **
********************************************************************
** In  : -                                                        **
** Out : -                                                        **
*******************************************************************/
void OnSlave(void)
{
	u8 ReturnCode = 0xff;
	static u32 CurData = 0;
//	static u32 LastData = 0;
	ReturnCode = 0xff;
	RFbufferSize = 0;
	// Receives the frame from the RF chip
	
	RFbuffer[0] = 0x00;
	RFbuffer[1] = 0x00;
	RFbuffer[2] = 0x00;
	RFbuffer[3] = 0x00;
	RFbuffer[4] = 0x00;
	RFbuffer[5] = 0x00;

	ReceiveRfFrame(RFbuffer, (u8*)&RFbufferSize, &ReturnCode);
	
//	printf("[%s:%d]=====================\r\n",__FUNCTION__,__LINE__);
	// Tests if we have received a frame
	if ((ReturnCode == OK)&&(RFbuffer[5] == 0xaa))
	{
		CurData = RFbuffer[0];
		CurData <<= 8;
		CurData |= RFbuffer[1];
		CurData <<= 8;
		CurData |= RFbuffer[2];
		CurData <<= 8;
		CurData |= RFbuffer[3];
		printf("[%s:%d]Rev data  %x    RFbufferSize:%d\r\n",__FUNCTION__,__LINE__,CurData,RFbufferSize);
		
		
		
//		if(CurData != LastData)
//		{
//			if(CurData == LastData+1)
//			{
////				printf("[%s:%d]Rev ok...\r\n",__FUNCTION__,__LINE__);
//			}
//			else
//			{
//				printf("[%s:%d]Rev err...  %d  %d\r\n",__FUNCTION__,__LINE__,CurData,LastData);
//			}
//			LastData = CurData;
//		}
//		else
//		{
//			printf("[%s:%d]CurData == LastData\r\n",__FUNCTION__,__LINE__);
//		}
//		
//		Led0_Reverse( );
//		// Tests if the received buffer size is greater than 0
//		if (RFbufferSize > 0)
//		{
//			
//		}
	}
	delay_ms(100);
}


void SX1212Test(void)
{
	EnableMaster = true;	
	while(1)
	{
		if(EnableMaster)
		{
			OnMasterWireless();
//			OnSlave();
		}
		else
		{
//			OnMasterWireless();
			OnSlave();
		}		
	}
}


