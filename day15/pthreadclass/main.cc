#include "thread.h"
#include <iostream>
using namespace std;
#include <unistd.h>

class MyThread : public Thread {
public:
	MyThread() : cnt(5) { cout << "MyThread()" << endl; }
	~MyThread() { cout << "~MyThread()" << endl; }

private:
	void Run() {
		int i;
		for ( i = 0; i < 5; i++ ) {
			cout << "cnt : " << i << endl;
			sleep(1);
		}
	}
	int cnt;
};

int main( void ) {
	MyThread th;
	th.Start();
	th.Join();
}
	
