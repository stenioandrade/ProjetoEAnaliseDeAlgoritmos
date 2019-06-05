#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(){
	FILE* input1 = fopen("output.txt","r");
	FILE* input2 = fopen("porto.output.txt","r");
	char ch1 = fgetc(input1);
	char ch2 = fgetc(input2);
	float cont=0;
	float total=0;
	  while (ch1 != EOF && ch2 != EOF) 
	  {
		total++;
		/* display contents of file on screen */
		if(ch1 == ' ') ch1 = fgetc(input1);
		if(ch2 == ' ') ch2 = fgetc(input2);
		if( ch1 != ch2 ){
			cont++;
			printf("Divergencia (%.f) %c != %c\n",cont, ch1, ch2);
		}
		//else printf("%c = %c\n",ch1, ch2);
		//fputc(ch1,output1); 
	 
		ch1 = getc(input1);
		ch2 = getc(input2);
	  }
	   
	  if (feof(input1) || feof(input2))
		 printf("\n Comparação terminada com (%.f) divergencias dentre (%.f) caracteres => proporção (%f).",cont,total,cont/total);
	  else
		 printf("\n Something went wrong.");
	  fclose(input1);
	  fclose(input2);
		 
	  getchar();
	  return 0;
}
