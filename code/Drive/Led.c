/*******                                                                   ************************�ļ���Ϣ***************************************
 **  �� �� ��:    led.c
 **  ��    ����   V1.0
 **  ��    �ܣ�   LED����
 **  ��    ����
 **  ��    �ߣ�   ����
 **  ��	   �ڣ�
 **----------------------------��ʷ�汾��Ϣ------------------------------------
 **  �� �� �ˣ�
 **  ��    ���� 
 **  ��  ���ڣ�
 **  ��  ������
 ******************************************************************************/
#include "Led.h"


u16 RevUsart1TimeOut = 0;
u16 RevUsart2TimeOut = 0;


/*================================================================= 
 * ���ܣ� ����LED
 * ������ 
 * ���أ�   
 * ���ڣ� 
 *================================================================*/
void LedGpioConfig(void)
{
	GPIO_InitTypeDef GPIO_InitStructureLed;

	GPIO_InitStructureLed.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructureLed.GPIO_Mode = GPIO_Mode_Out_PP;  //GPIO_Mode_IN_FLOATING//��������
                                                       //GPIO_Mode_IPD//��������
                                                       //GPIO_Mode_IPU//��������

	GPIO_InitStructureLed.GPIO_Pin = PinLed0;	   
	GPIO_Init(PortLed0, &GPIO_InitStructureLed);
	
//	GPIO_InitStructureLed.GPIO_Pin = PinLedPs3;	   
//	GPIO_Init(PortLedPs3, &GPIO_InitStructureLed);

//	GPIO_InitStructureLed.GPIO_Pin = PinLed360;	   
//	GPIO_Init(PortLed360, &GPIO_InitStructureLed);

//	GPIO_InitStructureLed.GPIO_Pin = PinLedPc;	   
//	GPIO_Init(PortLedPc, &GPIO_InitStructureLed);

//	GPIO_InitStructureLed.GPIO_Pin = PinLedPs4;	   
//	GPIO_Init(PortLedPs4, &GPIO_InitStructureLed);	
	


	Led0_Off;
//	LedPs3_Off;
//	Led360_Off;
//	LedPc_Off;
//	LedPs4_Off;
//	Led1_Off;
//	Led2_Off;

}



void Led0_Reverse(void)
{
	static u8 bIsHigh = 0;

	if(bIsHigh == 1)
	{
		bIsHigh = 0;
		Led0_On;
	}
	else
	{
		bIsHigh = 1;
		Led0_Off;
	}
}

//void Led1_Reverse(void)
//{
//	static u8 bIsHigh = 0;

//	if(bIsHigh == 1)
//	{
//		bIsHigh = 0;
//		Led1_On;
//	}
//	else
//	{
//		bIsHigh = 1;
//		Led1_Off;
//	}
//}



void RevUart1LedFlag(void)
{
	if(RevUsart1TimeOut>0)
	{
		RevUsart1TimeOut --;
		Led0_On;
		if(RevUsart1TimeOut == 0)
		{
			Led0_Off;
		}
	}
}



void RevUart2LedFlag(void)
{
//	if(RevUart2TimeOut>0)
//	{
//		RevUart2TimeOut --;
//		Led1_On;
//		if(RevUart2TimeOut == 0)
//		{
//			Led1_Off;
//		}
//	}
}






