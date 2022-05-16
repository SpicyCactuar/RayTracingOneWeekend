#ifndef RAYTRACINGONEWEEKEND_LAMBERTIAN_H
#define RAYTRACINGONEWEEKEND_LAMBERTIAN_H

#include "material.h"

class Lambertian : public Material {
public:
    Lambertian(const Color& a) : albedo(a) {}

    virtual bool scatter(const Ray& rayIn, const HitRecord& hit, Color& attenuation, Ray& scattered) const override {
        auto scatterDirection = hit.normal + randomUnitVector();

        // Prevent direction opposite to normal
        if (scatterDirection.isNearZero()) {
            scatterDirection = hit.normal;
        }

        scattered = Ray(hit.point, scatterDirection);
        attenuation = albedo;
        return true;
    }

public:
    Color albedo;
};

#endif //RAYTRACINGONEWEEKEND_LAMBERTIAN_H
