#ifndef __UNO_PROTOCOL_H__
#define __UNO_PROTOCOL_H__

#define  TRIGGERSPEED_HZ_MAX         10000
#define  UNO_OUTPUT_CHANNEL_NUM      2

#define  UNO_PROTOCOL_PRE            'C'
#define  UNO_PROTOCOL_END            'B'

#define  UNO_CHECKSUM( ucChannel, ucFuncMode, usTriggerSpeed, usPulseNum)    (BYTE)( ucChannel + ucFuncMode + usTriggerSpeed + usPulseNum)

// ����UNO���ư��ͨ��Э��
#define FM_STOP         0
#define FM_START        1
#define FM_SET_PARAM    2
#define FM_GET_PARAM    3

#pragma pack( push, 1 )

typedef struct
{
	unsigned char  ucPre;                        // ���ֽڣ��ַ�'C',CatchBest����
	unsigned char  ucChannel;					 // 0- ͨ��1��1- ͨ��2��2- ͬʱ�������ͨ����
	unsigned char  ucFuncMode;					 // 0-ֹͣ��1-������2-���ò���,3-��ȡ����
	unsigned short usTriggerSpeed;				 // ��������ٶ�,��λHZ
	unsigned char  ucCheckSum;					 // У��ͣ� ucCheckSum = ucChannel + ucFuncMode + usTriggerSpeed + usPulseNum	
	unsigned short usPulseNum;					 // ���������Χ��0-65535��,��������������Ϊ65535ʱ�����ư彫�����õ�Ƶ�ʷ������޸��������壬ֱ���յ����ֹͣ���
	unsigned char  ucEnd;						 // ��β��ucEnd = 'B" ;Catch Best
}CB_UNO_CMD;

#pragma pack( push, 4 )


#endif