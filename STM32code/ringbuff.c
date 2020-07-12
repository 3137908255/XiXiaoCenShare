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
  * �������ͻ��ڡ�DataType.h������
  * ��ģ����Ӳ���޹ء�����������޹ء���һ����ɶ�����ģ�飬��Ϊһ���м�������������
  * ����������ģ�飬��Ҫ�ṩһ������Ĺ����ܣ�˼·�ǽ�һ��һά���ݻ�����֯��һ�����ε��߼��ṹ��
  * ��Ҫ���ܣ�
  * A����ʼ����������������������뻺��Խ�����
  * B���򻺴�д�����ݣ��������ֽ�����ֽ����ַ�����
  * C���ӻ����ȡ���ݣ�������ȡ���ֽڡ����ֽ���ȫ��������
  * D����ѯ����״̬������գ�������������ǿ�
  * E����ѯ������пռ��С
  * F����ѯ����ʹ������������װ�ж������ݣ�
  * G�����軺��������������������ָ�����ʼ״̬��
  * ------------------------------------------------------------
  * 
  * 
  * ------------------------------------------------------------
  * ע�⣺
  * 1����ģ���������ܹ��������˼·����ģ��Ϊ�м�㣩
  * 2��������ƣ���ȡ����֮�󻺴��Ƿ�������ܿ�---������߲����㣨����ԭ�����ݣ�֮���ɺ���д��������滻��
  * 3��������֮���޷�д���µ����ݣ������ȡ�����е����ݻ��߸�λ��ʵ��
  * ------------------------------------------------------------
  * �ϲ�Ͳ���ú���
  * GetRingbuffFreeSize();GetRingbuffStatus();
  * ------------------------------------------------------------
  * �ϲ���ú�����
  * GetRingbuffUseSize();resetRingBuff();
  * readOneByteFromRingbuff();readNByteFromRingbuff();readAllByteFromRingbuff();
  * read1KeyWordFromRingbuff();read3KeyWordFromRingbuff()
  * �Ͳ���ú�����
  * RingbuffInit();writeOneByteToRingbuff();writeNByteToRingbuff();
  * ------------------------------------------------------------
  ******************************************************************************
