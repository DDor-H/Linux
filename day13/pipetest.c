#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main( void ) {
	int pipefd[2];  //管道读写描述符
	
	pipe(pipefd);  // 不做错误处理了
	pid_t pid = fork();
	if ( pid == 0 ) {
		//子进程
		close(pipefd[0]);  // 关闭管道读
		sleep(2);
		write(pipefd[1], "abc", 3);
		close(pipefd[1]);
	} else {
		//父进程
		close(pipefd[1]);  // 关闭管道写
		char buf[12];
		read(pipefd[0], buf, 12);
		close(pipefd[0]);
		printf("%s\n", buf);
	}
	return 0;
}
