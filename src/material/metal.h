#ifndef RAYTRACINGONEWEEKEND_METAL_H
#define RAYTRACINGONEWEEKEND_METAL_H

#include "../color/color.h"
#include "material.h"

class Metal : public Material {
public:
    Metal(const Color& a, double fuzz) : albedo(a), fuzz(fuzz) {}

    bool scatter(const Ray& rayIn, const HitRecord& hit, Color& attenuation, Ray& scattered) const override {
        Vector3 reflected = reflect(normalize(rayIn.direction), hit.normal);
        scattered = Ray(hit.point, reflected + fuzz * randomInUnitSphere());
        attenuation = albedo;
        return dot(scattered.direction, hit.normal) > 0;
    }

public:
    Color albedo;
    double fuzz;
};

#endif //RAYTRACINGONEWEEKEND_METAL_H
