//CPSC1020 FALL2021
//PROGRAMMING ASSIGNMENT #1 (PA1)
//Skylar Hubbarth
//Last revised: 10/10/2021
//Cathy Kittelstad
//This program as a whole is designed to take images and manipulate them,
//based on the user's choice, to be either grayscaled, mirrored, green screened,
//or any combination of the three.

//*ppm_info.h
//The following header file contains structs, include statements, and function
//prototypes to be used in ppm_functions.c, driver.c, and manip.c.

#ifndef PPM_INFO
#define PPM_INFO

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


// First meaningful line of the PPM file
typedef struct header {
   char magicNum[3];
   int width, height, maxVal;
} header_t;


// Represents an RGB pixel with integer values between 0-255
typedef struct pixel {
   unsigned char r, g, b;
} pixel_t;


// PPM Image representation
typedef struct image {
   header_t header;
   pixel_t** pixels;
} image_t;


// For file pointer list
typedef struct filePtr{
   FILE * theFile;
	char * imageFileName;
	image_t* theImage;
   struct filePtr* next;
} filePtr_t;


// prototypes
header_t read_header(FILE* image_file);
void write_header(FILE* out_file, header_t header);
image_t* read_ppm(FILE* image_file);
image_t* read_pixels(FILE* image_file, header_t header);
image_t* allocate_memory(header_t header);
int printMenu1();
filePtr_t* printList(filePtr_t* theList);
void gray_scale(filePtr_t* image, filePtr_t** theList, int count);
void mirror(filePtr_t* image, filePtr_t** theList, int count);
void green_screen(filePtr_t* image1, filePtr_t* image2,
                  filePtr_t** theList, int count);
// void green_screen(filePtr_t** theList, int count);
void addToList(filePtr_t* frontOfList, FILE* newImage,
			     image_t* theNewImage, char* nameOfImage);
void write_p6(FILE* out_file, image_t* image1);


#endif
