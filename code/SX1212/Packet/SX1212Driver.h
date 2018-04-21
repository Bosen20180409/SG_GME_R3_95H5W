/*******************************************************************
** File        : SX1212driver.h                                   **
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
#ifndef __SX1212DRIVER__
#define __SX1212DRIVER__

/*******************************************************************
** Include files                                                  **
*******************************************************************/
#include "config.h"



/*******************************************************************
** I/O Ports Definitions                                          **
*******************************************************************/
/*===============================================================*/
#define PIN_NSS_CONFIG	  GPIO_Pin_0//PB0
#define PORT_NSS_CONFIG	  GPIOB
#define	NSS_CONFIG_1      PORT_NSS_CONFIG->BSRR = PIN_NSS_CONFIG     								    
#define	NSS_CONFIG_0      PORT_NSS_CONFIG->BRR = PIN_NSS_CONFIG 
/*===============================================================*/
#define PIN_NSS_DATA	  GPIO_Pin_4//PA4
#define PORT_NSS_DATA	  GPIOA
#define	NSS_DATA_1      PORT_NSS_DATA->BSRR = PIN_NSS_DATA     								    
#define	NSS_DATA_0      PORT_NSS_DATA->BRR = PIN_NSS_DATA 
/*===============================================================*/
#define PIN_SCK	  GPIO_Pin_5//PA5
#define PORT_SCK	  GPIOA
#define	SCK_1      PORT_SCK->BSRR = PIN_SCK     								    
#define	SCK_0      PORT_SCK->BRR = PIN_SCK 
/*===============================================================*/
#define PIN_MISO	  GPIO_Pin_6//PA6
#define PORT_MISO	  GPIOA
#define	MISO_1      PORT_MISO->BSRR = PIN_MISO     								    
#define	MISO_0      PORT_MISO->BRR = PIN_MISO 
/*===============================================================*/
#define PIN_MOSI	  GPIO_Pin_7//PA7
#define PORT_MOSI	  GPIOA
#define	MOSI_1      PORT_MOSI->BSRR = PIN_MOSI     								    
#define	MOSI_0      PORT_MOSI->BRR = PIN_MOSI 
/*===============================================================*/

//#define PIN_MODE	  GPIO_Pin_3//PA3
//#define PORT_MODE	  GPIOA
//#define	MODE_1      PORT_MODE->BSRR = PIN_MODE     								    
//#define	MODE_0      PORT_MODE->BRR = PIN_MODE 
///*===============================================================*/


#define PIN_IRQ0	  GPIO_Pin_1//PB1
#define PORT_IRQ0	  GPIOB
#define	IRQ0_1      PORT_IRQ0->BSRR = PIN_IRQ0     								    
#define	IRQ0_0      PORT_IRQ0->BRR = PIN_IRQ0 

//#define PIN_IRQ0	  GPIO_Pin_1//PB1
//#define PORT_IRQ0	  GPIOB
//#define	IRQ0_1      PORT_IRQ0->BSRR = PIN_IRQ0     								    
//#define	IRQ0_0      PORT_IRQ0->BRR = PIN_IRQ0 
/*===============================================================*/
#define PIN_IRQ1	  GPIO_Pin_6//PB6
#define PORT_IRQ1	  GPIOB
#define	IRQ1_1      PORT_IRQ1->BSRR = PIN_IRQ1     								    
#define	IRQ1_0      PORT_IRQ1->BRR = PIN_IRQ1 
/*===============================================================*/

#define PIN_MB_SPI_CS     GPIO_Pin_4
#define PORT_MB_SPI_CS    GPIOA								 

#define PIN_MB_SPI_CLK     GPIO_Pin_5
#define PORT_MB_SPI_CLK    GPIOA								 

#define PIN_MB_SPI_MISO     GPIO_Pin_6
#define PORT_MB_SPI_MISO    GPIOA		

#define PIN_MB_SPI_MOSI     GPIO_Pin_7
#define PORT_MB_SPI_MOSI    GPIOA		

/*===============================================================*/

void SX1212Test(void);

void SPI1_Init(void);
u8 SPI1_ReadWriteByte(u8 TxData);
void SPI1_SetSpeed(u8 SPI_BaudRatePrescaler);

