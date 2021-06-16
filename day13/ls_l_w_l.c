#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main( void ) {
	int fds[2];
	pipe(fds);
	
	pid_t pid = fork();
	if ( pid == 0 ) {
		// 写管道
		close(1);  // 关闭标准输出文件描述符 1
		dup(fds[1]);  // 复制一份管道写文件描述符，因为1位置空了
					  // 所以复制的那份管道写文件描述符，即为1；
					  // 标准输出和管道写段绑定在一起；
		close(fds[0]);
		close(fds[1]);
		execlp("ls", "ls", "-l", NULL);
	} else {
		// 读管道
		close(0);
		dup(fds[0]);
		close(fds[0]);
		close(fds[1]);
		execlp("wc", "wc", "-l", NULL);
	}
	return 0;
}
