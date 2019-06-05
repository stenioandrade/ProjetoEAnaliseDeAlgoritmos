#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node{
	char codigo[17];
	int aposta[15];
	int acerto;
}node;

int esquerda(int i){
	return 2*i+1;
}

int direita(int i){
	return 2*i+2;
}

void troca (node *v, int p, int i){
	node aux = v[i];
	v[i] = v[p];
	v[p] = aux;
}

void heap_max (node *v, int t, int i){
	unsigned int p = i;
	unsigned int e = esquerda(i);
	unsigned int d = direita(i);
		if (e < t && v[e].acerto > v[p].acerto) p = e;
		if (d < t && v[d].acerto > v[p].acerto) p = d;
		if (p != i){
			troca(v,p,i);
			heap_max(v,t,p);
		}
}

void heap_min (node *v, int t, int i){
	unsigned int p = i;
	unsigned int e = esquerda(i);
	unsigned int d = direita(i);
		if (e < t && v[e].acerto < v[p].acerto) p = e;
		if (d < t && v[d].acerto < v[p].acerto) p = d;
		if (p != i){
			troca(v,p,i);
			heap_min(v,t,p);
		}
}


node remover(node *v, int *t){
	node root = v[0];
	v[0] = v[(*t)-1];
	*t = (*t)-1;
	return root;
}

int main(int argc, char* argv[]){
	FILE* input = fopen(argv[1],"r");
	FILE* output = fopen(argv[2],"w");
	int premio,napostas,sorteado[10],i,j,h;
	char str[17]={0};
	fscanf(input,"%d %d",&premio,&napostas);
	int tn = (napostas-1)/2;
	for (i=0;i<10;i++){
		fscanf(input,"%d",&sorteado[i]);
	}
	node *vheapmax = (node*)malloc(napostas*sizeof(node));
	node *vheapmin = (node*)malloc(napostas*sizeof(node));
	node *vmax = (node*)malloc(napostas*sizeof(node));
	node *vmin = (node*)malloc(napostas*sizeof(node));
		for(i=0;i<napostas;i++){
			fscanf(input,"%s\n",str);
			strcpy(vheapmax[i].codigo,str);
			strcpy(vheapmin[i].codigo,str);
			vheapmax[i].acerto = 0;
			vheapmin[i].acerto = 0;
			for(j=0;j<15;j++){
				fscanf(input,"%d",&vheapmax[i].aposta[j]);
				vheapmin[i].aposta[j] = vheapmax[i].aposta[j];
					for(h=0;h<10;h++){
						if(sorteado[h] == vheapmax[i].aposta[j]){
							vheapmax[i].acerto++;
							vheapmin[i].acerto++;
							break;
						}
					}
			}
		}	
		
		
//	heap_max
	for(i=tn;i>=0;i--) heap_max(vheapmax,napostas,i);
	i = 0;
	node temp;
	node referencia_acerto = vheapmax[0];
	while(1){
		temp = remover(vheapmax,&napostas);
		heap_max(vheapmax,napostas,0);
		if(referencia_acerto.acerto != temp.acerto){
			break;
		}
		else {
		vmax[i] = temp;
		i++;
		}
	}
//	imprime_max	
	int pmax = (premio/2)/i;
	if(vmax[0].acerto > 1) fprintf(output,"Faixa: %d acertos\n",vmax[0].acerto);
	else fprintf(output,"Faixa: %d acerto\n",vmax[0].acerto);
	for(j=0;j<i;j++) fprintf(output,"%s\n",vmax[j].codigo);
	if(i > 1) fprintf(output,"%d ganhadores de R$%d\n\n",i,pmax);
	else fprintf(output,"1 ganhador de R$%d\n\n",pmax);
	
//	heap_min
	for(i=tn;i>=0;i--) heap_min(vheapmin,napostas,i);
	i = 0;
	node temp2;
	node referencia_acerto2 = vheapmin[0];
	while(1){
		temp2 = remover(vheapmin,&napostas);
		heap_min(vheapmin,napostas,0);
		if(referencia_acerto2.acerto != temp2.acerto){
			break;
		}
		else {
		vmin[i] = temp2;
		i++;
		}
	}
//	imprime_min	
	int pmin = (premio/2)/i;
	if(vmin[0].acerto > 1) fprintf(output,"Faixa: %d acertos\n",vmin[0].acerto);
	else fprintf(output,"Faixa: %d acerto\n",vmin[0].acerto);
	for(j=0;j<i;j++) fprintf(output,"%s\n",vmin[j].codigo);
	if(i > 1) fprintf(output,"%d ganhadores de R$%d",i,pmin);
	else fprintf(output,"1 ganhador de R$%d",pmin);
	
	
	
	return 0;
}
