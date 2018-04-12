/*******************************�ļ���Ϣ***************************************
 **  �� �� ��:    HC165.h
 **  ��    ����   V1.0
 **  ��    �ܣ�   74HC165����
 **  ��    ����
 **  ��    �ߣ�   ����
 **  ��	   �ڣ�2011/06/21
 **----------------------------��ʷ�汾��Ϣ------------------------------------
 **  �� �� �ˣ�
 **  ��    ���� 
 **  ��  ���ڣ�
 **  ��  ������
 ******************************************************************************/
#ifndef __HC165_H__
#define __HC165_H__


#include "config.h"


//----165 ��·
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



