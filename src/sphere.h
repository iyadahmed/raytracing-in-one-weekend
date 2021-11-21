#ifndef SPHERE_H
#define SPHERE_H

#include "hittable.h"
#include "ray.h"
#include "vec3.h"

typedef struct Sphere {
    Vec3 center;
    double radius;
} Sphere;

int hit_sphere(Sphere *sphere, Ray *ray, double t_min, double t_max, HitRecord *hit_record);

#endif
