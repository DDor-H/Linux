#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/sem.h>

int main ( void ) {
	int sem_id = semget(1234, 0, 0);
	
	// 只有一个信号量，所以结构体数组大小为1	
	struct sembuf sb[1];
	sb[0].sem_num = 0;  // 所操作的信号量下标是 0
	sb[0].sem_op = 1;  // v操作，信号量 1
	sb[0].sem_flg = 0;  // 标志位为0
	
	semop(sem_id, sb, 1); // 信号量的个数为1
	return 0;
}
