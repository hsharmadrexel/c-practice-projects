/*===========================
 * Title: Computer Database Records Lookup
 * Author: Harsh Sharma
 * Purpose: View all the records present in the database file. 
 * Notes: Look at README for compiling and running instructions
===========================*/

/*--------Import all necessary header files/libraries-----------*/
#include <stdio.h>
#include <sys/file.h>
#include <stdlib.h>
#include "cc.h"

int
main(int argc, char *argv[])
{
	/*--------Variable, structure, pointer declarations-----------*/
	CComp comp;
	int index;
	FILE *fp;

	/*--------Open file for read and handle errors-----------*/
	fp = fopen("ccomp.db", "r");
	if(fp == NULL) {
		perror("fopen");
		exit(1);
	}

	/*--------Lock file for reading and seek to the first position in the file to read the structure-----------*/
	flock(fileno(fp), LOCK_SH);
	index = 1;
	fseek(fp, sizeof(CComp), SEEK_SET);

	/*--------Read a structure (entry) in the database and validate to print information for the structure to stdout-----------*/
	while(fread(&comp, sizeof(CComp), 1, fp) > 0) {
		if(index == comp.id) {
			printf("\n");
			printf("Maker: %s\n", comp.maker);
			printf("Model: %s\n", comp.model);
			printf("Year: %d\n", comp.year);
			printf("CPU: %s\n", comp.cpu);
			printf("Id: %d\n", comp.id);
			printf("Desc: %s\n", comp.desc);
			printf("----------------\n");
		}
		index++;
	}

	flock(fileno(fp), LOCK_UN);
	fclose(fp);
	exit(0);
}
