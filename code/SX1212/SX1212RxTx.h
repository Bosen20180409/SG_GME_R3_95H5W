#ifndef __SX1212RXTX_H
#define __SX1212RXTX_H	

#include "config.h"   

extern u8 RFbuffer[];       // RF buffer
extern u8 RFbufferSize;          // RF buffer size
extern u8 EnableMaster;   // Master/Slave selection   //false
extern u8 SendNextPacket; // Indicates when to send the next frame

void OnMasterWireless(void);
void OnSlave(void);
void DataConversationUsb(u8* SrcBuf,u8* DesBuf);
#endif
