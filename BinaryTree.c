/* 二叉链表 */


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
#define TREEMAXNUM 9	//允许建立的最大二叉树个数
#define NULLNODE ' '	//空节点的关键字标识


typedef int status;
typedef int ElemType; //数据元素类型定义
typedef char KeyElem;	//关键字元素类型定义

typedef struct BiNode {
	KeyElem key;	//关键字
	ElemType data;	//数据
	struct BiNode* lchild, *rchild;		//左右孩子指针
}BiTNode,*BiTree;	//二叉树结点结构体

typedef struct BiTList {
	BiTree Root;	//二叉树根结点
}BiTList;	//二叉树整体结构体

typedef BiTree Qelem;	//重定义二叉树结点类型为队列数据类型

typedef struct QNode {
	Qelem data;		//数据
	struct QNode* next;		//指针域
}QNode,*QPtr;	//队列结点结构体

typedef struct {
	QPtr front, rear;		//队列队首、队尾指针
}LinkQueue;		//队列整体结构体

int num = 0;	//建立的二叉树个数
char treename[TREEMAXNUM][20];	//建立的二叉树的名称


//子函数声明
status InitQueue(LinkQueue* Q);		//初始化队列
status DestroyQueue(LinkQueue* Q);		//销毁队列
status EnQueue(LinkQueue* Q, Qelem e);		//元素入队
status DeQueue(LinkQueue* Q, Qelem* e);		//元素出队
status InitBiTree(BiTList** R);		//初始化二叉树
BiTree CreateBiTree(int count);		//创建二叉树
void ClearBiTree(BiTree* T);		//清空二叉树
void DestroyBiTree(BiTList** R,int oplist);		//销毁二叉树
status BiTreeEmpty(BiTList R);		//判定空二叉树
int BiTreeDepth(BiTree T);		//求二叉树深度
BiTree Root(BiTList R);		//获得根结点
void visit(KeyElem key, ElemType e);		//访问二叉树结点数据
BiTree Vertex(BiTree T, KeyElem key);		//获得结点指针
ElemType Value(BiTree T, KeyElem key);		//获得结点值
status Assign(BiTree T, KeyElem key, ElemType value);		//结点赋值
BiTree Parent(BiTree T, KeyElem key);		//获得双亲结点
BiTree LeftChild(BiTree T, KeyElem key);		//获得左孩子结点
BiTree RightChild(BiTree T, KeyElem key);		//获得右孩子结点
BiTree LeftSibling(BiTree T, KeyElem key);		//获得左兄弟结点
BiTree RightSibling(BiTree T, KeyElem key);		//获得右兄弟结点
status InsertChild(BiTree T, KeyElem key, int LR, BiTree c);		//插入子树
status DeleteChild(BiTree T, KeyElem key, int LR);		//删除子树
void PreOrderTraverse(BiTree T, void visit(KeyElem, ElemType));		//前序遍历
void InOrderTraverse(BiTree T, void visit(KeyElem, ElemType));		//中序遍历
void PostOrderTraverse(BiTree T, void visit(KeyElem, ElemType));		//后序遍历
void LevelOrderTraverse(BiTree T, void visit(KeyElem, ElemType));		//层序遍历
void SaveBiTNode(BiTree T, FILE* fp);		//将二叉树结点元素存入文件
status SaveBiTreeElem(BiTList R);		//将二叉树存入文件
void LoadBiTNode(BiTree* T, FILE* fp);		//从文件加载二叉树结点元素
status LoadBiTreeElem(BiTList** R, int num, char* filename);		//从文件加载二叉树


