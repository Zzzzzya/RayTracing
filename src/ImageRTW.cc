#include "ImageRTW.hpp"
#define STB_IMAGE_IMPLEMENTATION
#define STBI_FAILURE_USERMSG
#include "stb_image.h"
ImageRTW::ImageRTW() {
}
ImageRTW::ImageRTW(const std::string &path) {
    auto filename = std::string(path);
    auto imagedir = getenv("RTW_IMAGES");

    // Hunt for the image file in some likely locations.
    if (imagedir && load(std::string(imagedir) + "/" + path))
        return;
    if (load(filename))
        return;
    if (load("images/" + filename))
        return;
    if (load("../images/" + filename))
        return;
    if (load("../../images/" + filename))
        return;
    if (load("../../../images/" + filename))
        return;
    if (load("../../../../images/" + filename))
        return;
    if (load("../../../../../images/" + filename))
        return;
    if (load("../../../../../../images/" + filename))
        return;
    std::cerr << "ERROR: Could not load image file '" << path << "'.\n";
}

ImageRTW::~ImageRTW() {
    if (bdata)
        delete[] bdata;
    STBI_FREE(fdata);
}

bool ImageRTW::load(const std::string &filename) {
    // Loads the linear (gamma=1) image data from the given file name. Returns true if the
    // load succeeded. The resulting data buffer contains the three [0.0, 1.0]
    // floating-point values for the first pixel (red, then green, then blue). Pixels are
    // contiguous, going left to right for the width of the image, followed by the next row
    // below, for the full height of the image.

    auto n = bytes_per_pixel; // Dummy out parameter: original components per pixel
    fdata = stbi_loadf(filename.c_str(), &image_width, &image_height, &n, bytes_per_pixel);
    if (fdata == nullptr)
        return false;

    bytes_per_scanline = image_width * bytes_per_pixel;
    convert_to_bytes();
    return true;
}

const unsigned char *ImageRTW::pixel_data(int x, int y) const {
    // Return the address of the three RGB bytes of the pixel at x,y. If there is no image
    // data, returns magenta.
    static unsigned char magenta[] = {255, 0, 255};
    if (bdata == nullptr)
        return magenta;

    x = clamp(x, 0, image_width);
    y = clamp(y, 0, image_height);

    return bdata + y * bytes_per_scanline + x * bytes_per_pixel;
}

void ImageRTW::convert_to_bytes() {
    // Convert the linear floating point pixel data to bytes, storing the resulting byte
    // data in the `bdata` member.

    int total_bytes = image_width * image_height * bytes_per_pixel;
    bdata = new unsigned char[total_bytes];

    // Iterate through all pixel components, converting from [0.0, 1.0] float values to
    // unsigned [0, 255] byte values.

    auto *bptr = bdata;
    auto *fptr = fdata;
    for (auto i = 0; i < total_bytes; i++, fptr++, bptr++)
        *bptr = float_to_byte(*fptr);
}