/*******                                                                   ************************文件信息***************************************
 **  文 件 名:    GpioDet.c
 **  版    本：   V1.0
 **  功    能：  
 **  用    法：
 **  作    者：   草塘
 **  日	   期：
 **----------------------------历史版本信息------------------------------------
 **  修 改 人：
 **  版    本： 
 **  日  　期：
 **  描  　述：
 ******************************************************************************/
#include "GpioDet.h"


void WakeUpGpioConfig(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;

	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;

	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;  //上拉输入
/*--------------------------------------------------*/	
	GPIO_InitStructure.GPIO_Pin = PIN_WAKE_UP;	   
	GPIO_Init(PORT_WAKE_UP, &GPIO_InitStructure);
/*--------------------------------------------------*/	
}
void Sys_Standby(void)
{  
	WakeUpGpioConfig( );
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR, ENABLE);	//使能PWR外设时钟
	//	RCC->APB2RSTR|=0X01FC;//复位所有IO口
	PWR_WakeUpPinCmd(ENABLE);  //使能唤醒管脚功能
	PWR_EnterSTANDBYMode();	  //进入待命（STANDBY）模式 
    
}

//////////////////////////////////////////////////////////////////////////////////	 
//将HSI作为系统时钟  
//////////////////////////////////////////////////////////////////////////////////
void HSI_SYSCLK(void)
{
	RCC_HSICmd(ENABLE);
	while(RCC_GetFlagStatus(RCC_FLAG_HSIRDY)==RESET);
	RCC->CFGR &=~ 0xf;
	while((RCC->CFGR&0xf) != 0x0);
}	

void WKUP_Init(void)
{	
	GPIO_InitTypeDef GPIO_InitStructure;  		  
	NVIC_InitTypeDef NVIC_InitStructure;
	EXTI_InitTypeDef EXTI_InitStructure;
	
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA, ENABLE);
	RCC_APB2PeriphClockCmd( RCC_APB2Periph_SYSCFG, ENABLE);//使能GPIOA和复用功能时钟
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;//PA.0
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;//上拉输入
	GPIO_Init(GPIOA, &GPIO_InitStructure);//初始化IO
	//使用外部中断方式
	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOA,  EXTI_PinSource0);
	
	EXTI_InitStructure.EXTI_Line = EXTI_Line0;	//设置按键所有的外部线路
	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;//设外外部中断模式:EXTI线路为中断请求
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;//上升沿触发EXTI_Trigger_Falling;//
	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
	EXTI_Init(&EXTI_InitStructure);//初始化外部中断
	
	NVIC_InitStructure.NVIC_IRQChannel = EXTI0_1_IRQn;//使能按键所在的外部中断通道
	NVIC_InitStructure.NVIC_IRQChannelPriority = 2;//先占优先级2级
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;//使能外部中断通道
	NVIC_Init(&NVIC_InitStructure);//根据NVIC_InitStruct中指定的参数初始化外设NVIC寄存器
	
	PWR_WakeUpPinCmd(ENABLE); 	
	HSI_SYSCLK();//将HSI作为系统时钟
	PWR_EnterSTOPMode(0, PWR_STOPEntry_WFI);
}

void EXTI0_1_IRQHandler(void)
{
   EXTI_ClearFlag(EXTI_Line0);  //清除EXTI0线路挂起位
}

/*================================================================= 
 * 功能： 配置Gpio
 * 参数： 
 * 返回：   
 * 日期： 
 *================================================================*/
