/*
 *  Author: Commodore64
 *  Purpose: A simplistic implementation of a CSV file reader
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define BUFFER_SIZE 1024
#define DEFAULT_SEPARATOR ';'
#define PIPE_CHAR '|'
#define EOL '\0'

void out(char *msg){
	perror(msg);
	exit(EXIT_FAILURE);
}


/* TODO
 * Instead of malloc'ating like a madman
 * use a char* pointer parameter as the buffer
 * you'll write the parsed line into.
 *
 * Add a SQL "query builder"
 *
 * Add pardstart & padend using %f in printf to prettify
 * Write a separate function for that.
 */
char *parseLine(char* originalLine, char sep) {
		
	// init strings
	const int len = strlen(originalLine);
	if(len == 0) return NULL;

	char *line = (char *) calloc(len+1, 1);
	
	for (int i=0; i < len; i++)
		if(originalLine[i] == sep) line[i] = PIPE_CHAR ;
		else line[i] = originalLine[i];


	return line;
}


int main(int argc, char *argv[]) {
	
	char r_Buf[BUFFER_SIZE];

	// check argument
	if(argc < 2) out("Invalid filepath argument."); 
	const char *path = argv[1];
	
	// check file existence
	if (access(path, F_OK) != 0) out("File doesn't exist. check the path\n");
	
	// define separator
	const char separator = argv[2] != NULL ? argv[2][0] : DEFAULT_SEPARATOR;

	// open file
	FILE *fileptr = fopen(path, "rb");
	if (fileptr == NULL) out("Unexpected error while reading file\n");
	
	// readlines
	while(fgets(r_Buf, BUFFER_SIZE, fileptr)) {
		char *bufl = parseLine(r_Buf, separator);
		printf("%s", bufl);
		free(bufl);
	}


	// cleanup
	fclose(fileptr);
	return 0;
}

