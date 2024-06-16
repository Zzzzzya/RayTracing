#include "Intersection.hpp"
#include "Material.hpp"

void InterPoint::set_face_normal(const Ray &r, const Vector3 &outward_normal) {
    // 为了保证光线从物体内部发出时，能够正确的渲染物体的内部，因此要对法线进行动态的转换
    // outward_normal是根据计算，从内部指向外部的法线。传入时默认已单位化。

    front_face = dot(r.dir(), outward_normal) < 0;
    nor = front_face ? outward_normal : (-outward_normal);
}

ColorRGB InterPoint::Emit() const {
    return met->Emit(*this);
}
