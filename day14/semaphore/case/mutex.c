#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/sem.h>

int sem_id;

union semun { int val; };

void print_char( char c ) {
	int i;
	for ( i = 0; i < 10; ++i ) {
		struct sembuf sb[1];
		sb[0].sem_num = 0;
		sb[0].sem_op = -1;
		sb[0].sem_flg = 0;
		semop(sem_id, sb, 1); // P操作
		
		printf("%c", c);
		fflush(stdout);
		
		sleep(rand() % 3);
		
		printf("%c", c);
		fflush(stdout);
		
		sb[0].sem_op = 1;
		semop(sem_id, sb, 1); // V操作
	}
	printf("\n");
}
int main( void ) { 
	srand((unsigned)getpid());
	
	sem_id = semget(12345, 1, IPC_CREAT | 0644); // 创建信号量集
	union semun su;
	su.val = 1;
	semctl(sem_id, 0, SETVAL, su);  // 设置信号量初值为1
	
	pid_t pid = fork();
	if ( pid == 0 ) {
		//子进程
		print_char('1');
	} else {
		//父进程
		print_char('0');
	}
	return 0;
}
