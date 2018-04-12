/*******************************文件信息***************************************
 **  文 件 名:    led.h
 **  版    本：   V1.0
 **  功    能：   LED驱动
 **  用    法：
 **  作    者：   草塘
 **  日	   期：2011/06/21
 **----------------------------历史版本信息------------------------------------
 **  修 改 人：
 **  版    本： 
 **  日  　期：
 **  描  　述：
 ******************************************************************************/
#ifndef __LED_H__
#define __LED_H__

#include "config.h"



#define PinLed0	    GPIO_Pin_15
#define PortLed0	  GPIOA
#define	Led0_Off    PortLed0->BSRR = PinLed0   //PD2   								    
#define	Led0_On     PortLed0->BRR = PinLed0 

#define PinLedPs3	    GPIO_Pin_12
#define PortLedPs3	  GPIOC
#define	LedPs3_On    PortLedPs3->BSRR = PinLedPs3   //PC12  								    
#define	LedPs3_Off     PortLedPs3->BRR = PinLedPs3 

#define PinLed360	    GPIO_Pin_13
#define PortLed360	  GPIOC
#define	Led360_On    PortLed360->BSRR = PinLed360   //PC13   								    
#define	Led360_Off     PortLed360->BRR = PinLed360 

#define PinLedPc	    GPIO_Pin_14
#define PortLedPc	  	GPIOC
#define	LedPc_On    PortLedPc->BSRR = PinLedPc   //PC14   								    
#define	LedPc_Off     PortLedPc->BRR = PinLedPc 

#define PinLedPs4	    GPIO_Pin_15
#define PortLedPs4	  GPIOC
#define	LedPs4_On    PortLedPs4->BSRR = PinLedPs4   //PC15   								    
#define	LedPs4_Off     PortLedPs4->BRR = PinLedPs4



void RevUart1LedFlag(void);

//配置LED
void LedGpioConfig(void);

void Led0_Reverse(void);



#endif






























































