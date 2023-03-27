#define _CRT_SECURE_NO_WARNINGS
//#include "LQueue.h" 
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
typedef struct node
{
	void* data;                   //数据域指针
	struct node* next;            //指向当前结点的下一结点
} Node;

typedef struct Lqueue
{
	Node* front;                   //队头
	Node* rear;                    //队尾
	size_t length;            //队列长度
} LQueue;

typedef enum
{
	FALSE = 0, TRUE = 1
} Status;

extern char type;
extern char datatype[30];
/**
 *  @name        : void InitLQueue(LQueue *Q)
 *    @description : 初始化队列
 *    @param         Q 队列指针Q
 *  @notice      : None
 */
void InitLQueue(LQueue* Q) {
	//先创造空结点
	Node* temp = (Node*)malloc(sizeof(Node));
	temp->next = NULL;

	size_t datasize;
	if (datatype[0] == 'i')datasize = sizeof(int);
	else if (datatype[0] == 'f')datasize = sizeof(float);
	else if (datatype[0] == 'c')datasize = sizeof(char);
	temp->data = (void*)malloc(datasize);
	//队列头尾指向空结点
	Q->front = temp;
	Q->rear = temp;
	Q->length = 0;
}

/**
 *  @name        : void DestoryLQueue(LQueue *Q)
 *    @description : 销毁队列
 *    @param         Q 队列指针Q
 *  @notice      : None
 */
void DestoryLQueue(LQueue* Q) {
	//遍历队列，释放每一个节点
	Node* temp =Q->front;
	while (Q->front != Q->rear)//或用长度遍历
	{
		Q->front = Q->front->next;
		free(temp->data);
		free(temp);
		temp = Q->front;
	}
	free(temp->data);
	free(temp);//修改：还要free（temp->data）
	//Q还指向一个地方，不安全,让它指向NULL;
	Q = NULL;
}

/**
 *  @name        : Status IsEmptyLQueue(const LQueue *Q)
 *    @description : 检查队列是否为空
 *    @param         Q 队列指针Q
 *    @return         : 空-TRUE; 未空-FALSE
 *  @notice      : None
 */
Status IsEmptyLQueue(const LQueue* Q) {
	//分几种情况讨论，特别注意穿空指针进来的安全性校验。
	// 错误：这函数是判断是否为空，我原来的逻辑搞反了，变成不空为真了。
	if (Q == NULL || Q->front == NULL || Q->front == Q->rear)return TRUE;
	else return FALSE;
}

/**
 *  @name        : Status GetHeadLQueue(LQueue *Q, void *e)
 *    @description : 查看队头元素
 *    @param         Q e 队列指针Q,返回数据指针e
 *    @return         : 成功-TRUE; 失败-FALSE
 *  @notice      : 队列是否空
 */
Status GetHeadLQueue(LQueue* Q, void* e) {
	//队列有头节点，应该略过，看第二个节点。
	if (Q == NULL || Q->front == NULL || Q->front->next == NULL)return FALSE;
	//或者if(Q==NULL||Q->length==0)return FALSE;
	
	//给的头文件定义了datatype和type,在LQueue和main中两次引用了该文件，重复定义了全局变量，#ifndef没有解决问题
	//但是struct类型也是全局变量，去掉typedef后也没有报错，好奇怪。
	//解决办法，在main中定义datatype，在LQueue.cpp中引用外部全局变量。
	//第二天想出来原因了，LQueue.cpp 就不应该放头文件进去,把要用到的变量要么extern包进来，要么抄一遍，结构体类型的声明。

	//数据类型判断,然后将整个内存值搬过去。
	size_t datasize;
	if (datatype[0] == 'i')datasize = sizeof(int);
	else if (datatype[0] == 'f')datasize = sizeof(float);
	else if (datatype[0] == 'c')datasize = sizeof(char);
	memcpy(e, Q->front->next->data, datasize);

	return TRUE;
}

/**
 *  @name        : int LengthLQueue(LQueue *Q)
 *    @description : 确定队列长度
 *    @param         Q 队列指针Q
 *    @return         : 成功-TRUE; 失败-FALSE
 *  @notice      : None
 */

Status LengthLQueue(LQueue* Q,int *length) {
	//按照注解的说明，改了一下头文件，原来头文件应该是错误的。
	if (Q == NULL || Q->length < 0)
	{
		return  FALSE;
	}
	else 
	{ 
		*length = Q->length;
		return   TRUE;
	}
}

