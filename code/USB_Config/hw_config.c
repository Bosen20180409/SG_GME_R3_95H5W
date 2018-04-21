/******************** (C) COPYRIGHT 2009 STMicroelectronics ********************
* File Name          : hw_config.c
* Author             : MCD Application Team
* Version            : V3.0.1
* Date               : 04/27/2009
* Description        : Hardware Configuration & Setup
********************************************************************************
* THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
* WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE TIME.
* AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY DIRECT,
* INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING FROM THE
* CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE CODING
* INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
*******************************************************************************/

/* Includes ------------------------------------------------------------------*/
//#include "MM32x103.h"
#include "MM32L073PF.h"  //20180118_JADE_ADD
#include "hw_config.h"

#include "config.h"
#include "usb_regs.h"

#include "usb_lib.h"
#include "usb_desc.h"
#include "platform_config.h"

#include "usb_desc_pc.h"
#include "usb_desc_ps3.h"
#include "usb_desc_ps4.h"

#include "usb_pwr.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
ErrorStatus HSEStartUpStatus;
EXTI_InitTypeDef EXTI_InitStructure;

extern uint32_t SystemCoreClock;

u8 DeviceType = DEVICE_PC;

/* Extern variables ----------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
//static void IntToUnicode (uint32_t value , uint8_t *pbuf , uint8_t len);
/* Private functions ---------------------------------------------------------*/

//USB传输是否正在进行的标志（本例程没用到）
//1,空闲；0，正在传输。
volatile u8 PrevXferComplete = 1;//ST官方例程是在main.c定义的，我们改到这里定义



/* Extern variables ----------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/*******************************************************************************
* Function Name  : Set_System
* Description    : Configures Main system clocks & power.
* Input          : None.
* Return         : None.
*******************************************************************************/
void Set_System(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;

  /* Setup the microcontroller system. Initialize the Embedded Flash Interface,  
     initialize the PLL and update the SystemFrequency variable. */
  RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA, ENABLE);
  /* enable the PWR clock */
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR, ENABLE);

  /* Set all the GPIOs to AIN */

  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_Init(GPIOA, &GPIO_InitStructure);


  /* Enable Joystick GPIOs clock */
  RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIO_JOY_SET1, ENABLE);
  RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIO_JOY_SET2, ENABLE);

  /* Configure the JoyStick IOs */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_UP;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
  GPIO_Init(GPIO_UP, &GPIO_InitStructure);

  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_DOWN;
  GPIO_Init(GPIO_DOWN, &GPIO_InitStructure);

  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_LEFT;
  GPIO_Init(GPIO_LEFT, &GPIO_InitStructure);

  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_RIGHT;
  GPIO_Init(GPIO_RIGHT, &GPIO_InitStructure);

  /* Enable GPIOB & AFIO clocks */
  RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIO_KEY, ENABLE);

  /* Configure the Key pin as input floating */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_KEY;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
  GPIO_Init(GPIO_KEY, &GPIO_InitStructure);
  
  /* Configure the Key pin as input floating */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12|GPIO_Pin_11;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;
  GPIO_Init(GPIOA, &GPIO_InitStructure);

}

/*******************************************************************************
* Function Name  : Set_USBClock
* Description    : Configures USB Clock input (48MHz).
* Input          : None.
* Output         : None.
* Return         : None.
*******************************************************************************/
void Set_USBClock(void)
{
  /* Select USBCLK source */

  	
  if(SystemCoreClock==48000000)
	 {
     RCC_USBCLKConfig(RCC_USBCLKSource_PLLCLK_Div1);  //48M主频时无需分频		
	 }
  if(SystemCoreClock==96000000)
	 {
		 RCC_USBCLKConfig(RCC_USBCLKSource_PLLCLK_Div2);  //96M主频时需2分频 
	 }		
	
  /* Enable USB clock */
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_USB, ENABLE);
}

