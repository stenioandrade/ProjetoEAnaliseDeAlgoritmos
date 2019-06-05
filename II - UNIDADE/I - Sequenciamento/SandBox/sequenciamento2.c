#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Doencas{
	char codigo[9];
	int ngenes;
}doencas;

void calcular_tabela(int tab[], char P[]) {
	unsigned int i, m = strlen(P);
	int j = -1;
	inicializar(tab, m);
	for(i = 1; i < m; i++) {
		while(j >= 0 && P[j + 1] != P[i])
			j = tab[j];
		if(P[j + 1] == P[i])
		j++;
		tab[i] = j;
	}
}

void busca_kmp(int pos[], int tab[], char T[], char P[]) {
	unsigned int i, n = strlen(T);
	unsigned int m = strlen(P);
	int j = -1;
	calcular_tabela(tab, P);
	for(i = 0; i < n; i++) {
		while(j >= 0 && P[j + 1] != T[i])
			j = tab[j];
		if(P[j + 1] == T[i]) j++;
		if(j == m - 1) {
			inserir(pos, i - m + 1);
			j = tab[j];
		}
	}
}

int main(int argc , char **argv){
	FILE* input = fopen("sequenciamento.in.txt","r");
	FILE* output = fopen("output.txt","w");
	int subcadeia, ndoencas;
	int i,j;
	char ch;
	size_t tellin,tellout;// %lu long unsigned int
	
	fscanf(input,"%d",&subcadeia);
	
	fscanf(input,"%c",&ch);
	if(ch == '\n') fscanf(input,"%c",&ch);
	tellin = ftell(input) - 1;
	while(ch != '\n') ch = fgetc(input);
	tellout = ftell(input) - 1;
	
	char* DNA = (char*)malloc(sizeof(char)*(tellout-tellin));
	fseek(input,tellin,0);
	fscanf(input,"%s",DNA);
	printf("[%s]",DNA);
		
	fscanf(input," %d",&ndoencas);
	doencas *doenca = (doencas*)malloc(sizeof(doencas)*ndoencas);
	char ***gene = (char***)malloc(sizeof(char**)*ndoencas);
	for(i=0;i<ndoencas;i++){
		fscanf(input," %s",doenca[i].codigo);
		fscanf(input," %d",&doenca[i].ngenes);
		gene[i] = (char**)malloc(sizeof(char*)*doenca[i].ngenes);
		for(j=0;j<doenca[i].ngenes;j++){
			gene[i][j] = (char*)malloc(sizeof(char));
			fscanf(input," %s",gene[i][j]);
		}
	}
	
	
	
	//~ for(i=0;i<ndoencas;i++){
		//~ for(j=0;j<doenca[i].ngenes;j++)
			//~ printf("%s ",gene[i][j]);
		//~ printf("\n");
	//~ }
	
	return 0;
}
