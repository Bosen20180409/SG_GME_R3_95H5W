/*******************************文件信息***************************************
 **  文 件 名:    SysLoop.c
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
#include "SysLoop.h"


#include "led.h"

#include "usb_lib.h"
#include "hw_config.h"
#include "usb_pwr.h"
#include "HC165.h"	

void Delay(__IO uint32_t nCount);



vu8 DetEn = 0;
u8 MainPro = STEP00;
u32 CpuID[3];

u16 nCountDebug = 0;
extern void FlashRead(void);
extern u8 JoystickMode;
extern void SX1212SendData(u32 Data);
extern void OnMasterUsbPC(void);
void ChangeMode(void);
u8 DebugPoint = 0;
u8 ReturnCode = 0xff;
u8 RF_SEL = 0;

extern u8 DeviceType;
u32 nCountMax = 10;
u8 GamePad_Send_Flag = 0;
	
u8 GamePadSendBuf[8];
extern void USB_Port_Set(u8 enable);
u32 Rx_Count = 0;


void SysLoop(void)
{
	static u16 nCount = 0;
		switch(MainPro)
		{
			case STEP00:
				MainPro = STEP01;
				break;
//===================================================	
//===================================================				
			case STEP01://系统初始化
				Hc165GpioConfig( );
						
				delay_init();
				
				Usart1Config();//调试
				Usart2Config();
				WakeUpGpioConfig( );
				LedGpioConfig();
				STM32_TIM2_Config( ); 
				printf("==============================\r\n");	
				printf("==============================\r\n");	
	
				MainPro = STEP02;
//				MainPro = STEP09;			
				break;
//===================================================	
//===================================================				
			case STEP02://检测当前运行模式（USB，WIRELESS)
//	while(1)
//	{
//		Usart2SendTest( );
//		delay_ms(500);
//		delay_ms(500);
//		delay_ms(500);
//		delay_ms(500);
//		delay_ms(500);
//		delay_ms(500);
//	}	


				USB_Interrupts_Config();
				
				Set_USBClock();
				USB_Init();	
				USB->EP1_CTRL = 0;				
				delay_ms(500);
				delay_ms(500);
				delay_ms(500);
				delay_ms(500);
				delay_ms(500);
				delay_ms(500);
				delay_ms(500);
				delay_ms(500);
				delay_ms(500);
				delay_ms(500);
				if(bDeviceState == CONFIGURED)
				{
					MainPro = STEP03;
					printf("[%s:%d]usb ok\r\n",__FUNCTION__,__LINE__); 
				}
				else
				{
					MainPro = STEP05;
					printf("[%s:%d]usb err\r\n",__FUNCTION__,__LINE__); 
				}			
				break;
//===================================================	
//===================================================				
			case STEP03://USB模式,参数初始化
				MainPro = STEP04;
				break;	
//===================================================	
//===================================================				
			case STEP04://USB模式,Work
				OnMasterUsbPC( );
				break;	
//===================================================	
//===================================================				
			case STEP05://无线模式,参数初始化
			//	LoadRegistersCfg(RegistersCfg,RegistersCfg315M);
			//	LoadRegistersCfg(RegistersCfg,RegistersCfg433M);
				
				SPI1_Init( );
				InitRFChip ( );	
				/*配置ADC1为单次转换模式,通道1使能*/
//				ADC1_SingleChannel( ADC_Channel_1);	


			
			//	if(GPIO_ReadInputDataBit(PortSw01,PinSw01) == 0)
			//	{
			//		SetFeq(F315M);
			//		printf("[%s:%d]315M ok\r\n",__FUNCTION__,__LINE__); 
			//	}
			//	else
			//	{
			//		SetFeq(F433M);
			//		printf("[%s:%d]433M ok\r\n",__FUNCTION__,__LINE__); 
			//	}
				
				SetFeq(F315M);
								
				MainPro = STEP06;
				break;
//===================================================	
//===================================================				
			case STEP06://无线模式,Work
				OnMasterWireless( );
			
				nCount ++;
				if(nCount > 500)
				{
					nCount = 0;
//					ADC_VAL = Get_Adc_Average(ADC_Channel_1,2);
					
//					printf("[%s:%d]ADC_VAL:%d\r\n",__FUNCTION__,__LINE__,ADC_VAL); 
				}
				break;
//===================================================	
//===================================================				
			case STEP09://测试模式,参数初始化
				SPI1_Init( );
				InitRFChip ( );		
				SetFeq(F315M);
				MainPro = STEP10;
				break;
//===================================================	
//===================================================				
			case STEP10://测试模式,Work
				OnSlave( );
				break;	
//===================================================	
//===================================================				
		}
}

void test(void)
{
//	LoadRegistersCfg(RegistersCfg,RegistersCfg433M);
//	LoadRegistersCfg(RegistersCfg,RegistersCfg315M);


//	Usart1SendData(0x12345678);


//	while(1)
//	{
//		delay_ms(10);
//		Usart2RevHandle( );
//	}

//while(1)
//{
//	Usart2SendTest( );
//	delay_ms(500);	
//	delay_ms(500);
//}	
}


//void SX1212Test(void)
//{
//	while(1)
//	{
////	OnMasterWireless();
//		OnSlave( );		
////	OnSlave_433M( );			
//	}
//}
