/**
  ******************************************************************************
  * @file    FaultInfo.c 
  * @author  ��С�
  * @version V1.0.0
  * @date    2020.07.12
  * @brief   FaultInfo manage module
  ******************************************************************************
  * @attention
  Copyright (c) 2020 --- 2025 ��С�. All rights reserved.
  ������
  1����ģ�飨FaultInfo�������ߣ���Сᯣ���������Ȩ��
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


static u16 FaultParaBaseYear=FAULT_PARA_BASE_YEAR;

#if 1
/********************************************************************
�������ܣ����û�׼���
��ڲ������ޡ�
��    �أ��ޡ�
��    ע���ޡ�
********************************************************************/
void SetFaultInfoBaseYear(u16 Year)
{
	FaultParaBaseYear=Year;
}
u16 GetFaultInfoBaseYear(void)
{
	return FaultParaBaseYear;
}
/********************************************************************
�������ܣ����ù����뷢����ʱ��
��ڲ������ޡ�
��    �أ��ޡ�
��    ע���ޡ�
********************************************************************/
void SetFaultInfoYMD(FaultInfo_t *FaultInfo,u8 Year ,u8 Month ,u8 Day)
{
	if(Year>63)Year=63;
	if(Month>12)Month=12;
	if(Day>31)Day=31;
	FaultInfo->F.Year=Year;
	FaultInfo->F.Month=Month;
	FaultInfo->F.Day=Day;

}
void SetFaultInfoHMS(FaultInfo_t *FaultInfo,u8 Hour,u8 Minutes,u8 Second)
{
	if(Hour>24)Hour=24;
	if(Minutes>59)Minutes=59;
	if(Second>59)Second=59;
	FaultInfo->F.Hour=Hour;
	FaultInfo->F.Minutes=Minutes;
	FaultInfo->F.Second=Second;
}
void SetFaultInfoTime(FaultInfo_t *FaultInfo,u8 Year ,u8 Month ,u8 Day ,u8 Hour,u8 Minutes,u8 Second)
{
	if(Year>63)Year=63;
	if(Month>12)Month=12;
	if(Day>31)Day=31;
	if(Hour>24)Hour=24;
	if(Minutes>59)Minutes=59;
	if(Second>59)Second=59;
	FaultInfo->F.Year=Year;
	FaultInfo->F.Month=Month;
	FaultInfo->F.Day=Day;
	FaultInfo->F.Hour=Hour;
	FaultInfo->F.Minutes=Minutes;
	FaultInfo->F.Second=Second;
}
/********************************************************************
�������ܣ��������ȡ������״̬
��ڲ������ޡ�
��    �أ��ޡ�
��    ע���ޡ�
********************************************************************/
void SetFaultInfoStatus(FaultInfo_t *FaultInfo,u8 Status)
{
	if(Status>FAULT_STATUS_ACTIVE)Status=FAULT_STATUS_ACTIVE;
	FaultInfo->F.Status=Status;
}
u8 GetFaultInfoStatus(FaultInfo_t *FaultInfo)
{
	return FaultInfo->F.Status;
}
/********************************************************************
�������ܣ��������ȡ���������ͼ��������ֵ
��ڲ������ޡ�
��    �أ��ޡ�
��    ע���ޡ�
********************************************************************/
void SetFaultInfoPara(FaultInfo_t *FaultInfo,u8 Type,u8 SubType,u32 Num)
{
	if(Type>1)Type=1;
	if(Num>0x00ffffff)Num=0x00ffffff;
	if(SubType>0x3F)SubType=0x3F;
	FaultInfo->F.Type=Type;
	FaultInfo->F.SubType=SubType;
	FaultInfo->F.Num=Num;
}
u8 GetFaultInfoPara(FaultInfo_t *FaultInfo,u8 *Type,u8 *SubType,u32 *Num)
{
	*Type=FaultInfo->F.Type;
	*SubType=FaultInfo->F.SubType;
	*Num=FaultInfo->F.Num;
	return FaultInfo->F.Status;
}
/********************************************************************
�������ܣ���ӡ������Ϣ
��ڲ������ޡ�
��    �أ��ޡ�
��    ע���ޡ�
********************************************************************/
void PrintFaultInfo(FaultInfo_t *FaultInfo,u16 NodeNum)
{
	printf(" NodeNum %d--- ��������Ϣ --- ",NodeNum);
	if(FaultInfo->F.Status==FAULT_STATUS_ACTIVE)
	{
		printf(" ״̬->���� ");
	}	
	else 
	{
		printf(" ״̬->���� ");
	}
	printf(" Type =%d SubType=%d Num=%XH ",FaultInfo->F.Type,FaultInfo->F.SubType,FaultInfo->F.Num);
	printf(" %d-%d-%d %d:%d:%d\r\n",FaultParaBaseYear+FaultInfo->F.Year,FaultInfo->F.Month,FaultInfo->F.Day,FaultInfo->F.Hour,FaultInfo->F.Minutes,FaultInfo->F.Second);
}
#endif



