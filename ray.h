#ifndef RAY_H
#define RAY_H

#include "vec3.h"

typedef struct ray {
	point3 orig;
	vec3 dir;
} ray;

double *ray_at(double *out, ray *r, double t) {
	return add(out, r->orig, scale(out, r->dir, t));
}

#endif