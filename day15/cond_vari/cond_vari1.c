#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

pthread_cond_t cond;
pthread_mutex_t mutex;

void* r1(void* arg) {
	while( 1 ) {
		pthread_cond_wait(&cond, &mutex); // 这个线程信号量暂时没用
		printf("活了！\n");
	}
}

void* r2(void* arg) {
	while( 1 ) {
		pthread_cond_signal(&cond);
		sleep(1);	
	}
}

int main( void ) {
	pthread_t t1, t2;
	pthread_cond_init(&cond, NULL);
	pthread_mutex_init(&mutex, NULL);

	pthread_create(&t1, NULL, r1, NULL);
	pthread_create(&t2, NULL, r2, NULL);

	pthread_join(t1, NULL);
	pthread_join(t2, NULL);

	pthread_cond_destroy(&cond);
	pthread_mutex_destroy(&mutex);
	return 0;
}
