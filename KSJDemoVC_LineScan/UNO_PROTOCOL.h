#ifndef __UNO_PROTOCOL_H__
#define __UNO_PROTOCOL_H__

#define  TRIGGERSPEED_HZ_MAX         10000
#define  UNO_OUTPUT_CHANNEL_NUM      2

#define  UNO_PROTOCOL_PRE            'C'
#define  UNO_PROTOCOL_END            'B'

#define  UNO_CHECKSUM( ucChannel, ucFuncMode, usTriggerSpeed, usPulseNum)    (BYTE)( ucChannel + ucFuncMode + usTriggerSpeed + usPulseNum)

// 对于UNO控制板的通信协议
#define FM_STOP         0
#define FM_START        1
#define FM_SET_PARAM    2
#define FM_GET_PARAM    3

#pragma pack( push, 1 )

typedef struct
{
	unsigned char  ucPre;                        // 首字节，字符'C',CatchBest首字
	unsigned char  ucChannel;					 // 0- 通道1；1- 通道2；2- 同时针对两个通道都
	unsigned char  ucFuncMode;					 // 0-停止，1-启动，2-设置参数,3-读取参数
	unsigned short usTriggerSpeed;				 // 脉冲输出速度,单位HZ
	unsigned char  ucCheckSum;					 // 校验和， ucCheckSum = ucChannel + ucFuncMode + usTriggerSpeed + usPulseNum	
	unsigned short usPulseNum;					 // 脉冲个数范围（0-65535）,当脉冲数量设置为65535时，控制板将以设置的频率发送无限个数的脉冲，直至收到软件停止命令。
	unsigned char  ucEnd;						 // 字尾，ucEnd = 'B" ;Catch Best
}CB_UNO_CMD;

#pragma pack( push, 4 )


#endif