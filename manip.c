//CPSC1020 FALL2021
//PROGRAMMING ASSIGNMENT #1 (PA1)
//Skylar Hubbarth
//Last revised: 10/10/2021
//Cathy Kittelstad
//This program as a whole is designed to take images and manipulate them,
//based on the user's choice, to be either grayscaled, mirrored, green screened,
//or any combination of the three.

//*manip.c*
//The following program holds the function definitions for each of the
//image manipulation functions: gray_scale, mirror, and green_screen, as
//well as the definition for the linked list function that adds images
//to our linked list, addToList.

//DISCLAIMER: Any random print statements that have been commented out were
//there for the sake of debugging my program. I was going to just leave them in
//the program, but felt like that was inappropriate. I've now left them
//commented out because they made me laugh. I hope they make you laugh too.

#include "ppm_info.h"

// GRAY SCALE FUNCTION
// make each color pixel the average of the r, g, b components
// which will gray-scale the image
// inputs:  the image pointer
// outputs:  none
void gray_scale(filePtr_t* image, filePtr_t** theList, int count) {
   int row = 0;
   int col = 0;
	 int avg = 0;
   header_t header = image->theImage->header;

   image_t* newImage; //declaring new image
   newImage = allocate_memory(header); //sending image header to allocate memory

   //create a new file name and open that file for writing (from PA1 document)
   char fileName[30] = "g"; //for the gray scale function
   strcat(fileName, image->imageFileName);

   FILE* grayedImage; //taken out of if statement
   char* imageName;

   //printf("PREPROCING \n\n");

   //see if image already exists in the list
   //if the 2nd letter is a lower case 'g', then it already exists
   if(fileName[1] != 'g') {
     char buf[5];
     fileName[strlen(fileName)-4] = '\0';
     int length = snprintf(buf, 5, "%d", count);
     imageName = (char*)malloc(50);
     sprintf(imageName, "%s%02d.ppm", fileName, count);

     //printf("is sometng wrong here??\n\n\n");

     grayedImage = fopen(imageName, "w");
     if(!grayedImage) {
       fprintf(stderr, "grayed image file could not open\n\n");
       exit(1);
       }
   }
   else {
     return; //continues the program if image was already grayscaled
   }

   //for loops copied from lab4
   for(row = 0; row < header.height; row++) {
      for(col = 0; col < header.width; col++) {
  			// calculate the average of the r, g, b values for the pixel
  			avg = ( image->theImage->pixels[row][col].r +
  			        image->theImage->pixels[row][col].g +
  					  image->theImage->pixels[row][col].b ) / 3;

  			// assign avg to each r, g, b value of the pixel
  			newImage->pixels[row][col].r = avg;
  			newImage->pixels[row][col].g = avg;
  			newImage->pixels[row][col].b = avg;

      }
   }

   //printf("Completed preprpcajsinoadg 0011 \n\n");

   //calling write_p6, sending the new file pointer and the new image
   write_p6(grayedImage, newImage);

   //close the new file pointer
   fclose(grayedImage);

   //add the new image to the list of images by calling addToList
   filePtr_t* current = *theList;
   addToList(current, grayedImage, newImage, imageName);

}


//MIRROR FUNCTION
// flips an image's pixels over the y-axis
// which will mirror the image
// inputs:  the image pointer
// outputs:  none
void mirror(filePtr_t* image, filePtr_t** theList, int count){
  int row = 0;
  int col = 0;

  header_t header = image->theImage->header;

  image_t* newImage; //declaring new image
  newImage = allocate_memory(header); //sending image header to allocate memory

  //create a new file name and open that file for writing (from PA1 document)
  char fileName[30] = "m"; //for the mirror function
  strcat(fileName, image->imageFileName);

  FILE* mirroredImage;
  char* imageName;

  //printf("im tryign  \n\n\n");

  //see if image already exists in the list
  //if the 2nd letter is a lower case 'm', then it already exists
  if(fileName[1] != 'm') {
    char buf[5];
    fileName[strlen(fileName)-4] = '\0';
    int length = snprintf(buf, 5, "%d", count);
    imageName = (char*)malloc(50);
    sprintf(imageName, "%s%02d.ppm", fileName, count);

    mirroredImage = fopen(imageName, "w");
    if(!mirroredImage) {
      fprintf(stderr, "mirrored image file could not open\n\n");
      exit(1);
      }
  }
  else {
    return;
  } //continues the program if image was already mirrored

  //temp variables to fix 80 character limit
  pixel_t temp1;
  pixel_t temp2;

  //for loops for mirrored image algorithm

  for(row = 0; row < header.height; row++) {
      for(col = 0; col < header.width/2; col++) {
      newImage->pixels[row][col] = temp1;
      temp1 = image->theImage->pixels[row][header.width - 1 - col];
      newImage->pixels[row][header.width - 1 - col] = temp2;
      temp2 = image->theImage->pixels[row][col];

     }
  }

  //printf("flip flop 0110 1001 0110 1010 1110 \n\n");

  //calling write_p6, sending the new file pointer and the new image
  write_p6(mirroredImage, newImage);

  //close the new file pointer
  fclose(mirroredImage);

  //add the new image to the list of images by calling addToList
  filePtr_t* current = *theList;
  addToList(current, mirroredImage, newImage, imageName);
}

