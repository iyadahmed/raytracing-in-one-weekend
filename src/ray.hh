#pragma once

#include "vec3.hh"

class Ray
{
public:
    Point3 origin;
    Vec3 direction;

    Ray(Point3 origin = {0., 0., 0.}, Vec3 direction = {0., 0., 0.}) {}

    Vec3 at(double t)
    {
        return origin + direction *t;
    }
};
