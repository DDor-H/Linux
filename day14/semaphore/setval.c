#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/sem.h>

union semun {
	int val;
};

int main ( void ) {
	// 类似于共享内存，只要是打开，数量就可以写 0 
	int sem_id = semget(1234, 0, 0);
	union semun su;
	su.val = 5;  // 信号量值为5
	semctl(sem_id, 0, SETVAL, su); // 信号量数量已经确定，所以这里填0	
	return 0;
}
