#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/wait.h>

int mysystem( const char* cmd ) {
	pid_t pid;
	if ( (pid=fork()) == -1 )
		exit(127);
	if ( pid == 0 ) {
		if ( execlp("/bin/sh", "/bin/sh", "-c", cmd, NULL) == -1 )
			exit(1);
	}

	//子进程一定走不到这里
	int status;
	while ( waitpid(pid, &status, WNOHANG) != pid )
		;
	if ( WIFEXITED(status) ) {  //子进程正常退出返回真
		return WEXITSTATUS(status);   //获取子进程的退出码
	}
	
	return -1;  //子进程不是正常退出返回-1

}

int main( void ) {
	printf("before system...\n");
	//system("ls -l");	
	mysystem("ls -l");
	printf("after system...\n");
	return 0;
}
