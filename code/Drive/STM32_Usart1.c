/*******************************文件信息***************************************
 **  文 件 名:    Usart1.c
 **  版    本：   V1.0
 **  功    能：   stm32串口1驱动
 **  用    法：
 **  作    者：   草塘
 **  日	   期：
 **----------------------------历史版本信息------------------------------------
 **  修 改 人：
 **  版    本： 
 **  日  　期：
 **  描  　述：
 ******************************************************************************/

#include "STM32_Usart1.h"

#include <stdarg.h>
#include <stdio.h>

#define RX_BUF_SIZE  32

static u8 USART1_RxBuffer[RX_BUF_SIZE];//串口3内部接收缓存

stPrintfBuf PrintfBuf[PrintfBufArraySize];

u8 nCountPrintfBuf = 0;

static volatile u32 USART1_ReadIndex = 0;//读索引
vu8 Usart1SendDoneFlag = 1;//发送完成标志
vu8 Usart1RecvDoneFlag = 0;//接收完成标志 

u8 UART_IDLE_start=0; 

extern u8  UART_IDLE_time; //UART 模拟空闲中断计时变量

/*================================================================= 
 * 功能描述：串口1引脚配置
 * 参    数：无 
 * 返    回：无   
 * 修改日期：2016.06.15 
 *================================================================*/
void Usart1GpioConfig(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;

	/* Configure USART1 Tx(PA9) as alternate function push-pull */
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	/* Configure USART1 Rx(PA10) as input floating */
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	
}

u8 Read_NRF24L01_MODE(void)
{
  if(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_6) == 0)
  {
    return 0;
  }
  else
  {
    return 1;
  }  
}

/*================================================================= 
 * 功能描述：串口3配置
 * 参    数：无 
 * 返    回：无   
 * 修改日期：2016.06.15 
 *================================================================*/
void Usart1Config(void)
{
	NVIC_InitTypeDef NVIC_InitStructure;	
	DMA_InitTypeDef DMA_InitStructure;	
	UART_InitTypeDef UART_InitStructure;	
    
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);
	RCC_AHBPeriphClockCmd( RCC_AHBPeriph_GPIOA ,ENABLE);	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_UART1,ENABLE);	

  GPIO_PinAFConfig(GPIOA,GPIO_PinSource9,GPIO_AF_1);
  GPIO_PinAFConfig(GPIOA,GPIO_PinSource10,GPIO_AF_1); //20180118_jade_add	

	NVIC_InitStructure.NVIC_IRQChannel = UART1_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
    
	NVIC_InitStructure.NVIC_IRQChannel = DMA1_Channel2_3_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPriority = 1;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
  	
	UART_InitStructure.UART_BaudRate =  115200; //波特率115200
	UART_InitStructure.UART_WordLength = UART_WordLength_8b;//数据位
	UART_InitStructure.UART_StopBits = UART_StopBits_1;//停止位
	UART_InitStructure.UART_Parity = UART_Parity_No ;
	UART_InitStructure.UART_Mode = UART_Mode_Rx | UART_Mode_Tx;//输入输出模式
	UART_InitStructure.UART_HardwareFlowControl = UART_HardwareFlowControl_None; 	
	UART_Init(UART1, &UART_InitStructure);
	UART_Cmd(UART1, ENABLE);  //UART1 模块使能
    
	DMA_DeInit(DMA1_Channel3);
	DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)&(UART1->RDR);
	DMA_InitStructure.DMA_MemoryBaseAddr = (uint32_t)&USART1_RxBuffer[0];
	DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralSRC;
	DMA_InitStructure.DMA_BufferSize = sizeof(USART1_RxBuffer);
	DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
	DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;
	DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;
	DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;
	DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;
	DMA_InitStructure.DMA_Priority = DMA_Priority_VeryHigh;
	DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;
	DMA_Init(DMA1_Channel3, &DMA_InitStructure);
	UART_DMACmd(UART1, UART_DMAReq_EN, ENABLE);
	DMA_Cmd(DMA1_Channel3, ENABLE);
    
    
	DMA_DeInit(DMA1_Channel2);
	DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)&(UART1->TDR);
	//	DMA_InitStructure.DMA_MemoryBaseAddr = (uint32_t)&USART3_TxBuffer[0];
	DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralDST;
	//	DMA_InitStructure.DMA_BufferSize = sizeof(USART3_TxBuffer);
	DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
	DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;
	DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;
	DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;
	DMA_InitStructure.DMA_Mode = DMA_Mode_Normal;
	DMA_InitStructure.DMA_Priority = DMA_Priority_VeryHigh;
	DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;
	DMA_Init(DMA1_Channel2, &DMA_InitStructure);
	UART_DMACmd(UART1, UART_DMAReq_EN, ENABLE);
	DMA_ITConfig(DMA1_Channel2, DMA_IT_TC, ENABLE);
	
  UART_ITConfig(UART1, UART_IT_RXIEN, ENABLE);   //开启UART1接收中断（用于模拟UART空闲中断）
	//UART_ITConfig(UART1, UART_IT_IDLE, ENABLE);  //MM32L062没有空闲中断需用定时模拟该功能
	UART_Cmd(UART1, ENABLE);
	
	Usart1GpioConfig(); //注意先使能UART再初始化GPIO
}

