# include<stdio.h>
# include<sys/time.h>
# include<time.h>
# include<stdlib.h>
# include<math.h>
# define UMBRAL 1
# define K 1000
# define INS "Ordenacion Insercion "
# define QSOR "Ordenacion Rapida "
# define ASC "con inicializacion ascendente"
# define DES "con inicializacion descendente"
# define ALE "con inicializacion aleatoria"

typedef int bool;
#define TRUE 1
#define FALSE 0

///////////////////////////////////////////////////////////////////////////////
// Establecer semilla
void inicializar_semilla() {
    srand(time(NULL));
/* se establece la semilla de una nueva serie de enteros pseudo-aleatorios */
}
///////////////////////////////////////////////////////////////////////////////
void listar_vector (int v[],int n) {
    int i;
    printf("[");
    for(i=0;i<n;i++){
        printf("%2d%2s",v[i]," ");
    }
    printf("]");
}
///////////////////////////////////////////////////////////////////////////////
//Intercambia los valores de dos posiciones de un vector
void intercambiar(int V[],int i, int j){
    int x = V[i];
    V[i]=V[j];
    V[j]=x;
}
///////////////////////////////////////////////////////////////////////////////
// Hora del sistema
double microsegundos(){
    struct timeval t;
    if (gettimeofday(&t, NULL) < 0 )
        return 0.0;
    return (t.tv_usec + t.tv_sec * 1000000.0);
}
///////////////////////////////////////////////////////////////////////////////
//Calculo de la mediana del vector
void mediana3(int V[],int izq,int der)
{
    int i=izq;
    int j=der;
    int k;
    k = (i + j)/2 ; /* precondición: i < j */
    if (V[k] > V[j]) {intercambiar (V,k,j) ;}
    if (V[k] > V[i]) {intercambiar (V,k,i) ;}
    if (V[i] > V[j]){intercambiar (V,i,j) ;}
}

///////////////////////////////////////////////////////////////////////////////
//Ordenacion auxiliar empleada en Quicksort
void rapida_aux(int v[],int izq, int der)
{
    int pivote,i,j;
    if ((izq + UMBRAL) <= der){
        mediana3(v,izq,der);
        pivote = v[izq];
        i = izq;
        j = der;
        do{
            do{ i = i + 1 ;} while(v[i] < pivote) ;
            do{j = j - 1 ;} while (v[j] > pivote) ;
            intercambiar (v,i,j);
        }while(j>i);
        intercambiar (v,i,j); /* se deshace el último intercambio */
        intercambiar (v,izq,j);
        rapida_aux (v,izq,j-1);
        rapida_aux (v,j+1,der);
    }
}

///////////////////////////////////////////////////////////////////////////////
//ORDENACION POR INSERCION
void ord_ins(int v[], int n){
	int i, j, x;
	for (i=1; i<n; i++) {
		x = v[i];
		j = i-1;
		while (j>=0 && v[j]>x) {
			if (v[j+1]!=v[j])
				v[j+1] = v[j];;
			j--;
		}
		v[j+1] = x;
	}
}

///////////////////////////////////////////////////////////////////////////////
//ORDENACION RAPIDA
void ord_rapida(int v [], int n) {
    rapida_aux(v, 0, n-1);
    if (UMBRAL > 1)
        ord_ins(v, n);
}

///////////////////////////////////////////////////////////////////////////////
// Generador Vector Aleatorio
void aleatorio(int v [], int n) {
	int i, m=2*n+1;
	for (i=0; i < n; i++)
		v[i] = (rand() % m) - n;
/* se generan números pseudoaleatorio entre -n y +n */
}

///////////////////////////////////////////////////////////////////////////////
// Crea vector ascendente de tamano n
void ascendente(int v [], int n) {
    int i;
    for (i=0; i < n; i++)
        v[i] = i+1;
}
///////////////////////////////////////////////////////////////////////////////
// Crea vector descendente de tamano n
void descendente(int v [], int n) {
    int i;
    int j=0;
    for (i=n; i > 0;i--){
        v[j] = i;
        j++;
    }
}
///////////////////////////////////////////////////////////////////////////////
//Comprueba si el vector esta ordenado
int comprobarOrd(int v[],int n){
    int i=0;
    int z=1;
    while((i<n-1)&&z){
        if (v[i]>v[i+1])
            z=0;
        i++;
    }
    return z;
}

