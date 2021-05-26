#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// 创建退出执行函数
void func1( void ) { printf("func1\n"); }
void func2( void ) { printf("func2\n"); }

// 退出执行函数节点结构体
typedef struct func_node {
	void (*f)(void);
	struct func_node* next;
}node_t;

// 退出执行函数链表
node_t* head = NULL;

// 将退出执行函数加入链表
int my_atexit( void (*f)(void) )
{
	node_t* p = (node_t*)malloc(sizeof(node_t));
	p->f = f;
	p->next = NULL;
	
	// 头插节点，模拟压栈
	if (head == NULL)
		head = p;
	else
	{
		p->next = head;
		head = p;
	}
}

void my_exit( int s )
{
	fflush(stdout);  //刷新缓存

	// 执行退出执行函数	
	while( head != NULL )
	{
		head->f();
		head = head->next;
	}  // 没有释放节点内存，会出现内存泄露现象
	
	// 调用底层_exit()函数	
	_exit(s);
}

int main()
{
	my_atexit( func1 );
	my_atexit( func2 );
	printf("alibaba");
	
	while( getchar() != '\n' )
		;
	my_exit(-1);
	return 0;
}
