#pragma once

#include "files/image/ImageFile.hpp"
#include "files/image/Pixel.hpp"
#include <algorithm>
#include <cmath>
#include <functional>
#include <memory>
#include <sstream>

enum Channel {
    RED = 0,
    GREEN = 1,
    BLUE = 2
};

class ImageFilter {
protected:
    /**
     * Interpolates between two pixels using a specified ratio.
     *
     * @param p1 the first pixel
     * @param p2 the second pixel
     * @param p1_ratio the weight of the first pixel (between 0.0 and 1.0)
     * @return the interpolated pixel
     */
    static Pixel interpolate(Pixel p1, Pixel p2, double p1_ratio);
    static void applyToBuffer(std::function<Pixel(const Pixel& p)> func, std::vector<std::vector<Pixel>>& buffer);

    const static double DEFAULT_STRENGTH;
    double strength_;

public:
    /**
     * Constructs an ImageFilter with a given initial strength.
     *
     * @param initialStrength the initial filter strength, clamped between 0.0 and 1.0
     */
    ImageFilter(double initialStrength = DEFAULT_STRENGTH);

    /**
     * Sets the strength of the filter.
     *
     * @param strength the new filter strength, clamped between 0.0 and 1.0
     */
    void setStrength(double strength);

    /**
     * Getter for the strength_ member
     */
    double getStrength() const;

    /**
     * @brief Applies the filter to the given image.
     * @param image A reference to the ImageFile object to which the filter will be applied.
     * @post The image's pixel data is modified to reflect the applied filter effect.
     */
    virtual void apply(ImageFile& image) const = 0;

    /**
     * @brief Returns the name of the filter.
     * @return A string representing the name of the filter.
     */
    virtual std::string name() const = 0;

    /**
     * @brief Creates and returns a deep copy of this filter object.
     *
     * This virtual "copy constructor" is used to create a new filter
     * instance of the correct concrete type (e.g., BlurFilter)
     * when only a base ImageFilter reference is available.
     *
     * @return A std::shared_ptr<ImageFilter> pointing to the new copy.
     */
    virtual std::shared_ptr<ImageFilter> clone() const = 0;

    virtual ~ImageFilter() = default;
};
