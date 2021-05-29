#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

typedef struct {
	int id;
	char name[32];
}stu_t;

//输入学生信息
void input(int n) {
	int fd = open("stu.dat", O_RDWR | O_CREAT | O_TRUNC, 0644);
	if ( fd == -1 ) perror("open"), exit(1);
	
	int i = 1;
	do {
		stu_t s;
		s.id = i++;
		printf("name : ");
		scanf("%s", s.name);
		// 顺序写
		if ( write(fd, &s, sizeof(stu_t)) != sizeof(stu_t) ) perror("write"), exit(1);
	} while ( --n > 0 );
	
	close( fd );
}

//输出学生信息
void output( int n ) {
	int fd = open("stu.dat", O_RDONLY);
	if ( fd == -1 ) perror("open"), exit(1);
	
	int r = lseek(fd, (n - 1) * sizeof(stu_t), SEEK_END);
	if ( r == -1 ) perror("lseek"), exit(1);
	printf("offset = %d\n", r);
	
	stu_t s;
	if ( read(fd, &s, sizeof(s)) == -1 ) perror("read"), exit(1);
	printf("id = %d, name = %s\n", s.id, s.name);
	close(fd);
}

int main ( void ) {
	int  n;
	printf("要输入几个学生的信息：");
	scanf("%d", &n);
	input( n );

	while ( 1 ) {
		printf("要显示几号学生的信息（-1 exit）：");
		int m;
		scanf("%d", &m);
		if ( m == -1 ) break;
		output(m);
	}
	return 0;		
}



