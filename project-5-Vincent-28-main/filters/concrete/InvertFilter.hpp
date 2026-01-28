#pragma once

#include "filters/ImageFilter.hpp"

class InvertFilter : public ImageFilter {
private:
    const static int MAX_CHANNEL_VALUE = 255;

public:
    using ImageFilter::ImageFilter;

    /**
     * @brief Inverts the pixel colors of the given image, adjusting for the filter's strength
     *
     * @param image A (non-const) reference to the ImageFile object to which the filter will be applied.
     *
     * @post The image's pixel data is modified such that:
     * 1. The pixel colors are inverted using (255 - channel_value)
     * 2. The final pixel value is adjusted for the filter's strength by
     * averaging the inverted pixel color by the filter strength and
     * averaging the original pixel color by (1.0 - strength)
     *
     * @example See specs above for an example.
     */
    virtual void apply(ImageFile& image) const override;

    /**
     * @brief Returns the name of the filter, that is "Invert Filter"
     * @return A string representing the name of the filter.
     */
    std::string name() const override;

    /**
     * @brief Creates a deep copy of this InvertFilter.
     *
     * @return A std::shared_ptr<ImageFilter> pointing to the new InvertFilter copy.
     */
    virtual std::shared_ptr<ImageFilter> clone() const override;
};
