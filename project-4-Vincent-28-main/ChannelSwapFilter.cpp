#include "ChannelSwapFilter.hpp"
#include "ImageFile.hpp"
#include "ImageFilter.hpp"
#include "Pixel.hpp"
#include <string>
#include <vector>

std::string channelToString(Channel c) { //helper function (channel enum -> string) used to build the channel swapper
    if(c == RED) { //map based on enum values
        return "RED";
    }
    else if(c == GREEN) {
        return "GREEN";
    }
    else {
        return "BLUE";
    }
}

ChannelSwapFilter::ChannelSwapFilter(Channel c1, Channel c2, double strength) : ImageFilter(strength) /*call the base class so strength is clamped*/
    , c1_(c1), c2_(c2) /*store first and second channel to swap*/ {}

void ChannelSwapFilter::setSwapChannels(Channel c1, Channel c2) {
    c1_ = c1; //here we are just storing the 2 channels
    c2_ = c2;
}

std::pair<Channel, Channel> ChannelSwapFilter::getSwapChannels() const {
    return std::make_pair(c1_, c2_);
}
void ChannelSwapFilter::apply(ImageFile& image) const {
    double s = getStrength(); //get strength from base which was already changed

    std::vector<std::vector <Pixel>> pixels = image.getPixels(); //make a copy of the pixels

    int h = image.getHeight(); //number of rows
    int w = image.getWidth(); //number of columns

    for(int row = 0; row < h; row++) { //loop through every pixel
        for(int col = 0; col < w; col++) {
            Pixel original = pixels[row][col]; //we gonna save the original pixel

            Pixel swapped = original; //we're gonna start the swapped pixels as the originals and then we will change the channels

            int r = original.red; //these are termporary values that hold the original channels for easier reading
            int g = original.green;
            int b = original.blue;

            //here we are handling each swap case of c1_ and c2_
            if(c1_ == RED && c2_ == GREEN) {
                swapped.red = g;
                swapped.green = r;
                swapped.blue = b;
            }
            else if(c1_ == GREEN && c2_ == RED) {
                swapped.red = g;
                swapped.green = r;
                swapped.blue = b;
            }
            else if(c1_ == RED && c2_ == BLUE) {
                swapped.red = b;
                swapped.green = g;
                swapped.blue = r;
            }
            else if(c1_ == BLUE && c2_ == RED) {
                swapped.red = b;
                swapped.green = g;
                swapped.blue = r;
            }
            else if(c1_ == GREEN && c2_ == BLUE) {
                swapped.red = r;
                swapped.green = b;
                swapped.blue = g;
            }
            else if(c1_ == BLUE && c2_ == GREEN) {
                swapped.red = r;
                swapped.green = b;
                swapped.blue = g;
            }
            else { //if there is no real swap and somehow c1_ and c2_ are the same, we leave swapped as original
                swapped = original;
            }

            int newR = swapped.red * s + original.red * (1.0 - s); //use the formula here with the blended and original using the strength
            int newG = swapped.green * s + original.green * (1.0 - s);
            int newB = swapped.blue * s + original.blue * (1.0 - s);

            if(newR < 0) { //here we are clamping all values to be from [0,255]
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

            Pixel finalPixel; //now we want to write the final blended values back into the pixel
            finalPixel.red = newR;
            finalPixel.green = newG;
            finalPixel.blue = newB;

            pixels[row][col] = finalPixel; //store the updated pixel into the local grid
        }
    }
    image.setPixels(pixels);
}

std::string ChannelSwapFilter::name() const {
/**
 * @brief Returns the filter name and swap details
 * @return A string like "ChannelSwapper [RED, BLUE]"
 */
    std::string result = "ChannelSwapper [";
    result += channelToString(c1_);
    result += ", ";
    result += channelToString(c2_);
    result += "]";
    //here we're just doing what the instructions say and want it to be formatted like
    return result;
}