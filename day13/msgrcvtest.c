#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <string.h>

struct msgbuf {
	long channel;
	char buf[100];
};

int main( void ) {
	int msg_id = msgget(1234, 0);
	struct msgbuf mb;

	memset(&mb, 0x00, sizeof(mb));
	printf("which channel:>");
	scanf("%ld", &(mb.channel));
	msgrcv(msg_id, &mb, sizeof(mb.buf), mb.channel, 0);
	printf("%s\n", mb.buf);
	return 0;
}
