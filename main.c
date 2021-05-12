#include <stdio.h>
#include <stdlib.h>
#include "ppmio.h"

int main(int argc, char *argv[])
{
	unsigned int width = 1024;
	unsigned int height = 512;
	unsigned char *data = (unsigned char *)malloc(width * height * 3);
	unsigned char *orig_data = data;
	int i, j, k;
	int foo = 0;
	for (j = height-1; j >= 0; j--)
	{
		for (i = 0; i < width; i++)
		{
			// TODO: Render Code
			*data = (unsigned char)(((float)i / width) * 255);
			*(data+1) = (unsigned char)(((float)j / height) * 255);
			*(data+2) = 127;
			data += 3;
		}
	}
	write_ppm(orig_data, width, height);
	free(orig_data);
	return 0;
}