/*******************************************************************************
* Function Name  : GPIO_AINConfig
* Description    : Configures all IOs as AIN to reduce the power consumption.
* Input          : None.
* Output         : None.
* Return         : None.
*******************************************************************************/
void GPIO_AINConfig(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;

  /* Enable all GPIOs Clock*/
  RCC_AHBPeriphClockCmd(RCC_AHBPeriph_ALLGPIO, ENABLE);

  /* Configure all GPIO port pins in Analog Input mode (floating input trigger OFF) */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_All;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;
  GPIO_Init(GPIOA, &GPIO_InitStructure);
  GPIO_Init(GPIOB, &GPIO_InitStructure);
  GPIO_Init(GPIOC, &GPIO_InitStructure);
  GPIO_Init(GPIOD, &GPIO_InitStructure);

  /* Disable all GPIOs Clock*/
  RCC_AHBPeriphClockCmd(RCC_AHBPeriph_ALLGPIO, DISABLE);
}
/*******************************************************************************
* Function Name  : Enter_LowPowerMode.
* Description    : Power-off system clocks and power while entering suspend mode.
* Input          : None.
* Output         : None.
* Return         : None.
*******************************************************************************/
void Enter_LowPowerMode(void)
{
  /* Set the device state to suspend */
  bDeviceState = SUSPENDED;

//  /* Clear EXTI Line18 pending bit */
//  EXTI_ClearITPendingBit(GPIO_KEY_EXTI_Line);

//  /* Request to enter STOP mode with regulator in low power mode */
//  PWR_EnterSTOPMode(PWR_Regulator_LowPower, PWR_STOPEntry_WFI);
}

/*******************************************************************************
* Function Name  : Leave_LowPowerMode.
* Description    : Restores system clocks and power while exiting suspend mode.
* Input          : None.
* Output         : None.
* Return         : None.
*******************************************************************************/
void Leave_LowPowerMode(void)
{
  DEVICE_INFO *pInfo = &Device_Info;

//  /* Enable HSE */
//  RCC_HSEConfig(RCC_HSE_ON);

//  /* Wait till HSE is ready */
//  HSEStartUpStatus = RCC_WaitForHSEStartUp();

//  /* Enable PLL */
//  RCC_PLLCmd(ENABLE);

//  /* Wait till PLL is ready */
//  while (RCC_GetFlagStatus(RCC_FLAG_PLLRDY) == RESET)
//  {}

//  /* Select PLL as system clock source */
//  RCC_SYSCLKConfig(RCC_SYSCLKSource_PLLCLK);

//  /* Wait till PLL is used as system clock source */
//  while (RCC_GetSYSCLKSource() != 0x08)
//  {}

  /* Set the device state to the correct state */
  if (pInfo->Current_Configuration != 0)
  {
    /* Device configured */
    bDeviceState = CONFIGURED;
  }
  else
  {
    bDeviceState = ATTACHED;
  }
}

/*******************************************************************************
* Function Name  : USB_Interrupts_Config.
* Description    : Configures the USB interrupts.
* Input          : None.
* Output         : None.
* Return         : None.
*******************************************************************************/
void USB_Interrupts_Config(void)
{
  NVIC_InitTypeDef NVIC_InitStructure;

  /* 2 bit for pre-emption priority, 2 bits for subpriority */
  //NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);  //20180118_jade_mark

  /* Enable the USB interrupt */
  NVIC_InitStructure.NVIC_IRQChannel = USB_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPriority = 1;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);

  /* Enable the USB Wake-up interrupt */
	/*
  NVIC_InitStructure.NVIC_IRQChannel = USBWakeUp_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);
  */ //20180118_jade_mark  M0没看到这个中断
	
  /* Enable the Key EXTI line Interrupt */
  NVIC_InitStructure.NVIC_IRQChannel = EXTI_KEY_IRQChannel;
  NVIC_InitStructure.NVIC_IRQChannelPriority = 2;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);
}

/*******************************************************************************
* Function Name  : USB_Cable_Config.
* Description    : Software Connection/Disconnection of USB Cable.
* Input          : NewState: new state.
* Output         : None.
* Return         : None
*******************************************************************************/
void USB_Cable_Config (FunctionalState NewState)
{
  if (NewState != DISABLE)
  {
      _SetUSB_TOP(USB_TOP_CONNECT);
  }
  else
  {
      _ClrUSB_TOP(USB_TOP_CONNECT);
  }
}

