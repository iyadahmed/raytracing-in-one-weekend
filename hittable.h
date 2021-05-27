#ifndef HITTABLE_H
#define HITTABLE_H

#include "ray.h"

typedef struct hit_record {
	point3 p;
	vec3 normal;
	double t;
	bool front_face;
} hit_record;

void set_hit_record_face_normal(hit_record *rec, ray *r, vec3 *outward_normal) {
	rec->front_face = DOT(r->dir, *outward_normal) < 0;
	if (rec->front_face) {
		rec->normal[0] = *outward_normal[0];
		rec->normal[1] = *outward_normal[1];
		rec->normal[2] = *outward_normal[2];
	} else {
		rec->normal[0] = - *outward_normal[0];
		rec->normal[1] = - *outward_normal[1];
		rec->normal[2] = - *outward_normal[2];
	}

}

#endif