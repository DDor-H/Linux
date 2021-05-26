#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[], char* envp[])
{	
	int i = 0;
	for (i = 0; i < argc; ++i)
	{
		printf("%s\n", argv[i]);
	}
	for (i = 0; envp[i] != NULL; ++i)
	{
		printf("envp[%d] = %s\n", i, envp[i]);
	}
	char* bash = getenv("SHELL");  //获取环境变量
	printf("%s\n", bash == NULL ? "NULL" : bash);
	
	if (putenv("AAA=abc") == 0)  //设置环境变量
		printf("putenv() ok\n");
	else
		printf("putenv() error\n");
	
	bash = getenv("AAA");
	printf("%s\n", bash == NULL ? "NULL" : bash);
	sleep(50000);
	return 0;
}
