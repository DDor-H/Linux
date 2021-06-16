#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <string.h>
#include <signal.h>

int msg_id;

struct msgbuf {
	long msg_type;
	char buf[100];
};
void handler( int s ) {
	msgctl(msg_id, IPC_RMID, NULL);
	exit(0);
}

int main ( void ) {
	struct sigaction act;
	act.sa_handler = handler;
	sigemptyset(&act.sa_mask);
	act.sa_flags = 0;
	sigaction(SIGINT, &act, NULL);

	struct msgbuf mb;
	msg_id = msgget(12345, IPC_CREAT | 0644);
	
	while( 1 ) {
		memset(&mb, 0x00, sizeof(mb));
		// 服务器只在 1 号通道取消息
		msgrcv(msg_id, &mb, 100, 1, 0);
		//pid_t pid = *(pid_t*)(mb.buf);
		// 再将要回复的消息放到pid号通道
		mb.msg_type = *(long*)(mb.buf);
		// 服务器只读取了pid，然后将消息原封不动的返回了
		msgsnd(msg_id, &mb, 100, 0);
	}
	return 0;
}
