/**
  ******************************************************************************
  * @file    listMgr.c 
  * @author  西小岑
  * @version V1.0.0
  * @date    2020.07.12
  * @brief   listMgr manage module
  ******************************************************************************
  * @attention
  Copyright (c) 2020 --- 2025 西小岑. All rights reserved.
  声明：
  1、此模块（listMgr），作者（西小岑）保留所有权限
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


#if 1
/********************************************************************
函数功能：创建双向链表
入口参数：无。
返    回：链表指针
备    注：链表初始为空
********************************************************************/
List_t *ListCreate(void)
{
	List_t *list= NULL ;							//定义链表指针
	list = (List_t *)malloc(sizeof(List_t));		//申请内存
	if(list == NULL)
	{
		return NULL;
	}
	else
	{
		memset(list,0,sizeof(List_t));
		list->count=0;
		list->pFirst=NULL;
		list->pLast=NULL;
		list->pNow=NULL;
		//printf("first=%X last=%X size=%X \r\n",list->first,list->last,list->size);	
		return list;
	}
}
/********************************************************************
函数功能：在链表尾部添加节点
入口参数：list,链表指针 *pLoad加入链表的数据指针 nodeNum，节点编号
返    回：无。
备    注：添加节点编号为差值节点提速
********************************************************************/
listOpResult_t ListBackAddNode(List_t *list,void* pLoad,u16 nodeNum)
{
	Node_t *node= NULL;
	if (list == NULL) return listOpListNotExist;					//给定的链表无效
	node = (Node_t *)malloc(sizeof(Node_t));
	if(node == NULL)
	{
		return listOpNewNodeNull;
	}
	else
	{
		node->num=nodeNum;
		node->pLoad=pLoad;
		if(list->pLast)
		{
			list->pLast->next = node;
			node->pre=list->pLast;
			node->next=NULL;
		}
		else
		{
			node->next=NULL;
			node->pre=NULL;
			list->pFirst=node;
		}
		list->pLast=node;
		list->pNow=node;
		list->count++;
	}
	//printf("node:%X nodeNum=%d\n",node,nodeNum);
	return listOpSuccess;
}
/********************************************************************
函数功能：从链表头部添加节点
入口参数：list,链表指针 *pLoad加入链表的数据指针 nodeNum，节点编号
返    回：无。
备    注：无。
********************************************************************/
listOpResult_t ListHeadAddNode(List_t *list,void* pLoad,u16 nodeNum)
{
	Node_t *node= NULL;
	if (list == NULL) return listOpListNotExist;					//给定的链表无效
	node = (Node_t *)malloc(sizeof(Node_t));
	if(node == NULL)
	{
		return listOpNewNodeNull;
	}
	else
	{
		node->num=nodeNum;
		node->pLoad=pLoad;
		if(list->pFirst)
		{
			list->pFirst->pre = node;
			node->pre=NULL;
			node->next=list->pFirst;
		}
		else
		{
			node->next=NULL;
			node->pre=NULL;
			list->pLast=node;
		}
		list->pFirst=node;
		list->pNow=node;
		list->count++;
	}
	//printf("node:%X nodeNum=%d\n",node,nodeNum);
	return listOpSuccess;
}
/********************************************************************
函数功能：从尾部移除一个节点(自动释放这个节点的内存，添加节点时自动申请内存)
入口参数：list目标链表
返    回：对应节点的负载数据指针（移除节点后需要释放这个内存块）在外部free这个内存块
备    注：释放节点对应的存储空间。
********************************************************************/
void* RemoveNodeFromBack(List_t* list)
{
	Node_t* temp;
	void *pLoad=NULL;
	if (list == NULL)return NULL;
	if(!list->count) return NULL;
	temp = list->pLast;
	pLoad = list->pLast->pLoad;
	if(list->pFirst == list->pLast)
	{
		list->pFirst = NULL;
		list->pLast = NULL;
		list->pNow  = NULL;
	}
	else
	{
		list->pLast = list->pLast->pre;
		list->pLast->next = NULL;
	}
	--list->count;
	free(temp);
	return pLoad;
}
/********************************************************************
函数功能：从头部移除一个节点(自动释放这个节点的内存，添加节点时自动申请内存)
入口参数：无。
返    回：对应节点的负载数据指针（移除节点后需要释放这个内存块）在外部free这个内存块
备    注：释放节点对应的存储空间。
********************************************************************/
void* RemoveNodeFromHead(List_t* list)
{
	Node_t* temp;
	void *pLoad=NULL;
	if (list == NULL)return NULL;
	if(!list->count) return NULL;
	temp = list->pFirst;
	pLoad = list->pFirst->pLoad;
	if(list->pFirst == list->pLast)
	{
		list->pFirst = NULL;
		list->pLast = NULL;
		list->pNow  = NULL;
	}
	else
	{
		list->pFirst = list->pFirst->next;
		list->pFirst->pre = NULL;
	}
	--list->count;
	free(temp);
	return pLoad;
}
/********************************************************************
函数功能：移除当前节点(自动释放这个节点的内存，添加节点时自动申请内存)
入口参数：无。
返    回：对应节点的负载数据指针（移除节点后需要释放这个内存块）在外部free这个内存块
备    注：前提条件：先查找到某个节点（使得当前节点指向该节点），再进行删除操作。
********************************************************************/
void* RemoveCurrentNode(List_t* list)
{
	Node_t* temp= NULL;
	void *pLoad=NULL;
	if (list == NULL)return NULL;
	if(!list->count) return NULL;
	if(list->pFirst == list->pLast)
	{
		temp = list->pNow;
		pLoad = list->pNow->pLoad;
		list->pFirst = NULL;
		list->pLast = NULL;
		list->pNow  = NULL;
		--list->count;
		free(temp);
	}
	else if(list->pNow->pre==NULL)					//当前节点为头节点
	{
		temp = list->pNow;
		pLoad = list->pNow->pLoad;
		list->pFirst=list->pNow->next;
		list->pNow->next->pre=NULL;
		--list->count;
		free(temp);
	}
	else if(list->pNow->next==NULL)					//当前节点为尾节点
	{
		temp = list->pNow;
		pLoad = list->pNow->pLoad;
		list->pLast=list->pNow->pre;
		list->pNow->pre->next=NULL;
		--list->count;
		free(temp);
	}
	else if(list->pNow!=NULL)						//中间节点
	{
		temp = list->pNow;
		pLoad = list->pNow->pLoad;
		list->pNow->pre->next=list->pNow->next;
		list->pNow->next->pre=list->pNow->pre;
		--list->count;
		free(temp);
	}
	return pLoad;
}
#endif
/********************************************************************
函数功能：
入口参数：无。
返    回：无。
备    注：无。
********************************************************************/
#if 1
 // 如果当前链表为空则返回非0，否则返回0 
