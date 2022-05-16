#ifndef RAYTRACINGONEWEEKEND_RAY_H
#define RAYTRACINGONEWEEKEND_RAY_H

#include "../vector/vector3.h"

class Ray {

public:
    Ray() {}

    Ray(const Point3& origin, const Vector3& direction) : origin(origin), direction(direction) {}

    Point3 at(double t) const {
        return origin + t * direction;
    }

public:
    Point3 origin;
    Vector3 direction;
};

#endif //RAYTRACINGONEWEEKEND_RAY_H