/*================================================================= 
 * 功能描述：串口发送函数
 * 参    数：buffer	发送内容
 *         : length	发送长度
 * 返    回：
 * 修改日期：2016.06.17  
 *================================================================*/
uint16_t USART1_SendBuffer(const uint8_t* buffer, uint16_t length)
{
	if( (buffer==0) || (length==0) )
	{
		return 0;
	}
	Usart1SendDoneFlag = 0;
	DMA_Cmd(DMA1_Channel2, DISABLE);
	DMA1_Channel2->CMAR = (uint32_t)buffer;
	DMA_SetCurrDataCounter(DMA1_Channel2, length);
	DMA_Cmd(DMA1_Channel2, ENABLE);
	return length;
}
/*================================================================= 
 * 功能描述：发送完成标志查询
 * 参    数：
 * 返    回：1:发送完成 	0:未完成
 * 修改日期：2016.06.17  
 *================================================================*/
uint8_t isUSART1SendDone(void)
{
	return Usart1SendDoneFlag;
}




/*================================================================= 
 * 功能描述：打印16进制数组
 * 参    数：hex			数组
 *         : hex_length	数组长度
 * 返    回：
 * 修改日期：2016.06.17  
 *================================================================*/
void Printf_Hex(const uint8_t* hex, uint16_t hex_length)
{
//	const uint8_t char_table[] = "0123456789ABCDEF";
//	uint16_t j=0;
//	uint16_t i=0;
//	
//	if(Usart1SendDoneFlag == 0)
//	{
//		return;
//	}
//	
//	for(i=0;(i<hex_length)&&j<sizeof(print_buffer);i++)
//	{
//		print_buffer[j++] = char_table[(hex[i]&0xF0)>>4];
//		print_buffer[j++] = char_table[hex[i]&0x0F];
//		print_buffer[j++] = ' ';
//	}
//	print_buffer[j++] = '\r';	
//	print_buffer[j++] = '\n';
//	USART1_SendBuffer(print_buffer,j);//发送
	
	
//	while(!Usart1SendDoneFlag);//等待发送完成
}

/*================================================================= 
 * 功能描述：串口接收函数
 * 参    数：buffer		接收缓存 
 *         : max_length	接收缓存的大小,若max_length小于数据的长度,则接收完成标志不被清0
 * 返    回：接收到数据的长度   
 * 修改日期：2016.06.17  
 *================================================================*/
