#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "ppmio.h"
#include "vec3.h"
#include "ray.h"

#define lerp(a, b, t) ((1.0-t) + t * b)


double *ray_color(double *out, ray *r) {
    vec3 unit_direction;
	normalize(unit_direction, r->dir);
    double t = 0.5*(unit_direction[1] + 1.0);
    out[0] = lerp(1, .5, t);
    out[1] = lerp(1, .7, t);
    out[2] = 1;
    return out;
}


void write_color(unsigned char *buf, double r, double g, double b)
{			
	*buf = (unsigned char)(255 * r);
	*(buf+1) = (unsigned char)(255 * g);
	*(buf+2) = (unsigned char)(255 * b);
}

int main(int argc, char *argv[])
{
	vec3 a = {0, 1, 0};
	vec3 b = {0, 0, 0};
	vec3 result;
	add(result, a, b);
	printv(result);
	
	// Image
	const float aspect_ratio = 16.0 / 9.0;
    const int image_width = 1024;
    const int image_height = (int)(image_width / aspect_ratio);
    
    // Camera
	const float viewport_height = 2.0;
    const float viewport_width = aspect_ratio * viewport_height;
    const float focal_length = 1.0;

    point3 origin = {0, 0, 0};
    vec3 horizontal = {0, 0, 0};
    vec3 vertical = {0, viewport_height, 0};

    vec3 lower_left_corner;
    lower_left_corner[0] = origin[0] - horizontal[0]/2 - vertical[0]/2;
    lower_left_corner[1] = origin[1] - horizontal[1]/2 - vertical[1]/2;
    lower_left_corner[2] = origin[2] - horizontal[2]/2 - vertical[2]/2 - focal_length;
    
    ray r;
	r.orig = origin;
	

	unsigned char *buf = (unsigned char *)malloc(image_width * image_height * 3);
	unsigned char *tmp_buf = buf;
	int i, j;
	double time = 0;
	clock_t begin;
	for (j = image_height-1; j >= 0; j--)
	{
		printf("\rScanlines remaining: %d", j);
		fflush(stdout);
		begin = clock();
		for (i = 0; i < image_width; i++)
		{
			// TODO: Render Code
			double u = (double)i / image_width;
			double v = (double)j / image_height;
			
			ray.dir[0] = lower_left_corner[0] + u*horizontal[0] + v*vertical[0] - origin[0];

			write_color(tmp_buf, u, v, .25);
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