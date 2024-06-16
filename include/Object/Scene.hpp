#pragma once

#include "Head.hpp"
#include "Object.hpp"
#include <vector>

// 世界 -- Object的集合
class Scene : public hittable {
  private:
    AABB _aabb;

  public:
    std::vector<shared_ptr<hittable>> objects;

    Scene();
    Scene(shared_ptr<hittable> object);
    void add(shared_ptr<hittable> object);
    void clear();
    size_t size() const;
    virtual bool hit(const Ray &ray, Interval rayT, InterPoint &inter) const override;
    virtual AABB aabb() const override;
};