/*===========================
 * Title: Computer Database Menu Options
 * Author: Harsh Sharma
 * Purpose: Provide a simple menu-driven front-end which allows the users to execute different programs on CCOMP DB accordingly.
 * Notes: Look at README for compiling and running instructions
===========================*/

/*--------Import all necessary header files/libraries-----------*/
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

/*--------Prototype declarations-----------*/
void showMenu();
void runchild();

int
main(int argc, char *argv[])
{
	if(argc != 1) {
		fprintf(stderr, "Usage: ccmenu\n");
		exit(1);
	}
	showMenu();
}

/*--------Child function which takes command line arguments and the child executes them while the parent waits-----------*/
void runchild(char *tokens[]) 
{
	int chpid, status;
	chpid = fork();

	if(chpid == 0) {
		execvp(tokens[0], tokens);
	}
	else {
		wait(&status);
	}
}

/*--------Dynamic allocation of tokens and looping through the menu till exit is chosen by the user-----------*/
void showMenu()
{
	int i, usrchoice;
	char *tokens[8];

    while (1) {
    	for (i=0 ; i<8; i++) {
        	tokens[i] = malloc(sizeof(char) * 200);
    	}
    	
    	printf("--------------------------------\n");
		printf("Welcome to the Database Program!\n");
		printf("Please select a numbered option from the choices below\n");
		printf("1. Add a record\n");
		printf("2. Delete a record\n");
		printf("3. View a record by ID\n");
		printf("4. View all records\n");
		printf("5. Query by substring\n");
		printf("6. Query by year range\n");
		printf("7. Edit a record by ID\n");
		printf("8. Exit\n");
		printf("Your Choice: ");
		scanf("%d", &usrchoice);
		getchar();
		
		if (usrchoice == 1) {
			tokens[0] = "./ccadd"; 
			printf("ID: ");
			fgets(tokens[1], 200, stdin);
			printf("Maker: ");
			fgets(tokens[2], 200, stdin);
			printf("Model: ");
			fgets(tokens[3], 200, stdin);
			printf("Year: ");
			fgets(tokens[4], 200, stdin);
			printf("CPU: ");
			fgets(tokens[5], 200, stdin);
			printf("Desc: ");
			fgets(tokens[6], 200, stdin);
			tokens[7] = NULL; //NULL token to mark the termination of arguments
		}
		else if (usrchoice == 2) {
			tokens[0] = "./ccdel";
			printf("ID: ");
			fgets(tokens[1], 200, stdin);
			tokens[2] = NULL;
		}
		else if (usrchoice == 3) {
			tokens[0] = "./ccitem";
			printf("ID: ");
			fgets(tokens[1], 200, stdin);
			tokens[2] = NULL;
		}
		else if (usrchoice == 4) {
			tokens[0] = "./cclist";
			tokens[1] = NULL;
		}
		else if (usrchoice == 5) {
			tokens[0] = "./ccmatch";
			printf("Match Substring: ");
			fgets(tokens[1], 200, stdin);
			tokens[2] = NULL;
		}
		else if (usrchoice == 6) {
			tokens[0] = "./ccyear";
			printf("Year Range 1: ");
			fgets(tokens[1], 200, stdin);
			printf("Year Range 2: ");
			fgets(tokens[2], 200, stdin);
			tokens[3] = NULL;
		}
		else if (usrchoice == 7) {
			tokens[0] = "./ccedit";
			tokens[1] = NULL;
		}
		else {
			exit(0);
		}

		/*--------Get rid of the newline character that came from fgets-----------*/
		for (i = 0; i < 8; i++) {
			strtok(tokens[i], "\n");
		}

		runchild(tokens);

		// for (i=0 ; i<8; i++) {
  //       	free(tokens[i]);
  //   	}
	}
}