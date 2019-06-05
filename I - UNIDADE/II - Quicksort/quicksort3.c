#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct VETOR{
	int tam;
	int cont;
	int *vet;
}vetor;

int cont = 0;

void trocar (int *v1, int *v2){
	cont++;
	int aux = *v1;
	*v1 = *v2;
	*v2 = aux;
}

int mediana(int *v, int inicio, int fim){
	int n = fim + 1 - inicio;
	int v1 = (v[inicio + (n/4)]);
	int v2 = (v[inicio + (n/2)]);
	int v3 = (v[inicio + ((3*n)/4)]);
	if(v1 >= v2 && v2 >= v3)
		return inicio + n/2;
	if(v2 >= v3 && v3 >= v1)
		return inicio + (3*n)/4;
	if(v2 >= v1 && v1 >= v3)
		return inicio + n/4;
		
	if(v3 >= v2 && v2 >= v1)
		return inicio + n/2;
	if(v1 >= v3 && v3 >= v2)
		return inicio + (3*n)/4;
	if(v3 >= v1 && v1 >= v2)
		return inicio + n/4;
		
	return -1;
}

int aleatorio(int *v, int inicio, int fim){
	int n = (fim + 1) - inicio;
	int va = inicio + abs(v[inicio]) % n;
	return va;
}

int particionar(int *V, int inicio, int fim, int tipopivo){
	int piv, pivo;
	switch(tipopivo){
		case 0: // padrao
			pivo = V[fim];
			break;
		case 1: // mediana de 3
			piv = mediana(V,inicio,fim);
			trocar(&V[piv],&V[fim]);
			break;
		case 2: // aleatorio
			piv = aleatorio(V,inicio,fim);
			trocar(&V[piv],&V[fim]);
			break;
	}
	
	pivo = V[fim];
	
	int i = inicio - 1, j;
	for(j = inicio; j < fim; j++) {
		if(V[j] <= pivo) {
			i = i + 1;
			trocar(&V[i], &V[j]);
		}
	}
	trocar(&V[i + 1], &V[fim]);
	return i + 1;
}

int hoare(int V[], int inicio, int fim, int tipopivo){
	int piv, pivo;
	switch(tipopivo){
		case 0: // padrao
			pivo = V[inicio];
			break;
		case 1: // mediana de 3
			piv = mediana(V,inicio,fim);
			trocar(&V[piv],&V[inicio]);
			pivo = V[inicio];
			break;
		case 2: // aleatorio
			piv = aleatorio(V,inicio,fim);
			trocar(&V[piv],&V[inicio]);
			pivo = V[inicio];
			break;
	}
	int i = inicio;
	int j = fim;
	while(i < j) {
		while(j > i && V[j] >= pivo) j--;
			while(i < j && V[i] < pivo) i++;
				if(i < j) trocar(&V[i], &V[j]);
	}
	return j;
}

void quicksort(int *V, int inicio, int fim, int tipo, int tipopivo){
	cont++;
	switch (tipo){
		case 0: // particionar
			if(inicio < fim) {
				int pivo = particionar(V, inicio, fim, tipopivo);
				quicksort(V, inicio, pivo - 1,tipo,tipopivo);
				quicksort(V, pivo + 1, fim,tipo,tipopivo);
			}
			break;
		case 1: // hoare
			if(inicio < fim) {
				int pivo = hoare(V, inicio, fim, tipopivo);
				quicksort(V, inicio, pivo,tipo,tipopivo);
				quicksort(V, pivo + 1, fim,tipo,tipopivo);
			}
			break;
	}
}

int main(int argc, char **argv)
{
	FILE* input = fopen("quicksort.in.txt","r");
	FILE* output = fopen("output.txt","w");
	
	int n,i,j,tam;
	
	fscanf(input,"%d\n",&n);
	int **matrix = malloc(sizeof(int)*n);
	for(i=0;i<n;i++){
		fscanf(input,"%d\n",&tam);
		matrix[i] = malloc(sizeof(int)*(tam+2));
		matrix[i][0] = tam;
		matrix[i][1] = 0;
		for(j=2;j<tam+2;j++){
			fscanf(input,"%d",&matrix[i][j]);
		}
	}
	
	for(i=0;i<n;i++){
		cont = 0;
		//PP(0,0) PM(0,1) PA(0,2)
		//HP(1,0) HM(1,1) HA(1,2)
		quicksort(matrix[i],2,(matrix[i][0])+1,0,2); 
		matrix[i][1] = cont;
	}
	
	
	fprintf(output,"%d\n",n);
	for(i=0;i<n;i++){
		fprintf(output,"%d",matrix[i][0]);
		fprintf(output," cont: %d\n",matrix[i][1]);
		for(j=2;j<matrix[i][0]+2;j++){
			if(j)fprintf(output," ");
			fprintf(output,"%d",matrix[i][j]);
		}
		if(i<n-1)fprintf(output,"\n");
	}
	fclose(input);
	fflush(output);
	fclose(output);
	
	return 0;
}