void LoadRegistersCfg(u16 des_reg[],u16 src_reg[]);

extern u16 RegistersCfg315M[];
extern u16 RegistersCfg433M[];
extern u16 RegistersCfg[];

#define F315M 0
#define F433M 1
void SetFeq(u8 F);
/*******************************************************************
** Global definitions                                             **
*******************************************************************/
/*******************************************************************
** RF packet definition                                           **
*******************************************************************/
#define RF_BUFFER_SIZE_MAX   64
#define RF_BUFFER_SIZE       64

/*******************************************************************
** RF State machine                                               **
*******************************************************************/
#define RF_STOP              0x01
#define RF_BUSY              0x02
#define RF_RX_DONE           0x04
#define RF_TX_DONE           0x08
#define RF_ERROR             0x10
#define RF_TIMEOUT           0x20

/*******************************************************************
** RF function return codes                                       **
*******************************************************************/
#define OK                   0x00
#define ERROR                0x01
#define RX_TIMEOUT           0x02
#define RX_RUNNING           0x03
#define TX_TIMEOUT           0x04
#define TX_RUNNING           0x05

/*******************************************************************
** I/O Ports Definitions                                          **
*******************************************************************/
//#if defined(_XE88LC01A_) || defined(_XE88LC05A_)
//	#define PORTO              RegPCOut
//	#define PORTI              RegPCIn
//	#define PORTDIR            RegPCDir
//   #define PORTP              RegPCPullup

//#endif
//#if defined(_XE88LC02_) || defined(_XE88LC02_4KI_) || defined(_XE88LC02_8KI_)
//	#define PORTO              RegPD1Out
//	#define PORTI              RegPD1In
//	#define PORTDIR            RegPD1Dir
//   #define PORTP              RegPD1Pullup
//	
//#endif
//#if defined(_XE88LC06A_) || defined(_XE88LC07A_) 
//	#define PORTO              RegPDOut
//	#define PORTI              RegPDIn
//	#define PORTDIR            RegPDDir
//  #define PORTP              RegPDPullup
//#endif

/*******************************************************************
** Port A pins definitions                                        **
********************************************************************
**                                  *  uC     * SX1212    * PAx   **
*******************************************************************/
#define IRQ_1         	0x02      //*  In     *  Out      * PA1
#define IRQ_0           0x04      //*  In     *  Out      * PA2
//#define PLL_LOCK        0x08      //*  In     *  Out      * PA3

/*******************************************************************
** Port B pins definitions                                        **
********************************************************************
**                                  *  uC     * SX1212    * PBx   **
*******************************************************************/

/*******************************************************************
** Port C pins definitions                                        **
********************************************************************
**                                  *  uC     * SX1212    * PCx   **
*******************************************************************/
#define NSS_DATA        0x01      //*  Out     *  In      * PC0
#define NSS_CONFIG      0x02      //*  Out     *  In      * PC1
#define SCK             0x04      //*  Out     *  In      * PC2
#define MOSI            0x08      //*  Out     *  In      * PC3
#define MISO            0x10      //*  In      *  Out     * PC4

/*******************************************************************
** SX1212 SPI Macros definitions                                  **
*******************************************************************/
//#define SPIInit()           (PORTDIR = (PORTDIR | SCK | NSS_DATA | NSS_CONFIG | MOSI) & (~MISO))
//#define SPIClock(level)     ((level) ? (PORTO |= SCK) : (PORTO &= ~SCK))
//#define SPIMosi(level)      ((level) ? (PORTO |= MOSI) : (PORTO &= ~MOSI))
//#define SPINssData(level)   ((level) ? (PORTO |= NSS_DATA) : (PORTO &= ~NSS_DATA))
//#define SPINssConfig(level) ((level) ? (PORTO |= NSS_CONFIG) : (PORTO &= ~NSS_CONFIG))
//#define SPIMisoRead()       (PORTI & MISO)

//#define SPIInit()           
//#define SPIClock(level)     
//#define SPIMosi(level)     
//#define SPINssData(level)   
//#define SPINssConfig(level)
//#define SPIMisoRead()       

/*******************************************************************
** SX1212 definitions                                             **
*******************************************************************/

