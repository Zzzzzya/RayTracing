#include "BVH.hpp"
#include <algorithm>

bvh::bvh(Scene &sce) : bvh(sce.objects, 0, sce.size()) {
}

bvh::bvh(std::vector<shared_ptr<hittable>> objects, int begin, int end) {
    // 递归的进行构造
    // 0. 递归出口
    if (begin == end - 1) {
        left = right = objects[begin];

    } else if (begin == end - 2) {
        left = objects[begin];
        right = objects[end - 1];
    } else {

        // 1. 维度选择 - 随机选择一个维度
        auto axis = random_int(0, 2);

        auto compareFunc = axis == 0 ? comparex : (axis == 1 ? comparey : comparez);

        // 2. 按照此维度进行排序
        std::sort(objects.begin() + begin, objects.begin() + end, compareFunc);

        // 3. 递归构建
        int mid = (begin + end) >> 1;
        left = make_shared<bvh>(objects, begin, mid);
        right = make_shared<bvh>(objects, mid, end);
    }

    // 4.构建当前节点
    _aabb = AABB(left->aabb(), right->aabb());
}

bool bvh::hit(const Ray &ray, Interval rayT, InterPoint &inter) const {
    // 如果没打中外部包围盒 ， 内部的就更不可能打中
    if (!_aabb.hit(ray, rayT)) {
        return false;
    }

    // 如果打中了 那么就继续判断有没有打中内部的
    auto hitleft = left->hit(ray, rayT, inter);
    auto hitright = right->hit(ray, Interval(rayT.min, hitleft ? inter.t : rayT.max), inter);
    return hitleft || hitright;
}
