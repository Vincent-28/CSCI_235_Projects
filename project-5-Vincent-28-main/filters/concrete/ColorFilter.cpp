#include "ColorFilter.hpp"

ColorFilter::ColorFilter(int r, int g, int b, double strength)
    : ImageFilter(strength)
    , red_ { std::clamp(r, 0, 255) }
    , green_ { std::clamp(g, 0, 255) }
    , blue_ { std::clamp(b, 0, 255) }
{
}

std::string ColorFilter::name() const
{
    std::stringstream ss;
    ss << "Color Overlay ["
       << std::round(strength_ * 100) / 100
       << "] -- Red: " << red_ << " Green: " << green_ << " Blue: " << blue_;
    return ss.str();
}

void ColorFilter::apply(ImageFile& image) const
{
    std::vector<std::vector<Pixel>> result = image.getPixels();
    Pixel overlay { red_, green_, blue_ };
    applyToBuffer([&](const Pixel& p) { return interpolate(overlay, p, strength_); }, result);

    image.setPixels(result);
}

void ColorFilter::setColor(int r, int g, int b)
{
    red_ = std::clamp(r, 0, 255);
    green_ = std::clamp(g, 0, 255);
    blue_ = std::clamp(b, 0, 255);
}

Pixel ColorFilter::getColor() const
{
    return { red_, green_, blue_ };
}

std::shared_ptr<ImageFilter> ColorFilter::clone() const
{
    return std::make_shared<ColorFilter>(*this);
}