/*******************************文件信息***************************************
 **  文 件 名:    UsartProtocol.h
 **  版    本：   V1.0
 **  功    能：   stm32串口协议
 **  用    法：
 **  作    者：   草塘
 **  日	   期：
 **----------------------------历史版本信息------------------------------------
 **  修 改 人：
 **  版    本： 
 **  日  　期：
 **  描  　述：
 ******************************************************************************/
#ifndef _Usart2Protocol_h_
#define _Usart2Protocol_h_


//控制板在线
#define ComDataCtrlOnLine	0x7f
//机械操作中
#define ComDataCtrlMachineOp	0xf7

//成功接收一帧数据的返回值
#define ComAck	0xa5
//不成功接收一帧数据的返回值
#define ComNck	0x5a


//命令码
enum emCmdCode
{												
	ComCmdCodeNull,          
	ComCmdCodeMajorMotor = 0x01,//主轴电机控制命令码
	ComCmdCodeJumpBall = 0x02,  //跳球，彩球电磁铁控制          
	ComCmdCodeSetTime = 0x03,   //设置时间命令码
	ComCmdCodeMusic = 0x04,     //语音控制命令码
	
	ComCmdCodeJumpBallBoardMotor = 0x09,//大转盘电机控制命令码
	ComCmdCodeJumpBallFillMotor = 0x0a,//补球电机控制命令码
	ComCmdCodePushCoinMotor = 0x0b,//推盘电机控制命令码
	ComCmdCodePlayerLotteryClr = 0x0c,  //玩家彩票数清0


//主机与Jp数码管通信命令码
	CmdMainBoardSendValueJP = 0x30,	//主板发送JP值
	CmdMainBoardSendJumpBallDown = 0x31,  //掉球电磁铁控制
	CmdMainBoardSendValueJPGlint = 0x32,	//主板发送JP值，且Jp值闪烁			
};

//主轴电机控制
enum emComCmdMajorData
{
   ComCmdMajorDataNull,

   ComCmdMajorDataForward,      //0x01	主轴电机正转            
   ComCmdMajorDataBackward,     //0x02	主轴电机反转           
   ComCmdMajorDataStop,         //0x03	主轴电机停止            
   ComCmdMajorDataGetLightEye,  //0x04	返回主轴电机光眼值            
   ComCmdMajorData2Pos0,        //0x05	主轴电机到0            
   ComCmdMajorData2Pos1,        //0x06	主轴电机到1            
   ComCmdMajorData2Pos2,        //0x07	主轴电机到2           
   ComCmdMajorData2Pos3,        //0x08	主轴电机到3           
   ComCmdMajorData2Pos4,        //0x09	主轴电机到4          
   ComCmdMajorData2Pos5,        //0x0A	主轴电机到5          
   ComCmdMajorData2PosRMost,    //0x0B	主轴电机到初始位置           
   ComCmdMajorDataSpeed1,       //0x0C 主轴电机速度1            
   ComCmdMajorDataSpeed2,       //0x0D 主轴电机速度2          
   ComCmdMajorDataSpeed3,       //0x0E 主轴电机速度3          
   ComCmdMajorDataSpeed4,       //0x0F 主轴电机速度4          
   ComCmdMajorDataSpeed5,       //0x10 主轴电机速度5         
   ComCmdMajorDataSpeedReset,   //0x11 主轴电机速度复位
   ComCmdMajorDataSpeedUp,      //0x11 主轴电机速度加
   ComCmdMajorDataSpeedDown     //0x11 主轴电机速度减
   
};

enum emComCmdJumpBallBoardData     //大转盘电机
{
   ComCmdJumpBallBoardDataNull,

   ComCmdJumpBallBoardDataStart,      //0x01	          
   ComCmdJumpBallBoardDataStop,       //0x02	          
};

enum emComCmdJumpBallFillData     //补球电机
{
   ComCmdJumpBallFillDataNull,

   ComCmdJumpBallFillDataStart,      //0x01	          
   ComCmdJumpBallFillDataStop,       //0x02	
   ComCmdJumpBallFillDataOnce,       //0x03  补一个球
};

enum emComCmdPushCoinMotorData     //推盘电机
{
   ComCmdPushCoinDataNull,

   ComCmdCodePushCoinMotorStart,      //0x01	          
   ComCmdCodePushCoinMotorStop,       //0x02	
};

enum emComCmdLotteryClrPlayerData   //玩家账目更新
{
   ComCmdLotteryClrPlayerDataNull,

   ComCmdLotteryClrAll,
   ComCmdLotteryUpDataAll ,
};

//音量控制
enum emComCmdMusic
{
   ComCmdMusic0,
   ComCmdMusic1,
   ComCmdMusic2,
   ComCmdMusic3,
   ComCmdMusic4,
   ComCmdMusic5,
   ComCmdMusic6,
   ComCmdMusic7,
   ComCmdMusic8,
   ComCmdMusic9,
   ComCmdMusic10,
   ComCmdMusic11,

   ComCmdMusicLoopPlay,     //0x09	循环播放0xF2          
   ComCmdMusicStopPlay,     //0x0a	停止播放0xFE

   ComCmdMusicV0 = 0XE0,    //0x01	音量0xE0            
   ComCmdMusicV1,           //0x02	音量0xE1
   ComCmdMusicV2,           //0x03	音量0xE2           
   ComCmdMusicV3,           //0x04	音量0xE3           
   ComCmdMusicV4,           //0x05	音量0xE4           
   ComCmdMusicV5,           //0x06	音量0xE5           
   ComCmdMusicV6,           //0x07	音量0xE6          
   ComCmdMusicV7            //0x08	音量0xE7
};

enum emComCmdJumpBallData
{
   UsartCmdJumpBallSwitch1 = 0x00, //跳球电磁铁1
};

enum emComCmdDropCoinData
{
   Player1DropCoin = 0,//玩家1投币
   Player2DropCoin = 1,//玩家2投币
   Player3DropCoin = 2,//玩家3投币
   Player4DropCoin = 3,//玩家4投币
};

enum emComCmdSetTimeData
{
   UsartCmdSetYear   = 0x00,//修改年
   UsartCmdSetMonth  = 0x01,//修改月
   UsartCmdSetDays   = 0x02,//修改日
   UsartCmdSetHour   = 0x03,//修改时
   UsartCmdSetMinute = 0x04,//修改分
   UsartCmdSetSecond = 0x05,//修改秒
};


#endif



