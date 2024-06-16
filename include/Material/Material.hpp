#pragma once
#include "Head.hpp"

class InterPoint;
class Material {
  public:
    virtual ~Material() = default;
    virtual bool Scatter(const Ray &ray, const InterPoint &inter, ColorRGB &col, Ray &scattered) const;
    virtual ColorRGB Emit(const InterPoint &inter) const;
};