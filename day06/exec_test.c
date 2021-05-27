#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>

#define ERR_EXIT(msg) \
	do {  \
		printf("[%s][%d] %s: %s\n", __FILE__, __LINE__, msg, strerror(errno)); \
		exit(EXIT_FAILURE); \
	} while ( 0 )

int main( void ) {
	printf("before exec...\n");
	if ( execlp("ls", "ls", "-l", NULL) == -1 ) ERR_EXIT("execlp");
	printf("after exec...\n");
	return 0;
}
