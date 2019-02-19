#include <stdio.h>

void f(int iteracion) {
	unsigned int i, x;
	unsigned int array[5];

	x = 666;
	for (i = 0; i < 5; i++) array[i] = 10*iteracion+i;
	printf("Entrando en la iteracion %d de f() con valor de x: %u\n", iteracion, x);
	if (iteracion == 4) 
		for (i = 50; i < 100; i++) {
				if (array[i] == 666) {
					array[i] = 777;
					break;
				}
			}
	if (iteracion < 5) f(iteracion + 1);
	printf("Saliendo de la iteracion %d de f() con valor de x: %u\n", iteracion, x);
}

main() {
	f(0);
}
