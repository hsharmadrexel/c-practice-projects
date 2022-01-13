/*===========================
 * Title: Shell Application
 * Author: Harsh Sharma
 * Purpose: Supports pipes, redirection, and command sequences. 
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
#include <ctype.h>

/*--------Prototype and global variable declarations-----------*/
void displayPrompt();
void runchild();
void runcommand();
void doredir();
void dopipes();

int pfd[64][2];

int
main(int argc, char *argv[])
{
	if(argc != 1) {
		fprintf(stderr, "Usage: sh283\n");
		exit(1);
	}

	displayPrompt();
}

void runchild(char *tokens[], int bg, char *redir[], int pos, int pipecnt) 
{
	int in, out, chpid, i, exitstat;
	chpid = fork();

	if (chpid == 0) {
		if (pos != -1) {
			if (pos == 0) {
				dup2(pfd[0][1], 1);
			}
			else if (pos != pipecnt) {
				dup2(pfd[pos-1][0], 0);
				dup2(pfd[pos][1], 1);
			}
			else {
				dup2(pfd[pipecnt - 1][0], 0);
			}
		}
	
		if (redir[0] != NULL) {
			in = open(redir[0], O_RDONLY);
			close(0);
			dup(in);
		}

		if (redir[1] != NULL) {
			if (redir[2] != NULL) {
				out = open(redir[1], O_APPEND | O_RDWR | O_CREAT, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
			}
			else {
				out = open(redir[1], O_TRUNC | O_RDWR | O_CREAT, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
			}
			close(1);
			dup(out);
		}

		if ((execvp(tokens[0], tokens)) != 0) {
			perror("execution of command failed");
		}

		if (pos == 0) {
			close(pfd[0][1]);
		}
		else if (pos != pipecnt) {
			close(pfd[pos-1][0]);
			close(pfd[pos][1]);
		}
		else {
			close(pfd[pipecnt - 1][0]);
		}
	}
	else if (bg == 0) {
		if (pipecnt == 0) {
			do {
				exitstat = wait(0);
			} while (exitstat != chpid);
		}
		else {
			if (pos == 0) {
				close(pfd[0][1]);
			}
			else if (pos != pipecnt) {
				close(pfd[pos-1][0]);
				close(pfd[pos][1]);
			}
			else {
				close(pfd[pipecnt - 1][0]);
			}
		}
	}
}

void runcommand(char *cmd, char *redir[], int pos, int pipecnt, int bg) {
	char *tokens[64], cwd[256];
	int i;

	if (strchr(cmd, '&') != NULL) {
		bg = 1;
	}

	cmd = strtok(cmd, "&");

	tokens[0] = strtok(cmd, " \t\n");
	
	for(i = 1; i < 64; i++) {
		tokens[i] = strtok(NULL, " \t\n");
		if(tokens[i] == NULL) {
			break;
		}
	}

	if (strcmp(tokens[0], "cd") == 0) {
		if(tokens[1] == NULL) {
			getcwd(cwd, sizeof(cwd));
			tokens[1] = cwd;
		}
		if (chdir(tokens[1]) != 0) {
			perror("invalid cd use");
		}
	}
	else {
		runchild(tokens, bg, redir, pos, pipecnt);
	}
}

void doredir(char *cmd, int pos, int pipecnt, int bg)
{
	char *redir[3];

	redir[0] = strchr(cmd, '<');
	redir[1] = strchr(cmd, '>');
	redir[2] = strstr(cmd, ">>");

	if (redir[0] != NULL) {
	    redir[0] = strtok(redir[0], "< \t\n");
	}

	if (redir[1] != NULL) {
	    redir[1] = strtok(redir[1], "> \t\n");
	}

	cmd = strtok(cmd, "<>");
	runcommand(cmd, redir, pos, pipecnt, bg);
}

void dopipes(char *cmd, int bg) 
{
	int i, pipecnt;
	char *pipes[64];

	if (strchr(cmd, '|') != NULL) {
		pipes[0] = strtok(cmd, "|");
		for (i = 1; i < 64; i++) {
			pipes[i] = strtok(NULL, "|");
			if (pipes[i] == NULL) {
				pipecnt = i - 1;
				break;
			}
		}

		for(i = 0; i < pipecnt; i++) {
			pipe(pfd[i]);
		}

		for(i = 0; i <= pipecnt; i++) {
			cmd = pipes[i];
			doredir(cmd, i, pipecnt, bg);
		}

		for (i=0; i<=pipecnt; i++) {
			wait(0);
		}
	}
	else {
		doredir(cmd, -1, 0, bg);
	}
}

void displayPrompt()
{
	int i, cmdcnt;
	char usrcmd[512], cwd[256], *cmd, *cmds[128];

    while (1) {
   		getcwd(cwd, sizeof(cwd));
    	
    	printf("100:%s user$ ", cwd);
		fgets(usrcmd, 512, stdin);

		if (feof(stdin)) {
			printf("\nLogged out\n");
			break;
		}

		if (usrcmd[0] == '\n') {
			continue;
		}

		if (strchr(usrcmd, ';') != NULL) {
			cmds[0] = strtok(usrcmd, ";");
			for (i = 1; i < 128; i++) {
				cmds[i] = strtok(NULL, ";");
				if (cmds[i] == NULL) {
					cmdcnt = i;
					break;
				}
			}

			for(i = 0; i < cmdcnt; i++) {
				cmd = cmds[i];
				dopipes(cmd, 0);
			}
		}
		else if (strchr(usrcmd, '&') != NULL) {
			cmds[0] = strtok(usrcmd, "&");
			for (i = 1; i < 128; i++) {
				cmds[i] = strtok(NULL, "&");

				if (isspace(cmds[i][0])) {
					cmdcnt = i;
					break;
				}

				if (cmds[i] == NULL) {
					cmdcnt = i;
					break;
				}
			}

			for(i = 0; i < cmdcnt; i++) {
				cmd = cmds[i];
				dopipes(cmd, 1);
			}
		}
		else {
			dopipes(usrcmd, 0);
		}
	}
	exit(0);
}