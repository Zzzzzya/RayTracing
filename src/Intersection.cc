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

bool translate::hit(const Ray &r, Interval ray_t, InterPoint &rec) const {
    // Move the ray backwards by the offset
    Ray offset_r(r.orig() - offset, r.dir(), r.time());

    // Determine whether an intersection exists along the offset ray (and if so, where)
    if (!object->hit(offset_r, ray_t, rec))
        return false;

    // Move the intersection point forwards by the offset
    rec.loc += offset;

    return true;
}

rotate_y::rotate_y(shared_ptr<hittable> object, double angle) : object(object) {
    auto radians = d2r(angle);
    sin_theta = sin(radians);
    cos_theta = cos(radians);
    bbox = object->aabb();

    Point3 min(infinity, infinity, infinity);
    Point3 max(-infinity, -infinity, -infinity);

    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
            for (int k = 0; k < 2; k++) {
                auto x = i * bbox.x.max + (1 - i) * bbox.x.min;
                auto y = j * bbox.y.max + (1 - j) * bbox.y.min;
                auto z = k * bbox.z.max + (1 - k) * bbox.z.min;

                auto newx = cos_theta * x + sin_theta * z;
                auto newz = -sin_theta * x + cos_theta * z;

                Vector3 tester(newx, y, newz);

                for (int c = 0; c < 3; c++) {
                    min[c] = fmin(min[c], tester[c]);
                    max[c] = fmax(max[c], tester[c]);
                }
            }
        }
    }

    bbox = AABB(min, max);
}

bool rotate_y::hit(const Ray &r, Interval ray_t, InterPoint &rec) const {
    // Change the ray from world space to object space
    auto orig = r.orig();
    auto dir = r.dir();

    orig.xx = cos_theta * r.orig().xx - sin_theta * r.orig().zz;
    orig.zz = sin_theta * r.orig().xx + cos_theta * r.orig().zz;

    dir.xx = cos_theta * r.dir().xx - sin_theta * r.dir().zz;
    dir.zz = sin_theta * r.dir().xx + cos_theta * r.dir().zz;

    Ray rotated_r(orig, dir, r.time());

    // Determine whether an intersection exists in object space (and if so, where)
    if (!object->hit(rotated_r, ray_t, rec))
        return false;

    // Change the intersection point from object space to world space
    auto p = rec.loc;
    p[0] = cos_theta * rec.loc[0] + sin_theta * rec.loc[2];
    p[2] = -sin_theta * rec.loc[0] + cos_theta * rec.loc[2];

    // Change the normal from object space to world space
    auto normal = rec.nor;
    normal[0] = cos_theta * rec.nor[0] + sin_theta * rec.nor[2];
    normal[2] = -sin_theta * rec.nor[0] + cos_theta * rec.nor[2];

    rec.loc = p;
    rec.nor = normal;

    return true;
}