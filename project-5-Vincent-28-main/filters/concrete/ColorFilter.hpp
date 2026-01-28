#pragma once

#include "filters/ImageFilter.hpp"

class ColorFilter : public ImageFilter {
private:
    int red_, green_, blue_;

public:
    /**
     * Constructs a ColorFilter with a given overlay color and strength.
     *
     * @param red The red channel value of the overlay color
     * @param green The green channel value of the overlay color
     * @param blue The blue channel value of the overlay color
     * @param strength A double between [0.0, 1.0] indicating overlay intensity. Defaults to 1.0 if omitted.
     */
    ColorFilter(int red, int green, int blue, double initialStrength = DEFAULT_STRENGTH);

    /**
     * @brief Applies the color overlay to each pixel in the image,
     * blended according to strength
     *
     * @param image A (non-const) reference to the ImageFile
     * @post The image's pixel data is modified such that:
     * The final pixel value is adjusted for the filter's strength by
     * averaging the ColorFilter's color by the filter strength and
     * averaging the original pixel color by (1.0 - strength)
     */
    virtual void apply(ImageFile& image) const override;

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
    std::string name() const override;

    /**
     * Sets the overlay color of the filter.
     *
     * @param r the new red channel value, clamped to [0,255]
     * @param g the new green channel value, clamped to [0,255]
     * @param b the new blue channel value, clamped to [0,255]
     */
    void setColor(int red, int green, int blue);

    /**
     * Gets the overlay color of the filter.
     *
     * @return The filter's red, green & blue color
     * as a Pixel object
     */
    Pixel getColor() const;

    /**
     * @brief Creates a deep copy of this ColorFilter.
     *
     * @return A std::shared_ptr<ImageFilter> pointing to the new ColorFilter copy.
     */
    virtual std::shared_ptr<ImageFilter> clone() const override;
};
