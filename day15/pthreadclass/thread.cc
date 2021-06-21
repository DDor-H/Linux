#include "thread.h"
#include <iostream>
using namespace std;

Thread::Thread() {
	cout << "Thread()" << endl;
}

Thread::~Thread() {
	cout << "~Thread()" << endl;
}

void Thread::Start(){
	// 把对象地址传过去，防止因为静态函数丢失对象
	pthread_create(&threadID, NULL, ThreadRoutine, this);  
}

void Thread::Join() {
	pthread_join(threadID, NULL);
}

void* Thread::ThreadRoutine(void* arg) {
	Thread* thread = (Thread*)arg;
	thread->Run();
}

