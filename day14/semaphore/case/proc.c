#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/shm.h>

void P( int id ) {  // P操作
	struct sembuf sb[1];
	sb[0].sem_num = 0;
	sb[0].sem_op = -1;
	sb[0].sem_flg = 0;
	semop(id, sb, 1);
}

void V( int id ) {  // V操作
	struct sembuf sb[1];
	sb[0].sem_num = 0;
	sb[0].sem_op = 1;
	sb[0].sem_flg = 0;
	semop(id, sb, 1);
}

union semun { int val; };

void setval( int id, int val ) {
	union semun su;
	su.val = val;
	semctl(id, 0, SETVAL, su);
}

int main( void ) {
	// 共享内存
	int shmid = shmget(1234, sizeof(int), IPC_CREAT | 0644); // 创建共享内存
	int* p = (int*)shmat(shmid, NULL, 0);  // 挂载共享内存
	
	// 信号量
	int semida = semget(1234, 1, IPC_CREAT | 0644); // 创建信号量
	int semidb = semget(1235, 1, IPC_CREAT | 0644);
	setval(semida, 1); // 初始化信号量
	setval(semidb, 0);
	
	int num = 0;
	while ( 1 ) {
		P(semida);
		printf("开始装入数据，编号为 %d\n", num);
		*p = num++;
		sleep(1);
		printf("装入数据%d完成\n", num - 1);
		V(semidb);
	}
	return 0;
}







