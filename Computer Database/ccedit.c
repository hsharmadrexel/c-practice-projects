/*===========================
 * Title: Computer Database Edition
 * Author: Harsh Sharma
 * Purpose: Edit the attributes of an existing record given the ID of that record in database.
 * Notes: Look at README for compiling and running instructions
===========================*/

/*--------Import all necessary header files/libraries-----------*/
#include <stdio.h>
#include <stdlib.h>
#include <sys/file.h>
#include <string.h>
#include "cc.h"

int
main(int argc, char *argv[])
{
	/*--------Structure, pointer, variable declarations-----------*/
	CComp comp;
	char input[200]; //Buffer for getting user input through scanf
	FILE *fp;
	
	/*--------Validate user input argument count-----------*/
	if(argc != 2) {
		fprintf(stderr, "Usage: ccedit id\n");
		exit(1);
	}
	
	/*--------Open file for read/write and handle errors-----------*/
	fp = fopen("ccomp.db", "r+");
	if(fp == NULL) {
		perror("fopen");
		exit(2);
	}

	/*--------Lock file for writing purposes-----------*/
	flock(fileno(fp), LOCK_EX);

	/*--------Seek to the given position and read into structure-----------*/
	fseek(fp, atoi(argv[1]) * sizeof(CComp), SEEK_SET);
	fread(&comp, sizeof(CComp), 1, fp);

	/*--------Handle cases where the provided id doesn't exist in the database-----------*/
	if((atoi(argv[1])) != comp.id) {
		fprintf(stderr, "No such item to edit\n");
		exit(3);
	}

	/*--------Print prompts to show the original value and ask user if they want to change it-----------*/
	printf("----------------------------\n");
	printf("Original Maker Value: %s\n", comp.maker);
	printf("Do you wish to change the maker value? Enter y/n\n");
	scanf("%s", input);

	/*--------Use strncpy to copy the user input string to the structure's attribute after modification-----------*/
	if (input[0] == 'y') {
		printf("Please enter in a new maker value:\n");
		scanf("%s", input);
		strncpy(comp.maker, input, Nmaker-1);
	}

	printf("----------------------------\n");
	printf("Original Model Value: %s\n", comp.model);
	printf("Do you wish to change the model value? Enter y/n\n");
	scanf("%s", input);

	if (input[0] == 'y') {
		printf("Please enter in a new model value:\n");
		scanf("%s", input);
		strncpy(comp.model, input, Nmodel-1);
	}

	printf("----------------------------\n");
	printf("Original Year Value: %d\n", comp.year);
	printf("Do you wish to change the year value? Enter y/n\n");
	scanf("%s", input);

	if (input[0] == 'y') {
		printf("Please enter in a new year value:\n");
		scanf("%s", input);
		comp.year = atoi(input);
	}

	printf("----------------------------\n");
	printf("Original CPU Value: %s\n", comp.cpu);
	printf("Do you wish to change the CPU value? Enter y/n\n");
	scanf("%s", input);

	if (input[0] == 'y') {
		printf("Please enter in a new CPU value:\n");
		scanf("%s", input);
		strncpy(comp.cpu, input, Ncpu-1);
	}

	printf("----------------------------\n");
	printf("Original Description Value: %s\n", comp.desc);
	printf("Do you wish to change the Description value? Enter y/n\n");
	scanf("%s", input);

	if (input[0] == 'y') {
		printf("Please enter in a new Description value:\n");
		scanf("%s", input);
		strncpy(comp.desc, input, Ndesc-1);
	}
	printf("----------------------------\n");

	/*--------Seek to the given position and overwrite the updated structure-----------*/
	fseek(fp, atoi(argv[1]) * sizeof(CComp), SEEK_SET);
	fwrite(&comp, sizeof(CComp), 1, fp);

	/*--------Print appropriate status message to the user, unlock and close file-----------*/
	printf("Successfully edited the record\n");
	flock(fileno(fp), LOCK_UN);
	fclose(fp);
	exit(0);
}