#pragma once

#include "AABB.hpp"
#include "Head.hpp"

class Material;
class Texture;

// 交点
class InterPoint {
  public:
    Point3 loc;
    Vector3 nor;
    double t;
    bool front_face;
    shared_ptr<Material> met;
    shared_ptr<Texture> tex;
    double u;
    double v;

  public:
    void set_face_normal(const Ray &r, const Vector3 &outward_normal);
    ColorRGB Emit() const;
};

// 物体基类
class hittable {
  public:
    virtual ~hittable() = default;

    /*
   hit ： 判别一个光线和该物体是否相交 ---> 要求 t在hitTmin和hitTmax之间。 并且在hit中更新带出inter的信息。
   */
    virtual bool hit(const Ray &ray, Interval rayT, InterPoint &inter) const = 0;
    virtual AABB aabb() const = 0;
};
