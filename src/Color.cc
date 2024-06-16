#include "Color.hpp"
#include "Interval.hpp"

void write_color_rgb(std::ostream &out, const ColorRGB &color) {
    auto r = color.x();
    auto g = color.y();
    auto b = color.z();
    r = ColorLinear2Gama(r);
    g = ColorLinear2Gama(g);
    b = ColorLinear2Gama(b);
    const static Interval interval(0, 0.9999999);
    auto ir = int(interval.clamp(r) * 256);
    auto ig = int(interval.clamp(g) * 256);
    auto ib = int(interval.clamp(b) * 256);

    out << ir << " " << ig << " " << ib << "\n";
    return;
}

void write_color_rgb_f(std::fstream &out, const ColorRGB &color) {
    auto r = color.x();
    auto g = color.y();
    auto b = color.z();

    r = ColorLinear2Gama(r);
    g = ColorLinear2Gama(g);
    b = ColorLinear2Gama(b);

    const static Interval interval(0, 0.9999999);
    auto ir = int(interval.clamp(r) * 256);
    auto ig = int(interval.clamp(g) * 256);
    auto ib = int(interval.clamp(b) * 256);

    out << ir << " " << ig << " " << ib << "\n";
    return;
}

inline double ColorLinear2Gama(double linearColor) {
    static double gamma = 2.0;
    return linearColor > 0 ? std::pow(linearColor, 1 / gamma) : 0;
}