/*******************************************************************
** SX1212 Operating modes definition                              **
*******************************************************************/
#define RF_SLEEP                         0x00
#define RF_STANDBY                       0x20
#define RF_SYNTHESIZER                   0x40
#define RF_RECEIVER                      0x60
#define RF_TRANSMITTER                   0x80


/*******************************************************************
** SX1212 Internal registers Address                              **
*******************************************************************/
#define REG_MCPARAM1                     0x00
#define REG_MCPARAM2                     0x01
#define REG_FDEV                         0x02
#define REG_BITRATE_MSB                  0x03
#define REG_BITRATE_LSB                  0x04
#define REG_MCPARAM6                     0x05
#define REG_R1                           0x06
#define REG_P1                           0x07
#define REG_S1                           0x08
#define REG_R2                           0x09
#define REG_P2                           0x0A
#define REG_S2                           0x0B

#define REG_FIFOCONFIG                   0x0C
#define REG_IRQPARAM1                    0x0D
#define REG_IRQPARAM2                    0x0E
#define REG_RSSIIRQTHRESH                0x0F

#define REG_RXPARAM1                     0x10
#define REG_RXPARAM2                     0x11
#define REG_RXPARAM3                     0x12
#define REG_OOKFLOORTHRESH               0x13
#define REG_RSSIVALUE                    0x14 
#define REG_RXPARAM6                     0x15 

#define REG_SYNCBYTE1                    0x16 
#define REG_SYNCBYTE2                    0x17 
#define REG_SYNCBYTE3                    0x18 
#define REG_SYNCBYTE4                    0x19 

#define REG_TXPARAM                      0x1A

#define REG_OSCPARAM                     0x1B

#define REG_PKTPARAM1                    0x1C
#define REG_NODEADRS                     0x1D
#define REG_PKTPARAM3                    0x1E
#define REG_PKTPARAM4                    0x1F


/*******************************************************************
** SX1212 initialisation register values definition               **
*******************************************************************/
#define DEF_MCPARAM1                     0x00
#define DEF_MCPARAM2                     0x00
#define DEF_FDEV                         0x00
#define DEF_BITRATE_MSB                  0x00
#define DEF_BITRATE_LSB                  0x00
#define DEF_MCPARAM6                     0x00
#define DEF_R1                           0x00
#define DEF_P1                           0x00
#define DEF_S1                           0x00
#define DEF_R2                           0x00
#define DEF_P2                           0x00
#define DEF_S2                           0x00

#define DEF_FIFOCONFIG                   0x00
#define DEF_IRQPARAM1                    0x00
#define DEF_IRQPARAM2                    0x08
#define DEF_RSSIIRQTHRESH                0x00

#define DEF_RXPARAM1                     0x00
#define DEF_RXPARAM2                     0x08
#define DEF_RXPARAM3                     0x20
#define DEF_OOKFLOORTHRESH               0x00 
#define DEF_RSSIVALUE                    0x00 
#define DEF_RXPARAM6                     0x00 

#define DEF_SYNCBYTE1                    0x00 
#define DEF_SYNCBYTE2                    0x00 
#define DEF_SYNCBYTE3                    0x00 
#define DEF_SYNCBYTE4                    0x00 

#define DEF_TXPARAM                      0x00

#define DEF_OSCPARAM                     0x00

#define DEF_PKTPARAM1                    0x00
#define DEF_NODEADRS                     0x00
#define DEF_PKTPARAM3                    0x00
#define DEF_PKTPARAM4                    0x00

/*******************************************************************
** SX1212 bit control definition                                  **
*******************************************************************/
// MC Param 1
// Chip operating mode
#define RF_MC1_SLEEP                     0x00
#define RF_MC1_STANDBY                   0x20
#define RF_MC1_SYNTHESIZER               0x40
#define RF_MC1_RECEIVER                  0x60
#define RF_MC1_TRANSMITTER               0x80

// Frequency band
#define RF_MC1_BAND_300330               0x00
#define RF_MC1_BAND_320350               0x04
#define RF_MC1_BAND_350390               0x08
#define RF_MC1_BAND_390430               0x0C
#define RF_MC1_BAND_430470               0x10
#define RF_MC1_BAND_470510               0x14

