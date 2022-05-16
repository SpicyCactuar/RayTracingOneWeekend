#ifndef RAYTRACINGONEWEEKEND_SPHERE_H
#define RAYTRACINGONEWEEKEND_SPHERE_H

#include <utility>

#include "../hit/hit.h"
#include "../vector/vector3.h"
#include "../material/material.h"

class Sphere : public Hittable {
public:

    Sphere(Point3 center, double radius, std::shared_ptr<Material> material) : center(center), radius(radius),
                                                                               material(std::move(material)) {};

    std::unique_ptr<HitRecord> hit(const Ray& ray, double tMin, double tMax) const override {
        // Finds t that satisfies the following quadratic equation:
        // t^2 * D * D + 2t * D * (O - C) + (O - C) * (O - C) − r^2 = 0
        // D = ray.direction, O = ray.origin, C = sphere center, r = radius

        Vector3 oc = ray.origin - center;
        auto a = ray.direction.lengthSquared();
        auto halfB = dot(oc, ray.direction);
        auto c = oc.lengthSquared() - radius * radius;

        auto discriminant = halfB * halfB - a * c;
        if (discriminant < 0) return nullptr;
        auto squareRootDiscriminant = sqrt(discriminant);

        // If the discriminant > 0, the ray goes through the sphere
        // Find the nearest root that lies in the acceptable range
        auto root = (-halfB - squareRootDiscriminant) / a;
        if (root < tMin || tMax < root) {
            root = (-halfB + squareRootDiscriminant) / a;
            if (root < tMin || tMax < root) {
                return nullptr;
            }
        }

        auto point = ray.at(root);
        auto outwardNormal = (point - center) / radius;
        auto frontFace = dot(ray.direction, outwardNormal) < 0.0;
        auto normal = frontFace ? outwardNormal : -outwardNormal;
        return std::make_unique<HitRecord>(point, normal, material, root, frontFace);
    }

public:
    Point3 center;
    double radius;
    std::shared_ptr<Material> material;
};

#endif //RAYTRACINGONEWEEKEND_SPHERE_H