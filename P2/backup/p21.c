#include <stdio.h>

#define TAMANO 3
#define POSICION 5
#define SALTAR 1
#define CUANTAS 2

//NOTA: g() no debe modificar nunca el valor de la variable x
void g(void) {
	unsigned int i;
	unsigned int datos[TAMANO];

	for (i = 0; i < TAMANO; i++) datos[i] = 666;
	//for (i = 0; i < 15; i++) printf("%x -> %x (%u)\n", &datos[i], datos[i], datos[i]);
	if (SALTAR)
		datos[POSICION] += CUANTAS;
}

void f(void) {
	unsigned int x;

	x = 0;
	g();
	if (x != 0)
		x = 3 + x; /*INSTRUCCION QUE NOS VAMOS A SALTAR*/
	printf("Valor de x: %u\n", x);
}

int main(void) {
	f();
	return 0;
}