// Sub-band
#define RF_MC1_SUBBAND_FIRST             0x00
#define RF_MC1_SUBBAND_SECOND            0x01
#define RF_MC1_SUBBAND_THIRD             0x02
#define RF_MC1_SUBBAND_FOURTH            0x03


// MC Param 2
// Data operation mode
#define RF_MC2_DATA_MODE_CONTINUOUS      0x00
#define RF_MC2_DATA_MODE_BUFFERED        0x40
#define RF_MC2_DATA_MODE_PACKET          0x80

// Modulation scheme selection
#define RF_MC2_MODULATION_OOK            0x10
#define RF_MC2_MODULATION_FSK            0x20

// Rx OOK threshold mode selection
#define RF_MC2_OOK_THRESH_TYPE_FIXED     0x00
#define RF_MC2_OOK_THRESH_TYPE_PEAK      0x04
#define RF_MC2_OOK_THRESH_TYPE_AVERAGE   0x08

// Gain on IF chain
#define RF_MC2_GAIN_IF_00                0x00
#define RF_MC2_GAIN_IF_01                0x01
#define RF_MC2_GAIN_IF_10                0x02
#define RF_MC2_GAIN_IF_11                0x03


// Frequency deviation (kHz)
#define RF_FDEV_33                       0x0B
#define RF_FDEV_40                       0x09
#define RF_FDEV_50                       0x07
#define RF_FDEV_80                       0x04
#define RF_FDEV_100                      0x03
#define RF_FDEV_133                      0x02
#define RF_FDEV_200                      0x01


// Bitrate (bit/sec)  
#define RF_BITRATE_MSB_1600              0x7C
#define RF_BITRATE_LSB_1600              0x1F
#define RF_BITRATE_MSB_2000              0x63
#define RF_BITRATE_LSB_2000              0x1F
#define RF_BITRATE_MSB_2500              0x4F
#define RF_BITRATE_LSB_2500              0x1F
#define RF_BITRATE_MSB_5000              0x27
#define RF_BITRATE_LSB_5000              0x1F
#define RF_BITRATE_MSB_8000              0x18
#define RF_BITRATE_LSB_8000              0x1F
#define RF_BITRATE_MSB_10000             0x13
#define RF_BITRATE_LSB_10000             0x1F
#define RF_BITRATE_MSB_20000             0x09
#define RF_BITRATE_LSB_20000             0x1F
#define RF_BITRATE_MSB_25000             0x07
#define RF_BITRATE_LSB_25000             0x1F
#define RF_BITRATE_MSB_40000             0x04
#define RF_BITRATE_LSB_40000             0x1F
#define RF_BITRATE_MSB_50000             0x03
#define RF_BITRATE_LSB_50000             0x1F
#define RF_BITRATE_MSB_100000            0x01
#define RF_BITRATE_LSB_100000            0x1F
#define RF_BITRATE_MSB_200000            0x00
#define RF_BITRATE_LSB_200000            0x1F


// MC Param 6
// PA ramp times in OOK
#define RF_MC6_PARAMP_00                 0x00
#define RF_MC6_PARAMP_01                 0x40
#define RF_MC6_PARAMP_10                 0x80
#define RF_MC6_PARAMP_11                 0xC0

// Low power Rx mode
#define RF_MC6_LOW_POWER_RX_OFF          0x00
#define RF_MC6_LOW_POWER_RX_ON           0x20

// VCO trimming
#define RF_MC6_VCO_TRIM_00               0x00
#define RF_MC6_VCO_TRIM_01               0x02
#define RF_MC6_VCO_TRIM_10               0x04
#define RF_MC6_VCO_TRIM_11               0x06

// RF frequency selection
#define RF_MC6_RPS_SELECT_1              0x00
#define RF_MC6_RPS_SELECT_2              0x01


// SynthR1
#define RF_R1_VALUE                      0x6B

// SynthP1
#define RF_P1_VALUE                      0x2A

// SynthS1
#define RF_S1_VALUE                      0x1E


// SynthR2
#define RF_R2_VALUE                      0x77

// SynthP2
#define RF_P2_VALUE                      0x2F

// SynthS2
#define RF_S2_VALUE                      0x19


