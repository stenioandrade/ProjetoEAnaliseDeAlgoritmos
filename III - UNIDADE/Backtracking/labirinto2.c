#include <stdio.h>
#include <stdlib.h>

char Arq_in[] = "labirinto.input.txt";
char Arq_out[] = "myoutput.txt";

typedef struct Robot{
	int x;
	int y;
	int lastx;
	int lasty;
	int firstx;
	int firsty;
	int saidax;
	int saiday;
	int step;
	int D[2];
	int F[2];
	int E[2];
	int T[2];
}robot;

typedef struct Path{
	int x;
	int y;
}Path;

void D(int x,int y, int *pos){
	pos[0] = x;
	pos[1] = y+1;
}

void F(int x,int y, int *pos){
	pos[0] = x-1;
	pos[1] = y;
}

void E(int x,int y, int *pos){
	pos[0] = x;
	pos[1] = y-1;
}

void T(int x,int y, int *pos){
	pos[0] = x+1;
	pos[1] = y;
}

void LookArround(robot *rob){
	D(rob->x,rob->y,rob->D);
	F(rob->x,rob->y,rob->F);
	E(rob->x,rob->y,rob->E);
	T(rob->x,rob->y,rob->T);
}

void direita(FILE* output, Path *path, robot *rob){
	path[rob->step].x = rob->x;
	path[rob->step].y = rob->y;
	rob->step++;
	fprintf(output, "D [%d,%d]->[%d,%d]\n",rob->x,rob->y,rob->D[0],rob->D[1]);
	rob->lastx = rob->x;
	rob->lasty = rob->y;
	rob->x = rob->D[0];
	rob->y = rob->D[1];
}

void frente(FILE* output, Path *path, robot *rob){
	path[rob->step].x = rob->x;
	path[rob->step].y = rob->y;
	rob->step++;
	fprintf(output, "F [%d,%d]->[%d,%d]\n",rob->x,rob->y,rob->F[0],rob->F[1]);
	rob->lastx = rob->x;
	rob->lasty = rob->y;
	rob->x = rob->F[0];
	rob->y = rob->F[1];
}

void esquerda(FILE* output, Path *path, robot *rob){
	path[rob->step].x = rob->x;
	path[rob->step].y = rob->y;
	rob->step++;
	fprintf(output, "E [%d,%d]->[%d,%d]\n",rob->x,rob->y,rob->E[0],rob->E[1]);
	rob->lastx = rob->x;
	rob->lasty = rob->y;
	rob->x = rob->E[0];
	rob->y = rob->E[1];
}

void tras(FILE* output, Path *path, robot *rob){
	path[rob->step].x = rob->x;
	path[rob->step].y = rob->y;
	rob->step++;
	fprintf(output, "T [%d,%d]->[%d,%d]\n",rob->x,rob->y,rob->T[0],rob->T[1]);
	rob->lastx = rob->x;
	rob->lasty = rob->y;
	rob->x = rob->T[0];
	rob->y = rob->T[1];
}

void BT(Path *path, robot *rob){
	rob->x = rob->lastx;
	rob->y = rob->lasty;
	rob->step--;
	rob->lastx = path[rob->step-1].x;
	rob->lasty = path[rob->step-1].y;
}

void Processa_lab(FILE* input, FILE* output){
	int ilargura,ialtura,largura, altura;
	char ch;
	robot rob;
	rob.saidax = -1;
	rob.saiday = -1;
	fscanf(input," %d %d",&largura,&altura);
	int labirinto[altura][largura];
	for(ialtura=0;ialtura<altura;ialtura++){	
		for(ilargura=0;ilargura<largura;ilargura++){
			fscanf(input," %c",&ch);
			labirinto[ialtura][ilargura] = ch;
			if(ch == 'X'){
				rob.firstx = ialtura;
				rob.firsty = ilargura;
			}
		}
	}
	Path path[altura*largura];
	rob.x = rob.firstx;
	rob.y = rob.firsty;
	rob.lastx = rob.firstx;
	rob.lasty = rob.firsty;
	rob.step = 0;
	fprintf(output,"INICIO [%d,%d]\n",rob.firstx,rob.firsty);
	int nfim = 1;
	while(nfim){
		LookArround(&rob);
		if (0 <= rob.D[0] && rob.D[0] < altura &&
			0 <= rob.D[1] && rob.D[1] < largura &&
			labirinto[rob.D[0]][rob.D[1]]== '0' &&
			(rob.lastx != rob.D[0] || rob.lasty != rob.D[1]) ){
			labirinto[rob.x][rob.y] = '1';
			direita(output,path,&rob);
		}else if (0 <= rob.F[0] && rob.F[0] < altura &&
			0 <= rob.F[1] && rob.F[1] < largura &&
			labirinto[rob.F[0]][rob.F[1]]== '0' &&
			(rob.lastx != rob.F[0] || rob.lasty != rob.F[1]) ){
			labirinto[rob.x][rob.y] = '1';
			frente(output,path,&rob);
		}else if (0 <= rob.E[0] && rob.E[0] < altura &&
			0 <= rob.E[1] && rob.E[1] < largura &&
			labirinto[rob.E[0]][rob.E[1]]== '0' &&
			(rob.lastx != rob.E[0] || rob.lasty != rob.E[1]) ){
			labirinto[rob.x][rob.y] = '1';
			esquerda(output,path,&rob);
		}else if (0 <= rob.T[0] && rob.T[0] < altura &&
			0 <= rob.T[1] && rob.T[1] < largura &&
			labirinto[rob.T[0]][rob.T[1]]== '0' &&
			(rob.lastx != rob.T[0] || rob.lasty != rob.T[1]) ){
			labirinto[rob.x][rob.y] = '1';
			tras(output,path,&rob);
		}else{
			if(rob.x == rob.firstx && rob.y == rob.firsty){
				break;
			}else
				fprintf(output,"BT [%d,%d]<-[%d,%d]\n",rob.lastx,rob.lasty, rob.x,rob.y);
			labirinto[rob.x][rob.y] = '1';
			BT(path,&rob);
		}
		if((rob.x == 0 || rob.x == altura-1) || (rob.y == 0 || rob.y == largura-1)){				
			rob.saidax = rob.x;
			rob.saiday = rob.y;
			nfim = 0;
		}
	}
	if (rob.saidax == -1 && rob.saiday == -1)
		fprintf(output,"SEM SAIDA\n");
	else
		fprintf(output,"SAIDA [%d,%d]\n",rob.saidax,rob.saiday);
}

int main(int argc, char **argv){
	FILE* input = fopen(Arq_in,"r");
	FILE* output = fopen(Arq_out,"w");
	int nlab, index;
	fscanf(input,"%d",&nlab);
	for(index=0;index<nlab;index++){
		fprintf(output,"L%d:\n",index);
		Processa_lab(input,output);
	}
	fclose(input);
	fclose(output);
	return 0;
}
