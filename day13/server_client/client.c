#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <string.h>
#include <signal.h>


struct msgbuf {
	long msg_type;
	char buf[100];
};

int main ( void ) {
	struct msgbuf mb;
	int msg_id = msgget(12345, 0);
	
	while( fgets(mb.buf + sizeof(long), 100, stdin) != NULL ) {
		mb.msg_type = 1;
		// 类似于 *a = 10; 这种结构
		*(long*)mb.buf = getpid();
		msgsnd(msg_id, &mb, 100, 0);
		struct msgbuf mb2;
		memset(&mb2, 0x00, sizeof(mb2));
		msgrcv(msg_id, &mb2, 100, getpid(), 0);
		printf("=> %s\n", mb2.buf + sizeof(long));
	}
	return 0;
}
