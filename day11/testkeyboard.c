#include <stdio.h>
#include <stdlib.h>
#include "keyboard.h"

int main ( void ) {
	init_keyboard();
	
	while ( 1 ) {
		int ch = get_key();
		if ( is_up(ch) )
			printf("up\n");
		if ( is_down(ch) )
			printf("down\n");
		if ( is_left(ch) )
			printf("left\n");
		if ( is_right(ch) )
			printf("right\n");
		if ( is_esc(ch) )
			break;
	}

	recover_keyboard();	
	return 0;
}
