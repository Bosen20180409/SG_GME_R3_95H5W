#ifndef _MAIN_INIT_H_	
#define _MAIN_INIT_H_

#ifdef __cplusplus		   //定义对CPP进行C处理 //开始部分
extern "C" {
#endif

//#include "stm32f10x.h"		//STM32固件库
//#include "bsp.h"			//板级初始化
#include  "MM32L073PF.h"	
	
#define PC     0
#define PS3    1
#define PS4    2
#define XBOX   4
	
void GpioDetHandle(void);	


extern u8 GamePad_Send_Flag;

#ifdef __cplusplus		   //定义对CPP进行C处理 //结束部分
}
#endif

#endif
