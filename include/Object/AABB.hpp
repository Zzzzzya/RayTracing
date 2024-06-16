#pragma once

#include "Head.hpp"

class AABB {
  public:
    // 三个维度上的包围盒
    Interval x;
    Interval y;
    Interval z;

    AABB() : x(), y(), z() {
    }
    AABB(const Interval &x, const Interval &y, const Interval &z) : x(x), y(y), z(z) {
    }
    AABB(const Point3 &a, const Point3 &b) {
        x = a.x() < b.x() ? Interval(a.x(), b.x()) : Interval(b.x(), a.x());
        y = a.y() < b.y() ? Interval(a.y(), b.y()) : Interval(b.y(), a.y());
        z = a.z() < b.z() ? Interval(a.z(), b.z()) : Interval(b.z(), a.z());
    }
    AABB(const AABB &a, const AABB &b) {
        x = Interval(a.x, b.x);
        y = Interval(a.y, b.y);
        z = Interval(a.z, b.z);
    }

    const Interval &axisInterval(int n) const noexcept {
        if (n == 0)
            return x;
        if (n == 1)
            return y;
        return z;
    }

    // 判别光线是否击中该盒子
    bool hit(const Ray &ray, Interval rayT) const {
        Interval &cur = rayT;
        auto ori = ray.orig();
        auto dir = ray.dir();

        for (int i = 0; i < 3; i++) {
            const auto &curInterval = this->axisInterval(i);
            double overed = 1 / (dir[i]);

            auto tmin = (curInterval.min - ori[i]) * overed;
            auto tmax = (curInterval.max - ori[i]) * overed;
            if (tmin > tmax) {
                std::swap(tmin, tmax);
            }

            cur.min = std::max(cur.min, tmin);
            cur.max = std::min(cur.max, tmax);

            if (cur.min >= cur.max)
                return false;
        }
        return true;
    }
};