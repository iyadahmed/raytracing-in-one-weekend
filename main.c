#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "ppmio.h"
#include "vec3.h"
//#include "ray.h"


//color ray_color(const ray& r) {
//    vec3 unit_direction = unit_vector(r.direction());
//    auto t = 0.5*(unit_direction.y() + 1.0);
//    return (1.0-t)*color(1.0, 1.0, 1.0) + t*color(0.5, 0.7, 1.0);
//}


void write_color(unsigned char * buf, double r, double g, double b)
{			
	*buf = (unsigned char)(255 * r);
	*(buf+1) = (unsigned char)(255 * g);
	*(buf+2) = (unsigned char)(255 * b);
}

int main(int argc, char *argv[])
{
	// Image
	const float aspect_ratio = 16.0 / 9.0;
    const int image_width = 1024;
    const int image_height = (int)(image_width / aspect_ratio);
    
    // Camera
	const float viewport_height = 2.0;
    const float viewport_width = aspect_ratio * viewport_height;
    const float focal_length = 1.0;

    point3 origin = {0, 0, 0};
    vec3 horizontal = {viewport_width, 0, 0};
    vec3 vertical = {0, viewport_height, 0};
    // TODO: unuglify this
    double * lower_left_corner = sub(add(add(origin, scale(horizontal, -0.5)), scale(vertical, -0.5)), (vec3){0, 0, focal_length});
	

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
			double r = (double)i / image_width;
			double g = (double)j / image_height;
			double b = .25;
			write_color(tmp_buf, r, g, b);
			tmp_buf += 3;
		}
		time += (double)(clock() - begin) / CLOCKS_PER_SEC;
	}
	printf("\nDone.\n");
	printf("Render Time: %f\n", time);
	write_ppm(buf, image_width, image_height);
	free(buf);
	
	return 0;
}