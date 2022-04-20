#pragma once

#include "vec3.hh"
#include "ray.hh"
#include "hittable.hh"

#include <cmath>

class Sphere
{
public:
    Vec3 center;
    double radius;

    Sphere(Vec3 center = {0.0, 0.0, 0.0}, double radius = 0.0) : center(center), radius(radius) {}

    bool hit(Ray &ray, double t_min, double t_max, HitRecord &hit_record)
    {
        Vec3 oc = ray.origin - center;
        double a = ray.direction.length_squared();
        double half_b = oc.dot(ray.direction);
        double c = oc.length_squared() - radius * radius;

        double discriminant = half_b * half_b - a * c;
        if (discriminant < 0.0)
        {
            return 0;
        }
        double sqrtd = sqrt(discriminant);

        // Find the nearest root that lies in the acceptable range.
        double root = (-half_b - sqrtd) / a;
        if (root < t_min || t_max < root)
        {
            root = (-half_b + sqrtd) / a;
            if (root < t_min || t_max < root)
            {
                return 0;
            }
        }

        hit_record.t = root;
        hit_record.position = ray.at(root);

        Vec3 outward_normal = (hit_record.position - center) * (1.0 / radius);
        hit_record.set_normal(ray, outward_normal);

        return 1;
    }
};
