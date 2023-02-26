#include <stdlib.h>
#include <stdio.h>
#include "cola.h"

typedef int bool;
	#define TRUE 1
	#define FALSE 0

void crear_cola (cola *C){
	C->tamano = 0;
	C->cabeza = 0;
	C->final = -1;
}

bool cola_vacia(cola C){
	return (C.tamano == 0);
}


void incrementar( int *x){
	if (++(*x) == TAM_MAX )
		*x =0;
		
}

void insertar(tipo_elemento x, cola * C){
	if (C->tamano == TAM_MAX){
		printf("error: cola llena: %d\n", C->tamano);
		exit(EXIT_FAILURE);
	}
	else {
		C->tamano++;
		incrementar(&C->final);
		C->vector[C->final] = x;
	}
}

tipo_elemento quitar_primero(cola *C){
	tipo_elemento x;
	if (cola_vacia(*C)){
		printf("error: cola vacia\n");
		exit(EXIT_FAILURE);
	}
	else {
		C->tamano --;
		x = C->vector[C->cabeza];
		incrementar(&(C->cabeza));
		return x;	
	}

}

tipo_elemento primero(cola c) {
	if (cola_vacia(c)) {
		printf("error: cola vacia\n"); exit(EXIT_FAILURE);
	}
	return(c.vector[c.cabeza]);
}

void mostrar_cola(cola c){	
	int peso=0;
	if ((cola_vacia(c) == TRUE)){
		printf("error: cola vacia\n"); 
		exit(EXIT_FAILURE);
	}
	else {
		printf("Aristas: ");
		while(cola_vacia(c)==FALSE){
			printf(" (%i,%i)", primero(c).x,primero(c).y);
			peso += primero(c).peso;
			if (c.tamano != 1)
				printf(",");
			quitar_primero(&c);	
		}
		printf("\n");
		printf("%s%i", "Peso: " , peso);
	}
	printf("\n");
}
	







