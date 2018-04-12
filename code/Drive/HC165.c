/*******************************文件信息***************************************
 **  文 件 名:    HC165.c
 **  版    本：   V1.0
 **  功    能：   74HC165驱动
 **  用    法：
 **  作    者：   草塘
 **  日	   期：
 **----------------------------历史版本信息------------------------------------
 **  修 改 人：
 **  版    本： 
 **  日  　期：
 **  描  　述：
 ******************************************************************************/
#include "HC165.h"


/*================================================================= 
 * 功能： 165上的IO引脚配置
 * 参数： 
 * 返回：   
 * 日期：
 *================================================================*/
void Hc165GpioConfig(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	
	GPIO_InitStructure.GPIO_Pin = Pin165LD;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;//GPIO_Mode_Out_PP	
	GPIO_Init(Port165LD, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;//GPIO_Mode_Out_PP	
	GPIO_InitStructure.GPIO_Pin = Pin165CLK1;		
	GPIO_Init(Port165CLK1, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin = Pin165Data1;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;	  
	GPIO_Init(Port165Data1, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = PinSw01;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;	  
	GPIO_Init(PortSw01, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = PinSw02;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;	  
	GPIO_Init(PortSw02, &GPIO_InitStructure);	
}


///*================================================================= 
// * 功能： 获取165链路的数据
// * 参数： 
// * 返回： 16位数据  
// * 日期： 2011/06/07 
// *================================================================*/
//void Get165Data(u8 DataBuf[])
//{

//	u8 i = 0;
//	u8 j = 0;
//	
//	uint8_t DataPinLineStatus  = 0;//数据线状态

//	Hc165GpioConfig( );
//	
//	GPIO_ResetBits(Port165LD,Pin165LD);	//载数据到74HC165
//	delay_us(4);	
//	GPIO_SetBits(Port165LD,Pin165LD);

//	delay_us(4);
//	for(j=0;j<5;j++)
//	{
//		for(i=0; i<8; i++)
//		{
//			GPIO_ResetBits(Port165CLK1,Pin165CLK1);				
//			delay_us(4);

//			DataPinLineStatus = GPIO_ReadInputDataBit(Port165Data1,Pin165Data1);				
//			delay_us(4);		
////			printf("%x-",DataPinLineStatus);
//			if(DataPinLineStatus == 0)
//			{
//				DataBuf[j] &= ~(1<<i);
//			}
//			else
//			{
//				DataBuf[j] |= (1<<i);
//			}
////			DataBuf[j] |= ((DataPinLineStatus & 0x01)) << i;	
//			GPIO_SetBits(Port165CLK1,Pin165CLK1);			
//			delay_us(4);
//		}	
//	}
//}

extern u8 ButtonCurDataTable[ ];
extern u16 TimeTable[ ];
/*================================================================= 
 * 功能： 获取165链路的数据
 * 参数： 
 * 返回： 16位数据  
 * 日期： 2011/06/07 
 *================================================================*/
void Get165Data(u8 DataBuf[])
{

	u8 i = 0;
//	u8 j = 0;
	
//	uint8_t DataPinLineStatus  = 0;//数据线状态

	Hc165GpioConfig( );
	
	GPIO_ResetBits(Port165LD,Pin165LD);	//载数据到74HC165
	delay_us(4);	
	GPIO_SetBits(Port165LD,Pin165LD);

	delay_us(4);

	for(i=0; i<40; i++)
	{
		GPIO_ResetBits(Port165CLK1,Pin165CLK1);				
		delay_us(4);

		DataBuf[i] = GPIO_ReadInputDataBit(Port165Data1,Pin165Data1);		
		if(DataBuf[i] == 0x00)
		{
			TimeTable[i] = 5;	
		}
		else
		{
			TimeTable[i] = 0;
		}
	
		delay_us(4);		
//			printf("%x-",DataPinLineStatus);

//			DataBuf[j] |= ((DataPinLineStatus & 0x01)) << i;	
		GPIO_SetBits(Port165CLK1,Pin165CLK1);			
		delay_us(4);
	}	
	
}

/*================================================================= 
 * 功能： 测试HC 165检测拨码开关状态
 * 参数： 
 * 返回：   
 * 日期： 2011/06/25 
 *================================================================*/
void Test_HC165(void)
{
	u8 DataBuf[5];
	
	u8 i = 0;
	for(i=0;i<5;i++)
	{
		DataBuf[i] = 0;
	}
	
	Get165Data(DataBuf);

	printf("%x %x %x %x %x\r\n",DataBuf[0],DataBuf[1],DataBuf[2],DataBuf[3],DataBuf[4]);
}




















