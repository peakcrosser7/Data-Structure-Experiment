/* 线性链表 */


#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include<string.h>

//基本标识宏定义
#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASTABLE -1
#define OVERFLOW -2
#define LISTMAXNUM 9	//允许建立的最大链表个数


typedef int status;
typedef int ElemType; //数据元素类型定义

typedef struct LNode{
	ElemType data;
	struct LNode* next;
}*Link;	//链表节点结构体

typedef struct {
	Link head;
	int len;
}LinkList;			//链表整体结构体

int num = 0;		//建立的链表个数
char listname[LISTMAXNUM][20];	//建立的链表的名称


//子函数声明
status InitList(LinkList** L);		//初始化链表
status CreateList(LinkList* L);		//创建链表结点并输入
status ListExist(LinkList* L);		//判定链表是否存在
status DestoryList(LinkList** L, int oplist);		//销毁链表
status ClearList(LinkList* L);		//清空链表
status ListEmpty(LinkList L);		//判定链表是否为空表
int ListLength(LinkList L);		//求链表长度
status GetELem(LinkList L, int i, ElemType* e);		//获得元素
status compare(struct LNode node, ElemType e);		//比较函数
int LocateElem(LinkList L, ElemType e, status compare(struct LNode, ElemType));		//根据条件查找元素
status PriorElem(LinkList L, ElemType cur_e, ElemType* pre_e);		//获得前驱
status NextElem(LinkList L, ElemType cur_e, ElemType* next_e);		//获得后继
status ListInsert(LinkList* L, int i, ElemType e);		//插入元素
status ListDelete(LinkList* L, int i, ElemType* e);		//删除元素
status ListTraverse(LinkList L, void (*visit)(ElemType));		//遍历链表
void visit(ElemType);		//访问结点中元素
status SaveElem(LinkList L);		//链表元素存入文件
status LoadElem(LinkList** L, int num, char* filename);		//从文件读入链表元素


