#include <stdio.h>
#include <stdlib.h>

#define TAMANO 3
#define LIMITE 10
#define POSICION 5
#define NUEVA_POS1 65
#define NUEVA_POS2 69
#define NUEVA_POS3 114
#define SALTAR 3

void f(int iteracion);

void h(void) {
	printf("Hola Mundo\n");
	exit(0);
}

void g(int iteracion) {
	unsigned int y;

	y = 777;
	printf("Entrando en la iteracion %d de g() con valor de y: %u\n", iteracion, y);
	if (iteracion < LIMITE) f(iteracion + 1);
	printf("Saliendo de la iteracion %d de g() con valor de y: %u\n", iteracion, y);
}

void f(int iteracion) {
	unsigned int i, x;
	unsigned int datos[TAMANO];

	for (i = 0; i < TAMANO; i++) datos[i] = 888;
	//if (iteracion == LIMITE - 1)
		//for (i = 0; i < 140; i++) printf("%x -> %x (%u)\n", &datos[i], datos[i], datos[i]);
	if ((SALTAR == 1) && (iteracion == LIMITE)) {
		datos[POSICION] = datos[NUEVA_POS1];
		datos[POSICION + 1] = datos[NUEVA_POS1 + 1];
	}
	else if ((SALTAR == 2) && (iteracion == LIMITE)) {
		datos[POSICION] = datos[NUEVA_POS2];
		datos[POSICION + 1] = datos[NUEVA_POS2 + 1];
	}
	else if ((SALTAR == 3) && (iteracion == LIMITE)) {
		datos[POSICION] = datos[NUEVA_POS3];
		datos[POSICION + 1] = h;
	}
	x = 666;
	printf("Entrando en la iteracion %d de f() con valor de x: %u\n", iteracion, x);
	g(iteracion);
	printf("Saliendo de la iteracion %d de f() con valor de x: %u\n", iteracion, x);
}

int main(void) {
	f(0);
	return 0;
}
