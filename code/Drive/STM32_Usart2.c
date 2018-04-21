/*******************************�ļ���Ϣ***************************************
 **  �� �� ��:    Usart2.c
 **  ��    ����   V1.0
 **  ��    �ܣ�   stm32����2����
 **  ��    ����
 **  ��    �ߣ�   ����
 **  ��	   �ڣ�
 **----------------------------��ʷ�汾��Ϣ------------------------------------
 **  �� �� �ˣ�
 **  ��    ���� 
 **  ��  ���ڣ�
 **  ��  ������
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
 * ��������������2��������
 * ��    ������ 
 * ��    �أ���   
 * �޸����ڣ�2011.12.29  
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
 * ��������������1����
 * ��    ������ 
 * ��    �أ���   
 * �޸����ڣ�2011.12.29  
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
	

    
	UART_InitStructure.UART_BaudRate = 19200;//���ڲ�����
	UART_InitStructure.UART_WordLength = UART_WordLength_8b;//�ֳ�Ϊ8λ���ݸ�ʽ
	UART_InitStructure.UART_StopBits = UART_StopBits_1;//һ��ֹͣλ
	UART_InitStructure.UART_Parity = UART_Parity_No;//����żУ��λ
	UART_InitStructure.UART_HardwareFlowControl = UART_HardwareFlowControl_None;//��Ӳ������������
	UART_InitStructure.UART_Mode = UART_Mode_Rx | UART_Mode_Tx;	//�շ�ģʽ	
	UART_Init(UART2, &UART_InitStructure); //��ʼ������2
    

    
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
    
	//UART_ITConfig(UART2, UART_IT_IDLE, ENABLE);  //MM32F103û�п����ж����ö�ʱģ��ù���
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

	UartDataBuf[0] = USART2_START_CODE;//֡ͷ	
	UartDataBuf[1] = Cmd;//����		
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
		while((UART2->CSR & UART_IT_TXIEN)==0);//ѭ������,ֱ���������   
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
 * ���������������ж�
 * ��    ������ 
 * ��    �أ���   
 * �޸����ڣ�2016.06.17  
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
//20171027_ADD_MARK ĿǰMM32û�п����ж���ʱ����
}


typedef u8 (*FRAME_CALLBACK)(u8* buf, u8 len); 

//#define Usart2RxDebug

#define USART2_START_CODE 0xf2
#define USART2_FRAME_LEN_MIN 4//��Ч֡��̳���
#define USART2_WAIT_DATA_TIME_MAX 20//�ȴ�����֡�����ʱ��

u8 ProcessUsart2RxFrame(FRAME_CALLBACK callback)
{
	USART2_RX_MANAGE *ring ;
	u16 StartCount;
	u16 EndCount = 0;
	static u32 WaitTime = 0;
	static u8 pro = 0;//״̬����ǰ״̬
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
	if(StartCount != EndCount)//�����ݸ���
	{
		while(1)
		{
			//����һ��ʱ��Ҫ�˳��˺�������ֹ���������ʱ��һֱ��������ִ��
			handle_time_count ++;
			
			if(handle_time_count > 30)//һ��ѭ����ദ��30������
			{
				printf("[%s:%d]handle_time_count==================================================\r\n",__FUNCTION__,__LINE__);
				return 1;
			}			
		
			StartCount = ring->start;
			EndCount = ring->end; 
			
			switch (pro)
			{
				//�ж������Ƿ����֡����	(�ڲ�֪��֡���ȵ�����£������ж��Ƿ���յ�һ֡�����Ч֡)
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
						if(WaitTime > USART2_WAIT_DATA_TIME_MAX)//��ʱδ�ȵ�һ֡��������
						{
							WaitTime = 0;							
					
							printf("[%s:%d]wait data timeout...cur rev:%d   need rev:%d\r\n",__FUNCTION__,__LINE__,l,USART2_FRAME_LEN_MIN);
							ring->start = ring->end; //�Ȳ���ʣ�µ����ݣ��������							
						}
						return 0;//֡���ݲ���,ֱ���˳�
					}
					else
					{
						WaitTime = 0;
						pro = 1;//״̬ת���ж�֡ͷ1
					}			
					break;
				case 1://�ж�֡ͷ1
					if(ring->buffer[StartCount] != USART2_START_CODE)
					{
						printf("[%s:%d]Frame header err:%x\r\n",__FUNCTION__,__LINE__,ring->buffer[StartCount]);		
						nCountFrameHeaderErr ++;
						
						if(nCountFrameHeaderErr > 20)
						{
							printf("[%s:%d]SysReboot...\r\n",__FUNCTION__,__LINE__);	
							delay_ms(100);					
							NVIC_SystemReset();// ��λ	
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
						pro = 0;//״̬ת�������ж�֡��						
					}
					else
					{
						//֡ͷ��ȷ����ʼ����һ֡����
						pro = 2;//״̬ת���ж�֡������
					}
					break;					
				case 2://�ж��Ƿ���յ�֡������
					idx = StartCount + 2;//��ȡ����������
					if(idx > USART2_RX_RING_SIZE-1)//��ͷ
					{
						idx = idx - USART2_RX_RING_SIZE;//��ȡ���ݳ�������µ�����ֵ
					}

					l = ring->buffer[idx];
					if(l < 0 || l > 10) // ���ݳ��Ȳ��ںϷ���Χ��
					{
						printf("[%s:%d]data len err...%d\r\n",__FUNCTION__,__LINE__,l);

						ring->buffer[StartCount] = 0;				
						ring->start++;
						if(ring->start >= USART2_RX_RING_SIZE)
						{
							ring->start = 0;
						}

						pro = 0;//״̬ת�������ж�֡��					
						return 0;
					}
					else//���ݳ����ڷ�Χ��
					{
						pro = 3;//״̬ת���жϵ�ǰ�Ƿ��յ�һ֡����֡									
					}
					break;
				case 3://����֡�������ж��Ƿ���յ�һ֡����֡
					idx = StartCount + 2;//���ݳ�����
					if(idx > USART2_RX_RING_SIZE-1)//��ͷ
					{
						idx = idx - USART2_RX_RING_SIZE;//��ȡ���ݳ�������µ�����ֵ
					}
					FrameLen = ring->buffer[idx] + 4; //����֡����=֡ͷ(1byte)+����(1byte)+����(1byte)+����(nbyte)+У��(1byte)					


					l = EndCount - StartCount;

					if (l < 0)
					{
						l = (USART2_RX_RING_SIZE - StartCount) + EndCount;
					}
										
					if(FrameLen > l)//���ݳ�������㣬���յ������ݲ���һ֡����֡
					{						
						WaitTime ++;
						if(WaitTime > USART2_WAIT_DATA_TIME_MAX)//��ʱδ�ȵ�һ֡��������
						{
							WaitTime = 0;							
					
							printf("[%s:%d]wait data timeout...cur rev:%d   need rev:%d\r\n",__FUNCTION__,__LINE__,l,FrameLen);

							ring->start = ring->end; //�Ȳ���ʣ�µ����ݣ��������							
						}
						return 0;//֡���ݲ���,ֱ���˳�
					}
					else
					{
						WaitTime = 0;
						CheckSum = 0;
						pro = 4;//״̬ת����ȡ֡����
					}
					break;
				case 4://��ȡһ֡����
					for(i=0; i<FrameLen; i++)
					{
						idx = StartCount + i;//��ȡ����
						if(idx > USART2_RX_RING_SIZE-1)//��ͷ
						{
							idx = idx - USART2_RX_RING_SIZE;//��ȡ���ݳ�������µ�����ֵ
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
							if((u8)CheckSum == buf[i])//У����ȷ
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

								pro = 0;//״̬ת�������ж�֡��		

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
					for(i=0; i < FrameLen; i++)//���buf
					{
						idx = StartCount + i;
						if(idx > USART2_RX_RING_SIZE-1)//��ͷ
						{
							idx = idx - USART2_RX_RING_SIZE;
						}											
						ring->buffer[idx] = 0;
					}
					
					idx = StartCount + FrameLen;//��ȡ����
					if(idx > USART2_RX_RING_SIZE-1)//��ͷ
					{
						idx = idx - USART2_RX_RING_SIZE;//��ȡ���ݳ�������µ�����ֵ
					}	
					
					ring->start = idx;
					pro = 0;//״̬ת�������ж�֡��	
					DealUsart2RevData(buf);//����1�յ����ݴ���  
					nCountFrameHeaderErr = 0;
					break;
			}
		}
	}
	return 1;
}




static u8 data_proc(u8* buf, u8 len)
{
//	DealUsart2RevData(buf);//����1�յ����ݴ���  
	return 1;
}

void Usart2RevHandle(void)
{
  ProcessUsart2RxFrame(data_proc);
}

void DealUsart2RevData(vu8* RxBuffer2)//����2�յ����ݴ���
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
 * ��������������2DMA��������ж�
 * ��    ������ 
 * ��    �أ���   
 * �޸����ڣ�2016.06.17  
 *================================================================*/
void DMA1_Channel4_5_IRQHandler(void)
{
	if(DMA_GetITStatus(DMA1_IT_TC4) )
	{
		DMA_ClearITPendingBit(DMA1_IT_TC4);

	}
}



