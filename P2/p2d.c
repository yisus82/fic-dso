#include <stdio.h>

int i=0;

void g() {
	i=1;	
}

void f() {
	unsigned int array[5];
	
	array[-2] = array[5];
	array[-1] = array[6];
	array[5] = (unsigned int) &array[-2];
	array[6] = (unsigned int) g;
}

main() {

	printf("El valor de i es %d\n",i);
	f();
	printf("El valor de i es %d\n",i);	

}
