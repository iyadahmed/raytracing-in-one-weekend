#ifndef RAY_H
#define RAY_H

#include "vec3.h"

typedef struct ray
{
	point3 orig;
	vec3 dir;
} ray;

double * ray_at(ray r, double t)
{
	return add(r.orig, scale(r.dir, t));
}

#endif