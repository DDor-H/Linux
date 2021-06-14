#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

void handler( int s ) {
	while ( waitpid(-1, NULL, WNOHANG) != -1 )
		;
}

int main( void ) {
	signal(SIGCHLD, handler);
	pid_t pid = getpid();

	int i = 0;
	for ( i = 0; i < 5; ++i ) {	
		pid_t pid = fork();
		if ( pid == 0 ) {
			//子进程
			break; //子进程创建好之后直接结束，
					//营造出一种多信号到达父进程的情况
		}
	}
	if ( pid == getpid() ) {
		//父进程
		while (1) {
			printf("￥");
			sleep(1);
			fflush(stdout);
		}
	}
	sleep(1);  // 5个子进程同时退出
}
