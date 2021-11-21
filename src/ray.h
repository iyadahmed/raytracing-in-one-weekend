#ifndef RAY_H
#define RAY_H

#include "vec3.h"

typedef struct _Ray
{
    Point3 origin;
    Vec3 direction;
} Ray;

void ray_at(Vec3 *out, Ray *ray, double t);

#endif