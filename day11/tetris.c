#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>
#include <sys/time.h>
#include "keyboard.h"
#define FC 5
#define BC 7
#define W 10
#define H 20

// 当前点的位置结构体
struct data {
	int x;
	int y;
};

// 初始位置
struct data t = { 5, 0 };

// 背景值
int background[H][W] = {};

// 将x，y点的位置置为c颜色
void draw_element( int x, int y, int c ) {
	x *= 2;
	y++;
	x++;
	printf("\033[%d;%dH\033[3%dm\033[4%dm[]\033[?25l\033[0m", y, x, c, c);
	fflush(stdout);
}

// 方块模型结构体
struct shape {
	int s[5][5];
};
struct shape shape_arr[7] = {
	{ 0,0,0,0,0, 0,0,1,0,0, 0,1,1,1,0, 0,0,0,0,0, 0,0,0,0,0,},	
	{ 0,0,0,0,0, 0,0,1,1,0, 0,1,1,0,0, 0,0,0,0,0, 0,0,0,0,0,},
	{ 0,0,0,0,0, 0,1,1,0,0, 0,0,1,1,0, 0,0,0,0,0, 0,0,0,0,0,},
	{ 0,0,0,0,0, 0,0,1,0,0, 0,0,1,0,0, 0,0,1,1,0, 0,0,0,0,0,},
	{ 0,0,0,0,0, 0,0,1,0,0, 0,0,1,0,0, 0,1,1,0,0, 0,0,0,0,0,},
	{ 0,0,0,0,0, 0,1,1,0,0, 0,1,1,0,0, 0,0,0,0,0, 0,0,0,0,0,},
	{ 0,0,0,0,0, 0,0,1,0,0, 0,0,1,0,0, 0,0,1,0,0, 0,0,0,0,0,},
};

//从X，Y位置开始将 p 图形绘制成 c 颜色
void draw_shape(int x, int y, struct shape p, int c) {
	int i, j;
	for (i = 0; i < 5; ++i) {
		for (j = 0; j < 5; ++j) {
			if (p.s[i][j] != 0) {
				draw_element(x+j, y+i, c);
			}
		}
	}
}

// 绘制背景
void draw_background() {
	int i, j;
	for ( i = 0; i < H; ++i ) {
		for ( j = 0; j < W; ++j ) {
			// 要是方块，就绘制前景色，否则绘制为背景色
			if ( background[i][j] == 0 )
				draw_element(j, i, BC);
			else
				draw_element(j, i, FC);
		}
	}
}

// 判断是否可以再次移动
// 判断边界，以及当前位置是否已有方块
int can_move(int x, int y, struct shape p) {
	int i, j;
	for ( i = 0; i < 5; ++i ) {
		for ( j = 0; j < 5; ++j ) {
			if ( p.s[i][j] == 0 ) continue;
			if ( y + i >= H ) return 0;
			if ( y + i <  0 ) return 0;
			if ( x + j >= W ) return 0;
			if ( x + j <  0 ) return 0;
			if ( background[y+i][x+j] != 0 ) return 0;
		}
	}
	return 1;
}

// 模块顺时针旋转90°，即up键
struct shape turn_90(struct shape p) {
	struct shape tmp;
	int i, j;
	for ( i = 0; i < 5; ++i ) {
		for ( j = 0; j < 5; ++j ) {
			tmp.s[i][j] = p.s[j][4-i];
		}
	}
	return tmp;
}

// 逆时针旋转90°
struct shape turn_n90(struct shape p) {
	struct shape tmp;
	int i, j;
	for ( i = 0; i < 5; ++i ) {
		for ( j = 0; j < 5; ++j ) {
			tmp.s[i][j] = p.s[4-j][i];
		}
	}
	return tmp;
}


// 按键操控
// 先将原位置置为背景色，然后判断是否可以操纵
// 再将修改后（也可能没修改）的位置置为前景色
void tetris(struct data* t) {
	int c = get_key();
	if ( is_up(c) ) {
		draw_shape(t->x, t->y, shape_arr[0], BC);
		shape_arr[0] = turn_90(shape_arr[0]);
		// 旋转越界就得再转回去
		if ( can_move(t->x, t->y, shape_arr[0]) == 0 )
			shape_arr[0] = turn_n90(shape_arr[0]);
		draw_shape(t->x, t->y, shape_arr[0], FC);
	} else if ( is_down(c) ) {
		draw_shape(t->x, t->y, shape_arr[0], BC);
		if ( can_move(t->x, t->y+1, shape_arr[0]) != 0 ) {
			t->y++;
		}
		draw_shape(t->x, t->y, shape_arr[0], FC);
	} else if ( is_left(c) ) {
		draw_shape(t->x, t->y, shape_arr[0], BC);
		if ( can_move(t->x-1, t->y, shape_arr[0]) != 0 ) {		
			t->x--;
		}
		draw_shape(t->x, t->y, shape_arr[0], FC);
	} else if ( is_right(c) ) {
		draw_shape(t->x, t->y, shape_arr[0], BC);
		if ( can_move(t->x+1, t->y, shape_arr[0]) != 0 ) {
			t->x++;
		}
		draw_shape(t->x, t->y, shape_arr[0], FC);
	} 
}

// 方块到达底部了，就将方块写回到背景矩阵
void set_background(struct data* t, struct shape p) {
	int i, j;
	for ( i = 0; i < 5; ++i ) {
		for ( j = 0; j < 5; ++j ) {
			if ( p.s[i][j] != 0 ) {
				background[t->y + i][t->x + j] = 1;
			}
		}
	}
}

// 清理消除的所有行，自下向上，效率高
void clean_line( void ) {
	int i, j;
	
	for ( i = H - 1; i > 0; --i ) {
		int total = 0;  // 当前行1的个数
		for ( j = 0; j < W; ++j ) {
			if ( background[i][j] != 0 ) 
				++total;
		}
		if ( total == W ) {
			int k;
			for ( k = i; k > 0; --k ) {
				memcpy(background[k], background[k-1], sizeof(background[k]));
			}
			memset(background[0], 0x00, sizeof(background[0]));
		}
	}
}

// 信号处理自动向下走的handler函数
void tetris_timer(struct data* t) {
	draw_shape(t->x, t->y, shape_arr[0], BC);
	if ( can_move(t->x, t->y + 1, shape_arr[0]) != 0 ) {
		t->y++;
	} else {
		// 如果到底了就得写回背景矩阵
		// 并从初始位置重新生成一个
		// 再检查是否有可清除的行
		// 清除完重绘制背景
		set_background(t, shape_arr[0]);
		t->y = 0;
		t->x = 5;
		clean_line();
		draw_background();
	}
	draw_shape(t->x, t->y, shape_arr[0], FC);
}

void handler( int s ) {
	tetris_timer(&t);
}


int main ( void ) {
	signal(SIGALRM, handler);
	struct itimerval it;
	it.it_value.tv_sec     = 1;
	it.it_value.tv_usec    = 0;
	it.it_interval.tv_sec  = 1;
	it.it_interval.tv_usec = 0;
	setitimer(ITIMER_REAL, &it, NULL);
	
	draw_background();
	//键盘事件初始化	
	init_keyboard();
	for ( ; ; ) {
		//接收键盘事件
		tetris(&t);
	}
	//键盘事件恢复
	recover_keyboard();
	return 0;
}
