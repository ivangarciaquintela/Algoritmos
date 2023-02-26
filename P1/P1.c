//IVAN GARCIA QUINTELA
//ALVARO REGUEIRA VILAR 
//CANDELA IGLESIAS LORENZO
# include<stdio.h>
# include<sys/time.h>
# include<time.h>
# include<stdlib.h> 
# include<math.h>

//Primer Algoritmo

int sumaSubMax1 (int v[], int n){
	int i,j;
	int estaSuma, sumaMax =0;
	for(i=0; i<n;i++){
		estaSuma=0;
		for(j=i; j<n; j++){
			estaSuma += v[j];
			if (estaSuma > sumaMax)
				sumaMax = estaSuma;
			}
	}
	return sumaMax;
}

//Segundo Algoritmo
int sumaSubMax2(int v[], int n) {
	int j;
	int estaSuma = 0, sumaMax =0;
	for( j=0;j<n;j++){
		estaSuma = estaSuma + v[j];
		if(estaSuma>sumaMax)
		{
			sumaMax = estaSuma;
		}
		if (estaSuma<0){
				estaSuma =0 ;
		}
	}
	return sumaMax;		
}

//Establece una semilla
void inicializar_semilla() {
	srand(time(NULL));
/* se establece la semilla de una nueva serie de enteros pseudo-aleatorios */
}

//Generador de numeros aleatorios
void aleatorio(int v [], int n) {
	int i, m=2*n+1;
	for (i=0; i < n; i++)
		v[i] = (rand() % m) - n;
/* se generan números pseudoaleatorio entre -n y +n */
}

//Hora del sistema
double microsegundos() { /* obtiene la hora del sistema en microsegundos */
	struct timeval t;
	if (gettimeofday(&t, NULL) < 0 )
		return 0.0;
	return (t.tv_usec + t.tv_sec * 1000000.0);
}


//Sacar por pantalla vector
void listar_vector(int v[], int n){
	int i;
	for (i = 0; i < n; i++)
	{
		printf("%3d",v[i]);
	}
}


//TEST 1
void test1() {
 int i;
    int a, b;
    int v[][5] = {
		{-9, 2, -5, -4, 6},
        {4, 0, 9, 2, 5},
        {-2, -1, -9, -7, -1},
        {9, -2, 1, -7, -8},        
        {15, -2, -5, -4, 16},
        {7, -5, 6, 7, -7}
    };
    printf("Test con vectores establecidos\n");
    printf("%18s%15s%15s\n", "", "sumaSubMax1", "sumaSubMax2");
    for (i=0; i<6; i++) {
        listar_vector(v[i], 5);
        a = sumaSubMax1(v[i], 5);
        b = sumaSubMax2(v[i], 5);
        printf("%15d%15d\n", a, b);
    }
}

//TEST 2
void test2() {
	int i, a, b;
	int v[9];
	printf("test\n");
	printf("%33s%15s%15s\n", "", "sumaSubMax1", "sumaSubMax2");
	for (i=0; i<10; i++) {
		aleatorio(v, 9);
		listar_vector(v, 9);
		a = sumaSubMax1(v, 9);
		b = sumaSubMax2(v, 9);
		printf("%15d%15d\n", a, b);
	}
}

//MEDIR EL TIEMPO DEL ALGORITMO 1
void tiempo1()
{
	int i,n;
	double ti,tf,ttot,tsub, taju, tsob,t1,t2;
	int v[32000];
	printf("%1s\n"," Medicion sumaSubMax1 ");
	printf("%4s%18s%20s%20s%20s\n","n","t(n)","t(n)/n^1.8",
			"t(n)/n^2","t(n)/n^2.2");
	for (i=500;i <32001 ;i*=2 ) {
		aleatorio(v,i); 	
		ti= microsegundos();
		sumaSubMax1(v,i);
		tf=microsegundos();
		ttot= tf - ti;
		if (ttot<500) {	//Umbral de confianza
			ti= microsegundos();
			for (n=0; n<1001; n++) {
				aleatorio(v,i);
				sumaSubMax1(v,i);
			}
			tf= microsegundos();
			t1= tf - ti;
			ti= microsegundos();
			for (n=0; n<1001; n++) { //Descontamos la generación del vector
				aleatorio(v,i);
			}
			tf=microsegundos();
			t2 = tf- ti;
			ttot = (t1 - t2)/n;
		}
		tsub= ttot/pow(i,1.8);	// Cotas subestimada,ajustada y sobreestimada
		taju= ttot/pow(i,2);
		tsob= ttot/pow(i,2.2);
		printf("%5d%17.6f%18.6f%22.6f%18.6f\n",
					i, ttot, tsub, taju, tsob);				
	}
}


//MEDIR EL TIEMPO DEL ALGORITMO 2
void tiempo2()
{
	int i,j;
	double ti,tf,ttot,tsub, taju, tsob,t1,t2;
	int v[32000];
	printf("%1s\n"," Medicion sumaSubMax2 ");
	printf("%4s%18s%21s%21s%21s\n","n","t(n)","t(n)/n^0.8",
				"t(n)/n","t(n)/n*logn");
	for (i=500;i <32001 ;i*=2 ) {
		aleatorio(v,i);
		ti=microsegundos();
		sumaSubMax2(v,i);
		tf=microsegundos();
		ttot = tf - ti;
		if(ttot<500){				//Umbral de confianza
			ti = microsegundos();
			for (j = 0; j < 1001; j++)
			{
				aleatorio(v,i);
				sumaSubMax2(v,i);
			}
			tf = microsegundos();
			t1 = tf - ti;
			ti = microsegundos();
			for (j= 0; j < 1001; j++) //Descontamos la generación del vector
			{
				aleatorio(v,i);
			}
			tf = microsegundos();
			t2 = tf - ti;
			ttot = (t1-t2)/j;
			printf("(*)");
		}
		tsub= ttot/pow(i, 0.8);   // Cotas subestimada,ajustada y sobreestimada
		taju= ttot/i;
		tsob= ttot/(i*log(i));
		printf("%5d%17.6f%18.6f%22.6f%18.6f\n",
					i, ttot, tsub, taju, tsob);
	}
}


int main() {
	inicializar_semilla();
	test1();
	test2();
	tiempo1();
	tiempo2();

	return 0;
}
