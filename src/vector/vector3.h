#ifndef RAYTRACINGONEWEEKEND_VECTOR3_H
#define RAYTRACINGONEWEEKEND_VECTOR3_H

#include <cmath>
#include <iostream>
#include "../random/rtrandom.h"

using std::sqrt;

class Vector3 {
public:
    Vector3() : e{0, 0, 0} {}

    Vector3(double e0, double e1, double e2) : e{e0, e1, e2} {}

    inline double x() const { return e[0]; }

    inline double y() const { return e[1]; }

    inline double z() const { return e[2]; }

    inline Vector3 operator-() const { return Vector3(-e[0], -e[1], -e[2]); }

    inline double operator[](int i) const { return e[i]; }

    inline double& operator[](int i) { return e[i]; }

    inline Vector3& operator+=(const Vector3& v) {
        e[0] += v[0];
        e[1] += v[1];
        e[2] += v[2];
        return *this;
    }

    inline Vector3& operator*=(const double t) {
        e[0] *= t;
        e[1] *= t;
        e[2] *= t;
        return *this;
    }

    inline Vector3& operator/=(const double t) {
        return *this *= 1 / t;
    }

    inline double length() const {
        return sqrt(lengthSquared());
    }

    inline double lengthSquared() const {
        return e[0] * e[0] + e[1] * e[1] + e[2] * e[2];
    }

    inline static Vector3 random() {
        return Vector3(randomDouble(), randomDouble(), randomDouble());
    }

    inline static Vector3 random(double min, double max) {
        return Vector3(randomDouble(min, max), randomDouble(min, max), randomDouble(min, max));
    }

    bool isNearZero() const {
        // Return true if the vector is close to zero in all dimensions
        const auto s = 1e-8;
        return (fabs(e[0]) < s) && (fabs(e[1]) < s) && (fabs(e[2]) < s);
    }

private:
    double e[3];

};

// Utility Functions

inline std::ostream& operator<<(std::ostream& out, const Vector3& v) {
    return out << v[0] << ' ' << v[1] << ' ' << v[2];
}

inline Vector3 operator+(const Vector3& u, const Vector3& v) {
    return Vector3(u[0] + v[0], u[1] + v[1], u[2] + v[2]);
}

inline Vector3 operator-(const Vector3& u, const Vector3& v) {
    return Vector3(u[0] - v[0], u[1] - v[1], u[2] - v[2]);
}

inline Vector3 operator*(const Vector3& u, const Vector3& v) {
    return Vector3(u[0] * v[0], u[1] * v[1], u[2] * v[2]);
}

inline Vector3 operator*(double t, const Vector3& v) {
    return Vector3(t * v[0], t * v[1], t * v[2]);
}

inline Vector3 operator*(const Vector3& v, double t) {
    return t * v;
}

inline Vector3 operator/(Vector3 v, double t) {
    return (1 / t) * v;
}

inline double dot(const Vector3& u, const Vector3& v) {
    return u[0] * v[0]
           + u[1] * v[1]
           + u[2] * v[2];
}

inline Vector3 cross(const Vector3& u, const Vector3& v) {
    return Vector3(u[1] * v[2] - u[2] * v[1],
                   u[2] * v[0] - u[0] * v[2],
                   u[0] * v[1] - u[1] * v[0]);
}

inline Vector3 normalize(Vector3 v) {
    return v / v.length();
}

inline static Vector3 randomInUnitSphere() {
    while (true) {
        auto p = Vector3::random(-1, 1);
        if (p.lengthSquared() >= 1) continue;
        return p;
    }
}

inline static Vector3 randomInUnitDisk() {
    while (true) {
        auto p = Vector3(randomDouble(-1, 1), randomDouble(-1, 1), 0);
        if (p.lengthSquared() >= 1) continue;
        return p;
    }
}

inline static Vector3 randomUnitVector() {
    return normalize(randomInUnitSphere());
}

inline Vector3 randomInHemisphere(const Vector3& normal) {
    Vector3 inUnitSphere = randomInUnitSphere();
    if (dot(inUnitSphere, normal) > 0.0) // In the same hemisphere as the normal
        return inUnitSphere;
    else
        return -inUnitSphere;
}

inline Vector3 reflect(const Vector3& v, const Vector3& n) {
    return v - 2 * dot(v, n) * n;
}

Vector3 refract(const Vector3& uv, const Vector3& n, double etaiOverEtat) {
    auto costTheta = fmin(dot(-uv, n), 1.0);
    Vector3 rOutPerpendicular = etaiOverEtat * (uv + costTheta * n);
    Vector3 rOutParallel = -sqrt(fabs(1.0 - rOutPerpendicular.lengthSquared())) * n;
    return rOutPerpendicular + rOutParallel;
}

using Point3 = Vector3;

#endif //RAYTRACINGONEWEEKEND_VECTOR3_H