u32 USART1_RecvBuffer(u8* buffer, u32 max_length)
{
	u32 recv_length;
	u32 write_idx;
	u8 i = 0;
	if((buffer==0) || (max_length==0))
	{
		return 0;
	}
		
	write_idx = sizeof(USART1_RxBuffer) - DMA_GetCurrDataCounter(DMA1_Channel3);
//	Printf("[%s:%d]USART1_ReadIndex:%d\r\n",__FUNCTION__,__LINE__,USART1_ReadIndex);	
//	Printf("[%s:%d]write_idx:%d\r\n",__FUNCTION__,__LINE__,write_idx);
	
	if(USART1_ReadIndex < write_idx)//计算接收到的长度
	{
		recv_length = write_idx - USART1_ReadIndex;
	
//		Printf("[%s:%d]recv_length:%d\r\n",__FUNCTION__,__LINE__,recv_length);	
	}
	else
	{
		recv_length = sizeof(USART1_RxBuffer) - USART1_ReadIndex + write_idx;				
//		Printf("[%s:%d]recv_length:%d\r\n\r\n",__FUNCTION__,__LINE__,recv_length);	
	}
	
	for(i=0;(i<recv_length) && (i<max_length);i++)//提取数据内容
	{
		if( (USART1_ReadIndex) == sizeof(USART1_RxBuffer))
		{
			USART1_ReadIndex = 0;
		}
		buffer[i] = USART1_RxBuffer[USART1_ReadIndex];
		USART1_ReadIndex++;
	}
	
//	USART1_ReadIndex = write_idx;
  Usart1RecvDoneFlag = 0;//清接收完成标志
	return recv_length;
}
/*================================================================= 
 * 功能描述：接收完成标志查询
 * 参    数：无 
 * 返    回：1:接收完成	0:未完成
 * 修改日期：2016.06.17  
 *================================================================*/
u8 isUSART1RecvDone(void)
{
	return Usart1RecvDoneFlag;
}

#define usart1_data_buf_size 32
u8 usart1_data[usart1_data_buf_size];//主函数小容量数组
u32 usart1_recv_length;//接收到的数据长度
u32 usart1_flush_length;//清空的数据长度

u8 Usart1RevBuf[10];
void *Uart1RxDataPtr;
void Usart1RevHandle(void)
{
	if(isUSART1RecvDone())//处理接收数据
	{
		usart1_recv_length = 0;
	
		usart1_recv_length = USART1_RecvBuffer(usart1_data,sizeof(usart1_data));//从串口缓存提取数据到data
//		printf("usart1_recv_length:%d\r\n",usart1_recv_length);		
		#if 0
		{
			u16  i = 1;		
	//		printf("[%s:%d]usart1_rx:",__FUNCTION__,__LINE__);	
			printf("usart1_rx:");	
			for(i=0;i<usart1_recv_length;i++)
			{
				printf("%x ",usart1_data[i]);			
			}
			printf("\r\n");
		}	
		#endif	
		
		if((*(usart1_data+0) != 0xaa)||(*(usart1_data+1) != 0x55))
		{
			return;
		}	


		switch(*(usart1_data+2))
		{
			case 0x00:     

				break;							
			case 0x01://单字符命令
				DealOneCharCmd(*(usart1_data+4));				
				break;					
			case 0x02://上位机模拟按键 

				break;		
			default:

				break;
		}
	}
}
/*================================================================= 
 * 功能描述：串口中断
 * 参    数：无 
 * 返    回：无   
 * 修改日期：2016.06.17  
 *================================================================*/
void UART1_IRQHandler(void)
{

	 
//	if(UART_GetITStatus(UART3, USART_IT_IDLE) != RESET)
//	{
//		UART_ClearITPendingBit(UART3, UART_IT_IDLE);//空闲
//		UART_ReceiveData(UART3);//空读清状态
////		Printf("[%s:%d]Usart1RecvDoneFlag = 1;",__FUNCTION__,__LINE__);	
//		Usart1RecvDoneFlag = 1;
//	}
//20171027_ADD_MARK 目前MM32没有空闲中断暂时屏蔽	
	
	if(UART_GetITStatus(UART1, UART_IT_RXIEN) != RESET)
	{
		UART_ClearITPendingBit(UART1, UART_IT_RXIEN);//清接收中断
    UART_IDLE_time=0;
		if(!UART_IDLE_start)
		{
			UART_IDLE_start=1;
			TIM_Cmd(TIM3,ENABLE); 	//使能定时器3 开始进行空闲计时
		}
	}
}


