/**
  ******************************************************************************
  * @file    FaultInfo.c 
  * @author  西小岑
  * @version V1.0.0
  * @date    2020.07.12
  * @brief   FaultInfo manage module
  ******************************************************************************
  * @attention
  Copyright (c) 2020 --- 2025 西小岑. All rights reserved.
  声明：
  1、此模块（FaultInfo），作者（西小岑）保留所有权限
  2、此模块仅供参考学习、研究、交流使用
  3、如用于商业目的，需要征求作者同意
  4、作者仅提供源代码，可以从“github.com”上下载，但不限于此渠道
  5、对此模块的使用请自行验证、测试、
  6、对于使用本模块造成的任何损失，作者（西小岑）不承担任何责任。
  7、如将此模块集成于你的代码中，必须保留此声明
  8、如不同意上述条款，请不要使用此模块
  ******************************************************************************
**/

#include "includes.h"


static u16 FaultParaBaseYear=FAULT_PARA_BASE_YEAR;

#if 1
/********************************************************************
函数功能：设置基准年份
入口参数：无。
返    回：无。
备    注：无。
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
函数功能：设置故障码发生的时间
入口参数：无。
返    回：无。
备    注：无。
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
函数功能：设置与获取故障码状态
入口参数：无。
返    回：无。
备    注：无。
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
函数功能：设置与获取故障码类型及其故障码值
入口参数：无。
返    回：无。
备    注：无。
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
函数功能：打印故障信息
入口参数：无。
返    回：无。
备    注：无。
********************************************************************/
void PrintFaultInfo(FaultInfo_t *FaultInfo,u16 NodeNum)
{
	printf(" NodeNum %d--- 错误码信息 --- ",NodeNum);
	if(FaultInfo->F.Status==FAULT_STATUS_ACTIVE)
	{
		printf(" 状态->激活 ");
	}	
	else 
	{
		printf(" 状态->冻结 ");
	}
	printf(" Type =%d SubType=%d Num=%XH ",FaultInfo->F.Type,FaultInfo->F.SubType,FaultInfo->F.Num);
	printf(" %d-%d-%d %d:%d:%d\r\n",FaultParaBaseYear+FaultInfo->F.Year,FaultInfo->F.Month,FaultInfo->F.Day,FaultInfo->F.Hour,FaultInfo->F.Minutes,FaultInfo->F.Second);
}
#endif



