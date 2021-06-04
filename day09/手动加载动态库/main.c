#include <stdio.h>
#include <stdlib.h>
#include <dlfcn.h>

int main ( void ) {
	void* p = dlopen("./libmymath.so", RTLD_LAZY);
	void (*pf)( void ) = dlsym(p, "func");
	
	pf();
	
	dlclose(p);
	return 0;
}
