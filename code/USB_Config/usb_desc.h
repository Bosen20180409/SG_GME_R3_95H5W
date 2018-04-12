/******************** (C) COPYRIGHT 2009 STMicroelectronics ********************
* File Name          : usb_desc.h
* Author             : MCD Application Team
* Version            : V3.0.1
* Date               : 04/27/2009
* Description        : Descriptor Header for Joystick Mouse Demo
********************************************************************************
* THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
* WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE TIME.
* AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY DIRECT,
* INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING FROM THE
* CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE CODING
* INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
*******************************************************************************/

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __USB_DESC_H
#define __USB_DESC_H

#include "MM32L073PF.h"

/* Includes ------------------------------------------------------------------*/
/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported define -----------------------------------------------------------*/
#define USB_DEVICE_DESCRIPTOR_TYPE              0x01
#define USB_CONFIGURATION_DESCRIPTOR_TYPE       0x02
#define USB_STRING_DESCRIPTOR_TYPE              0x03
#define USB_INTERFACE_DESCRIPTOR_TYPE           0x04
#define USB_ENDPOINT_DESCRIPTOR_TYPE            0x05

//20171030�_jade add start
#define USB_DEVICE_DESCRIPTOR_TYPE_PC              0x01//�豸����������
#define USB_CONFIGURATION_DESCRIPTOR_TYPE_PC       0x02//��������������
#define USB_STRING_DESCRIPTOR_TYPE_PC              0x03//�ַ�������������
#define USB_INTERFACE_DESCRIPTOR_TYPE_PC           0x04//�ӿ�����������
#define USB_ENDPOINT_DESCRIPTOR_TYPE_PC            0x05//�˵�����������

#define HID_DESCRIPTOR_TYPE_PC                    0x21//HID����������
#define KEYBOARD_SIZ_HID_DESC_PC                  0x09//HID�������ĳ���
#define KEYBOARD_OFF_HID_DESC_PC                  0x12//HID���������������������������е�ƫ��

#define KEYBOARD_SIZ_DEVICE_DESC_PC               18//�豸�������ĳ���
#define KEYBOARD_SIZ_CONFIG_DESC_PC               34//0x30//34//�����������ĳ���
#define KEYBOARD_SIZ_REPORT_DESC_PC               112//0x70//(0x89-6)//74//0x89//61//�����������ĵĳ���
#define KEYBOARD_SIZ_STRING_LANGID_PC             4//����ID�ַ����������ĳ���
#define KEYBOARD_SIZ_STRING_VENDOR_PC             30//�����ַ����������ĳ���
#define KEYBOARD_SIZ_STRING_PRODUCT_PC            30//��Ʒ�ַ����������ĳ���
#define KEYBOARD_SIZ_STRING_SERIAL_PC             14//���к��ַ����������ĳ���

#define STANDARD_ENDPOINT_DESC_SIZE_PC             0x09

//20171030�_jade add end

#define HID_DESCRIPTOR_TYPE                     0x21
#define JOYSTICK_SIZ_HID_DESC                   0x09
#define JOYSTICK_OFF_HID_DESC                   0x12

#define JOYSTICK_SIZ_DEVICE_DESC                18
//#define JOYSTICK_SIZ_CONFIG_DESC                34
//#define JOYSTICK_SIZ_REPORT_DESC                74
#define JOYSTICK_SIZ_CONFIG_DESC                0x29
#define JOYSTICK_SIZ_REPORT_DESC                112  //0x65,20171030_jade_m

#define JOYSTICK_SIZ_STRING_LANGID              4
#define JOYSTICK_SIZ_STRING_VENDOR              38
#define JOYSTICK_SIZ_STRING_PRODUCT             30
#define JOYSTICK_SIZ_STRING_SERIAL              26

#define STANDARD_ENDPOINT_DESC_SIZE             0x09

/* Exported functions ------------------------------------------------------- */
extern const uint8_t Joystick_DeviceDescriptor[JOYSTICK_SIZ_DEVICE_DESC];
extern const uint8_t Joystick_ConfigDescriptor[JOYSTICK_SIZ_CONFIG_DESC];
extern const uint8_t Joystick_ReportDescriptor[JOYSTICK_SIZ_REPORT_DESC];
extern const uint8_t Joystick_StringLangID[JOYSTICK_SIZ_STRING_LANGID];
extern const uint8_t Joystick_StringVendor[JOYSTICK_SIZ_STRING_VENDOR];
extern const uint8_t Joystick_StringProduct[JOYSTICK_SIZ_STRING_PRODUCT];
extern uint8_t Joystick_StringSerial[JOYSTICK_SIZ_STRING_SERIAL];

#endif /* __USB_DESC_H */

/******************* (C) COPYRIGHT 2009 STMicroelectronics *****END OF FILE****/
