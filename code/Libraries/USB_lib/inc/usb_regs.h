/******************** (C) COPYRIGHT 2009 MM32 ********************
* File Name          : usb_regs.h
* Author             : MCD Application Team
* Version            : V3.0.1
* Date               : 04/27/2009
* Description        : Interface prototype functions to USB cell registers
********************************************************************************
* THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
* WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE TIME.
* AS A RESULT, MM32 SHALL NOT BE HELD LIABLE FOR ANY DIRECT,
* INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING FROM THE
* CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE CODING
* INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
*******************************************************************************/

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __USB_REGS_H
#define __USB_REGS_H


/* Endpoint Addresses (w/direction) */
#define EP0_OUT     ((uint8_t)0x00)  
#define EP0_IN      ((uint8_t)0x80) 
#define EP1_OUT     ((uint8_t)0x01)  
#define EP1_IN      ((uint8_t)0x81)  
#define EP2_OUT     ((uint8_t)0x02)  
#define EP2_IN      ((uint8_t)0x82)  
#define EP3_OUT     ((uint8_t)0x03)  
#define EP3_IN      ((uint8_t)0x83) 
#define EP4_OUT     ((uint8_t)0x04)  
#define EP4_IN      ((uint8_t)0x84)
#define EP5_OUT     ((uint8_t)0x05)  
#define EP5_IN      ((uint8_t)0x85)
#define EP6_OUT     ((uint8_t)0x06)  
#define EP6_IN      ((uint8_t)0x86)
#define EP7_OUT     ((uint8_t)0x07)  
#define EP7_IN      ((uint8_t)0x87)



/* endpoints enumeration */
#define ENDP0   ((uint8_t)0)
#define ENDP1   ((uint8_t)1)
#define ENDP2   ((uint8_t)2)
#define ENDP3   ((uint8_t)3)
#define ENDP4   ((uint8_t)4)

#define ENDP5   ((uint8_t)5)
#define ENDP6   ((uint8_t)6)
#define ENDP7   ((uint8_t)7)
/* Exported macro ------------------------------------------------------------*/


/* SetUSB_TOP */
#define _SetUSB_TOP(wRegValue)  	    (USB->TOP  |= (uint16_t)wRegValue)
/* ClrUSB_TOP */
#define _ClrUSB_TOP(wRegValue)  	    (USB->TOP  &= (uint16_t)~wRegValue)

/* SetUSB_ISTR */
#define _ClrUSB_INT_STA(wRegValue)  	(USB->INT_STATE  = (uint16_t)wRegValue)
/* GetUSB_ISTR */
#define _GetUSB_INT_STA()  	            (USB->INT_STATE)

/* ClrEP_INT_STA ,write 1 clear 0.*/
#define _ClrEP_INT_STA(wRegValue)  	    (USB->EP_INT_STATE  = (uint16_t)wRegValue)
/* GetEP_INT_STA */
#define _GetEP_INT_STA()  	            (USB->EP_INT_STATE)

/* ClrEP0_INT_STA */
#define _ClrEP0_INT_STA(wRegValue)  	(USB->EP0_INT_STATE  = (uint16_t)wRegValue)
/* GetEP0_INT_STA */
#define _GetEP0_INT_STA()  	            (USB->EP0_INT_STATE)

/* SetUSB_INT_EN */
#define _SetUSB_INT_EN(wRegValue)  	    (USB->INT_EN  |= (uint16_t)wRegValue)
/* ClrUSB_INT_EN */
#define _ClrUSB_INT_EN(wRegValue)  	    (USB->INT_EN  &= (uint16_t)~wRegValue)

/* SetUSB_INT_EN */
#define _SetEP_INT_EN(wRegValue)  	    (USB->EP_INT_EN  |= (uint16_t)wRegValue)
/* SetUSB_INT_EN */
#define _ClrEP_INT_EN(wRegValue)  	    (USB->EP_INT_EN  &= (uint16_t)~wRegValue)

/* SetEP0_INT_EN */
#define _SetEP0_INT_EN(wRegValue)  	    (USB->EP0_INT_EN |= (uint16_t)wRegValue)
/* SetEP0_INT_EN */
#define _ClrEP0_INT_EN(wRegValue)  	    (USB->EP0_INT_EN &= (uint16_t)~wRegValue)

/* ClrEP1_INT_STA */
#define _ClrEP1_INT_STA(wRegValue)  	(USB->EP1_INT_STATE = (uint16_t)wRegValue)
/* GetEP1_INT_EN */
#define _GetEP1_INT_STA()  	            (USB->EP1_INT_STATE)

