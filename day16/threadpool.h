#ifndef __THREADPOOL_H__
#define __THREADPOOL_H__

#include <pthread.h>
// 进程等待队列
typedef struct node_ {
	void* (*func)(void* arg);  // callback函数
	void* arg;  // 回调函数参数
	struct node_* next;  // 下一个任务节点
}node_t;

// 线程池结构体
typedef struct threadpool_ {
	pthread_cond_t cond;  // 生产者消费者需要一个条件变量
	pthread_mutex_t mutex;  //互斥变量
	node_t* first;  // 队头结点
	node_t* last;  // 队尾节点
	int max_thread;  // 最大线程容量
	int counter;  // 已用线程个数
	int idle;  // 未使用线程个数
	int quit;  // 是否离开线程池  1 or 0
}threadpool_t;

// 创建线程池
void threadpool_init(threadpool_t* thread, int num);
// 往线程池添加任务
void threadpool_add_task(threadpool_t* thread, void* (*func)(void*), void* args);
// 销毁线程池
void threadpool_destroy(threadpool_t* thread);

#endif // __THREADPOOL_H__
