#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

void handler( int s ) {
	printf("时间到\n");
	exit(0);
}

int main ( void ) {
	signal(SIGALRM, handler);
	
	alarm(3);
	while ( 1 ) {
		printf(".");
		sleep(1);
		fflush(stdout);
	}
	return 0;
}
