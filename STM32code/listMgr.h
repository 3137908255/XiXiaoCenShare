
/**
  ******************************************************************************
  * @file    listMgr.h 
  * @author  ��С�
  * @version V1.0.0
  * @date    2020.07.12
  * @brief   listMgr manage module
  ******************************************************************************
  * @attention
  Copyright (c) 2020 --- 2025 ��С�. All rights reserved.
  ������
  1����ģ�飨listMgr�������ߣ���Сᯣ���������Ȩ��
  2����ģ������ο�ѧϰ���о�������ʹ��
  3����������ҵĿ�ģ���Ҫ��������ͬ��
  4�����߽��ṩԴ���룬���Դӡ�github.com�������أ��������ڴ�����
  5���Դ�ģ���ʹ����������֤�����ԡ�
  6������ʹ�ñ�ģ����ɵ��κ���ʧ�����ߣ���Сᯣ����е��κ����Ρ�
  7���罫��ģ�鼯������Ĵ����У����뱣��������
  8���粻ͬ����������벻Ҫʹ�ô�ģ��
  ******************************************************************************
**/

#ifndef LIST_MGR_H
#define LIST_MGR_H

#include "includes.h"

//�����������״̬
typedef enum{
	listOpSuccess=0,					//��������ɹ�
	listOpListEmpty,					//����Ϊ��
	listOpListNotExist,					//��������
	listOpNodeNotExist,					//�������ڴ˽ڵ�
	listOpNodeNull,						//�ڵ�Ϊ�գ��ڵ��ַ�Ƿ���
	listOpNewNodeNull,					//����½ڵ�ʱ�ڵ��ַΪ��
}listOpResult_t;
//����ڵ�ṹ��
typedef struct Node
{
	u16				num;				//�ڵ���
	void*			pLoad;				//ָ�������ָ��
	struct Node 	*pre;				//ǰһ���ڵ�	
	struct Node 	*next;				//��һ���ڵ�
}Node_t;
//��������ṹ��
typedef struct listMgr
{
	u16 	count;						//�ڵ�����
	Node_t 	*pFirst;						//�׽ڵ�	
	Node_t 	*pLast;						//ĩ�ڵ�
	Node_t 	*pNow;						//��ǰ�ڵ�
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



