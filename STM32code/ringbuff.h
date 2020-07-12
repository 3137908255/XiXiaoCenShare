/**
  ******************************************************************************
  * @file    ringbuff.h 
  * @author  ��С�
  * @version V1.2.0
  * @date    2019.12.25
  * @brief   ringbuff manage module
  ******************************************************************************
  * @attention
  Copyright (c) 2019 --- 2025 ��С�. All rights reserved.
  ������
  1����ģ�飨ringbuff������ƻ��λ���ģ��/��ˮ���棬���ߣ���Сᯣ���������Ȩ��
  2����ģ������ο�ѧϰ���о�������ʹ��
  3����������ҵĿ�ģ���Ҫ��������ͬ��
  4�����߽��ṩԴ���룬���Դӡ�github.com�������أ��������ڴ�����
  5���Դ�ģ���ʹ����������֤�����ԡ�
  6������ʹ�ñ�ģ����ɵ��κ���ʧ�����ߣ���Сᯣ����е��κ����Ρ�
  7���罫��ģ�鼯������Ĵ����У����뱣��������
  8���粻ͬ����������벻Ҫʹ�ô�ģ��
  ******************************************************************************
**/

#ifndef __RINGBUFF_H
#define __RINGBUFF_H

#include "includes.h"

#define RING_BUFF_WATERMARK	0xAA	//����ˮӡ

typedef enum
{
	RingbuffEmpty=0,		//�����
	RingbuffFull,			//������
	RingbuffNotFull			//�������
}RingbuffStatus_t;

typedef enum
{
	RingbuffOpSucess=0,		//��������ɹ�----��ȡд�뻺��
	RingbuffOpFailure,		//�������ʧ��----��ȡд�뻺��
	RingbuffOpNotInit
}RingbuffOperateResult_t;

typedef struct
{
	u8 UsePercent;			//����ʱ��ٷֱ�
	u8 MemberSize;			//�����Ա��С��1�ֽڡ�2�ֽڡ�4�ֽ�
	u8 clearEnableFlag;		//��ȡ����ʱ��ֵΪTRUE�����㻺��/
	void *pBuff;			//ָ�򻺴��ָ��
	u8 status;				//����״̬
	u16 inBuffPointer;		//�������ָ��
	u16 OutBuffPointer;		//�������ָ��
	u16 usedBytes;			//�������������ʹ��	
	u16 freeBytesSize;		//�����������ʣ��
	u16 totalByteSize;		//������������ܴ�С
}RingbuffMgr_t;

//#define readCmdFrameEndFromRingbuff(Ringbuff,cmd,cmdRev,frameEnd,FrameLength) read3KeyWordFromRingbuff(Ringbuff,cmd,cmdRev,frameEnd,0,1,((FrameLength)-1));

// -------------------------------------- �ϲ�Ͳ���ú��� --------------------------------------
u8 getRingbuffStatus(RingbuffMgr_t *Ringbuff);
u16 getRingbuffUseSize(RingbuffMgr_t *Ringbuff);
u16 getRingbuffFreeSize(RingbuffMgr_t *Ringbuff);
void setRingbuffClearFlag(RingbuffMgr_t *Ringbuff,u8 flag);
// -------------------------------------- �ϲ���ú��� --------------------------------------
void ringbuffInit(RingbuffMgr_t *Ringbuff,void *buff,u16 BuffByteSize,u8 MemberSize,u8 clearFlag);
void resetRingBuff(RingbuffMgr_t *Ringbuff);
RingbuffOperateResult_t readOneMemberFromRingbuff(RingbuffMgr_t *Ringbuff,void *data);
RingbuffOperateResult_t readNMemberFromRingbuff(RingbuffMgr_t *Ringbuff,void *pBuff,u16 readBytes);
//RingbuffOperateResult_t readNByteFromRingbuff2(RingbuffMgr_t *Ringbuff,u8 *pBuff,u8 offset,u16 readSize);
u16 readAllMemberFromRingbuff(RingbuffMgr_t *Ringbuff,void *pBuff);
//RingbuffOperateResult_t read1KeyWordFromRingbuff(RingbuffMgr_t *Ringbuff,u8 *keyWord,u16 keyWordIndex);
//RingbuffOperateResult_t read3KeyWordFromRingbuff(RingbuffMgr_t *Ringbuff,u8 *keyW1,u8 *keyW2,u8 *keyW3,u16 keyW1index,u16 keyW2index,u16 keyW3index);
//RingbuffOperateResult_t readCmdFrameEndFromRingbuff(RingbuffMgr_t *Ringbuff,u8 *cmd,u8 *cmdRev,u8 *frameEnd,u16 FrameLength);
// -------------------------------------- �ײ���ú��� --------------------------------------
RingbuffOperateResult_t writeOneMemberToRingbuff(RingbuffMgr_t *Ringbuff,void *data);
RingbuffOperateResult_t writeNMemberToRingbuff(RingbuffMgr_t *Ringbuff,void *pbuff,u16 WriteByteSize);
u8 CalRingbuffUsedPercent(RingbuffMgr_t *Ringbuff);
// -------------------------------------- �������Թ��� --------------------------------------

void printRingBuff(RingbuffMgr_t *Ringbuff,u8 printDataFlag);
void ringbuffTest(void);


#endif 


