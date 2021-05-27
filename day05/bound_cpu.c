#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sched.h>

int main ( void ) {
	pid_t pid;
	
	if ( (pid=fork()) == 0) {
		//child
		cpu_set_t cpu_affinity;
		CPU_ZERO(&cpu_affinity);
		CPU_SET(1, &cpu_affinity);
		sched_setaffinity(0, sizeof(cpu_affinity), &cpu_affinity);

		while (1) {
			printf("child\n");
		}
	} else {
		//parent
		cpu_set_t cpu_affinity;
		CPU_ZERO(&cpu_affinity);
		CPU_SET(0, &cpu_affinity);
		sched_setaffinity(0, sizeof(cpu_affinity), &cpu_affinity);

		while ( 1 ) {
			printf("parent\n");
		}
	}
	return 0;
}

