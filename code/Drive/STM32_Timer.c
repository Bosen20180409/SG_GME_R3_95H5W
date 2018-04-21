/*******************************�ļ���Ϣ***************************************
 **  �� �� ��:    Timer.c
 **  ��    ����   V1.0
 **  ��    �ܣ�   ��ʱ��
 **  ��    ����
 **  ��    �ߣ�   ����
 **  ��	   �ڣ�
 **----------------------------��ʷ�汾��Ϣ------------------------------------
 **  �� �� �ˣ�
 **  ��    ���� 
 **  ��  ���ڣ�
 **  ��  ������
 ******************************************************************************/
#include "STM32_Timer.h"

 u8  UART_IDLE_time=0; //UART ģ������жϼ�ʱ����
 extern vu8 Usart1RecvDoneFlag;//������ɱ�־
 extern u8 UART_IDLE_start; 

void STM32_TIM2_Config(void)    			  
{  
	NVIC_InitTypeDef NVIC_InitStructure;
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	
	NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;  //TIM2�ж�
	NVIC_InitStructure.NVIC_IRQChannelPriority = 0;  //��ռ���ȼ�0��
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; //IRQͨ����ʹ��
	NVIC_Init(&NVIC_InitStructure);  //����NVIC_InitStruct��ָ���Ĳ�����ʼ������NVIC�Ĵ���	

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);	//TIM2 ʱ��ʹ�� 

	TIM_TimeBaseStructure.TIM_Period = 10; //�趨�������Զ���װֵ ���1ms���  
	//TIM_TimeBaseStructure.TIM_Prescaler =(7200-1); 	//Ԥ��Ƶ��,1M�ļ���Ƶ��,100us��1.	  
  TIM_TimeBaseStructure.TIM_Prescaler =(4800-1); 	//Ԥ��Ƶ��,1M�ļ���Ƶ��,10us��1.		
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1; //����ʱ�ӷָ�:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM���ϼ���ģʽ

	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure); //����ָ���Ĳ�����ʼ��TIMx
	
	TIM_ITConfig( TIM2,TIM_IT_Update,ENABLE);//��������ж�
	TIM_Cmd(TIM2,ENABLE ); 	//ʹ�ܶ�ʱ��2
}

extern u32 GpioData;
extern u32 GpioDataTemp;

//��ʱ��2�жϷ������	 
extern u16 TimeTable[ ];
void TIM2_IRQHandler(void)
{ 

//	static u16 nCount = 0;
//	u8 i = 0; 
/*=============================================================*/		
  if(TIM_GetITStatus(TIM2,TIM_IT_Update)!=RESET)
	{	
		TIM_ClearFlag(TIM2, TIM_FLAG_Update);	     //���жϱ��	
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
	
	NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn;  //TIM3�ж�
	NVIC_InitStructure.NVIC_IRQChannelPriority = 1;  //��ռ���ȼ�1��
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; //IRQͨ����ʹ��
	NVIC_Init(&NVIC_InitStructure);  //����NVIC_InitStruct��ָ���Ĳ�����ʼ������NVIC�Ĵ���	

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);	//TIM3 ʱ��ʹ�� 

	TIM_TimeBaseStructure.TIM_Period = 10; //�趨�������Զ���װֵ ���1ms���  
	TIM_TimeBaseStructure.TIM_Prescaler =(4800-1); 	//Ԥ��Ƶ��,1M�ļ���Ƶ��,10us��1.	   
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1; //����ʱ�ӷָ�:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM���ϼ���ģʽ

	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure); //����ָ���Ĳ�����ʼ��TIMx
	
	TIM_ITConfig( TIM3,TIM_IT_Update,ENABLE);//��������ж�
	//TIM_Cmd(TIM3,ENABLE ); 	//ʹ�ܶ�ʱ��3
}


//��ʱ��2�жϷ������	 
void TIM3_IRQHandler(void)
{ 

/*=============================================================*/		
  if(TIM_GetITStatus(TIM3,TIM_IT_Update)!=RESET)
	{	
		TIM_ClearFlag(TIM3, TIM_FLAG_Update);	     //���жϱ��	
		TIM_ClearITPendingBit(TIM3, TIM_IT_Update);
/*	
    UART3  115200 �����жϲ���ʱ����Ϊ����(1/115200)*8(1���ֽ�8bit)=69.4us 
*/		
    UART_IDLE_time++;
		if(UART_IDLE_time>13) //10us*14=140us ����Ԥ��2���ֽ�
		{
			UART_IDLE_time=0;
			Usart1RecvDoneFlag=1;
			
			UART_IDLE_start=0;
			TIM_Cmd(TIM3,DISABLE); 	//�رն�ʱ��3
		}
		  

	}
}


