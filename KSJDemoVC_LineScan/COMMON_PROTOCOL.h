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
    #define FPGAREG_LED                0X13 // FPGA�Ĵ�����ַ��0x13��

enum KSJ_CTRL_BOARD_TYPE
{
	KSJ_CONTROL_BOARD_UNO = 0,
	KSJ_CONTROL_BOARD_MEGA128,
	KSJ_CONTROL_BOARD_UNKNOWN
};

#pragma pack(push,1)

typedef struct
{
	unsigned char ucPre;				// 8bit ��־λ'C'	
	unsigned char ucFunctionMode;		// FM 2 ��ȡmega8����Ϣ
	unsigned char ucInfoIndex;          // 0-MEGA8�汾�ţ�1-�ٶ���Ϣ��2-�豸�ͺ�
	unsigned char ucCheckSum;			// 8bit ��У��
	unsigned char ucEnd;				// 8bit ��β��־,0xFF		
}CB_CMD_MEGA8_READ_INFO;

// ������Ϣ2���ֽڡ�  
typedef struct
{
	BYTE  btMSB;
	BYTE  btLSB;
}REP_CMD_MAGE8_READ_INFO;

typedef struct
{
	unsigned char ucPre;				// 8bit ��־λ'C'	
	unsigned char ucFunctionMode;		// 3��ȡfpga�Ĵ�����
	unsigned char ucRegAddress;         // FPGA�Ĵ�����ַ
	unsigned char ucCheckSum;			// 8bit ��У��
	unsigned char ucEnd;				// 8bit ��β��־,0xFF		
}CB_CMD_FPGA_READ_REG;

typedef struct
{
	unsigned char ucPre; // 8bit ��־λ'C'
	unsigned char ucFunctionMode; // 8bit ��Ҫ���õĹ���ģʽ��Ԫ��4 ���Ƶ�����
	unsigned char ucSetFlash; // 0�����õƹ�ģʽ1����������ʱ��2��������ǰ����ʱ��
	unsigned char ucFlashParam; // ����ʱ��ms
	unsigned char ucCheckSum; // 8bit ��У��
	unsigned char ucEnd; // 8bit ��β��־,0xFF
}CB_CMD_CTRL_LAMP;

typedef struct
{
	unsigned char ucPre;				// 8bit ��־λ'C'	
	unsigned char ucFunctionMode;		// FM 2 ��ȡ��Ϣ
	unsigned char ucInfoIndex;          // 0-MEGA8�汾�ţ�1-�������
	unsigned char ucCheckSum;			// 8bit У���
	unsigned char ucEnd;				// 8bit ��β��־,0xFF		
}CB_CMD_READ_INFO;

// ������Ϣ4���ֽڡ�  
typedef struct
{
	BYTE  bt1;
	BYTE  bt2;
	BYTE  bt3;
	BYTE  bt4;
}REP_CMD_READ_INFO;

#pragma pack(push,4)

#endif