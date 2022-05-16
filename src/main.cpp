#include <iostream>

#include "vector/vector3.h"
#include "color/color.h"
#include "ray/ray.h"
#include "hit/sphere.h"
#include "hit/hittable_list.h"
#include "camera/camera.h"
#include "material/lambertian.h"
#include "material/metal.h"
#include "material/dielectric.h"

using std::make_shared;

const double infinity = std::numeric_limits<double>::infinity();

HittableList randomWorld();

Color rayColor(const Ray& ray, const Hittable& world, int depth);

void renderWorld(int imageWidth, int imageHeight, int samplesPerPixel, int maxRayDepth, const Camera& camera,
                 const HittableList& world);

int main() {

    const double aspectRatio = 3.0 / 2.0;
    const int imageWidth = 1200;
    const int imageHeight = static_cast<int>(imageWidth / aspectRatio);
    const int samplesPerPixel = 250;
    const int maxRayDepth = 50;

    const Camera camera(
        Point3(13, 2, 3),
        Point3(0, 0, 0),
        Vector3(0, 1, 0),
        20,
        aspectRatio,
        0.1,
        10.0
    );

    HittableList world = randomWorld();

    renderWorld(imageWidth, imageHeight, samplesPerPixel, maxRayDepth, camera, world);

    return 0;
}

void renderWorld(
    int imageWidth,
    const int imageHeight,
    const int samplesPerPixel,
    const int maxRayDepth,
    const Camera& camera,
    const HittableList& world
) {
    std::cout << "P3\n" << imageWidth << ' ' << imageHeight << "\n255\n";

    // Iterate over rows
    for (int j = imageHeight - 1; j >= 0; --j) {
        std::clog << "\rScanlines remaining: " << j << ' ' << std::flush;
        // Iterate over columns
        for (int i = 0; i < imageWidth; ++i) {
            Color pixelColor;
            for (int k = 0; k < samplesPerPixel; ++k) {
                auto s = (i + randomDouble()) / (imageWidth - 1);
                auto t = (j + randomDouble()) / (imageHeight - 1);
                Ray ray = camera.createRay(s, t);
                pixelColor += rayColor(ray, world, maxRayDepth);
            }
            writeColor(std::cout, pixelColor, samplesPerPixel);
        }
    }

    std::clog << "\nDone.\n";
}

Color rayColor(const Ray& ray, const Hittable& world, int depth) {
    if (depth <= 0) {
        return Color(0, 0, 0);
    }

    auto hit = world.hit(ray, 0.001, infinity);
    double t;
    if (hit != nullptr) {
        Ray scattered;
        Color attenuation;
        if (hit->material->scatter(ray, *hit, attenuation, scattered)) {
            return attenuation * rayColor(scattered, world, depth - 1);
        }
        return Color(0, 0, 0);
    }

    Vector3 unitDirection = normalize(ray.direction);
    // Transforms the range of t as [-1.0, 1.0] ~(+1)~> [0.0, 2.0] ~(*0.5)~> [0.0, 1.0]
    t = 0.5 * (unitDirection.y() + 1.0);
    return (1.0 - t) * Color(1.0, 1.0, 1.0) + t * Color(0.5, 0.7, 1.0);
}

HittableList randomWorld() {
    HittableList world;

    auto groundMaterial = make_shared<Lambertian>(Color(0.5, 0.5, 0.5));
    world.add(make_shared<Sphere>(Point3(0, -1000, 0), 1000, groundMaterial));

    for (int a = -11; a < 11; a++) {
        for (int b = -11; b < 11; b++) {
            auto chooseMaterial = randomDouble();
            Point3 center(a + 0.9 * randomDouble(), 0.2, b + 0.9 * randomDouble());

            if ((center - Point3(4, 0.2, 0)).length() > 0.9) {
                shared_ptr<Material> sphereMaterial;

                if (chooseMaterial < 0.8) {
                    // Diffuse
                    auto albedo = Color::random() * Color::random();
                    sphereMaterial = make_shared<Lambertian>(albedo);
                    world.add(make_shared<Sphere>(center, 0.2, sphereMaterial));
                } else if (chooseMaterial < 0.95) {
                    // Metal
                    auto albedo = Color::random(0.5, 1);
                    auto fuzz = randomDouble(0, 0.5);
                    sphereMaterial = make_shared<Metal>(albedo, fuzz);
                    world.add(make_shared<Sphere>(center, 0.2, sphereMaterial));
                } else {
                    // Glass
                    sphereMaterial = make_shared<Dielectric>(1.5);
                    world.add(make_shared<Sphere>(center, 0.2, sphereMaterial));
                }
            }
        }
    }

    auto material1 = make_shared<Dielectric>(1.5);
    world.add(make_shared<Sphere>(Point3(0, 1, 0), 1.0, material1));

    auto material2 = make_shared<Lambertian>(Color(0.4, 0.2, 0.1));
    world.add(make_shared<Sphere>(Point3(-4, 1, 0), 1.0, material2));

    auto material3 = make_shared<Metal>(Color(0.7, 0.6, 0.5), 0.0);
    world.add(make_shared<Sphere>(Point3(4, 1, 0), 1.0, material3));

    return world;
}