//主函数：主界面和调用子函数预处理
void main(void) {
	LinkList* L[LISTMAXNUM] = { NULL };		//链表指针数组
	char tempname[20];		//临时名称
	int op = 1;
	int temp;
	int oplist;		//选择的链表序号
	int count=num;		//临时建立链表的次数（计数器）
	ElemType elemdest,elemsrc;		//源元素，目的元素

	while (op) 
	{
		system("cls");	printf("\n\n");
		printf("      Menu for Linear Table On Chain Structure \n");
		printf("-------------------------------------------------\n");
		printf("    	  1. InitList        8. PriorElem\n");
		printf("    	  2. DestroyList     9. NextElem \n");
		printf("    	  3. ClearList       10.ListInsert \n");
		printf("    	  4. ListEmpty       11.ListDelete\n");
		printf("    	  5. ListLength      12.ListTrabverse\n");
		printf("    	  6. GetElem         13.SaveElem \n");
		printf("          7. LocateElem      14.LoadElem\n");
		printf("    	  0. Exit\n");
		printf("-------------------------------------------------\n");
		printf("Active List:\t");		//显示当前已建立的链表
		if (num)
			for (int i = 0; i < num; i++)
			{
				if ((i + 1) % 4 == 0)
					putchar('\n');
				printf("%d: %s\t", i, listname[i]);	
			}
		printf("\n-------------------------------------------------\n");
		printf("    请选择你的操作[0~14]:");
		scanf("%d", &op);

		if (op == 1)
		{	//输入1则初始化链表同时创建链表输入数据
			if (InitList(&L[num%LISTMAXNUM]) && CreateList(L[num%LISTMAXNUM]))
			{	//若建立链表成功对链表临时命名
				memset(tempname, 0, 20);
				strcat(tempname, "temp");
				_itoa(count, tempname + 4, 10);
				strcpy(listname[num%LISTMAXNUM], tempname);
				num = (num >= LISTMAXNUM ? LISTMAXNUM : num + 1);
				//若已建立链表未超过最大数目：建立链表数+1，否则保持最大数目不变（超过最大数目的链表一直覆盖第一个链表）
				count++;	//计数器+1
				printf("\n线性表创建成功！\n");
			}
			else
				printf("\n线性表创建失败！\n");
			system("pause");
		}
		else if (op == 14)
		{	//输入14加载文件中的数据
			printf("input file name: ");
			scanf("%s", tempname);
			if (LoadElem(L,num%9,tempname))
			{	//加载数据成功则对链表命名为文件名
				strcpy(listname[num % LISTMAXNUM], tempname);
				num = (num >= LISTMAXNUM ? LISTMAXNUM : num+1);
				printf("\n载入数据成功!\n");
			}
			else
				printf("\nFalse!\n");
			system("pause");
		}
		else if(op>1&&op<14)
		{	//输入其他选项
			if (num > 1)
			{	//若已建立链表数＞1则操作前需要确定操作链表的序号
				printf("请输入操作链表序号：");
				scanf("%d", &oplist);
			}
			else	//若仅有一个链表，则该链表默认为操作的链表
				oplist = 0;

			if (oplist<0||oplist>=num||!ListExist(L[oplist]))
			{	//检查输入操作链表的序号是否合法 以及操作的链表是否存在
				printf("\nList is NOT EXIST!\n");
				system("pause");
			}
			else	//链表序号合法且链表存在
				switch (op)
				{
				case 2:		//输入2 销毁链表
				if (DestoryList(L,oplist))
					printf("\n线性表已删除！\n");
				else
					printf("\nFalse!\n");
				system("pause");
				break;

				case 3:		//输入3 清空链表
					if (ClearList(L[oplist]))
						printf("\n线性表已清空！\n");
					else
						printf("\nFalse!\n");
					system("pause");
					break;

				case 4:		//判断链表是否为空
					if (ListEmpty(*L[oplist]))
						printf("\nList is empty!\n");
					else
						printf("\nList is NOT empty!\n");
					system("pause");
					break;

				case 5:		//输出链表长度（元素个数）
					printf("\nThe length of the list is:%d\n", ListLength(*L[oplist]));
					system("pause");
					break;

				case 6:		//获取链表某元素
					printf("\n请输入获取的元素序号：");
					scanf("%d", &temp);
					if (GetELem(*L[oplist], temp, &elemdest))
						printf("\n获取成功：%d\n", elemdest);
					else
						printf("\n获取失败！\n");
					system("pause");
					break;

				case 7:		//根据条件比对元素输出序号
					printf("\n请输入待比对数据：");
					scanf("%d", &elemsrc);
					printf("\n第一个满足的数据序号：%d\n", LocateElem(*L[oplist], elemsrc, compare));
					system("pause");
					break;

				case 8:		//输出某元素的前驱
					printf("\n请输入一个数据元素：");
					scanf("%d", &elemsrc);
					if (PriorElem(*L[oplist], elemsrc, &elemdest))
						printf("\n获取成功：%d\n", elemdest);
					else
						printf("\n获取失败！\n");
					system("pause");
					break;

				case 9:		//输出某元素的后件
					printf("\n请输入一个数据元素：");
					scanf("%d", &elemsrc);
					if (NextElem(*L[oplist], elemsrc, &elemdest))
						printf("\n获取成功：%d\n", elemdest);
					else
						printf("\n获取失败！\n");
					system("pause");
					break;
				
				case 10:		//插入元素
					printf("\n请输入插入元素序号：");
					scanf("%d", &temp);
					printf("\n请输入插入元素数值：");
					scanf("%d", &elemsrc);
					if (ListInsert(L[oplist], temp, elemsrc))
						printf("\n插入成功!\n");
					else
						printf("\nFalse!\n");
					system("pause");
					break;

				case 11:		//删除元素
					printf("\n请输入删除元素序号：");
					scanf("%d", &temp);
					if (ListDelete(L[oplist], temp, &elemdest))
						printf("\n删除成功: Delete %d\n", elemdest);
					else
						printf("\nFalse!\n");
					system("pause");
					break;

				case 12:		//遍历链表
					if (!ListTraverse(*L[oplist], visit))
						printf("线性表是空表！\n");
					system("pause");
					break;

				case 13:		//将链表中的元素存入到文件中
					if(SaveElem(*L[oplist]))
						printf("\n保存数据成功!\n");
					else
						printf("\nFalse!\n");
					system("pause");
					break;
				}
		}
		else if (op)	//输入其他数字
		{
			printf("\n输入错误!\n");
			system("pause");
		}
	}//end of while

	for (int i = 0; i < num; i++)		//退出系统前销毁所以已建链表
		DestoryList(L, i);
	printf("欢迎下次再使用本系统！\n");
}//end of main()