/* ClrEP2_INT_STA */
#define _ClrEP2_INT_STA(wRegValue)  	(USB->EP2_INT_STATE = (uint16_t)wRegValue)
/* GetEP2_INT_STA */
#define _GetEP2_INT_STA()  	            (USB->EP2_INT_STATE)

/* ClrEP3_INT_STA */
#define _ClrEP3_INT_STA(wRegValue)  	(USB->EP3_INT_STATE = (uint16_t)wRegValue)
/* GetEP3_INT_STA */
#define _GetEP3_INT_STA()  	            (USB->EP3_INT_STATE)

/* ClrEP4_INT_STA */
#define _ClrEP4_INT_STA(wRegValue)  	(USB->EP4_INT_STATE = (uint16_t)wRegValue)
/* GetEP4_INT_STA */
#define _GetEP4_INT_STA()  	            (USB->EP4_INT_STATE)

/* ClrEPn_INT_STA ,n = 1,2,3,4*/
#define _ClrEPn_INT_STA(wRegValue,n)  	(*(u32*)((u32)(&(USB->EP1_INT_STATE))+(n-1)*4) = (uint16_t)wRegValue)
/* GetEPn_INT_EN */
#define _GetEPn_INT_STA(n)  	        (*(u32*)((u32)(&(USB->EP1_INT_STATE))+(n-1)*4))

/* SetEP1_INT_EN */
#define _SetEP1_INT_EN(wRegValue)  	    (USB->EP1_INT_EN |= (uint16_t)wRegValue)
/* SetEP1_INT_EN */
#define _ClrEP1_INT_EN(wRegValue)  	    (USB->EP1_INT_EN &= (uint16_t)~wRegValue)

/* SetEP2_INT_EN */
#define _SetEP2_INT_EN(wRegValue)  	    (USB->EP2_INT_EN |= (uint16_t)wRegValue)
/* SetEP2_INT_EN */
#define _ClrEP2_INT_EN(wRegValue)  	    (USB->EP2_INT_EN &= (uint16_t)~wRegValue)

/* SetEP3_INT_EN */
#define _SetEP3_INT_EN(wRegValue)  	    (USB->EP3_INT_EN |= (uint16_t)wRegValue)
/* SetEP3_INT_EN */
#define _ClrEP3_INT_EN(wRegValue)  	    (USB->EP3_INT_EN &= (uint16_t)~wRegValue)

/* SetEP4_INT_EN */
#define _SetEP4_INT_EN(wRegValue)  	    (USB->EP4_INT_EN |= (uint16_t)wRegValue)
/* SetEP4_INT_EN */
#define _ClrEP4_INT_EN(wRegValue)  	    (USB->EP4_INT_EN &= (uint16_t)~wRegValue)

/* GetEP4_INT_EN */
#define _GetEPn_INT_EN(n)               (*(u32*)((u32)(&(USB->EP1_INT_EN))+(n-1)*4))
/* GetEP4_INT_EN */
#define _SetEPn_INT_EN(wRegValue,n)     (*(u32*)((u32)(&(USB->EP1_INT_EN))+(n-1)*4) = (uint16_t)wRegValue)

/* Set_EP_EN */
#define _SetUSB_ADDR(wRegValue)	        (USB->ADDR = (uint16_t)wRegValue)

/* Set_EP_EN */
#define _SetEP_EN(wRegValue)		    (USB->EP_EN |= (uint16_t)wRegValue)
/* Clr_EP_EN */
#define _ClrEP_EN(wRegValue)		    (USB->EP_EN &= (uint16_t)~wRegValue)

/* SetUSB_AVIL0 */
#define _SetUSB_AVIL0(wRegValue)  	    (USB->EP0_AVIL  = (uint16_t)wRegValue)

/* SetUSB_AVIL1 */
#define _SetUSB_AVIL1(wRegValue)  	    (USB->EP1_AVIL  = (uint16_t)wRegValue)

/* SetUSB_AVIL2 */
#define _SetUSB_AVIL2(wRegValue)  	    (USB->EP2_AVIL  = (uint16_t)wRegValue)

/* SetUSB_AVIL3 */
#define _SetUSB_AVIL3(wRegValue)  	    (USB->EP3_AVIL  = (uint16_t)wRegValue)

/* SetUSB_AVIL4 */
#define _SetUSB_AVIL4(wRegValue)  	    (USB->EP4_AVIL  = (uint16_t)wRegValue)

/* GetUSB_FIFOn NUM */
#define _GetUSB_AVILn(n)  	            (*(u32*)((u32)(&(USB->EP0_AVIL))+(n)*4))

