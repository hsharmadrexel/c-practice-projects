/*===========================
 * Title: Computer Database Substring Lookup
 * Author: Harsh Sharma
 * Purpose: Match a specified record with the given string if it is a substring of maker, model, desc fields. 
 * Notes: Look at README for compiling and running instructions
===========================*/

/*--------Import all necessary header files/libraries-----------*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/file.h>
#include "cc.h"

int
main(int argc, char *argv[])
{
	/*--------Structure, pointer declarations-----------*/
	CComp comp;
	FILE *fp;
	
	/*--------Validate user input argument count-----------*/
	if(argc != 2) {
		fprintf(stderr, "Usage: ccmatch string\n");
		exit(1);
	}
	
	/*--------Open file for read and handle errors-----------*/
	fp = fopen("ccomp.db", "r");
	if(fp == NULL) {
		perror("fopen");
		exit(2);
	}

	/*--------Lock file for reading and seek to the first position in the file to read the structure-----------*/
	flock(fileno(fp), LOCK_SH);
	fseek(fp, sizeof(CComp), SEEK_SET);

	/*--------Read each structure (entry) in the database and check for substring, then print to stdout-----------*/
	while(fread(&comp, sizeof(CComp), 1, fp) > 0) {
		if ((strstr(comp.maker, argv[1]) != NULL) || (strstr(comp.model, argv[1]) != NULL) || (strstr(comp.desc, argv[1]) != NULL)) {
			printf("\n");
			printf("Maker: %s\n", comp.maker);
			printf("Model: %s\n", comp.model);
			printf("Year: %d\n", comp.year);
			printf("CPU: %s\n", comp.cpu);
			printf("Id: %d\n", comp.id);
			printf("Desc: %s\n", comp.desc);
			printf("----------------\n");
		}
	}
	flock(fileno(fp), LOCK_UN);
	fclose(fp);
	exit(0);
}
