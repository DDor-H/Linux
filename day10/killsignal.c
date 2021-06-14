#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

void handler( int s ) {
	printf("recv %d\n", s);
	exit(0);
}

int main( void ) {
	signal(SIGUSR1, handler);
	
	pid_t pid = fork();
	if ( pid == 0 ) {
		//子进程
		sleep(5); //子进程睡三秒再给父进程发信号
		kill(getppid(), SIGUSR1);
	} else {
		//父进程
		while (1) {
			printf(".");
			sleep(1);
			fflush(stdout);
		}
	}
}