//主函数
void main(void) {
	BiTList* T[TREEMAXNUM] = { NULL };		//二叉树指针数组
	BiTree temptree=NULL;	//临时二叉树结点指针
	char tempname[20];		//临时名称
	int op = 1;
	int temp;
	int oplist;		//选择的二叉树序号
	int count = num;		//临时建立二叉树的次数（计数器）
	KeyElem tempkey;
	ElemType elemdest, elemsrc;		//源元素，目的元素

	while (op)
	{
		system("cls");	printf("\n\n");
		printf("      Menu for Binary Tree On Chain Structure \n");
		printf("-------------------------------------------------\n");
		printf("    	  1. InitBiTree        12.RightChild\n");
		printf("    	  2. DestroyBiTree     13.LeftSibling\n");
		printf("    	  3. CreatBiTree       14.RightSibling\n");
		printf("    	  4. ClearBiTree       15.InsertChild\n");
		printf("    	  5. BiTreeEmpty       16.DeleteChild\n");
		printf("    	  6. BiTreeDepth       17.PreOrderTraverse \n");
		printf("          7. Root              18.InOrderTraverse\n");
		printf("    	  8. Value             19.PostOrderTraverse\n");
		printf("    	  9. Assign            20.LevelOrderTraverse\n");
		printf("    	  10.Parent            21.SaveBiTreeElem\n");
		printf("    	  11.LeftChild         22.LoadBiTreeElem\n");
		printf("    	  0. Exit\n");
		printf("-------------------------------------------------\n");
		printf("Active Tree:\t");		//显示当前已建立的二叉树
		if (num)
			for (int i = 0; i < num; i++)
			{
				if ((i + 1) % 4 == 0)
					putchar('\n');
				printf("%d: %s\t", i, treename[i]);
			}
		printf("\n-------------------------------------------------\n");
		printf("    请选择你的操作[0~22]:");
		scanf("%d", &op);

		if (op == 1)
		{	//输入1则初始化二叉树
			if (InitBiTree(&T[num % TREEMAXNUM]))
			{	//若建立二叉树成功对链表临时命名
				memset(tempname, 0, 20);
				strcat(tempname, "temp");
				_itoa(count, tempname + 4, 10);
				strcpy(treename[num % TREEMAXNUM], tempname);
				num = (num >= TREEMAXNUM ? TREEMAXNUM : num + 1);
				//若已建立二叉树未超过最大数目：建立二叉树个数+1，否则保持最大数目不变（超过最大数目的二叉树一直覆盖第一个二叉树）
				count++;	//计数器+1
				printf("\n二叉树初始化成功！\n");
			}
			else
				printf("\n二叉树初始化失败！\n");
			system("pause");
		}
	
		else if (op == 22)
		{	//输入22加载文件中的数据
			printf("input file name: ");
			scanf("%s", tempname);
			if (LoadBiTreeElem(T,num,tempname))
			{	//加载数据成功则对二叉树命名为文件名
				strcpy(treename[num % TREEMAXNUM], tempname);
				num = (num >= TREEMAXNUM ? TREEMAXNUM : num + 1);
				printf("\n二叉树数据加载成功!\n");
			}
			else
				printf("\nFalse!\n");
			system("pause");
		}
		else if (op > 1 && op < 22)
		{	//输入其他选项
			if (num > 1)
			{	//若已建立链表数＞1则操作前需要确定操作链表的序号
				printf("请输入操作链表序号：");
				scanf("%d", &oplist);
			}
			else	//若仅有一个链表，则该链表默认为操作的链表
				oplist = 0;

			if (oplist < 0 || oplist >= num || !T[oplist])
			{	//检查输入操作二叉树的序号是否合法 以及操作的二叉树是否存在
				printf("\nBiTree is NOT EXIST!\n");
				system("pause");
			}
			else	//二叉树序号合法且二叉树存在
				switch (op)
				{
				case 2:		//输入2 销毁二叉树
					DestroyBiTree(T,oplist);
					printf("\n二叉树已销毁!\n");
					system("pause");
					break;

				case 3:		//输入3 创建二叉树
					T[oplist]->Root = CreateBiTree(1);
					printf("二叉树已建立成功!\n");
					system("pause");
					break;
				case 4:		//输入4 清空二叉树
					if (T[oplist] && T[oplist]->Root)
					{
						ClearBiTree(&T[oplist]->Root);
						printf("\n二叉树已清空!\n");
					}
					else
						printf("\n二叉树清空失败！\n");
					system("pause");
					break;

				case 5:		//判断二叉树是否为空
					if (BiTreeEmpty(*T[oplist]))
						printf("\nBiTree is empty!\n");
					else
						printf("\nBiTree is NOT empty!\n");
					system("pause");
					break;

				case 6:		//输出二叉树深度
					printf("\n二叉树深度为:%d\n", BiTreeDepth(T[oplist]->Root));
					system("pause");
					break;

				case 7:		//求二叉树根结点并输出
					if (temptree = Root(*T[oplist]))
					{
						printf("\n根结点：");
						visit(temptree->key, temptree->data);
					}
					else
						printf("\n根结点为空！\n");
					putchar('\n');
					system("pause");
					break;

				case 8:		//获取结点数据值
					printf("请输入搜索关键字：");
					scanf("%*c%c", &tempkey);
					elemdest = Value(T[oplist]->Root, tempkey);
					if ( elemdest== -1)
						printf("\n该结点未找到！\n");
					else
						printf("\n该结点已找到，数据值：%d\n", elemdest);
					system("pause");
					break;

				case 9:		//结点赋值
					printf("请输入搜索关键字：");
					scanf("%*c%c", &tempkey);
					printf("\n请输入新的数据：");
					scanf("%d", &elemsrc);
					if (Assign(T[oplist]->Root, tempkey, elemsrc))
						printf("\n结点已重新赋值！\n");
					else
						printf("\n结点赋值失败！\n");
					system("pause");
					break;

				case 10:		//获得双亲结点并输出
					printf("请输入搜索关键字：");
					scanf("%*c%c", &tempkey);
					if (temptree = Parent(T[oplist]->Root, tempkey))
					{
						printf("\n其双亲结点为 ");
						visit(temptree->key, temptree->data);
						putchar('\n');
					}
					else
						printf("\n结点双亲获得失败！\n");
					system("pause");
					break;

				case 11:		//获得左孩子结点并输出
					printf("请输入搜索关键字：");
					scanf("%*c%c", &tempkey);
					if (temptree = LeftChild(T[oplist]->Root, tempkey))
					{
						printf("\n其左孩子结点为 ");
						visit(temptree->key, temptree->data);
						putchar('\n');
					}
					else
						printf("\n结点左孩子获得失败！\n");
					system("pause");
					break;

				case 12:		//获得右孩子结点并输出
					printf("请输入搜索关键字：");
					scanf("%*c%c", &tempkey);
					if (temptree = RightChild(T[oplist]->Root, tempkey))
					{
						printf("\n其右孩子结点为 ");
						visit(temptree->key, temptree->data);
						putchar('\n');
					}
					else
						printf("\n结点右孩子获得失败！\n");
					system("pause");
					break;

				case 13:		//获得左兄弟结点并输出
					printf("请输入搜索关键字：");
					scanf("%*c%c", &tempkey);
					if (temptree = LeftSibling(T[oplist]->Root, tempkey))
					{
						printf("\n其左兄弟结点为 ");
						visit(temptree->key, temptree->data);
						putchar('\n');
					}
					else
						printf("\n结点左兄弟获得失败！\n");
					system("pause");
					break;

				case 14:		//获得右兄弟结点并输出
					printf("请输入搜索关键字：");
					scanf("%*c%c", &tempkey);
					if (temptree = RightSibling(T[oplist]->Root, tempkey))
					{
						printf("\n其右兄弟结点为 ");
						visit(temptree->key, temptree->data);
						putchar('\n');
					}
					else
						printf("\n结点右兄弟获得失败！\n");
					system("pause");
					break;

				case 15:		//插入子树
					printf("建立插入子树c：\n");
					printf("需输入1个结点\n请输入关键字:");
					scanf("%*c%c", &tempkey);	//输入子树根结点
					if (tempkey == NULLNODE)	//若子树根结点为空则不合法
					{
						printf("\n建立子树不合法！\n");
						system("pause");
						break;
					}
					
					temptree = (BiTree)malloc(sizeof(BiTNode));		//若子树根结点不为空继续操作
					if (!temptree)
					{
						printf("建立子树失败！\n");
						system("pause");
						break;
					}
					temptree->key = tempkey;
					printf("请输入数据:");
					scanf("%d", &temptree->data);
					//temptree->father = NULL;//
					temptree->lchild = CreateBiTree(1);	//仅递归创建子树的左子树，右子树为空
					temptree->rchild = NULL;
				
					printf("\n请输入搜索关键字：");
					scanf("%*c%c", &tempkey);
					printf("\n请输入操作子树(0.左子树/1.右子树):");
					scanf("%d", &temp);
					if (temp != 0 && temp != 1)
					{
						printf("\n输入错误!\n");
						system("pause");
						break;
					}
					if (InsertChild(T[oplist]->Root, tempkey, temp, temptree))
						printf("\n插入子树成功！\n");
					else
						printf("\n插入子树失败！\n");
					system("pause");
					break;

				case 16:		//删除子树
					printf("\n请输入搜索关键字：");
					scanf("%*c%c", &tempkey);
					printf("\n请输入操作子树(0.左子树/1.右子树):");
					scanf("%d", &temp);
					if (temp != 0 && temp != 1)
					{
						printf("\n输入错误!\n");
						system("pause");
						break;
					}
					if (DeleteChild(T[oplist]->Root, tempkey, temp))
						printf("\n删除子树成功！\n");
					else
						printf("\n删除子树失败！\n");
					system("pause");
					break;

				case 17:
					printf("前序遍历：");
					PreOrderTraverse(T[oplist]->Root,visit);
					putchar('\n');
					system("pause");
					break;

				case 18:
					printf("中序遍历：");
					InOrderTraverse(T[oplist]->Root, visit);
					putchar('\n');
					system("pause");
					break;

				case 19:
					printf("后序遍历：");
					PostOrderTraverse(T[oplist]->Root, visit);
					putchar('\n');
					system("pause");
					break;

				case 20:
					printf("层序遍历：");
					LevelOrderTraverse(T[oplist]->Root, visit);
					putchar('\n');
					system("pause");
					break;
							
				case 21:		//将二叉树中的元素存入到文件中
					if (SaveBiTreeElem(*T[oplist]))
						printf("\n二叉树数据已保存!\n");
					else
						printf("\n二叉树数据保存失败！\n");
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

	for (int i = 0; i < num; i++)		//退出系统前销毁所以已建二叉树
		DestroyBiTree(T,i);
	printf("欢迎下次再使用本系统！\n");
}//end of main()


status InitQueue(LinkQueue* Q)
{	//初始化队列
	Q->front = Q->rear = (QPtr)malloc(sizeof(QNode));	//创建首尾结点
	if (!Q->front)
		exit(OVERFLOW);
	Q->front->next = NULL;	//结点指针为空
	return OK;
}

status DestroyQueue(LinkQueue* Q)
{	//销毁队列
	while (Q->front)	//队首指针不为空则释放当前所指结点
	{
		Q->rear = Q->front->next;
		free(Q->front);
		Q->front = Q->rear;
	}
	return OK;
}

status EnQueue(LinkQueue* Q, Qelem e)
{	//元素入队
	QPtr p;
	p = (QPtr)malloc(sizeof(QNode));	//创建队列结点
	if (!p)
		return FALSE;
	p->data = e;		//队列数据赋值
	p->next = NULL;
	Q->rear->next = p;	//队首队尾指针操作
	Q->rear = p;
	return OK;
}

status DeQueue(LinkQueue* Q, Qelem* e)
{	//元素出队
	QPtr p;
	if (Q->front == Q->rear)	//队列为空返回失败
		return ERROR;
	p = Q->front->next;
	*e = p->data;		//队首元素赋值
	Q->front->next = p->next;
	if (Q->rear == p)		//若出队后队空则首尾指针指向一处
		Q->rear = Q->front;
	free(p);
	return OK;
}

status InitBiTree(BiTList** R)
{	//初始化二叉树R
	(*R) = (BiTList*)malloc(sizeof(BiTList));	//创建二叉树结构体
	if (!(*R)->Root)
		return OVERFLOW;
	(*R)->Root = NULL;		//二叉树根结点设为空指针
	return OK;
}

BiTree CreateBiTree(int count)
{	//创建二叉树：count为当前还需输入的结点个数
	KeyElem e;
	BiTree New = NULL;
	printf("需输入%d个结点\n请输入关键字:", count);
	scanf("%*c%c", &e);
	count--;	//需输入结点个数-1
	if (e != NULLNODE)		//若输入的关键字不为空节点标识
	{
		New = (BiTree)malloc(sizeof(BiTNode));		//创建二叉树结点
		if (!New)
			return FALSE;
		New->key = e;		//结点赋值
		printf("请输入数据:");
		scanf("%d", &New->data);
		//New->father = father;	//
		New->lchild = CreateBiTree(count + 2);		//递归建立子节点
		New->rchild = CreateBiTree(count + 1);
	}
	return New;		//返回二叉树根结点
}


void ClearBiTree(BiTree* T)
{	//清空二叉树T
	if ((*T)->lchild)	//若二叉树T的子节点不为空则先递归清空子树
		ClearBiTree(&(*T)->lchild);
	if ((*T)->rchild)
		ClearBiTree(&(*T)->rchild);
	if (!(*T)->lchild && !(*T)->rchild)		//若T是叶子结点
	{
		free(*T);	//则释放结点内存
		*T = NULL;	//指针指向空
	}
}

void DestroyBiTree(BiTList** R,int oplist)
{	//销毁二叉树R[oplist]
	if(R[oplist]->Root)
		ClearBiTree(&R[oplist]->Root);	//先清空二叉树所有结点
	free(R[oplist]);	//释放二叉树结构体
	for (; oplist < num - 1; oplist++)
	{
		R[oplist] = R[oplist + 1];		//将销毁二叉树后的二叉树前移
		strcpy(treename[oplist], treename[oplist + 1]);		//销毁二叉树后的二叉树名称前移
	}
	memset(treename[oplist], 0, 20);	//最后二叉树名称清空
	R[oplist] = NULL;		//二叉树指针指向空
	num--;		//已建立二叉树个数-1
}


status BiTreeEmpty(BiTList R)
{	//判定R是否为空二叉树：TRUE树空，FALSE树不为空
	if (R.Root)		//若二叉树根结点不为空
		return FALSE;		//则树不为空
	else		//若二叉树根结点为空
		return TRUE;	//则二叉树为空
}

int BiTreeDepth(BiTree T)
{	//求二叉树T的深度：返回二叉树深度的整数
	int dep = 0;	//初始化树的深度为0
	int i, j;
	if (T)	//若T的根结点结点不为空
	{
		dep++;		//树的深度+1
		i = BiTreeDepth(T->lchild);		//递归求结点的左右子树深度
		j = BiTreeDepth(T->rchild);
		dep += i > j ? i : j;	//树T的深度为原深度+子树深度大的深度
	}
	return dep;		//返回树的深度
}


BiTree Root(BiTList R)
{	//返回二叉树R的根结点
	return R.Root;
}

void visit(KeyElem key, ElemType e)
{	//结点数据访问
	printf("%c:%d\t", key, e);		//输出结点关键字和数据
}

BiTree Vertex(BiTree T, KeyElem key)
{	//获得结点：返回二叉树T中指向关键字为key的结点指针
	BiTree temp1 = NULL, temp2 = NULL;
	if (T)		//若当前结点T不为空
	{
		if (T->key == key)	//若当前结点T的关键字即为所找
			return T;		//则直接返回当前结点指针
		if (T->lchild)		//若当前结点有左孩子结点
			temp1 = Vertex(T->lchild, key);	//递归寻找结点并返回给temp1
		if (temp1)		//若temp1不为空则已找到结点
			return temp1;		//返回temp1所指结点指针
		if (T->rchild)		//若左子树未找到，且有右子树
			temp2 = Vertex(T->rchild, key);		//递归寻找结点并返回给temp2
		return temp2;		//返回temp2
	}
	return NULL;	//若根结点T为空直接返回NULL
}

ElemType Value(BiTree T, KeyElem key)
{	//获得结点值：返回二叉树T中关键字为key的结点的数据值，未找到返回-1
	BiTree temp = Vertex(T, key);	//temp为指向key结点的指针
	if (temp)		//若temp不为空
		return temp->data;		//则返回结点的数据
	return -1;		//若temp为空则返回-1（表示未找到）
}

status Assign(BiTree T, KeyElem key, ElemType value)
{	//结点赋值：给二叉树T中关键字为key的结点赋值value
	BiTree temp = Vertex(T, key);		//temp为指向key结点的指针
	if (temp)		//若temp不为空
	{
		temp->data = value;		//结点的数据重新赋值
		return OK;		//返回成功
	}
	return ERROR;		//未找到返回失败
}

BiTree Parent(BiTree T, KeyElem key)
{	//获得双亲结点：返回二叉树T中关键字为key的结点的双亲结点指针，其他情况返回NULL
	BiTree temp1 = NULL, temp2 = NULL;
	if (T)	//若当前节点T不为空
	{
		if (T->lchild && T->lchild->key == key)
			return T;		//若T有左子树且左子树的关键字为key则返回T
		if (T->rchild && T->rchild->key == key)
			return T;		//若T有右子树且右子树的关键字为key则返回T
		if (T->lchild)		//若T有左孩子
			temp1 = Parent(T->lchild, key);		//递归寻找双亲
		if (temp1)
			return temp1;	//若在左子树找到双亲则返回
		if (T->rchild)		//否则在右子树查找并返回
			temp2 = Parent(T->rchild, key);
		return temp2;
	}
	return NULL;		//若根结点T为空直接返回NULL
}

BiTree LeftChild(BiTree T, KeyElem key)
{	//获得左孩子结点：返回二叉树T中关键字为key的结点的左孩子结点指针
	BiTree temp = Vertex(T, key);		//temp为指向key结点的指针
	if (temp)
		return temp->lchild;		//temp不为空返回左孩子指针
	return NULL;		//未找到返回NULL
}

BiTree RightChild(BiTree T, KeyElem key)
{	//获得右孩子结点：返回二叉树T中关键字为key的结点的右孩子结点指针
	BiTree temp = Vertex(T, key);		//temp为指向key结点的指针
	if (temp)
		return temp->rchild;		//temp不为空返回右孩子指针
	return NULL;		//未找到返回NULL
}

BiTree LeftSibling(BiTree T, KeyElem key)
{	//获得左兄弟结点：返回二叉树T中关键字为key的结点的左兄弟结点指针
	BiTree dad = Parent(T, key);	//dad为key结点的双亲结点
	if (dad && dad->lchild && dad->lchild->key != key)//若key结点有双亲结点、双亲结点有左孩子且左孩子不为key结点
		return dad->lchild;		//返回双亲结点的左孩子
	return NULL;		//其他情况返回NULL
}

BiTree RightSibling(BiTree T, KeyElem key)
{	//获得右兄弟结点：返回二叉树T中关键字为key的结点的右兄弟结点指针
	BiTree dad = Parent(T, key);	//dad为key结点的双亲结点
	if (dad && dad->rchild && dad->rchild->key != key)//若key结点有双亲结点、双亲结点有右孩子且右孩子不为key结点
		return dad->rchild;		//返回双亲结点的右孩子
	return NULL;		//其他情况返回NULL
}

status InsertChild(BiTree T, KeyElem key, int LR, BiTree c)
{	//插入子树：在二叉树T中key结点的LR（0为左/1为右）子树插入子树c
	BiTree p = Vertex(T, key);		//p指向key结点
	if (!p)		//若结点未找到则返回失败
		return ERROR;
	if (LR)		//插入到左子树
	{
		c->rchild = p->rchild;
		p->rchild = c;
	}
	else		//插入到右子树
	{
		c->rchild = p->lchild;
		p->lchild = c;
	}
	return OK;		//返回成功
}

status DeleteChild(BiTree T, KeyElem key, int LR)
{	//删除子树：删除二叉树T中关键字为key的结点的LR子树
	BiTree p = Vertex(T, key);		//p为key结点
	if (!p)		//若结点未找到返回失败
		return ERROR;
	if (LR && p->rchild)	//删除左子树
		ClearBiTree(&p->rchild);
	else if (p->lchild)		//删除右子树
		ClearBiTree(&p->lchild);
	return OK;		//返回成功
}

void PreOrderTraverse(BiTree T, void visit(KeyElem, ElemType))
{	//先序遍历
	if (T)		//当前结点不为空
	{
		visit(T->key, T->data);		//先访问数据
		PreOrderTraverse(T->lchild, visit);		//在依次递归先序遍历左右子树
		PreOrderTraverse(T->rchild, visit);
	}
}

void InOrderTraverse(BiTree T, void visit(KeyElem, ElemType))
{	//中序遍历
	if (T)		//当前结点不为空
	{
		InOrderTraverse(T->lchild, visit);		//先递归中序遍历左子树
		visit(T->key, T->data);		//再访问当前节点数据
		InOrderTraverse(T->rchild, visit);		//最后递归中序遍历右子树
	}
}

void PostOrderTraverse(BiTree T, void visit(KeyElem, ElemType))
{	//后序遍历
	if (T)		//当前结点不为空
	{
		PostOrderTraverse(T->lchild, visit);	//先依次递归后序遍历左右子树
		PostOrderTraverse(T->rchild, visit);
		visit(T->key, T->data);		//最后访问数据
	}
}

void LevelOrderTraverse(BiTree T, void visit(KeyElem, ElemType))
{	//层序遍历
	BiTree temp = T;	//temp指向二叉树根结点
	LinkQueue Q;	
	if (!T)
		return;
	InitQueue(&Q);	//初始化队列Q
	do {
		visit(temp->key, temp->data);	//先访问当前结点
		if (temp->lchild)		//若当前结点有左孩子则左孩子入队
			EnQueue(&Q, temp->lchild);
		if (temp->rchild)		//若当前节点有右孩子则右孩子入队
			EnQueue(&Q, temp->rchild);
	} while (DeQueue(&Q, &temp));	//若队列能出队一个元素则继续循环，出队元素赋值给temp
	DestroyQueue(&Q);
}

void SaveBiTNode(BiTree T, FILE* fp)
{	//将结点T中数据存入文件
	KeyElem nullkey = NULLNODE;		//nullkey为空结点标识
	if (!T)		//若当前节点T为空则仅读入空节点标识
	{
		fwrite(&nullkey, sizeof(KeyElem), 1, fp);
		return;
	}
	fwrite(&T->key, sizeof(KeyElem), 1, fp);	//结点T不为空则依次读入关键字和数据
	fwrite(&T->data, sizeof(ElemType), 1, fp);
	SaveBiTNode(T->lchild, fp);		//递归将当前节点左右孩子存入文件
	SaveBiTNode(T->rchild, fp);
}

status SaveBiTreeElem(BiTList R)
{	//将二叉树R的数据存入文件
	FILE* fp;
	char filename[30];
	printf("input file name: ");		//输入文件名
	scanf("%s", filename);
	if ((fp = fopen(filename, "wb")) == NULL)
	{
		printf("File open error!\n ");
		return ERROR;
	}
	SaveBiTNode(R.Root, fp);	//从根结点递归存入文件
	fclose(fp);
	return OK;
}

void LoadBiTNode(BiTree* T, FILE* fp)
{	//从文件加载到二叉树结点T
	KeyElem tempkey;
	ElemType tempdata;
	if (fread(&tempkey, sizeof(KeyElem), 1, fp))	//首先读取一个关键字
	{
		if (tempkey == NULLNODE)		//若读入的为空节点标识
		{
			*T = NULL;		//则当前结点为空并返回
			return;
		}	
		fread(&tempdata, sizeof(ElemType), 1, fp);		//若当前节点不为空则继续将数据读入
		(*T) = (BiTree)malloc(sizeof(BiTNode));		//创建一个二叉树结点
		(*T)->key = tempkey;		//结点赋值
		(*T)->data = tempdata;
		LoadBiTNode(&(*T)->lchild, fp);		//递归加载当前结点的左右子树
		LoadBiTNode(&(*T)->rchild, fp);
	}
}

status LoadBiTreeElem(BiTList** R, int num, char* filename)
{	//从filename文件中读入数据到二叉树R[num]
	FILE* fp;

	if (!R[num])	//若二叉树R[num]不存在则初始化二叉树
		InitBiTree(&R[num]);
	else	//若已存在则清空树
		ClearBiTree(&R[num]->Root);
	if ((fp = fopen(filename, "rb")) == NULL)
	{
		printf("File open error!\n ");
		return ERROR;
	}
	LoadBiTNode(&R[num]->Root, fp);		//从根结点递归加载数据到结点
	fclose(fp);
	return OK;
}

