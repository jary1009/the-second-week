#ifndef STACK_H_INCLUDED
#define STACK_H_INCLUDED
//改成char类型
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

//放int的栈
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

//链栈
Status initLStack(LinkStack* s);//初始化栈
Status isEmptyLStack(LinkStack* s);//判断栈是否为空
Status getTopLStack(LinkStack* s, ElemType* e);//得到栈顶元素
Status clearLStack(LinkStack* s);//清空栈
Status destroyLStack(LinkStack* s);//销毁栈
Status LStackLength(LinkStack* s, int* length);//检测栈长度
Status pushLStack(LinkStack* s, ElemType data);//入栈
Status popLStack(LinkStack* s, ElemType* data);//出栈
//加一个遍历函数
void LStackPrint(char q);
Status TraverseLinkStack(LinkStack*, void(*f)(char q));

//放int的栈的进出栈函数,还有初始化函数
Status initLStack1(LinkStack1* s);
Status pushLStack1(LinkStack1* s, int data);//入栈
Status popLStack1(LinkStack1* s, int* data);//出栈
#endif 