/**
 *  @name        : Status EnLQueue(LQueue *Q, void *data)
 *    @description : 入队操作
 *    @param         Q 队列指针Q,入队数据指针data
 *    @return         : 成功-TRUE; 失败-FALSE
 *  @notice      : 队列是否为空
 */
Status EnLQueue(LQueue* Q, void* data) {
	//思路：在尾巴接上即可
	//结点生成
	Node* temp = (Node*)malloc(sizeof(Node));
	temp->next = NULL;

	size_t datasize;
	if (datatype[0] == 'i')datasize = sizeof(int);
	else if (datatype[0] == 'f')datasize = sizeof(float);
	else if (datatype[0] == 'c')datasize = sizeof(char);
	temp->data = (void*)malloc(datasize);
	memcpy(temp->data,data, datasize);//出错了，出错原因，temp是分配了空间，但data是指针，他没有分配空间。修改：在前面进行分配空间
	//分类讨论
	if (Q == NULL)return FALSE;
	else 
	{
		Q->rear->next = temp;
		Q->rear = temp;
		Q->length++;
	}
	return TRUE;
}

/**
 *  @name        : Status DeLQueue(LQueue *Q)
 *    @description : 出队操作
 *    @param         Q 队列指针Q
 *    @return         : 成功-TRUE; 失败-FALSE
 *  @notice      : None
 */
Status DeLQueue(LQueue* Q) {
	//思路：头部出去。
	//分类讨论
	if (Q == NULL|| Q->front == Q->rear)//只有头节点或队列不存在，返回失败
		return FALSE;
	else if(Q->front->next->next==NULL)//只有一个节点
	{
		Node* temp = Q->rear;
		Q->rear = Q->front;

		free(temp->data);
		free(temp);
		Q->length = 0;
	}
	else//有两个以上的结点
	{
		Node* temp=Q->front->next;
		Q->front->next = Q->front->next->next;

		free(temp->data);
		free(temp);
		Q->length--;
	}
		return TRUE;
}

/**
 *  @name        : void ClearLQueue(AQueue *Q)
 *    @description : 清空队列
 *    @param         Q 队列指针Q
 *  @notice      : None
 */
void ClearLQueue(LQueue* Q) {
	//思路：遍历即可。
	//分类讨论
	if (Q == NULL)return;
	else if (Q->front == Q->rear)return;

	size_t datasize;
	if (datatype[0] == 'i')datasize = sizeof(int);
	else if (datatype[0] == 'f')datasize = sizeof(float);
	else if (datatype[0] == 'c')datasize = sizeof(char);

	Node* realFront= Q->front->next;//第一个节点
	while (realFront!= Q->rear)
	{
		memset(realFront->data ,0, datasize);//学习到新函数了
		realFront = realFront->next;
	}
	memset(realFront->data, 0, datasize);
}

/**
 *  @name        : Status TraverseLQueue(const LQueue *Q, void (*foo)(void *q))
 *    @description : 遍历函数操作
 *    @param         Q 队列指针Q，操作函数指针foo
 *    @return         : None
 *  @notice      : None
 */
Status TraverseLQueue(const LQueue* Q, void (*foo)(void* q)) {
	//思路：遍历
	//分类讨论
	if (Q == NULL)return FALSE;
	else if (Q->front == Q->rear)return FALSE;

	Node* realFront = Q->front->next;//第一个节点
	while (realFront != Q->rear)
	{
		foo(realFront->data);
		realFront = realFront->next;
	}
	foo(realFront->data);
	return TRUE;
}

/**
 *  @name        : void LPrint(void *q)
 *    @description : 操作函数
 *    @param         q 指针q

 *  @notice      : None
 */
void LPrint(void* q) {
	//先写一个打印函数吧
	if (datatype[0] == 'i')
	{
		int tempData;
		int* temp=&tempData;
		memcpy(temp, q, sizeof(int));//错误：memcpy中不能有空指针。
		printf("%d\n", *temp);
	}
	else if (datatype[0] == 'f') 
	{
		float tempData;
		float* temp=&tempData;
		memcpy(temp, q, sizeof(float));
		printf("%f\n", *temp);
	}
	else if (datatype[0] == 'c')
	{
		char tempData;
		char* temp=&tempData;
		memcpy(temp, q, sizeof(char));
		printf("%c\n", *temp);
	}
}

/**************************************************************
 *    End-Multi-Include-Prevent Section
 **************************************************************/


