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

class translate : public hittable {
  public:
    translate(shared_ptr<hittable> object, const Vector3 &offset) : object(object), offset(offset) {
        bbox = object->aabb() + offset;
    }
    bool hit(const Ray &r, Interval ray_t, InterPoint &rec) const override;
    AABB aabb() const override {
        return bbox;
    }

  private:
    shared_ptr<hittable> object;
    Vector3 offset;
    AABB bbox;
};

class rotate_y : public hittable {
  public:
    rotate_y(shared_ptr<hittable> object, double angle);
    bool hit(const Ray &r, Interval ray_t, InterPoint &rec) const override;
    AABB aabb() const override {
        return bbox;
    }

  private:
    shared_ptr<hittable> object;
    double sin_theta;
    double cos_theta;
    AABB bbox;
};