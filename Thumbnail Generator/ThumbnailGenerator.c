/*===========================
 * Title: Thumbnail Generator from Image
 * Author: Harsh Sharma
 * Purpose: Generate a thumbnail for a PGM file passed through standard input stream
 * Notes: Look at README for compiling and running instructions
===========================*/

/*--------Import all necessary header files/libraries-----------*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int
main(int argc, char *argv[]) {
	/*--------Variable and pointer declarations-----------*/
	int n, r, w; /*Return values from scanf, fread, and fwrite system calls*/
	int width, height, max; /*Width, height, and max values of input PGM image*/
	int s, newWidth, newHeight; /*Downscale factor, new width, and new height values of thumbnail PGM image*/
	int newRow, newCol; /*Row and column loop variables while writing new image*/
	char newline; /*Newline character after the header text*/
	unsigned char *buff, *new_buff; /*Buffer pointers for the original and new images*/

	/*--------Scan header into the variables' memory addresses-----------*/
	n = scanf("P5 %d %d %d", &width, &height, &max);

	if (n != 3) {	
		perror("headerscan"); /*Error handling*/
		exit(1); /*Exit status*/
	}
	
	newline = getchar(); /*Get newline character*/
	
	/*--------Original Image Buffer Memory Allocation-----------*/
	buff = malloc(width * height); 
	
	if(buff == NULL) {
		perror("read malloc");
		exit(2);
	}

	/*--------Scale, new width, and new height calculations-----------*/
	s = width/200;
	newWidth = width/s;
	newHeight = height/s;

	/*--------New Image Buffer Memory Allocation-----------*/
	new_buff = malloc(newWidth * newHeight);
	
	if(new_buff == NULL) {
		perror("write malloc");
		exit(3);
	}
	
	/*---Reading pixel data byte by byte into the buffer created---*/
	r = fread(buff, width * height, 1, stdin);
		
	if(r < 0) {
		perror("fread");
		exit(4);
	}	

	/*---Printing the revised header text for new image to stdout---*/
	printf("P5\n%d %d\n%d\n", newWidth, newHeight, max);
	
	/*--------Loop to assign data for thumbnail at different addresses using top left pixel-----------*/
	for (newRow=0; newRow < newHeight; newRow++) {
		for (newCol=0; newCol < newWidth; newCol++) {
			*(new_buff+newWidth*newRow+newCol) = *(buff+width*newRow*s+newCol*s);
		}
	}
	
	/*--------Write out pixel data byte by byte from the buffer to stdout-----------*/
	w = fwrite(new_buff, newWidth * newHeight, 1, stdout);
	
	if(w < 0) {
		perror("fwrite");
		exit(5);
	}
	
	/*--------Free memory spaces used by pointers-----------*/
	free(buff);
	free(new_buff);
}
