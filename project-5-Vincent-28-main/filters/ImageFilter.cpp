#include "ImageFilter.hpp"

const double ImageFilter::DEFAULT_STRENGTH = 1.0;

ImageFilter::ImageFilter(double initialStrength)
    : strength_ {
        std::clamp(initialStrength, 0.0, 1.0)
    }
{
}

double ImageFilter::getStrength() const
{
    return strength_;
}

void ImageFilter::setStrength(double strength)
{
    strength_ = std::clamp(strength, 0.0, 1.0);
}

Pixel ImageFilter::interpolate(Pixel p1, Pixel p2, double p1_ratio)
{
    Pixel result;
    double complement = 1 - p1_ratio;

    result.red = (p1.red * p1_ratio + p2.red * complement);
    result.green = (p1.green * p1_ratio + p2.green * complement);
    result.blue = (p1.blue * p1_ratio + p2.blue * complement);
    return result;
}

void ImageFilter::applyToBuffer(std::function<Pixel(const Pixel& p)> func, std::vector<std::vector<Pixel>>& buffer)
{
    for (auto& row : buffer) {
        for (auto& pixel : row) {
            pixel = func(pixel);
        }
    }
}