#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

typedef struct Pacote{
	unsigned int nump;
	unsigned int tamp;
	unsigned int bytp[512];
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
void imprime(FILE *output, pac *p, int start, int stop){
	//puts("#");
	int i,j;
	fprintf(output,"%d:",print);
	//printf("%d:",print);
	print++;
	for(j=start;j<=stop;j++){
		for(i=0;i<p[j].tamp;i++)
			fprintf(output," %02X",p[j].bytp[i]);
			//printf(" %02X",p[j].bytp[i]);
	}
}

int main(int argc, char **argv){
	FILE* input = fopen("datagrama.input.txt","r");
	FILE* output = fopen("output.txt","w");
	
	unsigned int totp, qntp;
	int i, j, ctrl=0, auxi=0, auxqntp=0, auxprint=0, auxtotp=0, flag=0;
	
	fscanf(input,"%d %d",&totp,&qntp);
	
	pac *pacote = malloc(sizeof(pac)*totp);
	pac *aux = malloc(sizeof(pac)*totp);
	auxtotp = totp;
	//leitura dos pacotes
	while(ctrl<totp){
		//printf("while 1\n");
				//printf("%d\n",x++);
			
		for(i=0;i<qntp;i++){
				if(feof(input)) break;
				//printf("%d\n",x++);
				fscanf(input,"%d %d",&pacote[i+auxqntp].nump,&pacote[i+auxqntp].tamp);
				for(j=0;j<pacote[i+auxqntp].tamp;j++) fscanf(input," %X",&pacote[i+auxqntp].bytp[j]);
				auxtotp--;
				printf("%d %d %d\n",i,qntp,pacote[i+auxqntp].nump);
				if(feof(input)) break;
			}
			auxqntp += i;	
				
		
		if(auxqntp > 1){	
			int tn = (auxqntp-1)/2;
		//printf("heap in %d\n",pacote[0].nump);
			for(i=tn;i>=0;i--) heapsort(pacote,auxqntp,i);
		//printf("heap out\n");
		}
		while(auxqntp > 0){
		//printf("while 2 %d %d %d\n",pacote[0].nump,auxi,auxqntp);
			if(pacote[0].nump == auxi){
		//printf("if auxi\n");
				aux[auxi] = remover(pacote,&auxqntp);
				//printf("%d %d %d\n",aux[auxi].nump,auxi,auxqntp);
				heapsort(pacote,auxqntp,0);
				auxi++;
				ctrl = auxi;
				flag = 1;
			}else{
		//printf("break\n");
				break;
			}
		}
		//printf("while 2 out\n");
		if(flag){
		//printf("flag\n");
			fprintf(output,"%d:",print);
			print++;
			for(j=auxprint;j<=auxi-1;j++){
				for(i=0;i<aux[j].tamp;i++)
					fprintf(output," %02X",aux[j].bytp[i]);
			}
			//imprime(output,aux,auxprint,auxi-1);
			if (ctrl<totp) fprintf(output,"\n");
			auxprint = auxi;
			flag = 0;
		}
	}
	//printf("%d",print);
	fflush(output);
	fclose(input);
	fclose(output);
		
	return 0;
}
