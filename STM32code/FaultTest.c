/**
  ******************************************************************************
  * @file    ringbuff.h 
  * @author  西小岑
  * @version V1.2.0
  * @date    2019.12.25
  * @brief   ringbuff manage module
  ******************************************************************************
  * @attention
  Copyright (c) 2020 --- 2025 西小岑. All rights reserved.
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

#include "includes.h"




//序号	类型	子类型	故障值	含义			维护方法		备注
//1		0		2		1		水位量低于阈值	加水			检查水位
//2		0		2		2		水流量低于阈值	加水检查水泵	
//3		0		2		3		光阀打开失败	检查光阀电机	限位开关
//4		0		2		4		光阀关闭失败	检查光阀电机	限位开关
//5		0		2		5		650nm瞄准光无效	检查650激光器	
//6		0		2		6		水温高于阈值	检查制冷系统	
//7		0		2		7		调试风扇故障	检查调试风扇	正常时检查反馈信号
//8		0		2		8		气流量低于阈值	检查气泵	

void printFaultInfo(u8 Active,u8 Type,u8 SubType,u32 FaultVal)
{
	printf(" --- 错误码信息 --- ");
	if(Active==FAULT_STATUS_ACTIVE)
	{
		printf(" 状态->激活 ");
	}	
	else 
	{
		printf(" 状态->冻结 ");
	}
	if(Type==0)
	{
		printf(" 软件故障 ");
	}	
	else 
	{
		printf(" 硬件故障 ");
	}
	switch(FaultVal)
	{
		case 1:	printf("FaultVal=%d 水位量低于阈值,请加水\r\n ",FaultVal);
			break;
		case 2:	printf("FaultVal=%d 水流量低于阈值,请加水检查水泵\r\n ",FaultVal);
			break;
		case 3:	printf("FaultVal=%d 光阀打开失败,请检查光阀电机\r\n ",FaultVal);
			break;
		case 4:	printf("FaultVal=%d 光阀关闭失败,请检查光阀电机\r\n ",FaultVal);
			break;
		case 5:	printf("FaultVal=%d 650nm瞄准光无效,请检查650激光器\r\n ",FaultVal);
			break;
		case 6:	printf("FaultVal=%d 水温高于阈值,请检查制冷系统\r\n ",FaultVal);
			break;
		case 7:	printf("FaultVal=%d 调试风扇故障,请检查调试风扇\r\n ",FaultVal);
			break;
		case 8:	printf("FaultVal=%d 气流量低于阈值,请检查气泵\r\n ",FaultVal);
			break;
		default:printf(" 未定义故障值 \r\n ");
			break;
	}
}
void printDecodeFaultInfo(FaultInfo_t *pFaultInfo)
{
	printf(" --- 错误码信息 --- ");
	if(pFaultInfo->F.Status==FAULT_STATUS_ACTIVE)
	{
		printf(" 状态->激活 ");
	}	
	else 
	{
		printf(" 状态->冻结 ");
	}
	if(pFaultInfo->F.Type==0)
	{
		printf(" 类型->软件故障 ");
	}	
	else 
	{
		printf(" 类型->硬件故障 ");
	}
	if(pFaultInfo->F.SubType==0)
	{
		printf(" 子类型->未定义 ");
	}	
	else if(pFaultInfo->F.SubType==1)
	{
		printf(" 子类型->电源故障 ");
	}
	else if(pFaultInfo->F.SubType==2)
	{
		printf(" 子类型->主控板故障 ");
	}
	switch(pFaultInfo->F.Num)
	{
		case 1:	printf("FaultVal=%d 水位量低于阈值,请加水 \t\t\t",pFaultInfo->F.Num);
			break;
		case 2:	printf("FaultVal=%d 水流量低于阈值,请加水检查水泵 \t\t",pFaultInfo->F.Num);
			break;
		case 3:	printf("FaultVal=%d 光阀打开失败,请检查光阀电机 \t\t",pFaultInfo->F.Num);
			break;
		case 4:	printf("FaultVal=%d 光阀关闭失败,请检查光阀电机 \t\t",pFaultInfo->F.Num);
			break;
		case 5:	printf("FaultVal=%d 650nm瞄准光无效,请检查650激光器 \t\t",pFaultInfo->F.Num);
			break;
		case 6:	printf("FaultVal=%d 水温高于阈值,请检查制冷系统 \t\t",pFaultInfo->F.Num);
			break;
		case 7:	printf("FaultVal=%d 调试风扇故障,请检查调试风扇 \t\t",pFaultInfo->F.Num);
			break;
		case 8:	printf("FaultVal=%d 气流量低于阈值,请检查气泵 \t\t",pFaultInfo->F.Num);
			break;
		default:printf(" 未定义故障值  \t\t");
			break;
	}
	printf(" %d-%d-%d %d:%d:%d\r\n",GetFaultInfoBaseYear()+pFaultInfo->F.Year,pFaultInfo->F.Month,pFaultInfo->F.Day,pFaultInfo->F.Hour,pFaultInfo->F.Minutes,pFaultInfo->F.Second);
}
/********************************************************************
函数功能：仿真测试故障码
入口参数：无。
返    回：无。
备    注：无。
********************************************************************/
List_t *FaultCodelist;							//定义故障码链表指针
void FaultCodeTest(void)
{
	int i;
	u16 NodeNum=0;
	u8 minutes=20,second=10;
	FaultInfo_t *pFaultInfo;					//定义故障信息指针							
	FaultCodelist = ListCreate();				//创建链表
	#if 1 // -------- 添加节点（故障码） --------
		for(i=0; i<8; i++)
		{
			pFaultInfo=malloc(sizeof(FaultInfo_t));					//申请内存
			SetFaultInfoTime(pFaultInfo,20 ,7 ,12 ,17,minutes+i,second+i);		//设置故障码时间：年月日时分秒
			SetFaultInfoStatus(pFaultInfo,FAULT_STATUS_ACTIVE);		//设置故障状态：激活
			SetFaultInfoPara(pFaultInfo ,0,2,i+1);					//设置故障码：类型，子类型，故障值1--8
			ListBackAddNode(FaultCodelist, pFaultInfo,NodeNum++);	//将故障信息添加到链表中
		}
	#endif	
	#if 1 // -------- 输出链表信息 --------
		NodeNum=0;
		for(i=0; i<10; i++)
		{
			pFaultInfo=listFindNodeFromBegin2(FaultCodelist,NodeNum);
			if(pFaultInfo!=NULL)
			{
				PrintFaultInfo(pFaultInfo,NodeNum);				//打印故障信息
			}
			else
			{
				printf(" Node %d Not Exist \r\n",NodeNum);
			}
			NodeNum++;
		}
	#endif
	#if 1 // -------- 输出链表信息 --------
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