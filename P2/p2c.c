#include <stdio.h>

#define SALTO 24 //Longitud de frames (longitud frame f + longitud frame g)

int cantidad=5; //Numero de iteraciones que se quieren saltar

void f(int iteracion);

void g(int iteracion) {
	printf("Entrando en la iteracion %d de g()\n", iteracion);
	if (iteracion < 10) f(iteracion + 1);
	printf("Saliendo de la iteracion %d de g()\n", iteracion);
}

void f(int iteracion) {
	unsigned int i;
	unsigned int array[5];

	for (i = 0; i < 5; i++) array[i] = 10*iteracion+i;
	
	if (iteracion == 10) {
		array[6] = array[6+cantidad*SALTO];
		array[7] = array[7+cantidad*SALTO];
	}
	printf("Entrando en la iteracion %d de f()\n", iteracion);
	g(iteracion);
	printf("Saliendo de la iteracion %d de f()\n", iteracion);
}

main() {
	f(0);
}
