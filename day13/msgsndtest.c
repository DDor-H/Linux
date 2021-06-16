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
	int msg_id = msgget(1234, 0);  // 已经存在，只打开，填 0 
	
	struct msgbuf mb;
	printf("channel:>");
	scanf("%ld", &(mb.channel));
	printf("message:>");
	scanf("%s", mb.buf);
	
	if ( (msgsnd(msg_id, &mb, strlen(mb.buf), 0)) == -1 ) 
		perror("msgsnd"), exit(1);
	return 0;
}
