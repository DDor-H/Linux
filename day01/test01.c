#include <stdio.h>
#include <stdlib.h>

void fun1(void)
{
	printf("func1(void)\n");
}

 void fun2(void)
{
        printf("func2(void)\n");
}

void fun3(void)
{
	printf("func3(void)\n");
}

int main(int argc, char* argv[])
{
	typedef void FUN(void);
	
	printf("in main");
	FUN* arr[3] = {fun1, fun2, fun3};

	int i;
	
	for (i = 0; i < 100; ++i)
	{
		arr[i%3]();
		sleep(1);
	}
	for (i = 0; i < argc; ++i)
	{
		printf("argv[%d] = %s\n", i, argv[i]);
	}
	printf("exiting\n");
	return 0;
}