#if 0
void GpioDetConfig(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;

	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;

	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;  //上拉输入
/*--------------------------------------------------*/	
	GPIO_InitStructure.GPIO_Pin = PIN_GPIO1;	   
	GPIO_Init(PORT_GPIO1, &GPIO_InitStructure);
/*--------------------------------------------------*/	
	GPIO_InitStructure.GPIO_Pin = PIN_GPIO2;	   
	GPIO_Init(PORT_GPIO2, &GPIO_InitStructure);
/*--------------------------------------------------*/
	GPIO_InitStructure.GPIO_Pin = PIN_GPIO3;	   
	GPIO_Init(PORT_GPIO3, &GPIO_InitStructure);
/*--------------------------------------------------*/
	GPIO_InitStructure.GPIO_Pin = PIN_GPIO4;	   
	GPIO_Init(PORT_GPIO4, &GPIO_InitStructure);
/*--------------------------------------------------*/
	GPIO_InitStructure.GPIO_Pin = PIN_GPIO5;	   
	GPIO_Init(PORT_GPIO5, &GPIO_InitStructure);
/*--------------------------------------------------*/
	GPIO_InitStructure.GPIO_Pin = PIN_GPIO6;	   
	GPIO_Init(PORT_GPIO6, &GPIO_InitStructure);
/*--------------------------------------------------*/
	GPIO_InitStructure.GPIO_Pin = PIN_GPIO7;	   
	GPIO_Init(PORT_GPIO7, &GPIO_InitStructure);
/*--------------------------------------------------*/	
	GPIO_InitStructure.GPIO_Pin = PIN_GPIO8;	   
	GPIO_Init(PORT_GPIO8, &GPIO_InitStructure);
/*--------------------------------------------------*/
	GPIO_InitStructure.GPIO_Pin = PIN_GPIO9;	   
	GPIO_Init(PORT_GPIO9, &GPIO_InitStructure);
/*--------------------------------------------------*/
	GPIO_InitStructure.GPIO_Pin = PIN_GPIO10;	   
	GPIO_Init(PORT_GPIO10, &GPIO_InitStructure);
/*--------------------------------------------------*/
	GPIO_InitStructure.GPIO_Pin = PIN_GPIO11;	   
	GPIO_Init(PORT_GPIO11, &GPIO_InitStructure);
/*--------------------------------------------------*/
	GPIO_InitStructure.GPIO_Pin = PIN_GPIO13;	   
	GPIO_Init(PORT_GPIO13, &GPIO_InitStructure);
/*--------------------------------------------------*/
	GPIO_InitStructure.GPIO_Pin = PIN_GPIO14;	   
	GPIO_Init(PORT_GPIO14, &GPIO_InitStructure);
/*--------------------------------------------------*/	
	GPIO_InitStructure.GPIO_Pin = PIN_GPIO15;	   
	GPIO_Init(PORT_GPIO15, &GPIO_InitStructure);
/*--------------------------------------------------*/
	GPIO_InitStructure.GPIO_Pin = PIN_GPIO16;	   
	GPIO_Init(PORT_GPIO16, &GPIO_InitStructure);
/*--------------------------------------------------*/
	GPIO_InitStructure.GPIO_Pin = PIN_GPIO17;	   
	GPIO_Init(PORT_GPIO17, &GPIO_InitStructure);
/*--------------------------------------------------*/
	GPIO_InitStructure.GPIO_Pin = PIN_GPIO18;	   
	GPIO_Init(PORT_GPIO18, &GPIO_InitStructure);
/*--------------------------------------------------*/
	GPIO_InitStructure.GPIO_Pin = PIN_GPIO19;	   
	GPIO_Init(PORT_GPIO19, &GPIO_InitStructure);
/*--------------------------------------------------*/
	GPIO_InitStructure.GPIO_Pin = PIN_GPIO20;	   
	GPIO_Init(PORT_GPIO20, &GPIO_InitStructure);
/*--------------------------------------------------*/	
	GPIO_InitStructure.GPIO_Pin = PIN_GPIO21;	   
	GPIO_Init(PORT_GPIO21, &GPIO_InitStructure);
/*--------------------------------------------------*/
	GPIO_InitStructure.GPIO_Pin = PIN_GPIO22;	   
	GPIO_Init(PORT_GPIO22, &GPIO_InitStructure);
/*--------------------------------------------------*/
	GPIO_InitStructure.GPIO_Pin = PIN_GPIO23;	   
	GPIO_Init(PORT_GPIO23, &GPIO_InitStructure);
/*--------------------------------------------------*/
/*--------------------------------------------------*/
	GPIO_InitStructure.GPIO_Pin = PIN_SELECT1;	   
	GPIO_Init(PORT_SELECT1, &GPIO_InitStructure);
/*--------------------------------------------------*/
	GPIO_InitStructure.GPIO_Pin = PIN_SELECT2;	   
	GPIO_Init(PORT_SELECT2, &GPIO_InitStructure);
/*--------------------------------------------------*/
/*--------------------------------------------------*/
	GPIO_InitStructure.GPIO_Pin = PIN_MODE1;	   
	GPIO_Init(PORT_MODE1, &GPIO_InitStructure);
/*--------------------------------------------------*/
//	GPIO_InitStructure.GPIO_Pin = PIN_MODE2;	   
//	GPIO_Init(PORT_MODE2, &GPIO_InitStructure);
/*--------------------------------------------------*/
/*--------------------------------------------------*/
	GPIO_InitStructure.GPIO_Pin = PIN_L1;	   
	GPIO_Init(PORT_L1, &GPIO_InitStructure);
/*--------------------------------------------------*/
	GPIO_InitStructure.GPIO_Pin = PIN_L2;	   
	GPIO_Init(PORT_L2, &GPIO_InitStructure);
/*--------------------------------------------------*/
/*--------------------------------------------------*/
	GPIO_InitStructure.GPIO_Pin = PIN_R1;	   
	GPIO_Init(PORT_R1, &GPIO_InitStructure);
/*--------------------------------------------------*/
	GPIO_InitStructure.GPIO_Pin = PIN_R2;	   
	GPIO_Init(PORT_R2, &GPIO_InitStructure);
/*--------------------------------------------------*/
/*--------------------------------------------------*/
}

