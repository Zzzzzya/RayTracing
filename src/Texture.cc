#include "Texture.hpp"

ColorRGB Solid::value(double u, double v, const Point3 &p) const {
    return albedo;
}

ColorRGB Checker::value(double u, double v, const Point3 &p) const {
    // 网格状
    int xInt = std::floor(p.x() * invScale);
    int yInt = std::floor(p.y() * invScale);
    int zInt = std::floor(p.z() * invScale);

    auto res = (xInt + yInt + zInt) % 2;
    if (res)
        return odd->value(u, v, p);
    return even->value(u, v, p);
}

ImageTex::ImageTex(const std::string filename) : image(filename) {
}
ColorRGB ImageTex::value(double u, double v, const Point3 &p) const {
    if (image.height() <= 0)
        return ColorRGB(0, 0, 1);

    u = Interval(0, 1).clamp(u);
    v = 1.0 - Interval(0, 1).clamp(v);

    auto i = int(u * image.width());
    auto j = int(v * image.height());
    auto pixel = image.pixel_data(i, j);

    auto color_scale = 1.0 / 255.0;
    return ColorRGB(color_scale * pixel[0], color_scale * pixel[1], color_scale * pixel[2]);
}

ColorRGB Noise::value(double u, double v, const Point3 &p) const {
    return ColorRGB(.5, .5, .5) * (1 + sin(scale * p.z() + 10 * noise.turb(p, 7)));
}
