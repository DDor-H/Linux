#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <fcntl.h>

int main( int argc, char* argv[] ) {
	// 判断参数数量的合法性
	if ( argc != 3 ) {
		fprintf(stderr, "usage : %s src_file dst_file\n", argv[0]);
		exit(EXIT_FAILURE);
	}

	// 以只读的方式打开src文件
	int fd_src = open(argv[1], O_RDONLY);
	if ( fd_src == -1 ) {
		fprintf(stderr, "open(%s) : %se\n", argv[1], strerror(errno));
		exit(EXIT_FAILURE);
	}

	// 以只写的方式打开dst文件（不存在就创建）
	// O_TRUNC：如果文件存在，就将内容删除
	int fd_dst = open(argv[2], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if ( fd_dst == -1 ) {
		close(fd_src);  //重要，打开目标文件失败，就得关闭源文件
		fprintf(stderr, "open(%s) : %se\n", argv[2], strerror(errno));
		exit(EXIT_FAILURE);
	}

	char buf[1024];
	while ( 1 ) {
		memset(buf, 0x00, sizeof(buf));
		int ret = read(fd_src, buf, 1024);
		if ( ret == -1 ) { //读失败
			fprintf(stderr, "read(%s) : %se\n", argv[1], strerror(errno));
			break;
		} else if ( ret == 0 ) {  // 读完
			break;
		}
		
		if ( write(fd_dst, buf, ret) == -1 ) { //写失败
			fprintf(stderr, "write(%s) : %se\n", argv[2], strerror(errno));
			break;
		}
	}
	
	close(fd_src);
	close(fd_dst);
	return 0;
}
