#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

typedef struct CADASTRADO{
	int peso;
	int pos;
	char cod[12];
	char cnpj[19];
}cadastrado;

typedef struct SELECIONADO{
	int pesosel;
	int pesocad;
	float pesodif;
	float pesoper;
	int pos;
	int flagcnpj;
	int flagpeso;
	char cod[12];
	char cnpjcad[19];
	char cnpjsel[19];
}selecionado;

int cont = 0;

void computa(selecionado *sel, int ncs){
	float dif, percent;
		if( strcmp( ((*sel).cnpjsel),((*sel).cnpjcad) ) != 0 ){
			(*sel).flagcnpj = 1;
			cont++;
		}
		if( (*sel).pesosel != (*sel).pesocad ){
			dif = abs((*sel).pesosel - (*sel).pesocad);
			(*sel).pesodif = dif;
			percent = round((dif*100)/(*sel).pesocad); //Dúvida
			(*sel).pesoper = percent;
			if(percent > 10 || percent < -10){
				(*sel).flagpeso = 1;
				if( !((*sel).flagcnpj))
					cont++;
			}
		}
	
}

void problema (cadastrado *cad, int ncc, selecionado *sel, int ncs){
	int i, j;
	for(i=0;i<ncs;i++)
		for(j=0;j<ncc;j++)
			if( ( strcmp( (sel[i].cod) , (cad[j].cod) ) ) == 0 ){
				sel[i].pos = cad[j].pos;
				sel[i].pesocad = cad[j].peso;
				strcpy(sel[i].cnpjcad, cad[j].cnpj);
				computa(&sel[i],ncs);
				break;
			}
}

int prioritario(selecionado *sel, selecionado *aux){
	
	if( ((*sel).flagcnpj == 1) && ((*aux).flagcnpj == 0) ){
		return 1;
	}
	if( ((*sel).flagcnpj == 0) && ((*aux).flagcnpj == 1) ){
		return 0;
	}
    if( ((*sel).flagcnpj == 1) && ((*aux).flagcnpj == 1) ){
		if( (*sel).pos < (*aux).pos ){
			return 1;
		}else return 0;
	}
	if( ((*sel).flagpeso == 1) && ((*aux).flagpeso == 0)){
		return 1;
	}
	if( ((*sel).flagpeso == 0) && ((*aux).flagpeso == 1)){
		return 0;
	}
	if( ((*sel).flagpeso == 1) && ((*aux).flagpeso == 1) ){
		if ( (*sel).pesoper == (*aux).pesoper ){
			if( (*sel).pos < (*aux).pos ){
				return 1;
			}else return 0;
		}else 	if( (*sel).pesoper > (*aux).pesoper ){
					return 1;
				}else return 0;
	}
	return 0;
}

void merge(selecionado *sel, selecionado *aux, int i, int m, int f) {
  int z, isel = i, iaux = m + 1;

  for (z = i; z <= f; z++) aux[z] = sel[z];

  z = i; 
  while (isel <= m && iaux <= f) {
    /* Invariante: sel[i..z] possui os valores de sel[isel..m] e sel[iaux..f] em ordem crescente. */

    if (prioritario(&aux[isel] , &aux[iaux])) sel[z++] = aux[isel++];
    else sel[z++] = aux[iaux++];
  }

  while (isel <= m) sel[z++] = aux[isel++];

  while (iaux <= f) sel[z++] = aux[iaux++];
}

void sort(selecionado *sel, selecionado *aux, int i, int f) {
  if (i >= f) return;

  int m = (i + f) / 2;

  sort(sel, aux, i, m);
  sort(sel, aux, m + 1, f);

  /* Se sel[m] <= sel[m + 1], então sel[i..f] já está ordenado. */
  if (prioritario(&sel[m] , &sel[m + 1])) return;

  merge(sel, aux, i, m, f);
}

void mergesort(selecionado *sel, int ncs) {
  selecionado *aux = malloc(sizeof(selecionado) * ncs);
  sort(sel, aux, 0, ncs - 1);
  free(aux);
}





int main(int argc, char **argv){
	
	FILE *input  = fopen("porto.input.txt","r");
	FILE *output = fopen("output.txt","w");
	
	int ncc, ncs, i;
	
	fscanf(input,"%d",&ncc);
	cadastrado *cad = malloc(sizeof(cadastrado)*ncc);
	for(i = 0; i < ncc; i++){
		fscanf(input,"%s %s %d",cad[i].cod,cad[i].cnpj,&cad[i].peso);
		cad[i].pos = i;
	}
	
	fscanf(input,"%d",&ncs);
	selecionado *sel = malloc(sizeof(selecionado)*ncs);
	for(i = 0; i < ncs; i++){
		fscanf(input,"%s %s %d",sel[i].cod,sel[i].cnpjsel,&sel[i].pesosel);
		sel[i].flagcnpj = 0;
		sel[i].flagpeso = 0;
		sel[i].pesodif = 0;
		sel[i].pesoper = 0;
		sel[i].pesocad = 0;
		sel[i].cnpjcad[0] = '\0';
	}
	
	problema(cad,ncc,sel,ncs);
	
	mergesort(sel,ncs);
	
	for(i=0;i<cont;i++){
		if(sel[i].flagcnpj)
			fprintf(output,"%s: %s<->%s\n",sel[i].cod,sel[i].cnpjcad,sel[i].cnpjsel);
		else
			fprintf(output,"%s: %.fkg (%.f%%)\n",sel[i].cod,sel[i].pesodif,sel[i].pesoper);
	}
	
	
	fclose(input);
	fclose(output);
	return 0;
	
}
