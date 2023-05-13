#include <stdio.h>
#include <stdlib.h>

#define STR_SIZE 64

int main(){
	FILE *f = fopen("file/input1.txt", "r");
	
	if(f==NULL){
		printf("apertura file fallita\n");
		return 1;
	}
	
	char nome1[STR_SIZE], nome2[STR_SIZE];
	int p1, p2;
	while(fscanf(f, "%s %s %d %d", nome1, nome2, &p1, &p2)>0){
		printf("%s - %s: ", nome1, nome2);
		if(p1 != p2)
			printf("vincitore: %s\n", p1>p2 ? nome1 : nome2);
		else
			printf("pareggio\n");
	}
	
	fclose(f);
	
	return 0;
}
