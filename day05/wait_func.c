#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>

/*
 * 功能：回收僵尸子进程
 * pid_t wait(int* status);
 * 返回值：被回收的子进程的进程pid，若返回 -1 表示出错（没有僵尸进程但去回收的情况）
 * status：获得子进程的死亡信息
 */

#define ERR_EXIT(msg) \
	do {  \
		printf("[%s'[%d] %s: %s\n", __FILE__, __LINE__, msg, strerror(errno));  \
		exit(EXIT_FAILURE);  \
	} while ( 0 )

int main ( void ) {
	pid_t pid;
	
	if ( (pid=fork()) == -1 ) ERR_EXIT("fork");

	if ( pid == 0 ) {
		//子进程
		printf("child pid = %d\n", getpid()); // getpid() 获取自己的pid
		getchar();
		exit(1);
	} else {
		pid_t ret;
		int status;
		// wait函数如果出错，返回-1 ，在函数内部，会将子进程的死亡信息交给status（取地址）
		if ( (ret=wait(&status)) == -1) ERR_EXIT("wait");

		if ( WIFEXITED(status) ) { //子进程正常退出，WIFEXITED返回真
			printf("normal exit: %d\n", WEXITSTATUS(status));  //WEXITSTATUS函数获取子进程结束时的返回信息，也就是上面exit(1)中的 1
		} else if ( WIFSIGNALED(status) ) { //子进程异常退出返回true
			printf("killed by kill cmd\n");
		}

		printf("ret=%d\n", ret);
		while ( 1 ) {
			printf(".");
			fflush(stdout);
			sleep( 1 );
		}
	}
	return 0;
}
