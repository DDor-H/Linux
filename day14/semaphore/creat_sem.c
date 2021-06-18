#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/sem.h>

int main ( void ) {
	int id = semget(1234, 1, IPC_CREAT | 0644);
	return 0;
}
