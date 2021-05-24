#include "parse.h"
#include <stdio.h>
#define IN 1
#define OUT 0
#include "add.h"
#include "sub.h"
#include "mul.h"

typedef int FUNC(int, int);
FUNC* p_fun = NULL;
char op;

typedef struct stuct_t
{
	FUNC* pFun; //add(int,int)
	char* name; //add sub
	char op;    // + -
}struct_s;
struct_s expr[]={
	{add, "add", '+'},
	{sub, "sub", '-'},
	{mul, "mul", '*'},
	{NULL, NULL, 0}
};



void do_action(int argc, char* argv[])
{
	int left = atoi(argv[1]);
	int right = atoi(argv[2]);
	
	int ret = p_fun(left, right);
	printf("%s%c%s = %d\n", argv[1], op, argv[2], ret);	
}


void main_math(int argc, char* argv[])
{
	int i;
	p_fun = NULL;
	for (i = 0; ; ++i)
	{
		if(expr[i].name == NULL) 
		{
			printf("%s 命令不存在\n", argv[0]);
			return;
		}
		
		if (strcmp(expr[i].name, argv[0]) == 0) 
		{
			p_fun = expr[i].pFun;
			op = expr[i].op;
			break;
		}
	}
	do_action(argc, argv);
}




void parse(char* buf)
{
	int argc = 0;
	char* argv[8] = {};
	
	int flag = OUT;
	int i;
	for (i = 0; buf[i] != '\0'; ++i)
	{
		//还在单词外面，并且当前位置不是空白符
		if (flag == OUT && !isspace(buf[i]))
		{
			argv[argc++] = buf + i;
			flag = IN;
		}
		if (flag == IN && isspace(buf[i]))
		{
			buf[i] = '\0';
			flag = OUT;
		}
	}
	
	//for (i = 0; i < argc; ++i)
	//{
	//	printf("argv[%d] = [%s]\n", i, argv[i]);
	//}
	main_math(argc, argv);
}
