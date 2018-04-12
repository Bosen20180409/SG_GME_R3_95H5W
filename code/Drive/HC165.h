/*******************************文件信息***************************************
 **  文 件 名:    HC165.h
 **  版    本：   V1.0
 **  功    能：   74HC165驱动
 **  用    法：
 **  作    者：   草塘
 **  日	   期：2011/06/21
 **----------------------------历史版本信息------------------------------------
 **  修 改 人：
 **  版    本： 
 **  日  　期：
 **  描  　述：
 ******************************************************************************/
#ifndef __HC165_H__
#define __HC165_H__


#include "config.h"


//----165 链路
#define Pin165LD	GPIO_Pin_7
#define Port165LD	GPIOB

#define Pin165CLK1	GPIO_Pin_3
#define Port165CLK1	GPIOB

#define Pin165Data1	  GPIO_Pin_8
#define Port165Data1	GPIOA

#define PinSw01	  GPIO_Pin_5
#define PortSw01	GPIOB

#define PinSw02	  GPIO_Pin_6
#define PortSw02	GPIOB

void Hc165GpioConfig(void);
//void Get165Data(u8 DataBuf[]);
void Test_HC165(void);



#endif



