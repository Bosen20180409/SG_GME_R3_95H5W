/*******************************文件信息***************************************
 **  文 件 名:    Timer.c
 **  版    本：   V1.0
 **  功    能：   定时器
 **  用    法：
 **  作    者：   草塘
 **  日	   期：
 **----------------------------历史版本信息------------------------------------
 **  修 改 人：
 **  版    本： 
 **  日  　期：
 **  描  　述：
 ******************************************************************************/
#include "STM32_Timer.h"

 u8  UART_IDLE_time=0; //UART 模拟空闲中断计时变量
 extern vu8 Usart1RecvDoneFlag;//接收完成标志
 extern u8 UART_IDLE_start; 

void STM32_TIM2_Config(void)    			  
{  
	NVIC_InitTypeDef NVIC_InitStructure;
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	
	NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;  //TIM2中断
	NVIC_InitStructure.NVIC_IRQChannelPriority = 0;  //先占优先级0级
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; //IRQ通道被使能
	NVIC_Init(&NVIC_InitStructure);  //根据NVIC_InitStruct中指定的参数初始化外设NVIC寄存器	

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);	//TIM2 时钟使能 

	TIM_TimeBaseStructure.TIM_Period = 10; //设定计数器自动重装值 最大1ms溢出  
	//TIM_TimeBaseStructure.TIM_Prescaler =(7200-1); 	//预分频器,1M的计数频率,100us加1.	  
  TIM_TimeBaseStructure.TIM_Prescaler =(4800-1); 	//预分频器,1M的计数频率,10us加1.		
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1; //设置时钟分割:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM向上计数模式

	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure); //根据指定的参数初始化TIMx
	
	TIM_ITConfig( TIM2,TIM_IT_Update,ENABLE);//允许更新中断
	TIM_Cmd(TIM2,ENABLE ); 	//使能定时器2
}

extern u32 GpioData;
extern u32 GpioDataTemp;

//定时器2中断服务程序	 
extern u16 TimeTable[ ];
void TIM2_IRQHandler(void)
{ 

//	static u16 nCount = 0;
//	u8 i = 0; 
/*=============================================================*/		
  if(TIM_GetITStatus(TIM2,TIM_IT_Update)!=RESET)
	{	
		TIM_ClearFlag(TIM2, TIM_FLAG_Update);	     //清中断标记	
		TIM_ClearITPendingBit(TIM2, TIM_IT_Update);
/*=========================================================*/		
/*>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>*/		
/*=========================================================*/					
//		GpioDet1( );
//		GpioDet2( );
/*=========================================================*/		
/*>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>*/		
/*=========================================================*/		

//		GpioDetHandle( );

//	GpioData = GpioDet1( );
		
		
		
		
		
		
		
		
		
#if 0
		nCount ++;
		if(nCount > 500)
		{
			nCount = 0;										
//			printf("hello\r\n");
		}
//		printf("hello\r\n");
		for(i=0;i<40;i++)
		{
			if(TimeTable[i] > 0)
			{
				TimeTable[i] --;
			}
		}	
#endif
	}
}



void STM32_TIM3_Config(void)    			  
{  
	NVIC_InitTypeDef NVIC_InitStructure;
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	
	NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn;  //TIM3中断
	NVIC_InitStructure.NVIC_IRQChannelPriority = 1;  //先占优先级1级
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; //IRQ通道被使能
	NVIC_Init(&NVIC_InitStructure);  //根据NVIC_InitStruct中指定的参数初始化外设NVIC寄存器	

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);	//TIM3 时钟使能 

	TIM_TimeBaseStructure.TIM_Period = 10; //设定计数器自动重装值 最大1ms溢出  
	TIM_TimeBaseStructure.TIM_Prescaler =(4800-1); 	//预分频器,1M的计数频率,10us加1.	   
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1; //设置时钟分割:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM向上计数模式

	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure); //根据指定的参数初始化TIMx
	
	TIM_ITConfig( TIM3,TIM_IT_Update,ENABLE);//允许更新中断
	//TIM_Cmd(TIM3,ENABLE ); 	//使能定时器3
}


//定时器2中断服务程序	 
void TIM3_IRQHandler(void)
{ 

/*=============================================================*/		
  if(TIM_GetITStatus(TIM3,TIM_IT_Update)!=RESET)
	{	
		TIM_ClearFlag(TIM3, TIM_FLAG_Update);	     //清中断标记	
		TIM_ClearITPendingBit(TIM3, TIM_IT_Update);
/*	
    UART3  115200 空闲中断产生时间则为大于(1/115200)*8(1个字节8bit)=69.4us 
*/		
    UART_IDLE_time++;
		if(UART_IDLE_time>13) //10us*14=140us 这里预留2个字节
		{
			UART_IDLE_time=0;
			Usart1RecvDoneFlag=1;
			
			UART_IDLE_start=0;
			TIM_Cmd(TIM3,DISABLE); 	//关闭定时器3
		}
		  

	}
}


