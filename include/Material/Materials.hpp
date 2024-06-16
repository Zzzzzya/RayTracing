#pragma once
#include "Material.hpp"

// 遵循Lambertian漫反射
class Lambertian : public Material {
  private:
    ColorRGB albedo;

  public:
    Lambertian() : Material(), albedo() {
    }
    Lambertian(const ColorRGB &col) : Material(), albedo(col) {
    }
    virtual bool Scatter(const Ray &ray, const InterPoint &inter, ColorRGB &col, Ray &scattered) const override;
};

// 绝对镜面反射
class Glass : public Material {
  private:
    ColorRGB albedo;

  public:
    Glass(const ColorRGB &col) : Material(), albedo(col) {
    }
    virtual bool Scatter(const Ray &ray, const InterPoint &inter, ColorRGB &col, Ray &scattered) const override;
};

// fuzz镜面反射
class Metal : public Material {
  private:
    ColorRGB albedo;
    double fuzz;

  public:
    Metal(const ColorRGB &col, double fuzz) : Material(), albedo(col), fuzz(fuzz < 1 ? fuzz : 1) {
    }
    virtual bool Scatter(const Ray &ray, const InterPoint &inter, ColorRGB &col, Ray &scattered) const override;
};

// 介质 可折射
class Dielectric : public Material {
  private:
    double refraction_index;

  public:
    Dielectric(double refraction_index) : refraction_index(refraction_index) {
    }
    virtual bool Scatter(const Ray &ray, const InterPoint &inter, ColorRGB &col, Ray &scattered) const override;
    static double reflectance(double cosine, double ri);
};

// 光！
class LightDiffuse : public Material {
  public:
    virtual ColorRGB Emit(const InterPoint &inter) const override;
};