#pragma once
#ifndef __FUNCTION_H__
#define __FUNCTION_H__

extern enum Status;

Status TranslateToPostfix(char* s1, char* s2);//status在stack.h中，把头文件包进来或在这定义status。extern
Status isNum(char c);
Status isOperator(char c);
Status isLeftHigherLevel(char c1, char c2);
Status PostfixCalulate(char* s, int* result);
Status calculate(int num1, int num2, char c, int* Result);

#endif // !__FUNCTION_H__
