#ifndef HITTABLE_H
#define HITTABLE_H

#include "vec3.h"

typedef struct HitRecord
{
    Point3 position;
    Vec3 normal;
    int is_front_face;
} HitRecord;

#endif