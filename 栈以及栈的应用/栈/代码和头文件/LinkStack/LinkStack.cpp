//定义类型
#include<stdlib.h>
#include<stdio.h>
typedef enum Status
{
	ERROR = 0,
	SUCCESS = 1
} Status;
//这个好，不是泛型，省去一些工作了
typedef int ElemType;

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

//初始化栈
//初始化1：s在函数内给一个空间，此时传入LinkStack** s；
//初始化2：s传入函数以前就指向一个空间，此时只让top=0，count=0即可。
//该头文件应该是第二种意思。
Status initLStack(LinkStack* s) {
	//栈不需要头节点，这初始化只需要让栈顶指针指向空。
	//怎么才能初始化失败呢？

	s->top = NULL;//NULL在stdlib.h中定义了，引用它。
	s->count = 0;
	return SUCCESS;
}

//判断栈是否为空
Status isEmptyLStack(LinkStack* s) {
	if (s == NULL)exit(-1);//穿个空指针进来，直接寄
	else if (s->count != 0)return ERROR;
	return SUCCESS;
}

//得到栈顶元素
Status getTopLStack(LinkStack* s, ElemType* e) {
	if (s == NULL)return ERROR;
	if (s->count == 0)return ERROR;//测试中发现。
	else 
	{
		*e = s->top->data;
		return SUCCESS;
	}
}

//清空栈
Status clearLStack(LinkStack* s) {
	//遍历
	if (s == NULL)return ERROR;
	StackNode* temp = s->top;
	for (int i = 0; i < s->count; i++)
	{
		s->top->data = 0;
		s->top = s->top->next;
	}
	s->top = temp;
	return SUCCESS;
}

//销毁栈
Status destroyLStack(LinkStack* s) {
	if (s == NULL)return ERROR;
	StackNode* temp = s->top;
	for (int i = 0; i < s->count; i++)
	{
		s->top = s->top->next;
		free(temp);
		temp = s->top;
	}
	free(s);
	s = NULL;
	return SUCCESS;
}

//检测栈长度
Status LStackLength(LinkStack* s, int* length) {
	if (s == NULL)return ERROR;
	*length = s->count;
	return SUCCESS;

}

//入栈
Status pushLStack(LinkStack* s, ElemType data) {
	//思路：创造一个结点，接到头部
	if (s == NULL)return ERROR;
	StackNode* temp = (StackNode*)malloc(sizeof(StackNode));
	if (temp == NULL)return ERROR;
	temp->data = data;
	temp->next = s->top;

	s->top = temp;
	s->count++;
	return SUCCESS;
}

//出栈
Status popLStack(LinkStack* s, ElemType* data) {
	//思路：修改top，free掉第一个节点即可
	if (s == NULL)return ERROR;
	if (s->top == NULL)return ERROR;
	StackNode* temp = s->top;
	*data = s->top->data;//栈为空时不能出栈，测试中发现bug。
	s->top = s->top->next;
	s->count--;//差点忘了，测试中发现bug。
	free(temp);
	return SUCCESS;
}

//加一个遍历函数
void LStackPrint(int q) 
{
	printf("%d\n", q);
	return;
}

Status TraverseLinkStack(LinkStack*e, void(*f)(int q))
{
	//思路：遍历
	StackNode* temp = e->top;
	for (int i = 0; i < e->count; i++)
	{
		if (e->top == NULL)return ERROR;
		f(e->top->data);
		e->top = e->top->next;
	}
	//还要改回去。
	e->top = temp;
	return SUCCESS;
}

