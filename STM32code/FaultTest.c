/**
  ******************************************************************************
  * @file    ringbuff.h 
  * @author  ��С�
  * @version V1.2.0
  * @date    2019.12.25
  * @brief   ringbuff manage module
  ******************************************************************************
  * @attention
  Copyright (c) 2020 --- 2025 ��С�. All rights reserved.
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

#include "includes.h"




//���	����	������	����ֵ	����			ά������		��ע
//1		0		2		1		ˮλ��������ֵ	��ˮ			���ˮλ
//2		0		2		2		ˮ����������ֵ	��ˮ���ˮ��	
//3		0		2		3		�ⷧ��ʧ��	���ⷧ���	��λ����
//4		0		2		4		�ⷧ�ر�ʧ��	���ⷧ���	��λ����
//5		0		2		5		650nm��׼����Ч	���650������	
//6		0		2		6		ˮ�¸�����ֵ	�������ϵͳ	
//7		0		2		7		���Է��ȹ���	�����Է���	����ʱ��鷴���ź�
//8		0		2		8		������������ֵ	�������	

void printFaultInfo(u8 Active,u8 Type,u8 SubType,u32 FaultVal)
{
	printf(" --- ��������Ϣ --- ");
	if(Active==FAULT_STATUS_ACTIVE)
	{
		printf(" ״̬->���� ");
	}	
	else 
	{
		printf(" ״̬->���� ");
	}
	if(Type==0)
	{
		printf(" ������� ");
	}	
	else 
	{
		printf(" Ӳ������ ");
	}
	switch(FaultVal)
	{
		case 1:	printf("FaultVal=%d ˮλ��������ֵ,���ˮ\r\n ",FaultVal);
			break;
		case 2:	printf("FaultVal=%d ˮ����������ֵ,���ˮ���ˮ��\r\n ",FaultVal);
			break;
		case 3:	printf("FaultVal=%d �ⷧ��ʧ��,����ⷧ���\r\n ",FaultVal);
			break;
		case 4:	printf("FaultVal=%d �ⷧ�ر�ʧ��,����ⷧ���\r\n ",FaultVal);
			break;
		case 5:	printf("FaultVal=%d 650nm��׼����Ч,����650������\r\n ",FaultVal);
			break;
		case 6:	printf("FaultVal=%d ˮ�¸�����ֵ,��������ϵͳ\r\n ",FaultVal);
			break;
		case 7:	printf("FaultVal=%d ���Է��ȹ���,������Է���\r\n ",FaultVal);
			break;
		case 8:	printf("FaultVal=%d ������������ֵ,��������\r\n ",FaultVal);
			break;
		default:printf(" δ�������ֵ \r\n ");
			break;
	}
}
void printDecodeFaultInfo(FaultInfo_t *pFaultInfo)
{
	printf(" --- ��������Ϣ --- ");
	if(pFaultInfo->F.Status==FAULT_STATUS_ACTIVE)
	{
		printf(" ״̬->���� ");
	}	
	else 
	{
		printf(" ״̬->���� ");
	}
	if(pFaultInfo->F.Type==0)
	{
		printf(" ����->������� ");
	}	
	else 
	{
		printf(" ����->Ӳ������ ");
	}
	if(pFaultInfo->F.SubType==0)
	{
		printf(" ������->δ���� ");
	}	
	else if(pFaultInfo->F.SubType==1)
	{
		printf(" ������->��Դ���� ");
	}
	else if(pFaultInfo->F.SubType==2)
	{
		printf(" ������->���ذ���� ");
	}
	switch(pFaultInfo->F.Num)
	{
		case 1:	printf("FaultVal=%d ˮλ��������ֵ,���ˮ \t\t\t",pFaultInfo->F.Num);
			break;
		case 2:	printf("FaultVal=%d ˮ����������ֵ,���ˮ���ˮ�� \t\t",pFaultInfo->F.Num);
			break;
		case 3:	printf("FaultVal=%d �ⷧ��ʧ��,����ⷧ��� \t\t",pFaultInfo->F.Num);
			break;
		case 4:	printf("FaultVal=%d �ⷧ�ر�ʧ��,����ⷧ��� \t\t",pFaultInfo->F.Num);
			break;
		case 5:	printf("FaultVal=%d 650nm��׼����Ч,����650������ \t\t",pFaultInfo->F.Num);
			break;
		case 6:	printf("FaultVal=%d ˮ�¸�����ֵ,��������ϵͳ \t\t",pFaultInfo->F.Num);
			break;
		case 7:	printf("FaultVal=%d ���Է��ȹ���,������Է��� \t\t",pFaultInfo->F.Num);
			break;
		case 8:	printf("FaultVal=%d ������������ֵ,�������� \t\t",pFaultInfo->F.Num);
			break;
		default:printf(" δ�������ֵ  \t\t");
			break;
	}
	printf(" %d-%d-%d %d:%d:%d\r\n",GetFaultInfoBaseYear()+pFaultInfo->F.Year,pFaultInfo->F.Month,pFaultInfo->F.Day,pFaultInfo->F.Hour,pFaultInfo->F.Minutes,pFaultInfo->F.Second);
}
/********************************************************************
�������ܣ�������Թ�����
��ڲ������ޡ�
��    �أ��ޡ�
��    ע���ޡ�
********************************************************************/
List_t *FaultCodelist;							//�������������ָ��
void FaultCodeTest(void)
{
	int i;
	u16 NodeNum=0;
	u8 minutes=20,second=10;
	FaultInfo_t *pFaultInfo;					//���������Ϣָ��							
	FaultCodelist = ListCreate();				//��������
	#if 1 // -------- ��ӽڵ㣨�����룩 --------
		for(i=0; i<8; i++)
		{
			pFaultInfo=malloc(sizeof(FaultInfo_t));					//�����ڴ�
			SetFaultInfoTime(pFaultInfo,20 ,7 ,12 ,17,minutes+i,second+i);		//���ù�����ʱ�䣺������ʱ����
			SetFaultInfoStatus(pFaultInfo,FAULT_STATUS_ACTIVE);		//���ù���״̬������
			SetFaultInfoPara(pFaultInfo ,0,2,i+1);					//���ù����룺���ͣ������ͣ�����ֵ1--8
			ListBackAddNode(FaultCodelist, pFaultInfo,NodeNum++);	//��������Ϣ��ӵ�������
		}
	#endif	
	#if 1 // -------- ���������Ϣ --------
		NodeNum=0;
		for(i=0; i<10; i++)
		{
			pFaultInfo=listFindNodeFromBegin2(FaultCodelist,NodeNum);
			if(pFaultInfo!=NULL)
			{
				PrintFaultInfo(pFaultInfo,NodeNum);				//��ӡ������Ϣ
			}
			else
			{
				printf(" Node %d Not Exist \r\n",NodeNum);
			}
			NodeNum++;
		}
	#endif
	#if 1 // -------- ���������Ϣ --------
		NodeNum=0;
		for(i=0; i<10; i++)
		{
			pFaultInfo=listFindNodeFromBegin2(FaultCodelist,NodeNum);
			if(pFaultInfo!=NULL)
			{
				printDecodeFaultInfo(pFaultInfo);
			}
			else
			{
				printf(" Node %d Not Exist \r\n",NodeNum);
			}
			NodeNum++;
		}
	#endif	
}