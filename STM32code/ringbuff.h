/**
  ******************************************************************************
  * @file    ringbuff.h 
  * @author  西小岑
  * @version V1.2.0
  * @date    2019.12.25
  * @brief   ringbuff manage module
  ******************************************************************************
  * @attention
  Copyright (c) 2019 --- 2025 西小岑. All rights reserved.
  声明：
  1、此模块（ringbuff），简称环形缓存模块/流水缓存，作者（西小岑）保留所有权限
  2、此模块仅供参考学习、研究、交流使用
  3、如用于商业目的，需要征求作者同意
  4、作者仅提供源代码，可以从“github.com”上下载，但不限于此渠道
  5、对此模块的使用请自行验证、测试、
  6、对于使用本模块造成的任何损失，作者（西小岑）不承担任何责任。
  7、如将此模块集成于你的代码中，必须保留此声明
  8、如不同意上述条款，请不要使用此模块
  ******************************************************************************
**/

#ifndef __RINGBUFF_H
#define __RINGBUFF_H

#include "includes.h"

#define RING_BUFF_WATERMARK	0xAA	//缓存水印

typedef enum
{
	RingbuffEmpty=0,		//缓存空
	RingbuffFull,			//缓存满
	RingbuffNotFull			//缓存非满
}RingbuffStatus_t;

typedef enum
{
	RingbuffOpSucess=0,		//缓存操作成功----读取写入缓存
	RingbuffOpFailure,		//缓存操作失败----读取写入缓存
	RingbuffOpNotInit
}RingbuffOperateResult_t;

typedef struct
{
	u8 UsePercent;			//缓存时候百分比
	u8 MemberSize;			//缓存成员大小：1字节、2字节、4字节
	u8 clearEnableFlag;		//读取缓存时此值为TRUE则清零缓存/
	void *pBuff;			//指向缓存的指针
	u8 status;				//缓存状态
	u16 inBuffPointer;		//缓存操作指针
	u16 OutBuffPointer;		//缓存操作指针
	u16 usedBytes;			//缓存计数器：已使用	
	u16 freeBytesSize;		//缓存计数器：剩余
	u16 totalByteSize;		//缓存计数器：总大小
}RingbuffMgr_t;

//#define readCmdFrameEndFromRingbuff(Ringbuff,cmd,cmdRev,frameEnd,FrameLength) read3KeyWordFromRingbuff(Ringbuff,cmd,cmdRev,frameEnd,0,1,((FrameLength)-1));

// -------------------------------------- 上层低层调用函数 --------------------------------------
u8 getRingbuffStatus(RingbuffMgr_t *Ringbuff);
u16 getRingbuffUseSize(RingbuffMgr_t *Ringbuff);
u16 getRingbuffFreeSize(RingbuffMgr_t *Ringbuff);
void setRingbuffClearFlag(RingbuffMgr_t *Ringbuff,u8 flag);
// -------------------------------------- 上层调用函数 --------------------------------------
void ringbuffInit(RingbuffMgr_t *Ringbuff,void *buff,u16 BuffByteSize,u8 MemberSize,u8 clearFlag);
void resetRingBuff(RingbuffMgr_t *Ringbuff);
RingbuffOperateResult_t readOneMemberFromRingbuff(RingbuffMgr_t *Ringbuff,void *data);
RingbuffOperateResult_t readNMemberFromRingbuff(RingbuffMgr_t *Ringbuff,void *pBuff,u16 readBytes);
//RingbuffOperateResult_t readNByteFromRingbuff2(RingbuffMgr_t *Ringbuff,u8 *pBuff,u8 offset,u16 readSize);
u16 readAllMemberFromRingbuff(RingbuffMgr_t *Ringbuff,void *pBuff);
//RingbuffOperateResult_t read1KeyWordFromRingbuff(RingbuffMgr_t *Ringbuff,u8 *keyWord,u16 keyWordIndex);
//RingbuffOperateResult_t read3KeyWordFromRingbuff(RingbuffMgr_t *Ringbuff,u8 *keyW1,u8 *keyW2,u8 *keyW3,u16 keyW1index,u16 keyW2index,u16 keyW3index);
//RingbuffOperateResult_t readCmdFrameEndFromRingbuff(RingbuffMgr_t *Ringbuff,u8 *cmd,u8 *cmdRev,u8 *frameEnd,u16 FrameLength);
// -------------------------------------- 底层调用函数 --------------------------------------
RingbuffOperateResult_t writeOneMemberToRingbuff(RingbuffMgr_t *Ringbuff,void *data);
RingbuffOperateResult_t writeNMemberToRingbuff(RingbuffMgr_t *Ringbuff,void *pbuff,u16 WriteByteSize);
u8 CalRingbuffUsedPercent(RingbuffMgr_t *Ringbuff);
// -------------------------------------- 辅助测试功能 --------------------------------------

void printRingBuff(RingbuffMgr_t *Ringbuff,u8 printDataFlag);
void ringbuffTest(void);


#endif 



