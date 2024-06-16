#include "AABB.hpp"

AABB operator+(const AABB &bbox, const Vector3 &offset) {
    return AABB(bbox.x + offset.x(), bbox.y + offset.y(), bbox.z + offset.z());
}

AABB operator+(const Vector3 &offset, const AABB &bbox) {
    return bbox + offset;
}