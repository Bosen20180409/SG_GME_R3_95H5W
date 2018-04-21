/*******************************************************************
** File        : SX1212driver.c                                   **
********************************************************************
**                                                                **
** Version     : V 1.0                                            **
**                                                                **
** Written by  : Chaouki ROUAISSIA                                **
** Edited by   : Florian KELLER                                   **
**                                                                **
** Date        : 18-08-2009                                       **
**                                                                **
** Project     : API-1212                                         **
**                                                                **
********************************************************************

********************************************************************
** Description : SX1212 transceiver drivers implementation for the**
**               XE8000 family products !!! Packet mode !!!       **
*******************************************************************/

/*******************************************************************
** Include files                                                  **
*******************************************************************/
#include "SX1212Driver.h"
#include <stdbool.h>		//避免bool错误

/*******************************************************************
** Global variables                                               **
*******************************************************************/
static   u8 RFState = RF_STOP;     // RF state machine
static   u8 *pRFFrame;             // Pointer to the RF frame
static   u8 RFFramePos;            // RF payload current position
static   u8 RFFrameSize;           // RF payload size
static   u16 ByteCounter = 0;       // RF frame byte counter
static   u8 PreMode = RF_STANDBY;  // Previous chip operating mode
static   u8 SyncSize = 4;          // Size of sync word
u8 SyncValue[4];       // Value of sync word
u32 RFFrameTimeOut = RF_FRAME_TIMEOUT(1600); // Reception counter value (full frame timeout generation)

//static   u8 RegCntA;                      // LSB of RFFrameTimeOut
//static   u8 RegCntB;

