#ifndef RAYTRACINGONEWEEKEND_HITTABLELIST_H
#define RAYTRACINGONEWEEKEND_HITTABLELIST_H

#include "hit.h"

#include <vector>

using std::shared_ptr;

class HittableList : public Hittable {
public:
    HittableList() = default;

    void add(const shared_ptr<Hittable>& hittable) { objects.push_back(hittable); }

    void clear() { objects.clear(); }

    std::unique_ptr<HitRecord> hit(const Ray& ray, double tMin, double tMax) const override {
        std::unique_ptr<HitRecord> closestHit;
        auto closestSoFar = tMax;

        for (const auto& object: objects) {
            std::unique_ptr<HitRecord> currentHit = object->hit(ray, tMin, closestSoFar);
            if (currentHit != nullptr) {
                closestHit.swap(currentHit);
                closestSoFar = closestHit->t;
            }
        }

        return closestHit;
    }

public:
    std::vector<shared_ptr<Hittable>> objects;
};

#endif //RAYTRACINGONEWEEKEND_HITTABLELIST_H
