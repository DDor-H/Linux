#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/time.h>
#include <string.h>

void handler( int s ) {
	//printf("recv %d\n", s);	
	printf("recv %d) %s\n", s, strsignal(s));  // 打印出信号值对应的信号名
}

int main ( void ) {
	signal(SIGALRM, handler);
	
	struct itimerval it;
	//基于桌面时间，启动后5秒开始第一次alarm
	it.it_value.tv_sec   = 5;
	it.it_value.tv_usec  = 0;

	//之后每隔1秒alarm一次
	it.it_interval.tv_sec = 1;
	it.it_interval.tv_usec = 0;
	
	setitimer(ITIMER_REAL, &it, NULL);
	while ( 1 ) {
		printf(".");
		fflush(stdout);
		sleep(1);
	}
	return 0;
}