/*******************************************************************************
* Function Name : JoyState.
* Description   : Decodes the Joystick direction.
* Input         : None.
* Output        : None.
* Return value  : The direction value.
*******************************************************************************/
uint8_t JoyState(void)
{
  /* "right" key is pressed */
  if (!GPIO_ReadInputDataBit(GPIO_RIGHT, GPIO_Pin_RIGHT))
  {
    return JOY_RIGHT;
  }
  /* "left" key is pressed */
  if (!GPIO_ReadInputDataBit(GPIO_LEFT, GPIO_Pin_LEFT))
  {
    return JOY_LEFT;
  }
  /* "up" key is pressed */
  if (!GPIO_ReadInputDataBit(GPIO_UP, GPIO_Pin_UP))
  {
    return JOY_UP;
  }
  /* "down" key is pressed */
  if (!GPIO_ReadInputDataBit(GPIO_DOWN, GPIO_Pin_DOWN))
  {
    return JOY_DOWN;
  }
  /* No key is pressed */
  else
  {
    return JOY_IDLE;
  }
}

/*******************************************************************************
* Function Name : Joystick_Send.
* Description   : prepares buffer to be sent containing Joystick event infos.
* Input         : Keys: keys received from terminal.
* Output        : None.
* Return value  : None.
*******************************************************************************/
void Joystick_Send(uint8_t Keys)
{
  uint8_t Joys_Buffer[8] = {0x7f, 0x7f ,0x7d ,0x7f  ,0x7f ,0x0f ,0x00 ,0xc0};
//  int8_t X = 0, Y = 0;

  switch (Keys)
  {
    case JOY_IDLE:
      break;    
    case JOY_LEFT:
      break;
    case JOY_RIGHT:
      break;
    case JOY_UP:
      break;
    case JOY_DOWN:
      break;
    default:
      return;
  }
  if(!(_GetUSB_CTRL0()&EP0_CTRL_TRANEN))
  {
      UserToPMABufferCopy(Joys_Buffer, ENDP1, 8);
      _SetUSB_CTRL1(EP1_CTRL_TRANEN|8) ;
  }
}

#define KEY_NONE 	0x00
#define KEY_UP    	0x1A
#define KEY_DOWN  	0x16
#define KEY_LEFT  	0x04
#define KEY_RIGHT 	0x07
#define KEY_A		0x18
#define KEY_B		0x0C
#define KEY_C		0x0D
#define KEY_D		0x0E

#define KEY_L_CTRL	0x01
#define KEY_L_SHIFT	0x02
#define KEY_L_ALT	0x04
#define KEY_L_WIN	0x08
#define KEY_R_CTRL	0x10
#define KEY_R_SHIFT	0x20
#define KEY_R_ALT	0x40
#define KEY_R_WIN	0x80

void keyBoard_value(char spcKey,char nomKey0,char nomKey1,char nomKey2,
					char nomKey3,char nomKey4,char nomKey5) 	
{
	USB->EP1_FIFO = spcKey;					//功能键
	USB->EP1_FIFO = 0;							//保留
	USB->EP1_FIFO = nomKey0;					//常用按键键值,按键1为0x59 数字依次类推
	USB->EP1_FIFO = nomKey1;					//常用按键键值
	USB->EP1_FIFO = nomKey2;					//常用按键键值
	USB->EP1_FIFO = nomKey3;
	USB->EP1_FIFO = nomKey4;
	USB->EP1_FIFO = nomKey5;
	USB->EP1_CTRL = 0x88;						//send 8 bytes packet	
}
/********************************************************************************************************
**函数信息 ： keyBoard_ctrl            
**功能描述 ： 键盘报告数据防重复发送
**输入参数 ： char spcKey(功能键)
			 nomKeyx(常用按键键值)
**输出参数 ：
********************************************************************************************************/
void keyBoard_ctrl(char spcKey,char nomKey0,char nomKey1,char nomKey2,
					char nomKey3,char nomKey4,char nomKey5)
{
    u32 timeout;
	keyBoard_value(spcKey,nomKey0,nomKey1,nomKey2,nomKey3,nomKey4,nomKey5);	//键值写入缓冲寄存器
	timeout =10000;
	while((USB->EP1_CTRL&0x80)&&(timeout--));
      
	keyBoard_value(KEY_NONE,KEY_NONE,KEY_NONE,KEY_NONE,KEY_NONE,KEY_NONE,KEY_NONE);//清键值
	
	timeout =10000;
	while((USB->EP1_CTRL&0x80)&&(timeout--));
}


