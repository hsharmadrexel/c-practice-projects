/*===========================
 * Title: Computer Database Deletion
 * Author: Harsh Sharma
 * Purpose: Delete a specified record in the database passed through ID number in the comamnd line. 
 * Notes: Look at README for compiling and running instructions
===========================*/

/*--------Import all necessary header files/libraries-----------*/
#include <stdio.h>
#include <stdlib.h>
#include <sys/file.h>
#include <string.h>
#include <sys/file.h>
#include "cc.h"

int
main(int argc, char * argv[])
{	
	/*--------Variable, structure, pointer declarations-----------*/
	CComp comp;
	CComp read;
	FILE *fp;
	int index;

	/*--------Validate user input argument count-----------*/
	if(argc != 2) {
		fprintf(stderr, "Usage: ccdel id\n");
		exit(1);
	}

	/*--------Open file for writing and handle errors-----------*/
	fp = fopen("ccomp.db", "r+");
	if(fp == NULL) {
		perror("fopen");
		exit(3);
	}

	/*--------Lock file for writing purposes-----------*/
	flock(fileno(fp), LOCK_EX);	

	index = atoi(argv[1]);

	/*--------Reading the structure to test if it exists in the database with the given ID-----------*/
	fseek(fp, index * sizeof(CComp), SEEK_SET);
	fread(&comp, sizeof(CComp), 1, fp);

	/*--------Handle cases where the provided id doesn't exist in the database-----------*/
	if(index != comp.id) {
		fprintf(stderr, "No such item to delete\n");
		exit(2);
	}
	
	/*--------Specify an empty structure to override with the existing one-----------*/
	comp.id = 0;
	strncpy(comp.maker, "", Nmaker-1);
	strncpy(comp.model, "", Nmodel-1);
	comp.year = 0;
	strncpy(comp.cpu, "", Ncpu-1);
	strncpy(comp.desc, "", Ndesc-1);

	/*--------Unlocking file after writing the empty structure to "delete" the record-----------*/
	fseek(fp, index * sizeof(CComp), SEEK_SET);
	fwrite(&comp, sizeof(CComp), 1, fp);
	printf("Successfully deleted the record\n");
	flock(fileno(fp), LOCK_UN);
	fclose(fp);
	exit(0);
}
