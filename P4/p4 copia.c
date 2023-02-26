#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include <sys/time.h>
#include "cola.c"
#define infinito INT_MAX     

void inicializar_semilla() {
	srand(time(NULL));
}

// Hora del sistema	
double microsegundos() { /* obtiene la hora del sistema en microsegundos */
	struct timeval t;
	if (gettimeofday(&t, NULL) < 0 )
		return 0.0;
	return (t.tv_usec + t.tv_sec * 1000000.0);
	
}	
matriz crear_matriz(int n) {
	int i;
	matriz aux;	
	if ((aux = malloc(n*sizeof(int *))) == NULL)
		return NULL;
	for (i=0; i<n; i++)
		if ((aux[i] = malloc(n*sizeof(int))) == NULL)
			return NULL;
	return aux;
}
void inicializar_matriz(matriz m, int n) {
/* Crea un grafo completo no dirigido con valores aleatorios entre 1 y n */
	int i, j;
	for (i=0; i<n; i++)
		for (j=i+1; j<n; j++)
			m[i][j] = rand() % n + 1;
	for (i=0; i<n; i++)
		for (j=0; j<=i; j++)
			if (i==j)
				m[i][j] = 0;
			else
				m[i][j] = m[j][i];
}

void liberar_matriz(matriz m, int n) {
	int i;
	for (i=0; i<n; i++)
	free(m[i]);
	free(m);
}

void prim (matriz m, int nodos, cola *aristas) {
/* calcular el árbol de recubrimiento mínimo devolviendo
las aristas del arbol en la cola ’aristas’ */
	int min, i,z, j,k=0;
	arista a;
	int *masProximo = (int *) malloc(nodos*sizeof(int));
	int *distanciaMinima = (int *) malloc(nodos*sizeof(int));
	crear_cola(aristas);
	distanciaMinima[0] = -1;
	for(i = 1; i < nodos; i++) {
		masProximo[i] = 0;
		distanciaMinima[i] = m[i][0];
	}
	for (z=0; z<nodos -1;z++) { 
		min=infinito;
		for (j = 1; j < nodos; j++)
			if ((0 <= distanciaMinima[j])&&(
				distanciaMinima[j] < min)){
				min = distanciaMinima[j];
				k = j;
			}
		a.x = masProximo[k];
		a.y = k;
		a.peso = min;
		insertar(a, aristas);
		distanciaMinima[k] = -1;
		for (j = 1; j< nodos; j++){
			if ((m[j][k]) < (distanciaMinima[j])) {
				distanciaMinima[j] = m[j][k];
				masProximo[j] = k;
			}
		}	
	} 
	free(masProximo);
	free(distanciaMinima);
}	

void test1(){
	
	int n=5;
	cola C;  
	int i,j;
	int m[][5] = {
	    {0,1,8,4,7},
	    {1,0,2,6,5},
	    {8,2,0,9,5},
	    {4,6,9,0,3},
	    {7,5,5,3,0}
	};
	matriz a=crear_matriz(n);
	for (i=0;i<n;i++)
		for (j=0;j<n;j++)
			a[i][j] = m[i][j];
	prim(a,n,&C);
	mostrar_cola(C);
	liberar_matriz(a,5);
}

void test2(){
	cola P; 
	int n=4;
	int i,j;
	int m[][4] = {
	    {0,1,4,7},
	    {1,0,2,8},
	    {4,2,0,3},
	    {7,8,3,0}
	};
	matriz a=crear_matriz(n);
	for (i=0;i<n;i++)
		for (j=0;j<n;j++)
			a[i][j] = m[i][j];
	prim(a,n,&P);
	mostrar_cola(P);
	liberar_matriz(a,4);
}

void test3(){
	cola P; 
	int n=7;
	int i,j;
	int m[][7] = {
	{0,7,99,5,99,99,99},
	{7,0,8,9,7,99,99},
	{99,8,0,99,5,99,99},
	{5,9,99,0,15,6,99},
	{99,7,5,15,0,8,9},
	{99,99,99,6,8,0,11},
	{99,99,99,99,9,11,0}
	};
	matriz a=crear_matriz(n);
	for (i=0;i<n;i++)
		for (j=0;j<n;j++)
			a[i][j] = m[i][j];
	prim(a,n,&P);
	mostrar_cola(P);
	liberar_matriz(a,7);
}

void tiempos () {
	double tant,tdes,ttot,tsub, taju, tsob;
	int i, n,umbral;
	matriz m;
	cola C;
	printf("%9s%14s%16s%15s%16s\n","n","t(n)","t(n)//n^1.8","t(n)/n^2.05",
	       "t(n)/n^2.2"); 
	for (n = 10;n <= 640;n *= 2){
		umbral = 0;
		m= crear_matriz(n);   
		inicializar_matriz(m,n);
		tant = microsegundos();    
		prim(m,n,&C);
		tdes = microsegundos();
		ttot = tdes - tant;
		if (ttot < 500) {
		    umbral = 1;
		    tant = microsegundos();
		    for (i = 0;i < 1000;i++) 
			prim(m,n,&C);
		    tdes = microsegundos();
		    ttot = (tdes - tant)/1000;
		}
		liberar_matriz(m,n);
		tsub = ttot / pow(n, 1.8);
		taju = ttot / pow(n, 2.05);
		tsob = ttot / pow(n, 2.2);
		if (umbral == 1) 
			printf("%2s%6d%15.3f","(*)",n, ttot);	
		else printf("%9d%15.3f", n, ttot);
			printf("%15.8f%15.8f%15.8f\n", tsub, taju, tsob);
	}
	printf("\n");
}

int main(void) {
	inicializar_semilla();
	test1();
	test2();
	test3();
	tiempos();tiempos();tiempos();
	tiempos();tiempos();tiempos();
}
