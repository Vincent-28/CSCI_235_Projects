#include "FilterList.hpp"

void FilterList::checkNotNull(ImageFilter* f)
{
    if (!f) {
        throw std::invalid_argument("Expected a filter, but received a nullptr instead.");
    }
}

void FilterList::addLastFilter(ImageFilter* f)
{
    checkNotNull(f);
    filters_.push_back(f);
}

bool FilterList::removeLastFilter()
{
    if (filters_.empty()) {
        return false;
    }

    filters_.pop_back();
    return true;
}

int FilterList::size() const
{
    return filters_.size();
}

std::vector<ImageFilter*> FilterList::getFilters() const
{
    return filters_;
}

void FilterList::applyAll(ImageFile& img) const
{
    for (const ImageFilter* p_filter : filters_) {
        // This will fail to compile if ImageFilter::apply is not marked const
        p_filter->apply(img);
    }
}

std::string FilterList::toString() const
{
    const std::string INDENT = "\t";
    std::stringstream ss;

    ss << "FilterList: " << std::endl;

    if (filters_.empty()) {
        ss << "(no filters added)" << std::endl;
        return ss.str();
    }

    int idx = 1;
    for (const ImageFilter* p_filter : filters_) {
        // This will fail to compile if ImageFilter::name is not marked const
        ss << INDENT << idx << ". " << p_filter->name() << std::endl;
        idx++;
    }

    return ss.str();
}