//USB使能连接/断线   enable:0,断开;1,允许连接	
void USB_Port_Set(u8 enable)
{
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA,ENABLE);    //使能PORTA时钟	 
	if(enable)
	{
		//_SetCNTR(_GetCNTR()&(~(1<<1)));//退出断电模式
		
    USB->TOP  |= (1<<1); //20171030 JADE ADD
	}
	else
	{	  
		//_SetCNTR(_GetCNTR()|(1<<1));  // 断电模式
		
	  USB->TOP  &= ~(1<<1); //20171030 JADE ADD
		
		GPIOA->CRH&=0XFFF00FFF;
		GPIOA->CRH|=0X00033000;
		PAout(12)=0;    		  
	}
}


/*******************************************************************************
* Function Name  : Get_SerialNum.
* Description    : Create the serial number string descriptor.
* Input          : None.
* Output         : None.
* Return         : None.
*******************************************************************************/
void Get_SerialNum(void)
{
//  uint32_t Device_Serial0, Device_Serial1, Device_Serial2;

//  Device_Serial0 = *(uint32_t*)(0x1FFFF7E8);
//  Device_Serial1 = *(uint32_t*)(0x1FFFF7EC);
//  Device_Serial2 = *(uint32_t*)(0x1FFFF7F0);

//  if (Device_Serial0 != 0)
//  {
//    Joystick_StringSerial[2] = (uint8_t)(Device_Serial0 & 0x000000FF);
//    Joystick_StringSerial[4] = (uint8_t)((Device_Serial0 & 0x0000FF00) >> 8);
//    Joystick_StringSerial[6] = (uint8_t)((Device_Serial0 & 0x00FF0000) >> 16);
//    Joystick_StringSerial[8] = (uint8_t)((Device_Serial0 & 0xFF000000) >> 24);

//    Joystick_StringSerial[10] = (uint8_t)(Device_Serial1 & 0x000000FF);
//    Joystick_StringSerial[12] = (uint8_t)((Device_Serial1 & 0x0000FF00) >> 8);
//    Joystick_StringSerial[14] = (uint8_t)((Device_Serial1 & 0x00FF0000) >> 16);
//    Joystick_StringSerial[16] = (uint8_t)((Device_Serial1 & 0xFF000000) >> 24);

//    Joystick_StringSerial[18] = (uint8_t)(Device_Serial2 & 0x000000FF);
//    Joystick_StringSerial[20] = (uint8_t)((Device_Serial2 & 0x0000FF00) >> 8);
//    Joystick_StringSerial[22] = (uint8_t)((Device_Serial2 & 0x00FF0000) >> 16);
//    Joystick_StringSerial[24] = (uint8_t)((Device_Serial2 & 0xFF000000) >> 24);
//  }
}


//20171030 jade add start 

u8 GamePad_Send_Buffer[8] = {0x00,0x00,0x0f};
void GamePad_Send_Xbox(u8 Data1,u8 Data2,u8 Data3)
{
		GamePad_Send_Buffer[0] = Data1; 		
		GamePad_Send_Buffer[1] = Data2;		
		GamePad_Send_Buffer[2] = Data3;			
}

void GamePad_Send_Ps3(u8 Data1,u8 Data2,u8 Data3,u8 Data4,
	                    u8 Data5,u8 Data6,u8 Data7,u8 Data8)
{	
		GamePad_Send_Buffer[0] = Data1; 		
		GamePad_Send_Buffer[1] = Data2;		
		GamePad_Send_Buffer[2] = Data3;	
		GamePad_Send_Buffer[3] = Data4;	
		
		GamePad_Send_Buffer[4] = Data5; 		
		GamePad_Send_Buffer[5] = Data6;		
		GamePad_Send_Buffer[6] = Data7;	
		GamePad_Send_Buffer[7] = Data8;			
}

