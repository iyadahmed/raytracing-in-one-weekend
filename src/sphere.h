#ifndef SPHERE_H
#define SPHERE_H

#include "hittable.h"
#include "vec3.h"


typedef struct sphere {
	point3 cen;
	double r;
} sphere;

bool hit_sphere(sphere *sp, ray *r, double t_min, double t_max, hit_record *rec) {
	point3 center;
	center[0] = sp->cen[0];
	center[1] = sp->cen[1];
	center[2] = sp->cen[2];
	vec3 oc;
	oc[0] = r->orig[0] - sp->cen[0];
	oc[1] = r->orig[1] - sp->cen[1];
	double a = LENSQ(r->dir);
	double half_b = DOT(oc, r->dir);
	double c = LENSQ(oc) - sp->r * sp->r;

	double discriminant = half_b*half_b - a*c;
	if (discriminant < 0) return false;
	double sqrtd = sqrt(discriminant);
	
    // Find the nearest root that lies in the acceptable range.
    double root = (-half_b - sqrtd) / a;
    if (root < t_min || t_max < root) {
        root = (-half_b + sqrtd) / a;
        if (root < t_min || t_max < root)
            return false;
    
	}
	rec->t = root;
	ray_at(rec->p, r, rec->t);
	vec3 outward_normal = (rec->p - center) / radius;
	set_hit_record_face_normal(rec, r, outward_normal);
	rec->normal = (rec->p - center) / radius;

	return true;
}

#endif