bool listIsEmpty(List_t* list)
{
	if(list->count == 0)
		return TRUE;
	else
		return FALSE;
}
// 获得链表的大小（元素总个数） 
int listCount(List_t* list)
{
	return list->count;
}
 // 将当前位置移动到链表的开始 
void listBegin(List_t* list)
{
	list->pNow = list->pFirst;
}
 // 将当前位置移动到链表的最后 
void listEnd(List_t* list)
{
	list->pNow = list->pLast;
}
 // 如果当前位置之后还有元素则返回非0，否则返回0 
int listHasNext(List_t* list)
{
	if (!list->pNow) return 0;
	if (list->pNow == list->pLast) return 1;
	return list->pNow->next != NULL;
}
 // 将当前位置向后移动一个位置 
void listMoveNext(List_t* list)
{
	list->pNow = list->pNow->next;
}
 // 如果当前位置之前还有元素则返回非0，否则返回0 
int listHasPrev(List_t* list)
{
	if (!list->pNow) return 0;
	if (list->pNow == list->pFirst) return 1;
	return list->pNow->pre != NULL;
}
 // 将当前位置向后移动一个位置 */
void listMovePrev(List_t* list)
{
	list->pNow = list->pNow->pre;
}
// 返回当前位置的元素 */
void* listGetCurrentNodeData(List_t* list)
{
	return list->pNow->pLoad;
}
u16 listGetCurrentNodeNum(List_t* list)
{
	return list->pNow->num;
}
 // 清空链表中所有元素 存在风险（此处忽略了释放节点数据对应的存储空间）
