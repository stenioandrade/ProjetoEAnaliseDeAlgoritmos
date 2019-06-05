#include <stdio.h>
#include <stdlib.h>

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

int particionar(int *V, int inicio, int fim) {
	int pivo = V[fim];
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

void quicksort(int *V, int inicio, int fim) {
	cont++;
	if(inicio < fim) {
		int pivo = particionar(V, inicio, fim);
		quicksort(V, inicio, pivo - 1);
		quicksort(V, pivo + 1, fim);
	}
}

int main(int argc, char **argv)
{
	FILE* input = fopen("quicksort.in.txt","r");
	FILE* output = fopen("output.txt","w");
	
	int n,i,j,tam;
	
	vetor **matrix = malloc(sizeof(vetor)*n);
	fscanf(input,"%d\n",&n);
	for(i=0;i<n;i++){
		matrix[i] = malloc(sizeof(vetor));
		matrix[i]->cont = 0;
		fscanf(input,"%d\n",&tam);
		matrix[i]->vet = malloc(sizeof(vetor)*tam);
		matrix[i]->tam = tam;
		for(j=0;j<tam;j++){
			fscanf(input,"%d",&matrix[i]->vet[j]);
		}
	}
	
	
	for(i=0;i<n;i++){
		cont = 0;
		
		
		quicksort(matrix[i]->vet,0,(matrix[i]->tam)-1);
		matrix[i]->cont = cont;
	}
	printf("%d\n",cont);
	
	
	fprintf(output,"%d\n",n);
	for(i=0;i<n;i++){
		fprintf(output,"%d\n",matrix[i]->tam);
		fprintf(output," cont: %d\n",matrix[i]->cont);
		for(j=0;j<matrix[i]->tam;j++){
			if(j)fprintf(output," ");
			fprintf(output,"%d",matrix[i]->vet[j]);
		}
		if(i<n-1)fprintf(output,"\n");
	}
	fclose(input);
	fflush(output);
	fclose(output);
	
	return 0;
}
