#include "vec3.h"
#include "ray.h"

void ray_at(Vec3 *out, Ray *ray, double t)
{
    out->x = ray->origin.x + ray->direction.x * t;
    out->y = ray->origin.y + ray->direction.y * t;
    out->z = ray->origin.z + ray->direction.z * t;
}