#include <stdio.h>
#include <stdlib.h>
#include "ppmio.h"

int main(int argc, char *argv[]) {
	unsigned int width = 2048;
	unsigned int height = 2048;
	// Create and fill data
	unsigned char *data = (unsigned char *)malloc(sizeof(unsigned char) * width * height * 3);
	unsigned char *tmp_data = data;
	int i, j, k;
	for (i=0; i<width; i++)
	{
		for (j=0; j<height; j++)
		{
			*tmp_data = (unsigned char)(((float)i / height) * 255);
			*(tmp_data+1) = (unsigned char)(((float)j / height) * 255);
			*(tmp_data+2) = 0;
			tmp_data += 3;
		}
	}
	write_ppm(data, width, height);
	free(data);
	return 0;
}