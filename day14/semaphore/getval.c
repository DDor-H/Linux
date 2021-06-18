#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/sem.h>

int main ( void ) {
	// 类似于共享内存，只要是打开，数量就可以写 0 
	int sem_id = semget(1234, 0, 0);
	
	int val = semctl(sem_id, 0, GETVAL, 0); // 获取信号量的值，所以第四个参数填0	
	printf("val = %d\n", val);
	return 0;
}
