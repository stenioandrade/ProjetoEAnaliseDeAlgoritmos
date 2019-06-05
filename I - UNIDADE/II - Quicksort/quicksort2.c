#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct VETOR{
	int tam;
	int cont;
	int *vet;
}vetor;

typedef struct SAIDA{
	int tipo;
	int total;
}saida;

int cont1 = 0;

void bubblesort (saida v[], int n) {
    int k, j;
    saida aux;
    for (k = 1; k < n; k++) {
        for (j = 0; j < n - 1; j++) {
            if (v[j].total > v[j + 1].total) {
                aux = v[j];
                v[j] = v[j + 1];
                v[j + 1] = aux;
            }
        }
    }
}

void trocar (int *v1, int *v2){
	cont1++;
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
	cont1++;
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
	FILE* input = fopen("quicksort.input.txt","r");
	FILE* output = fopen("output.txt","w");
	
	int n,i,j,tam,x;
	
	//tipo 1 de leitura (completa)
	fscanf(input,"%d\n",&n);
	//vetor **matrix = malloc(sizeof(vetor)*n);
	vetor **pp = malloc(sizeof(vetor)*n);
	vetor **pm = malloc(sizeof(vetor)*n);
	vetor **pa = malloc(sizeof(vetor)*n);
	vetor **hp = malloc(sizeof(vetor)*n);
	vetor **hm = malloc(sizeof(vetor)*n);
	vetor **ha = malloc(sizeof(vetor)*n);
	for(i=0;i<n;i++){
		//matrix[i] = (vetor*)malloc(sizeof(vetor));
		pp[i] = (vetor*)malloc(sizeof(vetor));
		pm[i] = (vetor*)malloc(sizeof(vetor));
		pa[i] = (vetor*)malloc(sizeof(vetor));
		hp[i] = (vetor*)malloc(sizeof(vetor));
		hm[i] = (vetor*)malloc(sizeof(vetor));
		ha[i] = (vetor*)malloc(sizeof(vetor));
		fscanf(input,"%d\n",&tam);
		//matrix[i]->vet = malloc(sizeof(vetor)*tam);
		pp[i]->vet = malloc(sizeof(vetor)*tam);
		pm[i]->vet = malloc(sizeof(vetor)*tam);
		pa[i]->vet = malloc(sizeof(vetor)*tam);
		hp[i]->vet = malloc(sizeof(vetor)*tam);
		hm[i]->vet = malloc(sizeof(vetor)*tam);
		ha[i]->vet = malloc(sizeof(vetor)*tam);
		//matrix[i]->tam = tam;
		//matrix[i]->cont = 0;
		pp[i]->tam = tam;
		pp[i]->cont = 0;
		pm[i]->tam = tam;
		pm[i]->cont = 0;
		pa[i]->tam = tam;
		pa[i]->cont = 0;
		hp[i]->tam = tam;
		hp[i]->cont = 0;
		hm[i]->tam = tam;
		hm[i]->cont = 0;
		ha[i]->tam = tam;
		ha[i]->cont = 0;
		for(j=0;j<tam;j++){
			//fscanf(input,"%d",&matrix[i]->vet[j]);
			fscanf(input,"%d",&x);
			pp[i]->vet[j] = x;
			pm[i]->vet[j] = x;
			pa[i]->vet[j] = x;
			hp[i]->vet[j] = x;
			hm[i]->vet[j] = x;
			ha[i]->vet[j] = x;
		}
	}
	
	saida *s = malloc(sizeof(saida)*6);
		
	for(i=0;i<n;i++){
		//PP(0,0) PM(0,1) PA(0,2)
		//HP(1,0) HM(1,1) HA(1,2)
		cont1 = 0;
		quicksort(pp[i]->vet,0,(pp[i]->tam)-1,0,0); 
		pp[i]->cont = cont1;
		s[0].tipo = 0;
		s[0].total = cont1;
		cont1 = 0;
		quicksort(pm[i]->vet,0,(pm[i]->tam)-1,0,1); 
		pm[i]->cont = cont1;
		s[1].tipo = 1;
		s[1].total = cont1;
		cont1 = 0;
		quicksort(pa[i]->vet,0,(pa[i]->tam)-1,0,2); 
		pa[i]->cont = cont1;
		s[2].tipo = 2;
		s[2].total = cont1;
		cont1 = 0;
		quicksort(hp[i]->vet,0,(hp[i]->tam)-1,1,0); 
		hp[i]->cont = cont1;
		s[3].tipo = 3;
		s[3].total = cont1;
		cont1 = 0;
		quicksort(hm[i]->vet,0,(hm[i]->tam)-1,1,1); 
		hm[i]->cont = cont1;
		s[4].tipo = 4;
		s[4].total = cont1;
		cont1 = 0;
		quicksort(ha[i]->vet,0,(ha[i]->tam)-1,1,2); 
		ha[i]->cont = cont1;
		s[5].tipo = 5;
		s[5].total = cont1;
		bubblesort(s,6);
		fprintf(output,"%d: N(%d)",i,pp[i]->tam);
		for(j=0;j<6;j++){
			if(s[j].tipo == 0) fprintf(output," PP(%d)",s[j].total);
			if(s[j].tipo == 1) fprintf(output," PM(%d)",s[j].total);
			if(s[j].tipo == 2) fprintf(output," PA(%d)",s[j].total);
			if(s[j].tipo == 3) fprintf(output," HP(%d)",s[j].total);
			if(s[j].tipo == 4) fprintf(output," HM(%d)",s[j].total);
			if(s[j].tipo == 5) fprintf(output," HA(%d)",s[j].total);
		}
		fprintf(output,"\n");
	}
	
	/*
	fprintf(output,"%d\n",n);
	for(i=0;i<n;i++){
		fprintf(output,"%d",matrix[i]->tam);
		fprintf(output," cont: %d\n",matrix[i]->cont);
		for(j=0;j<matrix[i]->tam;j++){
			if(j)fprintf(output," ");
			fprintf(output,"%d",matrix[i]->vet[j]);
		}
		if(i<n-1)fprintf(output,"\n");
	}*/
	fclose(input);
	fflush(output);
	fclose(output);
	
	return 0;
}
