#include "Scene.hpp"

Scene::Scene() : objects() {
}

Scene::Scene(shared_ptr<hittable> object) : objects() {
    add(object);
}

void Scene::add(shared_ptr<hittable> object) {
    objects.push_back(object);
    _aabb = AABB(_aabb, object->aabb());
}

void Scene::clear() {
    objects.clear();
}

size_t Scene::size() const {
    return objects.size();
}

bool Scene::hit(const Ray &ray, Interval rayT, InterPoint &inter) const {
    float Closest_T = rayT.max;
    InterPoint curInterPoint = InterPoint();
    bool hitSomething = false;

    for (const auto &object : objects) {
        if (object->hit(ray, Interval(rayT.min, Closest_T), curInterPoint)) {
            Closest_T = curInterPoint.t;
            inter = curInterPoint;
            hitSomething = true;
        }
    }
    return hitSomething;
}

AABB Scene::aabb() const {
    return _aabb;
}
