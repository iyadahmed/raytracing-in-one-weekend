#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>
#include <assert.h>
#include "ppmio.h"
#include "vec3.h"
#include "ray.h"
//#include "sphere.h"

#define LERP(a, b, t) ((1.0-t) + t * b)


double hit_sphere(const double *center, double radius, const ray *r) {
	vec3 oc;
	oc[0] = r->orig[0] - center[0];
	oc[1] = r->orig[1] - center[1];
	oc[2] = r->orig[2] - center[2];
	double a = LENSQ(r->dir);
	double half_b = DOT(oc, r->dir);
	double c = LENSQ(oc) - radius*radius;
	double discriminant = half_b*half_b - a*c;
	if (discriminant < 0) {
		return -1.0;
	} else {
		return (-half_b - sqrt(discriminant) ) / a;
	}
}


double *ray_color(double *out, ray *r) {
//	hit_record rec;
	double t = hit_sphere((point3) {
		0,0,-1
	},
	0.5,
	r);
	if (t > 0.0) {
		vec3 N;
		normalize(N, sub(N, ray_at(N, r, t), (vec3) {
			0,0,-1
		}));
		out[0] = N[0]+1;
		out[1] = N[1]+1;
		out[2] = N[2]+1;
		scale(out, out, 0.5);
		return out;
	}

	vec3 unit_direction;
	normalize(unit_direction, r->dir);
	t = 0.5*(unit_direction[1] + 1.0);
	out[0] = LERP(1, .5, t);
	out[1] = LERP(1, .7, t);
	out[2] = 1.0;
	return out;
}


void write_color(unsigned char *buf, double *col) {
	*buf = (unsigned char)(255 * col[0]);
	*(buf+1) = (unsigned char)(255 * col[1]);
	*(buf+2) = (unsigned char)(255 * col[2]);
}

void render(unsigned char *buf, unsigned int image_width, unsigned int image_height, ray r) {
	assert(sizeof(buf) == (image_width * image_height * 3));
}

int main(int argc, char *argv[]) {
	// Image
	const float aspect_ratio = 16.0 / 9.0;
	const unsigned int image_width = 4096;
	const unsigned int image_height = (unsigned int)(image_width / aspect_ratio);

	// Camera
	const float viewport_height = 2.0;
	const float viewport_width = aspect_ratio * viewport_height;
	const float focal_LEN = 1.0;

	point3 origin = {0, 0, 0};
	vec3 horizontal = {viewport_width, 0, 0};
	vec3 vertical = {0, viewport_height, 0};

	vec3 lower_left_corner;
	lower_left_corner[0] = origin[0] - horizontal[0]/2 - vertical[0]/2;
	lower_left_corner[1] = origin[1] - horizontal[1]/2 - vertical[1]/2;
	lower_left_corner[2] = origin[2] - horizontal[2]/2 - vertical[2]/2 - focal_LEN;

	ray r;
	r.orig[0] = origin[0];
	r.orig[1] = origin[1];
	r.orig[2] = origin[2];

	color final_color = {1, 0, 1};

	unsigned char *buf = (unsigned char *)malloc(image_width * image_height * 3);
	if (buf == NULL) {
		printf("Failed to allocate memory.\n");
		exit(1);
	}
//	render(buf, image_width, image_height);
	unsigned char *tmp_buf = buf;
	unsigned int i, j = image_height;
	double u, v;
	while(j--) {
		printf("\rScanlines remaining: %d", j);
		fflush(stdout);
		for (i = 0; i < image_width; i++) {
			// TODO: Render Code
			u = (double)i / image_width;
			v = (double)j / image_height;

			r.dir[0] = lower_left_corner[0] + u*horizontal[0] + v*vertical[0] - origin[0];
			r.dir[1] = lower_left_corner[1] + u*horizontal[1] + v*vertical[1] - origin[1];
			r.dir[2] = lower_left_corner[2] + u*horizontal[2] + v*vertical[2] - origin[2];

			ray_color(final_color, &r);

			write_color(tmp_buf, final_color);
			tmp_buf += 3;
		}
	}
	printf("\nDone.\n");
	printf("Exporting PPM ...\n");
	write_ppm(buf, image_width, image_height);
	printf("Done.\n");
	free(buf);
	return 0;
}