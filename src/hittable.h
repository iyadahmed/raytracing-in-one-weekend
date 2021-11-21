#ifndef HITTABLE_H
#define HITTABLE_H

#include "vec3.h"
#include "ray.h"

typedef struct HitRecord
{
    Point3 position;
    Vec3 normal;
    double t;
    int is_front_face;
} HitRecord;

void set_hit_record_face_normal(HitRecord *hit_record, Ray *ray, Vec3 *outward_normal);

#endif