#include <stdio.h>
#include <stdlib.h>
#include "ppmio.h"


int main(int argc, char *argv[])
{
	unsigned int width = 1024;
	unsigned int height = 512;
	unsigned char *data = (unsigned char *)malloc(width * height * 3);
	unsigned char *tmp_data = data;
	int i, j;
	for (j = height-1; j >= 0; j--)
	{
		printf("\rScanlines remaining: %d", j);
		fflush(stdout);
		for (i = 0; i < width; i++)
		{
			// TODO: Render Code
			*tmp_data = (unsigned char)(((float)i / width) * 255);
			*(tmp_data+1) = (unsigned char)(((float)j / height) * 255);
			*(tmp_data+2) = 127;
			tmp_data += 3;
		}
	}
	write_ppm(data, width, height);
	free(data);
	printf("\nDone.\n");
	return 0;
}