#ifndef VEC3_H
#define VEC3_H

#include <math.h>

#define DOT(a, b) (a[0] * b[0] + a[1] * b[1] + a[2] * b[2])
#define LENSQ(v) (DOT(v, v))
#define LEN(v) sqrt(LENSQ(v))
#define PRINTV(v) printf("(%lf, %lf, %lf)\n", v[0], v[1], v[2])

typedef double vec3[3];
typedef vec3 point3;
typedef vec3 color;

double *add(double *out, double *a, double *b) {
    out[0] = a[0] + b[0];
    out[1] = a[1] + b[1];
    out[2] = a[2] + b[2];
    return out;
}

double *sub(double *out, double *a, double *b) {
    out[0] = a[0] - b[0];
    out[1] = a[1] - b[1];
    out[2] = a[2] - b[2];
    return out;
}

double *mul(double *out, double *a, double *b) {
    out[0] = a[0] * b[0];
    out[1] = a[1] * b[1];
    out[2] = a[2] * b[2];
    return out;
}

double *scale(double *out, double *v, double s) {
    out[0] = v[0] * s;
    out[1] = v[1] * s;
    out[2] = v[2] * s;
    return out;
}

double *normalize(double *out, double *v) { return scale(out, v, 1 / LEN(v)); }

double *cross(double *out, double *u, double *v) {
    out[0] = u[1] * v[2] - u[2] * v[1];
    out[1] = u[2] * v[0] - u[0] * v[2];
    out[2] = u[0] * v[1] - u[1] * v[0];
    return out;
}

#endif