// FIFO size
#define RF_FIFO_SIZE_16                  0x00
#define RF_FIFO_SIZE_32                  0x40
#define RF_FIFO_SIZE_48                  0x80
#define RF_FIFO_SIZE_64                  0xC0
                                   
// FIFO threshold                
#define RF_FIFO_THRESH_VALUE             0x0F


// IRQ Param 1
// Select RX&STDBY IRQ_0 sources (Packet mode)
#define RF_IRQ0_RX_STDBY_PAYLOADREADY    0x00
#define RF_IRQ0_RX_STDBY_WRITEBYTE       0x40
#define RF_IRQ0_RX_STDBY_FIFOEMPTY       0x80
#define RF_IRQ0_RX_STDBY_SYNCADRS        0xC0

// Select RX&STDBY IRQ_1 sources (Packet mode)
#define RF_IRQ1_RX_STDBY_CRCOK           0x00
#define RF_IRQ1_RX_STDBY_FIFOFULL        0x10
#define RF_IRQ1_RX_STDBY_RSSI            0x20
#define RF_IRQ1_RX_STDBY_FIFOTHRESH      0x30

// Select TX start condition and IRQ_0 source (Packet mode)
#define RF_IRQ0_TX_FIFOTHRESH_START_FIFOTHRESH     0x00
#define RF_IRQ0_TX_FIFOEMPTY_START_FIFONOTEMPTY    0x08

// Select TX IRQ_1 sources (Packet mode)
#define RF_IRQ1_TX_FIFOFULL              0x00
#define RF_IRQ1_TX_TXDONE                0x04

// FIFO overrun/clear 
#define RF_IRQ1_FIFO_OVERRUN_CLEAR       0x10

// RSSI IRQ flag
#define RF_IRQ2_RSSI_IRQ_CLEAR           0x04

// PLL_Locked flag
#define RF_IRQ2_PLL_LOCK_CLEAR           0x02

// PLL_Locked pin
#define RF_IRQ2_PLL_LOCK_PIN_OFF         0x00
#define RF_IRQ2_PLL_LOCK_PIN_ON          0x01

// RSSI threshold for interrupt
#define RF_RSSIIRQTHRESH_VALUE           0x00


// RX Param 1
// Passive filter (kHz)
#define RF_RX1_PASSIVEFILT_65            0x00
#define RF_RX1_PASSIVEFILT_82            0x10
#define RF_RX1_PASSIVEFILT_109           0x20
#define RF_RX1_PASSIVEFILT_137           0x30
#define RF_RX1_PASSIVEFILT_157           0x40
#define RF_RX1_PASSIVEFILT_184           0x50
#define RF_RX1_PASSIVEFILT_211           0x60
#define RF_RX1_PASSIVEFILT_234           0x70
#define RF_RX1_PASSIVEFILT_262           0x80
#define RF_RX1_PASSIVEFILT_321           0x90
#define RF_RX1_PASSIVEFILT_378           0xA0
#define RF_RX1_PASSIVEFILT_414           0xB0
#define RF_RX1_PASSIVEFILT_458           0xC0
#define RF_RX1_PASSIVEFILT_514           0xD0
#define RF_RX1_PASSIVEFILT_676           0xE0
#define RF_RX1_PASSIVEFILT_987           0xF0

// Butterworth filter (kHz)
#define RF_RX1_FC_VALUE                  0x03
// !!! Values defined below only apply if RFCLKREF = DEFAULT VALUE = 0x07 !!!
#define RF_RX1_FC_FOPLUS25               0x00
#define RF_RX1_FC_FOPLUS50               0x01
#define RF_RX1_FC_FOPLUS75               0x02
#define RF_RX1_FC_FOPLUS100              0x03
#define RF_RX1_FC_FOPLUS125              0x04
#define RF_RX1_FC_FOPLUS150              0x05
#define RF_RX1_FC_FOPLUS175              0x06
#define RF_RX1_FC_FOPLUS200              0x07
#define RF_RX1_FC_FOPLUS225              0x08
#define RF_RX1_FC_FOPLUS250              0x09



