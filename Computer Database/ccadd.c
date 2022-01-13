/*===========================
 * Title: Computer Database Addition
 * Author: Harsh Sharma
 * Purpose: Add a record passed through as arguments in the command line to the ccomp.db file.
 * Notes: Look at README for compiling and running instructions
===========================*/

/*--------Import all necessary header files/libraries-----------*/
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/file.h>
#include "cc.h"

int
main(int argc, char *argv[])
{
	/*--------Structure and pointer declarations-----------*/
	CComp new;
	FILE *fp;
	struct stat buf;

	/*--------Validate user input argument count-----------*/
	if(argc != 7) {
		fprintf(stderr, "Usage: ccadd [-a | id] maker model year cpu desc\n");
		exit(1);
	}

	/*--------Calculate new id from stat call-----------*/
	if((strcmp(argv[1], "-a")) == 0) {
		stat("ccomp.db", &buf);
		new.id = buf.st_size / 256;
		if (new.id == 0) {
			new.id = 1;
		} 
	}
	else {
		new.id = atoi(argv[1]);
	}

	/*--------Copying user arguments into structure and adding null character for termination-----------*/
	strncpy(new.maker, argv[2], Nmaker-1);
	new.maker[Nmaker-1] = '\0';
	strncpy(new.model, argv[3], Nmodel-1);
	new.model[Nmodel-1] = '\0';
	new.year = atoi(argv[4]);
	strncpy(new.cpu, argv[5], Ncpu-1);
	new.cpu[Ncpu-1] = '\0';
	strncpy(new.desc, argv[6], Ndesc-1);
	new.desc[Ndesc-1] = '\0';

	/*--------Open file for read/write and handle errors-----------*/
	fp = fopen("ccomp.db", "r+");
	if(fp == NULL) {
		perror("fopen");
		exit(2);
	}

	/*--------Lock file for writing and seek to the position in the file to fwrite the structure-----------*/
	flock(fileno(fp), LOCK_EX);
	fseek(fp, new.id * sizeof(CComp), SEEK_SET);
	fwrite(&new, sizeof(CComp), 1, fp);
	printf("Successfully added the record\n");
	flock(fileno(fp), LOCK_UN);
	fclose(fp);
	exit(0);
}
