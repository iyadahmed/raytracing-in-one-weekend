#include "hittable.h"
#include "vec3.h"
#include "ray.h"

void set_hit_record_face_normal(HitRecord *hit_record, Ray *ray, Vec3 *outward_normal)
{
    hit_record->is_front_face = v3_dot(&ray->direction, outward_normal) < 0;
    if (hit_record->is_front_face)
    {
        hit_record->normal.x = outward_normal->x;
        hit_record->normal.y = outward_normal->y;
        hit_record->normal.z = outward_normal->z;
    }
    else
    {
        hit_record->normal.x = -outward_normal->x;
        hit_record->normal.y = -outward_normal->y;
        hit_record->normal.z = -outward_normal->z;
    }
}