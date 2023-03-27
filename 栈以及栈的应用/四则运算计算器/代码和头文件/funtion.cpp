#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include"function.h"
#include"stack.h"


Status TranslateToPostfix(char* s1,char *s2) {
	//��̬������ŵ�д����ʮ���㣬�ڱȽϷ������ȼ�ʱ���Լ��ƽ�ȥ�ˡ�
	//��ѵ��Ӧ�õ���дһ���������Ƚ���������ȼ�������������ŷֿ����ۣ���Ȼ���ˡ�


	//Ҫ�õı���
	LinkStack* stack = (LinkStack*)malloc(sizeof(LinkStack));
	initLStack(stack);//��ʼ��һ��ջ�����������
	char* temp1 = s1, * temp2 = s2;//���s1��s2�ַ���ԭ����λ��
	char temp3;//��ʱ���ջ��Ԫ��
	//���¿�ʼ
	//�����ַ���
	while (*s1 != '\0') 
	{
		//������
		//��λ�������ˣ��´��ȣ����ֻŪһλ����
		if (isNum(*s1)==SUCCESS)
		{
			//ֱ�ӽ���s2�ַ���
			*s2 = *s1;
			s2++;
		}
		//���������
		else if (isOperator(*s1)==SUCCESS)
		{
			//ͬʱ��������������ջ���գ�ջ�����������ţ�ջ��������ȼ���*s1�ߣ��򵯳�ջ��������s2���С�
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
			//��������������һ��������ȡ�����������ջ��
			pushLStack(stack, *s1);
			
			//��������������Ҳ��
			//����������һ��������ջ�գ�ջ���������ţ�ջ��������ȼ���*s1�ͣ��������ջ
			//����ջ��Ԫ�ص���������s2���С�
		}
		//��������
		else if (*s1=='(')
		{
			//ֱ����ջ
			pushLStack(stack, *s1);
		}
		//��������
		else if(*s1==')')
		{
			//Ҫ�ҵ�ƥ���������
			//����ջ��ֱ��ջ�ջ��ҵ������ţ���ջ��Ԫ�ؽӵ�s2�ַ�����
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
			//�������ų�ջ
			popLStack(stack, &temp3);
		}

			s1++;
	}
	//�������ˣ�ջ����������ͳ�ջ,�ӵ�s2�ַ����ϡ�
	while (isEmptyLStack(stack) != SUCCESS)
	{
		popLStack(stack, &temp3);
		*s2 = temp3;
		s2++;
	}
	//��������������s2��һ��������־��s1��s2��λ��
	*s2 = '\0';
	s1 = temp1;
	s2 = temp2;
	return SUCCESS;
}

Status PostfixCalulate(char* s, int* result)
{
	//��Ҫ�õ��ı���
	LinkStack1* stack1 = (LinkStack1*)malloc(sizeof(LinkStack1));
	initLStack1(stack1);//��ʼ��һ��ջ�������֡�
	//Ҫ����һ�������ͣ���ʱ���͵ĺô����ֳ����������Ȳ��ĳɷ��ͣ���һ�������͡�
	//���ˣ����ַ��ɣ�ֻ��һλ����128λ���ڡ�
	//����дһ�������Ͱɣ����д���ͣ�ǰ���ûʱ����ˡ�

	//�����ַ���
	while (*s != '\0')
	{
		//������
		if (isNum(*s) == SUCCESS)
		{
			//��ջ
			//ע�⣺�ַ���ջҪ�޸ġ�
			int temp = *s - '0';
			pushLStack1(stack1, temp);
		}
		//�������
		else if (isOperator(*s)==SUCCESS)
		{
			//�����������֣����㣬�����ѹ��ջ�С�
			int temp1, temp2;
			int tempResult;
			popLStack1(stack1, &temp2);
			popLStack1(stack1, &temp1);
			calculate(temp1, temp2,*s, &tempResult);
			pushLStack1(stack1, tempResult);
		}
		s++;
	}
	//������ɣ�ջ��ֻʣ����������ȡ����
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
	//������ͬ��Ҳ��ߵȼ�����Ϊͬ�����������������
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