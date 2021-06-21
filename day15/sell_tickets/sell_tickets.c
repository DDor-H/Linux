#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

int tickets = 100;

pthread_mutex_t mutex;  // 定义线程信号量

void* r1( void* argv ) {
	const char* name = (const char*)argv;
	while(1) {
		pthread_mutex_lock(&mutex); // P操作
		if ( tickets > 0 ) {
			printf("%s 卖 %d\n", name, tickets);
			tickets--;
		} else { 
			pthread_mutex_unlock(&mutex); //有一个线程从这里结束，其他的都会阻塞在上面的P操作
			break;
		}
		pthread_mutex_unlock(&mutex); //V操作
		usleep(100000);
	}
	return NULL;
}

int main( void ) {
	pthread_t t1, t2, t3, t4;

	pthread_mutex_init(&mutex, NULL);  // 初始化信号量，属性为空，有OS决定

	pthread_create(&t1, NULL, r1, "thread 1");
	pthread_create(&t2, NULL, r1, "thread 2");
	pthread_create(&t3, NULL, r1, "thread 3");
	pthread_create(&t4, NULL, r1, "thread 4");

	pthread_join(t1, NULL);
	pthread_join(t2, NULL);
	pthread_join(t3, NULL);
	pthread_join(t4, NULL);
	
	pthread_mutex_destroy(&mutex); // 释放信号量
	return 0;
}
