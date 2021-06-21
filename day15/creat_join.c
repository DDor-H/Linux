#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

void* r1( void* argv ) {
	const char* str = (const char*)argv;
	
	printf("I'm %s\n", str);
	return NULL;
}

int main( void ) {
	pthread_t tid;
	
	pthread_create(&tid, NULL, r1, "thread 1");
	pthread_join(tid, NULL); // 阻塞，等待tid线程结束，回收僵尸线程，main线程在结束，防止
							//其他线程还没结束，main线程已经结束的情况
	return 1;
}
