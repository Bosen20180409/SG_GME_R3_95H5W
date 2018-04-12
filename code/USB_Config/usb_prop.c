/******************** (C) COPYRIGHT 2009 STMicroelectronics ********************
* File Name          : usb_prop.c
* Author             : MCD Application Team
* Version            : V3.0.1
* Date               : 04/27/2009
* Description        : All processings related to Joystick Mouse Demo
********************************************************************************
* THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
* WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE TIME.
* AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY DIRECT,
* INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING FROM THE
* CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE CODING
* INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
*******************************************************************************/

/* Includes ------------------------------------------------------------------*/
#include "hw_config.h"
#include "usb_lib.h"
#include "usb_conf.h"
#include "usb_prop.h"

//#include "usb_desc.h"

#include "usb_desc_pc.h"
#include "usb_desc_ps3.h"
#include "usb_desc_ps4.h"

#include "usb_pwr.h"

#include "stdio.h"


/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
uint32_t ProtocolValue;
__IO uint8_t EXTI_Enable;
__IO uint8_t Request = 0;
uint8_t Report_Buf[2];   
/* -------------------------------------------------------------------------- */
/*  Structures initializations */
/* -------------------------------------------------------------------------- */

DEVICE Device_Table =
  {
    EP_NUM,
    1
  };

DEVICE_PROP Device_Property =
  {
	Keyboard_init,
	Keyboard_Reset,
	Keyboard_Status_In,
	Keyboard_Status_Out,
	Keyboard_Data_Setup,
	Keyboard_NoData_Setup,
	Keyboard_Get_Interface_Setting,
	Keyboard_GetDeviceDescriptor,
	Keyboard_GetConfigDescriptor,
	Keyboard_GetStringDescriptor,
    0,
    0x40 /*MAX PACKET SIZE*/
  };
USER_STANDARD_REQUESTS User_Standard_Requests =
  {
	Keyboard_GetConfiguration,
	Keyboard_SetConfiguration,
	Keyboard_GetInterface,
	Keyboard_SetInterface,
	Keyboard_GetStatus,
	Keyboard_ClearFeature,
	Keyboard_SetEndPointFeature,
	Keyboard_SetDeviceFeature,
	Keyboard_SetDeviceAddress
  };

ONE_DESCRIPTOR Device_Descriptor_pc =
  {
	(uint8_t*)Keyboard_DeviceDescriptor_pc,
	KEYBOARD_SIZ_DEVICE_DESC_PC
  };

ONE_DESCRIPTOR Config_Descriptor_pc =
  {
	(uint8_t*)Keyboard_ConfigDescriptor_pc,
	KEYBOARD_SIZ_CONFIG_DESC_PC
  };

ONE_DESCRIPTOR Keyboard_Report_Descriptor_pc =
{
	(uint8_t *)Keyboard_ReportDescriptor_pc,
	KEYBOARD_SIZ_REPORT_DESC_PC
  };

ONE_DESCRIPTOR Keyboard_Hid_Descriptor_pc =
{
	(uint8_t*)Keyboard_ConfigDescriptor_pc + KEYBOARD_OFF_HID_DESC_PC,
	KEYBOARD_SIZ_HID_DESC_PC
  };

ONE_DESCRIPTOR String_Descriptor_pc[4] =
  {
	{(uint8_t*)Keyboard_StringLangID_pc, KEYBOARD_SIZ_STRING_LANGID_PC},
	{(uint8_t*)Keyboard_StringVendor_pc, KEYBOARD_SIZ_STRING_VENDOR_PC},
	{(uint8_t*)Keyboard_StringProduct_pc, KEYBOARD_SIZ_STRING_PRODUCT_PC},
	{(uint8_t*)Keyboard_StringSerial_pc, KEYBOARD_SIZ_STRING_SERIAL_PC}
  };
//===============================================================
//===============================================================
ONE_DESCRIPTOR Device_Descriptor_ps3 =
{
	(uint8_t*)Keyboard_DeviceDescriptor_ps3,
	KEYBOARD_SIZ_DEVICE_DESC_PS3
};

ONE_DESCRIPTOR Config_Descriptor_ps3 =
{
	(uint8_t*)Keyboard_ConfigDescriptor_ps3,
	KEYBOARD_SIZ_CONFIG_DESC_PS3
};

ONE_DESCRIPTOR Keyboard_Report_Descriptor_ps3 =
{
	(uint8_t *)Keyboard_ReportDescriptor_ps3,
	KEYBOARD_SIZ_REPORT_DESC_PS3
};

