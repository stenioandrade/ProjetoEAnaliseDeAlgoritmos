#include <stdio.h>
int main(){
	FILE* input1 = fopen("output.txt","r");
	FILE* input2 = fopen("datagrama.output.txt","r");
	char ch1 = fgetc(input1);
	char ch2 = fgetc(input2);
	float cont=0, total=0;
		while (ch1 != EOF && ch2 != EOF) {
			total++;
			while(ch1 == ':' || ch1 == '[' || ch1 == ']' || ch1 == ' ' || ch1 == '\n' ){
				ch1 = fgetc(input1);
			}
			while(ch2 == ':' || ch2 == '[' || ch2 == ']' || ch2 == ' ' || ch2 == '\n' ){
				ch2 = fgetc(input2);
			}
			if( ch1 != ch2 ){
				cont++;
				printf("Divergencia (%.f) %c != %c\n",cont, ch1, ch2);
			}//else printf("IGUALDADE       %c != %c\n",ch1, ch2);
			ch1 = getc(input1);
			ch2 = getc(input2);
		}
		if (feof(input1) && feof(input2))
		 printf("Comparação concluida com (%.f) divergencias dentre (%.f) caracteres => proporção (%f).",cont,total,cont/total);
		else{
			printf("Comparação concluida com (%.f) divergencias dentre (%.f) caracteres => proporção (%f) mas um dos arquivos ainda possui os seguintes elementos:\n",cont,total,cont/total);
			while(!feof(input1)){
				ch1 = fgetc(input1);
				printf("1: [%c]\n",ch1);
			}
			while(!feof(input2)){
				ch2 = fgetc(input2);
				printf("2: [%c]\n",ch2);
			}
		}
	  fclose(input1);
	  fclose(input2);
	  return 0;
}
