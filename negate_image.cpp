#include <gd.h>
#include <iostream>
#include <omp.h>

using namespace std;

int main(int argc, char* argv[])
{
    // Check if the input image file is provided
    if (argc != 2) {
        cout << "Usage: " << argv[0] << " <input_image>" << endl;
        return 1;
    }

    // Open the input image file
    FILE* in_file = fopen(argv[1], "rb");
    // Load the input image
    gdImagePtr in_image = gdImageCreateFromPng(in_file);
    // Close the input image file
    fclose(in_file);

    // Get the dimensions of the input image
    int width = gdImageSX(in_image);
    int height = gdImageSY(in_image);
    // Create a new image for the black and white image
    gdImagePtr bw_image = gdImageCreate(width, height);

    // Set the number of threads to the number of processors on the system
    int num_threads = omp_get_num_procs();
    omp_set_num_threads(num_threads);

    // Parallelize the loop that converts the image to black and white
    #pragma omp parallel for
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            // Get the color of the current pixel
            int color = gdImageGetPixel(in_image, x, y);
            // Get the red, green, and blue components of the color
            int red = gdImageRed(in_image, color);
            int green = gdImageGreen(in_image, color);
            int blue = gdImageBlue(in_image, color);
            // Calculate the average (gray) value
            int gray = (red + green + blue) / 3;
            // Set the pixel in the black and white image to the gray value
            gdImageSetPixel(bw_image, x, y, gdImageColorAllocate(bw_image, gray, gray, gray));
        }
    }

    // Open the output image file
    FILE* out_file = fopen("bw_image.png", "wb");
    // Write the black and white image to the file
    gdImagePng(bw_image, out_file);
    // Close the output image file
    fclose(out_file);

    // Free the memory used by the input and output images
    gdImageDestroy(in_image);
    gdImageDestroy(bw_image);
    return 0;
}
