//CPSC1020 FALL2021
//PROGRAMMING ASSIGNMENT #1 (PA1)
//Skylar Hubbarth
//Last revised: 10/10/2021
//Cathy Kittelstad
//This program as a whole is designed to take images and manipulate them,
//based on the user's choice, to be either grayscaled, mirrored, green screened,
//or any combination of the three.

//*driver.c*
//The following program includes the main function for this program. Here
//is where we wil call the functions created in ppm_functions.c and manip.c
//in order to complete our program.

#include <stdio.h>
#include <stdlib.h>
#include "ppm_info.h"


int main(int argc, char* argv[]) {
	// check that 3 arguments were entered at the command-line
   if(argc != 3) {
      printf("USAGE: <executable> <oldImage> <newImage>\n\n");
      return -1;
   }

   filePtr_t* imageList = NULL;

	// open the two files sent in via the command line arguments
   FILE* oldImage1 = fopen(argv[1], "r");
   FILE* oldImage2 = fopen(argv[2], "r");

   if(!oldImage1 || !oldImage2) {
      printf("ERROR: File(s) could not be opened.\n");
      return -1;
   }


	// read in the two images from the two file pointers
  // and create image_t images for each
	// this is where the allocation is done and everything
	// is read in from the input file; a pointer to the
	// image is returned
   image_t* image1 = read_ppm(oldImage1);
   image_t* image2 = read_ppm(oldImage2);

   //declaring file pointers and mallocing
   filePtr_t* filePtr1 = (filePtr_t*)malloc(sizeof(filePtr_t));
   filePtr_t* filePtr2 = (filePtr_t*)malloc(sizeof(filePtr_t));

   //initializing file pointers with values to later add to our node
   //to store the image data in a nicer way :-)
   filePtr1->theFile = oldImage1;
   filePtr1->imageFileName = argv[1];
   filePtr1->theImage = image1;
   filePtr1->next = NULL;

   filePtr2->theFile = oldImage2;
   filePtr2->imageFileName = argv[2];
   filePtr2->theImage = image2;
   filePtr2->next = NULL;

   //set linked list head and node 2
   imageList = filePtr1;
   imageList->next = filePtr2;

   int printingMenu = printMenu1();
   filePtr_t* imageChoice = NULL;

   int size = 2;

   //printf("Running While Loop:\n");

   //while loop for image choice
   while (printingMenu != 0) {
     if (printingMenu == 1) {
       imageChoice = printList(imageList);
       gray_scale(imageChoice, &imageList, size);
       ++size;
     }
     else if(printingMenu == 2) {
       imageChoice = printList(imageList);
       mirror(imageChoice, &imageList, size);
       ++size;
     }
     else if(printingMenu == 3) {
       printf("\nThe Clemson Paw image will be copied on top of which");
       printf(" of the following Disney images:\n"); //split for 80 char limit
       imageChoice = printList(imageList);
       green_screen(filePtr1, imageChoice, &imageList, size);
       ++size;
     }
     printingMenu = printMenu1();
  }


  	return 0;
}
