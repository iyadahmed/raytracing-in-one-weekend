#ifndef PPM_H
#define PPM_H

#include <stdio.h>

void write_ppm()
{
	int width = 256;
	int height = 256;
	FILE *fptr;
	fptr = fopen("image.ppm", "wb");
	if (fptr == NULL)
	{
		printf("Erorr opening file\n");
		exit(1);
	}
	fprintf(fptr, "P6\n%d %d\n255\n", width, height);
	unsigned char data[width][height][3];
	int i, j, k;
	for (j=0; j<width; j++)
	{
		for (i=0; i<height; i++)
		{
			data[i][j][0] = (unsigned char)(((float)j / width) * 255);
			data[i][j][1] = 0;
			data[i][j][2] = 0;
		}
	}
	fwrite(data, sizeof(unsigned char), width * height * 3, fptr);
	fclose(fptr);
}

#endif