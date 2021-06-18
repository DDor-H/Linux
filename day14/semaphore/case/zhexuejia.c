#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/sem.h>

int semid;
union semun { int val; };

void philosopher( int no) {
	printf("%d 号哲学家思考问题.\n", no);
	sleep(3);
	printf("%d 号哲学家准备吃饭.\n", no);
	
	struct sembuf sb[1];
	sb[0].sem_num = no;
	sb[0].sem_op  = -1;
	sb[0].sem_flg = 0;
	semop(semid, sb, 1);  // 拿左手筷子
	
	sb[0].sem_num = (no + 1) % 5;
	semop(semid, sb, 1);  // 拿右手筷子

	printf("%d 号开始进餐.\n", no);
	sleep(3);
	printf("%d 号用餐结束.\n", no);
	
	sb[0].sem_num = (no + 1) % 5;
	sb[0].sem_op  = 1;
	semop(semid, sb, 1);  // 放下右筷子
	
	sb[0].sem_num = no;
	semop(semid, sb, 1);  // 放下左筷子
}

int main( void ) {
	semid = semget(12345, 5, IPC_CREAT | 0644);  // 创建5个信号量
	
	int i;
	union semun su;
	su.val = 1;
	for ( i = 0; i < 5; ++i ) {
		semctl(semid, i, SETVAL, su);
	}

	int no = 0;
	// 五个人，一个父进程，四个子进程
	for ( i = 1; i < 5; ++i ) {
		pid_t pid = fork();
		if ( pid == 0 ) {
			no = i;
			break;
		}
	}
	philosopher( no );
	return 0;
} 






