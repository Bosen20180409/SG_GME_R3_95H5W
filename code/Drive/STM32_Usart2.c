/*******************************文件信息***************************************
 **  文 件 名:    Usart2.c
 **  版    本：   V1.0
 **  功    能：   stm32串口2驱动
 **  用    法：
 **  作    者：   草塘
 **  日	   期：
 **----------------------------历史版本信息------------------------------------
 **  修 改 人：
 **  版    本： 
 **  日  　期：
 **  描  　述：
 ******************************************************************************/
#include "STM32_Usart2.h"



////==================================================
//#define USART2_RX_BUF_SIZE  32
//typedef struct   
//{	
//	u8 UsartDataBuf[USART2_RX_BUF_SIZE];	

//	u8 ReadIndex;

//}stUsart2Rx;

//static stUsart2Rx Usart2Rx;
//==================================================

#define USART2_RX_RING_SIZE 512
typedef struct   
{	
    u16 start;
    u16 end;
    u8 buffer[USART2_RX_RING_SIZE];
}USART2_RX_MANAGE;

static USART2_RX_MANAGE g_usart2_rx;
//==================================================



UART_RX_MANAGE g_uart_rx;

/*================================================================= 
 * 功能描述：串口2引脚配置
 * 参    数：无 
 * 返    回：无   
 * 修改日期：2011.12.29  
 *================================================================*/
void Usart2GpioConfig(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;

	/* Configure USART2 Tx(PA.2) as alternate function push-pull */
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	/* Configure USART2 Rx(PA.3) as input floating */
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_Init(GPIOA, &GPIO_InitStructure);	
}
/*================================================================= 
 * 功能描述：串口1配置
 * 参    数：无 
 * 返    回：无   
 * 修改日期：2011.12.29  
 *================================================================*/
void Usart2Config(void)
{
	NVIC_InitTypeDef NVIC_InitStructure;	
//	DMA_InitTypeDef DMA_InitStructure;	
	UART_InitTypeDef UART_InitStructure;	
	
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_UART2,ENABLE); 	
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA,ENABLE);
   
  GPIO_PinAFConfig(GPIOA,GPIO_PinSource2,GPIO_AF_1);
  GPIO_PinAFConfig(GPIOA,GPIO_PinSource3,GPIO_AF_1); //20180118_jade_add
	
	
	NVIC_InitStructure.NVIC_IRQChannel = UART2_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
    
	NVIC_InitStructure.NVIC_IRQChannel = DMA1_Channel4_5_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
	

    
	UART_InitStructure.UART_BaudRate = 19200;//串口波特率
	UART_InitStructure.UART_WordLength = UART_WordLength_8b;//字长为8位数据格式
	UART_InitStructure.UART_StopBits = UART_StopBits_1;//一个停止位
	UART_InitStructure.UART_Parity = UART_Parity_No;//无奇偶校验位
	UART_InitStructure.UART_HardwareFlowControl = UART_HardwareFlowControl_None;//无硬件数据流控制
	UART_InitStructure.UART_Mode = UART_Mode_Rx | UART_Mode_Tx;	//收发模式	
	UART_Init(UART2, &UART_InitStructure); //初始化串口2
    

    
//	DMA_DeInit(DMA1_Channel5);
//	DMA_InitStructure.DMA_PeripheralBaseAddr = (u32)&(UART2->RDR);
//	DMA_InitStructure.DMA_MemoryBaseAddr = (u32)&USART2_RxBuffer[0];
//	DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralSRC;
//	DMA_InitStructure.DMA_BufferSize = sizeof(USART2_RxBuffer);
//	DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
//	DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;
//	DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;
//	DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;
//	DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;
//	DMA_InitStructure.DMA_Priority = DMA_Priority_VeryHigh;
//	DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;
//	DMA_Init(DMA1_Channel5, &DMA_InitStructure);
//	UART_DMACmd(UART2,UART_DMAReq_EN, ENABLE);
//	DMA_Cmd(DMA1_Channel5, ENABLE);
    
    
//	DMA_DeInit(DMA1_Channel4);
//	DMA_InitStructure.DMA_PeripheralBaseAddr = (u32)&(UART2->TDR);
//	//	DMA_InitStructure.DMA_MemoryBaseAddr = (u32)&USART2_TxBuffer[0];
//	DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralDST;
//	//	DMA_InitStructure.DMA_BufferSize = sizeof(USART2_TxBuffer);
//	DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
//	DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;
//	DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;
//	DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;
//	DMA_InitStructure.DMA_Mode = DMA_Mode_Normal;
//	DMA_InitStructure.DMA_Priority = DMA_Priority_VeryHigh;
//	DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;
//	DMA_Init(DMA1_Channel4, &DMA_InitStructure);
//	UART_DMACmd(UART2, UART_DMAReq_EN, ENABLE);
//	DMA_ITConfig(DMA1_Channel4, DMA_IT_TC, ENABLE);
    
	//UART_ITConfig(UART2, UART_IT_IDLE, ENABLE);  //MM32F103没有空闲中断需用定时模拟该功能
	UART_ITConfig(UART2, UART_IT_RXIEN, ENABLE);
	
	UART_Cmd(UART2, ENABLE);
	
	Usart2GpioConfig( );
	

	
}

