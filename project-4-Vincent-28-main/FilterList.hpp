#pragma once

#include <vector>
#include <string>
#include <stdexcept>
#include "ImageFilter.hpp"
#include "ImageFile.hpp"
#include "Pixel.hpp"

class FilterList {
private:
    std::vector<ImageFilter*> filters_;

public:
/**
 * Default Constructor -- you may initialize whatever members you deem necessary
 *
 * @note Hint: I only have one private member variable; reference the getters.
 */
    FilterList();

/**
 * @brief Gets the number of filters currently in the list.
 *
 * @return The number of filters in the list as an integer
 */
    int size() const;

/**
 * @brief Returns a list of all of the ImageFilters pointers
 * within the FilterList.
 *
 * @return A std::vector<ImageFilter*> containing all the filters
 */
    std::vector<ImageFilter*> getFilters() const;

/**
 * @brief Adds a filter to the end of the filter list.
 *
 * @param f A pointer to the ImageFilter to add
 * @throws std::invalid_argument Thrown if the provided filter pointer is nullptr.
 *
 * @note Don't make a copy of the dereferenced pointer -- just use the pointer value/address itself
 */
    void addLastFilter(ImageFilter* f);

/**
 * @brief Removes the last filter from the list.
 *
 * @return Returns true if a filter was successfully removed,
 * otherwise returns false if the list was empty.
 *
 * @note The caller is expected to manage the de-allocation of the pointer.
 * i.e. This function does not release the memory of the removed filter
 */
bool removeLastFilter();

/**
 * @brief Generates a string representation of the filter list of the form:
 *
 * FilterList
 *  1. <filter 1>::name()
 *  ...
 *  N. <filter N>::name()
 *
 * or if no filters have been added:
 *
 * FilterList:
 *    (no filters added)
 *
 *
 * @return A string containing whose first line is "FilterList", and
 * names of all the filters in the list, each numbered on a new line and indented (for readability),
 * as seen in the format above.
 *
 * @example If we had a FilterList, where we add an InvertFilter first, and then
 * a red ColorFilter, we might have something like:
 *
 * FilterList
 *  1. Invert Filter
 *  2. Color Filter [255,0,0]
 */
std::string toString() const;

/**
 * @brief Applies all filters in the list to an ImageFile in the order
 * they were added (e.g. first to add => first applied, etc.)
 *
 * @param img A (non-const) reference to an ImageFile to apply the filters to
 */
void applyAll(ImageFile& img) const;
};