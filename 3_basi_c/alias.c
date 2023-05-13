#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define STR_SIZE 64
#define ALIAS_SIZE 3

int main(){
	FILE *in = fopen("file/input2.txt", "r");
	FILE *out = fopen("file/output2.txt", "w");
	
	char aliasin[ALIAS_SIZE][STR_SIZE] = {"lol", "lel", "boo"};
	char aliasout[ALIAS_SIZE][STR_SIZE] = {"laugh out loud", "laugh extremly loud", "scary noise"};
	
	if(in==NULL || out==NULL){
		printf("apertura file fallita\n");
		return 1;
	}
	
	char word[STR_SIZE];
	while(fscanf(in, "%s", word)>0){
		int match=0;
		for(int i=0; i<ALIAS_SIZE; i++){
			if(!strcmp(aliasin[i], word)){
				fprintf(out, " %s", aliasout[i]);
				match=1;
			}
		}
		if(!match)
			fprintf(out, " %s", word);
	}
	fprintf(out, "\n");
	
	fclose(in);
	fclose(out);
	
	return 0;
}
