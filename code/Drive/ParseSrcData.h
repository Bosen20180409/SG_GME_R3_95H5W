/*******************************ÎÄ¼þÐÅÏ¢***************************************
 **  ÎÄ ¼þ Ãû:    ParseSrcData.h
 **  °æ    ±¾£º   V1.0
 **  ¹¦    ÄÜ£º   
 **  ÓÃ    ·¨£º
 **  ×÷    Õß£º   ²ÝÌÁ
 **  ÈÕ	   ÆÚ£
 **----------------------------ÀúÊ·°æ±¾ÐÅÏ¢------------------------------------
 **  ÐÞ ¸Ä ÈË£º
 **  °æ    ±¾£º 
 **  ÈÕ  ¡¡ÆÚ£º
 **  Ãè  ¡¡Êö£º
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






























