status InitList(LinkList** L)
{	//初始化链表：建立链表结构体（*L）并创建头结点
	(*L) = (LinkList*)malloc(sizeof(LinkList));
	(*L)->head = (Link)malloc(sizeof(struct LNode));	//带创建头节点
	(*L)->head->next = NULL;
	if (!(*L)->head)
		return OVERFLOW;
	(*L)->len = 0;
	return OK;
}

status CreateList(LinkList* L)
{	//创建链表：创建链表L的节点并输入数据（输入0时结束创建）
	Link end, New;
	int e;
	end = L->head;
	printf("Input Element:");
	scanf("%d", &e);
	if (!e)		//开始输入0则不创建结点子函数结束
		return ERROR;
	while (e)
	{
		New = (Link)malloc(sizeof(struct LNode));	//创建结点
		if (!New)
			return OVERFLOW;
		New->data = e;		//数据赋值
		New->next = end->next;
		end->next = New;
		end = New;
		L->len++;	//链表长度+1
		scanf("%d", &e);
	}
	return OK;
}

status ListExist(LinkList* L)
{	//检测链表L是否存在，FALSE不存在，TRUE存在
	if (!L)
		return FALSE;
	return TRUE;
}

status DestoryList(LinkList** L, int oplist)
{	//销毁链表L[oplist]
	Link cur, next;
	cur = L[oplist]->head;
	while (cur)		//销毁链表结点
	{
		next = cur->next;
		free(cur);
		cur = next;
	}
	free(L[oplist]);	//销毁链表结构体
	for (; oplist < num - 1; oplist++)
	{
		L[oplist] = L[oplist + 1];		//将销毁链表后的链表前移
		strcpy(listname[oplist], listname[oplist + 1]);		//销毁链表后的链表名前移
	}
	memset(listname[oplist], 0, 20);	//最后的链表名清空
	L[oplist] = NULL;
	num--;		//已建立链表数-1
	return OK;
}

status ClearList(LinkList* L)
{	//清空链表L：使链表的元素结点释放，保留头结点
	Link cur, next;
	cur = L->head->next;
	while (cur)		//释放元素结点
	{
		next = cur->next;
		free(cur);
		cur = next;
	}
	L->head->next = NULL;
	L->len = 0;		//当前链表长度置0
	return OK;
}

status ListEmpty(LinkList L)
{	//检测链表L是否为空表：TRUE为空表，FLASE表不为空
	if (L.head->next)
		return FALSE;
	return TRUE;
}

int ListLength(LinkList L)
{	//返回链表L的长度
	//Link temp;
	//int len;
	//for (len = 0, temp = L.head->next; temp; temp = temp->next)
	//	len++;
	//return len;
	return L.len;
}

status GetELem(LinkList L, int i, ElemType* e)
{	//获取链表L第i个元素并存入e中
	Link temp;
	int j;
	if (i <= 0 || i > L.len)	//i的合法性检测
		return ERROR;
	for (j = 1, temp = L.head->next; j < i; temp = temp->next, j++);//使temp指向待访问元素的结点
	*e = temp->data;//元素赋值给e
	return OK;
}

status compare(struct LNode node, ElemType e)
{	//比较函数：若结点中的元素大于e则返回TRUE，否则返回FALSE（可自定义）
	if (node.data > e)
		return TRUE;
	else
		return FALSE;
}

int LocateElem(LinkList L, ElemType e, status compare(struct LNode, ElemType))
{	//根据比较函数compare返回满足条件的第一个元素的序号
	Link temp;
	int i;
	for (i = 1, temp = L.head->next; temp; temp = temp->next, i++)
		if (compare(*temp, e))	//遍历链表并对比较
			return i;
	return 0;
}

