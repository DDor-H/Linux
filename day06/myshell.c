#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>
#include <errno.h>

#define ERR_EXIT(msg) \
	do {   \
		printf("[%s][%d] %s: %s\n", __FILE__, __LINE__, msg, strerror(errno));  \
		exit(EXIT_FAILURE); \
	} while ( 0 )



int get_input(char* buf) {
	memset(buf, 0x00, sizeof(buf));
	if ( scanf("%[^\n]%*c", buf) != 1 ) {  //如果不是一个字符串，或者只有一个换行符，都读取不了，都得清空缓冲区
		int c;
		do { c=getchar(); } while (c != '\n');
	}
	return strlen(buf);
}

void do_action(int argc, char* argv[]) {
	pid_t pid;
	switch ( (pid=fork()) ) {
	case -1:
		ERR_EXIT("fork");
		return;
	case 0: {
			pid_t ret = execvp(argv[0], argv);	
			printf("[%s] : command not found\n", argv[0]);
			exit(1);
		}
		break;
	default: {
			int status;
			waitpid(pid, &status, 0);  //填0为默认值，阻塞在此等待
		}
		break;
	}
}

void do_parse(char* buf) {
	char *argv[10] = { 0 };
	int argc = 0;
	#define IN 1
	#define OUT 0
	int i = 0;
	int status = OUT;
	while ( buf[i] != '\0' ) {
		if ( status == OUT && !isspace( buf[i]) ) {
			argv[argc++] = buf + i;
			status = IN;
		}
		if ( status == IN && isspace(buf[i]) ) {
			buf[i] = '\0';
			status = OUT;
		}
		++i;
	}
	argv[argc] = NULL;
	/*int j = 0;
	while ( argv[j] != NULL )
		printf("%s\n", argv[j++]);*/
	do_action(argc, argv);  //创建子进程并执行命令
}

int main( void ) {
	char buf[512];
	while ( 1 ) {
		printf("[my shell]# ");
		fflush(stdout);
		if ( get_input(buf) == 0 )  // 读取一行数据
			continue;
		do_parse(buf);  // 解析数据
	}
	return 0;
}      
