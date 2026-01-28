#include "filters/ImageFilter.hpp"
#include "filters/batch_processing/FilterList.hpp"
#include "filters/concrete/ChannelSwapFilter.hpp"
#include "filters/concrete/ColorFilter.hpp"
#include "filters/concrete/InvertFilter.hpp"

// This is called a "barrel" (at least in like,, javascript).
// TLDR you can just `#include filters.hpp` in your main file
// to include all the filters instead of importing each of the files individually.