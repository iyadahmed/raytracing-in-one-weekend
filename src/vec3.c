#include <math.h>
#include "vec3.h"

double v3_dot(Vec3 *a, Vec3 *b) { return a->x * b->x + a->y * b->y + a->z * b->z; }

double v3_magnitude_sq(Vec3 *v)
{
    return v->x * v->x + v->y * v->y + v->z * v->z;
}

double v3_magnitude(Vec3 *v)
{
    return sqrt(v->x * v->x + v->y * v->y + v->z * v->z);
}

void v3_add(Vec3 *out, Vec3 *a, Vec3 *b)
{
    out->x = a->x + b->x;
    out->y = a->y + b->y;
    out->z = a->z + b->z;
}

void v3_sub(Vec3 *out, Vec3 *a, Vec3 *b)
{
    out->x = a->x - b->x;
    out->y = a->y - b->y;
    out->z = a->z - b->z;
}

void v3_mul(Vec3 *out, Vec3 *a, Vec3 *b)
{
    out->x = a->x * b->x;
    out->y = a->y * b->y;
    out->z = a->z * b->z;
}

void v3_scale(Vec3 *out, Vec3 *a, double s)
{
    out->x = a->x * s;
    out->y = a->y * s;
    out->z = a->z * s;
}

void v3_normalize(Vec3 *out, Vec3 *v)
{
    double mag = sqrt(v->x * v->x + v->y * v->y + v->z * v->z);
    out->x = v->x / mag;
    out->y = v->y / mag;
    out->z = v->z / mag;
}

void v3_cross(Vec3 *out, Vec3 *a, Vec3 *b)
{
    out->x = a->y * b->z - a->z * b->y;
    out->y = a->z * b->x - a->x * b->z;
    out->z = a->x * b->y - a->y * b->x;
}

void v3_lerp(Vec3 *out, Vec3 *a, Vec3 *b, Vec3 *t)
{
    out->x = a->x * (1 - t->x) + b->x * t->x;
    out->y = a->y * (1 - t->y) + b->y * t->y;
    out->z = a->z * (1 - t->z) + b->z * t->z;
}