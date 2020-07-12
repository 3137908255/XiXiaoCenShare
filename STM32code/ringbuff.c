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
  * 数据类型基于《DataType.h》定义
  * 此模块与硬件无关、与其他软件无关、是一个完成独立的模块，作为一个中间层软件独立存在
  * 不依赖其他模块，主要提供一个缓存的管理功能，思路是将一个一维数据缓存组织成一个环形的逻辑结构。
  * 主要功能：
  * A、初始化缓存管理器，将管理器与缓存对接起来
  * B、向缓存写入数据（包括单字节与多字节两种方法）
  * C、从缓存读取数据（包括读取单字节、多字节与全部读出）
  * D、查询缓存状态：缓存空，缓存满，缓存非空
  * E、查询缓存空闲空间大小
  * F、查询缓存使用量（即缓存装有多少数据）
  * G、重设缓存各个变量（各个变量恢复到初始状态）
  * ------------------------------------------------------------
  * 
  * 
  * ------------------------------------------------------------
  * 注意：
  * 1、此模块符合三层架构程序设计思路（此模块为中间层）
  * 2、清零控制：读取数据之后缓存是否清零可受控---清零或者不清零（保持原样数据，之后由后面写入的数据替换）
  * 3、缓存满之后：无法写入新的数据，必须读取缓存中的数据或者复位该实例
  * ------------------------------------------------------------
  * 上层低层调用函数
  * GetRingbuffFreeSize();GetRingbuffStatus();
  * ------------------------------------------------------------
  * 上层调用函数：
  * GetRingbuffUseSize();resetRingBuff();
  * readOneByteFromRingbuff();readNByteFromRingbuff();readAllByteFromRingbuff();
  * read1KeyWordFromRingbuff();read3KeyWordFromRingbuff()
  * 低层调用函数：
  * RingbuffInit();writeOneByteToRingbuff();writeNByteToRingbuff();
  * ------------------------------------------------------------
  ******************************************************************************
