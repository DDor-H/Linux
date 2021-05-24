#include <stdio.h>
#include <unistd.h>

int main(void)
{
	char buf[100] = {};
	char *p = "|/-\\";

	int i;
	for (i=0;i<100;++i)
	{
		buf[i] = '#';
		printf("[%-100s][%d%%][%c]\r", buf, i+1, p[i%4]);
		fflush(stdout);
		usleep(500000);
	}
	return 0;
}
