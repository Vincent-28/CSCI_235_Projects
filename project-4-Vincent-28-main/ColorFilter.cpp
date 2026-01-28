#include "ColorFilter.hpp"
#include "ImageFile.hpp"
#include "Pixel.hpp"

#include <vector>

ColorFilter::ColorFilter(int red, int green, int blue, double strength) : ImageFilter(strength) {
    if(red < 0) { //clamp red
        red = 0;
    }
    else if(red > 255) {
        red = 255;
    }

    if(green < 0) { //clamp green
        green = 0;
    }
    else if(green > 255) {
        green = 255;
    }

    if(blue < 0) { //clamp blue
        blue = 0;
    }
    else if(blue > 255) {
        blue = 255;
    }

    color_.red = red; //after clamping we store each cmaped color value into Pixel member
    color_.green = green;
    color_.blue = blue;
}

void ColorFilter::setColor(int r, int g, int b) {
    if(r < 0) { //here we clamp r
        r = 0;
    }
    else if(r > 255) {
        r = 255;
    }

    if(g < 0) { //here we clamp g
        g = 0;
    }
    else if(g > 255) {
        g = 255;
    }

    if(b < 0) { //here we clamp b
        b = 0;
    }
    else if(b > 255) {
        b = 255;
    }

    color_.red = r; //after we clamp, we set each overlay color
    color_.green = g;
    color_.blue = b;
}

Pixel ColorFilter::getColor() const {
    return color_; //getter returns the stored overlay Pixel
}

void ColorFilter::apply(ImageFile& image) const {
    double s = getStrength(); //getting the strength [1,0] (how strong the overlay is)

    std::vector<std::vector<Pixel>> pixels = image.getPixels(); //create a copy of the pixel grid from the image

    int h = image.getHeight(); //these are the L and W dimensions
    int w = image.getWidth();

    for(int row = 0; row < h; row++) { //loop over every pixel 
        for(int col = 0; col < w; col++) {
            Pixel px = pixels[row][col]; //take the current pixel we're at

            int REDoverlay = color_.red; //get the overlay color which is stored in color_
            int GREENoverlay = color_.green;
            int BLUEoverlay = color_.blue;

            int newR = REDoverlay * s + px.red * (1.0 - s); //blend it according to the formula
            int newG = GREENoverlay * s + px.green * (1.0 - s);
            int newB = BLUEoverlay * s + px.blue * (1.0 - s);

            if (newR < 0) { //clamp the newR
                newR = 0;
            } else if (newR > 255) {
                newR = 255;
            }

            if (newG < 0) { //clamp the newG
                newG = 0;
            } else if (newG > 255) {
                newG = 255;
            }

            if (newB < 0) { //clamp the newB
                newB = 0;
            } else if (newB > 255) {
                newB = 255;
            }

            px.red = newR; //write the blended values back into the pixel
            px.green = newG;
            px.blue = newB;

            pixels[row][col] = px; //store the updated pixel back into the local grid
        }
    }
    image.setPixels(pixels); //after modifying, push it back into the image
}

std::string ColorFilter::name() const {
/**
 * @brief Returns the name of the filter
 *
 * @return A string of the form:
 *
 * `Color Filter [<red_channel>, <green_channel>, <blue_channel>]`
 *
 * @example If we have a red filter, this would return:
 * `Color Filter [255,0,0]`
 */
    std::string result = "Color Filter[";

    result = "Color Filter [";

    result += std::to_string(color_.red);
    result += ",";
    result += std::to_string(color_.green);
    result += ",";
    result += std::to_string(color_.blue);
    result += "]";
    //here we're just doing what the instrcutions want it to be formatted like
    return result;
}






