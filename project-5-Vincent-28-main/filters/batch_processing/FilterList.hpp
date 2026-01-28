#pragma once

#include "files/image/ImageFile.hpp"
#include "filters/ImageFilter.hpp"
#include <sstream>
#include <vector>

class FilterList {
private:
    std::vector<ImageFilter*> filters_ = {};
    void checkNotNull(ImageFilter* filter);

public:
    /**
     * @brief Adds a filter to the end of the filter list.
     *
     * @param f A pointer to the ImageFilter to add
     * @throws std::invalid_argument Thrown if the provided filter pointer is nullptr.
     *
     * @note The pointer should be used as-is; no copies should be made.
     */
    void addLastFilter(ImageFilter* filter);

    /**
     * @brief Removes the last filter from the list.
     *
     * @return Returns true if a filter was successfully removed, otherwise returns false if the list was already empty.
     *
     * @note The caller is expected to manage the de-allocation of the pointer.
     * This does not release the memory of removed filter
     */
    bool removeLastFilter();

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
     * @brief Applies all filters in the list to an ImageFile in the order
     * they were added (e.g. first to add => first applied, etc.)
     *
     * @param img A (non-const) reference to an ImageFile to apply the filters to
     */
    void applyAll(ImageFile& img) const;

    /**
     * @brief Generates a string representation of the filter list of the form:
     *
     * FilterList
     *  1. <filter 1>::name()
     *  ...
     *  N. <filter N>::name()
     *
     * @return A std::string containing the names of all the filters in the list,
     * each on a new line and indented (for readability)
     *
     * @example If we had a FilterList, where we add an InvertFilter first, and then
     * a red ColorFilter, we might have something like:
     *
     * FilterList
     *  1. Invert Filter
     *  2. Color Filter [255,0,0]
     */
    std::string toString() const;
};