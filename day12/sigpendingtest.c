#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

void handler( int s ) {
	printf("recv %d\n", s);
}
// 解除信号屏蔽
void handler_quit( int s ) {
	sigset_t set;
	sigemptyset(&set);
	sigaddset(&set, SIGINT);
	sigprocmask(SIG_UNBLOCK, &set, NULL);
}

int main( void ) {
	signal(SIGINT, handler);
	signal(SIGQUIT, handler_quit);

	//屏蔽信号
	sigset_t set;
	sigemptyset(&set);  // 清空信号集
	sigaddset(&set, SIGINT);  // 将2号信号加入到信号集
	sigprocmask(SIG_BLOCK, &set, NULL);  // 通过这个函数，将内核的信号屏蔽集的2号信号屏蔽
	
	for ( ; ; ) {
		sigset_t pset;
		sigemptyset(&pset);
		sigpending(&pset);
		int j;
		for ( j = 1; j < 65; ++j ) {
			if ( sigismember(&pset, j) ) {
				printf("1");
			} else {
				printf("0");
			}
		}
		//fflush(stdout);
		printf("\n");
		sleep(1);
	}
	return 0;
}
