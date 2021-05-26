#include <stdio.h>
#include <stdlib.h>

int main()
{
	int i;
	int num;
	
	printf("你想创建几个子进程？：");
	scanf("%d%*c", &num);
	
	for (i = 0; i < num; ++i)
	{
		if (fork() == 0)
			break;
	}	
	printf("hehe\n");
	getchar();	
	return 0;
}
