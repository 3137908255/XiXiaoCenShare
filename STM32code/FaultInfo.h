/**
  ******************************************************************************
  * @file    FaultInfo.h 
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
#ifndef FAULT_INFO_H
#define FAULT_INFO_H

#include "includes.h"

#define FAULT_PARA_BASE_YEAR			2000	//��׼���
#define FAULT_STATUS_INACTIVE			0		//����
#define FAULT_STATUS_ACTIVE				1		//����

typedef union
{
	u64 Data;
	struct
	{
		u64 Second:6;					//0---63��
		u64 Minutes:6;					//0---63��
		u64	Hour:5;						//0---31ʱ
		u64 Day:5;						//0---31��
		u64 Month:4;					//0---15��
		u64 Year:6;						//0---63��
		u64	Num:24;						//0---16777215	�����ţ�0��Ч���Ϻţ�		
		u64 SubType:6;					//0---63������
		u64 Type:1;						//0---1�������ͣ�0������ϣ�1Ӳ������
		u64 Status:1;					//0---1����״̬��0���ᣨInactive����1���Active��
	}F;
}FaultInfo_t;

typedef union
{
	u64 Data;
	struct
	{
		u64 Second:6;		//0---63��
		u64 Minutes:6;		//0---63��
		u64	Hour:5;			//0---31ʱ
		u64 Day:5;			//0---31��
		u64 Month:4;		//0---15��
		u64 Year:12;		//0---4095��
		u64	Num:17;			//0---131071	�����ţ�0��Ч���Ϻţ�		
		u64 SubType:6;		//0---63������
		u64 Type:2;			//0---1�������ͣ�0������ϣ�1Ӳ������,2Ӧ����ͼ���ϣ����糬���ֵ�����£�
		u64 Status:1;		//0---1����״̬��0���ᣨInactive����1���Active��
	}F;
}FaultInfo_t2;



//���û�׼���
void SetFaultInfoBaseYear(u16 Year);
u16 GetFaultInfoBaseYear(void);
//���ù����뷢����ʱ��
void SetFaultInfoYMD(FaultInfo_t *FaultInfo,u8 Year ,u8 Month ,u8 Day);
void SetFaultInfoHMS(FaultInfo_t *FaultInfo,u8 Hour,u8 Minutes,u8 Second);
void SetFaultInfoTime(FaultInfo_t *FaultInfo,u8 Year ,u8 Month ,u8 Day ,u8 Hour,u8 Minutes,u8 Second);
//�������ȡ������״̬
void SetFaultInfoStatus(FaultInfo_t *FaultInfo,u8 Status);
u8 GetFaultInfoStatus(FaultInfo_t *FaultInfo);
//�������ȡ���������ͼ��������ֵ
void SetFaultInfoPara(FaultInfo_t *FaultInfo,u8 Type,u8 SubType,u32 Num);
u8 GetFaultInfoPara(FaultInfo_t *FaultInfo,u8 *Type,u8 *SubType,u32 *Num);
//��ӡ������Ϣ
void PrintFaultInfo(FaultInfo_t *FaultInfo,u16 NodeNum);


#endif 



