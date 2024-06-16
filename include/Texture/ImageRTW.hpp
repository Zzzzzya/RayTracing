#pragma once
#ifdef _MSC_VER
#pragma warning(push, 0)
#endif

#include <cstdlib>
#include <iostream>
#include <string>

class ImageRTW {
  public:
    ImageRTW();
    ImageRTW(const std::string &path);

    ~ImageRTW();
    int width() const {
        return (fdata) ? image_width : 0;
    }

    int height() const {
        return (fdata) ? image_height : 0;
    }

    bool load(const std::string &filename);
    const unsigned char *pixel_data(int x, int y) const;

  private:
    const int bytes_per_pixel = 3;
    float *fdata = nullptr;         // Linear floating point pixel data
    unsigned char *bdata = nullptr; // Linear 8-bit pixel data
    int image_width = 0;
    int image_height = 0;
    int bytes_per_scanline = 0;

    static int clamp(int x, int low, int high) {
        if (x < low)
            return low;
        if (x > high)
            return high - 1;
        return x;
    }

    static unsigned char float_to_byte(float value) {
        if (value <= 0.0)
            return 0;
        if (value >= 1)
            return 255;
        return static_cast<unsigned char>(256.0 * value);
    }

    void convert_to_bytes();
};

#ifdef _MSC_VER
#pragma warning(pop)
#endif