void listClear(List_t* list)
{
	//while(RemoveNodeFromBack(list));
	while(RemoveNodeFromBack(list));
}
// 销毁一个链表 存在风险（此处忽略了释放节点数据对应的存储空间）
 void listDestroy(List_t* list)
{
	listClear(list);
	free(list);
}
/********************************************************************
函数功能：遍历整个链表查找指定节点编号的节点
入口参数：list,链表 nodeNum节点编号,**pLoad目标节点负载数据的指针
返    回：找到返回TRUE,找不到返回FALSE
备    注：找到第一个节点即停止
********************************************************************/
bool listFindNodeFromBegin(List_t* list,u16 nodeNum,void **pLoad)
{
	u8 cnt=0;
	void *pDat=0;
	for(listBegin(list);listHasNext(list);listMoveNext(list))
	{
		if(listGetCurrentNodeNum(list)==nodeNum)
		{
			pDat=listGetCurrentNodeData(list);
			//printf(" --- pData Addr=%XH \r\n",(u32)pDat);
			break;
		}
		cnt++;
	}
	*pLoad=pDat;
	//list->pNow=list->pLast;
	//printf("cnt=%d listSize=%d\n",cnt,listCount(list));
	if(cnt<listCount(list))
		return TRUE;
	else return FALSE;
}

void* listFindNodeFromBegin2(List_t* list,u16 nodeNum)
{
	u8 cnt=0;
	void *pData=NULL;
	for(listBegin(list);listHasNext(list);listMoveNext(list))
	{
		if(listGetCurrentNodeNum(list)==nodeNum)
		{
			pData=listGetCurrentNodeData(list);
			break;
		}
		cnt++;
	}
	list->pNow=list->pLast;
	//printf("cnt=%d listSize=%d\n",cnt,listCount(list));
	if(cnt<listCount(list))
		return pData;
	else return pData;
}
//提取当前节点的数据指针并向后移动一个节点（与listHasNext()配合使用提取整个链表的数据）
void* listGetNodeDataAndMoveNext(List_t* list)
{
	void* Pdata=list->pNow->pLoad;
	list->pNow = list->pNow->next;
	return Pdata;
}

/********************************************************************
函数功能：遍历链表并返回节点编号及负载数据指针
入口参数：list,链表 pNodeNum节点编号保存地址
返    回：节点负载指针
备    注：需先执行链表头部
********************************************************************/
void* listGetNodePayLoadAndMoveNext(List_t* list,u16 *pNodeNum)
{
	void* Pdata=list->pNow->pLoad;
	*pNodeNum=list->pNow->num;
	list->pNow = list->pNow->next;
	return Pdata;
}
// 正向打印链表
void PrintListFromHead(List_t* list)
{
	u16 NodeNum=0;
	void* pLoad;
	for( listBegin(list);listHasNext(list);listMoveNext(list) )
	{
		NodeNum=listGetCurrentNodeNum(list);
		pLoad=listGetCurrentNodeData(list);
		printf("NodeNum=%d pLoad=0x%X \r\n",NodeNum,(u32)pLoad);
		//PrintErrorInfo(pLoad,NodeNum);
	}
	putchar('\n');
}
// 反向打印链表
void PrintListFromEnd(List_t* list)
{
	u16 NodeNum=0;
	void* pLoad;
	for (listEnd(list); listHasPrev(list); listMovePrev(list))
	{
		NodeNum=listGetCurrentNodeNum(list);
		pLoad=listGetCurrentNodeData(list);
		printf("NodeNum=%d pLoad=0x%X \r\n",NodeNum,(u32)pLoad);
	}
	putchar('\n');
}
#endif
/********************************************************************
函数功能：
入口参数：无。
返    回：无。
备    注：无。
********************************************************************/


