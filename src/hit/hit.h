#ifndef RAYTRACINGONEWEEKEND_HITTABLE_H
#define RAYTRACINGONEWEEKEND_HITTABLE_H

#include "../ray/ray.h"
#include "../material/material.h"

struct HitRecord {

    HitRecord() = default;

    HitRecord(Point3 point, Vector3 normal, std::shared_ptr<Material> material, double t, bool frontFace) :
        point(point), normal(normal), material(std::shared_ptr<Material>(material)), t(t), frontFace(frontFace) {};

    Point3 point;
    Vector3 normal;
    std::shared_ptr<Material> material;
    double t;
    bool frontFace;
};

class Hittable {
public:
    virtual std::unique_ptr<HitRecord> hit(const Ray& ray, double tMin, double tMax) const = 0;
};

#endif //RAYTRACINGONEWEEKEND_HITTABLE_H