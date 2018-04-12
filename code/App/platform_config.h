/******************** (C) COPYRIGHT 2009 MM32 ********************
* File Name          : platform_config.h
* Author             : MCD Application Team
* Version            : V3.0.1
* Date               : 04/27/2009
* Description        : Evaluation board specific configuration file.
********************************************************************************
* THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
* WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE TIME.
* AS A RESULT, MM32 SHALL NOT BE HELD LIABLE FOR ANY DIRECT,
* INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING FROM THE
* CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE CODING
* INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
*******************************************************************************/

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __PLATFORM_CONFIG_H
#define __PLATFORM_CONFIG_H

/* Includes ------------------------------------------------------------------*/

/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Uncomment the line corresponding to the MM32 evaluation board
   used to run the example */

/* Define the MM32L073 hardware depending on the used evaluation board */

#if 0 //MM32L073例程定义在此暂时屏蔽
  #define USB_DISCONNECT                      GPIOA  
  #define USB_DISCONNECT_PIN                  GPIO_Pin_11|GPIO_Pin_12
  #define RCC_AHBPeriph_GPIO_DISCONNECT      RCC_AHBPeriph_GPIOA

  #define RCC_AHBPeriph_GPIO_KEY             RCC_AHBPeriph_GPIOC
  #define RCC_AHBPeriph_GPIO_TAMPER          RCC_AHBPeriph_GPIOA
  #define RCC_AHBPeriph_GPIO_IOAIN           RCC_AHBPeriph_GPIOA
  #define RCC_AHBPeriph_GPIO_LED             RCC_AHBPeriph_GPIOA|RCC_AHBPeriph_GPIOD

  #define GPIO_KEY                            GPIOC
  #define GPIO_TAMPER                         GPIOA
  #define GPIO_IOAIN                          GPIOA
  #define GPIO_LED1                           GPIOA
	#define GPIO_LED2                           GPIOD

  #define GPIO_KEY1_PIN                       GPIO_Pin_5   /* PC.05 */
	#define GPIO_KEY2_PIN                       GPIO_Pin_1   /* PC.01 */
  #define GPIO_TAMPER_PIN                     GPIO_Pin_0   /* PA.00 */
  #define GPIO_IOAIN_PIN                      GPIO_Pin_1   /* PA.01 */
  
  #define GPIO_LED1_PIN                       GPIO_Pin_8   /* PA.08 */
  #define GPIO_LED2_PIN                       GPIO_Pin_2   /* PC.07 */ 

  #define GPIO_KEY1_PORTSOURCE                GPIO_PortSourceGPIOC
  #define GPIO_KEY1_PINSOURCE                 GPIO_PinSource5
  #define GPIO_KEY1_EXTI_Line                 EXTI_Line5
	
	#define GPIO_KEY2_PORTSOURCE                GPIO_PortSourceGPIOC
  #define GPIO_KEY2_PINSOURCE                 GPIO_PinSource1
  #define GPIO_KEY2_EXTI_Line                 EXTI_Line1

  #define GPIO_TAMPER_PORTSOURCE              GPIO_PortSourceGPIOA
  #define GPIO_TAMPER_PINSOURCE               GPIO_PinSource0
  #define GPIO_TAMPER_EXTI_Line               EXTI_Line0

  #define ADC_AIN_CHANNEL                       ADC_Channel_1
#endif
  //使用如下定义 20180118 jade add
  #define USB_DISCONNECT                      GPIOB  
  #define USB_DISCONNECT_PIN                  GPIO_Pin_6
  #define RCC_AHBPeriph_GPIO_DISCONNECT      RCC_AHBPeriph_GPIOB
  #define RCC_AHBPeriph_GPIO_KEY             RCC_AHBPeriph_GPIOD
  
  #define GPIO_Pin_KEY                        GPIO_Pin_6   /* PG.08 */
  #define GPIO_Pin_UP                         GPIO_Pin_6  /* PG.15 */
  #define GPIO_Pin_DOWN                       GPIO_Pin_6   /* PD.03 */
  #define GPIO_Pin_LEFT                       GPIO_Pin_6  /* PG.14 */
  #define GPIO_Pin_RIGHT                      GPIO_Pin_6  /* PG.13 */    
  
  #define RCC_AHBPeriph_GPIO_JOY_SET1        RCC_AHBPeriph_GPIOB
  #define RCC_AHBPeriph_GPIO_JOY_SET2        RCC_AHBPeriph_GPIOB

  #define GPIO_RIGHT                          GPIOB
  #define GPIO_LEFT                           GPIOB
  #define GPIO_DOWN                           GPIOB
  #define GPIO_UP                             GPIOB
  #define GPIO_KEY                            GPIOB

                                                
  #define RCC_AHBPeriph_ALLGPIO             (RCC_AHBPeriph_GPIOA \
                                              | RCC_AHBPeriph_GPIOB \
                                              | RCC_AHBPeriph_GPIOC \
                                              | RCC_AHBPeriph_GPIOD )

  #define GPIO_KEY_PORTSOURCE                 GPIO_PortSourceGPIOD
  #define GPIO_KEY_PINSOURCE                  GPIO_PinSource6
  #define GPIO_KEY_EXTI_Line                  EXTI_Line6

  #define EXTI_KEY_IRQChannel                 EXTI4_15_IRQn



/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */

#endif /* __PLATFORM_CONFIG_H */

/******************* (C) COPYRIGHT 2009 MM32 *****END OF FILE****/

