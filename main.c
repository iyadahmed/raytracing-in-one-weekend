#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include "ppmio.h"
#include "vec3.h"
#include "ray.h"

#define lerp(a, b, t) ((1.0-t) + t * b)


double hit_sphere(const double *center, double radius, const ray *r) {
	vec3 oc;
	oc[0] = r->orig[0] - center[0];
	oc[1] = r->orig[1] - center[1];
	oc[2] = r->orig[2] - center[2];
	double a = length_sq(r->dir);
	double half_b = dot(oc, r->dir);
	double c = length_sq(oc) - radius*radius;
	double discriminant = half_b*half_b - a*c;
	if (discriminant < 0) {
        return -1.0;
    } else {
        return (-half_b - sqrt(discriminant) ) / a;
    }
}


double *ray_color(double *out, ray *r) {
    double t = hit_sphere((point3){0,0,-1}, 0.5, r);
    if (t > 0.0) {
        vec3 N;
		normalize(N, sub(N, ray_at(N, r, t), (vec3){0,0,-1}));
		out[0] = N[0]+1;
		out[1] = N[1]+1;
		out[2] = N[2]+1;
		scale(out, out, 0.5);
        return out;
    }

	vec3 unit_direction;
	normalize(unit_direction, r->dir);
	t = 0.5*(unit_direction[1] + 1.0);
	out[0] = lerp(1, .5, t);
	out[1] = lerp(1, .7, t);
	out[2] = 1.0;
	return out;
}


void write_color(unsigned char *buf, double *col) {
	*buf = (unsigned char)(255 * col[0]);
	*(buf+1) = (unsigned char)(255 * col[1]);
	*(buf+2) = (unsigned char)(255 * col[2]);
}

int main(int argc, char *argv[]) {
	// Image
	const float aspect_ratio = 16.0 / 9.0;
	const int image_width = 4096;
	const int image_height = (int)(image_width / aspect_ratio);

	// Camera
	const float viewport_height = 2.0;
	const float viewport_width = aspect_ratio * viewport_height;
	const float focal_length = 1.0;

	point3 origin = {0, 0, 0};
	vec3 horizontal = {viewport_width, 0, 0};
	vec3 vertical = {0, viewport_height, 0};

	vec3 lower_left_corner;
	lower_left_corner[0] = origin[0] - horizontal[0]/2 - vertical[0]/2;
	lower_left_corner[1] = origin[1] - horizontal[1]/2 - vertical[1]/2;
	lower_left_corner[2] = origin[2] - horizontal[2]/2 - vertical[2]/2 - focal_length;

	ray r;
	r.orig[0] = origin[0];
	r.orig[1] = origin[1];
	r.orig[2] = origin[2];

	color final_color;

	unsigned char *buf = (unsigned char *)malloc(image_width * image_height * 3);
	unsigned char *tmp_buf = buf;
	int i, j;
	double time = 0;
	clock_t begin;
	for (j = image_height-1; j >= 0; j--) {
		printf("\rScanlines remaining: %d", j);
		fflush(stdout);
		begin = clock();
		for (i = 0; i < image_width; i++) {
			// TODO: Render Code
			double u = (double)i / image_width;
			double v = (double)j / image_height;

			r.dir[0] = lower_left_corner[0] + u*horizontal[0] + v*vertical[0] - origin[0];
			r.dir[1] = lower_left_corner[1] + u*horizontal[1] + v*vertical[1] - origin[1];
			r.dir[2] = lower_left_corner[2] + u*horizontal[2] + v*vertical[2] - origin[2];

			ray_color(final_color, &r);

			write_color(tmp_buf, final_color);
			tmp_buf += 3;
		}
		time += (double)(clock() - begin) / CLOCKS_PER_SEC;
	}
	printf("\nDone.\n");
	printf("Render Time: %f\n", time);
	printf("Exporting PPM ...\n");
	write_ppm(buf, image_width, image_height);
	printf("Done.\n");
	free(buf);
	return 0;
}