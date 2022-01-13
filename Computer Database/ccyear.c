/*===========================
 * Title: Computer Database Year Lookup
 * Author: Harsh Sharma
 * Purpose: Provide all the records given within the year range in the command line.
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
	if(argc != 3) {
		fprintf(stderr, "Usage: ccyear year1 year2\n");
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

	/*--------Read each structure (entry) in the database and check if the year is in range, then print to stdout if that's the case-----------*/
	while(fread(&comp, sizeof(CComp), 1, fp) > 0) {
		if ((comp.year >= (atoi(argv[1]))) && (comp.year <= atoi(argv[2]))) {
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
