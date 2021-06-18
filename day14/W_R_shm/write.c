#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/shm.h>
#include <sys/ipc.h>
#include <string.h>


int main( void ) {
	// 第二个参数，要是打开已有的共享内存，可以不指定size，直接写0
	// 要是创建共享内存，就得指定大小；
	int id = shmget(1234, 0, 0);
	if ( id == -1 ) perror("shmget"), exit(1);
	// 第二个参数，如果第一次挂载的时候，填NULL操作系统会自动安排挂载到哪块虚拟内存
	// 后面再挂载，填NULL，操作系统就会找到上次挂载的地址并返回，两次的意义不一样；
	int* p = (int*)shmat(id, NULL, 0);
	printf("input num:>");
	scanf("%d", p);
	
	getchar();
	getchar();
	return 0;
}
