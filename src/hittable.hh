#pragma once

#include "vec3.hh"
#include "ray.hh"

class HitRecord
{
public:
    Point3 position;
    Vec3 normal;
    double t;
    bool is_front_face;

    /* Set normal and face orientation (front/back) */
    void set_normal(Ray &ray, Vec3 &outward_normal)
    {
        is_front_face = ray.direction.dot(outward_normal);
        if (is_front_face)
        {
            normal.x = outward_normal.x;
            normal.y = outward_normal.y;
            normal.z = outward_normal.z;
        }
        else
        {
            normal.x = -outward_normal.x;
            normal.y = -outward_normal.y;
            normal.z = -outward_normal.z;
        }
    }
};