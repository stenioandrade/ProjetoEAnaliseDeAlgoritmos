#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

typedef struct Data{
	char bytp[513][3];
}data;
typedef struct Pacote{
	unsigned int nump;
	unsigned int tamp;
	unsigned int vetor;
}pac;

int esquerda(int i){
	return 2*i+1;
}

int direita(int i){
	return 2*i+2;
}

int pai(int i){
	return (i-1)/2;
}

void troca (pac *v, int p, int i){
	pac aux = v[i];
	v[i] = v[p];
	v[p] = aux;
}

void heapsort (pac *v, int t, int i){
	unsigned int p = i;
	unsigned int e = esquerda(i);
	unsigned int d = direita(i);
		if (e < t && v[e].nump < v[p].nump) p = e;
		if (d < t && v[d].nump < v[p].nump) p = d;
		if (p != i){
			troca(v,p,i);
			heapsort(v,t,p);
		}
}

pac remover(pac *v, int *t){
	pac root = v[0];
	v[0] = v[(*t)-1];
	*t = (*t)-1;
	return root;
}

void insere(pac* heap,  int h, pac *pacote, int p){
	heap[h] = *pacote;
	if (h>0){
		int pa = pai(h);
		heapsort(heap,h+1,pa);
	}
}
int print = 0;

int main(int argc, char **argv){
	FILE* input = fopen("datagrama.input.txt","r");
	FILE* output = fopen("output.txt","w");
	
	unsigned int totp, qntp;
	int i, ctrl=0, auxi=0, auxqntp=0, auxtotp=0, napareceu=1;
	
	fscanf(input,"%d %d",&totp,&qntp);

	
	pac *pacote = malloc(sizeof(pac)*totp);
	
	auxtotp = totp;//auxtotp serve pra controlar qnts pacotes faltam ser lidos
	
	data **str = (data**)malloc(sizeof(data)*totp);
	int strctrl = 0; //é o indice da linha da minha matrix
	while(ctrl<totp){//executa ate o ultimo pacote ser impresso
		napareceu = 1;//flag de controle pra apenas aplicar o heap qnd tiver o pacote esperado
		while(napareceu){//só sai do while qnd o numero da vez chegar
			for(i=0;i<qntp;i++){//le de bloco em bloco
					if(feof(input)) break;//o ultimo bloco tem tamanho diferente do determinado
					fscanf(input,"%d %d",&pacote[i+auxqntp].nump,&pacote[i+auxqntp].tamp);//auxqntp é o tamanho do vetor de espera
					if(pacote[i+auxqntp].nump == auxi) napareceu = 0; //se aparecer o numero esperado flag pra sair do while
						pacote[i+auxqntp].vetor = strctrl;//referencia para minha matriz onde está a string dos bytes do pacote
						str[strctrl] = malloc(sizeof(data));
						fscanf(input,"%[^\n]s",str[strctrl]->bytp[0]);//lê os bytes todos de uma vez
						strctrl++;
					auxtotp--; // controle de qnts faltam ser lidos
					if(feof(input)) break;//o ultimo bloco tem tamanho diferente do determinado
				}
				auxqntp += i;//atualisa o tamanho do vetor de espera
		}
		
		if(auxqntp > 1){//só aplica o heap se houver ao menos 2 elementos
			int tn = (auxqntp-1)/2;
			for(i=tn;i>=0;i--) heapsort(pacote,auxqntp,i);
		}
		fprintf(output,"%d:",print);//começo da impressão da linha
		print++;//numero da linha impressa
		while(pacote[0].nump == auxi){//enqt a raiz for o da vez
					fprintf(output,"%s",str[pacote[0].vetor]->bytp[0]);// imprime
				pacote[0] = pacote[auxqntp-1];//coloca o ultimo na raiz
				auxqntp--;//decrementa o tamanho do vetor de espera
				heapsort(pacote,auxqntp,0); //heap na raiz pra por o elemento que foi posto na raiz em seu lugar
				auxi++;//representa o pacote da vez
				ctrl = auxi;//se ctrl for >= total, sai do maior while e encerra a execução
		}
		if (ctrl<totp) fprintf(output,"\n");//não imprime \n no fim da ultima linha
	}
	fflush(output);
	fclose(input);
	fclose(output);
		
	return 0;
}
