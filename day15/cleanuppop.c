#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

pthread_mutex_t mutex;

void call_back( void ) {
	printf("call_back().\n");
	usleep(500000);
	// 调用回调函数时，解锁
	pthread_mutex_unlock(&mutex);
}

void* odd(void* arg) {
	int i;
	for(i = 1; ; i+=2) {
		pthread_mutex_lock(&mutex);
		printf("odd() %d\n", i);
		pthread_mutex_unlock(&mutex);
	}
	return NULL;
}

void* even(void* arg) {
	int i;
	for(i = 0; ; i+=2) {
		pthread_cleanup_push(call_back, NULL); // 有可能调用回调函数，参数为空
		pthread_mutex_lock(&mutex);
		printf("even() %d\n", i);
		usleep(10000);
		pthread_mutex_unlock(&mutex);
		pthread_cleanup_pop(0);  // 参数为0表示，执行这条语句不会触发回调函数
								 // 若非0，则每次打印都会触发一次；
	}
	return NULL;
}

int main( void ) {
	pthread_t t1, t2;
	pthread_mutex_init(&mutex, NULL);
	pthread_create(&t1, NULL, odd, NULL);
	pthread_create(&t2, NULL, even, NULL);

	sleep(2);
	pthread_cancel(t2);

	pthread_join(t1, NULL);
	pthread_join(t2, NULL);
	pthread_mutex_destroy(&mutex);
	return 0;
}