///////////////////////////////////////////////////////////////////////////////
//Test Algoritmo de Insercion
void testIns() {
    int v[16];
    int z[10]= { 10,9,8,7,6,5,4,3,2,1 };
    printf("Ordenacion por insercion con inicializacion aleatoria\n");
    aleatorio(v,16);
    listar_vector(v,16);
    printf("\n");
    printf("%5s","ordenado?");	// Comprobamos si esta ordenado
    if (comprobarOrd(v,16)) {printf("%5s","Si");}
    else {printf("%5s","No");}
    printf("\n");
    printf("ordenando...\n");
    ord_ins(v,16);
    listar_vector(v,16);
    printf("\n");
    printf("%5s","ordenado?");	// Comprobamos si esta ordenado
    if (comprobarOrd(v,16)) {printf("%5s","Si");}
    else {printf("%5s","No");}
    printf("\n");
    printf("Ordenacion por insercion con inicializacion descendente\n");
    listar_vector(z,10);
    printf("\n");
    printf("%5s","ordenado?");	// Comprobamos si esta ordenado
    if (comprobarOrd(z,16)) {printf("%5s","Si");}
    else {printf("%5s","No");}
    printf("\n");
    printf("ordenando...\n");

    ord_ins(z, 10 );

    listar_vector(z,10);
    printf("\n");
    printf("%5s","ordenado?");
    if (comprobarOrd(z,10)) {printf("%5s","Si");}
    else {printf("%5s","No");}
    printf("\n");
}
///////////////////////////////////////////////////////////////////////////////
//Test Algoritmo de Quicksort
void testRapida() {
    int v[16];
    printf("Ordenacion rapida con inicializacion aleatoria\n");
    aleatorio(v,16);
    listar_vector(v,16);
    printf("\n");printf("%5s","ordenado?");	// Comprobamos si esta ordenado
    if (comprobarOrd(v,16)) {printf("%5s","Si");}
    else {printf("%5s","No");}
    printf("\n"); printf("ordenando...\n");
    ord_rapida(v,16);
    listar_vector(v,16);
    printf("\n");printf("%5s","ordenado?");	// Comprobamos si esta ordenado
    if (comprobarOrd(v,16)) {printf("%5s","Si");}
    else {printf("%5s","No");}
    printf("\n");

    printf("Ordenacion por rapida con inicializacion descendente\n");
    descendente(v,16);
    listar_vector(v,16);
    printf("\n"); printf("%5s","ordenado?");	// Comprobamos si esta ordenado

    if (comprobarOrd(v,16)) {printf("%5s","Si");}
    else {printf("%5s","No");}

    printf("\n"); printf("ordenando...\n");
    ord_rapida(v,16 );

    listar_vector(v,16);
    printf("\n");
    printf("%5s","ordenado?");
    if (comprobarOrd(v,16)) {printf("%5s","Si");}
    else {printf("%5s","No");}
    printf("\n");
}


//Tiempo con Vectores Ascendentes
void tiempoAsc(void (*ordenar)(int [],int)){
    int i,j;
    double tant,tdes,ttot,t1,t2,tsub, taju, tsob;
    int v[32000];
    printf("%1s%1s\n",(ordenar==ord_ins) ?  INS : QSOR, ASC);
    printf("%4s%18s%21s%21s%21s\n","n","t(n)",
           (ordenar==ord_ins) ? "t(n)/n^0.8":"t(n)/n^0.8",//SUBEST
           (ordenar==ord_ins) ? "t(n)/n" : "t(n)/n*log(n)",//AJUST
           (ordenar==ord_ins) ? "t(n)/n^1.5" : "t(n)/n^1.3");//SOBRE
    for (i=500;i <32001 ;i*=2 ) {
        ascendente(v,i);
        tant= microsegundos();
        ordenar(v,i);
        tdes=microsegundos();
        ttot= tdes - tant;
        if (ttot<500) {					// umbral de confianza
            tant= microsegundos();
            for (j=0; j<K; j++) {
                ascendente(v,i);
                ordenar(v,i);
            }
            tdes= microsegundos();
            t1= tdes - tant;
            tant= microsegundos();
            for (j=0; j<K; j++)//Descontamos la inicializacion de v
                ascendente(v,i);
            tdes= microsegundos();
            t2= tdes - tant;
            ttot= (t1-t2)/K;
            printf("(*)");
        }
        else{	
			printf("   ");
		}	
        tsub= (ordenar==ord_ins) ? ttot/pow(i,0.8) : ttot/pow(i,0.8);
        taju= (ordenar==ord_ins) ? ttot/pow(i,1) : ttot/(i*log(i));
        tsob= (ordenar==ord_ins) ? ttot/pow(i,1.5) : ttot/pow(i,1.3);
        printf("%6d%17.6f%18.6f%22.6f%18.6f\n", i,ttot,tsub,taju,tsob);
    }
}

