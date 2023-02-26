#include <stdio.h>

int max(int a, int b, int c)
{
		if ((a>b)&&(a>c))
			return a;
		if ((b>a)&&(b>c))
			return b;
		if ((c>a)&&(c>b))
			return c;
		return a;
}


int SSMrec (int a[],int izq, int der)
{
	if (izq== der){
		if (a[izq] > 0)
			return a[izq];
		else
			return 0;
		}
	else {
			int centro = (izq + der) /2;
			int sol1 = SSMrec (a,izq,centro);
			int sol2 = SSMrec (a,centro+1,der);
			int sumaMI = 0;
			int sumaI = 0;
			for (int i = centro; i >= izq; i--)
			{
				sumaI = sumaI + a[i];
				if (sumaI > sumaMI)
					sumaMI = sumaI;
				
			}
			int sumaMD = 0;
			int sumaD = 0;
			for (int i = centro+1; i < der; i++)
			{
				sumaD = sumaD + a[i];
				if (sumaD > sumaMD)
					sumaMD = sumaD;
				
			}
			return max(sol1,sol2,sumaMD+sumaMI);
		}
}



int SSM (int a[],int n)
{
	return SSMrec (a,0,n);
}

int main() {
	int v[] = {15,-4,-2,7,-12,5};
	int res = SSM(v,6);
	printf("%i\n",res);
}