ONE_DESCRIPTOR Keyboard_Hid_Descriptor_ps3 =
{
	(uint8_t*)Keyboard_ConfigDescriptor_ps3 + KEYBOARD_OFF_HID_DESC_PS3,
	KEYBOARD_SIZ_HID_DESC_PS3
};

ONE_DESCRIPTOR String_Descriptor_ps3[4] =
{
	{(uint8_t*)Keyboard_StringLangID_ps3, KEYBOARD_SIZ_STRING_LANGID_PS3},
	{(uint8_t*)Keyboard_StringVendor_ps3, KEYBOARD_SIZ_STRING_VENDOR_PS3},
	{(uint8_t*)Keyboard_StringProduct_ps3, KEYBOARD_SIZ_STRING_PRODUCT_PS3},
	{(uint8_t*)Keyboard_StringSerial_ps3, KEYBOARD_SIZ_STRING_SERIAL_PS3}
};
//===============================================================
//===============================================================
ONE_DESCRIPTOR Device_Descriptor_ps4 =
{
	(uint8_t*)Keyboard_DeviceDescriptor_ps4,
	KEYBOARD_SIZ_DEVICE_DESC_PS4
};

ONE_DESCRIPTOR Config_Descriptor_ps4 =
{
	(uint8_t*)Keyboard_ConfigDescriptor_ps4,
	KEYBOARD_SIZ_CONFIG_DESC_PS4
};

ONE_DESCRIPTOR Keyboard_Report_Descriptor_ps4 =
{
	(uint8_t *)Keyboard_ReportDescriptor_ps4,
	KEYBOARD_SIZ_REPORT_DESC_PS4
};

ONE_DESCRIPTOR Keyboard_Hid_Descriptor_ps4 =
{
	(uint8_t*)Keyboard_ConfigDescriptor_ps4 + KEYBOARD_OFF_HID_DESC_PS4,
	KEYBOARD_SIZ_HID_DESC_PS4
};

ONE_DESCRIPTOR String_Descriptor_ps4[4] =
{
	{(uint8_t*)Keyboard_StringLangID_ps4, KEYBOARD_SIZ_STRING_LANGID_PS4},
	{(uint8_t*)Keyboard_StringVendor_ps4, KEYBOARD_SIZ_STRING_VENDOR_PS4},
	{(uint8_t*)Keyboard_StringProduct_ps4, KEYBOARD_SIZ_STRING_PRODUCT_PS4},
	{(uint8_t*)Keyboard_StringSerial_ps4, KEYBOARD_SIZ_STRING_SERIAL_PS4}
};
//===============================================================
//===============================================================
/* Extern variables ----------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/*Keyboard_SetReport_Feature function prototypes*/
uint8_t *Keyboard_SetReport_Feature(uint16_t Length);
/* Extern function prototypes ------------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/*******************************************************************************
* Function Name  : Keyboard_init.
* Description    : Custom HID init routine.
* Input          : None.
* Output         : None.
* Return         : None.
*******************************************************************************/
void Keyboard_init(void)
{

  /* Update the serial number string descriptor with the data from the unique
  ID*/
  Get_SerialNum();

  pInformation->Current_Configuration = 0;
  /* Connect the device */
  PowerOn();
  /* USB interrupts initialization */

  bDeviceState = UNCONNECTED;
}

