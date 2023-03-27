#define _CRT_SECURE_NO_WARNINGS
//#include "LQueue.h" 
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
typedef struct node
{
	void* data;                   //������ָ��
	struct node* next;            //ָ��ǰ������һ���
} Node;

typedef struct Lqueue
{
	Node* front;                   //��ͷ
	Node* rear;                    //��β
	size_t length;            //���г���
} LQueue;

typedef enum
{
	FALSE = 0, TRUE = 1
} Status;

extern char type;
extern char datatype[30];
/**
 *  @name        : void InitLQueue(LQueue *Q)
 *    @description : ��ʼ������
 *    @param         Q ����ָ��Q
 *  @notice      : None
 */
void InitLQueue(LQueue* Q) {
	//�ȴ���ս��
	Node* temp = (Node*)malloc(sizeof(Node));
	temp->next = NULL;

	size_t datasize;
	if (datatype[0] == 'i')datasize = sizeof(int);
	else if (datatype[0] == 'f')datasize = sizeof(float);
	else if (datatype[0] == 'c')datasize = sizeof(char);
	temp->data = (void*)malloc(datasize);
	//����ͷβָ��ս��
	Q->front = temp;
	Q->rear = temp;
	Q->length = 0;
}

/**
 *  @name        : void DestoryLQueue(LQueue *Q)
 *    @description : ���ٶ���
 *    @param         Q ����ָ��Q
 *  @notice      : None
 */
void DestoryLQueue(LQueue* Q) {
	//�������У��ͷ�ÿһ���ڵ�
	Node* temp =Q->front;
	while (Q->front != Q->rear)//���ó��ȱ���
	{
		Q->front = Q->front->next;
		free(temp->data);
		free(temp);
		temp = Q->front;
	}
	free(temp->data);
	free(temp);//�޸ģ���Ҫfree��temp->data��
	//Q��ָ��һ���ط�������ȫ,����ָ��NULL;
	Q = NULL;
}

/**
 *  @name        : Status IsEmptyLQueue(const LQueue *Q)
 *    @description : �������Ƿ�Ϊ��
 *    @param         Q ����ָ��Q
 *    @return         : ��-TRUE; δ��-FALSE
 *  @notice      : None
 */
Status IsEmptyLQueue(const LQueue* Q) {
	//�ּ���������ۣ��ر�ע�⴩��ָ������İ�ȫ��У�顣
	// �����⺯�����ж��Ƿ�Ϊ�գ���ԭ�����߼��㷴�ˣ���ɲ���Ϊ���ˡ�
	if (Q == NULL || Q->front == NULL || Q->front == Q->rear)return TRUE;
	else return FALSE;
}

/**
 *  @name        : Status GetHeadLQueue(LQueue *Q, void *e)
 *    @description : �鿴��ͷԪ��
 *    @param         Q e ����ָ��Q,��������ָ��e
 *    @return         : �ɹ�-TRUE; ʧ��-FALSE
 *  @notice      : �����Ƿ��
 */
Status GetHeadLQueue(LQueue* Q, void* e) {
	//������ͷ�ڵ㣬Ӧ���Թ������ڶ����ڵ㡣
	if (Q == NULL || Q->front == NULL || Q->front->next == NULL)return FALSE;
	//����if(Q==NULL||Q->length==0)return FALSE;
	
	//����ͷ�ļ�������datatype��type,��LQueue��main�����������˸��ļ����ظ�������ȫ�ֱ�����#ifndefû�н������
	//����struct����Ҳ��ȫ�ֱ�����ȥ��typedef��Ҳû�б�������֡�
	//����취����main�ж���datatype����LQueue.cpp�������ⲿȫ�ֱ�����
	//�ڶ��������ԭ���ˣ�LQueue.cpp �Ͳ�Ӧ�÷�ͷ�ļ���ȥ,��Ҫ�õ��ı���Ҫôextern��������Ҫô��һ�飬�ṹ�����͵�������

	//���������ж�,Ȼ�������ڴ�ֵ���ȥ��
	size_t datasize;
	if (datatype[0] == 'i')datasize = sizeof(int);
	else if (datatype[0] == 'f')datasize = sizeof(float);
	else if (datatype[0] == 'c')datasize = sizeof(char);
	memcpy(e, Q->front->next->data, datasize);

	return TRUE;
}

