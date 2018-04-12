/******************** (C) COPYRIGHT 2009 STMicroelectronics ********************
* File Name          : main.c
* Author             : MCD Application Team
* Version            : V3.0.1
* Date               : 04/27/2009
* Description        : Custom HID demo main file
********************************************************************************
* THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
* WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE TIME.
* AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY DIRECT,
* INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING FROM THE
* CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE CODING
* INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
*******************************************************************************/

/* Includes ------------------------------------------------------------------*/
#include "MM32L073PF.h"  //20180118_JADE_ADD

#include "main.h"

#include "hw_config.h"
#include "initial.h"

/* Private functions ---------------------------------------------------------*/

/*******************************************************************************
* Function Name  : main.
* Description    : main routine.
* Input          : None.
* Output         : None.
* Return         : None.
*******************************************************************************/

extern void SysLoop(void);
int main(void)
{
//	u16 nCount = 0;
//	u8 i = 0;
	
  Set_System();
	
  NVIC_Configuration();  //中断配置
	
	while(1)
	{
		SysLoop( );
	}
	
//	Hc165GpioConfig( );
//	
//  USB_Interrupts_Config();
//	
//  Set_USBClock();
//  USB_Init();	
//  USB->EP1_CTRL = 0;
//	
//	delay_init();
//	
//	Usart1Config();//调试
//	Usart2Config();
//	
//	LedGpioConfig();

//	printf("==============================\r\n");	
//	printf("==============================\r\n");	
//	delay_ms(500);
//	delay_ms(500);
//	delay_ms(500);
//	delay_ms(500);
//	delay_ms(500);
//	delay_ms(500);
//	delay_ms(500);
//	delay_ms(500);
//	delay_ms(500);
//	delay_ms(500);
//	
//	if(bDeviceState == CONFIGURED)	
//	{
//		printf("[%s:%d]usb ok\r\n",__FUNCTION__,__LINE__); 
//	}
//	else
//	{
//		printf("[%s:%d]usb err\r\n",__FUNCTION__,__LINE__); 
//	}
//	
////	LoadRegistersCfg(RegistersCfg,RegistersCfg315M);
////	LoadRegistersCfg(RegistersCfg,RegistersCfg433M);
//	
//	SPI1_Init( );
//	InitRFChip ( );

//	STM32_TIM2_Config( ); 
//	
////	if(GPIO_ReadInputDataBit(PortSw01,PinSw01) == 0)
////	{
////		SetFeq(F315M);
////		printf("[%s:%d]315M ok\r\n",__FUNCTION__,__LINE__); 
////	}
////	else
////	{
////		SetFeq(F433M);
////		printf("[%s:%d]433M ok\r\n",__FUNCTION__,__LINE__); 
////	}
//	
//	SetFeq(F315M);

////	while(1)
////	{
////		Usart2RevHandle( );
////		delay_ms(10);
////	}
//	
//	SX1212Test( );
#if 0
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
	
//	i = 0x1e;
//	WriteRegister(i, RegistersCfg[i]);
	DeviceType = DEVICE_PS3;  //DEVICE_PC;
	
	GpioDetConfig();
	
//	while(1)
//	{
//		Test_HC165( );
//		delay_ms(500);
//		delay_ms(500);
//		delay_ms(500);
//		delay_ms(500);
//		delay_ms(500);
//		delay_ms(500);	
//		delay_ms(500);
//		delay_ms(500);
//		delay_ms(500);
//		delay_ms(500);
//		delay_ms(500);
//		delay_ms(500);		
//		Led0_Reverse( );
//	}
		
	LedPs3_On;
  //STM32_TIM2_Config(); 
	
	STM32_TIM3_Config(); //UART1 空闲中断模拟用TIM3定时实现	
	
	while(1)
	{
		switch(bDeviceState)
		{
			case UNCONNECTED:
//				printf("[%s:%d]UNCONNECTED\r\n",__FUNCTION__,__LINE__);
				break;
			case ATTACHED:
//				printf("[%s:%d]ATTACHED\r\n",__FUNCTION__,__LINE__);
				break;	
			case POWERED:
//				printf("[%s:%d]POWERED\r\n",__FUNCTION__,__LINE__);
				break;
			case SUSPENDED:
//				printf("[%s:%d]SUSPENDED\r\n",__FUNCTION__,__LINE__);
				break;	
			case ADDRESSED:
//				printf("[%s:%d]ADDRESSED\r\n",__FUNCTION__,__LINE__);
				break;	
			case CONFIGURED:
//				printf("[%s:%d]CONFIGURED\r\n",__FUNCTION__,__LINE__);
				Led0_On;//当USB配置成功了，LED1亮，否则，灭
				break;			
		}

		if(bDeviceState==CONFIGURED)
		{
//			if(GamePad_Send_Flag == 1)	
			{
				switch (DeviceType)
				{
					case DEVICE_PC:	
					  GpioData = GpioDet1( );					
//						nCountDebug ++;
//						if(nCountDebug > 10000)
//						{
//							nCountDebug = 0;
//							printf("[%s:%d]GpioData         %x\r\n",__FUNCTION__,__LINE__,GpioData);
//					
//						}					
					//if(GpioDataTemp != GpioData)  //20171030  Debug jade mark
						{	
							GpioDataTemp = GpioData;
							ParseSrcData(GpioDataTemp,GamePadSendBuf);
							
							
							GamePadSendBuf[0]=0x01;
							GamePadSendBuf[1]=0x02;							
							GamePadSendBuf[2]=0x5a;
							GamePadSendBuf[3]=0xa5;  //20171030  Debug jade add

							
							
							GamePad_Send_Buffer_Pc(GamePadSendBuf);

							GamePad_Send_Handle_Pc( );
							delay_us(500);
							GamePad_Send_Handle_Pc( );
							delay_us(500);
							GamePad_Send_Handle_Pc( );
							delay_us(500);
							GamePad_Send_Handle_Pc( );
							delay_us(500);
							GamePad_Send_Handle_Pc( );
							delay_us(500);		
							GamePad_Send_Handle_Pc( );
							delay_us(500);
							GamePad_Send_Handle_Pc( );
							delay_us(500);		
							GamePad_Send_Handle_Pc( );
							delay_us(500);							
						}						
//						nCountDebug ++;
//						if(nCountDebug > 10000)
//						{
//							nCountDebug = 0;
//							printf("[%s:%d]GpioData         %x\r\n",__FUNCTION__,__LINE__,GpioData);
//					
//						}						
						
						nCount ++;
						if(nCount > 200)
						{
							nCount = 0;
							
//							ParseSrcData(GpioDataTemp,GamePadSendBuf);
//							printf("[%s:%d]GpioDataTemp         %x\r\n",__FUNCTION__,__LINE__,GpioDataTemp);
//							printf("[%s:%d]GamePadSendBuf %x %x %x %x\r\n",__FUNCTION__,__LINE__,GamePadSendBuf[3],GamePadSendBuf[2],GamePadSendBuf[1],GamePadSendBuf[0]);
//							printf("[%s:%d]               %x %x %x %x\r\n",__FUNCTION__,__LINE__,GamePadSendBuf[7],GamePadSendBuf[6],GamePadSendBuf[5],GamePadSendBuf[4]);
							
							GamePad_Send_Handle_Pc( );
						}					
						break;							
					case DEVICE_PS3:	
					case DEVICE_PS4:		
			
						break;	
				}						
			}									
		}
		else//无线模式
		{
			Test_HC165( );
		}
		delay_us(100);
			
		Usart1RevHandle( );				
	}
#endif
}


/*******************************************************************************
* Function Name  : Delay
* Description    : Inserts a delay time.
* Input          : nCount: specifies the delay time length.
* Output         : None
* Return         : None
*******************************************************************************/
void Delay(__IO uint32_t nCount)
{
  for(; nCount!= 0;nCount--);
}

#ifdef  USE_FULL_ASSERT
/*******************************************************************************
* Function Name  : assert_failed
* Description    : Reports the name of the source file and the source line number
*                  where the assert_param error has occurred.
* Input          : - file: pointer to the source file name
*                  - line: assert_param error line source number
* Output         : None
* Return         : None
*******************************************************************************/
void assert_failed(uint8_t* file, uint32_t line)
{ 
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */

  /* Infinite loop */
  while(1)
  {
  }
}
#endif

/******************* (C) COPYRIGHT 2009 STMicroelectronics *****END OF FILE****/
