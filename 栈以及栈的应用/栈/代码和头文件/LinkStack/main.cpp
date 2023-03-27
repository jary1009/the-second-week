#define _CRT_SECURE_NO_WARNINGS
#include"LinkStack.h"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
int main()
{
	void show();
	show();
	return 0;
}
void show()
{
	void get_int(int* data);
	LinkStack* S=(LinkStack*)malloc(sizeof(LinkStack));
	initLStack(S);
	int flag;
	int e;
	int length;
	while (1)
	{
		while (1)
		{
			flag = 0;
			//修改：加两条线吧
			printf("______________________________________________________\n");
			printf("You can do these function:\n");
			printf("1.Check whether the stack is empty or not;\n");
			printf("2.Get the number of the stack head;\n");
			printf("3.Add a number into the stack;\n");
			printf("4.Get a number out of the stack;\n");
			printf("5.Read all the node of the queue;\n");
			printf("6.Get the length of the queue;\n");
			printf("7.Clear the queue;\n");
			printf("8.Delete the queue and quit;\n");
			printf("Now please give me the number to finish the function:\n");
			printf("______________________________________________________\n");
			scanf("%d", &flag);
			while (getchar() != '\n');
			if (flag < 1 || flag>8)
			{
				system("cls");
				printf("Please give me the right number!\n");
			}
			else
				break;
		}
		switch (flag)
		{
		case(1):
			if (isEmptyLStack(S) == SUCCESS)
				printf("The stack is empty now!You should add something!\n");
			else
				printf("The stack is not empty now.\n");
			break;
		case(2):
			if (getTopLStack(S, &e) == SUCCESS)
				printf("%d\n", e);
			else
				printf("The queue is empty now!You should add something!\n");
			break;
		case(3):
			get_int(&e);
			if (pushLStack(S,e)==SUCCESS)
				printf("Printf we have add it into the queue!\n");
			else
			{
				printf("There is something wrong.Maybe the RAM is full\n");
				exit(-1);
			}
			break;
		case(4):
			if (popLStack(S, &e) == SUCCESS)
			{
				printf("We have get the node out of the queue.\n");
				printf("the data is %d\n", e);
			}
			else
				printf("The queue is empty now!\n");
			break;//漏了break；测试中发现了
		case(5):
			if (TraverseLinkStack(S, LStackPrint) == SUCCESS)
			{
				printf("the stack is successfully traversed\n");
				printf("Notice:if the stack is empty.It can also traverse\n");
			}
			else 
			{
				printf("There is some wrong in the stack!!!\n");
				exit(-1);
			}
			break;
		case(6):
			if (LStackLength(S, &length) == SUCCESS)
				printf("The length of the stack is %d.\n", length);
			else
			{
				printf("There is some wrong in the stack!!!\n");
				exit(-1);
			}
			break;
		case(7):
			if (clearLStack(S) == SUCCESS)
			{
				printf("Notice:if the stack is empty,It can also be cleaned. \n");
				printf("now the all data in stack is \n");
					if (TraverseLinkStack(S, LStackPrint) == SUCCESS)
					{
						printf("the stack is successfully traversed\n");
						printf("NOtice:if the stack is empty.It can also traverse\n");
					}
					else
					{
						printf("There is some wrong in the stack!!!\n");
						exit(-1);
					}
			}
			else
			{
				printf("There is some wrong in the stack!!!\n");
				exit(-1);
			}
			break;
		case(8):
			if (destroyLStack(S) == SUCCESS)
			{
				//free(S);//修改：将它挪到函数中。
				printf("the stack is successfully destoryed\n");
				exit(0);
			}
			else
			{ 
				printf("There is some wrong in the stack!!!\n");
				exit(-1);
			}
			break;
		}
	}

}


void get_int(int* data)//这个好用，直接小改一下
{
	printf("Please give me a int number:\n");
	char s[50];
	int flag = 1;//错误的，错误原因：没有重新赋flag为1
	while (1)
	{
		flag = 1;
		gets_s(s);
		if (*s == '-')
		{
			if (strlen(s) < 6)
			{
				int i;
				for (i = 1; i < 6 && s[i] != '\0'; i++)
					if (s[i] < '0' || s[i]>'9');
				{
					flag = 0;
					break;
				}
				if (flag == 1)
				{
					*data = 0;
					for (i = 1; i < 6 && s[i] != '\0'; i++)
						*data = (*data) * 10 + s[i] - '0';
					(*data) *= -1;
					return;
				}
			}
		}
		else if (strlen(s) < 5)
		{
			int i;
			for (i = 0; i < 5 && s[i] != '\0'; i++)
				if (s[i] < '0' || s[i]>'9')
				{
					flag = 0;
					break;
				}
			if (flag == 1)
			{
				*data = 0;
				for (i = 0; i < 5 && s[i] != '\0'; i++)
					*data = (*data) * 10 + s[i] - '0';
				return;
			}
		}
		printf("Please give me a right int number which is bigger than -10000 and smaller than 10000;\n");
	}
}