#include <stdio.h>
#include <stdlib.h>
#include "ppmio.h"


int main(int argc, char *argv[]) {
	unsigned int width = 256;
	unsigned int height = 256;
	// Create and fill data
	unsigned char data[width][height][3];
	int i, j, k;
	for (j=height-1; j>=0; --j)
	{
		for (i=width-1; i>=0; --i)
		{
			data[i][j][0] = (unsigned char)(((float)j / height) * 255);
			data[i][j][1] = (unsigned char)(((float)i / width) * 255);
			data[i][j][2] = 0;
		}
	}
	write_ppm(data, width, height);
	return 0;
}