*/
#include "includes.h"
/********************************************************************
�������ܣ���ʼ�����λ���ʵ��
��ڲ�����Ringbuff�������ʵ����buff�����ַ��BuffByteSize�����С,MemberSize�����Ա��С 
clearFlag�����־����ȡ����֮���Ƿ����㻺�棩
��    �أ��ޡ�
��    ע���ޡ�
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
�������ܣ���ȡ���λ���״̬
��ڲ������ޡ�
��    �أ��ޡ�
��    ע���ޡ�
********************************************************************/
u8 getRingbuffStatus(RingbuffMgr_t *Ringbuff)
{
	return Ringbuff->status;
}
/********************************************************************
�������ܣ���ȡ���λ������ݴ�С
��ڲ������ޡ�
��    �أ��ޡ�
��    ע���ޡ�
********************************************************************/
u16 getRingbuffUseSize(RingbuffMgr_t *Ringbuff)
{
	return Ringbuff->usedBytes;
}
/********************************************************************
�������ܣ���ȡ���λ���ʣ��ռ��С
��ڲ������ޡ�
��    �أ��ޡ�
��    ע���ޡ�
********************************************************************/
u16 getRingbuffFreeSize(RingbuffMgr_t *Ringbuff)
{
	return Ringbuff->freeBytesSize;
}
/********************************************************************
�������ܣ����ö�ȡ��������֮���Ƿ����㻺�����ݵı�־
��ڲ�����flag=TRUEʱ��ȡ�������������Ӧ���棬��������
��    �أ��ޡ�
��    ע���ޡ�
********************************************************************/
void setRingbuffClearFlag(RingbuffMgr_t *Ringbuff,u8 flag)
{
	Ringbuff->clearEnableFlag=flag;
}
/********************************************************************
�������ܣ���ȡ���λ���ʣ��ռ��С
��ڲ������ޡ�
��    �أ��ޡ�
��    ע���ޡ�
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
�������ܣ��ӻ��λ����ȡһ����Ա����
��ڲ�����Ringbuff�������ʵ��,*data�������ݱ����ַ
���أ�RingbuffOpFailure����RingbuffOpSucess
��    ע���ޡ�
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
�������ܣ��ӻ��λ����ȡN���ֽڱ��浽ָ�����ݴ�
��ڲ�����Ringbuff�������ʵ��,*pBuff�������ݱ����ַ,readBytes ��ȡ�ֽ�����
��    �أ��ޡ�
��    ע���ޡ�
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
�������ܣ��ӻ��λ����ȡN���ֽڣ����浽ָ������ָ��ƫ������λ��
��ڲ�����Ringbuff�������ʵ��,*pBuff�������ݱ����ַ,offset�������ݱ��浽ָ��ƫ���������飬readSizeĿ���ȡ���ݵĴ�С
��    �أ��ޡ�
��    ע���ޡ�
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
�������ܣ��ӻ��λ����ȡȫ���ֽ�
��ڲ�����Ringbuff�������ʵ��,*pBuff�������ݱ����ַ
��    �أ���ȡ�����ֽ�����
��    ע���ޡ�
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
�������ܣ��ӻ��λ����ȡһ���ؼ���---���ڿ��ټ�⻺��������ͨ��Э��Ĺؼ���
��ڲ�����Ringbuff�������ʵ��,*keyWord�������ݱ����ַ��keyWordIndex�ؼ�������
��    �أ����������� RingbuffOperateResult_t �ɹ�����ʧ��
��    ע��
A�������������ʹ�������ָ��ָ����һ���������ݵ�λ�ã�
B����������Ϊ���浱ǰ���λ�ÿ�ʼ��ǰ��ƫ����������0��Ϊ��һ������λ�õ�ֵ��
C������ֻ����ǰָ��ƫ�Ʋ�������ع���ֵ---��ֻ����ǰȡָ��λ�õ�ֵ������Ӱ��������ֵ�����Ĳ�����
D���˺���ֻ�Ƕ�ȡһ��ָ��λ�õ�ֵ�����ı仺���κο��Ʊ�����
********************************************************************/
#if 0
RingbuffOperateResult_t read1KeyWordFromRingbuff(RingbuffMgr_t *Ringbuff,u8 *keyWord,u16 keyWordIndex)
{
	if(keyWordIndex <= Ringbuff->usedBytes)								//�ؼ�������λ�ñ����ǻ����������ݵķ�Χ��
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
�������ܣ��ӻ��λ����ȡ�����ؼ���---���ڿ��ټ�⻺��������ͨ��Э��Ĺؼ���
��ڲ�����Ringbuff�������ʵ��,*keyW1,*keyW2,*keyW3�������ݱ����ַ��keyW1index��keyW2index��keyW3index�ؼ�������
��    �أ����������� RingbuffOperateResult_t �ɹ�����ʧ��
��    ע��
A�������������ʹ�������ָ��ָ����һ���������ݵ�λ�ã�
B����������Ϊ���浱ǰ���λ�ÿ�ʼ��ǰ��ƫ����������0��Ϊ��һ������λ�õ�ֵ��
C������ֻ����ǰָ��ƫ�Ʋ�������ع���ֵ---��ֻ����ǰȡָ��λ�õ�ֵ������Ӱ��������ֵ�����Ĳ�����
D���˺���ֻ�Ƕ�ȡһ��ָ��λ�õ�ֵ�����ı仺���κο��Ʊ�����
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
�������ܣ��ӻ��λ����ȡ�����ؼ���---���ڿ��ټ�⻺��������ͨ��Э��Ĺؼ���
��ڲ�����Ringbuff�������ʵ��,*keyW1,*keyW2,*keyW3�������ݱ����ַ��keyW1index��keyW2index��keyW3index�ؼ�������
��    �أ����������� RingbuffOperateResult_t �ɹ�����ʧ��
��    ע��
A�������������ʹ�������ָ��ָ����һ���������ݵ�λ�ã�
B����������Ϊ���浱ǰ���λ�ÿ�ʼ��ǰ��ƫ����������0��Ϊ��һ������λ�õ�ֵ��
C������ֻ����ǰָ��ƫ�Ʋ�������ع���ֵ---��ֻ����ǰȡָ��λ�õ�ֵ������Ӱ��������ֵ�����Ĳ�����
D���˺���ֻ�Ƕ�ȡһ��ָ��λ�õ�ֵ�����ı仺���κο��Ʊ�����
��ʽ��֡ͷ ֡����2B�� ���� ����� ����1...У��(2B) ֡β
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
�������ܣ�дһ�����ݳ�Ա�����λ���
��ڲ�����Ringbuff�������ʵ����dataд������
��    �أ��ޡ�
��    ע���ޡ�
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
�������ܣ�дN����Ա�����λ���
��ڲ�����Ringbuff�������ʵ����pbuff��д������ָ�룬writeSize��д���ݴ�С
��    �أ��ޡ�
��    ע���ޡ�
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
�������ܣ����㻺��ʹ�ðٷֱ�ֵ
��ڲ�����Ringbuff�������ʵ��
��    �أ��ٷֱ�ֵ��0---100����
��    ע���ޡ�
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
�������ܣ���ӡ�������ʵ����ر�������������
��ڲ�����Ringbuff�������ʵ����printDataFlag=TRUEʱ��ӡ�������������ݣ�ÿ16�ֽ�һ�У�������к�
��    �أ��ޡ�
��    ע���ޡ�
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
�������ܣ�
��ڲ������ޡ�
��    �أ��ޡ�
��    ע���ޡ�
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
	printf(" ------------------ ��ˮ������� 1------------------\r\n");
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
	printf(" ------------------ ��ˮ������� 2------------------\r\n");
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