/*******************************************************************************
* Function Name  : Joystick_Reset.
* Description    : Joystick Mouse reset routine.
* Input          : None.
* Output         : None.
* Return         : None.
*******************************************************************************/
void Keyboard_Reset(void)
{
    /* Set Joystick_DEVICE as not configured */
    pInformation->Current_Configuration = 0;
    pInformation->Current_Interface = 0;/*the default Interface*/

    /* Current Feature initialization */
	switch(DeviceType)
	{
		case DEVICE_PC:
			pInformation->Current_Feature = Keyboard_ConfigDescriptor_pc[7];//当前的属性，bmAttributes:设备的一些特性，0xc0表示自供电，不支持远程唤醒
			break;
		case DEVICE_PS3:
			pInformation->Current_Feature = Keyboard_ConfigDescriptor_ps3[7];//当前的属性，bmAttributes:设备的一些特性，0xc0表示自供电，不支持远程唤醒
			break;
		case DEVICE_PS4:
			pInformation->Current_Feature = Keyboard_ConfigDescriptor_ps4[7];//当前的属性，bmAttributes:设备的一些特性，0xc0表示自供电，不支持远程唤醒
			break;
		default:
			break;
	}	
    _ClrEP_EN((1<<ENDP0)|(1<<ENDP1)|(1<<ENDP2)|(1<<ENDP3)|(1<<ENDP4));

    _SetEP0_INT_EN( EPn_INT_EN_SETUPIE|EPn_INT_EN_INNACKIE|\
              EPn_INT_EN_OUTACKIE|EPn_INT_EN_OUTACKIE);//EPn_INT_EN_INACKIE|
    _ClrEP0_INT_STA(EPn_INT_STATE_SETUP|EPn_INT_STATE_INNACK|\
              EPn_INT_EN_INACKIE|EPn_INT_STATE_OUTACK);


    _SetEP1_INT_EN( EPn_INT_EN_INNACKIE );//| EPn_INT_EN_INACKIE
    _ClrEP1_INT_STA(EPn_INT_STATE_INNACK| EPn_INT_STATE_INACK);
    
    _SetEP_EN(1<<ENDP0);
    _SetEP_INT_EN((1<<ENDP0)|(1<<ENDP1));
    /* Set this device to response on default address */    
    SetDeviceAddress(0);

    _SetUSB_TOP(USB_TOP_RESET);
    _ClrUSB_TOP(USB_TOP_RESET); 

    bDeviceState = ATTACHED;
}
/*******************************************************************************
* Function Name  : Keyboard_SetConfiguration.
* Description    : Update the device state to configured and command the ADC 
*                  conversion.
* Input          : None.
* Output         : None.
* Return         : None.
*******************************************************************************/
void Keyboard_SetConfiguration(void)
{
  DEVICE_INFO *pInfo = &Device_Info;

  if (pInfo->Current_Configuration != 0)
  {
    /* Device configured */
    bDeviceState = CONFIGURED;
  }
}
/*******************************************************************************
* Function Name  : Keyboard_SetConfiguration.
* Description    : Update the device state to addressed.
* Input          : None.
* Output         : None.
* Return         : None.
*******************************************************************************/
void Keyboard_SetDeviceAddress (void)
{
  bDeviceState = ADDRESSED;
}
/*******************************************************************************
* Function Name  : Keyboard_Status_In.
* Description    : Joystick status IN routine.
* Input          : None.
* Output         : None.
* Return         : None.
*******************************************************************************/
void Keyboard_Status_In(void)
{  
  BitAction Led_State;
  
  if (Report_Buf[1] == 0)
  {
    Led_State = Bit_RESET;
  }
  else 
  {
    Led_State = Bit_SET;
  }
  
  switch (Report_Buf[0])  
  {
    /*Change LED's status according to the host report*/
    
  case 1: /* Led 1 */ 
    if (Led_State != Bit_RESET)
    {
      printf("[%s:%d]Led1_On\r\n",__FUNCTION__,__LINE__);
    }
    else
    {
      printf("[%s:%d]Led1_Off\r\n",__FUNCTION__,__LINE__);
    }
    break;
  case 2:   /* Led 2 */    
    if (Led_State != Bit_RESET)
    {
      printf("[%s:%d]Led2_On\r\n",__FUNCTION__,__LINE__);
    }
    else
    {
      printf("[%s:%d]Led2_Off\r\n",__FUNCTION__,__LINE__);
    }
    break;
  case 3:/* Led 3 */    
    if (Led_State != Bit_RESET)
    {
      printf("[%s:%d]Led3_On\r\n",__FUNCTION__,__LINE__);
    }
    else
    {
      printf("[%s:%d]Led3_Off\r\n",__FUNCTION__,__LINE__);
    }
    break;
  case 4:/* Led 4 */    
    if (Led_State != Bit_RESET)
    {
      printf("[%s:%d]Led4_On\r\n",__FUNCTION__,__LINE__);
    }
    else
    {
      printf("[%s:%d]Led4_Off\r\n",__FUNCTION__,__LINE__);
    }
    break;
  default:
		printf("[%s:%d]Led1_Off\r\n",__FUNCTION__,__LINE__);
		printf("[%s:%d]Led2_Off\r\n",__FUNCTION__,__LINE__);
		printf("[%s:%d]Led3_Off\r\n",__FUNCTION__,__LINE__);
		printf("[%s:%d]Led4_Off\r\n",__FUNCTION__,__LINE__);
    break;
  }
}

/*******************************************************************************
* Function Name  : Keyboard_Status_Out
* Description    : Joystick status OUT routine.
* Input          : None.
* Output         : None.
* Return         : None.
*******************************************************************************/
void Keyboard_Status_Out (void)
{
}