#define USART2_START_CODE 0xf2

void Usart2SendData(u8 Cmd,vu8* Data, vu16 Len)
{
	
	u8 i = 0;
	u8 CheckSum = 0;
	u8 DataLen = 0;
	u8 UartDataLen = 0;
	u8 UartDataBuf[16];

	UartDataBuf[0] = USART2_START_CODE;//帧头	
	UartDataBuf[1] = Cmd;//命令		
	UartDataBuf[2] = Len;;
	
	DataLen = Len; 
 
	for(i=3; i<DataLen+3; i++) 
	{
		UartDataBuf[i] = Data[i-3];
	}
	
	for(i=0;i<Len+3;i++)
	{
		CheckSum += UartDataBuf[i];
	}

	UartDataBuf[i] = (u8)(CheckSum);

	DataLen = i+1;
	
	UartDataLen = DataLen;
	
#if 0	
	{	
		printf("[%s:%d] ",__FUNCTION__,__LINE__);
		for(i=0;i<UartDataLen;i++)
		{
			printf("%x ",*(UartDataBuf+i));	
		}
		printf("\r\n");
	}
#endif			
		
	for(i=0;i<UartDataLen;i++)
	{
		while((UART2->CSR & UART_IT_TXIEN)==0);//循环发送,直到发送完毕   
			UART2->TDR = (u8) UartDataBuf[i]; 			
	}  
}

void Usart2SendTest(void)
{
	u8 buf[10];
	static u8 nCountData = 0;
	
	nCountData ++;
	
	buf[0] = nCountData;
	buf[1] = 1;
	buf[2] = 2;
	buf[3] = 3;
	buf[4] = 4;
	buf[5] = 0x55;
	
	Usart2SendData(0x02,buf, 6);
}





extern u32 nCountTimeHeartBeatRx;
/*================================================================= 
 * 功能描述：串口中断
 * 参    数：无 
 * 返    回：无   
 * 修改日期：2016.06.17  
 *================================================================*/
void UART2_IRQHandler(void)
{
	USART2_RX_MANAGE *ring;
	u8 Data = 0;
	if(UART_GetITStatus(UART2, UART_IT_RXIEN) != RESET)
	{	
		ring = &g_usart2_rx;	
		Data = UART_ReceiveData(UART2);		
		ring->buffer[ring->end++] = Data;
		if(ring->end >= USART2_RX_RING_SIZE)
		{
			ring->end = 0;
		}


		if(ring->end == ring->start)
		{
			printf("[%s:%d] catch the end....err....err....err....err....err....err....err....err....err....err....err....err....err....err",__FUNCTION__,__LINE__);
		}
		
		UART_ClearITPendingBit(UART2, UART_IT_RXIEN);
	}
//	printf("%x ",Data);
//20171027_ADD_MARK 目前MM32没有空闲中断暂时屏蔽
}


typedef u8 (*FRAME_CALLBACK)(u8* buf, u8 len); 

//#define Usart2RxDebug

#define USART2_START_CODE 0xf2
#define USART2_FRAME_LEN_MIN 4//有效帧最短长度
#define USART2_WAIT_DATA_TIME_MAX 20//等待完整帧的最大时间

