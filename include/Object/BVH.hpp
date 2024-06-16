#pragma once

#include "Head.hpp"
#include "Intersection.hpp"
#include "Scene.hpp"

class bvh : public hittable {
  public:
    shared_ptr<hittable> left;
    shared_ptr<hittable> right;
    AABB _aabb;

    bvh(Scene &sce);
    bvh(std::vector<shared_ptr<hittable>> objects, int begin, int end);

    bool hit(const Ray &ray, Interval rayT, InterPoint &inter) const override;
    AABB aabb() const override {
        return _aabb;
    }

    static bool compare(const shared_ptr<hittable> a, const shared_ptr<hittable> b, int axisIndex) {
        auto aAxisInterval = a->aabb().axisInterval(axisIndex);
        auto bAxisInterval = b->aabb().axisInterval(axisIndex);
        return (aAxisInterval.min + aAxisInterval.max) < (bAxisInterval.min + bAxisInterval.max);
    }

    static bool comparex(const shared_ptr<hittable> a, const shared_ptr<hittable> b) {
        return compare(a, b, 0);
    }

    static bool comparey(const shared_ptr<hittable> a, const shared_ptr<hittable> b) {
        return compare(a, b, 1);
    }

    static bool comparez(const shared_ptr<hittable> a, const shared_ptr<hittable> b) {
        return compare(a, b, 2);
    }
};