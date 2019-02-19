#include <stdio.h>

void f() {
	unsigned int array[5];
	array[6]+=13;
}

main () {
	f();
	printf("\nmain: El salto NO ha funcionado\n");
	printf("\nmain: El salto SI ha funcionado\n");
}
