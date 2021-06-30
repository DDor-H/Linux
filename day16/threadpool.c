#include <stdio.h>
#include <stdlib.h>
#include "threadpool.h"
#include <time.h>
#include <errno.h>

void* thread_routine(void* arg) {
	threadpool_t* pool = (threadpool_t*)arg;
	int	timeout = 0; // 超时退出标志
	while ( 1 ) {
		pthread_mutex_lock(&pool->mutex);
		// 没有新任务并且不退出线程池时，阻塞等待任务

		pool->idle++;
		while ( pool->first == NULL && pool->quit != 1 ) {
			printf("%p 正在等待任务.\n", pthread_self());
			
			// timedwait超时阻塞函数，参数struct timespec
			struct timespec abstime; // 绝对时间
			clock_gettime(CLOCK_REALTIME, &abstime);
			abstime.tv_sec += 2;  // 超时两秒则结束阻塞
			int res = pthread_cond_timedwait(&pool->cond, &pool->mutex, &abstime);
			if ( res == ETIMEDOUT ) {
				timeout = 1;
				break;
			}
		}

		// 有新任务了
//		pool->idle--;
		if ( pool->first != NULL ) { // 防止任务被其他线程抢去
			pool->idle--;
			node_t* tmp = pool->first;
			pool->first = tmp->next;

			// 执行线程回调函数时，可能需要很长时间
			// 此时需要解锁，方便其他线程去处理新的任务
			pthread_mutex_unlock(&pool->mutex);
			tmp->func(tmp->arg);
			free(tmp);  // 释放掉动态开辟的任务内存
			pthread_mutex_lock(&pool->mutex);
		}
		
		// 当退出标志为1，并且准备退出时，没有新任务到来，则可以退出
		if ( pool->quit == 1 && pool->first == NULL ) {
			pool->counter--;  // 线程数减一
			if ( pool->counter == 0 ) {
				// 最后一个活着的线程退出了，就可以给destroy函数发信号
				// 说可以结束阻塞等待，所有的线程都结束了
				pthread_cond_signal(&pool->cond);
			}
			// 当前线程结束前，要先解锁，以便后续线程可以正常运行
			pthread_mutex_unlock(&pool->mutex);
			break;
		}
		
		// 超时退出
		if ( timeout == 1 && pool->first == NULL ) {
			pool->counter--;
			printf("%p 线程超时退出.\n", pthread_self());
			pthread_mutex_unlock(&pool->mutex);
			break;
		}
				
		pthread_mutex_unlock(&pool->mutex);
	}
	printf("%p 线程退出.\n", pthread_self());
}

// 创建线程池
void threadpool_init(threadpool_t* thread, int num) {
	pthread_cond_init(&thread->cond, NULL);	
	pthread_mutex_init(&thread->mutex, NULL);
	thread->first = NULL;
	thread->last = NULL;
	thread->max_thread = num;
	thread->counter    = 0;
	thread->idle       = 0;
	thread->quit       = 0;
}

// 往线程池添加任务
void threadpool_add_task(threadpool_t* thread, void* (*func)(void*), void* args) {
	node_t* newtask = (node_t*)malloc(sizeof(node_t));
	newtask->func = func;
	newtask->arg  = args;
	newtask->next = NULL;
	
	pthread_mutex_lock(&thread->mutex);
	// 直接将任务先加入任务队列，后续做统一处理
	if ( thread->first == NULL ) { // 只要针对线程池元素做修改，就需要上锁
		thread->first = newtask;  // 因为是线程池变量是一个临界资源；
	} else { 
		thread->last->next = newtask;
	}
	thread->last = newtask;

	if ( thread->idle > 0 ) {  // 线程池中有空闲线程
		pthread_cond_signal(&thread->cond);
	} else if ( thread->counter < thread->max_thread ) { // 线程池中没有空闲线程，但还可以继续创建
		pthread_t pid;
		// 回调函数需要知道线程池的情况，所以需要将线程池本身作为参数传递过去
		pthread_create(&pid, NULL, thread_routine, thread);
		thread->counter++;  // 这个也需要上锁
		// 不能在这里通知，各个线程是否空闲（即idle++）得由他们自己决定
		// 信号通知也有可能白通知（线程还没阻塞）
		// 若线程创建满后，只能等第一个线程依次执行完才能执行下一个任务（还是第一个线程执行）;
//		thread->idle++;  // 空闲线程数++
//		pthread_cond_signal(&thread->cond);  // 通知有空闲
	}
	pthread_mutex_unlock(&thread->mutex);
}

// 销毁线程池
void threadpool_destroy(threadpool_t* thread) {
	if ( thread->quit == 1 )
		return;
	pthread_mutex_lock(&thread->mutex);
	thread->quit = 1;
	
	// 如果有线程存在，在通知结束线程（回收由系统回收）
	if ( thread->counter > 0 ) {
		// 如果有空闲线程，则用broadcast一并通知结束；
		// broadcast和signal的区别在于可以一次通知所有的阻塞线程
		// 但这里只有空闲线程阻塞了
		if ( thread->idle > 0 ) 
			pthread_cond_broadcast(&thread->cond);
		// 上面那个 if 通知了所有空闲的
		// 还有正在运行的线程，得阻塞等待，所以用wait阻塞
		// while的使用含义和wait等待 条件变量 一样，防止外界信号唤醒wait
		while ( thread->counter > 0 )
			pthread_cond_wait(&thread->cond, &thread->mutex);
	}
	pthread_mutex_unlock(&thread->mutex);		
	pthread_mutex_destroy(&thread->mutex);
	pthread_cond_destroy(&thread->cond);
}



