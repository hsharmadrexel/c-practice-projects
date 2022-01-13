Title: Computer Database
Name: Harsh Sharma

Files Needed:
1. cc.h
2. ccadd.c
3. ccdel.c
4. ccedit.c
5. ccitem.c
6. cclist.c
7. ccmatch.c
8. ccmenu.c
8. Makefile

Comments:
All of the source code files are functional and behave appropriately. ccmenu.c is the main driver application which would execute other programs based on user input. Had to comment out the freeing of the tokens because of an error which I was unable to resolve or find a solution to in the given time frame.

Supplement Instructions:
1. Using a linux server or a machine that has the GCC compiler, compile the source code files with the command below using the makefile:
   make ccomp

2. The makefile will also create the ccomp.db file along with compiling all the source code files. 

3. Now that you have the executable files and the ccomp.db file created, launch the ccmenu executable with the command below and enter in user input as needed:
   ./ccmenu

4. After you're done testing the program, execute the command below to clean up all the executable files and remove ccomp.db file:
   make clean