/*******************************************************************************
* Function Name  : Keyboard_Data_Setup
* Description    : Handle the data class specific requests.
* Input          : Request Nb.
* Output         : None.
* Return         : USB_UNSUPPORT or USB_SUCCESS.
*******************************************************************************/
RESULT Keyboard_Data_Setup(uint8_t RequestNo)
{
  uint8_t *(*CopyRoutine)(uint16_t);

  CopyRoutine = NULL;
  if ((RequestNo == GET_DESCRIPTOR)
      && (Type_Recipient == (STANDARD_REQUEST | INTERFACE_RECIPIENT))
      && (pInformation->USBwIndex0 == 0))
  {

    if (pInformation->USBwValue1 == REPORT_DESCRIPTOR)
    {
      CopyRoutine = Keyboard_GetReportDescriptor;
    }
    else if (pInformation->USBwValue1 == HID_DESCRIPTOR_TYPE_PC)
    {
      CopyRoutine = Keyboard_GetHIDDescriptor;
    }

  } /* End of GET_DESCRIPTOR */

  /*** GET_PROTOCOL ***/
  else if ((Type_Recipient == (CLASS_REQUEST | INTERFACE_RECIPIENT))
           && RequestNo == GET_PROTOCOL)
  {
    CopyRoutine = Keyboard_GetProtocolValue;
  }


  if (CopyRoutine == NULL)
  {
    return USB_UNSUPPORT;
  }

  pInformation->Ctrl_Info.CopyData = CopyRoutine;
  pInformation->Ctrl_Info.Usb_wOffset = 0;
  (*CopyRoutine)(0);
  return USB_SUCCESS;
}

/*******************************************************************************
* Function Name  : Keyboard_NoData_Setup
* Description    : handle the no data class specific requests
* Input          : Request Nb.
* Output         : None.
* Return         : USB_UNSUPPORT or USB_SUCCESS.
*******************************************************************************/
RESULT Keyboard_NoData_Setup(uint8_t RequestNo)
{
  if ((Type_Recipient == (CLASS_REQUEST | INTERFACE_RECIPIENT))
      && (RequestNo == SET_PROTOCOL))
  {
    return Keyboard_SetProtocol();
  }

  else
  {
    return USB_UNSUPPORT;
  }
}

/*******************************************************************************
* Function Name  : Keyboard_GetDeviceDescriptor.
* Description    : Gets the device descriptor.
* Input          : Length
* Output         : None.
* Return         : The address of the device descriptor.
*******************************************************************************/
uint8_t *Keyboard_GetDeviceDescriptor(uint16_t Length)
{
	switch(DeviceType)
	{
		case DEVICE_PC:
			//printf("[%s:%d]Length:%d\r\n",__FUNCTION__,__LINE__,Length);
			return Standard_GetDescriptorData(Length, &Device_Descriptor_pc);
		case DEVICE_PS3:
			//printf("[%s:%d]Length:%d\r\n",__FUNCTION__,__LINE__,Length);
			return Standard_GetDescriptorData(Length, &Device_Descriptor_ps3);
		case DEVICE_PS4:
			//printf("[%s:%d]Length:%d\r\n",__FUNCTION__,__LINE__,Length);
			return Standard_GetDescriptorData(Length, &Device_Descriptor_ps4);
		default:
			break;
	}
	return 0;	
}

/*******************************************************************************
* Function Name  : Keyboard_GetConfigDescriptor.
* Description    : Gets the configuration descriptor.
* Input          : Length
* Output         : None.
* Return         : The address of the configuration descriptor.
*******************************************************************************/
uint8_t *Keyboard_GetConfigDescriptor(uint16_t Length)
{
	switch(DeviceType)
	{
		case DEVICE_PC:
			//printf("[%s:%d]Length:%d\r\n",__FUNCTION__,__LINE__,Length);
			return Standard_GetDescriptorData(Length, &Config_Descriptor_pc);
		case DEVICE_PS3:
			//printf("[%s:%d]Length:%d\r\n",__FUNCTION__,__LINE__,Length);
			return Standard_GetDescriptorData(Length, &Config_Descriptor_ps3);
		case DEVICE_PS4:
			//printf("[%s:%d]Length:%d\r\n",__FUNCTION__,__LINE__,Length);
			return Standard_GetDescriptorData(Length, &Config_Descriptor_ps4);
		default:
			break;
	}	
	return 0;  
}

