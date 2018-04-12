#include "STM32SPI.h"

void STM32_SPI1_Init(void)
{

  SPI_InitTypeDef  SPI_InitStructure;

	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA, ENABLE);//PORTA时钟使能 
	RCC_APB2PeriphClockCmd(	RCC_APB2Periph_SPI1,ENABLE );//SPI1时钟使能 	

	SPI_InitStructure.SPI_Mode = SPI_Mode_Master;
	SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b;
	SPI_InitStructure.SPI_DataWidth = SPI_DataWidth_8b;
	SPI_InitStructure.SPI_CPOL = SPI_CPOL_Low;    			// mode0 SPI_CPOL_Low, SPI_CPHA_1Edge;
	SPI_InitStructure.SPI_CPHA = SPI_CPHA_2Edge;  			// mode3 SPI_CPOL_High,SPI_CPHA_2Edge
	SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;
	SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_2;
	SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;

	SPI_Init(SPI1, &SPI_InitStructure);  //根据SPI_InitStruct中指定的参数初始化外设SPIx寄存器
 
	SPI_Cmd(SPI1, ENABLE); //使能SPI外设
	
	SPI1_ReadWriteByte(0xff);//启动传输		 
}


//SPIx 读写一个字节
//TxData:要写入的字节
//返回值:读取到的字节
u8 SPI1_ReadWriteByte(u8 TxData)
{		
	u8 retry=0;		
	SPI_SendData(SPI2, TxData);	
	while (1)
	{
		if(SPI_GetFlagStatus(SPI2,SPI_FLAG_TXEPT))
		{
			break;
		}
		retry++;
		if(retry>200)
		{
			return 0;
		}		
	}	
	while (1)
	{
		if(SPI_GetFlagStatus(SPI2, SPI_FLAG_RXAVL))	
		{
			return SPI_ReceiveData(SPI2);
		}
		retry++;
		if(retry>200)
		{
			return 0;
		}		
	}					    
}