// RX Param 2
// Polyphase filter center value (kHz)
#define RF_RX2_FO_VALUE                  0x03
// !!! Values defined below only apply if RFCLKREF = DEFAULT VALUE = 0x07 !!!
#define RF_RX2_FO_50                     0x10
#define RF_RX2_FO_75                     0x20
#define RF_RX2_FO_100                    0x30
#define RF_RX2_FO_125                    0x40
#define RF_RX2_FO_150                    0x50
#define RF_RX2_FO_175                    0x60
#define RF_RX2_FO_200                    0x70
#define RF_RX2_FO_225                    0x80
#define RF_RX2_FO_250                    0x90
#define RF_RX2_FO_275                    0xA0
#define RF_RX2_FO_300                    0xB0
#define RF_RX2_FO_325                    0xC0
#define RF_RX2_FO_350                    0xD0
#define RF_RX2_FO_375                    0xE0
#define RF_RX2_FO_400                    0xF0


// Rx Param 3
// Polyphase filter enable
#define RF_RX3_POLYPFILT_ON              0x80
#define RF_RX3_POLYPFILT_OFF             0x00

// Bit synchronizer
// Automatically activated in Packet mode

// Sync word recognition
// Automatically activated in Packet mode

// Size of the reference sync word
#define RF_RX3_SYNC_SIZE_8               0x00
#define RF_RX3_SYNC_SIZE_16              0x08
#define RF_RX3_SYNC_SIZE_24              0x10
#define RF_RX3_SYNC_SIZE_32              0x18

// Number of tolerated errors for the sync word recognition
#define RF_RX3_SYNC_TOL_0                0x00
#define RF_RX3_SYNC_TOL_1                0x02
#define RF_RX3_SYNC_TOL_2                0x04
#define RF_RX3_SYNC_TOL_3                0x06

// OOK threshold
#define RF_OOKFLOORTHRESH_VALUE          0x0C 

// RSSI Value (Read only)


// Rx Param 6
// Decrement step of RSSI threshold in OOK demodulator (peak mode)
#define RF_RX6_OOK_THRESH_DECSTEP_000    0x00
#define RF_RX6_OOK_THRESH_DECSTEP_001    0x20
#define RF_RX6_OOK_THRESH_DECSTEP_010    0x40
#define RF_RX6_OOK_THRESH_DECSTEP_011    0x60
#define RF_RX6_OOK_THRESH_DECSTEP_100    0x80
#define RF_RX6_OOK_THRESH_DECSTEP_101    0xA0
#define RF_RX6_OOK_THRESH_DECSTEP_110    0xC0
#define RF_RX6_OOK_THRESH_DECSTEP_111    0xE0 

// Decrement period of RSSI threshold in OOK demodulator (peak mode)
#define RF_RX6_OOK_THRESH_DECPERIOD_000  0x00
#define RF_RX6_OOK_THRESH_DECPERIOD_001  0x04
#define RF_RX6_OOK_THRESH_DECPERIOD_010  0x08
#define RF_RX6_OOK_THRESH_DECPERIOD_011  0x0C
#define RF_RX6_OOK_THRESH_DECPERIOD_100  0x10
#define RF_RX6_OOK_THRESH_DECPERIOD_101  0x14
#define RF_RX6_OOK_THRESH_DECPERIOD_110  0x18
#define RF_RX6_OOK_THRESH_DECPERIOD_111  0x1C

// Cutoff freq of average function of RSSI threshold in OOK demodulator (average mode)
#define RF_RX6_OOK_THRESH_AVERAGING_00   0x00
#define RF_RX6_OOK_THRESH_AVERAGING_11   0x03


// TX Param 
// Interpolator filter Tx (kHz)
#define RF_TX_FC_VALUE                   0x70
// !!! Values defined below only apply if RFCLKREF = DEFAULT VALUE = 0x07 !!!
#define RF_TX_FC_25                      0x00
#define RF_TX_FC_50                      0x10
#define RF_TX_FC_75                      0x20
#define RF_TX_FC_100                     0x30
#define RF_TX_FC_125                     0x40
#define RF_TX_FC_150                     0x50
#define RF_TX_FC_175                     0x60
#define RF_TX_FC_200                     0x70
#define RF_TX_FC_225                     0x80
#define RF_TX_FC_250                     0x90
#define RF_TX_FC_275                     0xA0
#define RF_TX_FC_300                     0xB0
#define RF_TX_FC_325                     0xC0
#define RF_TX_FC_350                     0xD0
#define RF_TX_FC_375                     0xE0
#define RF_TX_FC_400                     0xF0

