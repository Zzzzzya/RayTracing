#pragma once
#ifndef OBJECT_HPP
#define OBJECT_HPP
#include "Intersection.hpp"

// 1. 球
class Sphere : public hittable {
  public:
    Sphere(const Point3 &p, double r) : center(p), radius(r), met(), tex() {
        auto rec = Vector3(radius, radius, radius);
        _aabb = AABB(center - rec, center + rec);
    }
    Sphere(const Point3 &p, double r, shared_ptr<Material> met) : center(p), radius(r), met(met), tex() {
        auto rec = Vector3(radius, radius, radius);
        _aabb = AABB(center - rec, center + rec);
    }
    Sphere(const Point3 &p, double r, shared_ptr<Material> met, shared_ptr<Texture> tex)
        : center(p), radius(r), met(met), tex(tex) {
        auto rec = Vector3(radius, radius, radius);
        _aabb = AABB(center - rec, center + rec);
    }
    Point3 center;
    double radius;
    shared_ptr<Material> met;
    shared_ptr<Texture> tex;
    AABB _aabb;

    virtual bool hit(const Ray &ray, Interval rayT, InterPoint &inter) const override;
    virtual AABB aabb() const override;

    static void GetSphereUV(const Point3 &p, double &u, double &v);
};

// 2. 直线往复运动的球
class SphereMovingStraight : public hittable {
  public:
    Point3 start;
    Point3 end;
    double radius;
    shared_ptr<Material> met;
    shared_ptr<Texture> tex;
    bool isMoving;
    AABB _aabb;

    SphereMovingStraight(Point3 start = Point3(0, 0, 0), Point3 end = Point3(0, 0, 0), double radius = 1.0,
                         shared_ptr<Material> met = make_shared<Material>(),
                         shared_ptr<Texture> tex = make_shared<Texture>(), bool isMoving = true)
        : start(start), end(end), radius(radius), met(met), tex(tex), isMoving(isMoving) {
        auto rec = Vector3(radius, radius, radius);
        auto _a = AABB(start - rec, start + rec);
        auto _b = AABB(end - rec, end + rec);
        _aabb = AABB(_a, _b);
    }

    inline Point3 center(double t) const {
        return start + (end - start) * t;
    }

    virtual bool hit(const Ray &ray, Interval rayT, InterPoint &inter) const override;
    virtual AABB aabb() const override;
};

// 3. 三角形
class Triangle : public hittable {
  public:
    Point3 v[3];
    shared_ptr<Material> met;
    shared_ptr<Texture> tex;
    AABB _aabb;
    Vector3 E1;
    Vector3 E2;

    Triangle(const Point3 &x, const Point3 &y, const Point3 &z, shared_ptr<Material> met = shared_ptr<Material>(),
             shared_ptr<Texture> tex = shared_ptr<Texture>());
    virtual bool hit(const Ray &ray, Interval rayT, InterPoint &inter) const override;
    virtual AABB aabb() const override;
    void setAABB();
};

// 4. 平行四边形
class Quad : public hittable {
  public:
    Point3 v;

    shared_ptr<Material> met;
    shared_ptr<Texture> tex;
    AABB _aabb;
    Vector3 E1;
    Vector3 E2;

    Quad(const Point3 &x, const Vector3 &y, const Vector3 &z, shared_ptr<Material> met = shared_ptr<Material>(),
         shared_ptr<Texture> tex = shared_ptr<Texture>());
    virtual bool hit(const Ray &ray, Interval rayT, InterPoint &inter) const override;
    virtual AABB aabb() const override;
    void setAABB();
};

// 5. 立方体
class Scene;
shared_ptr<Scene> box(const Point3 &a, const Point3 &b, shared_ptr<Material> mat);
#endif