/******************** (C) COPYRIGHT 2009 STMicroelectronics ********************
* File Name          : usb_endp.c
* Author             : MCD Application Team
* Version            : V3.0.1
* Date               : 04/27/2009
* Description        : Endpoint routines
********************************************************************************
* THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
* WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE TIME.
* AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY DIRECT,
* INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING FROM THE
* CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE CODING
* INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
*******************************************************************************/

/* Includes ------------------------------------------------------------------*/
#include "platform_config.h"
//#include "MM32x103.h"
#include "MM32F103.h"  //20171027_JADE_ADD
#include "usb_lib.h"
#include "usb_istr.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
uint8_t Receive_Buffer[2];

/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
/*******************************************************************************
* Function Name  : EP1_OUT_Callback.
* Description    : EP1 OUT Callback Routine.
* Input          : None.
* Output         : None.
* Return         : None.
*******************************************************************************/
#if 0  //20171030 jade mark
void EP1_OUT_Callback(void)
{
  BitAction Led_State;
  
  PMAToUserBufferCopy(Receive_Buffer, ENDP3, 2);
  
  if (Receive_Buffer[1] == 0)
  {
    Led_State = Bit_RESET;
  }
  else 
  {
    Led_State = Bit_SET;
  }
  switch (Receive_Buffer[0])
  {
    case 1: /* Led 1 */
     GPIO_WriteBit(GPIO_LED1, GPIO_LED1_PIN, Led_State);
     break;
    case 2: /* Led 2 */
      GPIO_WriteBit(GPIO_LED2, GPIO_LED2_PIN, Led_State);
      break;
		default:
    GPIO_Write(GPIO_LED1, ~(uint16_t)(GPIO_LED1_PIN));
		GPIO_Write(GPIO_LED2, ~(uint16_t)(GPIO_LED2_PIN));
    break;
  }

}
#endif


extern __IO uint8_t PrevXferComplete;

void EP1_IN_Callback(void)
{
  PrevXferComplete = 1;
}
/******************* (C) COPYRIGHT 2009 STMicroelectronics *****END OF FILE****/

