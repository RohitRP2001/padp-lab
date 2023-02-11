#include <iostream>
#include <gd.h>  // include the gd library header
#include <omp.h> // include the OpenMP library header

int main()
{
  gdImagePtr im;   // declare an image pointer
  int color, x, y; // declare variables to store the color, x and y coordinates of the image

FILE *fp.*fptr;
	fp=fopen("mario.png","r");
  // read the image and store it in the im pointer
  im = gdImageCreateFromPng(fp);

  // get the size of the image
  int width = gdImageSX(im);
  int height = gdImageSY(im);

  // parallelize the for loop using OpenMP
  #pragma omp parallel for private(color, x, y)
  for (x = 0; x < width; x++)
  {
    for (y = 0; y < height; y++)
    {
      // get the color of the current pixel
      color = gdImageGetPixel(im, x, y);

      // convert the color to grayscale by taking the average of red, green, and blue components
      int gray = (gdImageRed(im, color) + gdImageGreen(im, color) + gdImageBlue(im, color)) / 3;

      // set the pixel color to the grayscale value
      gdImageSetPixel(im, x, y, gdImageColorAllocate(im, gray, gray, gray));
    }
  }
	
fptr=fopen("outputt.png","w");
	
  // save the converted image
  gdImagePng(im, fptr);

  // free the memory used by the image
  gdImageDestroy(im);

  return 0;
}
