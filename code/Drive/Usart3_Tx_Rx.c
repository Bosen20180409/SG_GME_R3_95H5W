/*******************************文件信息***************************************
 **  文 件 名:    Usart3_Tx_Rx.c
 **  版    本：   V1.0
 **  功    能：   串口3发送接收处理
 **  用    法：
 **  作    者：   草塘
 **  日	   期：   2013/08
 **----------------------------历史版本信息------------------------------------
 **  修 改 人：
 **  版    本： 
 **  日  　期：
 **  描  　述：
 ******************************************************************************/
#include "Usart3_Tx_Rx.h"



void DealOneCharCmd(u8 cmd)
{
	switch (cmd)
	{
		case '0':
//			Printf("[%s:%d]--Rev cmd:0\r\n",__FUNCTION__,__LINE__);	

			break;				
		case '1':	

			break;
		case '2':
		
//			Printf("[%s:%d]--Rev cmd:2\r\n",__FUNCTION__,__LINE__);	
	
			break;
		case '3':

//			Printf("[%s:%d]--Rev cmd:3\r\n",__FUNCTION__,__LINE__);	
	
			break;
		case '4':		
	
//			Printf("[%s:%d]--Rev cmd:4\r\n",__FUNCTION__,__LINE__);	
	
			break;
		case '5':

//			Printf("[%s:%d]--Rev cmd:5\r\n",__FUNCTION__,__LINE__);	

			break;
		case '6':

			Printf("[%s:%d]--Rev cmd:6\r\n",__FUNCTION__,__LINE__);	
			break;	
		case '7':		

			Printf("[%s:%d]--Rev cmd:7\r\n",__FUNCTION__,__LINE__);	
			break;
		case '8':		

			Printf("[%s:%d]--Rev cmd:8\r\n",__FUNCTION__,__LINE__);	
			break;
		case '9':			

			Printf("[%s:%d]--Rev cmd:9\r\n",__FUNCTION__,__LINE__);	

			break;
		case 'a':				
		case 'A':	

			Printf("[%s:%d]--Rev cmd:a\r\n",__FUNCTION__,__LINE__);	
	
			break;
		case 'b':
		case 'B':
			Printf("[%s:%d]--Rev cmd:b\r\n",__FUNCTION__,__LINE__);	

			break;
		case 'c':
		case 'C':
			Printf("[%s:%d]--Rev cmd:c\r\n",__FUNCTION__,__LINE__);	

			break;
		case 'd':
		case 'D':
			Printf("[%s:%d]--Rev cmd:d\r\n",__FUNCTION__,__LINE__);	

			break;
		case 'e':
		case 'E':
			Printf("[%s:%d]--Rev cmd:e\r\n",__FUNCTION__,__LINE__);	

			break;
		case 'f':
		case 'F':
			Printf("[%s:%d]--Rev cmd:f\r\n",__FUNCTION__,__LINE__);	

			break;
		case 'g':
		case 'G':
			Printf("[%s:%d]--Rev cmd:g\r\n",__FUNCTION__,__LINE__);	

			break;
		case 'h':
		case 'H':
			Printf("[%s:%d]--Rev cmd:h\r\n",__FUNCTION__,__LINE__);	
				
			break;			
		case 'i':
		case 'I':
			Printf("[%s:%d]--Rev cmd:i\r\n",__FUNCTION__,__LINE__);	

			break;
		case 'j':
		case 'J':		
			Printf("[%s:%d]--Rev cmd:j\r\n",__FUNCTION__,__LINE__);	

			break;
		case 'k':
		case 'K':
			Printf("[%s:%d]--Rev cmd:k\r\n",__FUNCTION__,__LINE__);	

			break;			
		case 'l':
		case 'L':
			Printf("[%s:%d]--Rev cmd:l\r\n",__FUNCTION__,__LINE__);	

			break;					
		case 'm':
		case 'M':
			Printf("[%s:%d]--Rev cmd:m\r\n",__FUNCTION__,__LINE__);	

			break;
		case 'n':
		case 'N':
			Printf("[%s:%d]--Rev cmd:n\r\n",__FUNCTION__,__LINE__);	

			break;
		case 'o':
		case 'O':	
			Printf("[%s:%d]--Rev cmd:o\r\n",__FUNCTION__,__LINE__);	
				
			break;
		case 'p':
		case 'P':	
			Printf("[%s:%d]--Rev cmd:p\r\n",__FUNCTION__,__LINE__);	

			break;
		case 'q':
		case 'Q':	
			Printf("[%s:%d]--Rev cmd:q\r\n",__FUNCTION__,__LINE__);	

			break;			
		case 'r':
		case 'R':
			Printf("[%s:%d]--Rev cmd:r\r\n",__FUNCTION__,__LINE__);	

			break;
		case 's':
		case 'S':
			Printf("[%s:%d]--Rev cmd:s\r\n",__FUNCTION__,__LINE__);	
		
			break;	
		case 't':
		case 'T':
			Printf("[%s:%d]--Rev cmd:t\r\n",__FUNCTION__,__LINE__);	

			break;
		case 'u':
		case 'U':
			Printf("[%s:%d]--Rev cmd:u\r\n",__FUNCTION__,__LINE__);	

			break;	
		case 'v':		
		case 'V':
			Printf("[%s:%d]--Rev cmd:v\r\n",__FUNCTION__,__LINE__);	
			break;			
		case 'w':
		case 'W':
			Printf("[%s:%d]--Rev cmd:w\r\n",__FUNCTION__,__LINE__);	

			break;
		case 'x':
		case 'X':	
			Printf("[%s:%d]--Rev cmd:x\r\n",__FUNCTION__,__LINE__);	

			break;
		case 'y':
		case 'Y':
			Printf("[%s:%d]--Rev cmd:y\r\n",__FUNCTION__,__LINE__);	

			break;
		case 'z':
		case 'Z':
			Printf("[%s:%d]--Rev cmd:z\r\n",__FUNCTION__,__LINE__);	

			break;				

		default:
			
			break;
	}
}





