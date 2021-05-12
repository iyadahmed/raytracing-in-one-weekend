#include <stdio.h>
#include <stdlib.h>
#include "ppmio.h"

int offset(int i, int j, int k, int width, int height) { 
    return (i * width * 3) + (j * 3) + k;
}

int main(int argc, char *argv[]) {
	unsigned int width = 1024;
	unsigned int height = 1024;
	// Create and fill data
	unsigned char *data = (unsigned char *)malloc(sizeof(unsigned char) * width * height * 3);
	int i, j, k;
	for (i=0; i<width; i++)
	{
		for (j=0; j<height; j++)
		{
//			*data = (unsigned char)(((float)i / height) * 255);
//			*(data+1) = (unsigned char)(((float)j / height) * 255);
//			*(data+2) = 0;
//			data += 3;
			data[offset(i, j, 0, width, height)] = (unsigned char)(((float)i / height) * 255);
			data[offset(i, j, 1, width, height)] = (unsigned char)(((float)j / width) * 255);
			data[offset(i, j, 2, width, height)] = 0;
		}
	}
	write_ppm(data, width, height);
	free(data);
	return 0;
}