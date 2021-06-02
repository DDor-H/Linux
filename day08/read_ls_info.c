#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <error.h>
#include <string.h>
#include <pwd.h>
#include <grp.h>
#include <time.h>

void file_type(mode_t mode) {
	char buf[11] = "?---------";
	switch (mode & S_IFMT) {
		case S_IFSOCK: buf[0] = 's'; break;
		case S_IFLNK:  buf[0] = 'l'; break;
		case S_IFREG: buf[0] = '-'; break;
		case S_IFBLK:  buf[0] = 'b'; break;
		case S_IFDIR:  buf[0] = 'd'; break;
		case S_IFCHR:  buf[0] = 'c'; break;
		case S_IFIFO:  buf[0] = 'p'; break;
	}
	
	if ( mode & S_IRUSR ) buf[1] = 'r';
	if ( mode & S_IWUSR ) buf[2] = 'w';
	if ( mode & S_IXUSR ) buf[3] = 'x';
	if ( mode & S_IRGRP ) buf[4] = 'r';
	if ( mode & S_IWGRP ) buf[5] = 'w';
	if ( mode & S_IXGRP ) buf[6] = 'x';
	if ( mode & S_IROTH ) buf[7] = 'r';
	if ( mode & S_IWOTH ) buf[8] = 'w';
	if ( mode & S_IXOTH ) buf[9] = 'x';
	
	printf("%s. ", buf);
}

int main( int argc, char* argv[] ) {
	if ( argc == 1 ) 
		printf("usage : %s file\n", argv[0]), exit(0);
	
	struct stat buf;
	if (stat(argv[1], &buf) == -1)
		perror("stat"), exit(1);
	// 打印文件权限
	file_type(buf.st_mode);
	// 打印硬连接数
	printf("%d ", buf.st_nlink);
	// 打印用户名和用户组名
	// 利用专用函数，输入用户id和组id来得到用户名和组名
	struct passwd* pw = getpwuid(buf.st_uid);
	printf("%s ", pw->pw_name);
	struct group* gp = getgrgid(buf.st_gid);
	printf("%s ", gp->gr_name);
	// 文件大小（字节数）
	printf("%d ", buf.st_size);
	// 最后一次修改时间
	// OS提供的时间都是时间戳，可以通过localtime这个函数来将时间戳转换为一个结构体变量
	struct tm* ptm = localtime(&buf.st_mtime);
	printf("%d月  %2d %02d:%02d ", ptm->tm_mon + 1, ptm->tm_mday, ptm->tm_hour, ptm->tm_min);
	printf("%s", argv[1]);
	printf("\n");
	return 0;
}
