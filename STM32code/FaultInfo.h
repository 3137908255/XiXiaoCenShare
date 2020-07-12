/**
  ******************************************************************************
  * @file    FaultInfo.h 
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
#ifndef FAULT_INFO_H
#define FAULT_INFO_H

#include "includes.h"

#define FAULT_PARA_BASE_YEAR			2000	//基准年份
#define FAULT_STATUS_INACTIVE			0		//冻结
#define FAULT_STATUS_ACTIVE				1		//激活

typedef union
{
	u64 Data;
	struct
	{
		u64 Second:6;					//0---63秒
		u64 Minutes:6;					//0---63分
		u64	Hour:5;						//0---31时
		u64 Day:5;						//0---31日
		u64 Month:4;					//0---15月
		u64 Year:6;						//0---63年
		u64	Num:24;						//0---16777215	错误编号（0无效故障号）		
		u64 SubType:6;					//0---63子类型
		u64 Type:1;						//0---1错误类型：0软件故障，1硬件故障
		u64 Status:1;					//0---1错误状态：0冻结（Inactive），1激活（Active）
	}F;
}FaultInfo_t;

typedef union
{
	u64 Data;
	struct
	{
		u64 Second:6;		//0---63秒
		u64 Minutes:6;		//0---63分
		u64	Hour:5;			//0---31时
		u64 Day:5;			//0---31日
		u64 Month:4;		//0---15月
		u64 Year:12;		//0---4095年
		u64	Num:17;			//0---131071	错误编号（0无效故障号）		
		u64 SubType:6;		//0---63子类型
		u64 Type:2;			//0---1错误类型：0软件故障，1硬件故障,2应用意图故障（比如超设计值，过温）
		u64 Status:1;		//0---1错误状态：0冻结（Inactive），1激活（Active）
	}F;
}FaultInfo_t2;



//设置基准年份
void SetFaultInfoBaseYear(u16 Year);
u16 GetFaultInfoBaseYear(void);
//设置故障码发生的时间
void SetFaultInfoYMD(FaultInfo_t *FaultInfo,u8 Year ,u8 Month ,u8 Day);
void SetFaultInfoHMS(FaultInfo_t *FaultInfo,u8 Hour,u8 Minutes,u8 Second);
void SetFaultInfoTime(FaultInfo_t *FaultInfo,u8 Year ,u8 Month ,u8 Day ,u8 Hour,u8 Minutes,u8 Second);
//设置与获取故障码状态
void SetFaultInfoStatus(FaultInfo_t *FaultInfo,u8 Status);
u8 GetFaultInfoStatus(FaultInfo_t *FaultInfo);
//设置与获取故障码类型及其故障码值
void SetFaultInfoPara(FaultInfo_t *FaultInfo,u8 Type,u8 SubType,u32 Num);
u8 GetFaultInfoPara(FaultInfo_t *FaultInfo,u8 *Type,u8 *SubType,u32 *Num);
//打印故障信息
void PrintFaultInfo(FaultInfo_t *FaultInfo,u16 NodeNum);


#endif 



