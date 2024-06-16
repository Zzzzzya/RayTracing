#pragma once
#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <fstream>

using std::cos;
using std::sin;

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
    float &operator[](int i);
    float len() const;
    float len_squared() const;

    // 运算符重载-自运算
    Vector3 &operator+=(const Vector3 &v);
    Vector3 &operator-=(const Vector3 &v);
    Vector3 &operator*=(const float &t);
    Vector3 &operator/=(const float &t);

    // 归一
    inline void normalize() {
        auto len = this->len();
        if (!len) {
            return;
        }
        xx /= len;
        yy /= len;
        zz /= len;
        return;
    }

    inline Vector3 normalized() const {
        auto len = this->len();
        if (!len) {
            return Vector3();
        }

        return Vector3(xx / len, yy / len, zz / len);
    }

    // 随机生成一个单位向量
    static Vector3 rand();

    static Vector3 rand(double min, double max);

    static Vector3 randLen(double len);

    static Vector3 randOnHemisphere(Vector3 nor);

    static Vector3 randomXYunit();

    // 判断向量是否接近与0向量
    inline bool isZero() const {
        auto s = 1e-8;
        return std::fabs(xx) < s && std::fabs(yy) < s && std::fabs(zz) < s;
    }

    // 给出对称 || 反射向量
    Vector3 reflect(const Vector3 &) const;

    // 给出折射 向量
    Vector3 refract(const Vector3 &nor, double etai_over_etat) const;
};

using Point3 = Vector3;

inline Vector3 operator-(const Vector3 &v) {
    return Vector3(-v.xx, -v.yy, -v.zz);
}

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

inline Vector3 productElement(const Vector3 &v1, const Vector3 &v2) {
    return Vector3(v1.xx * v2.xx, v1.yy * v2.yy, v1.zz * v2.zz);
}

inline std::ostream &operator<<(std::ostream &out, const Vector3 &v) {
    return out << v.xx << ' ' << v.yy << ' ' << v.zz;
}

inline Vector3 refract2(const Vector3 &uv, const Vector3 &n, double etai_over_etat) {
    auto cos_theta = fmin(dot(-uv, n), 1.0);
    Vector3 r_out_perp = etai_over_etat * (uv + cos_theta * n);
    Vector3 r_out_parallel = -sqrt(fabs(1.0 - r_out_perp.len_squared())) * n;
    return r_out_perp + r_out_parallel;
}

Vector3 rotx(double alpha, Vector3 a);
Vector3 roty(double alpha, Vector3 a);
Vector3 rotz(double alpha, Vector3 a);
#endif