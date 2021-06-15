#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

void handler( int s ) {
	printf("recv %d\n", s);
}

int main( void ) {
	signal(SIGINT, handler);
	//屏蔽信号
	sigset_t set;
	sigemptyset(&set);  // 清空信号集
	sigaddset(&set, SIGINT);  // 将2号信号加入到信号集
	sigprocmask(SIG_BLOCK, &set, NULL);  // 通过这个函数，将内核的信号屏蔽集的2号信号屏蔽
	
	int i;	
	for ( i = 0; i < 5; ++i ) {
		printf("开始拷贝第%d集数据.\n", i);
		sleep(3);
		printf("第%d集数据拷贝完毕.\n", i);
	}
	
	//解除屏蔽
	sigprocmask(SIG_UNBLOCK, &set, NULL);
	
	for ( ; ; ) {
		printf(".");
		fflush(stdout);
		sleep(1);
	}
	return 0;
}