//static   u8 RegIrqEnHig;
//static   u8 RegCntOn;
//static   u8 RegCntConfig1;
//static   u8 RegCntCtrlCk;
//static   u8 RegEvnEn;
static   u8 RegIrqEnMid;
//static   u8 RegPAIn;
//static   u8 RegEvnEn;
//static   u8 RegEvn;
#include "STM32SPI.h"
void SPI1_Init(void)
{
  GPIO_InitTypeDef  GPIO_InitStructure;  		  
	  
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
	
	GPIO_InitStructure.GPIO_Pin = PIN_NSS_CONFIG;
  GPIO_Init(PORT_NSS_CONFIG, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = PIN_NSS_DATA;
  GPIO_Init(PORT_NSS_DATA, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = PIN_SCK;
  GPIO_Init(PORT_SCK, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = PIN_MOSI;
  GPIO_Init(PORT_MOSI, &GPIO_InitStructure);

  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;   //MISO要用模拟输入

	GPIO_InitStructure.GPIO_Pin = PIN_MISO;
  GPIO_Init(PORT_MISO, &GPIO_InitStructure);


	GPIO_InitStructure.GPIO_Pin = PIN_IRQ0;
  GPIO_Init(PORT_IRQ0, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin = PIN_IRQ1;
  GPIO_Init(PORT_IRQ1, &GPIO_InitStructure);
	
//	STM32_SPI1_Init( );
	
	
//  if(GPIO_ReadInputDataBit(PORT_MODE,PIN_MODE) == 0)
//  {
//		EnableMaster = false;
//		printf("[%s:%d]RX...\r\n",__FUNCTION__,__LINE__);
//  }
//  else
  {
		EnableMaster = true;
		printf("[%s:%d]TX...\r\n",__FUNCTION__,__LINE__);
  }  
} 




u8 SPIInit(void)
{
//	SPI1_Init( );
	return 0;
}	
u8 SPIClock(u8 level) 
{
	delay_us(1);
	if(level == 0)
	{
		SCK_0;		
	}
	else
	{
		SCK_1;		
	}		
	return 0;
}
u8 SPIMosi(u8 level) 
{
	if(level == 0)
	{
		MOSI_0;
	}
	else
	{
		MOSI_1;
	}
//	delay_us(1);
	return 0;
}	
u8 SPINssData(u8 level)  
{
	if(level == 0)
	{
		NSS_DATA_0;
		delay_us(1);
	}
	else
	{
		delay_us(1);
		NSS_DATA_1;
	}
	return 0;
}	
u8 SPINssConfig(u8 level)
{
	if(level == 0)
	{
		NSS_CONFIG_0;
	}
	else
	{
		NSS_CONFIG_1;
	}	
	delay_us(1);
	return 0;
}
u8 SPIMisoRead(void)
{
	delay_us(1);
  if(GPIO_ReadInputDataBit(PORT_MISO,PIN_MISO)==0)
  {
    return 0;
  }
  else
  {
    return 1;
  }	
}	


//u16 RegistersCfg433M[] = // SX1212 configuration registers values
//{ 
//	DEF_MCPARAM1 | RF_MC1_STANDBY | RF_MC1_BAND_430470 | RF_MC1_SUBBAND_FIRST,   //00                 
//	DEF_MCPARAM2 | RF_MC2_DATA_MODE_PACKET | RF_MC2_MODULATION_FSK | RF_MC2_OOK_THRESH_TYPE_PEAK | RF_MC2_GAIN_IF_00,  //01                    
//	DEF_FDEV | RF_FDEV_100,//02
//	DEF_BITRATE_MSB | RF_BITRATE_MSB_20000,//03
//	DEF_BITRATE_LSB | RF_BITRATE_LSB_20000, //04   

//	DEF_MCPARAM6 | RF_MC6_PARAMP_11 | RF_MC6_LOW_POWER_RX_OFF | RF_MC6_VCO_TRIM_11 | RF_MC6_RPS_SELECT_1, //05                  
//	DEF_R1 | 0x6b,  //06                          
//	DEF_P1 | 0x2a,    //07                        
//	DEF_S1 | 0x1e,     //08     
//	
//	DEF_R2 | RF_R2_VALUE,  //09                          
//	DEF_P2 | RF_P2_VALUE,   //0a                         
//	DEF_S2 | RF_S2_VALUE,   //0b                      
//	
//	DEF_FIFOCONFIG | RF_FIFO_SIZE_64 | RF_FIFO_THRESH_VALUE,//0c
//	DEF_IRQPARAM1 | RF_IRQ0_RX_STDBY_PAYLOADREADY | RF_IRQ1_RX_STDBY_CRCOK | RF_IRQ0_TX_FIFOEMPTY_START_FIFONOTEMPTY | RF_IRQ1_TX_TXDONE,   //0d                  
//	DEF_IRQPARAM2 | RF_IRQ2_PLL_LOCK_PIN_ON,       //0e             
//	DEF_RSSIIRQTHRESH | RF_RSSIIRQTHRESH_VALUE,    //0f             
//	
//	DEF_RXPARAM1 | RF_RX1_PASSIVEFILT_378 | RF_RX1_FC_FOPLUS100,  //10                    
//	DEF_RXPARAM2 | RF_RX2_FO_100,   //11                   
//	DEF_RXPARAM3 | RF_RX3_POLYPFILT_OFF | RF_RX3_SYNC_SIZE_32 | RF_RX3_SYNC_TOL_0,  //12                    
//	DEF_OOKFLOORTHRESH | RF_OOKFLOORTHRESH_VALUE,    //13                   
//		//RSSI Value (Read only)  //14             
//	DEF_RXPARAM6 | RF_RX6_OOK_THRESH_DECSTEP_000 | RF_RX6_OOK_THRESH_DECPERIOD_000 | RF_RX6_OOK_THRESH_AVERAGING_00,     //15                  
//	
//	DEF_SYNCBYTE1 | 0x69, // 1st byte of Sync word,    //16                 
//	DEF_SYNCBYTE2 | 0x81, // 2nd byte of Sync word,    //17                 
//	DEF_SYNCBYTE3 | 0x7E, // 3rd byte of Sync word,    //18                 
//	DEF_SYNCBYTE4 | 0x96, // 4th byte of Sync word,    //19                 
//	
//	DEF_TXPARAM | RF_TX_FC_200 | RF_TX_POWER_MAX | RF_TX_ZERO_IF_OFF,   //RF_TX_POWER_MAX       RF_TX_POWER_PLUS10    //1a         
//	
//	DEF_OSCPARAM | RF_OSC_CLKOUT_ON | RF_OSC_CLKOUT_427,   //1b                  

//	DEF_PKTPARAM1 | RF_PKT1_MANCHESTER_OFF | 64,    //1c              
//	DEF_NODEADRS  | RF_NODEADRS_VALUE,            //1d     
//	DEF_PKTPARAM3 | RF_PKT3_FORMAT_VARIABLE | RF_PKT3_PREAMBLE_SIZE_32 | RF_PKT3_WHITENING_OFF | RF_PKT3_CRC_ON | RF_PKT3_ADRSFILT_00,     //RF_PKT3_ADRSFILT_00   //1e            
//	DEF_PKTPARAM4 | RF_PKT4_AUTOCLEAR_ON | RF_PKT4_FIFO_STANDBY_WRITE //1f	
//	
//   
//};

//u16 RegistersCfg315M[] = // SX1212 configuration registers values
//{ 
//	DEF_MCPARAM1 | RF_MC1_STANDBY | RF_MC1_BAND_430470 | RF_MC1_SUBBAND_FIRST,   //00                  
//	DEF_MCPARAM2 | RF_MC2_DATA_MODE_PACKET | RF_MC2_MODULATION_FSK | RF_MC2_OOK_THRESH_TYPE_PEAK | RF_MC2_GAIN_IF_00,  //01                    
//	DEF_FDEV | RF_FDEV_100,//02
//	DEF_BITRATE_MSB | RF_BITRATE_MSB_20000,//03
//	DEF_BITRATE_LSB | RF_BITRATE_LSB_20000, //04   

//	DEF_MCPARAM6 | RF_MC6_PARAMP_11 | RF_MC6_LOW_POWER_RX_OFF | RF_MC6_VCO_TRIM_11 | RF_MC6_RPS_SELECT_1, //05                  
//  
//	DEF_R1 | 0x74,  //06                          
//	DEF_P1 | 0x2a,    //07                        
//	DEF_S1 | 0x19,     //08 
//	
//	DEF_R2 | RF_R2_VALUE,  //09                          
//	DEF_P2 | RF_P2_VALUE,   //0a                         
//	DEF_S2 | RF_S2_VALUE,   //0b                      
//	
//	DEF_FIFOCONFIG | RF_FIFO_SIZE_64 | RF_FIFO_THRESH_VALUE,//0c
//	DEF_IRQPARAM1 | RF_IRQ0_RX_STDBY_PAYLOADREADY | RF_IRQ1_RX_STDBY_CRCOK | RF_IRQ0_TX_FIFOEMPTY_START_FIFONOTEMPTY | RF_IRQ1_TX_TXDONE,   //0d                  
//	DEF_IRQPARAM2 | RF_IRQ2_PLL_LOCK_PIN_ON,       //0e             
//	DEF_RSSIIRQTHRESH | RF_RSSIIRQTHRESH_VALUE,    //0f             
//	
//	DEF_RXPARAM1 | RF_RX1_PASSIVEFILT_378 | RF_RX1_FC_FOPLUS100,  //10                    
//	DEF_RXPARAM2 | RF_RX2_FO_100,   //11                   
//	DEF_RXPARAM3 | RF_RX3_POLYPFILT_OFF | RF_RX3_SYNC_SIZE_32 | RF_RX3_SYNC_TOL_0,  //12                    
//	DEF_OOKFLOORTHRESH | RF_OOKFLOORTHRESH_VALUE,    //13                   
//		//RSSI Value (Read only)  //14             
//	DEF_RXPARAM6 | RF_RX6_OOK_THRESH_DECSTEP_000 | RF_RX6_OOK_THRESH_DECPERIOD_000 | RF_RX6_OOK_THRESH_AVERAGING_00,     //15                  
//	
//	DEF_SYNCBYTE1 | 0x69, // 1st byte of Sync word,    //16                 
//	DEF_SYNCBYTE2 | 0x81, // 2nd byte of Sync word,    //17                 
//	DEF_SYNCBYTE3 | 0x7E, // 3rd byte of Sync word,    //18                 
//	DEF_SYNCBYTE4 | 0x96, // 4th byte of Sync word,    //19                 
//	
//	DEF_TXPARAM | RF_TX_FC_200 | RF_TX_POWER_MAX | RF_TX_ZERO_IF_OFF,   //RF_TX_POWER_MAX       RF_TX_POWER_PLUS10    //1a         
//	
//	DEF_OSCPARAM | RF_OSC_CLKOUT_ON | RF_OSC_CLKOUT_427,   //1b                  

//	DEF_PKTPARAM1 | RF_PKT1_MANCHESTER_OFF | 64,    //1c              
//	DEF_NODEADRS  | RF_NODEADRS_VALUE,            //1d     
//	DEF_PKTPARAM3 | RF_PKT3_FORMAT_VARIABLE | RF_PKT3_PREAMBLE_SIZE_32 | RF_PKT3_WHITENING_OFF | RF_PKT3_CRC_ON | RF_PKT3_ADRSFILT_00,     //RF_PKT3_ADRSFILT_00   //1e            
//	DEF_PKTPARAM4 | RF_PKT4_AUTOCLEAR_ON | RF_PKT4_FIFO_STANDBY_WRITE //1f	
//   
//};

void LoadRegistersCfg(u16 des_reg[],u16 src_reg[])
{
	u8 i = 0;
	for(i=0;i<0x1f;i++)
	{
		des_reg[i] = src_reg[i];
	}
}

u8 Freq = F433M;
void SetFeq(u8 F)
{
	if(F == F315M)
	{
		Freq = F315M;
		
		WriteRegister(0x06, DEF_R1 | 0x8f);
		WriteRegister(0x07, DEF_P1 | 0x38);
		WriteRegister(0x08, DEF_S1 | 0x05);		
				
	}
	else if(F == F433M)
	{
		Freq = F433M;
		
		WriteRegister(0x06, DEF_R1 | 0x6b);//433M
		WriteRegister(0x07, DEF_P1 | 0x2a);
		WriteRegister(0x08, DEF_S1 | 0x1e);	
	}	
}


u16 RegistersCfg[] = // SX1212 configuration registers values
{ 
//#define RF_MC1_BAND_300330               0x00
//#define RF_MC1_BAND_320350               0x04
//#define RF_MC1_BAND_350390               0x08
//#define RF_MC1_BAND_390430               0x0C
//#define RF_MC1_BAND_430470               0x10
//#define RF_MC1_BAND_470510               0x14
	DEF_MCPARAM1 | RF_MC1_STANDBY | RF_MC1_BAND_390430 | RF_MC1_SUBBAND_FIRST,   //00                 
	DEF_MCPARAM2 | RF_MC2_DATA_MODE_PACKET | RF_MC2_MODULATION_FSK | RF_MC2_OOK_THRESH_TYPE_PEAK | RF_MC2_GAIN_IF_00,  //01                    
	DEF_FDEV | RF_FDEV_100,//02
	DEF_BITRATE_MSB | RF_BITRATE_MSB_20000,//03
	DEF_BITRATE_LSB | RF_BITRATE_LSB_20000, //04   

	DEF_MCPARAM6 | RF_MC6_PARAMP_11 | RF_MC6_LOW_POWER_RX_OFF | RF_MC6_VCO_TRIM_01 | RF_MC6_RPS_SELECT_1, //05                  
	DEF_R1 | 0x8f,  //06                          
	DEF_P1 | 0x39,    //07                        
	DEF_S1 | 0x37,     //08     
	
	DEF_R2 | RF_R2_VALUE,  //09                          
	DEF_P2 | RF_P2_VALUE,   //0a                         
	DEF_S2 | RF_S2_VALUE,   //0b                      
	
	DEF_FIFOCONFIG | RF_FIFO_SIZE_64 | RF_FIFO_THRESH_VALUE,//0c
	DEF_IRQPARAM1 | RF_IRQ0_RX_STDBY_PAYLOADREADY | RF_IRQ1_RX_STDBY_CRCOK | RF_IRQ0_TX_FIFOEMPTY_START_FIFONOTEMPTY | RF_IRQ1_TX_TXDONE,   //0d                  
	DEF_IRQPARAM2 | RF_IRQ2_PLL_LOCK_PIN_ON,       //0e             
	DEF_RSSIIRQTHRESH | RF_RSSIIRQTHRESH_VALUE,    //0f             
	
	DEF_RXPARAM1 | RF_RX1_PASSIVEFILT_378 | RF_RX1_FC_FOPLUS100,  //10                    
	DEF_RXPARAM2 | RF_RX2_FO_100,   //11                   
	DEF_RXPARAM3 | RF_RX3_POLYPFILT_OFF | RF_RX3_SYNC_SIZE_32 | RF_RX3_SYNC_TOL_0,  //12                    
	DEF_OOKFLOORTHRESH | RF_OOKFLOORTHRESH_VALUE,    //13                   
		//RSSI Value (Read only)  //14             
	DEF_RXPARAM6 | RF_RX6_OOK_THRESH_DECSTEP_000 | RF_RX6_OOK_THRESH_DECPERIOD_000 | RF_RX6_OOK_THRESH_AVERAGING_00,     //15                  
	
	DEF_SYNCBYTE1 | 0x69, // 1st byte of Sync word,    //16                 
	DEF_SYNCBYTE2 | 0x81, // 2nd byte of Sync word,    //17                 
	DEF_SYNCBYTE3 | 0x7E, // 3rd byte of Sync word,    //18                 
	DEF_SYNCBYTE4 | 0x96, // 4th byte of Sync word,    //19                 
	
	DEF_TXPARAM | RF_TX_FC_200 | RF_TX_POWER_MAX | RF_TX_ZERO_IF_OFF,   //RF_TX_POWER_MAX       RF_TX_POWER_PLUS10    //1a         
	
	DEF_OSCPARAM | RF_OSC_CLKOUT_ON | RF_OSC_CLKOUT_427,   //1b                  

	DEF_PKTPARAM1 | RF_PKT1_MANCHESTER_OFF | 64,    //1c              
	DEF_NODEADRS  | RF_NODEADRS_VALUE,            //1d     
	DEF_PKTPARAM3 | RF_PKT3_FORMAT_VARIABLE | RF_PKT3_PREAMBLE_SIZE_32 | RF_PKT3_WHITENING_OFF | RF_PKT3_CRC_ON | RF_PKT3_ADRSFILT_00,     //RF_PKT3_ADRSFILT_00   //1e            
	DEF_PKTPARAM4 | RF_PKT4_AUTOCLEAR_ON | RF_PKT4_FIFO_STANDBY_WRITE //1f	
	
   
};

/*******************************************************************
** Configuration functions                                        **
*******************************************************************/

/*******************************************************************
** InitRFChip : This routine initializes the RFChip registers     **
**              Using Pre Initialized variables                   **
********************************************************************
** In  : -                                                        **
** Out : -                                                        **
*******************************************************************/
void InitRFChip (void)
{
	u16 i;
	// Initializes SX1212

	//    set_bit(PORTO, (SCK + NSS_DATA + NSS_CONFIG + MOSI));
	//    set_bit(PORTP, (SCK + NSS_DATA + NSS_CONFIG + MOSI));

	for(i = 0; (i + 1) <= REG_PKTPARAM4; i++)
	{
		if(i < REG_RSSIVALUE)
		{
			WriteRegister(i, RegistersCfg[i]);
		}
		else
		{
			WriteRegister(i + 1, RegistersCfg[i]);
		}
	}

	SyncSize = ((RegistersCfg[REG_RXPARAM3] >> 3) & 0x03) + 1;
	for(i = 0; i < SyncSize; i++)
	{
		SyncValue[i] = RegistersCfg[REG_SYNCBYTE1 - 1 + i];
	}

	if((RegistersCfg[REG_BITRATE_MSB] == RF_BITRATE_MSB_1600) && (RegistersCfg[REG_BITRATE_LSB] == RF_BITRATE_LSB_1600))
	{
		RFFrameTimeOut = RF_FRAME_TIMEOUT(1600);
	}
	else if((RegistersCfg[REG_BITRATE_MSB] == RF_BITRATE_MSB_2000) && (RegistersCfg[REG_BITRATE_LSB] == RF_BITRATE_LSB_2000))
	{
		RFFrameTimeOut = RF_FRAME_TIMEOUT(2000);
	}
	else if((RegistersCfg[REG_BITRATE_MSB] == RF_BITRATE_MSB_2500) && (RegistersCfg[REG_BITRATE_LSB] == RF_BITRATE_LSB_2500))
	{
		RFFrameTimeOut = RF_FRAME_TIMEOUT(2500);
	}
	else if((RegistersCfg[REG_BITRATE_MSB] == RF_BITRATE_MSB_5000) && (RegistersCfg[REG_BITRATE_LSB] == RF_BITRATE_LSB_5000))
	{
		RFFrameTimeOut = RF_FRAME_TIMEOUT(5000);
	}
	else if((RegistersCfg[REG_BITRATE_MSB] == RF_BITRATE_MSB_5000) && (RegistersCfg[REG_BITRATE_LSB] == RF_BITRATE_LSB_5000))
	{
		RFFrameTimeOut = RF_FRAME_TIMEOUT(8000);
	}
	else if((RegistersCfg[REG_BITRATE_MSB] == RF_BITRATE_MSB_10000) && (RegistersCfg[REG_BITRATE_LSB] == RF_BITRATE_LSB_10000))
	{
		RFFrameTimeOut = RF_FRAME_TIMEOUT(10000);
	}
	else if((RegistersCfg[REG_BITRATE_MSB] == RF_BITRATE_MSB_20000) && (RegistersCfg[REG_BITRATE_LSB] == RF_BITRATE_LSB_20000))
	{    
		RFFrameTimeOut = RF_FRAME_TIMEOUT(20000);
	}
	else if((RegistersCfg[REG_BITRATE_MSB] == RF_BITRATE_MSB_25000) && (RegistersCfg[REG_BITRATE_LSB] == RF_BITRATE_LSB_25000))
	{
		RFFrameTimeOut = RF_FRAME_TIMEOUT(25000);
	}
	else if((RegistersCfg[REG_BITRATE_MSB] == RF_BITRATE_MSB_40000) && (RegistersCfg[REG_BITRATE_LSB] == RF_BITRATE_LSB_40000))
	{
		RFFrameTimeOut = RF_FRAME_TIMEOUT(40000);
	}
	else if((RegistersCfg[REG_BITRATE_MSB] == RF_BITRATE_MSB_50000) && (RegistersCfg[REG_BITRATE_LSB] == RF_BITRATE_LSB_50000))
	{
		RFFrameTimeOut = RF_FRAME_TIMEOUT(50000);
	}
	else if((RegistersCfg[REG_BITRATE_MSB] == RF_BITRATE_MSB_100000) && (RegistersCfg[REG_BITRATE_LSB] == RF_BITRATE_LSB_100000))
	{
		RFFrameTimeOut = RF_FRAME_TIMEOUT(100000);
	}
	else if((RegistersCfg[REG_BITRATE_MSB] == RF_BITRATE_MSB_200000) && (RegistersCfg[REG_BITRATE_LSB] == RF_BITRATE_LSB_200000))
	{
		RFFrameTimeOut = RF_FRAME_TIMEOUT(200000);
	}
	else 
	{
		RFFrameTimeOut = RF_FRAME_TIMEOUT(1600);
	}
//	SetRFMode(RF_SLEEP);
//	SetRFMode(RF_RECEIVER);
	
}

/*******************************************************************
** SetRFMode : Sets the SX1212 operating mode                     **
********************************************************************
** In  : mode                                                     **
** Out : -                                                        **
*******************************************************************/
void SetRFMode(u8 mode)
{
	if(mode != PreMode)
	{
		if(mode == RF_TRANSMITTER)
		{	
			if (PreMode == RF_SLEEP)
			{
				WriteRegister(REG_MCPARAM1, (RegistersCfg[REG_MCPARAM1] & 0x1F) | RF_STANDBY);        		
				Wait(TS_OS);        		
				WriteRegister(REG_MCPARAM1, (RegistersCfg[REG_MCPARAM1] & 0x1F) | RF_SYNTHESIZER);        		
				Wait(TS_FS);         		
				WriteRegister(REG_MCPARAM1, (RegistersCfg[REG_MCPARAM1] & 0x1F) | RF_TRANSMITTER);
				Wait(TS_TR);
			}
			else if (PreMode == RF_STANDBY)
			{
				WriteRegister(REG_MCPARAM1, (RegistersCfg[REG_MCPARAM1] & 0x1F) | RF_SYNTHESIZER);        		
				Wait(TS_FS);         		
				WriteRegister(REG_MCPARAM1, (RegistersCfg[REG_MCPARAM1] & 0x1F) | RF_TRANSMITTER);
				Wait(TS_TR);
			}
			else if (PreMode == RF_SYNTHESIZER)
			{
				WriteRegister(REG_MCPARAM1, (RegistersCfg[REG_MCPARAM1] & 0x1F) | RF_TRANSMITTER);
				Wait(TS_TR);
			}
			else if (PreMode == RF_RECEIVER)
			{
				WriteRegister(REG_MCPARAM1, (RegistersCfg[REG_MCPARAM1] & 0x1F) | RF_TRANSMITTER);
				Wait(TS_TR);
			}		        
			PreMode = RF_TRANSMITTER;
		}		
		else if(mode == RF_RECEIVER)
		{		
			if (PreMode == RF_SLEEP)
			{
				WriteRegister(REG_MCPARAM1, (RegistersCfg[REG_MCPARAM1] & 0x1F) | RF_STANDBY);        		
				Wait(TS_OS);        		
				WriteRegister(REG_MCPARAM1, (RegistersCfg[REG_MCPARAM1] & 0x1F) | RF_SYNTHESIZER);        		
				Wait(TS_FS); 
				WriteRegister(REG_MCPARAM1, (RegistersCfg[REG_MCPARAM1] & 0x1F) | RF_RECEIVER);
				Wait(TS_RE);
			}

			else if (PreMode == RF_STANDBY)
			{
				WriteRegister(REG_MCPARAM1, (RegistersCfg[REG_MCPARAM1] & 0x1F) | RF_SYNTHESIZER);        		
				Wait(TS_FS); 
				WriteRegister(REG_MCPARAM1, (RegistersCfg[REG_MCPARAM1] & 0x1F) | RF_RECEIVER);
				Wait(TS_RE);
			}

			else if (PreMode == RF_SYNTHESIZER)
			{
				WriteRegister(REG_MCPARAM1, (RegistersCfg[REG_MCPARAM1] & 0x1F) | RF_RECEIVER);
				Wait(TS_RE);     		
			}

			else if (PreMode == RF_TRANSMITTER)
			{	
				WriteRegister(REG_MCPARAM1, (RegistersCfg[REG_MCPARAM1] & 0x1F) | RF_RECEIVER);
				Wait(TS_RE);
			}
			PreMode = RF_RECEIVER;
		}		
		else if(mode == RF_SYNTHESIZER)				
		{	
			if (PreMode == RF_SLEEP)
			{
				WriteRegister(REG_MCPARAM1, (RegistersCfg[REG_MCPARAM1] & 0x1F) | RF_STANDBY);        		
				Wait(TS_OS);        		
				WriteRegister(REG_MCPARAM1, (RegistersCfg[REG_MCPARAM1] & 0x1F) | RF_SYNTHESIZER);        		
				Wait(TS_FS); 
			}
			else if (PreMode == RF_STANDBY)
			{
				WriteRegister(REG_MCPARAM1, (RegistersCfg[REG_MCPARAM1] & 0x1F) | RF_SYNTHESIZER);        		
				Wait(TS_FS); 
			}
			else 
			{
				WriteRegister(REG_MCPARAM1, (RegistersCfg[REG_MCPARAM1] & 0x1F) | RF_SYNTHESIZER);        		
			}
			PreMode = RF_SYNTHESIZER;
		}	
		else if(mode == RF_STANDBY)
		{		
			if (PreMode == RF_SLEEP)
			{
				WriteRegister(REG_MCPARAM1, (RegistersCfg[REG_MCPARAM1] & 0x1F) | RF_STANDBY);        		
				Wait(TS_OS);
			}

			else 
			{
				WriteRegister(REG_MCPARAM1, (RegistersCfg[REG_MCPARAM1] & 0x1F) | RF_STANDBY);       		
			}
			
			PreMode = RF_STANDBY;
		}
		
		else // mode == RF_SLEEP
		{
			WriteRegister(REG_MCPARAM1, (RegistersCfg[REG_MCPARAM1] & 0x1F) | RF_SLEEP);
			PreMode = RF_SLEEP;
		}
	}
}

/*******************************************************************
** WriteRegister : Writes the register value at the given address **
**                  on the SX1212                                 **
********************************************************************
** In  : address, value                                           **
** Out : -                                                        **
*******************************************************************/
void WriteRegister(u8 address, u16 value)
{
//	printf("[%s:%d]Address:%x     Data:%x\r\n",__FUNCTION__,__LINE__,address,value);
	SPIInit();
	address = (address << 1) & 0x3E ;
	SPINssData(1);
	SPINssConfig(0);
	SpiInOut(address);
	SpiInOut(value);
	SPINssConfig(1);
}

/*******************************************************************
** ReadRegister : Reads the register value at the given address on**
**                the SX1212                                      **
********************************************************************
** In  : address                                                  **
** Out : value                                                    **
*******************************************************************/
u16 ReadRegister(u8 address)
{
	u8 value = 0;
//	u8 Address = address;
	SPIInit();
	SPINssData(1);
	address = ((address << 1) & 0x7E) | 0x40;
	SPINssConfig(0);
	SpiInOut(address);
	value = SpiInOut(0);
	SPINssConfig(1);
	
//	printf("[%s:%d]Address:%x     Data:%x\r\n",__FUNCTION__,__LINE__,Address,value);

	return value;
}

/*******************************************************************
** Communication functions                                        **
*******************************************************************/

/*******************************************************************
** SendRfFrame : Sends a RF frame                                 **
********************************************************************
** In  : *buffer, size                                            **
** Out : *pReturnCode                                             **
*******************************************************************/
 void SendRfFrame(u8 *buffer, u8 size, u8 *pReturnCode)
{
	u32 nCountTime = 0;
	
//	printf("[%s:%d]: ",__FUNCTION__,__LINE__);
	if((size+1) > (((RegistersCfg[REG_FIFOCONFIG])>>6)+1)*16)// If (size + length byte) > FIFO size
	{  
		RFState |= RF_STOP;
		*pReturnCode = ERROR;
		return;
	}

	RFState |= RF_BUSY;
	RFState &= ~RF_STOP;
	RFFrameSize = size;
	pRFFrame = buffer;

//	SetRFMode(RF_STANDBY);
	WriteRegister(REG_PKTPARAM4, (RegistersCfg[REG_PKTPARAM4-1] & 0xBF) | RF_PKT4_FIFO_STANDBY_WRITE);

	SendByte(RFFrameSize);
	for(ByteCounter = 0, RFFramePos = 0; ByteCounter < RFFrameSize;)
	{
		SendByte(pRFFrame[RFFramePos++]); 
		ByteCounter++; 
	}

	SetRFMode(RF_TRANSMITTER); // Cf RF_IRQ0_TX_FIFOEMPTY_START_FIFONOTEMPTY in RegistersConfig 

	nCountTime = 0;
	while(1)
	{
		if(GPIO_ReadInputDataBit(PORT_IRQ1,PIN_IRQ1) == 1)
		{
			Handle_Irq_Pa1 ( );
//			delay_ms(5);
			Led0_On;
			break;
		}
		else
		{
			delay_ms(1);
			nCountTime ++;
			if(nCountTime > 100)
			{
				nCountTime = 0;
				printf("[%s:%d]Timeout...\r\n",__FUNCTION__,__LINE__);
				Led0_Reverse( );				
				break;
			}
		}
	}
	
//	Wait(1000); // Wait for last bit to be sent (worst case bitrate)
//	printf("[%s:%d]\r\n",__FUNCTION__,__LINE__);
	//SetRFMode(RF_SLEEP);

//	SetRFMode(RF_STANDBY);

//	printf("[%s:%d]\r\n",__FUNCTION__,__LINE__);
	RFState |= RF_STOP;
	RFState &= ~RF_TX_DONE;
	*pReturnCode = OK;
} 

///*******************************************************************
//** ReceiveRfFrame : Receives a RF frame                           **
//********************************************************************
//** In  : -                                                        **
//** Out : *buffer, size, *pReturnCode                              **
//*******************************************************************/
//void ReceiveRfFrame(u8 *buffer, u8 *size, u8 *pReturnCode)
//{   
//	u8 TempRFState;

//	*pReturnCode = RX_RUNNING;

//	TempRFState = RFState; 

//	if(TempRFState & RF_STOP)
//	{
//		pRFFrame = buffer;
//		RFFramePos = 0;
//		RFFrameSize = 2;
//						
//		RegIrqEnMid |= 0x02; // Enables Port A pin 1 interrupt IRQ_1 (CRCOK, Cf RF_IRQ1_RX_STDBY_CRCOK in RegistersConfig)

//		SetRFMode(RF_RECEIVER);
//		EnableTimeOut(true);
//		RFState |= RF_BUSY;
//		RFState &= ~RF_STOP;
//		RFState &= ~RF_TIMEOUT;
//		return;
//	}
//	else if(TempRFState & RF_RX_DONE)
//	{		
//		SetRFMode(RF_STANDBY);        
//		WriteRegister(REG_PKTPARAM4, (RegistersCfg[REG_PKTPARAM4-1] & 0xBF) | RF_PKT4_FIFO_STANDBY_READ);
////		printf("[%s:%d]: ",__FUNCTION__,__LINE__);		
//		RFFrameSize = ReceiveByte();
//		for(ByteCounter = 0, RFFramePos = 0; ByteCounter < RFFrameSize; )
//		{
//			pRFFrame[RFFramePos++] = ReceiveByte();
//			ByteCounter++; 
//		}
//		//SetRFMode(RF_SLEEP);
////		printf("\r\n");
//		*size = RFFrameSize;
//		*pReturnCode = OK;
//		RFState |= RF_STOP;
//		EnableTimeOut(false);
//		RFState &= ~RF_RX_DONE;
//		RegIrqEnMid &= ~0x02; // Disables Port A pin 1 interrupt IRQ_1 (CRCOK, Cf RF_IRQ1_RX_STDBY_CRCOK in RegistersConfig)
//		SPINssData(1);
//		return;
//	}
//	else if(TempRFState & RF_ERROR)
//	{
//		RFState |= RF_STOP;
//		RFState &= ~RF_ERROR;
//		*pReturnCode = ERROR;
//		RegIrqEnMid &= ~0x02; // Disables Port A pin 1 interrupt IRQ_1 (CRCOK, Cf RF_IRQ1_RX_STDBY_CRCOK in RegistersConfig)
//		SPINssData(1);
//		return;
//	}
//	else if(TempRFState & RF_TIMEOUT)
//	{
//		RFState |= RF_STOP;
//		RFState &= ~RF_TIMEOUT;
//		EnableTimeOut(false);
//		*pReturnCode = RX_TIMEOUT;
//		RegIrqEnMid &= ~0x02; // Disables Port A pin 1 interrupt IRQ_1 (CRCOK, Cf RF_IRQ1_RX_STDBY_CRCOK in RegistersConfig)
//		SPINssData(1);
//		return;
//	}
//} 






void ReceiveRfFrame(u8 *buffer, u8 *size, u8 *pReturnCode)
{   
	u8 TempRFState;
	u16 nCount = 0;
	*pReturnCode = RX_RUNNING;

	TempRFState = RFState; 
	nCount = 0;
	while(1)
	{
		nCount ++;
		if(nCount > 1)
		{
//			printf("[%s:%d]Timeout...\r\n",__FUNCTION__,__LINE__);
			break;
		}
		if(GPIO_ReadInputDataBit(PORT_IRQ0,PIN_IRQ0) == 1)
		{
			Handle_Irq_Pa1 ( );
//			printf("[%s:%d]Wait Time %dms\r\n",__FUNCTION__,__LINE__,nCount);
			break;
		}	
//		delay_ms(1);		
	}

	if(TempRFState & RF_STOP)
	{
		printf("[%s:%d]RF_STOP...\r\n",__FUNCTION__,__LINE__);
		pRFFrame = buffer;
		RFFramePos = 0;
		RFFrameSize = 2;
						
		RegIrqEnMid |= 0x02; // Enables Port A pin 1 interrupt IRQ_1 (CRCOK, Cf RF_IRQ1_RX_STDBY_CRCOK in RegistersConfig)

		SetRFMode(RF_RECEIVER);
		EnableTimeOut(true);
		RFState |= RF_BUSY;
		RFState &= ~RF_STOP;
		RFState &= ~RF_TIMEOUT;
		return;
	}
	else if(TempRFState & RF_RX_DONE)
	{		
//		SetRFMode(RF_STANDBY);        
//		WriteRegister(REG_PKTPARAM4, (RegistersCfg[REG_PKTPARAM4-1] & 0xBF) | RF_PKT4_FIFO_STANDBY_READ);
	
		RFFrameSize = ReceiveByte();
//		printf("[%s:%d]RFFrameSize %d\r\n",__FUNCTION__,__LINE__,RFFrameSize);
		for(ByteCounter = 0, RFFramePos = 0; ByteCounter < RFFrameSize; )
		{
			pRFFrame[RFFramePos++] = ReceiveByte();
			ByteCounter++; 
		}
		
		*size = RFFrameSize;
		*pReturnCode = OK;
		
		
//		RFState |= RF_STOP;
		RFState &= ~RF_RX_DONE;
		
		
		RegIrqEnMid &= ~0x02; // Disables Port A pin 1 interrupt IRQ_1 (CRCOK, Cf RF_IRQ1_RX_STDBY_CRCOK in RegistersConfig)
		SPINssData(1);
		return;
	}
	else if(TempRFState & RF_ERROR)
	{
		printf("[%s:%d]RF_ERROR...\r\n",__FUNCTION__,__LINE__);
		RFState |= RF_STOP;
		RFState &= ~RF_ERROR;
		*pReturnCode = ERROR;
		RegIrqEnMid &= ~0x02; // Disables Port A pin 1 interrupt IRQ_1 (CRCOK, Cf RF_IRQ1_RX_STDBY_CRCOK in RegistersConfig)
		SPINssData(1);
		return;
	}
	else if(TempRFState & RF_TIMEOUT)
	{
		printf("[%s:%d]RF_TIMEOUT...\r\n",__FUNCTION__,__LINE__);
		RFState |= RF_STOP;
		RFState &= ~RF_TIMEOUT;
		EnableTimeOut(false);
		*pReturnCode = RX_TIMEOUT;
		RegIrqEnMid &= ~0x02; // Disables Port A pin 1 interrupt IRQ_1 (CRCOK, Cf RF_IRQ1_RX_STDBY_CRCOK in RegistersConfig)
		SPINssData(1);
		return;
	}
}









/*******************************************************************
** SendByte : Sends a data to the transceiver trough the SPI      **
**            interface                                           **
********************************************************************
** In  : b                                                        **
** Out : -                                                        **
*******************************************************************/
/*******************************************************************
**  Information                                                   **
********************************************************************
** This function has been optimized to send a byte to the         **
** transceiver SPI interface as quick as possible by using        **
** IO ports.                                                      **
** If the microcontroller has an  SPI hardware interface there is **
** no need to optimize the function                               **
*******************************************************************/
void SendByte(u8 b)
{
	SPIInit();
	SPINssConfig(1);
	SPINssData(0);

	SPIClock(0);
	if (b & 0x80)
	{
		SPIMosi(1);
	}
	else
	{
		SPIMosi(0);
	}
	SPIClock(1);
	SPIClock(0);
	if (b & 0x40)
	{
		SPIMosi(1);
	}
	else
	{
		SPIMosi(0);
	}
	SPIClock(1);
	SPIClock(0);
	if (b & 0x20)
	{
		SPIMosi(1);
	}
	else
	{
		SPIMosi(0);
	}
	SPIClock(1);
	SPIClock(0);
	if (b & 0x10)
	{
		SPIMosi(1);
	}
	else
	{
		SPIMosi(0);
	}
	SPIClock(1);
	SPIClock(0);
	if (b & 0x08)
	{
		SPIMosi(1);
	}
	else
	{
		SPIMosi(0);
	}
	SPIClock(1);
	SPIClock(0);
	if (b & 0x04)
	{
		SPIMosi(1);
	}
	else
	{
		SPIMosi(0);
	}
	SPIClock(1);
	SPIClock(0);
	if (b & 0x02)
	{
		SPIMosi(1);
	}
	else
	{
		SPIMosi(0);
	}
	SPIClock(1);
	SPIClock(0);
	if (b & 0x01)
	{
		SPIMosi(1);
	}
	else
	{
		SPIMosi(0);
	}
	SPIClock(1);
	SPIClock(0);
	SPIMosi(0);

	SPINssData(1);
	
//	printf("%x ",b);
} // void SendByte(u8 b)

/*******************************************************************
** ReceiveByte : Receives a data from the transceiver trough the  **
**               SPI interface                                    **                                                
********************************************************************
** In  : -                                                        **
** Out : b                                                        **
*******************************************************************/
/*******************************************************************
**  Information                                                   **
********************************************************************
** This function has been optimized to receive a byte from the    **
** transceiver SPI interface as quick as possible by using        **
** IO ports.                                                      **
** If the microcontroller has an  SPI hardware interface there is **
** no need to optimize the function                               **
*******************************************************************/
u8 ReceiveByte(void)
{
	u8 inputByte = 0;

	SPIInit();
	SPINssConfig(1);
	SPINssData(0);

	SPIClock(0);
	SPIClock(1);
	if (SPIMisoRead())
	{
		
		inputByte |= 0x80;
	}
	SPIClock(0);
	SPIClock(1);
	if (SPIMisoRead())
	{
		inputByte |= 0x40;
	}
	SPIClock(0);
	SPIClock(1);
	if (SPIMisoRead())
	{
		inputByte |= 0x20;
	}
	SPIClock(0);
	SPIClock(1);
	if (SPIMisoRead())
	{
		inputByte |= 0x10;
	}
	SPIClock(0);
	SPIClock(1);
	if (SPIMisoRead())
	{
		inputByte |= 0x08;
	}
	SPIClock(0);
	SPIClock(1);
	if (SPIMisoRead())
	{
		inputByte |= 0x04;
	}
	SPIClock(0);
	SPIClock(1);
	if (SPIMisoRead())
	{
		inputByte |= 0x02;
	}
	SPIClock(0);
	SPIClock(1);
	if (SPIMisoRead())
	{
		inputByte |= 0x01;
	}
	SPIClock(0);
	SPIMosi(0);

	SPINssData(1);
	
//	printf("%x ",inputByte);

	return inputByte;
}
/*******************************************************************
** Transceiver specific functions                                 **
*******************************************************************/

/*******************************************************************
** ReadRssi : Reads the Rssi value from the SX1212                **
********************************************************************
** In  : -                                                        **
** Out : value                                                    **
*******************************************************************/
u16 ReadRssi(void)
{
	u16 value;
	value = ReadRegister(REG_RSSIVALUE);  // Reads the RSSI result
	return value;
}

/*******************************************************************
** Utility functions                                              **
*******************************************************************/

/*******************************************************************
** Wait : This routine uses the counter A&B to create a delay     **
**        using the RC ck source                                  **
********************************************************************
** In   : cntVal                                                  **
** Out  : -                                                       **
*******************************************************************/
void Wait(u16 cntVal)
{
	if(cntVal > 1000)
	{
		delay_ms(cntVal/1000);
	}
	else
	{
		delay_us(cntVal);
	}
	
	
//	delay_ms(10);
	
//	RegCntOn &= 0xFC;                              // Disables counter A&B
//	RegEvnEn &= 0x7F;                              // Disables events from the counter A&B
//	RegEvn = 0x80;                                 // Clears the event from the CntA on the event register
//	RegCntCtrlCk =  (RegCntCtrlCk & 0xFC) | 0x01;  // Selects RC frequency as clock source for counter A&B
//	RegCntConfig1 |= 0x34;                         // A&B counters count up, counter A&B are in cascade mode
//	RegCntA       = (u8)(cntVal);                 // LSB of cntVal
//	RegCntB       = (u8)(cntVal >> 8);            // MSB of cntVal
//	RegEvnEn      |= 0x80;                         // Enables events from CntA
//	RegEvn        |= 0x80;                         // Clears the event from the CntA on the event register
//	asm("clrb %stat, #0");                         // Clears the event on the CoolRISC status register
//	RegCntOn      |= 0x03;                         // Enables counter A&B
//	do
//	{
//		asm("halt");
//	}while ((RegEvn & 0x80) == 0x00);              // Waits the event from counter A
//	RegCntOn      &= 0xFE;                         // Disables counter A
//	RegEvnEn      &= 0x7F;                         // Disables events from the counter A
//	RegEvn        |= 0x80;                         // Clears the event from the CntA on the event register
//	asm("clrb %stat, #0");                         // Clears the event on the CoolRISC status register
} // void Wait(u16 cntVal)

/*******************************************************************
** EnableTimeOut : Enables/Disables the RF frame timeout          **
********************************************************************
** In  : enable                                                   **
** Out : -                                                        **
*******************************************************************/
void EnableTimeOut(u8 enable)
{
//	RegCntCtrlCk = (RegCntCtrlCk & 0xFC) | 0x03;        // Selects 128 Hz frequency as clock source for counter A&B
//	RegCntConfig1 |=  0x34;                             // A&B counters count up, counter A&B  are in cascade mode

//	RegCntA = (u8)RFFrameTimeOut;                      // LSB of RFFrameTimeOut
//	RegCntB = (u8)(RFFrameTimeOut >> 8);               // MSB of RFFrameTimeOut

//	if(enable)
//	{
//		RegIrqEnHig |= 0x10;                            // Enables IRQ for the counter A&B
//		RegCntOn |= 0x03;                               // Enables counter A&B
//	}
//	else
//	{
//		RegIrqEnHig &= ~0x10;                           // Disables IRQ for the counter A&B
//		RegCntOn &= ~0x03;                              // Disables counter A&B
//	}
	
} // void EnableTimeOut(u8 enable)

/*******************************************************************
** InvertByte : Inverts a byte. MSB -> LSB, LSB -> MSB            **
********************************************************************
** In  : b                                                        **
** Out : b                                                        **
*******************************************************************/
u8 InvertByte(u8 b)
{
//	u8 Data = 0;
//	u8 i = 0;
//	for(i=0;i<8;i++)
//	{
//		
//	}
//	asm("   move %r0, #0x08");
//	asm("LoopInvertByte:");
//	asm("   shl  %r3");
//	asm("   shrc %r2");
//	asm("   dec  %r0");
//	asm("   jzc  LoopInvertByte");
	return 0;
} // u8 InvertByte(u8 b)

/*******************************************************************
** SpiInOut : Sends and receives a byte from the SPI bus          **
********************************************************************
** In  : outputByte                                               **
** Out : inputByte                                                **
*******************************************************************/
u8 SpiInOut (u8 outputByte)
{
	u8 bitCounter;
	u8 inputByte = 0;

	SPIClock(0);
	for(bitCounter = 0x80; bitCounter != 0x00; bitCounter >>= 1)
	{
		if (outputByte & bitCounter)
		{
			SPIMosi(1);
		}
		else
		{
			SPIMosi(0);
		}
		SPIClock(1);
		if (SPIMisoRead())
		{
			inputByte |= bitCounter;
		}
		SPIClock(0);
	}  // for(BitCounter = 0x80; BitCounter != 0x00; BitCounter >>= 1)
	SPIMosi(0);

	return inputByte;
} // u8 SpiInOut (u8 outputByte)

/*******************************************************************
** SX1212 Packet interrupt handlers                             **
*******************************************************************/

/*******************************************************************
** Handle_Irq_Pa1 : Handles the interruption from the Pin 1 of    **
**                  Port A                                        **
********************************************************************
** In  : -                                                        **
** Out : -                                                        **
*******************************************************************/
void Handle_Irq_Pa1(void)// IRQ_1 = CRC_OK , Cf RF_IRQ1_RX_STDBY_CRCOK in RegistersConfig (Irq routine only used in Rx)
{  
	RFState |= RF_RX_DONE;
	RFState &= ~RF_BUSY;        
} //End Handle_Irq_Pa1

/*******************************************************************
** Handle_Irq_Pa2 : Handles the interruption from the Pin 2 of    **
**                  Port A                                        **
********************************************************************
** In  : -                                                        **
** Out : -                                                        **
*******************************************************************/
void Handle_Irq_Pa2 (void)// IRQ_0 
{ 
//	RFState |= RF_RX_DONE;
//	RFState &= ~RF_BUSY;  

} //End Handle_Irq_Pa2

/*******************************************************************
** Handle_Irq_CntA : Handles the interruption from the Counter A  **
********************************************************************
** In              : -                                            **
** Out             : -                                            **
*******************************************************************/
void Handle_Irq_CntA (void)
{
	RFState |= RF_TIMEOUT;
	RFState &= ~RF_BUSY;
} //End Handle_Irq_CntA

