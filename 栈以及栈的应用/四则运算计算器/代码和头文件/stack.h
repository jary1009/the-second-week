#ifndef STACK_H_INCLUDED
#define STACK_H_INCLUDED
//�ĳ�char����
typedef enum Status
{
	ERROR = 0,
	SUCCESS = 1
} Status;

typedef char ElemType;

typedef  struct StackNode
{
	ElemType data;
	struct StackNode* next;
}StackNode, * LinkStackPtr;

typedef  struct  LinkStack
{
	LinkStackPtr top;
	int	count;
}LinkStack;

//��int��ջ
typedef  struct StackNode1
{
	int data;
	struct StackNode1* next;
}StackNode1, * LinkStackPtr1;

typedef  struct  LinkStack1
{
	LinkStackPtr1 top;
	int	count;
}LinkStack1;

//��ջ
Status initLStack(LinkStack* s);//��ʼ��ջ
Status isEmptyLStack(LinkStack* s);//�ж�ջ�Ƿ�Ϊ��
Status getTopLStack(LinkStack* s, ElemType* e);//�õ�ջ��Ԫ��
Status clearLStack(LinkStack* s);//���ջ
Status destroyLStack(LinkStack* s);//����ջ
Status LStackLength(LinkStack* s, int* length);//���ջ����
Status pushLStack(LinkStack* s, ElemType data);//��ջ
Status popLStack(LinkStack* s, ElemType* data);//��ջ
//��һ����������
void LStackPrint(char q);
Status TraverseLinkStack(LinkStack*, void(*f)(char q));

//��int��ջ�Ľ���ջ����,���г�ʼ������
Status initLStack1(LinkStack1* s);
Status pushLStack1(LinkStack1* s, int data);//��ջ
Status popLStack1(LinkStack1* s, int* data);//��ջ
#endif 