//GREEN SCREEN FUNCTION
// remove any non g components from the r g b pixels
// which will green screen the image
// inputs:  the image pointer
// outputs:  none
void green_screen(filePtr_t* image1, filePtr_t* image2,
                  filePtr_t** theList, int count) {
  int row = 0;
  int col = 0;

  header_t header = image1->theImage->header;

  image_t* newImage; //declaring new image
  newImage = allocate_memory(header); //sending image header to allocate memory

  //create a new file name and open that file for writing (from PA1 document)
  char fileName[30] = "gs"; //for the green screen function
  strcat(fileName, image2->imageFileName);

  FILE* gsImage;
  char* imageName;

  //printf("GREEN SCREEN AAAHHHHHHHHHHHHHH \n\n");

  //see if image already exists in the list
  //if the 4th letter is a lower case 's', then it already exists
  if(fileName[3] != 's') {
    char buf[5];
    fileName[strlen(fileName)-4] = '\0';
    int length = snprintf(buf, 5, "%d", count);
    imageName = (char*)malloc(50);
    sprintf(imageName, "%s%02d.ppm", fileName, count);

    gsImage = fopen(imageName, "w");
    if(!gsImage) {
      fprintf(stderr, "green screened image file could not open\n\n");
      exit(1);
      }
  }
  else {
     return; //continues the program if image was already green screened
   }

  //FOR LOOPS
  for(row = 0; row < header.height; row++) {
     for(col = 0; col < header.width; col++) {
       if((image1->theImage->pixels[row][col].r == 0) &&
          (image1->theImage->pixels[row][col].g == 255) &&
          (image1->theImage->pixels[row][col].b == 0)) {

         newImage->pixels[row][col].r = image2->theImage->pixels[row][col].r;
         newImage->pixels[row][col].g = image2->theImage->pixels[row][col].g;
         newImage->pixels[row][col].b = image2->theImage->pixels[row][col].b;

       }
       else {
         newImage->pixels[row][col].r = image1->theImage->pixels[row][col].r;
         newImage->pixels[row][col].g = image1->theImage->pixels[row][col].g;
         newImage->pixels[row][col].b = image1->theImage->pixels[row][col].b;

       }

     }
  }

  //printf("COMPUT \n\n\n");

  //calling write_p6, sending the new file pointer and the new image
  write_p6(gsImage, newImage);

  //close the new file pointer
  fclose(gsImage);

  //add the new image to the list of images by calling addToList
  filePtr_t* current = *theList;
  addToList(current, gsImage, newImage, imageName);



}

//ADDTOLIST FUNCTION
// adds the newimage to the end of the list of new output images
// inputs:  the image pointer
// outputs:  none
void addToList(filePtr_t* frontOfList, FILE* newImage,
			     image_t* theNewImage, char* nameOfImage){

             filePtr_t* currentNode = (filePtr_t*)malloc(sizeof(filePtr_t));
             currentNode = frontOfList;

             while(currentNode->next != NULL) {
               currentNode = currentNode->next;
             }

             filePtr_t* newNode = (filePtr_t*)malloc(sizeof(filePtr_t));

             newNode->theFile = newImage;
             newNode->imageFileName = nameOfImage;
             newNode->theImage = theNewImage;
             newNode->next = NULL;

             currentNode->next = newNode;

           }






//hi
