#include "Vector.hpp"
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

inline void Vector3::normalize() {
    auto len = this->len();
    if (!len) {
        return;
    }
    xx /= len;
    yy /= len;
    zz /= len;
    return;
}

inline Vector3 Vector3::normalized() const {
    auto len = this->len();
    if (!len) {
        return Vector3();
    }

    return Vector3(xx / len, yy / len, zz / len);
}
