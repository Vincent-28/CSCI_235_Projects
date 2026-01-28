#include "ImageFilter.hpp"

ImageFilter::ImageFilter(double initialStrength) : strength_(initialStrength) {
    if(strength_ > 1.0) { //check if strength_ is greater than 1.0
        strength_ = 1.0; //set srength_ to 1.0 
    }
    else if(strength_ < 0.0) { //check if strength_ is less then 0
        strength_ = 0.0; //set strength_ to 0
    }
    else {
        strength_ = initialStrength; //
    }
}

void ImageFilter::setStrength(double strength) {
    if(strength > 1.0) { //check if strength_ is greater than 1.0
        strength_ = 1.0; //set srength_ to 1.0 
    }
    else if(strength < 0) { //check if strength_ is less then 0
        strength_ = 0.0; //set strength_ to 0
    }
    else {
        strength_ = strength; //set strength to the strength
    }
}

double ImageFilter::getStrength() const{
    return strength_; //return strength
}

