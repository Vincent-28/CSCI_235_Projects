#pragma once

#include <memory>
#include <vector>
#include <string>

#include "history/Command.hpp"
#include "filters/ImageFilter.hpp"
#include "files/image/ImageFile.hpp"
#include "files/image/Pixel.hpp"

class FilterCommand : public Command {
private:
    //A reference to the ImageFile being modified (NOT A COPY).
    ImageFile& image_file_; 

    ///// Add this to your .hpp
    /// Yes it is const -- because we are only assigning the filter pointer once and won't repoint it to some other object.
    const std::shared_ptr<ImageFilter> applied_filter_;

    //Two 2D Pixel vectors to store the "before" and "after" states
    std::vector<std::vector<Pixel>> before_pixels_;
    std::vector<std::vector<Pixel>> after_pixels_;

public:
    FilterCommand(ImageFile& imageFile, const ImageFilter& filter);

/**
 * @brief Executes the filter application.
 * @post
 * 1. The pixel data of the image's state *before* filtering is stored.
 * 2. The filter is applied to the image passed in the constructor (and modifying that original image object directly)
 * 3. (depending on implementation) The pixel data of the image's *after* filtering is stored.
 */
    void execute() override;

/**
 * @brief Undoes the filter application.
 * @post The modified Image's pixels are restored to the pixel data before the filter was applied.
 */
    void undo() override;

/**
 * @brief Re-applies the filter application.
 * @post The modified Image's pixels are restored the pixel data after the filter was applied.
 */
    void redo() override;

/**
 * @brief Gets the image file modified by this command.
 * @return The ImageFile object.
 */
    ImageFile& getModifiedImage();

/**
 * @brief Gets the filter that was applied by this command.
 * @return A shared_ptr to the ImageFilter.
 */
    std::shared_ptr<ImageFilter> getAppliedFilter() const;

/**
 * @brief Generates a string representation of the command.
 * @return A string in the format: "<Filter Name> --> <Filename>"
 */
    std::string toString() const override;
};