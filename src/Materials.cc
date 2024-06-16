#include "Materials.hpp"
#include "Head.hpp"
#include "Intersection.hpp"
#include "Texture.hpp"

bool Lambertian::Scatter(const Ray &ray, const InterPoint &inter, ColorRGB &col, Ray &scattered) const {
    // Lambertian的漫反射 - 跟法线夹角的cos值成正比。
    Vector3 dir;

    // 防止生成向量刚好和法线反向 +后为0向量

    dir = Vector3::rand() + inter.nor;
    if (dir.isZero())
        dir = inter.nor + Vector3::rand();
    scattered = Ray(inter.loc, dir, ray.time());
    col = inter.tex ? inter.tex->value(inter.u, inter.v, inter.loc) : albedo;

    return true;
}

bool Glass::Scatter(const Ray &ray, const InterPoint &inter, ColorRGB &col, Ray &scattered) const {
    // 纯镜面反射
    Vector3 dir = ray.dir().reflect(inter.nor);
    scattered = Ray(inter.loc, dir, ray.time());
    col = inter.tex ? inter.tex->value(inter.u, inter.v, inter.loc) : albedo;
    return true;
}

bool Metal::Scatter(const Ray &ray, const InterPoint &inter, ColorRGB &col, Ray &scattered) const {
    // 金属的反射 ---> 是 fuzz + 镜面反射！

    Vector3 dir = ray.dir().reflect(inter.nor).normalized() + Vector3::rand() * fuzz;
    scattered = Ray(inter.loc, dir, ray.time());
    col = inter.tex ? inter.tex->value(inter.u, inter.v, inter.loc) : albedo;
    return dot(dir, inter.nor) > 0;
}

bool Dielectric::Scatter(const Ray &ray, const InterPoint &inter, ColorRGB &col, Ray &scattered) const {
    col = inter.tex ? inter.tex->value(inter.u, inter.v, inter.loc) : ColorRGB(1.0, 1.0, 1.0); // 完全不吸收能量。
    double ri = inter.front_face ? (1.0 / refraction_index) : refraction_index;
    auto dir = ray.dir().normalized();

    double cos_theta = fmin(dot(-dir, inter.nor), 1.0);
    double sin_theta = sqrt(1.0 - cos_theta * cos_theta);

    bool cannot_refract = ri * sin_theta > 1.0;
    Vector3 direction;

    if (cannot_refract) //|| reflectance(cos_theta, ri) > random_double()
        direction = dir.reflect(inter.nor);
    else
        direction = refract2(dir, inter.nor.normalized(), ri);

    scattered = Ray(inter.loc, direction, ray.time());

    return true;
}

double Dielectric::reflectance(double cosine, double ri) {
    double R0 = std::pow((1.0 - ri) / (1.0 + ri), 2);

    return R0 + (1.0 - R0) * std::pow((1 - cosine), 5);
}

ColorRGB LightDiffuse::Emit(const InterPoint &inter) const {
    return inter.tex->value(inter.u, inter.v, inter.loc);
}
