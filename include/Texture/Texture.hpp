#pragma once

#include "Head.hpp"
#include "ImageRTW.hpp"
#include "Perlin.hpp"

class Texture {
  public:
    virtual ~Texture() = default;
    virtual ColorRGB value(double u, double v, const Point3 &p) const = 0;
};

class Solid : public Texture {

  public:
    Solid(const ColorRGB &albedo) : albedo(albedo) {
    }
    Solid(const double r, const double g, const double b) : albedo(ColorRGB(r, g, b)) {
    }
    virtual ColorRGB value(double u, double v, const Point3 &p) const override;

  private:
    ColorRGB albedo;
};

class Checker : public Texture {
  public:
    Checker(double scale, shared_ptr<Texture> even, shared_ptr<Texture> odd)
        : invScale(1 / scale), even(even), odd(odd) {
    }
    Checker(double scale, const ColorRGB &c1, const ColorRGB &c2)
        : invScale(1 / scale), even(make_shared<Solid>(c1)), odd(make_shared<Solid>(c2)) {
    }

    virtual ColorRGB value(double u, double v, const Point3 &p) const override;

  private:
    double invScale;
    shared_ptr<Texture> even;
    shared_ptr<Texture> odd;
};

class ImageTex : public Texture {
  public:
    ImageTex(const std::string filename);
    virtual ColorRGB value(double u, double v, const Point3 &p) const override;

  private:
    ImageRTW image;
};

class Noise : public Texture {
  public:
    Noise() {
    }
    Noise(double scale) : scale(scale) {
    }
    virtual ColorRGB value(double u, double v, const Point3 &p) const override;

  private:
    Perlin noise;
    double scale = 1;
};