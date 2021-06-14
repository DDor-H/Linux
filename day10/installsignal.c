#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

void handler(int s) {
	printf("你弄不死我...%d\n", s);
}

typedef void (*__handler_t)(int s);

int main() {
	// 这一句代表，当出现SIGINT这个信号，即ctrl c，
	// 不去执行缺省的处理函数，而执行自定义的handler函数
	//signal(SIGINT, handler);
	__handler_t old = NULL;

	if ( (old = signal(SIGINT, SIG_IGN)) == SIG_ERR ) {
		perror("signal"),exit(1);	
	}
	while ( 1 ) {
		printf(".");
		fflush(stdout);
		sleep(1);
	}
	return 0;
}
