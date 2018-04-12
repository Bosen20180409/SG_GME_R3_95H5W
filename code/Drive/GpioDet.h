/*******************************文件信息***************************************
 **  文 件 名:    GpioDet.h
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
#ifndef __GpioDet_H__
#define __GpioDet_H__

#include "config.h"


/*===================================================*///start
#define PIN_GPIO1	    GPIO_Pin_0//PB0
#define PORT_GPIO1	  GPIOB
/*===================================================*///up
#define PIN_GPIO2	    GPIO_Pin_1//PB1
#define PORT_GPIO2	  GPIOB
/*===================================================*///down
#define PIN_GPIO3	    GPIO_Pin_3//PB3
#define PORT_GPIO3	  GPIOB
/*===================================================*///left
#define PIN_GPIO4	    GPIO_Pin_4//PB4
#define PORT_GPIO4	  GPIOB
/*===================================================*///right
#define PIN_GPIO5	    GPIO_Pin_5//PB5
#define PORT_GPIO5	  GPIOB
/*===================================================*///a
#define PIN_GPIO6	    GPIO_Pin_6//PB6
#define PORT_GPIO6	  GPIOB
/*===================================================*///b
#define PIN_GPIO7	    GPIO_Pin_7//PB7
#define PORT_GPIO7	  GPIOB
/*===================================================*///c
#define PIN_GPIO8	    GPIO_Pin_8//PB8
#define PORT_GPIO8	  GPIOB
/*===================================================*///d
#define PIN_GPIO9	    GPIO_Pin_9//PB9
#define PORT_GPIO9	  GPIOB
/*===================================================*///e
#define PIN_GPIO10	   GPIO_Pin_12//PB12
#define PORT_GPIO10	   GPIOB
/*===================================================*///f
#define PIN_GPIO11	   GPIO_Pin_13//PB13
#define PORT_GPIO11	   GPIOB
/*===================================================*/
/*===================================================*///start
#define PIN_GPIO13	   GPIO_Pin_0//PC0
#define PORT_GPIO13	   GPIOC
/*===================================================*///up
#define PIN_GPIO14	   GPIO_Pin_1//PC1
#define PORT_GPIO14	   GPIOC
/*===================================================*///down
#define PIN_GPIO15	   GPIO_Pin_2//PC2
#define PORT_GPIO15	   GPIOC
/*===================================================*///left
#define PIN_GPIO16	   GPIO_Pin_3//PC3
#define PORT_GPIO16	   GPIOC
/*===================================================*///right
#define PIN_GPIO17	   GPIO_Pin_4//PC4
#define PORT_GPIO17	   GPIOC
/*===================================================*///a
#define PIN_GPIO18	   GPIO_Pin_5//PC5
#define PORT_GPIO18	   GPIOC
/*===================================================*///b
#define PIN_GPIO19	   GPIO_Pin_6//PC6
#define PORT_GPIO19	   GPIOC
/*===================================================*///c
#define PIN_GPIO20	   GPIO_Pin_7//PC7
#define PORT_GPIO20	   GPIOC
/*===================================================*///d
#define PIN_GPIO21	   GPIO_Pin_8//PC8
#define PORT_GPIO21	   GPIOC
/*===================================================*///e
#define PIN_GPIO22	   GPIO_Pin_9//PC9
#define PORT_GPIO22	   GPIOC
/*===================================================*///f
#define PIN_GPIO23	   GPIO_Pin_10//PC10
#define PORT_GPIO23	   GPIOC
/*===================================================*/
//#define PIN_TB1	       GPIO_Pin_11//PC11
//#define PORT_TB1	     GPIOC
///*===================================================*/
//#define PIN_TB2	       GPIO_Pin_15//PA15
//#define PORT_TB2	     GPIOA
///*===================================================*/
/*===================================================*/
//#define PIN_START1	     GPIO_Pin_0//PC0
//#define PORT_START1	     GPIOC
///*===================================================*/
//#define PIN_START2	     GPIO_Pin_0//PA0
//#define PORT_START2	     GPIOB
///*===================================================*/
///*===================================================*///select



#define PIN_SELECT2	     GPIO_Pin_8//PA8
#define PORT_SELECT2	   GPIOA
/*===================================================*/
#define PIN_SELECT1	     GPIO_Pin_0//PA0
#define PORT_SELECT1	   GPIOA
/*===================================================*/
#define PIN_MODE2	       GPIO_Pin_8//PA9
#define PORT_MODE2	     GPIOA
/*===================================================*/
#define PIN_MODE1	       GPIO_Pin_1//PA1
#define PORT_MODE1	     GPIOA
/*===================================================*/
#define PIN_L2	         GPIO_Pin_5//PA5
#define PORT_L2	         GPIOA
/*===================================================*/
#define PIN_L1	         GPIO_Pin_2//PA2
#define PORT_L1	         GPIOA
/*===================================================*/
#define PIN_R2	         GPIO_Pin_4//PA4
#define PORT_R2	         GPIOA
/*===================================================*/
#define PIN_R1	         GPIO_Pin_13//PC13
#define PORT_R1	         GPIOC
/*===================================================*/

/*===================================================*/
#define PIN_WAKE_UP	     GPIO_Pin_0//PA0
#define PORT_WAKE_UP	   GPIOA
/*===================================================*/

void WakeUpGpioConfig(void);
void WKUP_Init(void);

u32 GpioDet1(void);
void GpioDetConfig(void);

#endif






























































