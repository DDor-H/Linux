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

int main( void ) {
	// 打开共享内存
	int shmid = shmget(1234, 0, 0); // 创建共享内存
	int* p = (int*)shmat(shmid, NULL, 0);  // 挂载共享内存
	
	// 信号量
	int semida = semget(1234, 0, 0); // 获取信号量
	int semidb = semget(1235, 0, 0);
	while ( 1 ) {
		P(semidb);
		sleep(1);
		printf("取出数据%d完成\n", *p);
		V(semida);
	}
	return 0;
}







