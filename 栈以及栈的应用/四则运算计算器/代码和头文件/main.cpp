#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include"function.h"
#include"stack.h"

int main()
{
	while (1)
	{
		system("cls");
		//提示语

		printf("请输入算式\n");
		printf("注意事项1：括号是英文状态的小括号\n");
		printf("注意事项2：算子不能有负数出现，即数字和括号内的表达结果都不能有负数，该版本无此功能\n");
		printf("注意事项3：请输入正确表达式，该版本没有检错功能\n");
		printf("注意事项4：该版本算子支持一位数\n");



		char s2[1000] = "0";
		//检查输入的表达式是否正确（选做）
		//转化为后缀表达式
		char s1[1000] = "0";
		gets_s(s1);
		TranslateToPostfix(s1, s2);
		printf("后缀表达式为%s\n", s2);
		//后缀表达式计算
		int result;
		PostfixCalulate(s2, &result);
		printf("运算结果为%d\n", result);

		printf("输入？退出程序\n");
		printf("输入其他符号继续运算\n");
		char temp = getchar();
		while (getchar() != '\n');
		if (temp == '?')break;
		else continue;
	}

}