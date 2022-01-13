/*===========================
 * Title: Computer Database Item Lookup
 * Author: Harsh Sharma
 * Purpose: View a record in the database file given the ID number. 
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
	CComp target;
	FILE *fp;
	int index;

	/*--------Validate user input argument count-----------*/
	if(argc != 2) {
		fprintf(stderr, "Usage: ccitem id\n");
		exit(1);
	}

	/*--------Open file and lock for read purposes-----------*/
	fp = fopen("ccomp.db", "r");
	flock(fileno(fp), LOCK_SH);
	index = atoi(argv[1]);

	/*--------Seek to the desired index position and read into the structure-----------*/
	fseek(fp, index * sizeof(CComp), SEEK_SET);
	fread(&target, sizeof(CComp), 1, fp);
	flock(fileno(fp), LOCK_UN);
	fclose(fp);

	/*--------Handle cases where the provided id doesn't exist in the database-----------*/
	if(index != target.id) {
		fprintf(stderr, "No such item\n");
		exit(2);
	}

	/*--------Display the struct information to stdout-----------*/
	printf("Maker: %s\n", target.maker);
	printf("Model: %s\n", target.model);
	printf("Year: %d\n", target.year);
	printf("CPU: %s\n", target.cpu);
	printf("Id: %d\n", target.id);
	printf("Desc: %s\n", target.desc);
	exit(0);
}