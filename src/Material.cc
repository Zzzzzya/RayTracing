#include "Material.hpp"

bool Material::Scatter(const Ray &ray, const InterPoint &inter, ColorRGB &col, Ray &scattered) const {
    return false;
}

ColorRGB Material::Emit(const InterPoint &inter) const {
    return ColorRGB(0, 0, 0);
}
