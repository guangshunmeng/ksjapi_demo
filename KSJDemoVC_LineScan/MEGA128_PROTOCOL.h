#ifndef _KSJSTRUCTDEF_H__
#define _KSJSTRUCTDEF_H__

#define  RESOLUTION_ENCODER     2000    // 编码器分辨率

//============================================================================
// 结构体：CB_TRIGGERMODE0 (CB:control board)
// 功能：   外触发模式0：控制板内部自动产生脉冲
//============================================================================
#pragma pack(push,1)

typedef struct
{
	unsigned short usOutputFreq;		// 输出脉冲的频率
	unsigned short usOutputPulseNum;	// 输出脉冲个数，0或FFFF代表无限个数
	unsigned char  szReserve[8];
}CB_TRIGGERMODE0;				        // 外触发模式0, 共12byte

//============================================================================
// 结构体：CB_TRIGGERMODE1
// 功能： 外触发模式1：根据输入进行触发，延时是指收到触发输入之后，延时一定时间触发
//============================================================================
#define DM_CUSTOM_TIME_MS     0
#define DM_ENCODER_PULSE_NUM  1

typedef struct
{
	unsigned char  ucTriggerInputChannel;    // 触发输入源，共有两个触发源，0/1
	unsigned char  ucDelayMode;	         // 触发延时模式, 两种延时模式，0：自定义延时时间DM_CUSTOM_TIME_MS ，1：根据编码器输入延时DM_ENCODER_PULSE_NUM
	unsigned short usDelayCounter;		 // 延时计数：延时模式0时：自定义单位ms；延时模式1时：代表编码器输入脉冲个数
	unsigned char  szReserve[8];
}CB_TRIGGERMODE1;				 // 12byte

//============================================================================
// 结构体：CB_TRIGGERMODE2
// 功能： 外触发模式2：相机线扫模式设置
//============================================================================
typedef struct
{
	unsigned char  ucTriggerInputChannel;    // 触发输入源，共有3个触发源，0/1/2,0-触发输入源0；1-触发输入源1; 2-以编码器Z为输入源
	unsigned char  ucDelayMode;		 // 触发延时模式, 两种延时模式，0：自定义延时时间DM_CUSTOM_TIME_MS，1：根据编码器输入延时DM_ENCODER_PULSE_NUM
	unsigned short usDelayCounter;		 // 延时计数：延时模式0时：自定义单位ms；延时模式1时：代表编码器输入脉冲个数
	unsigned short usLineTriggerPusles;      // 1024个编码器脉冲输出线扫触发脉冲数量; 公式： 1024*(N/RESOLUTION_ENCODER); N为编码器每圈需要触发相机的次数
	unsigned short usLineTriggerPkt;	 // 相机软件设定采集一帧线扫数量
	unsigned char  szReserve[4];
}CB_TRIGGERMODE2;                                // 12个字节 

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#define  TAG_CMD             'C'
#define  TAG_END              0xFF

#define  FM_TRIGGER_MODE      0
#define  FM_STEPPER_MODE      1

#define  CBC_TRIGGER_SET      0x00
#define  CBC_TRIGGER_START    0x01
#define  CBC_TRIGGER_STOP     0x02

#define  NUM_BYTE_OF_CMD      30
//============================================================================
// 结构体：CB_CMD_TRIGGER
// 功能：  外触发命令格式结构体
//============================================================================
typedef struct
{
	unsigned char ucPre;			// 8bit 标志位'C'=TAG_CMD		
	unsigned char ucFunctionMode;		// 8bit 所要设置的功能模式单元； =0:外触发功能FM_TRIGGER_MODE
	unsigned char ucStart;			// 暂时作为启停命令，0-设置CBC_TRIGGER_SET， 1-开始CBC_TRIGGER_START， 2-停止CBC_TRIGGER_STOP
	unsigned char ucOutputChannel;		// 8bit 设置外触发输出通道,两个触发输出通道0/1
	unsigned char ucOutputTriggerMethod;    // 8bit 触发方式，上升沿，下降沿，高电平，低电平
	unsigned char ucOutputTriggerMode;	// 8bit 触发模式0: 内部自动触发脉冲；1：外部触发产生脉冲		
	union
	{
		CB_TRIGGERMODE0 Mode0;			// 12byte TriggerMode0 
		CB_TRIGGERMODE1 Mode1;			// 12byte TriggerMode1
		CB_TRIGGERMODE2 Mode2;			// 12byte TriggerMode2
	} TriggerMode;
	unsigned char szReserve[10];
	unsigned char ucCheckSum;			// 8bit 和校验
	unsigned char ucEnd;				// 8bit 结尾标志0xFF=TAG_END 		
}CB_CMD_TRIGGER;					// 共 30个字节NUM_BYTE_OF_CMD

#pragma pack(pop)


#endif