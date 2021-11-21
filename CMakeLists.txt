cmake_minimum_required(VERSION 3.10)
project(raytracing-c)
add_executable(raytracing_c src/main.c src/image.c src/sphere.c src/vec3.c src/ray.c src/hittable.c)