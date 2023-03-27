#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include"function.h"
#include"stack.h"


Status TranslateToPostfix(char* s1,char *s2) {
	//心态大崩，九点写到快十二点，在比较符号优先级时把自己绕进去了。
	//教训：应该单独写一个函数，比较运算符优先级，运算符和括号分开讨论，不然乱了。


	//要用的变量
	LinkStack* stack = (LinkStack*)malloc(sizeof(LinkStack));
	initLStack(stack);//初始化一个栈，放运算符。
	char* temp1 = s1, * temp2 = s2;//存放s1和s2字符串原来的位置
	char temp3;//暂时存放栈顶元素
	//重新开始
	//遍历字符串
	while (*s1 != '\0') 
	{
		//是算子
		//多位数不搞了，下次先，这次只弄一位数的
		if (isNum(*s1)==SUCCESS)
		{
			//直接接着s2字符串
			*s2 = *s1;
			s2++;
		}
		//是运算符，
		else if (isOperator(*s1)==SUCCESS)
		{
			//同时满足三个条件：栈不空，栈顶不是左括号，栈顶运算符等级比*s1高，则弹出栈顶，加入s2串中。
			while (1)
			{
				if (isEmptyLStack(stack) != SUCCESS)
				{
					getTopLStack(stack, &temp3);
					if (temp3 != '(' && isLeftHigherLevel(temp3, *s1) == SUCCESS)
					{
						popLStack(stack, &temp3);
						*s2 = temp3;
						s2++;
					}
					else break;
				}
				else break;
			}
			//若满足上述其中一个条件的取反，运算符入栈。
			pushLStack(stack, *s1);
			
			//或者上述反过来也行
			//即满足其中一个条件：栈空，栈顶是左括号，栈顶运算符等级比*s1低，运算符入栈
			//否则，栈顶元素弹出，加入s2串中。
		}
		//是左括号
		else if (*s1=='(')
		{
			//直接入栈
			pushLStack(stack, *s1);
		}
		//是右括号
		else if(*s1==')')
		{
			//要找到匹配的左括号
			//遍历栈，直到栈空或找到左括号，将栈顶元素接到s2字符串上
			while (1)
			{
				if (isEmptyLStack(stack) != SUCCESS)
				{
					getTopLStack(stack, &temp3);
					if (temp3!='(')
					{
						popLStack(stack, &temp3);
						*s2 = temp3;
						s2++;
					}
					else break;
				}
				else break;
			}
			//将左括号出栈
			popLStack(stack, &temp3);
		}

			s1++;
	}
	//遍历完了，栈里有运算符就出栈,接到s2字符串上。
	while (isEmptyLStack(stack) != SUCCESS)
	{
		popLStack(stack, &temp3);
		*s2 = temp3;
		s2++;
	}
	//结束整个操作，s2给一个结束标志，s1，s2归位。
	*s2 = '\0';
	s1 = temp1;
	s2 = temp2;
	return SUCCESS;
}

Status PostfixCalulate(char* s, int* result)
{
	//需要用到的变量
	LinkStack1* stack1 = (LinkStack1*)malloc(sizeof(LinkStack1));
	initLStack1(stack1);//初始化一个栈，放数字。
	//要创建一个新类型，这时泛型的好处体现出来。现在先不改成泛型，创一个新类型。
	//算了，放字符吧，只有一位数。128位以内。
	//还是写一个新类型吧，如果写泛型，前面的没时间改了。

	//遍历字符串
	while (*s != '\0')
	{
		//是算子
		if (isNum(*s) == SUCCESS)
		{
			//进栈
			//注意：字符进栈要修改。
			int temp = *s - '0';
			pushLStack1(stack1, temp);
		}
		//是运算符
		else if (isOperator(*s)==SUCCESS)
		{
			//弹出两个数字，运算，将结果压回栈中。
			int temp1, temp2;
			int tempResult;
			popLStack1(stack1, &temp2);
			popLStack1(stack1, &temp1);
			calculate(temp1, temp2,*s, &tempResult);
			pushLStack1(stack1, tempResult);
		}
		s++;
	}
	//遍历完成，栈中只剩运算结果，提取出来
	popLStack1(stack1, result);
	return SUCCESS;
}
Status isNum(char c)
{
	if (c <= '9' && c >= '0')return SUCCESS;
	else return ERROR;
}
Status isOperator(char c)
{
	if (c == '+' || c == '-' || c == '*' || c == '/')
		return SUCCESS;
	else return ERROR;
}
Status isLeftHigherLevel(char c1, char c2)
{
	//在这里同级也算高等级，因为同级运算符从左到右运算
	switch (c1)
	{
	case('+'):
	case('-'):
		switch (c2)
		{
			case('+'):
			case('-'):
				return SUCCESS;
			case('*'):
			case('/'):
				return ERROR;
		}
	case('*'):
	case('/'):
		return SUCCESS;
	}
}

Status calculate(int num1, int num2,char c, int* Result)
{
	int tempResult;
	switch (c)
	{
	case('+'):
		tempResult = num1 + num2;
		break;
	case('-'):
		tempResult = num1 - num2;
		break;
	case('*'):
		tempResult = num1 * num2;
		break;
	case('/'):
		tempResult = num1 / num2;
		break;
	default:
		return ERROR;
		break;
	}
	*Result = tempResult;
	return SUCCESS;


}