//链表负载数据结构
typedef struct
{
	u8 Voltage;			//电压
	u8 Currnet;			//电流
	u8 Freq;			//频率
}sPowerInfo_t;
//负载数据初始化
void PowerInfoInit(sPowerInfo_t *PowerInfo,u8 Voltage,u8 Currnet,u8 Freq)
{
	PowerInfo->Voltage=Voltage;
	PowerInfo->Currnet=Currnet;
	PowerInfo->Freq=Freq;
}
//打印负载信息
void printPowerInfo(sPowerInfo_t *PowerInfo,u8 NodeNum)
{
	printf("NodeNum=%d Voltage=%dV Currnet=%dA Freq=%dHz \r\n",NodeNum,PowerInfo->Voltage,PowerInfo->Currnet,PowerInfo->Freq);
}

static List_t *list;		//定义链表指针
void ListMgrTest0(void)
{
	bool findNodeFlag=FALSE;
	int i;
	u8 Voltage=100;			//电压
	u8 Currnet=5;			//电流
	u8 Freq=50;				//频率
	u16 NodeNum=1,FindNodeNum;
	sPowerInfo_t *PowerInfo;
	list = ListCreate();
	#if 1																	//添加节点
		printf("------------------链表添加节点------------------------\r\n");
		for(i=0; i<5; i++)
		{
			PowerInfo = (sPowerInfo_t *)malloc(sizeof(sPowerInfo_t));		//申请节点内存
			PowerInfoInit(PowerInfo,Voltage,Currnet,Freq);					//初始化节点数据
			printPowerInfo(PowerInfo,NodeNum);								//打印节点负载信息	
			ListBackAddNode(list, PowerInfo,NodeNum);						//将节点添加到链表末尾
			NodeNum++;														//节点编号
			Voltage+=10;													//电压
			Currnet++;														//电流
			Freq++;															//频率
		}
		PrintListFromHead(list);											//打印节点负载内存地址
	#endif
	#if 1																	//查找节点	
		FindNodeNum=4;
		printf("------------------查找节点%d------------------------\r\n",FindNodeNum);
		findNodeFlag=listFindNodeFromBegin(list,FindNodeNum,(void*)&PowerInfo);
		if(findNodeFlag==FALSE)
		{
			printf("----listCount=%d 链表无编号=%d的节点\r\n",listCount(list),FindNodeNum);
		}
		else
		{
			printf("----listCount=%d pLoad=0x%X\r\n",listCount(list),(u32)PowerInfo);
			printPowerInfo(PowerInfo,FindNodeNum);
		}
		FindNodeNum=8;
		printf("------------------查找节点%d------------------------\r\n",FindNodeNum);
		findNodeFlag=listFindNodeFromBegin(list,FindNodeNum,(void*)&PowerInfo);
		if(findNodeFlag==FALSE)
		{
			printf("-1--listCount=%d 链表无编号=%d的节点\r\n",listCount(list),FindNodeNum);
		}
		else
		{
			printf("-2--listCount=%d pLoad=0x%X\r\n",listCount(list),(u32)PowerInfo);
			printPowerInfo(PowerInfo,FindNodeNum);
		}
	#endif
	#if 1																	//遍历节点
	printf("------------------遍历链表节点------------------------\r\n");
	listBegin(list);	
	while(listHasNext(list))
	{
		PowerInfo=listGetNodePayLoadAndMoveNext(list,&FindNodeNum);
		printPowerInfo(PowerInfo,FindNodeNum);
	}
	#endif
	#if 0				//移除全部节点
	for(i=0; i<10; i++)
	{
		findNodeFlag=listFindNodeFromBegin(list,9-i);
		pdata=RemoveCurrentNode(list);pdata=listFreeBuff(pdata);
		printf("listcount=%d findNode:%d %X  %X\n",listCount(list),findNodeFlag,pdata,listGetCurrentDataPointer(list));
		//free(pdata);
		
	}
	#endif
	#if 1				//移除部分节点
		printf("------------------移除部分节点------------------------\r\n");
		//listSetBegin(list);
		findNodeFlag=listFindNodeFromBegin(list,1,(void*)&PowerInfo);		//查找节点
		PowerInfo=RemoveCurrentNode(list);free(PowerInfo);					//移除节点并释放节点负载内存
		printf("findNode:%d 移除节点0x%X \n",findNodeFlag,(u32)PowerInfo);	//打印该节点内存地址
		
		findNodeFlag=listFindNodeFromBegin(list,3,(void*)&PowerInfo);		//查找节点
		PowerInfo=RemoveCurrentNode(list);free(PowerInfo);					//移除节点并释放节点负载内存
		printf("findNode:%d 移除节点0x%X \n",findNodeFlag,(u32)PowerInfo);	//打印该节点内存地址

		printf("----剩余节点数量=%d \r\n",listCount(list));
		
	#endif
	#if 1																	//遍历节点
	printf("----------------移除部分节点--遍历链表节点------------------------\r\n");
	listBegin(list);	
	while(listHasNext(list))
	{
		PowerInfo=listGetNodePayLoadAndMoveNext(list,&FindNodeNum);
		printPowerInfo(PowerInfo,FindNodeNum);
	}
	#endif
	
	
	for(i=0; i<5; i++)
	{
		//printf("%d size=%d data:%X\n",i,listCount(list),RemoveNodeFromHead(list));
		//printf("%d size=%d data:%X\n",i,listCount(list),RemoveNodeFromBack(list));
	}
	#if 0				//查找节点
		for(i=0; i<15; i++)
		{
			findNodeFlag=listFindNodeFromBegin(list,i);
			printf("%d findNode:%d %X\n",i,findNodeFlag,listGetCurrentDataPointer(list));
		}	
	#endif
	
//	listTest(list);
}
void ListMgrTest1(void)
{
	bool findNodeFlag=FALSE;
	int i;
	u16 NodeNum=0,temp16A;
	U32 temp32A=0;
	U64 temp64A=0;
	//ErrPara_t ErrPara;
	list = ListCreate();
	//SetErrorNodeYMD(&ErrPara,21 ,3 ,25);
	//SetErrorNodeHMS(&ErrPara,13,39,35);
	#if 0				//添加节点
		temp32A=0x5678;
		for(i=0; i<5; i++)
		{
			SetErrorNodePara(&ErrPara,1,2,temp32A++);
			ListBackAddNode(list, ErrPara.Data,NodeNum++);
		}
		findNodeFlag=listFindNodeFromBegin(list,5);
		printf("-1--listCount=%d findNodeFlag=%d\r\n",listCount(list),findNodeFlag);
	#endif
	#if 0				//添加节点
		temp32A=0x1234;
		for(i=0; i<3; i++)
		{
			SetErrorNodePara(&ErrPara,1,2,temp32A++);
			ListHeadAddNode(list, ErrPara.Data,NodeNum++); 
		}
		findNodeFlag=listFindNodeFromBegin(list,8);
		ErrPara.Data=listGetCurrentNodeData(list);
		temp16A=listGetCurrentNodeNum(list);
		printf("-2 NodeNum=%d\r\n",temp16A);
		printf("-3 Type =%d SubType=%d num=%X \r\n",ErrPara.F.Type,ErrPara.F.SubType,ErrPara.F.Num);
		printf("-4--listCount=%d findNodeFlag=%d\r\n",listCount(list),findNodeFlag);
		Traverse(list);
	#endif
	#if 0				//遍历节点
	listSetBegin(list);i=0;
	while(listHasNext(list))
	{
		pdata=listGetNodeDataAndMoveNext(list);
		printf("aRR 1---[%d]:%X p=%X\n",i++,temp,pdata);
	}
	#endif
	#if 0				//移除全部节点
	for(i=0; i<10; i++)
	{
		findNodeFlag=listFindNodeFromBegin(list,9-i);
		pdata=RemoveCurrentNode(list);pdata=listFreeBuff(pdata);
		printf("listcount=%d findNode:%d %X  %X\n",listCount(list),findNodeFlag,pdata,listGetCurrentDataPointer(list));
		//free(pdata);
		
	}
	#endif
	#if 0				//添加节点
	for(i=0; i<10; i++)
	{
		array2[i] = i+100+1;
		ListBackAddNode(list, &array2[i],i); 
		printf("array2[%d]:%X\n",i,&array2[i]);
	}
	#endif
	#if 0				//移除部分节点
		//listSetBegin(list);
		findNodeFlag=listFindNodeFromBegin(list,0);
		pdata=RemoveCurrentNode(list);free(pdata);
		printf("findNode:%d %X  %X\n",findNodeFlag,pdata,listGetCurrentDataPointer(list));
		
		findNodeFlag=listFindNodeFromBegin(list,9);
		pdata=RemoveCurrentNode(list);free(pdata);
		printf("findNode:%d %X  %X\n",findNodeFlag,pdata,listGetCurrentDataPointer(list));
	
		findNodeFlag=listFindNodeFromBegin(list,2);
		pdata=RemoveCurrentNode(list);free(pdata);
		printf("findNode:%d %X  %X\n",findNodeFlag,pdata,listGetCurrentDataPointer(list));	
	
		findNodeFlag=listFindNodeFromBegin(list,7);
		pdata=RemoveCurrentNode(list);free(pdata);
		printf("findNode:%d %X  %X\n",findNodeFlag,pdata,listGetCurrentDataPointer(list));	
	
	#endif
	#if 0				//遍历链表所有节点
		listSetBegin(list);i=0;
		while(listHasNext(list))
		{
			pdata=listGetNodeDataAndMoveNext(list);free(pdata);
			printf("aRR 2---[%d]:%X p=%X\n",i++,temp,pdata);
		}
	#endif
	
	
	for(i=0; i<5; i++)
	{
		//printf("%d size=%d data:%X\n",i,listCount(list),RemoveNodeFromHead(list));
		//printf("%d size=%d data:%X\n",i,listCount(list),RemoveNodeFromBack(list));
	}
	#if 0				//查找节点
		for(i=0; i<15; i++)
		{
			findNodeFlag=listFindNodeFromBegin(list,i);
			printf("%d findNode:%d %X\n",i,findNodeFlag,listGetCurrentDataPointer(list));
		}	
	#endif
	
//	listTest(list);
}
/********************************************************************
函数功能：
入口参数：无。
返    回：无。
备    注：无。
********************************************************************/
void ListTest(void)
{
	//printf("list=%d Node=%d \r\n",sizeof(List_t),sizeof(Node_t));
	ListMgrTest0();
	//ListMgrTest1();
	//ListMgrTest2();
	
	//printf("list=%08XH \r\n",(u32)list);
	
	while(1)
	{
		DelayMs(100);
	}
}

#if 0
/********************************************************************
函数功能：
入口参数：无。
返    回：无。
备    注：无。
********************************************************************/
Node_t *pNodeFirst,*pNodeNow;
void ListMgrTest2(void)
{
	u8 i;
	Node_t *Node= NULL;	
	Node = (Node_t *)malloc(sizeof(Node_t));
	Node->pre = NULL;
	Node->next = NULL;
	Node->ErrPara.Data=0x12345678;
	pNodeNow = Node;
	pNodeFirst = Node;
	printf(" Node%d = %08XH \r\n",i,(u32)Node);
	for(i=0;i<5;i++)
	{
		Node = (Node_t *)malloc(sizeof(Node_t));
		Node->ErrPara.Data=0x12345670+i;
		Node->pre = pNodeNow;
		pNodeNow->next=Node;
		pNodeNow = Node;
		printf(" Node%d = %08XH \r\n",i+1,(u32)Node);
	}
	
}
#endif

