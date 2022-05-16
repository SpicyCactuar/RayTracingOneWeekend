#ifndef RAYTRACINGONEWEEKEND_CAMERA_H
#define RAYTRACINGONEWEEKEND_CAMERA_H

#include "../vector/vector3.h"
#include "../ray/ray.h"

const double pi = 3.1415926535897932385;

class Camera {
public:
    Camera(
        Point3 origin,
        Point3 target,
        Vector3 vup,
        double verticalFovInDegrees,
        double aspectRatio,
        double aperture,
        double focusDistance
    ) {
        // Calculate viewportHeight & viewportWidth in relation to verticalFovInDegrees
        const auto theta = degreesToRadians(verticalFovInDegrees);
        const auto height = tan(theta / 2);
        const auto viewportHeight = 2.0 * height;
        const auto viewportWidth = viewportHeight * aspectRatio;

        // Calculate (u, v, w) that defines camera's plane from vertical up (vup)
        w = normalize(origin - target);
        u = normalize(cross(vup, w));
        v = cross(w, u);

        // +V = Up | +U = Right | -W = Forward (into target)
        this->origin = origin;
        horizontal = focusDistance * viewportWidth * u;
        vertical = focusDistance * viewportHeight * v;
        lowerLeftCorner = origin - horizontal / 2 - vertical / 2 - focusDistance * w;

        lensRadius = aperture / 2;
    }

    inline double degreesToRadians(double degrees) {
        return degrees * pi / 180.0;
    }

    Ray createRay(double s, double t) const {
        Vector3 rd = lensRadius * randomInUnitDisk();
        Vector3 offset = u * rd.x() + v * rd.y();

        return Ray(origin + offset, lowerLeftCorner + s * horizontal + t * vertical - origin - offset);
    }

private:
    Point3 origin;
    Point3 lowerLeftCorner;
    Vector3 horizontal;
    Vector3 vertical;
    Vector3 u, v, w;
    double lensRadius;
};

#endif //RAYTRACINGONEWEEKEND_CAMERA_H
