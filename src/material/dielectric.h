#ifndef RAYTRACINGONEWEEKEND_DIELECTRIC_H
#define RAYTRACINGONEWEEKEND_DIELECTRIC_H

#include "material.h"

class Dielectric : public Material {
public:
    Dielectric(double refractionIndex) : refractionIndex(refractionIndex) {}

    bool scatter(const Ray& rayIn, const HitRecord& hit, Color& attenuation, Ray& scattered) const override {
        attenuation = Color(1.0, 1.0, 1.0);
        double refractionRatio = hit.frontFace ? (1.0 / refractionIndex) : refractionIndex;

        Vector3 unitDirection = normalize(rayIn.direction);

        double cosTheta = fmin(dot(-unitDirection, hit.normal), 1.0);
        double sinTheta = sqrt(1.0 - cosTheta * cosTheta);

        bool cannotRefract = refractionRatio * sinTheta > 1.0;
        Vector3 direction;

        if (cannotRefract || reflectance(cosTheta, refractionRatio) > randomDouble()) {
            direction = reflect(unitDirection, hit.normal);
        } else {
            direction = refract(unitDirection, hit.normal, refractionRatio);
        }

        scattered = Ray(hit.point, direction);
        return true;
    }


public:
    double refractionIndex;

private:
    static double reflectance(double cos, double refractionRatio) {
        // Schlick's approximation for reflectance
        auto r0 = (1 - refractionRatio) / (1 + refractionRatio);
        r0 = r0 * r0;
        return r0 + (1 - r0) * pow((1 - cos), 5);
    }

};

#endif //RAYTRACINGONEWEEKEND_DIELECTRIC_H
