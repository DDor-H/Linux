#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <string.h>
#include <semaphore.h>

#define BUFSIZE 5
#define P 3
#define C 2

pthread_mutex_t mutex;
sem_t full, empty;
pthread_t tid[P + C];
int buf[BUFSIZE];
int in = 0;
int out = 0;

void* pro(void* arg) {
	int id = *(int*)arg;
	free(arg);
	id = 1;
	while ( 1 ) {
		sem_wait(&empty); // 要先获取信号，才能上锁，否则会死锁
		pthread_mutex_lock(&mutex);

		buf[in] = id++;
		in = (in + 1) % BUFSIZE;
		sleep(1);

		pthread_mutex_unlock(&mutex);
		sem_post(&full);
	}
}

void* coss(void* arg) {
	int id = *(int*)arg;
	free(arg);
	id = 1;
	while ( 1 ) {
		sem_wait(&full);
		pthread_mutex_lock(&mutex);

		printf("%d\n", buf[out]);
		out = (out + 1) % BUFSIZE;

		pthread_mutex_unlock(&mutex);
		sem_post(&full);
	}
}

int main ( void ) {
	pthread_mutex_init(&mutex, NULL);
	sem_init(&full, 0, 0);
	sem_init(&empty, 0, BUFSIZE);
	int i;
	
	for ( i = 0; i < P; ++i ) {
		int* p = (int*)malloc(sizeof(int));
		*p = i;
		pthread_create(&tid[i], NULL, pro, (void*)p);
	}
	
	for ( i = 0; i < C; ++i ) {
		int* p = (int*)malloc(sizeof(int));
		*p = i;
		pthread_create(&tid[i + P], NULL, coss, (void*)p);
	}
	for ( i = 0; i < P + C; ++i ) {
		pthread_join(tid[i], NULL);
	}

	sem_destroy(&full);
	sem_destroy(&empty);
	pthread_mutex_destroy(&mutex);
	return 0;
}
