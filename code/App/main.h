#ifndef _MAIN_INIT_H_	
#define _MAIN_INIT_H_

#ifdef __cplusplus		   //�����CPP����C���� //��ʼ����
extern "C" {
#endif

//#include "stm32f10x.h"		//STM32�̼���
//#include "bsp.h"			//�弶��ʼ��
#include  "MM32L073PF.h"	
	
#define PC     0
#define PS3    1
#define PS4    2
#define XBOX   4
	
void GpioDetHandle(void);	


extern u8 GamePad_Send_Flag;

#ifdef __cplusplus		   //�����CPP����C���� //��������
}
#endif

#endif
