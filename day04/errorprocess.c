#include <stdio.h>
#include <stdlib.h>
#include <setjmp.h>

jmp_buf buf;

void fun( int n )
{
	printf("in fun\n");
	if ( n == 1 ) {
		longjmp(buf, 1);
	}
	if ( n == 2 ) {
		longjmp(buf, 2);
	}
	
	printf("ok\n");
}

int main()
{
	int r;
	if ( (r = setjmp(buf)) == 0) { // 第一次调用setjmp时，返回值一定为0
		fun(1);
		printf("normal\n");
	} else if ( r == 1 ) {
		printf("catch 1 error\n");
	} else if ( r == 2 ) {
		printf("catch 2 error\n");
	}

	printf("exit\n");
	return 0;
}