/**
* 串口1DMA发送完成中断
*/
void DMA1_Channel2_IRQHandler(void)
{
	if ( DMA_GetITStatus(DMA1_IT_TC2) )
	{
		DMA_ClearITPendingBit(DMA1_IT_TC2);
		Usart1SendDoneFlag = 1;
	}
}



/*================================================================= 
 * 功能：重定义fputc函数
 * 参数：
 * 返回：
 * 日期：  
 *================================================================*/
int fputc(int ch, FILE *f)
{      
	while((UART1->CSR & UART_IT_TXIEN)==0);//循环发送,直到发送完毕   
    UART1->TDR = (u8) ch;      
	return ch;
}

#include "hw_config.h"

void DealOneCharCmd(u8 cmd)
{
	switch (cmd)
	{
		//#if 0 //20171027_jade_mark
		case '0':
			printf("[%s:%d]--Rev cmd:0\r\n",__FUNCTION__,__LINE__);
			GamePad_Send_Xbox(0x00,0x00,0x0f);
			GamePad_Send_Ps3(0x01,0xf0,0x00,0xf0,
		                   0x02,0xf0,0x00,0xf0); 
		
			break;				
		case '1':	
			printf("[%s:%d]--Rev cmd:1\r\n",__FUNCTION__,__LINE__);	
			GamePad_Send_Xbox(0x10,0x00,0x0f);
			GamePad_Send_Ps3(0x01,0xf0,0x00,0xf0,
		                   0x02,0xf0,0x01,0xf0);  
			
			break;
		case '2':		
//			printf("[%s:%d]--Rev cmd:2\r\n",__FUNCTION__,__LINE__);	
			GamePad_Send_Xbox(0x01,0x00,0x0f);  
			break;
		case '3':			
//			printf("[%s:%d]--Rev cmd:3\r\n",__FUNCTION__,__LINE__);
			GamePad_Send_Xbox(0x08,0x00,0x0f);
			break;
		case '4':			
//			printf("[%s:%d]--Rev cmd:4\r\n",__FUNCTION__,__LINE__);	
			GamePad_Send_Xbox(0x20,0x00,0x0f);
			break;
		case '5':		
//			printf("[%s:%d]--Rev cmd:5\r\n",__FUNCTION__,__LINE__);	
			GamePad_Send_Xbox(0x40,0x00,0x0f);
			break;
		case '6':		
//			printf("[%s:%d]--Rev cmd:6\r\n",__FUNCTION__,__LINE__);
			GamePad_Send_Xbox(0x02,0x00,0x0f);
			break;	
		case '7':			
//			printf("[%s:%d]--Rev cmd:7\r\n",__FUNCTION__,__LINE__);
			GamePad_Send_Xbox(0x04,0x00,0x0f);
			break;
		case '8':			
//			printf("[%s:%d]--Rev cmd:8\r\n",__FUNCTION__,__LINE__);	
			GamePad_Send_Xbox(0x80,0x00,0x0f);
			break;
		case '9':					
//			printf("[%s:%d]--Rev cmd:9\r\n",__FUNCTION__,__LINE__);	//select
			GamePad_Send_Xbox(0x00,0x01,0x0f);
			break;
		case 'a':				
		case 'A':				
//			printf("[%s:%d]--Rev cmd:a\r\n",__FUNCTION__,__LINE__);	//mode
			GamePad_Send_Xbox(0x00,0x10,0x0f);
			break;
		case 'b':
		case 'B':
//			printf("[%s:%d]--Rev cmd:b\r\n",__FUNCTION__,__LINE__);	//start
			GamePad_Send_Xbox(0x00,0x02,0x0f);
			break;
		case 'c':
		case 'C':
//			printf("[%s:%d]--Rev cmd:c\r\n",__FUNCTION__,__LINE__);	//U
			GamePad_Send_Xbox(0x00,0x00,0x00);
			break;
		case 'd':
		case 'D':
//			printf("[%s:%d]--Rev cmd:d\r\n",__FUNCTION__,__LINE__);	
			GamePad_Send_Xbox(0x00,0x00,0x04);
			break;
		case 'e':
		case 'E':
//			printf("[%s:%d]--Rev cmd:e\r\n",__FUNCTION__,__LINE__);	
			GamePad_Send_Xbox(0x00,0x00,0x06);
			break;
		case 'f':
		case 'F':
//			printf("[%s:%d]--Rev cmd:f\r\n",__FUNCTION__,__LINE__);	
			GamePad_Send_Xbox(0x00,0x00,0x02);
			break;
		//#endif
		
		case 'g':
		case 'G':
			printf("[%s:%d]--Rev cmd:g\r\n",__FUNCTION__,__LINE__);	
			break;
		case 'h':
		case 'H':
			printf("[%s:%d]--Rev cmd:h\r\n",__FUNCTION__,__LINE__);	
				
			break;			
		case 'i':
		case 'I':
			printf("[%s:%d]--Rev cmd:i\r\n",__FUNCTION__,__LINE__);	

			break;
		case 'j':
		case 'J':		
			printf("[%s:%d]--Rev cmd:j\r\n",__FUNCTION__,__LINE__);	
			break;
		case 'k':
		case 'K':
			printf("[%s:%d]--Rev cmd:k\r\n",__FUNCTION__,__LINE__);
			break;			
		case 'l':
		case 'L':
			printf("[%s:%d]--Rev cmd:l\r\n",__FUNCTION__,__LINE__);	

			break;					
		case 'm':
		case 'M':
			printf("[%s:%d]--Rev cmd:m\r\n",__FUNCTION__,__LINE__);	
			break;
		case 'n':
		case 'N':
			printf("[%s:%d]--Rev cmd:n\r\n",__FUNCTION__,__LINE__);	
			break;
		case 'o':
		case 'O':	
			printf("[%s:%d]--Rev cmd:o\r\n",__FUNCTION__,__LINE__);	
			GamePad_Send_Flag = 0;	
			break;
		case 'p':
		case 'P':	
			printf("[%s:%d]--Rev cmd:p\r\n",__FUNCTION__,__LINE__);	
			GamePad_Send_Flag = 1;
			break;
		case 'q':
		case 'Q':	
			printf("[%s:%d]--Rev cmd:q\r\n",__FUNCTION__,__LINE__);	

			break;			
		case 'r':
		case 'R':
			printf("[%s:%d]--Rev cmd:r\r\n",__FUNCTION__,__LINE__);	

			break;
		case 's':
		case 'S':
			printf("[%s:%d]--Rev cmd:s\r\n",__FUNCTION__,__LINE__);	

			break;	
		case 't':
		case 'T':
			printf("[%s:%d]--Rev cmd:t\r\n",__FUNCTION__,__LINE__);	

			break;
		case 'u':
		case 'U':
			printf("[%s:%d]--Rev cmd:u\r\n",__FUNCTION__,__LINE__);	

			break;	
		case 'v':		
		case 'V':
			printf("[%s:%d]--Rev cmd:v\r\n",__FUNCTION__,__LINE__);	
			break;			
		case 'w':
		case 'W':
			printf("[%s:%d]--Rev cmd:w\r\n",__FUNCTION__,__LINE__);	

			break;
		case 'x':
		case 'X':	
			printf("[%s:%d]--Rev cmd:x\r\n",__FUNCTION__,__LINE__);	
			break;
		case 'y':
		case 'Y':
			printf("[%s:%d]--Rev cmd:y\r\n",__FUNCTION__,__LINE__);	
			break;
		case 'z':
		case 'Z':
			printf("[%s:%d]--Rev cmd:z\r\n",__FUNCTION__,__LINE__);	

			break;				

		default:
			
			break;
	}
}




