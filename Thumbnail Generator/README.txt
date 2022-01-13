Title: Thumbnail Generator
Name: Harsh Sharma

Comments:
The source code is functional and creates the thumbnail image using the top left pixels from the original supplied image. There are no known errors. Error handling for cases with fread, fwrite and malloc are handled in the code. 

Supplement Instructions:
1. Using a linux server or a machine that has the GCC compiler, compile the program with the command below:
   gcc ThumbnailGenerator.c -o thumbnailgen

2. Now that you have the executable thumbnailgen created in the working directory, run it with the following command:
   ./thumbnailgen < porsche.pgm > porsche_thumb.pgm

3. The above command would redirect stdin and stdout to their respective files to read/write data.