#include "files/image/ImageFile.hpp"
#include "files/load/FileLoader.hpp"
#include "filters.hpp"

#define STB_IMAGE_IMPLEMENTATION
#include "external/stb_image.h"

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "external/stb_image_write.h"

int main()
{
    FileLoader loader;
    ImageFile f = loader.loadImageFile("amogus.png");

    InvertFilter* inv = new InvertFilter(1);
    ChannelSwapFilter* csf = new ChannelSwapFilter(RED, GREEN);

    FilterList fl;

    fl.addLastFilter(inv);
    fl.addLastFilter(csf);

    fl.applyAll(f);

    loader.saveImageFile(f, "purple_mogus");

    delete inv;
    delete csf;
    return 0;
}