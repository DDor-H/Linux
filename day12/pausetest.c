#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

void handler( int s ) {
	printf("11111\n");
	sleep(3);
	printf("2222\n");
}

int main( void ) {
	signal(SIGINT, handler);
	for ( ; ; ) {
		pause();
		printf("pause return\n");	
	}
	return 0;
}
