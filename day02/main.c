#include <stdio.h>
#include "parse.h"
#include <string.h>

int main(void) {
	char buf[512] = {};

	while (1)
	{
		printf("计算器: ");
		memset(buf, 0x00, sizeof(buf));
		scanf("%[^\n]%*c", buf);
		//printf("buf = [%s]\n", buf);
		parse(buf);
	
	}

	return 0;
}
