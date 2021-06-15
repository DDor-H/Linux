#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

void handler( int s ) {
	printf("11111\n");
	sleep(3);
	printf("2222\n");
}

void handler_quit( int s ) {
}

int main( void ) {
	signal(SIGINT, handler);
	signal(SIGQUIT, handler_quit);
	
	sigset_t mask;
	sigemptyset(&mask);
	sigaddset(&mask, SIGINT);	

	for ( ; ; ) {
		//pause();
		sigsuspend(&mask);
		printf("pause return\n");	
	}
	return 0;
}
