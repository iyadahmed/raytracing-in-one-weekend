#ifndef VEC3_H
#define VEC3_H

typedef struct _Vec3 {
    double x, y, z;
} Vec3;

typedef Vec3 Point3;

typedef struct _Color3 {
    double r, g, b;
} Color3;

double v3_dot(Vec3 *a, Vec3 *b);
double v3_magnitude_sq(Vec3 *v);
double v3_magnitude(Vec3 *v);
void v3_add(Vec3 *out, Vec3 *a, Vec3 *b);
void v3_sub(Vec3 *out, Vec3 *a, Vec3 *b);
void v3_mul(Vec3 *out, Vec3 *a, Vec3 *b);
void v3_scale(Vec3 *out, Vec3 *a, double s);
void v3_normalize(Vec3 *out, Vec3 *v);
void v3_cross(Vec3 *out, Vec3 *a, Vec3 *b);

#endif