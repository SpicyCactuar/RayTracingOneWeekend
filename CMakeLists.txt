cmake_minimum_required(VERSION 3.21)
project(RayTracingOneWeekend)

set(CMAKE_CXX_STANDARD 17)

add_executable(RayTracingOneWeekend src/main.cpp src/vector/vector3.h src/color/color.h src/ray/ray.h src/hit/hit.h src/hit/sphere.h src/hit/hittable_list.h src/camera/camera.h src/random/rtrandom.h src/material/material.h src/material/lambertian.h src/material/metal.h src/material/dielectric.h)
