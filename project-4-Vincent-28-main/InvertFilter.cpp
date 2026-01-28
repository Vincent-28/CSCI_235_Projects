#include "InvertFilter.hpp"
#include "ImageFile.hpp"

#include <iostream>

InvertFilter::InvertFilter() : ImageFilter(1.0) {};

InvertFilter::InvertFilter(double initialStrength) : ImageFilter(initialStrength) {};

void InvertFilter::apply(ImageFile& image) const {
    double s = getStrength(); //we are asking the base class which is ImageFilter for the current strength (which has already been clamped)

    std::vector<std::vector<Pixel>> pixels = image.getPixels(); //ImageFile has pixels in a 2D vector

    int h = image.getHeight(); //grab the height in number of rows
    int w = image.getWidth(); //grab the width in number of columns

    for(int row = 0; row < h; row++) {
        for(int col = 0; col < w; col++) { //loop through every column for every row so that we can go to every pixel
            Pixel px = pixels[row][col]; //grab the pixel  at (row, col) from the 2D vector

            //we now want to find the inverted color for red green and blue
            int invR = 255 - px.red;
            int invG = 255 - px.green;
            int invB = 255 - px.blue;

            //we are now using the fully inverted rgb to find the average strength
            int newR = invR * s + px.red * (1.0 - s);
            int newG = invG * s + px.green * (1.0 - s);
            int newB = invB * s + px.blue * (1.0 - s);

            //here we are clamp the range from 0 to 255. If rgb end up going below 0, we set the new to 0 and if the rgb ends up going above 255 we set the new to 255
            if(newR < 0) {
                newR = 0; 
            } 
            else if(newR > 255) {
                newR = 255;
            } 

            if(newG < 0) {
                newG = 0; 
            } 
            else if(newG > 255) {
                newG = 255;
            } 

            if(newB < 0) {
            newB = 0; 
            } 
            else if(newB > 255) {
            newB = 255;
            } 

            //here we update each rgb to the new rgb we changed
            px.red = newR;
            px.green = newG;
            px.blue = newB;

            //then we write the pixel we changed back into the 2D vector
            pixels[row][col] = px;
        }
    }
    //after the loop we apply the change to ImageFile
    image.setPixels(pixels);
}

std::string InvertFilter::name() const {
    return "Invert Filter";
}
