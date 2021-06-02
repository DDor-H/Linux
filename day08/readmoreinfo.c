#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>

int main ( int argc, char* argv[] ) {
	if ( argc == 1 )
		printf("usage : %s file\n", argv[0]), exit(0);
	
	struct stat buf;
	stat(argv[1], &buf);
	//%hhd ：以signed char的类型打印整数
	//%hhu ：以unsigned char的类型打印整数
	//buf.st_dev：文件的设备号，高8位，主设备号；低8位，次设备号；
	printf("主设备号：%hhu\n", (buf.st_dev >> 8) & 0xFF);
	printf("次设备号：%hhu\n", (buf.st_dev) & 0xFF);
	return 0;
}