#define DetDelay 0

u8 nCountGpio1 = 0;
u8 nCountGpio2 = 0;
u8 nCountGpio3 = 0;
u8 nCountGpio4 = 0;
u8 nCountGpio5 = 0;
u8 nCountGpio6 = 0;
u8 nCountGpio7 = 0;
u8 nCountGpio8 = 0;
u8 nCountGpio9 = 0;
u8 nCountGpio10 = 0;
u8 nCountGpio11 = 0;
u8 nCountGpio13 = 0;
u8 nCountGpio14 = 0;
u8 nCountGpio15 = 0;
u8 nCountGpio16 = 0;
u8 nCountGpio17 = 0;
u8 nCountGpio18 = 0;
u8 nCountGpio19 = 0;
u8 nCountGpio20 = 0;
u8 nCountGpio21 = 0;
u8 nCountGpio22 = 0;
u8 nCountGpio23 = 0;

u8 nCountSelect1 = 0;
u8 nCountSelect2 = 0;

u8 nCountMode1 = 0;
u8 nCountMode2 = 0;

u8 nCountL1 = 0;
u8 nCountL2 = 0;

u8 nCountR1 = 0;
u8 nCountR2 = 0;


u32 GpioDet1(void)
{	
	u32 Data = 0x00000000;
/*==============================================*/
  if(GPIO_ReadInputDataBit(PORT_GPIO1,PIN_GPIO1) == 0)
  {
		nCountGpio1 ++;
		if(nCountGpio1 > DetDelay)
		{
			nCountGpio1 = DetDelay;
			Data &= Mask0SrcSTART1;
		}
		else
		{
			Data |= Mask1SrcSTART1;
		}
  }
  else
  {
		nCountGpio1 = 0;
		Data |= Mask1SrcSTART1;
  } 
/*==============================================*/	
  if(GPIO_ReadInputDataBit(PORT_GPIO2,PIN_GPIO2) == 0)
  {
		nCountGpio2 ++;
		if(nCountGpio2 > DetDelay)
		{
			nCountGpio2 = DetDelay;
			Data &= Mask0SrcUP1;
		}
		else
		{
			Data |= Mask1SrcUP1;
		}
  }
  else
  {
		nCountGpio2 = 0;
		Data |= Mask1SrcUP1;
  } 
/*==============================================*/
  if(GPIO_ReadInputDataBit(PORT_GPIO3,PIN_GPIO3) == 0)
  {
		nCountGpio3 ++;
		if(nCountGpio3 > DetDelay)
		{
			nCountGpio3 = DetDelay;
			Data &= Mask0SrcDOWN1;
		}
		else
		{
			Data |= Mask1SrcDOWN1;
		}
  }
  else
  {
		nCountGpio3 = 0;
		Data |= Mask1SrcDOWN1;
  } 
/*==============================================*/
  if(GPIO_ReadInputDataBit(PORT_GPIO4,PIN_GPIO4) == 0)
  {
		nCountGpio4 ++;
		if(nCountGpio4 > DetDelay)
		{
			nCountGpio4 = DetDelay;
			Data &= Mask0SrcLEFT1;
		}
		else
		{
			Data |= Mask1SrcLEFT1;
		}
  }
  else
  {
		nCountGpio4 = 0;
		Data |= Mask1SrcLEFT1;
  } 
/*==============================================*/
  if(GPIO_ReadInputDataBit(PORT_GPIO5,PIN_GPIO5) == 0)
  {
		nCountGpio5 ++;
		if(nCountGpio5 > DetDelay)
		{
			nCountGpio5 = DetDelay;
			Data &= Mask0SrcRIGHT1;
//			printf("[%s:%d]r1\r\n",__FUNCTION__,__LINE__);
		}
		else
		{
			Data |= Mask1SrcRIGHT1;
		}
  }
  else
  {
		nCountGpio5 = 0;
		Data |= Mask1SrcRIGHT1;
  } 
/*==============================================*/
  if(GPIO_ReadInputDataBit(PORT_GPIO6,PIN_GPIO6) == 0)
  {
		nCountGpio6 ++;
		if(nCountGpio6 > DetDelay)
		{
			nCountGpio6 = DetDelay;
			Data &= Mask0SrcA1;
//			printf("[%s:%d]A1\r\n",__FUNCTION__,__LINE__);
		}
		else
		{
			Data |= Mask1SrcA1;			
		}
  }
  else
  {
		nCountGpio6 = 0;
		Data |= Mask1SrcA1;
  } 
/*==============================================*/
  if(GPIO_ReadInputDataBit(PORT_GPIO7,PIN_GPIO7) == 0)
  {
		nCountGpio7 ++;
		if(nCountGpio7 > DetDelay)
		{
			nCountGpio7 = DetDelay;
			Data &= Mask0SrcB1;
//			printf("[%s:%d]B1\r\n",__FUNCTION__,__LINE__);
		}
		else
		{
			Data |= Mask1SrcB1;		
		}
  }
  else
  {
		nCountGpio7 = 0;
		Data |= Mask1SrcB1;
  } 
/*==============================================*/
  if(GPIO_ReadInputDataBit(PORT_GPIO8,PIN_GPIO8) == 0)
  {
		nCountGpio8 ++;
		if(nCountGpio8 > DetDelay)
		{
			nCountGpio8 = DetDelay;
			Data &= Mask0SrcC1;
		}
		else
		{
			Data |= Mask1SrcC1;
		}
  }
  else
  {
		nCountGpio8 = 0;
		Data |= Mask1SrcC1;
  } 
/*==============================================*/

  if(GPIO_ReadInputDataBit(PORT_GPIO9,PIN_GPIO9) == 0)
  {
		nCountGpio9 ++;
		if(nCountGpio9 > DetDelay)
		{
			nCountGpio9 = DetDelay;
			Data &= Mask0SrcD1;
		}
		else
		{
			Data |= Mask1SrcD1;
		}
  }
  else
  {
		nCountGpio9 = 0;
		Data |= Mask1SrcD1;
  } 
/*==============================================*/
  if(GPIO_ReadInputDataBit(PORT_GPIO10,PIN_GPIO10) == 0)
  {
		nCountGpio10 ++;
		if(nCountGpio10 > DetDelay)
		{
			nCountGpio10 = DetDelay;
			Data &= Mask0SrcE1;
		}
		else
		{
			Data |= Mask1SrcE1;
		}
  }
  else
  {
		nCountGpio10 = 0;
		Data |= Mask1SrcE1;
  } 
/*==============================================*/
  if(GPIO_ReadInputDataBit(PORT_GPIO11,PIN_GPIO11) == 0)
  {
		nCountGpio11 ++;
		if(nCountGpio11 > DetDelay)
		{
			nCountGpio11 = DetDelay;
			Data &= Mask0SrcF1;
		}
		else
		{
			Data |= Mask1SrcF1;
		}
  }
  else
  {
		nCountGpio11 = 0;
		Data |= Mask1SrcF1;
  } 

/*==============================================*/
/*==============================================*/	
/*==============================================*/	

/*==============================================*/
  if(GPIO_ReadInputDataBit(PORT_GPIO13,PIN_GPIO13) == 0)
  {
		nCountGpio13 ++;
		if(nCountGpio13 > DetDelay)
		{
			nCountGpio13 = DetDelay;
			Data &= Mask0SrcSTART2;
		}
		else
		{
			Data |= Mask1SrcSTART2;
		}
  }
  else
  {
		nCountGpio13 = 0;
		Data |= Mask1SrcSTART2;
  } 
/*==============================================*/
  if(GPIO_ReadInputDataBit(PORT_GPIO14,PIN_GPIO14) == 0)
  {
		nCountGpio14 ++;
		if(nCountGpio14 > DetDelay)
		{
			nCountGpio14 = DetDelay;
			Data &= Mask0SrcUP2;
		}
		else
		{
			Data |= Mask1SrcUP2;
		}
  }
  else
  {
		nCountGpio14 = 0;
		Data |= Mask1SrcUP2;
  } 
/*==============================================*/

  if(GPIO_ReadInputDataBit(PORT_GPIO15,PIN_GPIO15) == 0)
  {
		nCountGpio15 ++;
		if(nCountGpio15 > DetDelay)
		{
			nCountGpio15 = DetDelay;
			Data &= Mask0SrcDOWN2;
		}
		else
		{
			Data |= Mask1SrcDOWN2;
		}
  }
  else
  {
		nCountGpio15 = 0;
		Data |= Mask1SrcDOWN2;
  } 
/*==============================================*/		
  if(GPIO_ReadInputDataBit(PORT_GPIO16,PIN_GPIO16) == 0)
  {
		nCountGpio16 ++;
		if(nCountGpio16 > DetDelay)
		{
			nCountGpio16 = DetDelay;
			Data &= Mask0SrcLEFT2;
		}
		else
		{
			Data |= Mask1SrcLEFT2;
		}
  }
  else
  {
		nCountGpio16 = 0;
		Data |= Mask1SrcLEFT2;
  } 
/*==============================================*/
	
  if(GPIO_ReadInputDataBit(PORT_GPIO17,PIN_GPIO17) == 0)
  {
		nCountGpio17 ++;
		if(nCountGpio17 > DetDelay)
		{
			nCountGpio17 = DetDelay;
			Data &= Mask0SrcRIGHT2;
		}
		else
		{
			Data |= Mask1SrcRIGHT2;
		}
  }
  else
  {
		nCountGpio17 = 0;
		Data |= Mask1SrcRIGHT2;
  } 
/*==============================================*/
  if(GPIO_ReadInputDataBit(PORT_GPIO18,PIN_GPIO18) == 0)
  {
		nCountGpio18 ++;
		if(nCountGpio18 > DetDelay)
		{
			nCountGpio18 = DetDelay;
			Data &= Mask0SrcA2;
		}
		else
		{
			Data |= Mask1SrcA2;
		}
  }
  else
  {
		nCountGpio18 = 0;
		Data |= Mask1SrcA2;
  } 
/*==============================================*/
  if(GPIO_ReadInputDataBit(PORT_GPIO19,PIN_GPIO19) == 0)
  {
		nCountGpio19 ++;
		if(nCountGpio19 > DetDelay)
		{
			nCountGpio19 = DetDelay;
			Data &= Mask0SrcB2;
		}
		else
		{
			Data |= Mask1SrcB2;
		}
  }
  else
  {
		nCountGpio19 = 0;
		Data |= Mask1SrcB2;
  } 
/*==============================================*/
  if(GPIO_ReadInputDataBit(PORT_GPIO20,PIN_GPIO20) == 0)
  {
		nCountGpio20 ++;
		if(nCountGpio20 > DetDelay)
		{
			nCountGpio20 = DetDelay;
			Data &= Mask0SrcC2;
		}
		else
		{
			Data |= Mask1SrcC2;
		}
  }
  else
  {
		nCountGpio20 = 0;
		Data |= Mask1SrcC2;
  } 
/*==============================================*/
  if(GPIO_ReadInputDataBit(PORT_GPIO21,PIN_GPIO21) == 0)
  {
		nCountGpio21 ++;
		if(nCountGpio21 > DetDelay)
		{
			nCountGpio21 = DetDelay;
			Data &= Mask0SrcD2;
		}
		else
		{
			Data |= Mask1SrcD2;
		}
  }
  else
  {
		nCountGpio21 = 0;
		Data |= Mask1SrcD2;
  } 
/*==============================================*/
  if(GPIO_ReadInputDataBit(PORT_GPIO22,PIN_GPIO22) == 0)
  {
		nCountGpio22 ++;
		if(nCountGpio22 > DetDelay)
		{
			nCountGpio22 = DetDelay;
			Data &= Mask0SrcE2;
		}
		else
		{
			Data |= Mask1SrcE2;
		}
  }
  else
  {
		nCountGpio22 = 0;
		Data |= Mask1SrcE2;
  } 
/*==============================================*/
  if(GPIO_ReadInputDataBit(PORT_GPIO23,PIN_GPIO23) == 0)
  {
		nCountGpio23 ++;
		if(nCountGpio23 > DetDelay)
		{
			nCountGpio23 = DetDelay;
			Data &= Mask0SrcF2;
		}
		else
		{
			Data |= Mask1SrcF2;
		}
  }
  else
  {
		nCountGpio23 = 0;
		Data |= Mask1SrcF2;
  } 
/*==============================================*/	
/*==============================================*/		
  if(GPIO_ReadInputDataBit(PORT_SELECT1,PIN_SELECT1) == 0)
  {
		nCountSelect1 ++;
		if(nCountSelect1 > DetDelay)
		{
			nCountSelect1 = DetDelay;
			Data &= Mask0SrcSELECT1;
		}
		else
		{
			Data |= Mask1SrcSELECT1;
		}
  }
  else
  {
		nCountSelect1 = 0;
		Data |= Mask1SrcSELECT1;
  } 
/*==============================================*/
  if(GPIO_ReadInputDataBit(PORT_SELECT2,PIN_SELECT2) == 0)
  {
		nCountSelect2 ++;
		if(nCountSelect2 > DetDelay)
		{
			nCountSelect2 = DetDelay;
			Data &= Mask0SrcSELECT2;
		}
		else
		{
			Data |= Mask1SrcSELECT2;
		}
  }
  else
  {
		nCountSelect2 = 0;
		Data |= Mask1SrcSELECT2;
  }
/*==============================================*/
/*==============================================*/	
  if(GPIO_ReadInputDataBit(PORT_MODE1,PIN_MODE1) == 0)
  {
		nCountMode1 ++;
		if(nCountMode1 > DetDelay)
		{
			nCountMode1 = DetDelay;
			Data &= Mask0SrcMODE1;
		}
		else
		{
			Data |= Mask1SrcMODE1;
		}
  }
  else
  {
		nCountMode1 = 0;
		Data |= Mask1SrcMODE1;
  } 
/*==============================================*/
  if(GPIO_ReadInputDataBit(PORT_MODE2,PIN_MODE2) == 0)
  {
		nCountMode2 ++;
		if(nCountMode2 > DetDelay)
		{
			nCountMode2 = DetDelay;
			Data &= Mask0SrcMODE2;
		}
		else
		{
			Data |= Mask1SrcMODE2;
		}
  }
  else
  {
		nCountMode2 = 0;
		Data |= Mask1SrcMODE2;
  }
/*==============================================*/
/*==============================================*/	
  if(GPIO_ReadInputDataBit(PORT_L1,PIN_L1) == 0)
  {
		nCountL1 ++;
		if(nCountL1 > DetDelay)
		{
			nCountL1 = DetDelay;
			Data &= Mask0SrcL1;
//			printf("[%s:%d]L1\r\n",__FUNCTION__,__LINE__);
		}
		else
		{
			Data |= Mask1SrcL1;
			
		}
  }
  else
  {
		nCountL1 = 0;
		Data |= Mask1SrcL1;
  } 
/*==============================================*/
  if(GPIO_ReadInputDataBit(PORT_L2,PIN_L2) == 0)
  {
		nCountL2 ++;
		if(nCountL2 > DetDelay)
		{
			nCountL2 = DetDelay;
			Data &= Mask0SrcL2;
//			printf("[%s:%d]L2\r\n",__FUNCTION__,__LINE__);
		}
		else
		{
			Data |= Mask1SrcL2;
			
		}
  }
  else
  {
		nCountL2 = 0;
		Data |= Mask1SrcL2;
  }
/*==============================================*/
/*==============================================*/		
  if(GPIO_ReadInputDataBit(PORT_R1,PIN_R1) == 0)
  {
		nCountR1 ++;
		if(nCountR1 > DetDelay)
		{
			nCountR1 = DetDelay;
			Data &= Mask0SrcR1;
		}
		else
		{
			Data |= Mask1SrcR1;
		}
  }
  else
  {
		nCountR1 = 0;
		Data |= Mask1SrcR1;
  } 
/*==============================================*/
  if(GPIO_ReadInputDataBit(PORT_R2,PIN_R2) == 0)
  {
		nCountR2 ++;
		if(nCountR2 > DetDelay)
		{
			nCountR2 = DetDelay;
			Data &= Mask0SrcR2;
		}
		else
		{
			Data |= Mask1SrcR2;
		}
  }
  else
  {
		nCountR2 = 0;
		Data |= Mask1SrcR2;
  }
/*==============================================*/
/*==============================================*/		
	
	return Data;
}

#endif