// Tx Output power (dBm)
#define RF_TX_POWER_MAX                  0x00
#define RF_TX_POWER_PLUS10               0x02
#define RF_TX_POWER_PLUS7                0x04
#define RF_TX_POWER_PLUS4                0x06
#define RF_TX_POWER_PLUS1                0x08
#define RF_TX_POWER_MINUS2               0x0A

// Zero IF Tx operation
#define RF_TX_ZERO_IF_OFF                0x00
#define RF_TX_ZERO_IF_ON                 0x01


// OSC Param
// CLKOUT enable
#define RF_OSC_CLKOUT_ON                 0x80
#define RF_OSC_CLKOUT_OFF                0x00

// CLKOUT frequency (kHz)
#define RF_OSC_CLKOUT_12800              0x00
#define RF_OSC_CLKOUT_6400               0x04
#define RF_OSC_CLKOUT_3200               0x08
#define RF_OSC_CLKOUT_2133               0x0C
#define RF_OSC_CLKOUT_1600               0x10
#define RF_OSC_CLKOUT_1280               0x14
#define RF_OSC_CLKOUT_1067               0x18
#define RF_OSC_CLKOUT_914                0x1C
#define RF_OSC_CLKOUT_800                0x20
#define RF_OSC_CLKOUT_711                0x24
#define RF_OSC_CLKOUT_640                0x28
#define RF_OSC_CLKOUT_582                0x2C
#define RF_OSC_CLKOUT_533                0x30
#define RF_OSC_CLKOUT_492                0x34
#define RF_OSC_CLKOUT_457                0x38
#define RF_OSC_CLKOUT_427                0x3C


// PKT Param 1
// Manchester enable
#define RF_PKT1_MANCHESTER_ON            0x80
#define RF_PKT1_MANCHESTER_OFF           0x00

// Payload length
#define RF_PKT1_LENGTH_VALUE             0x00


// Node Address
#define RF_NODEADRS_VALUE                0x00


// PKT Param 3
//Packet format
#define RF_PKT3_FORMAT_FIXED             0x00
#define RF_PKT3_FORMAT_VARIABLE          0x80

// Preamble size
#define RF_PKT3_PREAMBLE_SIZE_8          0x00
#define RF_PKT3_PREAMBLE_SIZE_16         0x20
#define RF_PKT3_PREAMBLE_SIZE_24         0x40
#define RF_PKT3_PREAMBLE_SIZE_32         0x60

// Whitening enable
#define RF_PKT3_WHITENING_ON             0x10
#define RF_PKT3_WHITENING_OFF            0x00

// CRC enable
#define RF_PKT3_CRC_ON                   0x08
#define RF_PKT3_CRC_OFF                  0x00

// Address filtering
#define RF_PKT3_ADRSFILT_00              0x00
#define RF_PKT3_ADRSFILT_01              0x02
#define RF_PKT3_ADRSFILT_10              0x04
#define RF_PKT3_ADRSFILT_11              0x06

//CRC status (Read only)
#define RF_PKT3_CRC_STATUS               0x01


// PKT Param 4
// FIFO autoclear if CRC failed for current packet
#define RF_PKT4_AUTOCLEAR_ON             0x00
#define RF_PKT4_AUTOCLEAR_OFF            0x80

// Select FIFO access in standby mode (read or write)
#define RF_PKT4_FIFO_STANDBY_WRITE       0x00
#define RF_PKT4_FIFO_STANDBY_READ        0x40 


/*******************************************************************
** Timings section : all timing described here are done with the  **
**                   A&B counters cascaded                        **
*******************************************************************/

/*******************************************************************
**             -- SX1212 Recommended timings --                   **
********************************************************************
** These timings depends on the RC frequency                      **
** The following values corresponds to a 2.4576 MHz RC Freq       **
** Times calculation formula                                      **
**                                                                **
** CounterA&B value = RC * wanted time  = 2 457 600  * 2 ms = 4915**
**                                                                **
*******************************************************************/
#define TS_OS          5000//12288 // Quartz Osc wake up time, max 5 ms
#define TS_FS           800//1966 // Freq Synth wake-up time from OS, max 800 us
#define TS_RE           500//1229 // Receiver wake-up time from FS, max 500 us
#define TS_TR           500//1229 // Transmitter wake-up time from FS, max 500 us

