/*
3. Realizzare funzioni per stringhe char *stringrev(char * str) (inverte ordine
caratteri) e int stringpos(char * str, char chr) (cerca chr in str e restituisce la
posizione)
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ARGS_SIZE 5

char *stringrev(char *str);
int stringpos(char *str, char chr);

int main(int argc, char **argv){
	if(argc != 2){
		printf("argomenti sbagliati\n");
		exit(1);
	}
	char *valid_args[ARGS_SIZE] = {"-a", "-l", "-c", "-p", "--prosciutto"};
	
	printf("la stringa: \"%s\" ha %d caratteri\n", argv[1], (int)strlen(argv[1]));
	int found=0;
	for(int i=0; i<ARGS_SIZE; i++){
		if(!strcmp(valid_args[i], argv[1])){
			found = 1;
			break;
		}
	}
	printf("la stringa %s e' un argomento valido\n", found ? "" : "non ");
	
	char *reverse = stringrev(argv[1]);
	printf("il suo contrario e': \"%s\"\n", reverse);
	free(reverse);
	
	char x='p';
	int res = stringpos(argv[1], x);
	if(res!=-1)
		printf("la prima occorrenza di '%c' si trova in posizione: %d\n", x, res);
	else
		printf("'%c' non trovato nella stringa\n", x); 

	
	return 0;
}


char *stringrev(char *str){
	int len=strlen(str);
	char *result = malloc(sizeof(char)*len);
	for(int i=0; i<len; i++)
		result[len-i-1]=str[i];
	return result;
}


int stringpos(char *str, char chr){
	for(int i=0; i<strlen(str); i++)
		if(str[i]==chr)
			return i;
	return -1;
}
