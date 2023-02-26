
# include<stdio.h>
# include<sys/time.h>
# include<time.h>
# include<stdlib.h> 
# include<math.h>
#define K 1000
#define OSHELL "Ordenacion Shell "
#define OSEL "Ordenacion Seleccion "
#define ASC "con inicializacion ascendente"
#define DES "con inicializacion descendente"
#define ALE "con inicializacion aleatoria"


typedef int bool;
	#define TRUE 1
	#define FALSE 0


//ALGORITMO DE ORDENACION SELECCION
void ord_sel(int v[] , int n){
	int i,j,minj,minx;
	for (i = 0; i < n-1; i++)
	{
		minj = i;
		minx = v[i];
		for (j = i+1 ; j < n; j++)
		{
			if(v[j] < minx)
			{
				minj = j;
				minx = v[j];
			}
		}
		v[minj]= v[i];
		v[i] = minx;
	}
}

//ALGORITMO DE ORDENACIÓN SHELL
void ord_shell (int v [], int n){;
	int i,j,incremento,seguir,tmp;
	incremento = n-1;
	do { 
		incremento/=2;
		for(i = incremento; i<n; i++){
			tmp= v[i];
			j=i;
			seguir = TRUE;	
			while( (j- incremento >=0)&&(seguir) ){
				if (tmp < v[j-incremento]) {
					v[j]= v[j-incremento];
					j = j- incremento;
				}
				else seguir= FALSE;
			}
			v[j]= tmp;	
		}			
	} while (incremento!=1);
}



// Sacar por pantalla un vector 
void listar_vector (int v[],int n) {
    int i;
    printf("[");
    for(i=0;i<n;i++){
        printf("%2d%2s",v[i]," ");
    }
    printf("]");
}


// Establecer semilla 
void inicializar_semilla() {
	srand(time(NULL));
//Se genera la semilla de una nueva serie de enteros pseudo-aleatorios
}

//Vector Ordenado Ascendente
void ascendente(int v [], int n) {
	int i;
	for (i=0; i < n; i++)
		v[i] = i;
}

//Vector Ordenado Descendente
void descendente(int v [], int n) {
	int i;
	int j=0;
	for (i=n; i > 0;i--){		
		v[j] = i;
		j++;
	}	
}

// Generador Vector Aleatorio
void aleatorio(int v [], int n) {
	int i, m=2*n+1;
	for (i=0; i < n; i++)
		v[i] = (rand() % m) - n;
/* se generan números pseudoaleatorio entre -n y +n */
}

// Comprueba si un vector esta ya ordenado de menor a mayor
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

// Hora del sistema	
double microsegundos() { //Obtiene la hora del sistema en microsegundos
	struct timeval t;
	if (gettimeofday(&t, NULL) < 0 )
		return 0.0;
	return (t.tv_usec + t.tv_sec * 1000000.0);
}

//TEST ORDENACION SELECCION
void testSel()
{
	int v[16];
	int z[10] = {10,9,8,7,6,5,4,3,2,1};
	printf("Ordenacion por Selección con inicializacion aleatoria\n");
	aleatorio(v,16);
	listar_vector(v,16);
	printf("\n");
	printf("%5s%5d","ordenado?", comprobarOrd(v,16));//Comprobamos orden
	printf("\n");
	printf("ordenando...\n");	
	ord_sel(v,16);	
	listar_vector(v,16);
	printf("\n");		
	printf("%5s%5d","ordenado?", comprobarOrd(v,16));	
	printf("\n");
	printf("Ordenacion por Selección con inicializacion descendente\n");
	listar_vector(z,10);
	printf("\n");	
	printf("%5s%3d","ordenado?", comprobarOrd(z,10));	
	printf("\n");	
	printf("ordenando...\n");	
	ord_sel(z, 10 );
	listar_vector(z,10);
	printf("\n");		
	printf("%5s%5d","ordenado?", comprobarOrd(z,10));	

}

// TEST ORDENACION SHELL
void testShell(){
	int v[16];
	int d[10]= { 10,9,8,7,6,5,4,3,2,1 };
	printf("Ordenacion Shell con inicializacion aleatoria\n");
	aleatorio(v,16);
	listar_vector(v,16);
	printf("\n");
	printf("%5s%5d","ordenado?", comprobarOrd(v,16));	
	printf("\n");	
	printf("ordenando...\n");	
	ord_shell(v,16);	
	listar_vector(v,16);
	printf("\n");		
	printf("%5s%5d","ordenado?", comprobarOrd(v,16));	
	printf("\n");
	printf("Ordenacion Shell con inicializacion descendente\n");
	listar_vector(d,10);
	printf("\n");	
	printf("%5s%3d","ordenado?", comprobarOrd(d,10));	
	printf("\n");	
	printf("ordenando...\n");	
	ord_shell(d,10);
	listar_vector(d,10);
	printf("\n");		
	printf("%5s%5d","ordenado?", comprobarOrd(d,10));	
}

