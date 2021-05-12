#include <stdio.h>
#include <stdlib.h>
#include "ppmio.h"
#include "vec3.h"


void write_color(unsigned char * buf, color rgb)
{			
    *buf = (unsigned char)(255.999 * rgb[0]);
	*(buf+1) = (unsigned char)(255.999 * rgb[1]);
	*(buf+2) = (unsigned char)(255.999 * rgb[2]);
}


int main(int argc, char *argv[])
{
	unsigned int width = 1024;
	unsigned int height = 512;
	unsigned char *buf = (unsigned char *)malloc(width * height * 3);
	unsigned char *tmp_buf = buf;
	int i, j;
	for (j = height-1; j >= 0; j--)
	{
		printf("\rScanlines remaining: %d", j);
		fflush(stdout);
		for (i = 0; i < width; i++)
		{
			// TODO: Render Code
            color c;
            c[0] = (double)i / width;
            c[1] = (double)j / height;
            c[2] = .25;
            write_color(tmp_buf, c);
			tmp_buf += 3;
		}
	}
	write_ppm(buf, width, height);
	free(buf);
	printf("\nDone.\n");
	return 0;
}