#include "Vector.hpp"
#include "Head.hpp"
#include <cmath>
#include <exception>

Vector3::~Vector3() {
}

float Vector3::x() const {
    return this->xx;
}

float Vector3::y() const {
    return this->yy;
}

float Vector3::z() const {
    return this->zz;
}

float Vector3::operator[](int i) const {
    switch (i) {
    case 0:
        return xx;
    case 1:
        return yy;
    case 2:
        return zz;
    default:
        throw std::runtime_error("Vector[] - 下标越界\n");
    }
}

float Vector3::len() const {
    return std::sqrt(xx * xx + yy * yy + zz * zz);
}

float Vector3::len_squared() const {
    return xx * xx + yy * yy + zz * zz;
}

Vector3 &Vector3::operator+=(const Vector3 &v) {
    xx += v.xx;
    yy += v.yy;
    zz += v.zz;
    return *this;
}

Vector3 &Vector3::operator-=(const Vector3 &v) {
    xx -= v.xx;
    yy -= v.yy;
    zz -= v.zz;
    return *this;
}

Vector3 &Vector3::operator*=(const float &t) {
    xx *= t;
    yy *= t;
    zz *= t;
    return *this;
}

Vector3 &Vector3::operator/=(const float &t) {
    xx /= t;
    yy /= t;
    zz /= t;
    return *this;
}

Vector3 Vector3::rand() {
    return Vector3(random_double(), random_double(), random_double()).normalized();
}

Vector3 Vector3::randLen(double len) {
    return rand() * len;
}

Vector3 Vector3::randOnHemisphere(Vector3 nor) {
    auto r = rand();
    if (dot(r, nor) > 0)
        return r;
    return -r;
}

Vector3 Vector3::randomXYunit() {
    while (true) {
        auto p = Vector3(random_double(-1, 1), random_double(-1, 1), 0);
        if (p.len_squared() < 1)
            return p;
    }
}

Vector3 Vector3::reflect(const Vector3 &n) const {
    // 返回按照n向量对称的向量。默认传入的n为单位向量。
    return *this - n * dot(*this, n) * 2;
}

Vector3 Vector3::refract(const Vector3 &n, double etai_over_etat) const {

    // 计算入射向量和法线向量之间的余弦值
    auto cos_theta = std::fmin(dot(-*this, n), 1.0);

    // 计算垂直于法线的折射向量分量
    Vector3 r_out_perp = etai_over_etat * (*this + cos_theta * n);

    // 计算平行于法线的折射向量分量
    double len_squared = r_out_perp.len_squared();
    Vector3 r_out_parallel = -sqrt(fabs(1.0 - len_squared)) * n;

    // 返回总的折射向量
    return r_out_perp + r_out_parallel;
}
