#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

void handler( int s ) {
	printf("timeout\n");
	exit(0);
}

int main ( void ) {
	signal(SIGALRM, handler);
	
	alarm(3);
	char buf[1024] = {};
	read(0, buf, 1024);  //从键盘读入数据，如果三秒内没读到，就timeout
	alarm(0);           //如果三秒内读到了，就用参数 0 取消之前的alarm设定；
	while ( 1 ) {
		printf(".");
		sleep(1);
		fflush(stdout);
	}
	return 0;
}
