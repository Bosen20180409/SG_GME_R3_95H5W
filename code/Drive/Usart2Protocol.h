/*******************************�ļ���Ϣ***************************************
 **  �� �� ��:    UsartProtocol.h
 **  ��    ����   V1.0
 **  ��    �ܣ�   stm32����Э��
 **  ��    ����
 **  ��    �ߣ�   ����
 **  ��	   �ڣ�
 **----------------------------��ʷ�汾��Ϣ------------------------------------
 **  �� �� �ˣ�
 **  ��    ���� 
 **  ��  ���ڣ�
 **  ��  ������
 ******************************************************************************/
#ifndef _Usart2Protocol_h_
#define _Usart2Protocol_h_


//���ư�����
#define ComDataCtrlOnLine	0x7f
//��е������
#define ComDataCtrlMachineOp	0xf7

//�ɹ�����һ֡���ݵķ���ֵ
#define ComAck	0xa5
//���ɹ�����һ֡���ݵķ���ֵ
#define ComNck	0x5a


//������
enum emCmdCode
{												
	ComCmdCodeNull,          
	ComCmdCodeMajorMotor = 0x01,//����������������
	ComCmdCodeJumpBall = 0x02,  //���򣬲�����������          
	ComCmdCodeSetTime = 0x03,   //����ʱ��������
	ComCmdCodeMusic = 0x04,     //��������������
	
	ComCmdCodeJumpBallBoardMotor = 0x09,//��ת�̵������������
	ComCmdCodeJumpBallFillMotor = 0x0a,//����������������
	ComCmdCodePushCoinMotor = 0x0b,//���̵������������
	ComCmdCodePlayerLotteryClr = 0x0c,  //��Ҳ�Ʊ����0


//������Jp�����ͨ��������
	CmdMainBoardSendValueJP = 0x30,	//���巢��JPֵ
	CmdMainBoardSendJumpBallDown = 0x31,  //������������
	CmdMainBoardSendValueJPGlint = 0x32,	//���巢��JPֵ����Jpֵ��˸			
};

//����������
enum emComCmdMajorData
{
   ComCmdMajorDataNull,

   ComCmdMajorDataForward,      //0x01	��������ת            
   ComCmdMajorDataBackward,     //0x02	��������ת           
   ComCmdMajorDataStop,         //0x03	������ֹͣ            
   ComCmdMajorDataGetLightEye,  //0x04	��������������ֵ            
   ComCmdMajorData2Pos0,        //0x05	��������0            
   ComCmdMajorData2Pos1,        //0x06	��������1            
   ComCmdMajorData2Pos2,        //0x07	��������2           
   ComCmdMajorData2Pos3,        //0x08	��������3           
   ComCmdMajorData2Pos4,        //0x09	��������4          
   ComCmdMajorData2Pos5,        //0x0A	��������5          
   ComCmdMajorData2PosRMost,    //0x0B	����������ʼλ��           
   ComCmdMajorDataSpeed1,       //0x0C �������ٶ�1            
   ComCmdMajorDataSpeed2,       //0x0D �������ٶ�2          
   ComCmdMajorDataSpeed3,       //0x0E �������ٶ�3          
   ComCmdMajorDataSpeed4,       //0x0F �������ٶ�4          
   ComCmdMajorDataSpeed5,       //0x10 �������ٶ�5         
   ComCmdMajorDataSpeedReset,   //0x11 �������ٶȸ�λ
   ComCmdMajorDataSpeedUp,      //0x11 �������ٶȼ�
   ComCmdMajorDataSpeedDown     //0x11 �������ٶȼ�
   
};

enum emComCmdJumpBallBoardData     //��ת�̵��
{
   ComCmdJumpBallBoardDataNull,

   ComCmdJumpBallBoardDataStart,      //0x01	          
   ComCmdJumpBallBoardDataStop,       //0x02	          
};

enum emComCmdJumpBallFillData     //������
{
   ComCmdJumpBallFillDataNull,

   ComCmdJumpBallFillDataStart,      //0x01	          
   ComCmdJumpBallFillDataStop,       //0x02	
   ComCmdJumpBallFillDataOnce,       //0x03  ��һ����
};

enum emComCmdPushCoinMotorData     //���̵��
{
   ComCmdPushCoinDataNull,

   ComCmdCodePushCoinMotorStart,      //0x01	          
   ComCmdCodePushCoinMotorStop,       //0x02	
};

enum emComCmdLotteryClrPlayerData   //�����Ŀ����
{
   ComCmdLotteryClrPlayerDataNull,

   ComCmdLotteryClrAll,
   ComCmdLotteryUpDataAll ,
};

//��������
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

   ComCmdMusicLoopPlay,     //0x09	ѭ������0xF2          
   ComCmdMusicStopPlay,     //0x0a	ֹͣ����0xFE

   ComCmdMusicV0 = 0XE0,    //0x01	����0xE0            
   ComCmdMusicV1,           //0x02	����0xE1
   ComCmdMusicV2,           //0x03	����0xE2           
   ComCmdMusicV3,           //0x04	����0xE3           
   ComCmdMusicV4,           //0x05	����0xE4           
   ComCmdMusicV5,           //0x06	����0xE5           
   ComCmdMusicV6,           //0x07	����0xE6          
   ComCmdMusicV7            //0x08	����0xE7
};

enum emComCmdJumpBallData
{
   UsartCmdJumpBallSwitch1 = 0x00, //��������1
};

enum emComCmdDropCoinData
{
   Player1DropCoin = 0,//���1Ͷ��
   Player2DropCoin = 1,//���2Ͷ��
   Player3DropCoin = 2,//���3Ͷ��
   Player4DropCoin = 3,//���4Ͷ��
};

enum emComCmdSetTimeData
{
   UsartCmdSetYear   = 0x00,//�޸���
   UsartCmdSetMonth  = 0x01,//�޸���
   UsartCmdSetDays   = 0x02,//�޸���
   UsartCmdSetHour   = 0x03,//�޸�ʱ
   UsartCmdSetMinute = 0x04,//�޸ķ�
   UsartCmdSetSecond = 0x05,//�޸���
};


#endif