*/
#include "includes.h"
/********************************************************************
函数功能：初始化环形缓存实例
入口参数：Ringbuff缓存管理实例，buff缓存地址，BuffByteSize缓存大小,MemberSize缓存成员大小 
clearFlag清零标志（读取数据之后是否清零缓存）
返    回：无。
备    注：无。
********************************************************************/
void ringbuffInit(RingbuffMgr_t *Ringbuff,void *buff,u16 BuffByteSize,u8 MemberSize,u8 clearFlag)
{
	Ringbuff->UsePercent=0;
	Ringbuff->MemberSize=MemberSize;
	Ringbuff->clearEnableFlag=clearFlag;
	Ringbuff->pBuff=buff;
	Ringbuff->usedBytes=0;
	Ringbuff->inBuffPointer=0;
	Ringbuff->OutBuffPointer=0;
	Ringbuff->status=RingbuffEmpty;
	Ringbuff->totalByteSize=BuffByteSize;
	Ringbuff->freeBytesSize=BuffByteSize;
	memset(Ringbuff->pBuff,RING_BUFF_WATERMARK,Ringbuff->totalByteSize);
}
/********************************************************************
函数功能：获取环形缓存状态
入口参数：无。
返    回：无。
备    注：无。
********************************************************************/
u8 getRingbuffStatus(RingbuffMgr_t *Ringbuff)
{
	return Ringbuff->status;
}
/********************************************************************
函数功能：获取环形缓存数据大小
入口参数：无。
返    回：无。
备    注：无。
********************************************************************/
u16 getRingbuffUseSize(RingbuffMgr_t *Ringbuff)
{
	return Ringbuff->usedBytes;
}
/********************************************************************
函数功能：获取环形缓存剩余空间大小
入口参数：无。
返    回：无。
备    注：无。
********************************************************************/
u16 getRingbuffFreeSize(RingbuffMgr_t *Ringbuff)
{
	return Ringbuff->freeBytesSize;
}
/********************************************************************
函数功能：设置读取缓存数据之后是否清零缓存数据的标志
入口参数：flag=TRUE时读取数据立即清零对应缓存，否则不清零
返    回：无。
备    注：无。
********************************************************************/
void setRingbuffClearFlag(RingbuffMgr_t *Ringbuff,u8 flag)
{
	Ringbuff->clearEnableFlag=flag;
}
/********************************************************************
函数功能：获取环形缓存剩余空间大小
入口参数：无。
返    回：无。
备    注：无。
********************************************************************/
void resetRingBuff(RingbuffMgr_t *Ringbuff)
{
	Ringbuff->UsePercent=0;
	Ringbuff->inBuffPointer=0;
	Ringbuff->OutBuffPointer=0;
	Ringbuff->status=RingbuffEmpty;
	Ringbuff->usedBytes=0;
	Ringbuff->freeBytesSize=Ringbuff->totalByteSize;
	if(Ringbuff->clearEnableFlag==TRUE)
	{
		memset(Ringbuff->pBuff,RING_BUFF_WATERMARK,Ringbuff->totalByteSize);
	}
}
/********************************************************************
函数功能：从环形缓存读取一个成员数据
入口参数：Ringbuff缓存管理实例,*data读出数据保存地址
返回：RingbuffOpFailure或者RingbuffOpSucess
备    注：无。
********************************************************************/
RingbuffOperateResult_t readOneMemberFromRingbuff(RingbuffMgr_t *Ringbuff,void *data)
{
	if(Ringbuff->pBuff == NULL)return RingbuffOpNotInit;
	if(Ringbuff->usedBytes>0)
	{
		Ringbuff->usedBytes-=Ringbuff->MemberSize;
		Ringbuff->freeBytesSize+=Ringbuff->MemberSize;
		if(Ringbuff->clearEnableFlag==TRUE)	{
			memcpy(data,(u8*)Ringbuff->pBuff+Ringbuff->OutBuffPointer,Ringbuff->MemberSize);
			memset((u8*)Ringbuff->pBuff+Ringbuff->OutBuffPointer,0,Ringbuff->MemberSize);
			Ringbuff->OutBuffPointer+=Ringbuff->MemberSize;
		}
		else{
			memcpy(data,(u8*)Ringbuff->pBuff+Ringbuff->OutBuffPointer,Ringbuff->MemberSize);
			Ringbuff->OutBuffPointer+=Ringbuff->MemberSize;
		}
		if(Ringbuff->OutBuffPointer >= Ringbuff->totalByteSize)Ringbuff->OutBuffPointer=0;
		return RingbuffOpSucess;
	}
	else{
		Ringbuff->usedBytes=0;
		Ringbuff->inBuffPointer=0;
		Ringbuff->OutBuffPointer=0;
		Ringbuff->status=RingbuffEmpty;
		return RingbuffOpFailure;
	}
}
/********************************************************************
函数功能：从环形缓存读取N个字节保存到指定数据从
入口参数：Ringbuff缓存管理实例,*pBuff读出数据保存地址,readBytes 读取字节数量
返    回：无。
备    注：无。
********************************************************************/
#if 1
RingbuffOperateResult_t readNMemberFromRingbuff(RingbuffMgr_t *Ringbuff,void *pBuff,u16 readBytes)
{
	u16 i;
	if(Ringbuff->pBuff==NULL)return RingbuffOpNotInit;
	if(Ringbuff->usedBytes >= readBytes)
	{
		Ringbuff->usedBytes-=readBytes;			//
		Ringbuff->freeBytesSize+=readBytes;		//
		if(Ringbuff->clearEnableFlag==TRUE)
		{
			for(i=0;i<readBytes;i++)
			{
				memcpy((u8*)pBuff+i,(u8*)Ringbuff->pBuff+Ringbuff->OutBuffPointer,1);
				memset((u8*)Ringbuff->pBuff+Ringbuff->OutBuffPointer,0,1);
				Ringbuff->OutBuffPointer++;
				if(Ringbuff->OutBuffPointer >= Ringbuff->totalByteSize)Ringbuff->OutBuffPointer = 0;	
			}	
		}
		else
		{
			for(i=0;i<readBytes;i++)
			{
				memcpy((u8*)pBuff+i,(u8*)Ringbuff->pBuff+Ringbuff->OutBuffPointer,1);
				if(Ringbuff->OutBuffPointer>=Ringbuff->totalByteSize)Ringbuff->OutBuffPointer = 0;		
			}
		}
		if(Ringbuff->usedBytes == 0)
		{
			Ringbuff->usedBytes=0;
			Ringbuff->inBuffPointer=0;
			Ringbuff->OutBuffPointer=0;
			Ringbuff->status=RingbuffEmpty;
		}
		return RingbuffOpSucess;
	}
	else
	{
		return RingbuffOpFailure;
	}
}
#endif
/********************************************************************
函数功能：从环形缓存读取N个字节，保存到指定数组指定偏移量的位置
入口参数：Ringbuff缓存管理实例,*pBuff读出数据保存地址,offset读出数据保存到指定偏移量的数组，readSize目标读取数据的大小
返    回：无。
备    注：无。
********************************************************************/
#if 0
RingbuffOperateResult_t readNByteFromRingbuff2(RingbuffMgr_t *Ringbuff,u8 *pBuff,u8 offset,u16 readSize)
{
	u8 *pbuff;
	u16 i;
	if(Ringbuff->pBuff==NULL)return RingbuffOpNotInit;
	if(Ringbuff->usedBytes >= readSize)
	{
		Ringbuff->usedBytes-=readSize;
		Ringbuff->freeBytesSize+=readSize;
		pbuff=pBuff+offset;
		if(Ringbuff->clearEnableFlag==TRUE)
		{
			for(i=0;i<readSize;i++)
			{
				*pbuff++ = Ringbuff->pBuff[Ringbuff->OutBuffPointer];
				Ringbuff->pBuff[Ringbuff->OutBuffPointer++] = 0;
				if(Ringbuff->OutBuffPointer>=Ringbuff->totalByteSize)Ringbuff->OutBuffPointer = 0;		
			}	
		}
		else
		{
			for(i=0;i<readSize;i++)
			{
				*pbuff++ = Ringbuff->pBuff[Ringbuff->OutBuffPointer++];
				if(Ringbuff->OutBuffPointer>=Ringbuff->totalByteSize)Ringbuff->OutBuffPointer = 0;		
			}
		}
		
		return RingbuffOpSucess;
	}
	else
	{
		return RingbuffOpFailure;
	}
}
#endif
/********************************************************************
函数功能：从环形缓存读取全部字节
入口参数：Ringbuff缓存管理实例,*pBuff读出数据保存地址
返    回：读取到的字节数量
备    注：无。
********************************************************************/
#if 1
u16 readAllMemberFromRingbuff(RingbuffMgr_t *Ringbuff,void *pBuff)
{
	u16 i;
	//if(Ringbuff->pBuff==NULL)return RingbuffOpNotInit;//
	if(Ringbuff->usedBytes >0)
	{
		if(Ringbuff->clearEnableFlag==TRUE)
		{
			for(i=0;i<Ringbuff->usedBytes;i++)
			{
				memcpy((u8*)pBuff+i,(u8*)Ringbuff->pBuff+Ringbuff->OutBuffPointer,1);
				memset((u8*)Ringbuff->pBuff+Ringbuff->OutBuffPointer,0,1);
				Ringbuff->OutBuffPointer++;
				if(Ringbuff->OutBuffPointer >= Ringbuff->totalByteSize)Ringbuff->OutBuffPointer = 0;
				
				//*pBuff++ = Ringbuff->pBuff[Ringbuff->OutBuffPointer];
				//Ringbuff->pBuff[Ringbuff->OutBuffPointer++]=0;
				//if(Ringbuff->OutBuffPointer>=Ringbuff->totalByteSize)Ringbuff->OutBuffPointer=0;		
			}
		}
		else
		{
			for(i=0;i<Ringbuff->usedBytes;i++)
			{
				memcpy((u8*)pBuff+i,(u8*)Ringbuff->pBuff+Ringbuff->OutBuffPointer,1);
				Ringbuff->OutBuffPointer++;
				//*pBuff++ = Ringbuff->pBuff[Ringbuff->OutBuffPointer++];
				if(Ringbuff->OutBuffPointer>=Ringbuff->totalByteSize)Ringbuff->OutBuffPointer=0;		
			}
		}
		Ringbuff->usedBytes=0;
		Ringbuff->inBuffPointer=0;
		Ringbuff->OutBuffPointer=0;
		Ringbuff->freeBytesSize=Ringbuff->totalByteSize;
		Ringbuff->status=RingbuffEmpty;
		return i;
	}
	else
	{
		Ringbuff->usedBytes=0;
		Ringbuff->inBuffPointer=0;
		Ringbuff->OutBuffPointer=0;
		Ringbuff->status=RingbuffEmpty;
		return 0;
	}
}
#endif
/********************************************************************
函数功能：从环形缓存读取一个关键字---用于快速检测缓存数据与通信协议的关键字
入口参数：Ringbuff缓存管理实例,*keyWord读出数据保存地址，keyWordIndex关键字索引
返    回：缓存操作结果 RingbuffOperateResult_t 成功或者失败
备    注：
A、任意读函数均使缓存输出指针指向下一个待读数据的位置；
B、输入索引为缓存当前输出位置开始往前的偏移量，索引0即为下一个待读位置的值；
C、方向：只能往前指定偏移不可往后回滚读值---即只能往前取指定位置的值，但不影响正常读值函数的操作。
D、此函数只是读取一个指定位置的值，不改变缓存任何控制变量。
********************************************************************/
#if 0
RingbuffOperateResult_t read1KeyWordFromRingbuff(RingbuffMgr_t *Ringbuff,u8 *keyWord,u16 keyWordIndex)
{
	if(keyWordIndex <= Ringbuff->usedBytes)								//关键字索引位置必须是缓存内有数据的范围内
	{
		if(Ringbuff->OutBuffPointer + keyWordIndex >= Ringbuff->totalByteSize)
			*keyWord = Ringbuff->pBuff[Ringbuff->OutBuffPointer + keyWordIndex - Ringbuff->totalByteSize];
		else 
			*keyWord = Ringbuff->pBuff[Ringbuff->OutBuffPointer + keyWordIndex];
		return RingbuffOpSucess;
	}
	else
		return RingbuffOpFailure;
}
#endif
/********************************************************************
函数功能：从环形缓存读取三个关键字---用于快速检测缓存数据与通信协议的关键字
入口参数：Ringbuff缓存管理实例,*keyW1,*keyW2,*keyW3读出数据保存地址，keyW1index，keyW2index，keyW3index关键字索引
返    回：缓存操作结果 RingbuffOperateResult_t 成功或者失败
备    注：
A、任意读函数均使缓存输出指针指向下一个待读数据的位置；
B、输入索引为缓存当前输出位置开始往前的偏移量，索引0即为下一个待读位置的值；
C、方向：只能往前指定偏移不可往后回滚读值---即只能往前取指定位置的值，但不影响正常读值函数的操作。
D、此函数只是读取一个指定位置的值，不改变缓存任何控制变量。
********************************************************************/
#if 0
RingbuffOperateResult_t read3KeyWordFromRingbuff(RingbuffMgr_t *Ringbuff,u8 *keyW1,u8 *keyW2,u8 *keyW3,u16 keyW1index,u16 keyW2index,u16 keyW3index)
{
	if(keyW1index <= Ringbuff->usedBytes && keyW2index <= Ringbuff->usedBytes && keyW3index <= Ringbuff->usedBytes)
	{
		if(Ringbuff->OutBuffPointer + keyW1index>= Ringbuff->totalByteSize)
			*keyW1 = Ringbuff->pBuff[Ringbuff->OutBuffPointer + keyW1index - Ringbuff->totalByteSize];
		else 
			*keyW1 = Ringbuff->pBuff[Ringbuff->OutBuffPointer + keyW1index];
		
		if(Ringbuff->OutBuffPointer + keyW2index >= Ringbuff->totalByteSize)
			*keyW2 = Ringbuff->pBuff[Ringbuff->OutBuffPointer + keyW2index - Ringbuff->totalByteSize];
		else 
			*keyW2 = Ringbuff->pBuff[Ringbuff->OutBuffPointer + keyW2index];
		
		if(Ringbuff->OutBuffPointer + keyW3index >= Ringbuff->totalByteSize)
			*keyW3 = Ringbuff->pBuff[Ringbuff->OutBuffPointer + keyW3index - Ringbuff->totalByteSize];
		else 
			*keyW3 = Ringbuff->pBuff[Ringbuff->OutBuffPointer + keyW3index];
		return RingbuffOpSucess;
	}
	else
		return RingbuffOpFailure;
}
#endif
/********************************************************************
函数功能：从环形缓存读取三个关键字---用于快速检测缓存数据与通信协议的关键字
入口参数：Ringbuff缓存管理实例,*keyW1,*keyW2,*keyW3读出数据保存地址，keyW1index，keyW2index，keyW3index关键字索引
返    回：缓存操作结果 RingbuffOperateResult_t 成功或者失败
备    注：
A、任意读函数均使缓存输出指针指向下一个待读数据的位置；
B、输入索引为缓存当前输出位置开始往前的偏移量，索引0即为下一个待读位置的值；
C、方向：只能往前指定偏移不可往后回滚读值---即只能往前取指定位置的值，但不影响正常读值函数的操作。
D、此函数只是读取一个指定位置的值，不改变缓存任何控制变量。
格式：帧头 帧长（2B） 命令 命令反码 数据1...校验(2B) 帧尾
********************************************************************/
#if 0
RingbuffOperateResult_t readCmdFrameEndFromRingbuff(RingbuffMgr_t *Ringbuff,u8 *cmd,u8 *cmdRev,u8 *frameEnd,u16 FrameLength)
{
	if(FrameLength <= Ringbuff->usedBytes)
	{
		FrameLength-=1;
		if(Ringbuff->OutBuffPointer >= Ringbuff->totalByteSize)
			*cmd = Ringbuff->pBuff[Ringbuff->OutBuffPointer - Ringbuff->totalByteSize];
		else 
			*cmd = Ringbuff->pBuff[Ringbuff->OutBuffPointer];
		
		if(Ringbuff->OutBuffPointer + 1 >= Ringbuff->totalByteSize)
			*cmdRev = Ringbuff->pBuff[Ringbuff->OutBuffPointer + 1 - Ringbuff->totalByteSize];
		else 
			*cmdRev = Ringbuff->pBuff[Ringbuff->OutBuffPointer + 1];
		
		if(Ringbuff->OutBuffPointer + FrameLength >= Ringbuff->totalByteSize)
			*frameEnd = Ringbuff->pBuff[Ringbuff->OutBuffPointer + FrameLength - Ringbuff->totalByteSize];
		else 
			*frameEnd = Ringbuff->pBuff[Ringbuff->OutBuffPointer + FrameLength];
		return RingbuffOpSucess;
	}
	else
		return RingbuffOpFailure;
}
#endif
/********************************************************************
函数功能：写一个数据成员到环形缓存
入口参数：Ringbuff缓存管理实例，data写入数据
返    回：无。
备    注：无。
********************************************************************/
RingbuffOperateResult_t writeOneMemberToRingbuff(RingbuffMgr_t *Ringbuff,void *data)
{
	if(Ringbuff->pBuff==NULL)return RingbuffOpNotInit;
	if(Ringbuff->usedBytes<Ringbuff->totalByteSize)
	{
		Ringbuff->usedBytes+=Ringbuff->MemberSize;
		Ringbuff->freeBytesSize-=Ringbuff->MemberSize;
		memcpy((u8*)Ringbuff->pBuff+Ringbuff->inBuffPointer,data,Ringbuff->MemberSize);
		Ringbuff->inBuffPointer+=Ringbuff->MemberSize;
		
		if(Ringbuff->inBuffPointer>=Ringbuff->totalByteSize)Ringbuff->inBuffPointer=0;
		if(Ringbuff->usedBytes==Ringbuff->totalByteSize)Ringbuff->status=RingbuffFull;
		else Ringbuff->status=RingbuffNotFull;
		return RingbuffOpSucess;
	}
	else 
	{
		Ringbuff->status=RingbuffFull;
		return RingbuffOpFailure;
	}
}
/********************************************************************
函数功能：写N个成员到环形缓存
入口参数：Ringbuff缓存管理实例，pbuff待写入数据指针，writeSize待写数据大小
返    回：无。
备    注：无。
********************************************************************/
RingbuffOperateResult_t writeNMemberToRingbuff(RingbuffMgr_t *Ringbuff,void *pbuff,u16 WriteByteSize)
{
	u16 i;
	if(Ringbuff->pBuff==NULL)return RingbuffOpNotInit;
	if(Ringbuff->freeBytesSize >= WriteByteSize)	
	{
		Ringbuff->usedBytes  += WriteByteSize;
		Ringbuff->freeBytesSize -= WriteByteSize;
		for(i=0;i<WriteByteSize;i++)
		{
			memcpy((u8*)Ringbuff->pBuff+Ringbuff->inBuffPointer,(u8*)pbuff+i,1);
			Ringbuff->inBuffPointer++;
			if(Ringbuff->inBuffPointer >= Ringbuff->totalByteSize)Ringbuff->inBuffPointer = 0;		
		}
		if(Ringbuff->usedBytes==Ringbuff->totalByteSize)Ringbuff->status=RingbuffFull;
		else Ringbuff->status=RingbuffNotFull;
		return RingbuffOpSucess;
	}
	else 
	{
		Ringbuff->status=RingbuffFull;
		return RingbuffOpFailure;
	}
}

