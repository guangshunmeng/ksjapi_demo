#ifndef _KSJSTRUCTDEF_H__
#define _KSJSTRUCTDEF_H__

#define  RESOLUTION_ENCODER     2000    // �������ֱ���

//============================================================================
// �ṹ�壺CB_TRIGGERMODE0 (CB:control board)
// ���ܣ�   �ⴥ��ģʽ0�����ư��ڲ��Զ���������
//============================================================================
#pragma pack(push,1)

typedef struct
{
	unsigned short usOutputFreq;		// ��������Ƶ��
	unsigned short usOutputPulseNum;	// ������������0��FFFF�������޸���
	unsigned char  szReserve[8];
}CB_TRIGGERMODE0;				        // �ⴥ��ģʽ0, ��12byte

//============================================================================
// �ṹ�壺CB_TRIGGERMODE1
// ���ܣ� �ⴥ��ģʽ1������������д�������ʱ��ָ�յ���������֮����ʱһ��ʱ�䴥��
//============================================================================
#define DM_CUSTOM_TIME_MS     0
#define DM_ENCODER_PULSE_NUM  1

typedef struct
{
	unsigned char  ucTriggerInputChannel;    // ��������Դ��������������Դ��0/1
	unsigned char  ucDelayMode;	         // ������ʱģʽ, ������ʱģʽ��0���Զ�����ʱʱ��DM_CUSTOM_TIME_MS ��1�����ݱ�����������ʱDM_ENCODER_PULSE_NUM
	unsigned short usDelayCounter;		 // ��ʱ��������ʱģʽ0ʱ���Զ��嵥λms����ʱģʽ1ʱ����������������������
	unsigned char  szReserve[8];
}CB_TRIGGERMODE1;				 // 12byte

//============================================================================
// �ṹ�壺CB_TRIGGERMODE2
// ���ܣ� �ⴥ��ģʽ2�������ɨģʽ����
//============================================================================
typedef struct
{
	unsigned char  ucTriggerInputChannel;    // ��������Դ������3������Դ��0/1/2,0-��������Դ0��1-��������Դ1; 2-�Ա�����ZΪ����Դ
	unsigned char  ucDelayMode;		 // ������ʱģʽ, ������ʱģʽ��0���Զ�����ʱʱ��DM_CUSTOM_TIME_MS��1�����ݱ�����������ʱDM_ENCODER_PULSE_NUM
	unsigned short usDelayCounter;		 // ��ʱ��������ʱģʽ0ʱ���Զ��嵥λms����ʱģʽ1ʱ����������������������
	unsigned short usLineTriggerPusles;      // 1024�����������������ɨ������������; ��ʽ�� 1024*(N/RESOLUTION_ENCODER); NΪ������ÿȦ��Ҫ��������Ĵ���
	unsigned short usLineTriggerPkt;	 // �������趨�ɼ�һ֡��ɨ����
	unsigned char  szReserve[4];
}CB_TRIGGERMODE2;                                // 12���ֽ� 

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
// �ṹ�壺CB_CMD_TRIGGER
// ���ܣ�  �ⴥ�������ʽ�ṹ��
//============================================================================
typedef struct
{
	unsigned char ucPre;			// 8bit ��־λ'C'=TAG_CMD		
	unsigned char ucFunctionMode;		// 8bit ��Ҫ���õĹ���ģʽ��Ԫ�� =0:�ⴥ������FM_TRIGGER_MODE
	unsigned char ucStart;			// ��ʱ��Ϊ��ͣ���0-����CBC_TRIGGER_SET�� 1-��ʼCBC_TRIGGER_START�� 2-ֹͣCBC_TRIGGER_STOP
	unsigned char ucOutputChannel;		// 8bit �����ⴥ�����ͨ��,�����������ͨ��0/1
	unsigned char ucOutputTriggerMethod;    // 8bit ������ʽ�������أ��½��أ��ߵ�ƽ���͵�ƽ
	unsigned char ucOutputTriggerMode;	// 8bit ����ģʽ0: �ڲ��Զ��������壻1���ⲿ������������		
	union
	{
		CB_TRIGGERMODE0 Mode0;			// 12byte TriggerMode0 
		CB_TRIGGERMODE1 Mode1;			// 12byte TriggerMode1
		CB_TRIGGERMODE2 Mode2;			// 12byte TriggerMode2
	} TriggerMode;
	unsigned char szReserve[10];
	unsigned char ucCheckSum;			// 8bit ��У��
	unsigned char ucEnd;				// 8bit ��β��־0xFF=TAG_END 		
}CB_CMD_TRIGGER;					// �� 30���ֽ�NUM_BYTE_OF_CMD

#pragma pack(pop)


#endif