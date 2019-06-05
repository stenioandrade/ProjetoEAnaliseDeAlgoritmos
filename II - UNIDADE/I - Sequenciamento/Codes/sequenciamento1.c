#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Doencas{
	char codigo[9];
	int ngenes;
}doencas;

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
	
	for(i=0;i<ndoencas;i++){
		for(j=0;j<doenca[i].ngenes;j++)
			printf("%s ",gene[i][j]);
		printf("\n");
		}
	
	return 0;
}