status PriorElem(LinkList L, ElemType cur_e, ElemType* pre_e)
{	//返回链表L中元素为cur_e的前驱元素到pre_e中
	Link pre = L.head, cur = pre->next;
	if (!cur || cur_e == cur->data)		//检测链表是否为空表，同时cur_e不为第一个元素
		return ERROR;
	for (; cur; pre = cur, cur = cur->next)
		if (cur_e == cur->data)		//判断是否为cur_e
		{
			*pre_e = pre->data;
			return OK;
		}
	return ERROR;	//未找到返回ERROR
}

status NextElem(LinkList L, ElemType cur_e, ElemType* next_e)
{	//返回链表L中元素为cur_e的后继元素到next_e中
	Link cur = L.head->next, next;
	if (!cur)	//检测链表是否为空表
		return ERROR;
	next = cur->next;
	for (; next; cur = next, next = next->next)	//遍历链表至倒数第二个元素
		if (cur_e == cur->data)		//判断是否为cur_e
		{
			*next_e = next->data;
			return OK;
		}
	return ERROR;	//未找到返回ERROR
}

status ListInsert(LinkList* L, int i, ElemType e)
{	//在链表L的第i（1<=i<=len+1）个元素前插入元素e
	Link temp, New;
	int j;
	if (i<1 || i>L->len + 1)	//检测i的合法性，不合法返回ERROR
		return ERROR;
	for (j = 1, temp = L->head; j < i; j++, temp = temp->next);	//遍历到待插入位置
	New = (Link)malloc(sizeof(struct LNode));		//新建结点
	if (!New)
		return ERROR;
	New->data = e;		//结点赋值
	New->next = temp->next;		//结点链接到链表
	temp->next = New;
	L->len++;	//链表长度+1
	return OK;
}

status ListDelete(LinkList* L, int i, ElemType* e)
{	//删除链表L的第i个元素并将其值赋给e
	Link temp, dest;
	int j;
	if (i<1 || i>L->len)	//检测i的合法性，不合法返回ERROR
		return ERROR;
	for (j = 1, temp = L->head; j < i; j++, temp = temp->next);	//遍历到待删除位置
	dest = temp->next;
	*e = dest->data;		//将删除值赋给e
	temp->next = dest->next;
	free(dest);		//释放结点
	L->len--;		//链表长度-1
	return OK;
}


status ListTraverse(LinkList L, void (*visit)(ElemType))
{	//使用vist函数遍历链表L
	Link temp;
	if (!L.head->next)
		return ERROR;
	for (temp = L.head->next; temp; temp = temp->next)
		visit(temp->data);
	putchar('\n');
	return OK;
}

void visit(ElemType e)
{	//访问（输出）结点node的元素
	printf("%d\t", e);
}

status SaveElem(LinkList L)
{	//将链表L中的元素存入文件中
	Link temp;
	FILE* fp;
	char filename[30];
	printf("input file name: ");		//输入文件名
	scanf("%s", filename);
	if ((fp = fopen(filename, "wb")) == NULL)
	{
		printf("File open error!\n ");
		return ERROR;
	}
	for (temp = L.head->next; temp; temp = temp->next)
		fwrite(&temp->data, sizeof(ElemType), 1, fp);	//将每个结点中的元素写入文件中
	fclose(fp);
	return OK;
}

status LoadElem(LinkList** L, int num, char* filename)
{	//加载文件名为filename中的元素到链表L[num]中
	FILE* fp;
	Link end, New;
	ElemType temp;
	if (!ListExist(L[num]))		//若链表L[num]不存在则初始化
		InitList(&L[num]);
	else
		ClearList(L[num]);		//若链表L[num]已存在则清空链表
	if ((fp = fopen(filename, "rb")) == NULL)
	{
		printf("File open error!\n ");
		return ERROR;
	}
	end = L[num]->head;
	while (fread(&temp, sizeof(ElemType), 1, fp))
	{	//每次读入一个数据并存入到建立的链表结点中
		New = (Link)malloc(sizeof(struct LNode));
		New->data = temp;
		New->next = end->next;
		end->next = New;
		end = New;
		L[num]->len++;
	}
	return OK;
}

