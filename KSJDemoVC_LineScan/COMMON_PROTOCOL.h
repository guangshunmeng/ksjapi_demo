#ifndef __COMMON_PROTOCOL_H__
#define __COMMON_PROTOCOL_H__

#define  COMMON_PROTOCOL_PRE            'C'
#define  COMMON_PROTOCOL_END            0xFF


#define FM_READ_MAGE8_INFO         2
    #define MAGE8REG_VERSION        0
    #define MAGE8REG_SPEED          1
    #define MAGE8REG_DEVICE_TYPE    2

#define FM_READ_FPGA               3
#define FM_WRITE_FPGA              4
    #define FPGAREG_LED                0X13 // FPGA寄存器地址（0x13）

enum KSJ_CTRL_BOARD_TYPE
{
	KSJ_CONTROL_BOARD_UNO = 0,
	KSJ_CONTROL_BOARD_MEGA128,
	KSJ_CONTROL_BOARD_UNKNOWN
};

#pragma pack(push,1)

typedef struct
{
	unsigned char ucPre;				// 8bit 标志位'C'	
	unsigned char ucFunctionMode;		// FM 2 读取mega8的信息
	unsigned char ucInfoIndex;          // 0-MEGA8版本号，1-速度信息，2-设备型号
	unsigned char ucCheckSum;			// 8bit 和校验
	unsigned char ucEnd;				// 8bit 结尾标志,0xFF		
}CB_CMD_MEGA8_READ_INFO;

// 返回信息2个字节。  
typedef struct
{
	BYTE  btMSB;
	BYTE  btLSB;
}REP_CMD_MAGE8_READ_INFO;

typedef struct
{
	unsigned char ucPre;				// 8bit 标志位'C'	
	unsigned char ucFunctionMode;		// 3读取fpga寄存器；
	unsigned char ucRegAddress;         // FPGA寄存器地址
	unsigned char ucCheckSum;			// 8bit 和校验
	unsigned char ucEnd;				// 8bit 结尾标志,0xFF		
}CB_CMD_FPGA_READ_REG;

typedef struct
{
	unsigned char ucPre; // 8bit 标志位'C'
	unsigned char ucFunctionMode; // 8bit 所要设置的功能模式单元；4 控制调焦灯
	unsigned char ucSetFlash; // 0：设置灯光模式1：设置闪光时间2：设置提前闪光时间
	unsigned char ucFlashParam; // 闪光时间ms
	unsigned char ucCheckSum; // 8bit 和校验
	unsigned char ucEnd; // 8bit 结尾标志,0xFF
}CB_CMD_CTRL_LAMP;

typedef struct
{
	unsigned char ucPre;				// 8bit 标志位'C'	
	unsigned char ucFunctionMode;		// FM 2 读取信息
	unsigned char ucInfoIndex;          // 0-MEGA8版本号，1-脉冲个数
	unsigned char ucCheckSum;			// 8bit 校验和
	unsigned char ucEnd;				// 8bit 结尾标志,0xFF		
}CB_CMD_READ_INFO;

// 返回信息4个字节。  
typedef struct
{
	BYTE  bt1;
	BYTE  bt2;
	BYTE  bt3;
	BYTE  bt4;
}REP_CMD_READ_INFO;

#pragma pack(push,4)

#endif