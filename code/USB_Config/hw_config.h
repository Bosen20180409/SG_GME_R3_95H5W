/******************** (C) COPYRIGHT 2009 STMicroelectronics ********************
* File Name          : hw_config.h
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

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __HW_CONFIG_H
#define __HW_CONFIG_H

/* Includes ------------------------------------------------------------------*/
#include "usb_type.h"
#include "HAL_uart.h"

/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported define -----------------------------------------------------------*/
#define JOY_IDLE            0
#define JOY_DOWN            1
#define JOY_LEFT            2
#define JOY_RIGHT           3
#define JOY_UP              4
#define JOY_A               5
#define JOY_B               6
#define JOY_X               7
#define JOY_Y               8
#define CURSOR_STEP         30




#define DEVICE_PC  0
#define DEVICE_PS3 1
#define DEVICE_PS4 2

extern u8 DeviceType;


void GamePad_Send_Xbox(u8 Data1,u8 Data2,u8 Data3);
void GamePad_Send_Handle_Xbox(void);
void GamePad_Send_Ps3(u8 Data1,u8 Data2,u8 Data3,u8 Data4,
	                    u8 Data5,u8 Data6,u8 Data7,u8 Data8);

void GamePad_Send_Handle_Pc(void);
void GamePad_Send_Buffer_Pc(u8 Buffer[]);

void GamePad_Send_Handle_Ps3(void);
void GamePad_Send_Buffer_Ps3(u8 Buffer[]);

void GamePad_Send_Test1( u8 Data1,u8 Data2,u8 Data3,u8 Data4,
												u8 Data5,u8 Data6,u8 Data7,u8 Data8,
												u8 Data9,u8 Data10,u8 Data11,u8 Data12,
												u8 Data13,u8 Data14,u8 Data15,u8 Data16,
												u8 Data17,u8 Data18,u8 Data19,u8 Data20,
												u8 Data21,u8 Data22,u8 Data23,u8 Data24,
												u8 Data25,u8 Data26,u8 Data27);




/* Exported functions ------------------------------------------------------- */
void Set_System(void);
void Set_USBClock(void);
void GPIO_AINConfig(void);
void Enter_LowPowerMode(void);
void Leave_LowPowerMode(void);
void USB_Interrupts_Config(void);
void USB_Cable_Config (FunctionalState NewState);
void Joystick_Send(uint8_t Keys);
uint8_t JoyState(void);
void Get_SerialNum(void);

#endif  /*__HW_CONFIG_H*/

/******************* (C) COPYRIGHT 2009 STMicroelectronics *****END OF FILE****/
