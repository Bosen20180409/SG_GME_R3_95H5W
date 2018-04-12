/*******************************文件信息***************************************
 **  文 件 名:    ParseSrcData.h
 **  版    本：   V1.0
 **  功    能：   
 **  用    法：
 **  作    者：   草塘
 **  日	   期�
 **----------------------------历史版本信息------------------------------------
 **  修 改 人：
 **  版    本： 
 **  日  　期：
 **  描  　述：
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






























