/*******************************************************************************
* Function Name  : Keyboard_GetStringDescriptor
* Description    : Gets the string descriptors according to the needed index
* Input          : Length
* Output         : None.
* Return         : The address of the string descriptors.
*******************************************************************************/
uint8_t *Keyboard_GetStringDescriptor(uint16_t Length)
{
  uint8_t wValue0 = pInformation->USBwValue0;
  if (wValue0 > 4)
  {
    return NULL;
  }
  else
  {
		switch(DeviceType)
		{
			case DEVICE_PC:
				//printf("[%s:%d]Length:%d\r\n",__FUNCTION__,__LINE__,Length);
				return Standard_GetDescriptorData(Length, &String_Descriptor_pc[wValue0]);
			case DEVICE_PS3:
				//printf("[%s:%d]Length:%d\r\n",__FUNCTION__,__LINE__,Length);
				return Standard_GetDescriptorData(Length, &String_Descriptor_ps3[wValue0]);
			case DEVICE_PS4:
				//printf("[%s:%d]Length:%d\r\n",__FUNCTION__,__LINE__,Length);
				return Standard_GetDescriptorData(Length, &String_Descriptor_ps4[wValue0]);
			default:
				break;
		}		
  }
	return 0;	
}

/*******************************************************************************
* Function Name  : Keyboard_GetReportDescriptor.
* Description    : Gets the HID report descriptor.
* Input          : Length
* Output         : None.
* Return         : The address of the configuration descriptor.
*******************************************************************************/
uint8_t *Keyboard_GetReportDescriptor(uint16_t Length)
{
	switch(DeviceType)
	{
		case DEVICE_PC:
			//printf("[%s:%d]Length:%d\r\n",__FUNCTION__,__LINE__,Length);
			return Standard_GetDescriptorData(Length, &Keyboard_Report_Descriptor_pc);
		case DEVICE_PS3:
			//printf("[%s:%d]Length:%d\r\n",__FUNCTION__,__LINE__,Length);
			return Standard_GetDescriptorData(Length, &Keyboard_Report_Descriptor_ps3);
		case DEVICE_PS4:
			//printf("[%s:%d]Length:%d\r\n",__FUNCTION__,__LINE__,Length);
			return Standard_GetDescriptorData(Length, &Keyboard_Report_Descriptor_ps4);
		default:
			break;
	}	
	return 0;  
}

/*******************************************************************************
* Function Name  : Keyboard_GetHIDDescriptor.
* Description    : Gets the HID descriptor.
* Input          : Length
* Output         : None.
* Return         : The address of the configuration descriptor.
*******************************************************************************/
uint8_t *Keyboard_GetHIDDescriptor(uint16_t Length)
{
	switch(DeviceType)
	{
		case DEVICE_PC:
			//printf("[%s:%d]Length:%d\r\n",__FUNCTION__,__LINE__,Length);
			return Standard_GetDescriptorData(Length, &Keyboard_Hid_Descriptor_pc);
		case DEVICE_PS3:
			//printf("[%s:%d]Length:%d\r\n",__FUNCTION__,__LINE__,Length);
			return Standard_GetDescriptorData(Length, &Keyboard_Hid_Descriptor_ps3);
		case DEVICE_PS4:
			//printf("[%s:%d]Length:%d\r\n",__FUNCTION__,__LINE__,Length);
			return Standard_GetDescriptorData(Length, &Keyboard_Hid_Descriptor_ps4);
		default:
			break;
	}
	return 0;
}

/*******************************************************************************
* Function Name  : Keyboard_Get_Interface_Setting.
* Description    : tests the interface and the alternate setting according to the
*                  supported one.
* Input          : - Interface : interface number.
*                  - AlternateSetting : Alternate Setting number.
* Output         : None.
* Return         : USB_SUCCESS or USB_UNSUPPORT.
*******************************************************************************/
RESULT Keyboard_Get_Interface_Setting(uint8_t Interface, uint8_t AlternateSetting)
{
  if (AlternateSetting > 0)
  {
    return USB_UNSUPPORT;
  }
  else if (Interface > 0)
  {
    return USB_UNSUPPORT;
  }
  return USB_SUCCESS;
}

/*******************************************************************************
* Function Name  : Keyboard_SetProtocol
* Description    : Joystick Set Protocol request routine.
* Input          : None.
* Output         : None.
* Return         : USB SUCCESS.
*******************************************************************************/
RESULT Keyboard_SetProtocol(void)
{
  uint8_t wValue0 = pInformation->USBwValue0;
  ProtocolValue = wValue0;
  return USB_SUCCESS;
}

/*******************************************************************************
* Function Name  : Keyboard_GetProtocolValue
* Description    : get the protocol value
* Input          : Length.
* Output         : None.
* Return         : address of the protcol value.
*******************************************************************************/
uint8_t *Keyboard_GetProtocolValue(uint16_t Length)
{
  if (Length == 0)
  {
    pInformation->Ctrl_Info.Usb_wLength = 1;
    return NULL;
  }
  else
  {
    return (uint8_t *)(&ProtocolValue);
  }
}

/******************* (C) COPYRIGHT 2009 STMicroelectronics *****END OF FILE****/