/**
 *  @name        : int LengthLQueue(LQueue *Q)
 *    @description : ȷ�����г���
 *    @param         Q ����ָ��Q
 *    @return         : �ɹ�-TRUE; ʧ��-FALSE
 *  @notice      : None
 */

Status LengthLQueue(LQueue* Q,int *length) {
	//����ע���˵��������һ��ͷ�ļ���ԭ��ͷ�ļ�Ӧ���Ǵ���ġ�
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
 *    @description : ��Ӳ���
 *    @param         Q ����ָ��Q,�������ָ��data
 *    @return         : �ɹ�-TRUE; ʧ��-FALSE
 *  @notice      : �����Ƿ�Ϊ��
 */
Status EnLQueue(LQueue* Q, void* data) {
	//˼·����β�ͽ��ϼ���
	//�������
	Node* temp = (Node*)malloc(sizeof(Node));
	temp->next = NULL;

	size_t datasize;
	if (datatype[0] == 'i')datasize = sizeof(int);
	else if (datatype[0] == 'f')datasize = sizeof(float);
	else if (datatype[0] == 'c')datasize = sizeof(char);
	temp->data = (void*)malloc(datasize);
	memcpy(temp->data,data, datasize);//�����ˣ�����ԭ��temp�Ƿ����˿ռ䣬��data��ָ�룬��û�з���ռ䡣�޸ģ���ǰ����з���ռ�
	//��������
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
 *    @description : ���Ӳ���
 *    @param         Q ����ָ��Q
 *    @return         : �ɹ�-TRUE; ʧ��-FALSE
 *  @notice      : None
 */
Status DeLQueue(LQueue* Q) {
	//˼·��ͷ����ȥ��
	//��������
	if (Q == NULL|| Q->front == Q->rear)//ֻ��ͷ�ڵ����в����ڣ�����ʧ��
		return FALSE;
	else if(Q->front->next->next==NULL)//ֻ��һ���ڵ�
	{
		Node* temp = Q->rear;
		Q->rear = Q->front;

		free(temp->data);
		free(temp);
		Q->length = 0;
	}
	else//���������ϵĽ��
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
 *    @description : ��ն���
 *    @param         Q ����ָ��Q
 *  @notice      : None
 */
void ClearLQueue(LQueue* Q) {
	//˼·���������ɡ�
	//��������
	if (Q == NULL)return;
	else if (Q->front == Q->rear)return;

	size_t datasize;
	if (datatype[0] == 'i')datasize = sizeof(int);
	else if (datatype[0] == 'f')datasize = sizeof(float);
	else if (datatype[0] == 'c')datasize = sizeof(char);

	Node* realFront= Q->front->next;//��һ���ڵ�
	while (realFront!= Q->rear)
	{
		memset(realFront->data ,0, datasize);//ѧϰ���º�����
		realFront = realFront->next;
	}
	memset(realFront->data, 0, datasize);
}

/**
 *  @name        : Status TraverseLQueue(const LQueue *Q, void (*foo)(void *q))
 *    @description : ������������
 *    @param         Q ����ָ��Q����������ָ��foo
 *    @return         : None
 *  @notice      : None
 */
Status TraverseLQueue(const LQueue* Q, void (*foo)(void* q)) {
	//˼·������
	//��������
	if (Q == NULL)return FALSE;
	else if (Q->front == Q->rear)return FALSE;

	Node* realFront = Q->front->next;//��һ���ڵ�
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
 *    @description : ��������
 *    @param         q ָ��q

 *  @notice      : None
 */
void LPrint(void* q) {
	//��дһ����ӡ������
	if (datatype[0] == 'i')
	{
		int tempData;
		int* temp=&tempData;
		memcpy(temp, q, sizeof(int));//����memcpy�в����п�ָ�롣
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


