#include "ChannelSwapFilter.hpp"

ChannelSwapFilter::ChannelSwapFilter(Channel c1, Channel c2, double initialStrength)
    : ImageFilter(initialStrength)
    , c1_ { c1 }
    , c2_ { c2 } {
    };

void ChannelSwapFilter::setSwapChannels(Channel c1, Channel c2)
{
    c1_ = c1;
    c2_ = c2;
}

std::pair<Channel, Channel> ChannelSwapFilter::getSwapChannels() const
{
    return { c1_, c2_ };
}

std::string ChannelSwapFilter::name() const
{
    auto getChannelName = [](Channel c) {
        switch (c) {
        case RED:
            return "RED";
        case GREEN:
            return "GREEN";
        case BLUE:
            return "BLUE";
        }

        return "ERROR";
    };

    std::stringstream ss;
    ss << "ChannelSwapper ["
       << std::round(strength_ * 100) / 100
       << "] -- " << getChannelName(c1_) << " with " << getChannelName(c2_);
    return ss.str();
}

void ChannelSwapFilter::apply(ImageFile& image) const
{
    std::vector<std::vector<Pixel>> result = image.getPixels();
    applyToBuffer(
        [&](const Pixel& p) {
            std::vector<int> values = { p.red, p.green, p.blue };
            std::swap(values[c1_], values[c2_]);
            Pixel swapped { values[0], values[1], values[2] };
            return interpolate(swapped, p, strength_);
        },
        result);

    image.setPixels(result);
}

std::shared_ptr<ImageFilter> ChannelSwapFilter::clone() const
{
    return std::make_shared<ChannelSwapFilter>(*this);
}