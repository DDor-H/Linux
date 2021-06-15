#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

void handler( int s ) {
	printf("recv %d\n", s);
}

int main( void ) {
	struct sigaction act;
	act.sa_handler = handler;
	sigemptyset(&act.sa_mask);
	act.sa_flags = 0;
	//注册信号
	sigaction(SIGINT, &act, NULL);

	for ( ; ; ) {
		printf(".");
		fflush(stdout);
		sleep(1);
	}

	return 0;
}
