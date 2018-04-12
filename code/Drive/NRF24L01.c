#include "NRF24L01.h"

u8 TX_ADDRESS[TX_ADR_WIDTH]={0x20,0x16,0x09,0x20,0x11}; //���͵�ַ
u8 RX_ADDRESS[RX_ADR_WIDTH]={0x20,0x16,0x09,0x20,0x11}; //���͵�ַ
    

u8 Read_NRF24L01_IRQ(void)
{
  if(GPIO_ReadInputDataBit(PORT_NRF24L01_IRQ,PIN_NRF24L01_IRQ)==0)
  {
    return 0;
  }
  else
  {
    return 1;
  }  
}

//��ʼ��24L01��IO��
void NRF24L01_Init(void)
{ 	
	GPIO_InitTypeDef GPIO_InitStructure;
  SPI_InitTypeDef  SPI_InitStructure;
   	 
	GPIO_InitStructure.GPIO_Pin  = PIN_NRF24L01_IRQ;   
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD; //PC13 ����  
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
	GPIO_Init(PORT_NRF24L01_IRQ, &GPIO_InitStructure);	

	GPIO_InitStructure.GPIO_Pin  = PIN_NRF24L01_CE;   
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; //PB3 ���  
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
	GPIO_Init(PORT_NRF24L01_CE, &GPIO_InitStructure);			

	GPIO_InitStructure.GPIO_Pin  = PIN_NRF24L01_CSN;   
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; //PA4 ���  
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
	GPIO_Init(PORT_NRF24L01_CSN, &GPIO_InitStructure);		
		 
  SPI1_Init();    		//��ʼ��SPI	 
 
	SPI_Cmd(SPI1, DISABLE); // SPI���費ʹ��

	SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex;  //SPI����Ϊ˫��˫��ȫ˫��
	SPI_InitStructure.SPI_Mode = SPI_Mode_Master;		//SPI����
  SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b;		//���ͽ���8λ֡�ṹ
	SPI_InitStructure.SPI_CPOL = SPI_CPOL_Low;		//ʱ�����յ�
	SPI_InitStructure.SPI_CPHA = SPI_CPHA_1Edge;	//���ݲ����ڵ�1��ʱ����
	SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;		//NSS�ź�����������
	SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_16;		//���岨����Ԥ��Ƶ��ֵ:������Ԥ��ƵֵΪ16
	SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;	//���ݴ����MSBλ��ʼ
	SPI_InitStructure.SPI_CRCPolynomial = 7;	//CRCֵ����Ķ���ʽ
	SPI_Init(SPI1, &SPI_InitStructure);  //����SPI_InitStruct��ָ���Ĳ�����ʼ������SPIx�Ĵ���
 
	SPI_Cmd(SPI1, ENABLE); //ʹ��SPI����
			 
	NRF24L01_CE_0; 			//ʹ��24L01
	NRF24L01_CSN_1;			//SPIƬѡȡ�� 	

//	NRF24L01_CE_1; 			//ʹ��24L01
//	NRF24L01_CSN_1;			//SPIƬѡȡ�� 
//	while(1);		 	 
}
//���24L01�Ƿ����
//����ֵ:0���ɹ�;1��ʧ��	
u8 NRF24L01_Check(void)
{
	u8 buf[5]={0XA5,0XA5,0XA5,0XA5,0XA5};
	u8 i;
	SPI1_SetSpeed(SPI_BaudRatePrescaler_4); //spi�ٶ�Ϊ9Mhz��24L01�����SPIʱ��Ϊ10Mhz��   	 
	NRF24L01_Write_Buf(WRITE_REG_NRF+TX_ADDR,buf,5);//д��5���ֽڵĵ�ַ.	
	NRF24L01_Read_Buf(TX_ADDR,buf,5); //����д��ĵ�ַ  
	for(i=0; i<5; i++)
	{
		if(buf[i] != 0XA5)
		{
			break;
		}
	}		
	if(i != 5)
	{
		return 1;//���24L01����	
	}
	return 0;		 //��⵽24L01
}	 	 
//SPIд�Ĵ���
//reg:ָ���Ĵ�����ַ
//value:д���ֵ
u8 NRF24L01_Write_Reg(u8 reg,u8 value)
{
	u8 status;	
	NRF24L01_CSN_0;                 //ʹ��SPI����			
	status =SPI1_ReadWriteByte(reg);//���ͼĴ����� 
	SPI1_ReadWriteByte(value);      //д��Ĵ�����ֵ 
  NRF24L01_CSN_1;          //��ֹSPI����		
	return(status);       			//����״ֵ̬
}
//��ȡSPI�Ĵ���ֵ
//reg:Ҫ���ļĴ���
u8 NRF24L01_Read_Reg(u8 reg)
{
	u8 reg_val;	    
	NRF24L01_CSN_0;                 //ʹ��SPI����	
	SPI1_ReadWriteByte(reg);   //���ͼĴ�����
	reg_val = SPI1_ReadWriteByte(0XFF);//��ȡ�Ĵ�������	  
  NRF24L01_CSN_1;          //��ֹSPI����	   
	return(reg_val);           //����״ֵ̬
}	
//��ָ��λ�ö���ָ�����ȵ�����
//reg:�Ĵ���(λ��)
//*pBuf:����ָ��
//len:���ݳ���
//����ֵ,�˴ζ�����״̬�Ĵ���ֵ 
u8 NRF24L01_Read_Buf(u8 reg,u8 *pBuf,u8 len)
{
	u8 status,u8_ctr;	       
	NRF24L01_CSN_0;                 //ʹ��SPI����			
	status=SPI1_ReadWriteByte(reg);//���ͼĴ���ֵ(λ��),����ȡ״ֵ̬   	   
	for(u8_ctr=0; u8_ctr<len; u8_ctr++)
	{
		pBuf[u8_ctr] = SPI1_ReadWriteByte(0XFF);//��������
	}
  NRF24L01_CSN_1;          //��ֹSPI����			
	return status;        //���ض�����״ֵ̬
}
//��ָ��λ��дָ�����ȵ�����
//reg:�Ĵ���(λ��)
//*pBuf:����ָ��
//len:���ݳ���
//����ֵ,�˴ζ�����״̬�Ĵ���ֵ
u8 NRF24L01_Write_Buf(u8 reg, u8 *pBuf, u8 len)
{
	u8 status,u8_ctr;	 
	NRF24L01_CSN_0;                 //ʹ��SPI����		
	status = SPI1_ReadWriteByte(reg);//���ͼĴ���ֵ(λ��),����ȡ״ֵ̬
	for(u8_ctr=0; u8_ctr<len; u8_ctr++)
	{
		SPI1_ReadWriteByte(*pBuf++); //д������	 
	}
  NRF24L01_CSN_1;          //��ֹSPI����		
	return status;          //���ض�����״ֵ̬
}				   
//����NRF24L01����һ������
//txbuf:�����������׵�ַ
//����ֵ:�������״��
u8 NRF24L01_TxPacket(u8 *txbuf)
{
	u8 sta;
 	SPI1_SetSpeed(SPI_BaudRatePrescaler_32);//spi�ٶ�Ϊ9Mhz��24L01�����SPIʱ��Ϊ10Mhz��   
	NRF24L01_CE_0;
  NRF24L01_Write_Buf(WR_TX_PLOAD,txbuf,TX_PLOAD_WIDTH);//д���ݵ�TX BUF  32���ֽ�
 	NRF24L01_CE_1;//��������	   
	while(1)//�ȴ��������
	{
		if(Read_NRF24L01_IRQ( ) == 0)
		{
			break;
		}
	}
	sta=NRF24L01_Read_Reg(STATUS);  //��ȡ״̬�Ĵ�����ֵ	   
	NRF24L01_Write_Reg(WRITE_REG_NRF+STATUS,sta); //���TX_DS��MAX_RT�жϱ�־
	if(sta&MAX_TX)//�ﵽ����ط�����
	{
		NRF24L01_Write_Reg(FLUSH_TX,0xff);//���TX FIFO�Ĵ��� 
//		printf("[%s:%d]------------\r\n",__FUNCTION__,__LINE__);
		return MAX_TX; 
	}
	if(sta&TX_OK)//�������
	{
//		printf("[%s:%d]------------\r\n",__FUNCTION__,__LINE__);
		return TX_OK;
	}
	printf("[%s:%d]------------\r\n",__FUNCTION__,__LINE__);
	return 0xff;//����ԭ����ʧ��
}
//����NRF24L01����һ������
//txbuf:�����������׵�ַ
//����ֵ:0��������ɣ��������������
u8 NRF24L01_RxPacket(u8 *rxbuf)
{
	u8 sta;		    							   
	SPI1_SetSpeed(SPI_BaudRatePrescaler_32); //spi�ٶ�Ϊ9Mhz��24L01�����SPIʱ��Ϊ10Mhz��   
	sta = NRF24L01_Read_Reg(STATUS);  //��ȡ״̬�Ĵ�����ֵ    	 
	NRF24L01_Write_Reg(WRITE_REG_NRF+STATUS,sta); //���TX_DS��MAX_RT�жϱ�־
	if(sta & RX_OK)//���յ�����
	{
		NRF24L01_Read_Buf(RD_RX_PLOAD,rxbuf,RX_PLOAD_WIDTH);//��ȡ����
		NRF24L01_Write_Reg(FLUSH_RX,0xff);//���RX FIFO�Ĵ��� 
		return 0; 
	}	   
	return 1;//û�յ��κ�����
}					    
//�ú�����ʼ��NRF24L01��RXģʽ
//����RX��ַ,дRX���ݿ���,ѡ��RFƵ��,�����ʺ�LNA HCURR
//��CE��ߺ�,������RXģʽ,�����Խ���������		   
void NRF24L01_RX_Mode(void)
{
	NRF24L01_CE_0;	  
	NRF24L01_Write_Buf(WRITE_REG_NRF+RX_ADDR_P0,(u8*)RX_ADDRESS,RX_ADR_WIDTH);//дRX�ڵ��ַ
	NRF24L01_Write_Reg(WRITE_REG_NRF+EN_AA,0x01);    //ʹ��ͨ��0���Զ�Ӧ��    
	NRF24L01_Write_Reg(WRITE_REG_NRF+EN_RXADDR,0x01);//ʹ��ͨ��0�Ľ��յ�ַ  	 
	NRF24L01_Write_Reg(WRITE_REG_NRF+RF_CH,40);	     //����RFͨ��Ƶ��		  
	NRF24L01_Write_Reg(WRITE_REG_NRF+RX_PW_P0,RX_PLOAD_WIDTH);//ѡ��ͨ��0����Ч���ݿ��� 	    
	NRF24L01_Write_Reg(WRITE_REG_NRF+RF_SETUP,0x0f);//����TX�������,0db����,2Mbps,���������濪��   
	NRF24L01_Write_Reg(WRITE_REG_NRF+CONFIG, 0x0f);//���û�������ģʽ�Ĳ���;PWR_UP,EN_CRC,16BIT_CRC,����ģʽ 
	NRF24L01_CE_1; //CEΪ��,�������ģʽ 
}						 
//�ú�����ʼ��NRF24L01��TXģʽ
//����TX��ַ,дTX���ݿ���,����RX�Զ�Ӧ��ĵ�ַ,���TX��������,ѡ��RFƵ��,�����ʺ�LNA HCURR
//PWR_UP,CRCʹ��
//��CE��ߺ�,������RXģʽ,�����Խ���������		   
//CEΪ�ߴ���10us,����������.	 
void NRF24L01_TX_Mode(void)
{														 
	NRF24L01_CE_0;	    
	NRF24L01_Write_Buf(WRITE_REG_NRF+TX_ADDR,(u8*)TX_ADDRESS,TX_ADR_WIDTH);//дTX�ڵ��ַ 
	NRF24L01_Write_Buf(WRITE_REG_NRF+RX_ADDR_P0,(u8*)RX_ADDRESS,RX_ADR_WIDTH); //����TX�ڵ��ַ,��ҪΪ��ʹ��ACK	  

	NRF24L01_Write_Reg(WRITE_REG_NRF+EN_AA,0x01);     //ʹ��ͨ��0���Զ�Ӧ��    
	NRF24L01_Write_Reg(WRITE_REG_NRF+EN_RXADDR,0x01); //ʹ��ͨ��0�Ľ��յ�ַ  
	NRF24L01_Write_Reg(WRITE_REG_NRF+SETUP_RETR,0x1a);//�����Զ��ط����ʱ��:500us + 86us;����Զ��ط�����:10��
	NRF24L01_Write_Reg(WRITE_REG_NRF+RF_CH,40);       //����RFͨ��Ϊ40
	NRF24L01_Write_Reg(WRITE_REG_NRF+RF_SETUP,0x0f);  //����TX�������,0db����,2Mbps,���������濪��   
	NRF24L01_Write_Reg(WRITE_REG_NRF+CONFIG,0x0e);    //���û�������ģʽ�Ĳ���;PWR_UP,EN_CRC,16BIT_CRC,����ģʽ,���������ж�
	NRF24L01_CE_1;//CEΪ��,10us����������
}		  