/*******************************************************************
**                                                                **
**                     // RF_BUFFER_SIZE * 8 *     (4  + 1)          \          \
** CounterA&B value = || -------------------------------------------- | * 128 Hz | + 1
**                     \\                 4 * BitRate                /          /
**                                                                **
** The plus 1 at the end of formula is required for the highest   **
** baudrate as the resulting timeout is lower than the 1 / 128Hz  **
*******************************************************************/
#define RF_FRAME_TIMEOUT(BitRate) (u16)(float)((((float)((u32)RF_BUFFER_SIZE * (u32)8 *((u32)4  + (u32)1)) / (float)((u32)4 * (u32)BitRate)) * (float)128) + (float)1)

/*******************************************************************
** Functions prototypes                                           **
*******************************************************************/

/*******************************************************************
** Configuration functions                                        **
*******************************************************************/

/*******************************************************************
** InitRFChip : This routine initializes the RFChip registers     **
**              Using Pre Initialized variable                    **
********************************************************************
** In  : -                                                        **
** Out : -                                                        **
*******************************************************************/ 
void InitRFChip (void);

/*******************************************************************
** SetRFMode : Sets the SX1212 operating mode (Sleep, Receiver,   **
**           Transmitter)                                         **
********************************************************************
** In  : mode                                                     **
** Out : -                                                        **
*******************************************************************/
void SetRFMode(u8 mode);

/*******************************************************************
** WriteRegister : Writes the register value at the given address **
**                  on the SX1212                                 **
********************************************************************
** In  : address, value                                           **
** Out : -                                                        **
*******************************************************************/
void WriteRegister(u8 address, u16 value);
 
/*******************************************************************
** ReadRegister : Reads the register value at the given address on**
**                the SX1212                                      **
********************************************************************
** In  : address                                                  **
** Out : value                                                    **
*******************************************************************/
u16 ReadRegister(u8 address);

/*******************************************************************
** Communication functions                                        **
*******************************************************************/

/*******************************************************************
** SendRfFrame : Sends a RF frame                                 **
********************************************************************
** In  : *buffer, size                                            **
** Out : *pReturnCode                                             **
*******************************************************************/
void SendRfFrame(u8 *buffer, u8 size, u8 *pReturnCode);

/*******************************************************************
** ReceiveRfFrame : Receives a RF frame                           **
********************************************************************
** In  : -                                                        **
** Out : *buffer, size, *pReturnCode                              **
*******************************************************************/
void ReceiveRfFrame(u8 *buffer, u8 *size, u8 *pReturnCode);

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
void SendByte(u8 b);

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
u8 ReceiveByte(void);

/*******************************************************************
** Transceiver specific functions                                 **
*******************************************************************/

/*******************************************************************
** ReadRssi : Reads the Rssi value from  SX1212                   **
********************************************************************
** In  : -                                                        **
** Out : value                                                    **
*******************************************************************/
u16 ReadRssi(void);

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
void Wait(u16 cntVal);

/*******************************************************************
** EnableTimeOut : Enables/Disables the RF frame timeout          **
********************************************************************
** In  : enable                                                   **
** Out : -                                                        **
*******************************************************************/
void EnableTimeOut(u8 enable);

/*******************************************************************
** InvertByte : Inverts a byte. MSB -> LSB, LSB -> MSB            **
********************************************************************
** In  : b                                                        **
** Out : b                                                        **
*******************************************************************/
u8 InvertByte(u8 b);

/*******************************************************************
** SpiInOut : Sends and receives a byte from the SPI bus          **
********************************************************************
** In  : outputByte                                               **
** Out : inputByte                                                **
*******************************************************************/
u8 SpiInOut (u8 outputByte);

void Handle_Irq_Pa1(void);
void ReceiveRfFrame(u8 *buffer, u8 *size, u8 *pReturnCode);
#endif /* __SX1212DRIVER__ */