u8 ProcessUsart2RxFrame(FRAME_CALLBACK callback)
{
	USART2_RX_MANAGE *ring ;
	u16 StartCount;
	u16 EndCount = 0;
	static u32 WaitTime = 0;
	static u8 pro = 0;//状态机当前状态
	static u32 nCountFrameHeaderErr = 0;
	u8 handle_time_count = 0;
	
	u8 FrameLen = 0;
	u8 i = 0;
	int l,idx;
	u8 buf[32];
	u16 CheckSum = 0;
	
	handle_time_count = 0;
	ring = &g_usart2_rx;
	StartCount = ring->start;
	EndCount = ring->end; 
	if(StartCount != EndCount)//有数据更新
	{
		while(1)
		{
			//处理一段时间要退出此函数，防止数据量大的时候，一直死在这里执行
			handle_time_count ++;
			
			if(handle_time_count > 30)//一个循环最多处理30次数据
			{
				printf("[%s:%d]handle_time_count==================================================\r\n",__FUNCTION__,__LINE__);
				return 1;
			}			
		
			StartCount = ring->start;
			EndCount = ring->end; 
			
			switch (pro)
			{
				//判断数据是否够最短帧数据	(在不知道帧长度的情况下，初步判断是否接收到一帧最短有效帧)
				case 0:
					l = EndCount - StartCount;					

					if (l < 0)
					{						
						l = (USART2_RX_RING_SIZE - StartCount) + EndCount;						
//						printf("[%s:%d].......EndCount:%d........StartCount:%d........\r\n",__FUNCTION__,__LINE__,EndCount,StartCount);
					}
										
					if(l < USART2_FRAME_LEN_MIN)
					{						
						WaitTime ++;
						if(WaitTime > USART2_WAIT_DATA_TIME_MAX)//超时未等到一帧完整数据
						{
							WaitTime = 0;							
					
							printf("[%s:%d]wait data timeout...cur rev:%d   need rev:%d\r\n",__FUNCTION__,__LINE__,l,USART2_FRAME_LEN_MIN);
							ring->start = ring->end; //等不到剩下的数据，清除数据							
						}
						return 0;//帧数据不够,直接退出
					}
					else
					{
						WaitTime = 0;
						pro = 1;//状态转到判断帧头1
					}			
					break;
				case 1://判断帧头1
					if(ring->buffer[StartCount] != USART2_START_CODE)
					{
						printf("[%s:%d]Frame header err:%x\r\n",__FUNCTION__,__LINE__,ring->buffer[StartCount]);		
						nCountFrameHeaderErr ++;
						
						if(nCountFrameHeaderErr > 20)
						{
							printf("[%s:%d]SysReboot...\r\n",__FUNCTION__,__LINE__);	
							delay_ms(100);					
							NVIC_SystemReset();// 复位	
							while(1)
							{
								printf("[%s:%d]SysReboot err...\r\n",__FUNCTION__,__LINE__);				
							}								
						}
						
						ring->buffer[StartCount] = 0;				
						ring->start++;
						if(ring->start >= USART2_RX_RING_SIZE)
						{
							ring->start = 0;
						}							
						pro = 0;//状态转到重新判断帧长						
					}
					else
					{
						//帧头正确，开始接收一帧数据
						pro = 2;//状态转到判断帧长度域
					}
					break;					
				case 2://判断是否接收到帧长度域
					idx = StartCount + 2;//获取长度域索引
					if(idx > USART2_RX_RING_SIZE-1)//回头
					{
						idx = idx - USART2_RX_RING_SIZE;//获取数据长度域的新的索引值
					}

					l = ring->buffer[idx];
					if(l < 0 || l > 10) // 数据长度不在合法范围内
					{
						printf("[%s:%d]data len err...%d\r\n",__FUNCTION__,__LINE__,l);

						ring->buffer[StartCount] = 0;				
						ring->start++;
						if(ring->start >= USART2_RX_RING_SIZE)
						{
							ring->start = 0;
						}

						pro = 0;//状态转到重新判断帧长					
						return 0;
					}
					else//数据长度在范围内
					{
						pro = 3;//状态转到判断当前是否收到一帧完整帧									
					}
					break;
				case 3://根据帧长度域判断是否接收到一帧完整帧
					idx = StartCount + 2;//数据长度域
					if(idx > USART2_RX_RING_SIZE-1)//回头
					{
						idx = idx - USART2_RX_RING_SIZE;//获取数据长度域的新的索引值
					}
					FrameLen = ring->buffer[idx] + 4; //完整帧长度=帧头(1byte)+命令(1byte)+长度(1byte)+数据(nbyte)+校验(1byte)					


					l = EndCount - StartCount;

					if (l < 0)
					{
						l = (USART2_RX_RING_SIZE - StartCount) + EndCount;
					}
										
					if(FrameLen > l)//根据长度域计算，接收到的数据不是一帧完整帧
					{						
						WaitTime ++;
						if(WaitTime > USART2_WAIT_DATA_TIME_MAX)//超时未等到一帧完整数据
						{
							WaitTime = 0;							
					
							printf("[%s:%d]wait data timeout...cur rev:%d   need rev:%d\r\n",__FUNCTION__,__LINE__,l,FrameLen);

							ring->start = ring->end; //等不到剩下的数据，清除数据							
						}
						return 0;//帧数据不够,直接退出
					}
					else
					{
						WaitTime = 0;
						CheckSum = 0;
						pro = 4;//状态转到抽取帧数据
					}
					break;
				case 4://抽取一帧数据
					for(i=0; i<FrameLen; i++)
					{
						idx = StartCount + i;//获取数据
						if(idx > USART2_RX_RING_SIZE-1)//回头
						{
							idx = idx - USART2_RX_RING_SIZE;//获取数据长度域的新的索引值
//							printf("[%s:%d]idx...%d\r\n",__FUNCTION__,__LINE__,idx);
						}						
						
						buf[i] = ring->buffer[idx];
						
					#ifdef Usart2RxDebug
						printf("%02x ",buf[i]);
					#endif
						if(i<FrameLen-1)
						{
							CheckSum += buf[i];
						}
						else
						{
							CheckSum = ((u8)CheckSum);	
							if((u8)CheckSum == buf[i])//校验正确
							{
								break;
							}
							else
							{
								ring->buffer[StartCount] = 0;				
								ring->start++;
								if(ring->start >= USART2_RX_RING_SIZE)
								{
									ring->start = 0;
								}

								pro = 0;//状态转到重新判断帧长		

							#ifdef Usart2RxDebug
								printf("CheckSum err... Cur:%02x   Y:%02x \r\n",CheckSum,buf[i]);
							#else
								printf("[%s:%d]CheckSum err... Cur:%02x   Y:%02x \r\n",__FUNCTION__,__LINE__,CheckSum,buf[i]);
							#endif									

								return 0;
							}
						}
					}
				#ifdef Usart2RxDebug
					printf("    Checksum ok!\r\n");			
				#endif
					for(i=0; i < FrameLen; i++)//清除buf
					{
						idx = StartCount + i;
						if(idx > USART2_RX_RING_SIZE-1)//回头
						{
							idx = idx - USART2_RX_RING_SIZE;
						}											
						ring->buffer[idx] = 0;
					}
					
					idx = StartCount + FrameLen;//获取数据
					if(idx > USART2_RX_RING_SIZE-1)//回头
					{
						idx = idx - USART2_RX_RING_SIZE;//获取数据长度域的新的索引值
					}	
					
					ring->start = idx;
					pro = 0;//状态转到重新判断帧长	
					DealUsart2RevData(buf);//串口1收到数据处理  
					nCountFrameHeaderErr = 0;
					break;
			}
		}
	}
	return 1;
}