//Tiempo con Vectores Ascendentes
void tiempoAsc(void ordenar()){
		int i,j;
	double tant,tdes,ttot,t1,t2,tsub, taju, tsob;
	int v[32000];
	printf("%1s%1s\n",(ordenar==ord_sel) ? OSEL : OSHELL, ASC);
	printf("%4s%18s%21s%21s%21s\n","n","t(n)",
			(ordenar==ord_sel) ? "t(n)/n^1.8":"t(n)/n^1.05",//SUBEST
			(ordenar==ord_sel) ? "t(n)/n" : "t(n)/n^1.15",//AJUST
			(ordenar==ord_sel) ? "t(n)/n^2.2" : "t(n)/n^1.4");//SOBRE
	for (i=500;i <32001 ;i*=2 ) {
		ascendente(v,i);
		tant= microsegundos();
		ordenar(v,i);
		tdes=microsegundos();
		ttot= tdes - tant;
		if (ttot<500) {					// umbral de confianza
			tant= microsegundos();
			for (j=0; j<K; j++) {
				ascendente(v,j);
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
		tsub= (ordenar==ord_sel) ? ttot/pow(i,1.8) : ttot/pow(i,1.05);
		taju= (ordenar==ord_sel) ? ttot/pow(i,2) : ttot/pow(i,1.15);
		tsob= (ordenar==ord_sel) ? ttot/pow(i,2.2) : ttot/pow(i,1.4);
		printf("%3d%17.6f%18.6f%22.6f%18.6f\n", i,ttot,tsub,taju,tsob);
	}	
}

// Tiempo con vectores descendentes
void tiempoDesc(void ordenar()){
	int i,j;
	double tant,tdes,ttot,t1,t2,tsub, taju, tsob;
	int v[32000];
	printf("%1s%1s\n",(ordenar==ord_sel) ? OSEL : OSHELL, DES);
	printf("%4s%18s%21s%21s%21s\n","n","t(n)",
			(ordenar==ord_sel) ? "t(n)/n^1.8":"t(n)/n^1.1",//SUBEST
			(ordenar==ord_sel) ? "t(n)/n^2" : "t(n)/n^1.2",//AJUST
			(ordenar==ord_sel) ? "t(n)/n^2.2" : "t(n)/n^1.3");//SOBRE
	for (i=500;i <32001 ;i*=2 ) {
		descendente(v,i);
		tant= microsegundos();
		ordenar(v,i);
		tdes=microsegundos();
		ttot= tdes - tant;
		if (ttot<500) {					// umbral de confianza
			tant= microsegundos();
			for (j=0; j<K; j++) {
				descendente(v,j);
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
		tsub= (ordenar==ord_sel) ? ttot/pow(i,1.8) : ttot/pow(i,1.1);
		taju= (ordenar==ord_sel) ? ttot/pow(i,2) : ttot/pow(i,1.2);
		tsob= (ordenar==ord_sel) ? ttot/pow(i,2.2) : ttot/pow(i,1.3);
		printf("%3d%17.6f%18.6f%22.6f%18.6f\n", i,ttot,tsub,taju,tsob);
	}	
}	
	
// Tiempo con vectores descendentes	
void tiempoAleatorio(void ordenar()){
	int i,j;
	double tant,tdes,ttot,t1,t2,tsub, taju, tsob;
	int v[32000];
	printf("%1s%1s\n",(ordenar==ord_sel) ? OSEL : OSHELL, ALE);
	printf("%4s%18s%21s%21s%21s\n","n","t(n)",
			(ordenar==ord_sel) ? "t(n)/n^1.8":"t(n)/n^1.1",//SUBEST
			(ordenar==ord_sel) ? "t(n)/n^2" : "t(n)/n^1.15",//AJUST
			(ordenar==ord_sel) ? "t(n)/n^2.2" : "t(n)/n^1.3");//SOBRE
	for (i=500;i <32001 ;i*=2 ) {
		aleatorio(v,i);
		tant= microsegundos();
		if (ordenar==ord_sel)
			ord_sel(v,i);
		else ord_shell(v,i);
		tdes=microsegundos();
		ttot= tdes - tant;
		if (ttot<500) {					// umbral de confianza
			tant= microsegundos();
			for (j=0; j<K; j++) {
				aleatorio(v,j);
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
		tsub= (ordenar==ord_sel)? ttot/pow(i,1.8):ttot/pow(i,1.1);//SUBE  
		taju= (ordenar==ord_sel)? ttot/pow(i,2):ttot/pow(i,1.15);//AJUST
		tsob= (ordenar==ord_sel)? ttot/pow(i,2.2):ttot/pow(i,1.3);//SOBR
		printf("%3d%17.6f%18.6f%22.6f%18.6f\n",i,ttot,tsub,taju,tsob);
	}	
}		

int main(void){
	inicializar_semilla();	
	testSel() ;	
	printf("\n");	
	testShell();
	printf("\n");
	tiempoAsc(ord_sel);
	tiempoAsc(ord_shell);
	tiempoDesc(ord_sel);
	tiempoDesc(ord_shell);
	tiempoAleatorio(ord_sel);
	tiempoAleatorio(ord_shell);
	
	tiempoAsc(ord_sel);
	tiempoAsc(ord_shell);
	tiempoDesc(ord_sel);
	tiempoDesc(ord_shell);
	tiempoAleatorio(ord_sel);
	tiempoAleatorio(ord_shell);
	
	tiempoAsc(ord_sel);
	tiempoAsc(ord_shell);
	tiempoDesc(ord_sel);
	tiempoDesc(ord_shell);
	tiempoAleatorio(ord_sel);
	tiempoAleatorio(ord_shell);
	
	tiempoAsc(ord_sel);
	tiempoAsc(ord_shell);
	tiempoDesc(ord_sel);
	tiempoDesc(ord_shell);
	tiempoAleatorio(ord_sel);
	tiempoAleatorio(ord_shell);
	printf("\n");	
}
