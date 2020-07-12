/**
  ******************************************************************************
  * @file    listMgr.c 
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

#include "includes.h"


#if 1
/********************************************************************
�������ܣ�����˫������
��ڲ������ޡ�
��    �أ�����ָ��
��    ע�������ʼΪ��
********************************************************************/
List_t *ListCreate(void)
{
	List_t *list= NULL ;							//��������ָ��
	list = (List_t *)malloc(sizeof(List_t));		//�����ڴ�
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
�������ܣ�������β����ӽڵ�
��ڲ�����list,����ָ�� *pLoad�������������ָ�� nodeNum���ڵ���
��    �أ��ޡ�
��    ע����ӽڵ���Ϊ��ֵ�ڵ�����
********************************************************************/
listOpResult_t ListBackAddNode(List_t *list,void* pLoad,u16 nodeNum)
{
	Node_t *node= NULL;
	if (list == NULL) return listOpListNotExist;					//������������Ч
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
�������ܣ�������ͷ����ӽڵ�
��ڲ�����list,����ָ�� *pLoad�������������ָ�� nodeNum���ڵ���
��    �أ��ޡ�
��    ע���ޡ�
********************************************************************/
listOpResult_t ListHeadAddNode(List_t *list,void* pLoad,u16 nodeNum)
{
	Node_t *node= NULL;
	if (list == NULL) return listOpListNotExist;					//������������Ч
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
�������ܣ���β���Ƴ�һ���ڵ�(�Զ��ͷ�����ڵ���ڴ棬��ӽڵ�ʱ�Զ������ڴ�)
��ڲ�����listĿ������
��    �أ���Ӧ�ڵ�ĸ�������ָ�루�Ƴ��ڵ����Ҫ�ͷ�����ڴ�飩���ⲿfree����ڴ��
��    ע���ͷŽڵ��Ӧ�Ĵ洢�ռ䡣
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
�������ܣ���ͷ���Ƴ�һ���ڵ�(�Զ��ͷ�����ڵ���ڴ棬��ӽڵ�ʱ�Զ������ڴ�)
��ڲ������ޡ�
��    �أ���Ӧ�ڵ�ĸ�������ָ�루�Ƴ��ڵ����Ҫ�ͷ�����ڴ�飩���ⲿfree����ڴ��
��    ע���ͷŽڵ��Ӧ�Ĵ洢�ռ䡣
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
�������ܣ��Ƴ���ǰ�ڵ�(�Զ��ͷ�����ڵ���ڴ棬��ӽڵ�ʱ�Զ������ڴ�)
��ڲ������ޡ�
��    �أ���Ӧ�ڵ�ĸ�������ָ�루�Ƴ��ڵ����Ҫ�ͷ�����ڴ�飩���ⲿfree����ڴ��
��    ע��ǰ���������Ȳ��ҵ�ĳ���ڵ㣨ʹ�õ�ǰ�ڵ�ָ��ýڵ㣩���ٽ���ɾ��������
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
	else if(list->pNow->pre==NULL)					//��ǰ�ڵ�Ϊͷ�ڵ�
	{
		temp = list->pNow;
		pLoad = list->pNow->pLoad;
		list->pFirst=list->pNow->next;
		list->pNow->next->pre=NULL;
		--list->count;
		free(temp);
	}
	else if(list->pNow->next==NULL)					//��ǰ�ڵ�Ϊβ�ڵ�
	{
		temp = list->pNow;
		pLoad = list->pNow->pLoad;
		list->pLast=list->pNow->pre;
		list->pNow->pre->next=NULL;
		--list->count;
		free(temp);
	}
	else if(list->pNow!=NULL)						//�м�ڵ�
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
�������ܣ�
��ڲ������ޡ�
��    �أ��ޡ�
��    ע���ޡ�
********************************************************************/
#if 1
 // �����ǰ����Ϊ���򷵻ط�0�����򷵻�0 
bool listIsEmpty(List_t* list)
{
	if(list->count == 0)
		return TRUE;
	else
		return FALSE;
}
// �������Ĵ�С��Ԫ���ܸ����� 
int listCount(List_t* list)
{
	return list->count;
}
 // ����ǰλ���ƶ�������Ŀ�ʼ 
void listBegin(List_t* list)
{
	list->pNow = list->pFirst;
}
 // ����ǰλ���ƶ����������� 
void listEnd(List_t* list)
{
	list->pNow = list->pLast;
}
 // �����ǰλ��֮����Ԫ���򷵻ط�0�����򷵻�0 
int listHasNext(List_t* list)
{
	if (!list->pNow) return 0;
	if (list->pNow == list->pLast) return 1;
	return list->pNow->next != NULL;
}
 // ����ǰλ������ƶ�һ��λ�� 
void listMoveNext(List_t* list)
{
	list->pNow = list->pNow->next;
}
 // �����ǰλ��֮ǰ����Ԫ���򷵻ط�0�����򷵻�0 
int listHasPrev(List_t* list)
{
	if (!list->pNow) return 0;
	if (list->pNow == list->pFirst) return 1;
	return list->pNow->pre != NULL;
}
 // ����ǰλ������ƶ�һ��λ�� */
void listMovePrev(List_t* list)
{
	list->pNow = list->pNow->pre;
}
// ���ص�ǰλ�õ�Ԫ�� */
void* listGetCurrentNodeData(List_t* list)
{
	return list->pNow->pLoad;
}
u16 listGetCurrentNodeNum(List_t* list)
{
	return list->pNow->num;
}
 // �������������Ԫ�� ���ڷ��գ��˴��������ͷŽڵ����ݶ�Ӧ�Ĵ洢�ռ䣩
void listClear(List_t* list)
{
	//while(RemoveNodeFromBack(list));
	while(RemoveNodeFromBack(list));
}
// ����һ������ ���ڷ��գ��˴��������ͷŽڵ����ݶ�Ӧ�Ĵ洢�ռ䣩
 void listDestroy(List_t* list)
{
	listClear(list);
	free(list);
}
/********************************************************************
�������ܣ����������������ָ���ڵ��ŵĽڵ�
��ڲ�����list,���� nodeNum�ڵ���,**pLoadĿ��ڵ㸺�����ݵ�ָ��
��    �أ��ҵ�����TRUE,�Ҳ�������FALSE
��    ע���ҵ���һ���ڵ㼴ֹͣ
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
//��ȡ��ǰ�ڵ������ָ�벢����ƶ�һ���ڵ㣨��listHasNext()���ʹ����ȡ������������ݣ�
void* listGetNodeDataAndMoveNext(List_t* list)
{
	void* Pdata=list->pNow->pLoad;
	list->pNow = list->pNow->next;
	return Pdata;
}

/********************************************************************
�������ܣ������������ؽڵ��ż���������ָ��
��ڲ�����list,���� pNodeNum�ڵ��ű����ַ
��    �أ��ڵ㸺��ָ��
��    ע������ִ������ͷ��
********************************************************************/
void* listGetNodePayLoadAndMoveNext(List_t* list,u16 *pNodeNum)
{
	void* Pdata=list->pNow->pLoad;
	*pNodeNum=list->pNow->num;
	list->pNow = list->pNow->next;
	return Pdata;
}
// �����ӡ����
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
// �����ӡ����
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
�������ܣ�
��ڲ������ޡ�
��    �أ��ޡ�
��    ע���ޡ�
********************************************************************/


//���������ݽṹ
typedef struct
{
	u8 Voltage;			//��ѹ
	u8 Currnet;			//����
	u8 Freq;			//Ƶ��
}sPowerInfo_t;
//�������ݳ�ʼ��
void PowerInfoInit(sPowerInfo_t *PowerInfo,u8 Voltage,u8 Currnet,u8 Freq)
{
	PowerInfo->Voltage=Voltage;
	PowerInfo->Currnet=Currnet;
	PowerInfo->Freq=Freq;
}
//��ӡ������Ϣ
void printPowerInfo(sPowerInfo_t *PowerInfo,u8 NodeNum)
{
	printf("NodeNum=%d Voltage=%dV Currnet=%dA Freq=%dHz \r\n",NodeNum,PowerInfo->Voltage,PowerInfo->Currnet,PowerInfo->Freq);
}

static List_t *list;		//��������ָ��
void ListMgrTest0(void)
{
	bool findNodeFlag=FALSE;
	int i;
	u8 Voltage=100;			//��ѹ
	u8 Currnet=5;			//����
	u8 Freq=50;				//Ƶ��
	u16 NodeNum=1,FindNodeNum;
	sPowerInfo_t *PowerInfo;
	list = ListCreate();
	#if 1																	//��ӽڵ�
		printf("------------------������ӽڵ�------------------------\r\n");
		for(i=0; i<5; i++)
		{
			PowerInfo = (sPowerInfo_t *)malloc(sizeof(sPowerInfo_t));		//����ڵ��ڴ�
			PowerInfoInit(PowerInfo,Voltage,Currnet,Freq);					//��ʼ���ڵ�����
			printPowerInfo(PowerInfo,NodeNum);								//��ӡ�ڵ㸺����Ϣ	
			ListBackAddNode(list, PowerInfo,NodeNum);						//���ڵ���ӵ�����ĩβ
			NodeNum++;														//�ڵ���
			Voltage+=10;													//��ѹ
			Currnet++;														//����
			Freq++;															//Ƶ��
		}
		PrintListFromHead(list);											//��ӡ�ڵ㸺���ڴ��ַ
	#endif
	#if 1																	//���ҽڵ�	
		FindNodeNum=4;
		printf("------------------���ҽڵ�%d------------------------\r\n",FindNodeNum);
		findNodeFlag=listFindNodeFromBegin(list,FindNodeNum,(void*)&PowerInfo);
		if(findNodeFlag==FALSE)
		{
			printf("----listCount=%d �����ޱ��=%d�Ľڵ�\r\n",listCount(list),FindNodeNum);
		}
		else
		{
			printf("----listCount=%d pLoad=0x%X\r\n",listCount(list),(u32)PowerInfo);
			printPowerInfo(PowerInfo,FindNodeNum);
		}
		FindNodeNum=8;
		printf("------------------���ҽڵ�%d------------------------\r\n",FindNodeNum);
		findNodeFlag=listFindNodeFromBegin(list,FindNodeNum,(void*)&PowerInfo);
		if(findNodeFlag==FALSE)
		{
			printf("-1--listCount=%d �����ޱ��=%d�Ľڵ�\r\n",listCount(list),FindNodeNum);
		}
		else
		{
			printf("-2--listCount=%d pLoad=0x%X\r\n",listCount(list),(u32)PowerInfo);
			printPowerInfo(PowerInfo,FindNodeNum);
		}
	#endif
	#if 1																	//�����ڵ�
	printf("------------------��������ڵ�------------------------\r\n");
	listBegin(list);	
	while(listHasNext(list))
	{
		PowerInfo=listGetNodePayLoadAndMoveNext(list,&FindNodeNum);
		printPowerInfo(PowerInfo,FindNodeNum);
	}
	#endif
	#if 0				//�Ƴ�ȫ���ڵ�
	for(i=0; i<10; i++)
	{
		findNodeFlag=listFindNodeFromBegin(list,9-i);
		pdata=RemoveCurrentNode(list);pdata=listFreeBuff(pdata);
		printf("listcount=%d findNode:%d %X  %X\n",listCount(list),findNodeFlag,pdata,listGetCurrentDataPointer(list));
		//free(pdata);
		
	}
	#endif
	#if 1				//�Ƴ����ֽڵ�
		printf("------------------�Ƴ����ֽڵ�------------------------\r\n");
		//listSetBegin(list);
		findNodeFlag=listFindNodeFromBegin(list,1,(void*)&PowerInfo);		//���ҽڵ�
		PowerInfo=RemoveCurrentNode(list);free(PowerInfo);					//�Ƴ��ڵ㲢�ͷŽڵ㸺���ڴ�
		printf("findNode:%d �Ƴ��ڵ�0x%X \n",findNodeFlag,(u32)PowerInfo);	//��ӡ�ýڵ��ڴ��ַ
		
		findNodeFlag=listFindNodeFromBegin(list,3,(void*)&PowerInfo);		//���ҽڵ�
		PowerInfo=RemoveCurrentNode(list);free(PowerInfo);					//�Ƴ��ڵ㲢�ͷŽڵ㸺���ڴ�
		printf("findNode:%d �Ƴ��ڵ�0x%X \n",findNodeFlag,(u32)PowerInfo);	//��ӡ�ýڵ��ڴ��ַ

		printf("----ʣ��ڵ�����=%d \r\n",listCount(list));
		
	#endif
	#if 1																	//�����ڵ�
	printf("----------------�Ƴ����ֽڵ�--��������ڵ�------------------------\r\n");
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
	#if 0				//���ҽڵ�
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
	#if 0				//��ӽڵ�
		temp32A=0x5678;
		for(i=0; i<5; i++)
		{
			SetErrorNodePara(&ErrPara,1,2,temp32A++);
			ListBackAddNode(list, ErrPara.Data,NodeNum++);
		}
		findNodeFlag=listFindNodeFromBegin(list,5);
		printf("-1--listCount=%d findNodeFlag=%d\r\n",listCount(list),findNodeFlag);
	#endif
	#if 0				//��ӽڵ�
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
	#if 0				//�����ڵ�
	listSetBegin(list);i=0;
	while(listHasNext(list))
	{
		pdata=listGetNodeDataAndMoveNext(list);
		printf("aRR 1---[%d]:%X p=%X\n",i++,temp,pdata);
	}
	#endif
	#if 0				//�Ƴ�ȫ���ڵ�
	for(i=0; i<10; i++)
	{
		findNodeFlag=listFindNodeFromBegin(list,9-i);
		pdata=RemoveCurrentNode(list);pdata=listFreeBuff(pdata);
		printf("listcount=%d findNode:%d %X  %X\n",listCount(list),findNodeFlag,pdata,listGetCurrentDataPointer(list));
		//free(pdata);
		
	}
	#endif
	#if 0				//��ӽڵ�
	for(i=0; i<10; i++)
	{
		array2[i] = i+100+1;
		ListBackAddNode(list, &array2[i],i); 
		printf("array2[%d]:%X\n",i,&array2[i]);
	}
	#endif
	#if 0				//�Ƴ����ֽڵ�
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
	#if 0				//�����������нڵ�
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
	#if 0				//���ҽڵ�
		for(i=0; i<15; i++)
		{
			findNodeFlag=listFindNodeFromBegin(list,i);
			printf("%d findNode:%d %X\n",i,findNodeFlag,listGetCurrentDataPointer(list));
		}	
	#endif
	
//	listTest(list);
}
/********************************************************************
�������ܣ�
��ڲ������ޡ�
��    �أ��ޡ�
��    ע���ޡ�
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
�������ܣ�
��ڲ������ޡ�
��    �أ��ޡ�
��    ע���ޡ�
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

