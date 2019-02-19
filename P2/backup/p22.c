#include <stdio.h>

#define TAMANO 3
#define LIMITE 10
#define CAMBIAR 1

void f(int iteracion) {
	unsigned int i, x;
	unsigned int datos[TAMANO];

	x = 777;
	for (i = 0; i < TAMANO; i++) datos[i] = 666;
	printf("Entrando en la iteracion %d de f() con valor de x: %u\n", iteracion, x);
	if (iteracion == LIMITE - 1) {
		if (CAMBIAR) {
			for (i = 50; i < 120; i++) {
				if (datos[i] == 777) {
					datos[i] = 888;
					break;
				}
			}
		}
		//for (i = 0; i < 140; i++) printf("%x -> %x (%u)\n", &datos[i], datos[i], datos[i]);
	}
	if (iteracion < LIMITE) f(iteracion + 1);
	printf("Saliendo de la iteracion %d de f() con valor de x: %u\n", iteracion, x);
}

int main(void) {
	f(0);
	return 0;
}
