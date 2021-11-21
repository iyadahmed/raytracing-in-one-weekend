#include "hittable.h"
#include "ray.h"
#include "vec3.h"
#include "sphere.h"
#include <math.h>

/* Perform a ray-sphere intersection, returns 1 if hit, otherwise 0 */
int hit_sphere(Sphere *sphere, Ray *ray, double t_min, double t_max, HitRecord *hit_record)
{
    Vec3 oc;
    v3_sub(&oc, &ray->origin, &sphere->center);
    double a = v3_magnitude_sq(&ray->direction);
    double half_b = v3_dot(&oc, &ray->direction);
    double c = v3_magnitude_sq(&oc) - sphere->radius * sphere->radius;

    double discriminant = half_b * half_b - a * c;
    if (discriminant < 0)
        return 0;
    double sqrtd = sqrt(discriminant);

    // Find the nearest root that lies in the acceptable range.
    double root = (-half_b - sqrtd) / a;
    if (root < t_min || t_max < root)
    {
        root = (-half_b + sqrtd) / a;
        if (root < t_min || t_max < root)
            return 0;
    }

    hit_record->t = root;
    ray_at(&hit_record->position, ray, root);

    Vec3 outward_normal;
    v3_sub(&outward_normal, &hit_record->position, &sphere->center);
    v3_scale(&outward_normal, &outward_normal, 1.0 / sphere->radius);
    set_hit_record_face_normal(hit_record, ray, &outward_normal);

    return 1;
}