#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

#define PRO 3
#define CUS 2
int g_data = 0;

pthread_cond_t cond;
pthread_mutex_t mutex;

void* pro(void* arg) {
	int id = *(int*)arg;
	free(arg); // 重要细节
	while ( 1 ) {
		pthread_mutex_lock(&mutex);  // P操作，防止多个生产者竞争
		printf("生产者线程 %d，开始生产产品，编号：%d\n", id, g_data);
		g_data++;
		sleep(rand() % 3);
		printf("生产者线程 %d，生产出产品 编号：%d\n", id, g_data - 1);
		pthread_cond_signal(&cond);  // 生产完给消费者发通知
		pthread_mutex_unlock(&mutex);  // V操作
		sleep(1);
	}
}

void* cus(void* arg) {
	int id = *(int*)arg;
	free(arg); // 重要细节
	while ( 1 ) {
		pthread_mutex_lock(&mutex);
		while ( g_data <= 0 ) {
			printf("没有产品可以消费，%d消费者线程休息\n", id);
			pthread_cond_wait(&cond, &mutex);  // 阻塞接收生产者的通知
			printf("%d 消费者线程被唤醒\n", id);
		}
		printf("消费者线程 %d，开始消费产品，编号：%d\n", id, g_data);
		g_data--;
		sleep(rand() % 3);
		printf("消费者线程 %d，消费完产品，编号：%d\n", id, g_data + 1);
		pthread_mutex_unlock(&mutex);
		sleep(1);
	}
}

int main( void ) {
	pthread_t tid[PRO + CUS];
	// 初始化信号量和条件变量
	pthread_mutex_init(&mutex, NULL);
	pthread_cond_init(&cond, NULL);
	int i;
	// 创建所有线程
	for ( i = 0; i < PRO ; ++i ) {
		int* p = (int*)malloc(sizeof(int));
		*p = i;
		pthread_create(&tid[i], NULL, pro, (void*)p);
	}
	for ( i = 0; i < CUS ; ++i ) {
		int* p = (int*)malloc(sizeof(int));
		*p = i + PRO;
		pthread_create(&tid[i + PRO], NULL, cus, (void*)p);
	}

	// 释放僵尸线程
	for ( i = 0; i < PRO + CUS; ++i ) {
		pthread_join(tid[i], NULL);
	}
	// 释放掉信号量和条件变量
	pthread_mutex_destroy(&mutex);
	pthread_cond_destroy(&cond);
	return 0;
}