void GamePad_Send_Pc(u8 Data1,u8 Data2,u8 Data3,u8 Data4,
	                    u8 Data5,u8 Data6,u8 Data7,u8 Data8)
{	
		GamePad_Send_Buffer[0] = Data1; 		
		GamePad_Send_Buffer[1] = Data2;		
		GamePad_Send_Buffer[2] = Data3;	
		GamePad_Send_Buffer[3] = Data4;	
		
		GamePad_Send_Buffer[4] = Data5; 		
		GamePad_Send_Buffer[5] = Data6;		
		GamePad_Send_Buffer[6] = Data7;	
		GamePad_Send_Buffer[7] = Data8;			
}

void GamePad_Send_Buffer_Pc(u8 Buffer[])
{
	GamePad_Send_Buffer[0] = Buffer[0]; 		
	GamePad_Send_Buffer[1] = Buffer[1];		
	GamePad_Send_Buffer[2] = Buffer[2];	
	GamePad_Send_Buffer[3] = Buffer[3];	
	
	GamePad_Send_Buffer[4] = Buffer[4]; 		
	GamePad_Send_Buffer[5] = Buffer[5];		
	GamePad_Send_Buffer[6] = Buffer[6];	
	GamePad_Send_Buffer[7] = Buffer[7];		
}

void GamePad_Send_Buffer_Ps3(u8 Buffer[])
{
	GamePad_Send_Buffer[0] = Buffer[0]; 		
	GamePad_Send_Buffer[1] = Buffer[1];		
	GamePad_Send_Buffer[2] = Buffer[2];	
	GamePad_Send_Buffer[3] = Buffer[3];	
	
	GamePad_Send_Buffer[4] = Buffer[4]; 		
	GamePad_Send_Buffer[5] = Buffer[5];		
	GamePad_Send_Buffer[6] = Buffer[6];	
	GamePad_Send_Buffer[7] = Buffer[7];		
}
extern uint32_t USB_SIL_Write(uint8_t bEpAddr, uint8_t* pBufferPointer, uint32_t wBufferSize);
void GamePad_Send_Handle_Pc(void)
{
	uint8_t Send_Buffer[4];
//	if ((PrevXferComplete) && (bDeviceState == CONFIGURED))
	if (bDeviceState == CONFIGURED)	
	{
		Send_Buffer[0] = GamePad_Send_Buffer[3]; 		
		Send_Buffer[1] = GamePad_Send_Buffer[2];		
		Send_Buffer[2] = GamePad_Send_Buffer[1];			
		Send_Buffer[3] = GamePad_Send_Buffer[0];
		/* Write the descriptor through the endpoint */
		USB_SIL_Write(EP1_IN, (uint8_t*) Send_Buffer, 4);  
		
		//SetEPTxValid(ENDP1);  //20171031 jade mrak
		
		delay_ms(2);
		Send_Buffer[0] = GamePad_Send_Buffer[7]; 		
		Send_Buffer[1] = GamePad_Send_Buffer[6];		
		Send_Buffer[2] = GamePad_Send_Buffer[5];			
		Send_Buffer[3] = GamePad_Send_Buffer[4];
		/* Write the descriptor through the endpoint */
		USB_SIL_Write(EP1_IN, (uint8_t*) Send_Buffer, 4);  
		
		//SetEPTxValid(ENDP1);	//20171031 jade mrak	
		
		PrevXferComplete = 0;
	}	
}

