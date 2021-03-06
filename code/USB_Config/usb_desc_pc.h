/**
  ******************************************************************************
  * @file    usb_desc.h
  * @author  MCD Application Team
  * @version V4.0.0
  * @date    21-January-2013
  * @brief   Descriptor Header for Keyboard HID Demo
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT 2013 STMicroelectronics</center></h2>
  *
  * Licensed under MCD-ST Liberty SW License Agreement V2, (the "License");
  * You may not use this file except in compliance with the License.
  * You may obtain a copy of the License at:
  *
  *        http://www.st.com/software_license_agreement_liberty_v2
  *
  * Unless required by applicable law or agreed to in writing, software 
  * distributed under the License is distributed on an "AS IS" BASIS, 
  * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  * See the License for the specific language governing permissions and
  * limitations under the License.
  *
  ******************************************************************************
  */


/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __USB_DESC_PC_H
#define __USB_DESC_PC_H

/* Includes ------------------------------------------------------------------*/
/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported define -----------------------------------------------------------*/
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

/* Exported functions ------------------------------------------------------- */
extern const uint8_t Keyboard_DeviceDescriptor_pc[KEYBOARD_SIZ_DEVICE_DESC_PC];
extern const uint8_t Keyboard_ConfigDescriptor_pc[KEYBOARD_SIZ_CONFIG_DESC_PC];
extern const uint8_t Keyboard_ReportDescriptor_pc[KEYBOARD_SIZ_REPORT_DESC_PC];
extern const uint8_t Keyboard_StringLangID_pc[KEYBOARD_SIZ_STRING_LANGID_PC];
extern const uint8_t Keyboard_StringVendor_pc[KEYBOARD_SIZ_STRING_VENDOR_PC];
extern const uint8_t Keyboard_StringProduct_pc[KEYBOARD_SIZ_STRING_PRODUCT_PC];
extern uint8_t Keyboard_StringSerial_pc[KEYBOARD_SIZ_STRING_SERIAL_PC];

#endif /* __USB_DESC_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
