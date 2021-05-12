#ifndef VEC3_H
#define VEC3_H

#include <math.h>

// TODO: vec3 struct

typedef double * vec3;
typedef vec3 color;
typedef vec3 point3;

vec3 vec3_create(double x, double y, double z)
{
	vec3 out = malloc(sizeof(double) * 3);
	out[0] = x;
	out[1] = y;
	out[2] = z;
	return out;
}

vec3 add(vec3 a, vec3 b)
{
	vec3 out = malloc(sizeof(double) * 3);
	out[0] = a[0] + b[0];
	out[1] = a[1] + b[1];
	out[2] = a[2] + b[2];
	return out;
}

vec3 sub(vec3 a, vec3 b)
{
	static vec3 out;
	out[0] = a[0] - b[0];
	out[1] = a[1] - b[1];
	out[2] = a[2] - b[2];
	return out;
}

vec3 mul(vec3 a, vec3 b)
{
	vec3 out = malloc(sizeof(double) * 3);
	out[0] = a[0] * b[0];
	out[1] = a[1] * b[1];
	out[2] = a[2] * b[2];
	return out;
}

double length_squared(vec3 e)
{
    return e[0]*e[0] + e[1]*e[1] + e[2]*e[2];
}

double length(vec3 e)
{
	return sqrt(length_squared(e));
}

double dot(vec3 a, vec3 b)
{
	return a[0]*b[0] + a[1]*b[1] + a[2]*b[2];
}

vec3 scale(vec3 e, double s)
{
	vec3 out = malloc(sizeof(double) * 3);
	out[0] = e[0] * s;
	out[1] = e[1] * s;
	out[2] = e[2] * s;
	return out;
}

double * normalize(vec3 e)
{
	return scale(e, 1/length(e));;
}

double * cross(const vec3 u, const vec3 v)
{
	vec3 out = malloc(sizeof(double) * 3);
	out[0] = u[1] * v[2] - u[2] * v[1];
	out[1] = u[2] * v[0] - u[0] * v[2];
	out[2] = u[0] * v[1] - u[1] * v[0];
    return out;
}

#endif