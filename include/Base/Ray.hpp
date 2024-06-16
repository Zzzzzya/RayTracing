#pragma once
#ifndef RAY_HPP
#define RAY_HPP

#include "Color.hpp"
#include "Vector.hpp"

class Ray {
  private:
    Point3 o;
    Vector3 d;
    double t; // 场景时间 用于动态模糊

  public:
    Ray() : o(0, 0, 0), d(1, 0, 0) {
    }
    Ray(const Point3 &oo, const Vector3 &dd) : o(oo), d(dd.normalized()), t(0) {
    }
    Ray(const Point3 &oo, const Vector3 &dd, double t) : o(oo), d(dd.normalized()), t(t) {
    }
    virtual ~Ray() {
    }

    Point3 at(const float &t) const {
        return o + d.normalized() * t;
    }

    inline const Point3 orig() const {
        return o;
    }

    inline const Vector3 dir() const {
        return d;
    }

    inline const double time() const {
        return t;
    }

    inline void setOrig(const Point3 &oo) {
        this->o = oo;
        return;
    }

    inline void setDir(const Vector3 &dir) {
        this->d = dir.normalized();
        return;
    }
};

#endif