/********************************************************************
函数功能：计算缓存使用百分比值
入口参数：Ringbuff缓存管理实例
返    回：百分比值（0---100）。
备    注：无。
********************************************************************/
u8 CalRingbuffUsedPercent(RingbuffMgr_t *Ringbuff)
{
	u8 temp=0;
	u16 i,UseBytes=0;
	for(i=0;i<Ringbuff->totalByteSize;i++)
	{
		temp=*((u8*)Ringbuff->pBuff+i);
		if(temp!=RING_BUFF_WATERMARK)UseBytes++;
	}
	temp=(u8)((float)UseBytes*100/(float)Ringbuff->totalByteSize);
	//printf("ringbuff UseBytes %d totalByteSize=%d\r\n",UseBytes,Ringbuff->totalByteSize);
	Ringbuff->UsePercent=temp;
	return temp;
}
/********************************************************************
函数功能：打印缓存管理实例相关变量及缓存数据
入口参数：Ringbuff缓存管理实例，printDataFlag=TRUE时打印出缓存所有数据，每16字节一行，并标记行号
返    回：无。
备    注：无。
********************************************************************/
void printRingBuff(RingbuffMgr_t *Ringbuff,u8 printDataFlag)
{
	#ifdef DEBUG
		u16 i,line=0;
		printf(" ----------------------------------- \r\n");
		if(Ringbuff->pBuff==NULL)printf("ringbuff Ringbuff not init \r\n");
		printf("ringbuff UsePercent %d%% \r\n",Ringbuff->UsePercent);
		printf(" totalByteSize:%d usedBytes:%d freeBytesSize:%d ",
						Ringbuff->totalByteSize,Ringbuff->usedBytes,Ringbuff->freeBytesSize);
		printf(" inBuffPointer:%d OutBuffPointer:%d ",Ringbuff->inBuffPointer,Ringbuff->OutBuffPointer);
		if(Ringbuff->status==RingbuffEmpty)printf(" status:RingbuffEmpty \r\n");
		if(Ringbuff->status==RingbuffFull)printf(" status:RingbuffFull \r\n");
		if(Ringbuff->status==RingbuffNotFull)printf(" status:RingbuffNotFull \r\n");
		if(printDataFlag==TRUE)
		{
			printf(" -------------- ringbuf data -------------- \r\n");
			if(Ringbuff->MemberSize==1)
			{
				for(i=0;i<Ringbuff->totalByteSize;i++)
				{
					if(i%16==0)printf("\r\n line:%d ",line++);
					printf(" %02X",*((u8*)Ringbuff->pBuff+i));
				}
			}
			else if(Ringbuff->MemberSize==2)
			{
				for(i=0;i<Ringbuff->totalByteSize/Ringbuff->MemberSize;i++)
				{
					if(i%16==0)printf("\r\n line:%d ",line++);
					printf(" %04X",*((u16*)Ringbuff->pBuff+i));
				}
			}
			else if(Ringbuff->MemberSize==4)
			{
				for(i=0;i<Ringbuff->totalByteSize/Ringbuff->MemberSize;i++)
				{
					if(i%16==0)printf("\r\n line:%d ",line++);
					printf(" %08X",*((u32*)Ringbuff->pBuff+i));
				}
			}
			printf(" \r\n");
		}
	#endif
}
/********************************************************************
函数功能：
入口参数：无。
返    回：无。
备    注：无。
********************************************************************/
#if 0
#define U1_RXBUFF_SIZE	64
#define U1_TXBUFF_SIZE	32
RingbuffMgr_t u1RxBuffMgr,u1TxBuffMgr;
#define RING_BUFF_DATA_TYPE		u8
RING_BUFF_DATA_TYPE U1RXbuff[U1_RXBUFF_SIZE],U1TXbuff[U1_TXBUFF_SIZE];
void ringbuffTest(void)
{
	u8 UsePercent;
	RING_BUFF_DATA_TYPE i,data,buff[40];
	RING_BUFF_DATA_TYPE cmdline1[]={0x0A,0,10,0x12,0xab,1,2,3,4,5,6,7,0xDA};
	RING_BUFF_DATA_TYPE cmdline2[]={8,9,0x0A,0,8,0x15,0xEA,1,2,3,6,7,0xDA,5,6};
	u16 temp,FrameLength;
	ringbuffInit(&u1RxBuffMgr,U1RXbuff,sizeof(U1RXbuff),sizeof(RING_BUFF_DATA_TYPE),TRUE);
	ringbuffInit(&u1TxBuffMgr,U1TXbuff,sizeof(U1TXbuff),sizeof(RING_BUFF_DATA_TYPE),TRUE);
	writeNMemberToRingbuff(&u1RxBuffMgr,(void *)cmdline1,sizeof(cmdline1));
	writeNMemberToRingbuff(&u1RxBuffMgr,(void *)cmdline2,sizeof(cmdline2));
	data=0x56;i=0;
	printf(" ------------------ 流水缓存测试 1------------------\r\n");
	writeOneMemberToRingbuff(&u1RxBuffMgr,&data);
	printRingBuff(&u1RxBuffMgr,TRUE);
	while(readOneMemberFromRingbuff(&u1RxBuffMgr,&data)==RingbuffOpSucess)
	{
		printf(" %02X",data);i++;
		if(i%16==0)printf("\r\n");
	}
	printf("\r\n");
	UsePercent=CalRingbuffUsedPercent(&u1RxBuffMgr);
	printf("UsePercent=%d%%\r\n",UsePercent);
	printRingBuff(&u1RxBuffMgr,TRUE);
	printf(" ------------------ 流水缓存测试 2------------------\r\n");
}
#endif
//---------------------------------------------------------------------
#if 1
#define U1_RXBUFF_SIZE	64
#define U1_TXBUFF_SIZE	32
RingbuffMgr_t u1RxBuffMgr,u1TxBuffMgr;
#define RING_BUFF_DATA_TYPE		u32
RING_BUFF_DATA_TYPE U1RXbuff[U1_RXBUFF_SIZE],U1TXbuff[U1_TXBUFF_SIZE];
void ringbuffTest(void)
{
	//u8 keyWord1,keyWord2,keyWord3;
	//u8 para1,para2,cmd,cmdrev,frameEnd;
	RING_BUFF_DATA_TYPE i,data,buff[40];
	RING_BUFF_DATA_TYPE cmdline1[]={0x0A,0,10,0x12345678,0xabcdeeff,1,2,3,4,5,6,7,0xDA};
	RING_BUFF_DATA_TYPE cmdline2[]={8,9,0x0A,0,8,0x15,0xEA,1,2,3,6,7,0xDA,5,6};
	//RING_BUFF_DATA_TYPE cmdline1[]={0x0A,0,10,0x12,0xab,1,2,3,4,5,6,7,0xDA};
	//RING_BUFF_DATA_TYPE cmdline2[]={8,9,0x0A,0,8,0x15,0xEA,1,2,3,6,7,0xDA,5,6};
	u16 temp16A,temp16B,FrameLength;
	ringbuffInit(&u1RxBuffMgr,U1RXbuff,sizeof(U1RXbuff),sizeof(RING_BUFF_DATA_TYPE),TRUE);
	ringbuffInit(&u1TxBuffMgr,U1TXbuff,sizeof(U1TXbuff),sizeof(RING_BUFF_DATA_TYPE),TRUE);
	writeNMemberToRingbuff(&u1RxBuffMgr,(void *)cmdline1,sizeof(cmdline1));
	writeNMemberToRingbuff(&u1RxBuffMgr,(void *)cmdline2,sizeof(cmdline2));
	data=0x56781234;
	writeOneMemberToRingbuff(&u1RxBuffMgr,&data);
	printRingBuff(&u1RxBuffMgr,TRUE);
	i=0;
	temp16A=getRingbuffUseSize(&u1RxBuffMgr);
	printf(" UseSize=%d FreeSize=%d \r\n",temp16A,getRingbuffFreeSize(&u1RxBuffMgr));
	printf(" -----------------------------------\r\n");
	#if 0
	while(readOneMemberFromRingbuff(&u1RxBuffMgr,&data)==RingbuffOpSucess)
	{
		if(i%8==0 && i!=0)printf("\r\n");
		printf(" %08X",data);i++;
	}
	#endif
	#if 0
	temp16B=temp16A-sizeof(RING_BUFF_DATA_TYPE)*3;
	readNMemberFromRingbuff(&u1RxBuffMgr,buff,temp16B);
	for(i=0;i<temp16A/(u1RxBuffMgr.MemberSize);i++)
	{
		if(i%8==0 && i!=0)printf("\r\n");
		printf(" %08X",buff[i]);
	}
	#endif
	#if 1
	temp16A=readAllMemberFromRingbuff(&u1RxBuffMgr,buff);
	for(i=0;i<temp16A/(u1RxBuffMgr.MemberSize);i++)
	{
		if(i%8==0 && i!=0)printf("\r\n");
		printf(" %08X",buff[i]);
	}
	#endif
	printf(" \r\n-----------------------------------\r\n");
	CalRingbuffUsedPercent(&u1RxBuffMgr);
	printRingBuff(&u1RxBuffMgr,TRUE);
	#if 0
	//-----------------------------------------
	//printRingBuff(&u1RxBuffMgr,TRUE);
	for(i=0;i<60;i++)writeOneByteToRingbuff(&u1RxBuffMgr ,i+5);	
	printRingBuff(&u1RxBuffMgr,TRUE);
	printf(" \r\n--------read 4 Byte------------ \r\n");
	for(i=0;i<4;i++)
	{
		if(readOneByteFromRingbuff(&u1RxBuffMgr,&data)!=RingbuffOpFailure)
			printf(" %02X",data);
	}
	printRingBuff(&u1RxBuffMgr,TRUE);
	printf(" \r\n--------read 10 Byte------------ \r\n");
	for(i=0;i<10;i++)
	{
		if(readOneByteFromRingbuff(&u1RxBuffMgr,&data)==RingbuffOpFailure)
			printf(" RingbuffOpFailure \r\n");
		printf(" %02X",data);
	}
	
	setRingbuffClearFlag(&u1RxBuffMgr,TRUE);
	
	printRingBuff(&u1RxBuffMgr,TRUE);
	printf(" \r\n--------read 20 Byte------------ \r\n");
	temp=readNByteFromRingbuff(&u1RxBuffMgr,buff,20);
	for(i=0;i<20;i++)printf(" %02X",buff[i]);
	printRingBuff(&u1RxBuffMgr,TRUE);
	
	setRingbuffClearFlag(&u1RxBuffMgr,FALSE);
	
	printf(" \r\n--------read all Byte------------ \r\n");
	temp=readAllByteFromRingbuff(&u1RxBuffMgr,buff);
	for(i=0;i<temp;i++)printf(" %02X",buff[i]);
	printRingBuff(&u1RxBuffMgr,TRUE);
	printf("temp:%d",temp);
	
	printf(" -------------------- \r\n");
	
	printf("\r\n --------Write 20 Byte------------ \r\n");
	for(i=0;i<20;i++)writeOneByteToRingbuff(&u1RxBuffMgr ,i+100);	
	printRingBuff(&u1RxBuffMgr,TRUE);
	
	printf(" \r\n--------read 10 Byte------------ \r\n");
	temp=readNByteFromRingbuff(&u1RxBuffMgr,buff,10);
	for(i=0;i<10;i++)printf(" %02X",buff[i]);
	printRingBuff(&u1RxBuffMgr,TRUE);
	printf(" \r\n -------------------- \r\n");	
	#endif
	//-----------------------------------------
	#if 0
	for(i=0;i<sizeof(cmdline1);i++)writeOneByteToRingbuff(&u1RxBuffMgr ,cmdline1[i]);
	writeNByteToRingbuff(&u1RxBuffMgr ,cmdline2,sizeof(cmdline2));
	printRingBuff(&u1RxBuffMgr,TRUE);
	setRingbuffClearFlag(&u1RxBuffMgr,TRUE);
	while(1)
	{
		if(readOneByteFromRingbuff(&u1RxBuffMgr,&data)==RingbuffOpSucess)
			if(data==0x0A)
			{
				readOneByteFromRingbuff(&u1RxBuffMgr,&data);FrameLength = (data<<8);
				readOneByteFromRingbuff(&u1RxBuffMgr,&data);FrameLength += data;
				break;
			}
	}
	read3KeyWordFromRingbuff(&u1RxBuffMgr,&keyWord1,&keyWord2,&keyWord3,0,1,FrameLength-1);
	readCmdFrameEndFromRingbuff(&u1RxBuffMgr,&cmd,&cmdrev,&frameEnd,FrameLength);
	printRingBuff(&u1RxBuffMgr,TRUE);
	printf(" keyWord1:%02X keyWord2:%02X keyWord3:%02X \r\n",keyWord1,keyWord2,keyWord3);
	printf(" cmd:%02X cmdrev:%02X frameEnd:%02X \r\n",cmd,cmdrev,frameEnd);
	printf(" \r\n-------------------- \r\n");
	
	while(1)
	{
		if(readOneByteFromRingbuff(&u1RxBuffMgr,&data)==RingbuffOpSucess)
			if(data==0x0A)
			{
				readOneByteFromRingbuff(&u1RxBuffMgr,&data);FrameLength = (data<<8);
				readOneByteFromRingbuff(&u1RxBuffMgr,&data);FrameLength += data;
				break;
			}
	}
	read3KeyWordFromRingbuff(&u1RxBuffMgr,&keyWord1,&keyWord2,&keyWord3,0,1,FrameLength-1);
	readCmdFrameEndFromRingbuff(&u1RxBuffMgr,&cmd,&cmdrev,&frameEnd,FrameLength);
	printRingBuff(&u1RxBuffMgr,TRUE);
	printf(" keyWord1:%02X keyWord2:%02X keyWord3:%02X \r\n",keyWord1,keyWord2,keyWord3);
	printf(" cmd:%02X cmdrev:%02X frameEnd:%02X \r\n",cmd,cmdrev,frameEnd);
	printf(" \r\n-------------------- \r\n");	
	
	
	printf(" \r\n--------read all Byte------------ \r\n");
	temp=readAllByteFromRingbuff(&u1RxBuffMgr,buff);
	for(i=0;i<temp;i++)printf(" %02X",buff[i]);
	printRingBuff(&u1RxBuffMgr,TRUE);
	printf("temp:%d",temp);
	
	
	#endif
	
	//-----------------------------------------
}
#endif










