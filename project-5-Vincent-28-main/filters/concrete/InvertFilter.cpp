#include "InvertFilter.hpp"

std::string InvertFilter::name() const
{
    std::stringstream ss;
    ss << "Invert ["
       << std::round(strength_ * 100) / 100
       << "]";
    return ss.str();
}

void InvertFilter::apply(ImageFile& image) const
{
    std::vector<std::vector<Pixel>> result = image.getPixels();
    applyToBuffer(
        [&](const Pixel& p) {
            Pixel inv {
                MAX_CHANNEL_VALUE - p.red,
                MAX_CHANNEL_VALUE - p.green,
                MAX_CHANNEL_VALUE - p.blue
            };
            return interpolate(inv, p, strength_);
        },
        result);

    image.setPixels(result);
}

std::shared_ptr<ImageFilter> InvertFilter::clone() const
{
    return std::make_shared<InvertFilter>(*this);
}