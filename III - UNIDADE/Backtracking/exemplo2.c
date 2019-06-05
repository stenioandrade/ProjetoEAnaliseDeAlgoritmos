#include <stdio.h>
#include <math.h> 
#include <string.h>
char input[] = "labirinto.input.txt";
char output[] = "output.txt" ;

struct Migalha {
   int X;
   int Y;
   char D;
   char F;
   char E;
   char T;
}; 

int main(int argc, char **argv)
{
	// Declaracao de variaveis
	FILE *entrada, *saida;
	int numeroLabirintos, contLab;
	
	// PRINT Argumentos
	//printf("-------------------------- Labirinto -------------------------------------------\n");
	//printf("N DE ARGUMENTOS: %i\n",(argc-1));
	//printf("ENTRADA: %s\n",argv[1]);
	//printf("SAIDA: %s\n",argv[2]);	
	
	// Arquivo de entrada
	entrada = fopen(input, "r");
	
	// Arquivo de saida
	saida = fopen(output, "w");
	
	// Le irformacao base	
	fscanf(entrada, "%i", &numeroLabirintos);
	//printf("NUMERO DE LABIRINTOS: %i\n", numeroLabirintos );
	//printf("--------------------------------------------------------------------------------\n\n");
	
	// Executa para cada labirinto
	for(contLab = 0; contLab < numeroLabirintos; contLab++){
		
		int largura, altura;
		
		//Info do labirinto
		//printf("#LAB----------------------------------------------------------------------------\n");
		
			//Labirinto X
		//printf("LABIRINTO: %i\n", contLab);
		fprintf(saida, "L%i:\n",contLab);
		
			//Largura
		fscanf(entrada, "%i", &largura);
		//printf("LARGURA: %i\n", largura);
		
			//Altura
		fscanf(entrada, "%i", &altura);
		//printf("ALTURA: %i\n\n", altura );		
		
		// Cria matriz
		char labirinto[altura][largura];
		
		// Ponto de partida e saida
		int start[2];
		int end[2] = {-1,-1};
		
		// Contadores de largura e altura para
		int contLargura, contAltura;
		
		// Le arquivo para preencher a matriz
		for(contAltura = 0; contAltura < altura; contAltura++){
			for(contLargura = 0; contLargura < largura; contLargura++){
				
				fscanf(entrada, " %c", &labirinto[contAltura][contLargura]);
				//printf("%c  ", labirinto[contAltura][contLargura] );
				
				if (labirinto[contAltura][contLargura] == 'X'){
					start[0] = contAltura;
					start[1] = contLargura;
				}
			
			}		
			//printf("\n");	
		}
		//printf("\n");
		
		// Imprime Inicio na saida
		fprintf(saida, "INICIO [%i,%i]\n",start[0],start[1]);
		
		// Variaveis de execução v[altura][largura]
		int tCaminho = (altura-2)*(largura-2)+1;
		int	marcadorRobo[2] = {start[0],start[1]};
		int	marcadorCaminho = 0;
		int	anterior[2] = {start[0],start[1]};
		struct Migalha caminho[tCaminho];
		//printf("tCAMINHO: %i\n\n",tCaminho);
		
		while (end[0] == -1){
			
			// Movimentos
			int D[2] = {marcadorRobo[0],marcadorRobo[1]+1};
			int	F[2] = {marcadorRobo[0]-1,marcadorRobo[1]};
			int	E[2] = {marcadorRobo[0],marcadorRobo[1]-1};
			int	T[2] = {marcadorRobo[0]+1,marcadorRobo[1]};
			
			// Imprime Movimentos
			//printf("UlTIMO MOVIMENTO[%i,%i] marcadorRobo[%i,%i] D[%i,%i] F[%i,%i] E[%i,%i] T[%i,%i]\n\n",caminho[marcadorCaminho].X, caminho[marcadorCaminho].Y,marcadorRobo[0],marcadorRobo[1],D[0],D[1],F[0],F[1],E[0],E[1],T[0],T[1]);
		

			
			if (0 <= D[0] && D[0] < altura && 0 <= D[1] && D[1] < largura && labirinto[D[0]][D[1]]== '0' && (anterior[0] != D[0] || anterior[1] != D[1]) ){
				
				// Grava pos 
				caminho[marcadorCaminho].X = marcadorRobo[0];
				caminho[marcadorCaminho].Y = marcadorRobo[1];
				
				//Bloqueia caminho em caso de BT
				caminho[marcadorCaminho].D = 'L';
				
				//Incrementa marcador
				marcadorCaminho++;
				
				// Imprime movimento na saida
				fprintf(saida, "D [%i,%i]->[%i,%i]\n",marcadorRobo[0],marcadorRobo[1],D[0],D[1]);
				//printf("D [%i,%i]->[%i,%i]\n",marcadorRobo[0],marcadorRobo[1],D[0],D[1]);
				
				// Atualiza anterior
				anterior[0] = marcadorRobo[0];
				anterior[1] = marcadorRobo[1];
				
				// Move robo
				labirinto[marcadorRobo[0]][marcadorRobo[1]] = '1';
				marcadorRobo[0] = D[0];
				marcadorRobo[1] = D[1];
				
			}
			else if (0 <= F[0] && F[0] < altura && 0 <= F[1] && F[1] < largura && labirinto[F[0]][F[1]]== '0' && (anterior[0] != F[0] || anterior[1] != F[1]) ){
				
				// Grava pos 
				caminho[marcadorCaminho].X = marcadorRobo[0];
				caminho[marcadorCaminho].Y = marcadorRobo[1];
				
				//Bloqueia caminho em caso de BT
				caminho[marcadorCaminho].D = 'L';
				caminho[marcadorCaminho].F = 'L';
				
				//Incrementa marcador
				marcadorCaminho++;
				
				// Imprime movimento na saida
				fprintf(saida, "F [%i,%i]->[%i,%i]\n",marcadorRobo[0],marcadorRobo[1],F[0],F[1]);
				//printf("F [%i,%i]->[%i,%i]\n",marcadorRobo[0],marcadorRobo[1],F[0],F[1]);
				
				// Atualiza anterior
				anterior[0] = marcadorRobo[0];
				anterior[1] = marcadorRobo[1];
				
				// Move robo
				labirinto[marcadorRobo[0]][marcadorRobo[1]] = '1';
				marcadorRobo[0] = F[0];
				marcadorRobo[1] = F[1];
			}
			else if (0 <= E[0] && E[0] < altura && 0 <= E[1] && E[1] < largura && labirinto[E[0]][E[1]]== '0' && (anterior[0] != E[0] || anterior[1] != E[1]) ){
				
				// Grava pos 
				caminho[marcadorCaminho].X = marcadorRobo[0];
				caminho[marcadorCaminho].Y = marcadorRobo[1];
				
				//Bloqueia caminho em caso de BT
				caminho[marcadorCaminho].D = 'L';
				caminho[marcadorCaminho].F = 'L';
				caminho[marcadorCaminho].E = 'L';
				
				//Incrementa marcador
				marcadorCaminho++;
				
				// Imprime movimento na saida
				fprintf(saida, "E [%i,%i]->[%i,%i]\n",marcadorRobo[0],marcadorRobo[1],E[0],E[1]);
				//printf("E [%i,%i]->[%i,%i]\n",marcadorRobo[0],marcadorRobo[1],E[0],E[1]);
				
				// Atualiza anterior
				anterior[0] = marcadorRobo[0];
				anterior[1] = marcadorRobo[1];
				
				// Move robo
				labirinto[marcadorRobo[0]][marcadorRobo[1]] = '1';
				marcadorRobo[0] = E[0];
				marcadorRobo[1] = E[1];
			}
			else if (0 <= T[0] && T[0] < altura && 0 <= T[1] && T[1] < largura && labirinto[T[0]][T[1]]== '0' && (anterior[0] != T[0] || anterior[1] != T[1]) ){
				
				// Grava pos 
				caminho[marcadorCaminho].X = marcadorRobo[0];
				caminho[marcadorCaminho].Y = marcadorRobo[1];
				
				//Bloqueia caminho em caso de BT
				caminho[marcadorCaminho].D = 'L';
				caminho[marcadorCaminho].F = 'L';
				caminho[marcadorCaminho].E = 'L';
				caminho[marcadorCaminho].T = 'L';
				
				//Incrementa marcador
				marcadorCaminho++;
				
				// Imprime movimento na saida
				fprintf(saida, "T [%i,%i]->[%i,%i]\n",marcadorRobo[0],marcadorRobo[1],T[0],T[1]);
				//printf("T [%i,%i]->[%i,%i]\n",marcadorRobo[0],marcadorRobo[1],T[0],T[1]);
				
				// Atualiza anterior
				anterior[0] = marcadorRobo[0];
				anterior[1] = marcadorRobo[1];
				
				// Move robo
				labirinto[marcadorRobo[0]][marcadorRobo[1]] = '1';
				marcadorRobo[0] = T[0];
				marcadorRobo[1] = T[1];
				
			}
// # DAQUI PRA CIMA TUDO OK DAQUI PRA CIMA TUDO OK DAQUI PRA CIMA TUDO OK
			else{
				
				// Imprime BT
				if(marcadorRobo[0] == start[0] && marcadorRobo[1] == start[1]){
					break;
				} else{
					fprintf(saida, "BT [%i,%i]<-[%i,%i]\n",anterior[0],anterior[1], marcadorRobo[0],marcadorRobo[1]);
					//printf("BT [%i,%i]<-[%i,%i]\n",anterior[0],anterior[1], marcadorRobo[0],marcadorRobo[1]);
				}
				
				
				labirinto[marcadorRobo[0]][marcadorRobo[1]] = '1';
				//Limpa migalha
				caminho[marcadorCaminho].D = 'Z';
				caminho[marcadorCaminho].F = 'Z';
				caminho[marcadorCaminho].E = 'Z';
				caminho[marcadorCaminho].T = 'Z';
				
				
								
				// Volta robo pra casa anterior
				labirinto[marcadorRobo[0]][marcadorRobo[1]] = '1';
				marcadorRobo[0] = anterior[0];
				marcadorRobo[1] = anterior[1];
				
				
				marcadorCaminho--;
				
				// Atualiza anterior
				anterior[0] = caminho[marcadorCaminho-1].X ;
				anterior[1] = caminho[marcadorCaminho-1].Y;
				
			}
// # DAQUI PRA BAIXO TUDO OK
			// Verifica se o robo chegou na saida
			if((marcadorRobo[0] == 0 || marcadorRobo[0]== altura-1) || (marcadorRobo[1] == 0 || marcadorRobo[1]== largura-1)){				
				end[0] = marcadorRobo[0];
				end[1] = marcadorRobo[1];
			}
				
		}
		

		
		// Imprime resposta do labirinto
		if (end[0] == -1 || end[1] == -1){
			// Imprime SAIDA na saida
			fprintf(saida, "SEM SAIDA\n");
		} else {
			// Imprime SAIDA na saida
			fprintf(saida, "SAIDA [%i,%i]\n",end[0],end[1]);
		}
		
		
		//printf("--------------------------------------------------------------------------------\n\n");
	}
	
	
	// Fecha Arquivos
	fclose(entrada);
	fclose(saida);
	
	return 0;
}
