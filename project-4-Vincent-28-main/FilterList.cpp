#include "FilterList.hpp"
#include <iostream>
#include <sstream>
#include <stdexcept>

FilterList::FilterList() : filters_() {} //initialize vector to be empty

int FilterList::size() const { //return how many filters are stored
    return static_cast<int>(filters_.size());
}

std::vector<ImageFilter*> FilterList::getFilters() const {
    return filters_; //return a copy of the vector of ImageFilter*
}

void FilterList::addLastFilter(ImageFilter* f) {
    if(f == nullptr) { //if the pointer is nullptr we throw
        throw std::invalid_argument("Filter can't be nullptr");
    }
    //add filter to the end of list
    filters_.push_back(f); //then we pushback. store the pointer value itself
}

bool FilterList::removeLastFilter() {
    if(filters_.empty()) { //if filters_ is empty then there is nothing to remove so we return false
        return false;
    }
    filters_.pop_back();
    return true; //return true after a successful pop_back when we know that filters_ is not empty
}

std::string FilterList::toString() const {
    std::string result;

    if (filters_.empty()) { //if no filters we use the special empty format
        result += "FilterList:\n";
        result += "(no filters added)"; //this has to be exact cause it's weird
    } else {
        result += "FilterList\n";
        for (int i = 0; i < static_cast<int>(filters_.size()); i++) {
            ImageFilter* f = filters_[i]; //get the pointer at index i
            result += "  " + std::to_string(i + 1) + ". " + f->name() + "\n"; // This relies on polymorphism (virtual name()) from derived filters.
        }
    }

    return result; //we return the whole string
}

void FilterList::applyAll(ImageFile& img) const { //apply all filters in the list to an ImageFile
    for(std::size_t i = 0; i < filters_.size(); i++) {
        ImageFilter* f = filters_[i]; //get pointer to itth filter
        if(f != nullptr) { //if somehow, it is nullptr, we skip
            f -> apply(img); //call the filter's apply(img)
        }
    }
}