// Tiempo con vectores descendentes
void tiempoDesc(void ordenar()){
    int i,j;
    double tant,tdes,ttot,t1,t2,tsub, taju, tsob;
    int v[32000];
    printf("%1s%1s\n",(ordenar==ord_ins) ? INS : QSOR, DES);
    printf("%4s%18s%21s%21s%21s\n","n","t(n)",
           (ordenar==ord_ins) ? "t(n)/n^1.8":"t(n)/n^0.8",//SUBEST
           (ordenar==ord_ins) ? "t(n)/n^2" : "t(n)/n^n*log(n)",//AJUST
           (ordenar==ord_ins) ? "t(n)/n^2.2" : "t(n)/n^1.3");//SOBRE
    for (i=500;i <32001 ;i*=2 ) {
        descendente(v,i);
        tant= microsegundos();
        ordenar(v,i);
        tdes=microsegundos();
        ttot= tdes - tant;
        if (ttot<500) {					// umbral de confianza
            tant= microsegundos();
            for (j=0; j<K; j++) {
                descendente(v,i);
                ordenar(v,i);
            }
            tdes= microsegundos();
            t1= tdes - tant;
            tant= microsegundos();
            for (j=0; j<K; j++)
                descendente(v,i);
            tdes= microsegundos();
            t2= tdes - tant;
            ttot= (t1-t2)/K;
            printf("(*)");
        }
        else{	
			printf("   ");
		}	
        tsub= (ordenar==ord_ins) ? ttot/pow(i,1.8) : ttot/pow(i,0.8);
        taju= (ordenar==ord_ins) ? ttot/pow(i,2) : ttot/(i*log(i));
        tsob= (ordenar==ord_ins) ? ttot/pow(i,2.2) : ttot/pow(i,1.3);
        printf("%6d%17.6f%18.6f%22.6f%18.6f\n", i,ttot,tsub,taju,tsob);
    }
}

// Tiempo con vectores aleatorios	
void tiempoAleatorio(void ordenar()){
	int i,j;
	double tant,tdes,ttot,t1,t2,tsub, taju, tsob;
	int v[32000];
	printf("%1s%1s\n",(ordenar==ord_ins) ? INS : QSOR, ALE);
	printf("%4s%18s%21s%21s%21s\n","n","t(n)",
           (ordenar==ord_ins) ? "t(n)/n^1.8":"t(n)/n^0.8",//SUBEST
           (ordenar==ord_ins) ? "t(n)/n^2" : "t(n)/n*log(n)",//AJUST
           (ordenar==ord_ins) ? "t(n)/n^2.2" : "t(n)/n^1.3");//SOBRE
	for (i=500;i <32001 ;i*=2 ) {
		aleatorio(v,i);
		tant= microsegundos();
		ordenar(v,i);
		tdes=microsegundos();
		ttot= tdes - tant;
		if (ttot<500) {					// umbral de confianza
			tant= microsegundos();
			for (j=0; j<K; j++) {
				aleatorio(v,i);
				ordenar(v,i);
			}
			tdes= microsegundos();
			t1= tdes - tant;
			tant= microsegundos();
			for (j=0; j<K; j++) 
				aleatorio(v,i);		
			tdes= microsegundos();
			t2= tdes - tant;
			ttot= (t1-t2)/K;
			printf("(*)");
		}
		else{	
			printf("   ");
		}	
		tsub= (ordenar==ord_ins) ? ttot/pow(i,1.8) : ttot/pow(i,0.8);
        taju= (ordenar==ord_ins) ? ttot/pow(i,2) : ttot/(i);
        tsob= (ordenar==ord_ins) ? ttot/pow(i,2.2) : ttot/pow(i,1.3);
        printf("%6d%17.6f%18.6f%22.6f%18.6f\n", i,ttot,tsub,taju,tsob);
	}	
}	
///////////////////////////////////////////////////////////////////////////////
//MAIN
int main() {
    inicializar_semilla();
    testIns() ;
    printf("\n");
    testRapida();
    printf("\n");
    tiempoAsc(ord_ins);
    tiempoDesc(ord_ins);
    tiempoAleatorio(ord_ins);
    tiempoAsc(ord_rapida);
    tiempoDesc(ord_rapida);
    tiempoAleatorio(ord_rapida);
    printf("\n");
}