/* SetUSB_CTRL0 */
#define _SetUSB_CTRL0(wRegValue)  	    (USB->EP0_CTRL  = (uint16_t)wRegValue)
/* GetUSB_CTRL0 */
#define _GetUSB_CTRL0()  	            (USB->EP0_CTRL)

/* SetUSB_CTRL1 */
#define _SetUSB_CTRL1(wRegValue)  	    (USB->EP1_CTRL  = (uint16_t)wRegValue)
/* GetUSB_CTRL1 */
#define _GetUSB_CTRL1()  	            (USB->EP1_CTRL)

/* SetUSB_CTRL2 */
#define _SetUSB_CTRL2(wRegValue)  	    (USB->EP2_CTRL  = (uint16_t)wRegValue)
/* GetUSB_CTRL2 */
#define _GetUSB_CTRL2()  	            (USB->EP2_CTRL)

/* SetUSB_CTRL3 */
#define _SetUSB_CTRL3(wRegValue)  	    (USB->EP3_CTRL  = (uint16_t)wRegValue)
/* GetUSB_CTRL3 */
#define _GetUSB_CTRL3()  	            (USB->EP3_CTRL)

/* SetUSB_CTRL4 */
#define _SetUSB_CTRL4(wRegValue)  	    (USB->EP4_CTRL  = (uint16_t)wRegValue)
/* GetUSB_CTRL4 */
#define _GetUSB_CTRL4()  	            (USB->EP4_CTRL)

/* SetUSB_FIFO0 */
#define _SetUSB_FIFO0(wRegValue)  	    (USB->EP0_FIFO  = (uint32_t)wRegValue&0xff)
/* GetUSB_FIFO0 */
#define _GetUSB_FIFO0()  	            (USB->EP0_FIFO )

/* SetUSB_FIFO1 */
#define _SetUSB_FIFO1(wRegValue)  	    (USB->EP1_FIFO  = (uint16_t)wRegValue)
/* GetUSB_FIFO1 */
#define _GetUSB_FIFO1()  	            (USB->EP1_FIFO )

/* SetUSB_FIFO2 */
#define _SetUSB_FIFO2(wRegValue)  	    (USB->EP2_FIFO  = (uint16_t)wRegValue)
/* GetUSB_FIFO0 */
#define _GetUSB_FIFO2()  	            (USB->EP2_FIFO )

/* SetUSB_FIFO03 */
#define _SetUSB_FIFO3(wRegValue)  	    (USB->EP3_FIFO  = (uint16_t)wRegValue)
/* GetUSB_FIFO3 */
#define _GetUSB_FIFO3()  	            (USB->EP3_FIFO )

/* SetUSB_FIFO4 */
#define _SetUSB_FIFO4(wRegValue)  	    (USB->EP4_FIFO  = (uint16_t)wRegValue)
/* GetUSB_FIFO0 */
#define _GetUSB_FIFO4()  	            (USB->EP4_FIFO )

/* SetUSB_FIFO4 */
#define _SetUSB_FIFOn(wRegValue,n)  	(*(u32*)((u32)(&(USB->EP1_FIFO))+(n-1)*4) = (uint16_t)wRegValue)
/* GetUSB_FIFO0 */
#define _GetUSB_FIFOn(n)  	            (*(u32*)((u32)(&(USB->EP1_FIFO))+(n-1)*4))

/* SetUSB_HALT */
#define _SetUSB_HALT(wRegValue)  	    (USB->EP_HALT  |= (uint16_t)wRegValue)
/* ClrUSB_HALT */
#define _ClrUSB_HALT(wRegValue)  	    (USB->EP_HALT  &= (uint16_t)~wRegValue)
/* GetUSB_HALT */
#define _GetUSB_HALT()  	            (USB->EP_HALT)

/* SetUSB_POWER */
#define _SetUSB_POWER(wRegValue)  	    (USB->POWER  |= (uint16_t)wRegValue)
/* ClrUSB_TOP */
#define _ClrUSB_POWER(wRegValue)  	    (USB->POWER  &= (uint16_t)~wRegValue)


/***********************************************/ //wenyang.du
 
/* PAKET_SIZE0 */
#define _Set_PAKET_SIZE0(wRegValue)  	(USB->PAKET_SIZE0 = (uint8_t)wRegValue) 
#define _Set_PAKET_SIZE1(wRegValue)  	(USB->PAKET_SIZE1 = (uint8_t)wRegValue) 
 
/* External variables --------------------------------------------------------*/


/* Exported functions ------------------------------------------------------- */


#endif /* __USB_REGS_H */

/******************* (C) COPYRIGHT 2009 MM32 *****END OF FILE****/
