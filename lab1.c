//Sabiq Khan Lab 1 Tuesday 2:15
#include <stdio.h>
#define MAX_WORD_LENGTH 30
int main(int argc, char *argv[]){//argc is the number of arguments, argv is the first argument, and what is input when running the function after ./a.out
	int counter=0;
	char word[MAX_WORD_LENGTH];
	if(argc==1){
		printf("The file name is missing");
		return 0;
	}
	FILE *fp;
	fp=fopen(argv[1], "r");
	if(fp==NULL){
		printf("Error opening file\n");
		return 0;
	}
	while(fscanf(fp, "%s", word)==1){//while the pointer is going through the text file and reads a word, the counter increases
		counter++;
	}
	printf("%d words found\n", counter);
	fclose(fp);
	return 0; 
}

