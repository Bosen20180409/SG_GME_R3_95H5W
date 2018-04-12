/*******************************�ļ���Ϣ***************************************
 **  �� �� ��:    ParseSrcData.h
 **  ��    ����   V1.0
 **  ��    �ܣ�   
 **  ��    ����
 **  ��    �ߣ�   ����
 **  ��	   �ڣ
 **----------------------------��ʷ�汾��Ϣ------------------------------------
 **  �� �� �ˣ�
 **  ��    ���� 
 **  ��  ���ڣ�
 **  ��  ������
 ******************************************************************************/
#ifndef __ParseSrcData_H__
#define __ParseSrcData_H__

#include "config.h"


#define Ps3DataBufferSize 4

typedef struct
{	
	const char* Name;
	u8 Data[Ps3DataBufferSize];
}stPs3ButtonInfo;

extern stPs3ButtonInfo Ps3ButtonTab[];
void StartPs3ButtonData (void);
void ResetPs3ButtonDataP1 (void);
void ParseSrcData(u32 SrcDataTemp,u8 DesData[]);
void Ps3ParseSrcData(u8* SrcBuf);
#endif






























