static u8 data_proc(u8* buf, u8 len)
{
//	DealUsart2RevData(buf);//串口1收到数据处理  
	return 1;
}

void Usart2RevHandle(void)
{
  ProcessUsart2RxFrame(data_proc);
}

void DealUsart2RevData(vu8* RxBuffer2)//串口2收到数据处理
{
//	u8 Data = 0;	
//	u32 DataTemp = 0;


#if 0
	u8 i = 0;
	u8 Len = 0;	
/*===================================================================*/
/*===================================================================*/
	Len = *(RxBuffer2+2);	
	
	{
		printf("[%s:%d]Usart2 rx:",__FUNCTION__,__LINE__);

		for(i=0;i<Len+4;i++)
		{
			printf("%02x ",*((u8*)RxBuffer2+i));
		}
		printf("\r\n");
	}
#endif
	
	nCountTimeHeartBeatRx = 500;
/*===================================================================*/
/*===================================================================*/	
	
//	for(i=0;i<6;i++)
//	{
//		RFbuffer_315M[i] = *(RxBuffer2+i+3);
//	}
	
//	switch(*(RxBuffer2+1))
//	{
//		case 0:
//			break;
//	}
}


/*================================================================= 
 * 功能描述：串口2DMA发送完成中断
 * 参    数：无 
 * 返    回：无   
 * 修改日期：2016.06.17  
 *================================================================*/
void DMA1_Channel4_5_IRQHandler(void)
{
	if(DMA_GetITStatus(DMA1_IT_TC4) )
	{
		DMA_ClearITPendingBit(DMA1_IT_TC4);

	}
}