void GamePad_Send_Handle_Ps3(void)
{
	uint8_t Send_Buffer[4];
//	if ((PrevXferComplete) && (bDeviceState == CONFIGURED))
	if (bDeviceState == CONFIGURED)	
	{
		Send_Buffer[0] = GamePad_Send_Buffer[3]; 		
		Send_Buffer[1] = GamePad_Send_Buffer[2];		
		Send_Buffer[2] = GamePad_Send_Buffer[1];			
		Send_Buffer[3] = GamePad_Send_Buffer[0];
		/* Write the descriptor through the endpoint */
		USB_SIL_Write(EP1_IN, (uint8_t*) Send_Buffer, 4);  
		
		//SetEPTxValid(ENDP1);  //20171031 jade mrak
		
		delay_ms(2);
		Send_Buffer[0] = GamePad_Send_Buffer[7]; 		
		Send_Buffer[1] = GamePad_Send_Buffer[6];		
		Send_Buffer[2] = GamePad_Send_Buffer[5];			
		Send_Buffer[3] = GamePad_Send_Buffer[4];
		/* Write the descriptor through the endpoint */
		USB_SIL_Write(EP1_IN, (uint8_t*) Send_Buffer, 4);  
		
		//SetEPTxValid(ENDP1);		//20171031 jade mrak
		
		PrevXferComplete = 0;
	}	
}

void GamePad_Send_Handle_Xbox(void)
{
	uint8_t Send_Buffer[7];
//	if ((PrevXferComplete) && (bDeviceState == CONFIGURED))
	if (bDeviceState == CONFIGURED)	
	{
		Send_Buffer[0] = GamePad_Send_Buffer[0]; 		
		Send_Buffer[1] = GamePad_Send_Buffer[1];		
		Send_Buffer[2] = GamePad_Send_Buffer[2];			
		Send_Buffer[3] = 0x7f;	
		Send_Buffer[4] = 0x7f;	
		Send_Buffer[5] = 0x7f;
		Send_Buffer[6] = 0x7f;
		/* Write the descriptor through the endpoint */
		USB_SIL_Write(EP1_IN, (uint8_t*) Send_Buffer, 7);  
		
		//SetEPTxValid(ENDP1);  //20171031 jade mrak
		
		PrevXferComplete = 0;
	}	
}
u8 Ps3ButtonDataBufferP1[Ps3DataBufferSize];
u8 Ps3ButtonDataBufferP2[Ps3DataBufferSize];
void AddButtonDataP1(u8 Index)
{
	u8 i = 0;

	for(i=0;i<Ps3DataBufferSize;i++)
	{
		if(Index == ButtonNullP1)
		{
			Ps3ButtonDataBufferP1[i] = Ps3ButtonTab[Index].Data[i];
		}		
		else
		{				
			Ps3ButtonDataBufferP1[i] |= Ps3ButtonTab[Index].Data[i];				
		}	
	}			
}

void AddButtonDataP2(u8 Index)
{
	u8 i = 0;

	for(i=0;i<Ps3DataBufferSize;i++)
	{
		if(Index == ButtonNullP2)
		{
			Ps3ButtonDataBufferP2[i] = Ps3ButtonTab[Index].Data[i];
		}		
		else
		{				
			Ps3ButtonDataBufferP2[i] |= Ps3ButtonTab[Index].Data[i];				
		}	
	}			
}

void Ps3SendButtonData(void)
{
	if (bDeviceState == CONFIGURED)	
	{
		/* Write the descriptor through the endpoint */
		USB_SIL_Write(EP1_IN, (uint8_t*) Ps3ButtonDataBufferP2, Ps3DataBufferSize);  

//		SetEPTxValid(ENDP1);	
//		PrevXferComplete = 0;		
			#if 0
			{
				u8 i = 0;
				printf("[%s:%d]usb tx data...\r\n",__FUNCTION__,__LINE__);
				printf("00 01 02 03 04 05 06 07 08 09 10 11 12 13 14 15 16 17 18 19");
				printf("\r\n");
				for(i=0;i<20;i++)
				{
					printf("%x  ",Ps3ButtonDataBufferP2[i]);			
				}	
				printf("\r\n\r\n");
			}
			#endif		
		delay_ms(9);	
		USB_SIL_Write(EP1_IN, (uint8_t*) Ps3ButtonDataBufferP1, Ps3DataBufferSize); //Ps3DataBufferSize
//		SetEPTxValid(ENDP1);
						
		PrevXferComplete = 0;
	}	
}

//20171030 jade add end 

/******************* (C) COPYRIGHT 2009 STMicroelectronics *****END OF FILE****/
