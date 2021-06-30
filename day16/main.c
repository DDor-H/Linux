#include <stdio.h>
#include <stdlib.h>
#include "threadpool.h"

void* myfun(void* args) {
	int num = *(int*)args;
	free(args);
	printf("%d 任务运行在 %p 线程上\n", num, pthread_self());
	sleep(1);
	return NULL;
}

int main( void ) {
	threadpool_t pool;  //创建线程池
	threadpool_init(&pool, 3);  //初始化线程池
	
	// 往线程池中添加任务
	int i;
	for ( i = 0; i < 5; ++i ) {
		int* p = (int*)malloc(sizeof(int));
		*p = i;
		threadpool_add_task(&pool, myfun, (void*)p);
	}
	sleep(10);
	threadpool_destroy(&pool);  // 销毁线程池
	return 0;
}
