#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>
#include <pthread.h>

sem_t sem;

void* r1(void* arg) {
	while ( 1 ) {
		sem_wait(&sem);
		printf("wait sem.\n");
	}
	return NULL;
}

void* r2(void* arg) {
	while ( 1 ) {
		sleep(1);
		sem_post(&sem);
	}
	return NULL;
}

int main( void ) {
	sem_init(&sem, 0, 3);
	
	pthread_t t1, t2;
	pthread_create(&t1, NULL, r1, NULL);
	pthread_create(&t2, NULL, r2, NULL);

	pthread_join(t1, NULL);
	pthread_join(t2, NULL);

	sem_destroy(&sem);
	return 0;
}
