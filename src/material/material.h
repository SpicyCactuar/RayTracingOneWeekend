#ifndef RAYTRACINGONEWEEKEND_MATERIAL_H
#define RAYTRACINGONEWEEKEND_MATERIAL_H

#include "../random/rtrandom.h"
#include "../color/color.h"
#include "../hit/hit.h"

struct HitRecord;

class Material {
public:
    virtual bool scatter(const Ray& rayIn, const HitRecord& hit, Color& attenuation, Ray& scattered) const = 0;
};

#endif //RAYTRACINGONEWEEKEND_MATERIAL_H
