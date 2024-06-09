#pragma once
#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <fstream>

class Vector3 {
  public:
    float xx, yy, zz;

    Vector3() : xx(0), yy(0), zz(0) {
    }
    Vector3(float xx, float yy, float zz) : xx(xx), yy(yy), zz(zz) {
    }

    virtual ~Vector3();

    // 元素访问
    float x() const;
    float y() const;
    float z() const;
    float operator[](int i) const;
    float len() const;
    float len_squared() const;

    // 运算符重载-自运算
    Vector3 &operator+=(const Vector3 &v);
    Vector3 &operator-=(const Vector3 &v);
    Vector3 &operator*=(const float &t);
    Vector3 &operator/=(const float &t);

    // 归一
    inline void normalize();
    inline Vector3 normalized() const;
};

using Point3 = Vector3;

inline Vector3 operator+(const Vector3 &v1, const Vector3 &v2) {
    return Vector3(v1.xx + v2.xx, v1.yy + v2.yy, v1.zz + v2.zz);
}

inline Vector3 operator-(const Vector3 &v1, const Vector3 &v2) {
    return Vector3(v1.xx - v2.xx, v1.yy - v2.yy, v1.zz - v2.zz);
}

inline Vector3 operator*(const Vector3 &v, const float &t) {
    return Vector3(v.xx * t, v.yy * t, v.zz * t);
}

inline Vector3 operator*(const float &t, const Vector3 &v) {
    return Vector3(v.xx * t, v.yy * t, v.zz * t);
}

inline Vector3 operator/(const Vector3 &v, const float &t) {
    return Vector3(v.xx * (1 / t), v.yy * (1 / t), v.zz * (1 / t));
}

inline Vector3 cross(const Vector3 &v1, const Vector3 &v2) {
    return Vector3(v1.yy * v2.zz - v1.zz * v2.yy, v1.zz * v2.xx - v1.xx * v2.zz, v1.xx * v2.yy - v1.yy * v2.xx);
}

inline float dot(const Vector3 &v1, const Vector3 &v2) {
    return v1.xx * v2.xx + v1.yy * v2.yy + v1.zz * v2.zz;
}

inline std::ostream &operator<<(std::ostream &out, const Vector3 &v) {
    return out << v.xx << ' ' << v.yy << ' ' << v.zz;
}

#endif