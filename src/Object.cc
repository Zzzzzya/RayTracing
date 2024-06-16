#include "Object.hpp"
#include <cmath>
// 球
// 球的命中运算
bool Sphere::hit(const Ray &ray, Interval rayT, InterPoint &inter) const {
    const Sphere &sphere = *this;

    auto d = ray.dir();
    auto o = ray.orig();
    auto cen = center;
    auto R = radius;

    double a = dot(d, d);

    double b = 2 * (dot(o, d) - dot(d, cen));
    double c = dot(cen - o, cen - o) - R * R;

    // 保证有非负解
    double delta = b * b - (double)4.0 * a * c;
    if (delta < 0) {
        return false;
    }

    auto sqrt_delta = std::sqrt(delta);
    auto posT = (-b + sqrt_delta) * 0.5 * (1 / a);
    auto negT = (-b - sqrt_delta) * 0.5 * (1 / a);

    if (rayT.contains(negT)) {

        inter.t = negT;
        inter.loc = ray.at(inter.t);
        Point3 nor = (inter.loc - center) * (1 / radius);
        inter.set_face_normal(ray, nor);
        inter.met = met;
        inter.tex = tex;
        GetSphereUV(nor, inter.u, inter.v);
        return true;
    }

    if (rayT.contains(posT)) {

        inter.t = posT;
        inter.loc = ray.at(inter.t);
        auto nor = (inter.loc - center) * (1 / radius);
        inter.set_face_normal(ray, nor);
        inter.met = met;
        inter.tex = tex;
        GetSphereUV(nor, inter.u, inter.v);
        return true;
    }
    return false;
}

AABB Sphere::aabb() const {
    return _aabb;
}

void Sphere::GetSphereUV(const Point3 &p, double &u, double &v) {
    auto theta = acos(-p.y());
    auto phi = atan2(-p.z(), p.x()) + pi;

    u = phi / (2 * pi);
    v = theta / pi;
}

bool SphereMovingStraight::hit(const Ray &ray, Interval rayT, InterPoint &inter) const {

    auto d = ray.dir();
    auto o = ray.orig();
    auto cen = isMoving ? this->center(ray.time()) : start;
    auto R = radius;

    double a = dot(d, d);

    double b = 2 * (dot(o, d) - dot(d, cen));
    double c = dot(cen - o, cen - o) - R * R;

    // 保证有非负解
    double delta = b * b - (double)4.0 * a * c;
    if (delta < 0) {
        return false;
    }

    auto sqrt_delta = std::sqrt(delta);
    auto posT = (-b + sqrt_delta) * 0.5 * (1 / a);
    auto negT = (-b - sqrt_delta) * 0.5 * (1 / a);

    if (c < 0) {

        if (rayT.contains(posT)) {
            inter.t = posT;
            inter.loc = ray.at(inter.t);
            inter.set_face_normal(ray, (inter.loc - cen) * (1 / radius));
            inter.met = met;
            inter.tex = tex;
            Sphere::GetSphereUV(inter.loc - cen, inter.u, inter.v);
            return true;
        }
        return false;
    }

    if (rayT.contains(negT)) {
        inter.t = negT;
        inter.loc = ray.at(inter.t);
        inter.set_face_normal(ray, (inter.loc - cen) * (1 / radius));
        inter.met = met;
        inter.tex = tex;
        Sphere::GetSphereUV(inter.loc - cen, inter.u, inter.v);
        return true;
    }

    if (rayT.contains(posT)) {
        inter.t = posT;
        inter.loc = ray.at(inter.t);
        inter.set_face_normal(ray, (inter.loc - cen) * (1 / radius));
        inter.met = met;
        inter.tex = tex;
        Sphere::GetSphereUV(inter.loc - cen, inter.u, inter.v);
        return true;
    }
    return false;
}

AABB SphereMovingStraight::aabb() const {
    return _aabb;
}

Triangle::Triangle(const Point3 &x, const Point3 &y, const Point3 &z, shared_ptr<Material> met, shared_ptr<Texture> tex)
    : v(), met(met), tex(tex) {
    v[0] = x;
    v[1] = y;
    v[2] = z;
    E1 = v[1] - v[0];
    E2 = v[2] - v[0];
    setAABB();
}

bool Triangle::hit(const Ray &ray, Interval rayT, InterPoint &inter) const {
    auto o = ray.orig();
    auto d = ray.dir();

    auto S = o - v[0];
    auto S1 = cross(d, E2);
    auto S2 = cross(S, E1);
    auto s1e1 = 1 / dot(S1, E1);

    auto t = dot(S2, E2) * s1e1;
    auto b1 = dot(S1, S) * s1e1;
    auto b2 = dot(S2, d) * s1e1;

    if (rayT.surrounds(t) && b1 >= 0 && b2 >= 0 && b1 + b2 <= 1.0) {
        inter.t = t;
        inter.loc = ray.at(inter.t);
        auto nor = cross(E1, E2).normalized();
        inter.set_face_normal(ray, nor);
        inter.met = met;
        inter.tex = tex;

        return true;
    }
    return false;
}

AABB Triangle::aabb() const {
    return _aabb;
}

void Triangle::setAABB() {
    _aabb = AABB(AABB(v[0], v[1]), AABB(v[1], v[2]));
    if (_aabb.x.size() <= 0)
        _aabb.x = _aabb.x.expand(0.002);
    if (_aabb.y.size() <= 0)
        _aabb.y = _aabb.y.expand(0.002);
    if (_aabb.z.size() <= 0)
        _aabb.z = _aabb.z.expand(0.002);
}

Quad::Quad(const Point3 &x, const Vector3 &y, const Vector3 &z, shared_ptr<Material> met, shared_ptr<Texture> tex)
    : v(x), E1(y), E2(z), met(met), tex(tex) {
    setAABB();
}

bool Quad::hit(const Ray &ray, Interval rayT, InterPoint &inter) const {

    auto o = ray.orig();
    auto d = ray.dir();

    auto S = o - v;
    auto S1 = cross(d, E2);
    auto S2 = cross(S, E1);
    auto s1e1 = 1 / dot(S1, E1);

    auto t = dot(S2, E2) * s1e1;
    auto b1 = dot(S1, S) * s1e1;
    auto b2 = dot(S2, d) * s1e1;

    if (rayT.surrounds(t) && b1 >= 0 && b2 >= 0 && b1 <= 1.0 && b2 <= 1.0) {
        inter.t = t;
        inter.loc = ray.at(inter.t);
        auto nor = cross(E1, E2).normalized();
        inter.set_face_normal(ray, nor);
        inter.met = met;
        inter.tex = tex;

        return true;
    }
    return false;
}

AABB Quad::aabb() const {
    return _aabb;
}

void Quad::setAABB() {
    _aabb = AABB(AABB(v, v + E1), AABB(v + E1, v + E1 + E2));
    if (_aabb.x.size() <= 0)
        _aabb.x = _aabb.x.expand(0.002);
    if (_aabb.y.size() <= 0)
        _aabb.y = _aabb.y.expand(0.002);
    if (_aabb.z.size() <= 0)
        _aabb.z = _aabb.z.expand(0.002);
}
