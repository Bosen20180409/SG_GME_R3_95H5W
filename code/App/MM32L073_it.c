/******************** (C) COPYRIGHT 2009 MM32 ********************
* File Name          : MM32L073_it.c
* Author             : MCD Application Team
* Version            : V3.0.1
* Date               : 04/27/2009
* Description        : Main Interrupt Service Routines.
*                      This file provides template for all exceptions handler
*                      and peripherals interrupt service routine.
********************************************************************************
* THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
* WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE TIME.
* AS A RESULT, MM32 SHALL NOT BE HELD LIABLE FOR ANY DIRECT,
* INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING FROM THE
* CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE CODING
* INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
*******************************************************************************/

/* Includes ------------------------------------------------------------------*/
#include "platform_config.h"
#include "MM32L073_it.h"
#include "usb_lib.h"
#include "usb_istr.h"
#include "hw_config.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
uint8_t Send_Buffer[64];
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/******************************************************************************/
/*            Cortex-M3 Processor Exceptions Handlers                         */
/******************************************************************************/

/*******************************************************************************
* Function Name  : NMI_Handler
* Description    : This function handles NMI exception.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void NMI_Handler(void)
{
}

/*******************************************************************************
* Function Name  : HardFault_Handler
* Description    : This function handles Hard Fault exception.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void HardFault_Handler(void)
{
  /* Go to infinite loop when Hard Fault exception occurs */
  while (1)
  {
  }
}

/*******************************************************************************
* Function Name  : MemManage_Handler
* Description    : This function handles Memory Manage exception.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void MemManage_Handler(void)
{
  /* Go to infinite loop when Memory Manage exception occurs */
  while (1)
  {
  }
}

/*******************************************************************************
* Function Name  : BusFault_Handler
* Description    : This function handles Bus Fault exception.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void BusFault_Handler(void)
{
  /* Go to infinite loop when Bus Fault exception occurs */
  while (1)
  {
  }
}

/*******************************************************************************
* Function Name  : UsageFault_Handler
* Description    : This function handles Usage Fault exception.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void UsageFault_Handler(void)
{
  /* Go to infinite loop when Usage Fault exception occurs */
  while (1)
  {
  }
}

/*******************************************************************************
* Function Name  : SVC_Handler
* Description    : This function handles SVCall exception.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void SVC_Handler(void)
{
}

/*******************************************************************************
* Function Name  : DebugMon_Handler
* Description    : This function handles Debug Monitor exception.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void DebugMon_Handler(void)
{
}

/*******************************************************************************
* Function Name  : PendSV_Handler
* Description    : This function handles PendSVC exception.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void PendSV_Handler(void)
{
}

/*******************************************************************************
* Function Name  : SysTick_Handler
* Description    : This function handles SysTick Handler.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void SysTick_Handler(void)
{
}

/******************************************************************************/
/*            MM32L073PF Peripherals Interrupt Handlers                        */
/******************************************************************************/

/*******************************************************************************
* Function Name  : USB_LP_CAN1_RX0_IRQHandler
* Description    : This function handles USB Low Priority or CAN RX0 interrupts 
*                  requests.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
//void USB_HP_CAN1_TX_IRQHandler(void)
//{
//    USB_Istr();
//}

void USB_IRQHandler(void) //mm32
{
	
	 USB_Istr();
	
}

///*******************************************************************************
//* Function Name  : EXTI0_IRQHandler
//* Description    : This function handles External lines 0 interrupt request.
//* Input          : None
//* Output         : None
//* Return         : None
//*******************************************************************************/
//void EXTI0_1_IRQHandler(void)
//{
//		/*  
//	if(EXTI_GetITStatus(GPIO_TAMPER_EXTI_Line) != RESET)
//  {  

//    Send_Buffer[0] = 0x06;
//    
//    if (GPIO_ReadInputDataBit(GPIO_TAMPER, GPIO_TAMPER_PIN) == Bit_RESET)
//    {
//      Send_Buffer[1] = 0x01;
//    }
//    else 
//    {
//      Send_Buffer[1] = 0x00;
//    }
//    
////    UserToPMABufferCopy(Send_Buffer, ENDP1_TXADDR, 2);
////    SetEPTxCount(ENDP1, 2);
////    SetEPTxValid(ENDP1);
//    
//    // Clear the EXTI line 0 pending bit 
////    EXTI_ClearITPendingBit(GPIO_TAMPER_EXTI_Line);
//  }*/ //20180118_jade_mark
//}

/*******************************************************************************
* Function Name  : EXTI1_IRQHandler
* Description    : This function handles External lines 1 interrupt request.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
/*
void EXTI1_IRQHandler(void)
{

  if(EXTI_GetITStatus(GPIO_KEY2_EXTI_Line) != RESET)
  {
		
    Send_Buffer[0] = 0x05;
    
    if (GPIO_ReadInputDataBit(GPIO_KEY, GPIO_KEY2_PIN) == Bit_RESET)
    {
      Send_Buffer[1] = 0x01;
    }
    else 
    {
      Send_Buffer[1] = 0x00;
    }
    
//    UserToPMABufferCopy(Send_Buffer, ENDP1_TXADDR, 2);
//    SetEPTxCount(ENDP1, 2);
//    SetEPTxValid(ENDP1);
    
    // Clear the EXTI 1 line  pending bit 
    EXTI_ClearITPendingBit(GPIO_KEY2_EXTI_Line);
  } 
}
*/ //20180118_jade_mark

/*******************************************************************************
* Function Name  : EXTI9_5_IRQHandler
* Description    : This function handles External lines 9 to 5 interrupt request.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/

void EXTI4_15_IRQHandler(void)
{
  if(EXTI_GetITStatus(GPIO_KEY_EXTI_Line) != RESET)
  { 
    /*		
    Send_Buffer[0] = 0x07; 
		Send_Buffer[1] =Get_Adc(ADC_AIN_CHANNEL);
		*/  //20180118_jade_mark
		
//		UserToPMABufferCopy(Send_Buffer, ENDP1_TXADDR, 2);
//		SetEPTxCount(ENDP1, 2);
//		SetEPTxValid(ENDP1);
    
    /* Clear the EXTI 9 to 5 line  pending bit */
    EXTI_ClearITPendingBit(GPIO_KEY_EXTI_Line);
  }
}

/******************************************************************************/
/*                 MM32L073 Peripherals Interrupt Handlers                   */
/*  Add here the Interrupt Handler for the used peripheral(s) (PPP), for the  */
/*  available peripheral interrupt handler's name please refer to the startup */
/*  file (startup_MM32X103.s).                                                */
/******************************************************************************/

/*******************************************************************************
* Function Name  : PPP_IRQHandler
* Description    : This function handles PPP interrupt request.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
/*void PPP_IRQHandler(void)
{
}*/

/******************* (C) COPYRIGHT 2009 MM32 *****END OF FILE****/
