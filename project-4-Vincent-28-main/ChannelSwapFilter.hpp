#pragma once

#include "ImageFilter.hpp"
#include <utility>

class ImageFile;

class ChannelSwapFilter : public ImageFilter {
private: 
    Channel c1_;
    Channel c2_;
public:
/**
 * Constructs a ChannelSwapFilter with two channels
 * to swap and an optional strength.
 *
 * @param c1 The first channel as a Channel Enum
 * @param c2 The second channel as a Channel Enum
 * @param strength A double between [0.0, 1.0] indicating overlay intensity. Defaults to 1.0 if omitted.
 */
    ChannelSwapFilter(Channel c1, Channel c2, double strength = 1.0);

/**
 * Sets the channels to be swapped by the filter.
 *
 * @param c1 The first channel to swap as a Channel enum
 * @param c2 The second channel to swap as a Channel enum
 */
    void setSwapChannels(Channel c1, Channel c2);

/**
 * Getter for swapped RGB channels
 *
 * @return A std::pair of Channels representing the swapped channels
 * @see Pairs in C++: https://www.geeksforgeeks.org/cpp/pair-in-cpp-stl/
 */
std::pair<Channel, Channel> getSwapChannels() const;

/**
 * @brief Swaps the values of the filter's channels for every pixel,
 * then blends with the original pixel by strength.
 *
 * @param image A (non-const) reference to the ImageFile
 *
 * @post The image's pixel data is modified such that for each pixel:
 * 1. The desired channel values are swapped
 * 2. The swapped channel version of the pixel color
 * is weighted by the filter strength and
 * the original pixel color by (1.0 - strength)
 */
void apply(ImageFile& image) const;

/**
 * @brief Returns the filter name and swap details
 * @return A string like "ChannelSwapper [RED, BLUE]"
 */
std::string name() const;
};