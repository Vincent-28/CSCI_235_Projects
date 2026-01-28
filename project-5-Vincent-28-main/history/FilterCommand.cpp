#include "history/FilterCommand.hpp"

#include <string>
#include <vector>

FilterCommand::FilterCommand(ImageFile& imageFile, const ImageFilter& filter) : image_file_(imageFile), applied_filter_ { filter.clone() }, before_pixels_(), after_pixels_() {}

void FilterCommand::execute() {
    before_pixels_ = image_file_.getPixels(); //save the pixels before applying the filter

    applied_filter_->apply(image_file_); //apply the filter to the image

    after_pixels_ = image_file_.getPixels(); //store the after state of the image
}

void FilterCommand::undo() {
    image_file_.setPixels(before_pixels_); //here we restore the "before" pixels into the ImageFile which undoes the effect of the filter
}

void FilterCommand::redo() {
    image_file_.setPixels(after_pixels_); //this restores the after pixels by re-applying the saved result of execute()
}

ImageFile& FilterCommand::getModifiedImage() {
    return image_file_; //returning the ImageFile that this command modifies
}

std::shared_ptr<ImageFilter> FilterCommand::getAppliedFilter() const {
    return applied_filter_; //returning the shared_ptr<ImageFilter> describing the applied filter.
}

std::string FilterCommand::toString() const {
    std::string filter_name = applied_filter_->name(); //getting the filter's name
    std::string file_name = image_file_.getFilename(); //getting the image file's filename

    return filter_name + " --> " + file_name; //the final string in the correct format
}





