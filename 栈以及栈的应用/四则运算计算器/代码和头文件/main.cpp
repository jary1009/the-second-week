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
		//��ʾ��

		printf("��������ʽ\n");
		printf("ע������1��������Ӣ��״̬��С����\n");
		printf("ע������2�����Ӳ����и������֣������ֺ������ڵı�����������и������ð汾�޴˹���\n");
		printf("ע������3����������ȷ���ʽ���ð汾û�м����\n");
		printf("ע������4���ð汾����֧��һλ��\n");



		char s2[1000] = "0";
		//�������ı��ʽ�Ƿ���ȷ��ѡ����
		//ת��Ϊ��׺���ʽ
		char s1[1000] = "0";
		gets_s(s1);
		TranslateToPostfix(s1, s2);
		printf("��׺���ʽΪ%s\n", s2);
		//��׺���ʽ����
		int result;
		PostfixCalulate(s2, &result);
		printf("������Ϊ%d\n", result);

		printf("���룿�˳�����\n");
		printf("�����������ż�������\n");
		char temp = getchar();
		while (getchar() != '\n');
		if (temp == '?')break;
		else continue;
	}

}