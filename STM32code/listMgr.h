
/**
  ******************************************************************************
  * @file    listMgr.h 
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

#ifndef LIST_MGR_H
#define LIST_MGR_H

#include "includes.h"

//定义链表操作状态
typedef enum{
	listOpSuccess=0,					//链表操作成功
	listOpListEmpty,					//链表为空
	listOpListNotExist,					//链表不存在
	listOpNodeNotExist,					//链表不存在此节点
	listOpNodeNull,						//节点为空（节点地址非法）
	listOpNewNodeNull,					//添加新节点时节点地址为空
}listOpResult_t;
//定义节点结构体
typedef struct Node
{
	u16				num;				//节点编号
	void*			pLoad;				//指向参数的指针
	struct Node 	*pre;				//前一个节点	
	struct Node 	*next;				//后一个节点
}Node_t;
//定义链表结构体
typedef struct listMgr
{
	u16 	count;						//节点数量
	Node_t 	*pFirst;						//首节点	
	Node_t 	*pLast;						//末节点
	Node_t 	*pNow;						//当前节点
}List_t;
	

List_t *ListCreate(void);
listOpResult_t ListBackAddNode(List_t *list,void* pLoad,u16 nodeNum);
listOpResult_t ListHeadAddNode(List_t *list,void* pLoad,u16 nodeNum);
void* RemoveNodeFromBack(List_t* list);
void* RemoveNodeFromHead(List_t* list);
void* RemoveCurrentNode(List_t* list);

bool listIsEmpty(List_t* list);
int listCount(List_t* list);
void listBegin(List_t* list);
void listEnd(List_t* list); 
int listHasNext(List_t* list);
void listMoveNext(List_t* list);
int listHasPrev(List_t* list);
void listMovePrev(List_t* list);
void* listGetCurrentNodeData(List_t* list);
u16 listGetCurrentNodeNum(List_t* list);
void listClear(List_t* list);
void listDestroy(List_t* list);
void PrintListFromHead(List_t* list);
void PrintListFromEnd(List_t* list);

bool listFindNodeFromBegin(List_t* list,u16 nodeNum,void **pData);
void* listFindNodeFromBegin2(List_t* list,u16 nodeNum);
void* listGetNodeDataAndMoveNext(List_t* list);




void ListTest(void);



#endif 



