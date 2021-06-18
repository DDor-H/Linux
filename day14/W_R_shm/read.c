#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/shm.h>
#include <sys/ipc.h>
#include <string.h>


int main( void ) {
	int id = shmget(1234, 0, 0);
	if ( id == -1 ) perror("shmget"), exit(1);
	int* p = (int*)shmat(id, NULL, 0);
	printf("num:> %d\n", *p);
	return 0;
}
