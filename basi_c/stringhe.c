/*
1. Scrivere un’applicazione che data una stringa come argomento ne stampa a video la
lunghezza, ad esempio:
./lengthof "Questa frase ha 28 caratteri"
deve restituire a video il numero 28.
2. Scrivere un’applicazione che definisce una lista di argomenti validi e legge quelli passati
alla chiamata verificandoli e memorizzando le opzioni corrette, restituendo un errore in
caso di un’opzione non valida.
3. Realizzare funzioni per stringhe char *stringrev(char * str) (inverte ordine
caratteri) e int stringpos(char * str, char chr) (cerca chr in str e restituisce la
posizione)
*/

#include <stdio.h>

int main(int argc, char **argv){
	if(argc != 2){
		printf("argomenti sbagliati\n");
		exit(1);
	}
	printf("la stringa: %s ha %d caratteri", argv[1], strlen(argv[1]));
	return 0;
}