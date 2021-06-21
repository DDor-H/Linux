#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

int main ( void ) {
	struct sigaction act;
	act.sa_handler = SIG_IGN;  // 显示忽略掉子进程返回的信息
	act.sa_flags = 0;
	sigemptyset(&act.sa_mask);
	sigaction(SIGCHLD, &act, NULL);

	pid_t pid = fork();
	if ( pid == 0 ) {
		exit(0);
	}

	for ( ; ; ) 
		pause();
	return 0;
}
